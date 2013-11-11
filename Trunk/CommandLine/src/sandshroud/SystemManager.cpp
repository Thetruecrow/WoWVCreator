
#include "StdAfx.h"

vector<ScriptDLLs> DLLScriptVector;

#define SCRIPTLIB_HIPART(x) ((x >> 16))
#define SCRIPTLIB_LOPART(x) ((x & 0x0000ffff))

SystemManager::SystemManager()
{

}

SystemManager::~SystemManager()
{

}

void SystemManager::Run()
{
	Init();
	while(!Master::m_stopEvent)
	{
		for(vector<ScriptDLLs>::iterator itr = DLLScriptVector.begin(); itr != DLLScriptVector.end(); itr++)
			(*itr).UpdateCall();
		Thread::Sleep(5);
	}
}

void SystemManager::Init()
{
	/* Loading system for win32 */
#ifdef WIN32
	string search_path = "./Plugins/*.dll";

	WIN32_FIND_DATA data;
	uint32 count = 0;
	HANDLE find_handle = FindFirstFile( search_path.c_str(), &data );
	if(find_handle == INVALID_HANDLE_VALUE)
		WriteConsole("No external scripts found." );
	else
	{
		do
		{
			string full_path = data.cFileName;
			HMODULE mod = LoadLibrary( full_path.c_str() );
			if( mod == 0 )
				printf("Loading %s failed, crc=0x%p\r\n", data.cFileName, reinterpret_cast< uint32* >( mod ));
			else
			{
				// find version import
				exp_get_version vcall = (exp_get_version)GetProcAddress(mod, "_exp_get_version");
				exp_script_update ucall = (exp_script_update)GetProcAddress(mod, "_exp_script_update");
				exp_script_register rcall = (exp_script_register)GetProcAddress(mod, "_exp_script_register");
				exp_get_script_type scall = (exp_get_script_type)GetProcAddress(mod, "_exp_get_script_type");
				if(vcall == 0 || rcall == 0 || scall == 0 || ucall == 0)
				{
					printf("Loading %s failed, version info not found\r\n", data.cFileName);
					FreeLibrary(mod);
				}
				else
				{
					uint32 version = vcall();
					uint32 stype = scall();
					uint32 versionhigh = SCRIPTLIB_HIPART(version), versionlow = SCRIPTLIB_LOPART(version);
					std::stringstream cmsg;
					cmsg << "Loading " << data.cFileName << ", crc:0x" << reinterpret_cast< uint32* >( mod );
					cmsg << ", Version:" << versionhigh << " " << versionlow << " delayed loading.";

					ScriptDLLs se;
					se.Handle = mod;
					se.InitializeCall = rcall;
					se.UpdateCall = ucall;
					se.Type = stype;
					se.highrev = versionhigh;
					se.lowrev = versionlow;
					DLLScriptVector.push_back( se );
					WriteConsole(cmsg.str());
					++count;
				}
			}
		}while(FindNextFile(find_handle, &data));

		FindClose(find_handle);
		printf("Loading %u external libraries.\r\n", count);
		for(vector<ScriptDLLs>::iterator itr = DLLScriptVector.begin(); itr != DLLScriptVector.end(); itr++)
			(*itr).InitializeCall(this);
	}

#else

	/* Loading system for *nix */
	struct dirent ** list;
	int filecount = scandir(PREFIX "/lib/", &list, 0, 0);
	uint32 count = 0;

	if(!filecount || !list || filecount < 0)
		WriteConsole("No external scripts found.");
	else
	{
char *ext;
		while(filecount--)
		{
			ext = strrchr(list[filecount]->d_name, '.');
#ifdef HAVE_DARWIN
			if (ext != NULL && strstr(list[filecount]->d_name, ".0.dylib") == NULL && !strcmp(ext, ".dylib")) {
#else
			if (ext != NULL && !strcmp(ext, ".so")) {
#endif
				string full_path = "../lib/" + string(list[filecount]->d_name);
				SCRIPT_MODULE mod = dlopen(full_path.c_str(), RTLD_NOW);
				printf("  %s : 0x%p : ", list[filecount]->d_name, mod);
				if(mod == 0)
					printf("error! [%s]\r\n", dlerror());
				else
				{
					// find version import
					exp_get_version vcall = (exp_get_version)dlsym(mod, "_exp_get_version");
					exp_script_update ucall = (exp_script_update)dlsym(mod, "_exp_script_update");
					exp_script_register rcall = (exp_script_register)dlsym(mod, "_exp_script_register");
					exp_get_script_type scall = (exp_get_script_type)dlsym(mod, "_exp_get_script_type");
					if(vcall == 0 || rcall == 0 || scall == 0 || ucall == 0)
					{
						WriteConsole("version functions not found!");
						dlclose(mod);
					}
					else
					{
						int32 version = vcall();
						uint32 stype = scall();
						uint32 versionhigh = SCRIPTLIB_HIPART(version), versionlow = SCRIPTLIB_LOPART(version);

						ScriptDLLs se;
						se.Handle = mod;
						se.InitializeCall = rcall;
						se.UpdateCall = ucall;
						se.Type = stype;
						se.highrev = versionhigh;
						se.lowrev = versionlow;
						DLLScriptVector.push_back( se );

						printf("v%u.%u : loaded.\r\n", versionhigh, versionlow);
						rcall(this);
						++count;
					}
				}
			}
			free(list[filecount]);
		}
		free(list);
		WriteConsole("");
		printf("Loaded %u external libraries.", count);
		WriteConsole("");

		WriteConsole("Loading optional scripting engines...");
		for(vector<ScriptingEngine>::iterator itr = ScriptEngines.begin(); itr != ScriptEngines.end(); itr++)
			itr->InitializeCall(this);
		WriteConsole("Done loading script engines...");
	}
#endif
}

void SystemManager::WriteConsole(const char* message)
{
	Console::Write(gcnew System::String(message)+"\r\n");
}