
#include "StdAfx.h"

using namespace sandshroud;

char* PreferedStructure = "";

BuildInfoMap ItemInfoLibs;
BuildInfoMap CreatureInfoLibs;
BuildInfoMap VendorInfoLibs;
BuildInfoMap LootInfoLibs;

SystemManager::SystemManager(Master^ master)
{
	masterClass = master;
	m_threadRunning = true;
}

SystemManager::~SystemManager()
{
	delete configfile;
}

Thread^ SystemManager::Run()
{
	Thread^ ThreadThis = gcnew Thread(gcnew ThreadStart(this, &SystemManager::Init));
	ThreadThis->Start();
	return ThreadThis;
}

void SystemManager::Init()
{
	SystemPrintf("Starting System Manager...");

	ReloadLibraries();

	ReadConfigs();

	while(m_threadRunning)
	{
		Thread::Sleep(5);
	}
}

void SystemManager::Shutdown()
{
	m_threadRunning = false;
}

void SystemManager::ReloadLibraries()
{
	string search_path = "./Plugins/";

	WIN32_FIND_DATA data;
	uint32 count = 0;
	HANDLE find_handle = FindFirstFile( string(search_path+string("*.dll")).c_str(), &data );
	if(find_handle == INVALID_HANDLE_VALUE)
		SystemPrintf("No external scripts found." );
	else
	{
		do
		{
			string full_path = search_path + data.cFileName;
			HMODULE mod = LoadLibrary( full_path.c_str() );
			if( mod == 0 )
				SystemPrintfDebug("Loading %s failed, crc=0x%p", data.cFileName, reinterpret_cast< uint32* >( mod ));
			else
			{
				// find version import
				exp_get_script_type scall = (exp_get_script_type)GetProcAddress(mod, "_exp_get_script_type");
				if(scall == 0)
				{
					SystemPrintfDebug("Loading %s failed, version info not found", data.cFileName);
					FreeLibrary(mod);
				}
				else
				{
					int DLLType = scall();
					switch(DLLType)
					{
					case SCRIPT_TYPE_ITEM_INFO:
						{
							exp_script_register rcall = (exp_script_register)GetProcAddress(mod, "_exp_script_register");
							exp_request_tablename tncall = (exp_request_tablename)GetProcAddress(mod, "_exp_request_tablename");
							exp_request_fieldcount fccall = (exp_request_fieldcount)GetProcAddress(mod, "_exp_request_fieldcount");
							if(rcall == NULL || tncall == NULL || fccall == NULL)
							{
								SystemPrintfDebug("Loading %s failed, structure call not found!", data.cFileName);
								FreeLibrary(mod);
							}
							else
							{
								FieldInfo* finfo;
								exp_request_fieldinfo ficall = (exp_request_fieldinfo)GetProcAddress(mod, "_exp_request_fieldinfo");
								if(ficall == NULL || (finfo = ficall()) == NULL)
								{
									SystemPrintfDebug("Loading %s failed, structure info not found!", data.cFileName);
									FreeLibrary(mod);
								}
								else
								{
									int fieldcount = fccall();
									if(fieldcount > ITEM_BUILD_MAX)
									{
										SystemPrintfDebug("Loading %s failed, Fieldcount mismatch! (%u/%u)", data.cFileName, fieldcount, ITEM_BUILD_MAX);
										FreeLibrary(mod);
									}
									else
									{
										char *name = rcall(), *tablename = tncall();

										InsertBuildInfo* buildinfo = new InsertBuildInfo(name, tablename);
										buildinfo->maxfields = fieldcount;
										memcpy(&buildinfo->fieldinfo, &finfo, sizeof(FieldInfo*));

										// Crow: memory copy it because we'll lose the other memory control when we unhook the dll
										if(buildinfo != NULL)
										{
											SystemPrintf("Success loading %s; Build info: %s", data.cFileName, buildinfo->BuildName);
											if(ItemInfoLibs.find(buildinfo->BuildName) == ItemInfoLibs.end())
												ItemInfoLibs.insert(make_pair(buildinfo->BuildName, buildinfo));
											count++;
										}
										else
											SystemPrintfDebug("Loading %s failed, call returned null structure!", data.cFileName);
									}
								}
							}
						}break;
					case SCRIPT_TYPE_CREATURE_INFO:
						{
							exp_script_register rcall = (exp_script_register)GetProcAddress(mod, "_exp_script_register");
							exp_request_tablename tncall = (exp_request_tablename)GetProcAddress(mod, "_exp_request_tablename");
							exp_request_fieldcount fccall = (exp_request_fieldcount)GetProcAddress(mod, "_exp_request_fieldcount");
							if(rcall == NULL || tncall == NULL || fccall == NULL)
							{
								SystemPrintfDebug("Loading %s failed, structure call not found!", data.cFileName);
								FreeLibrary(mod);
							}
							else
							{
								FieldInfo* finfo;
								exp_request_fieldinfo ficall = (exp_request_fieldinfo)GetProcAddress(mod, "_exp_request_fieldinfo");
								if(ficall == NULL || (finfo = ficall()) == NULL)
								{
									SystemPrintfDebug("Loading %s failed, structure info not found!", data.cFileName);
									FreeLibrary(mod);
								}
								else
								{
									int fieldcount = fccall();
									if(fieldcount > BUILD_INFO_MAX_FIELDS)
									{
										SystemPrintfDebug("Loading %s failed, Fieldcount mismatch! (%u/%u)", data.cFileName, fieldcount, ITEM_BUILD_MAX);
										FreeLibrary(mod);
									}
									else
									{
										char *name = rcall(), *tablename = tncall();

										InsertBuildInfo* buildinfo = new InsertBuildInfo(name, tablename);
										buildinfo->maxfields = fieldcount;
										memcpy(&buildinfo->fieldinfo, &finfo, sizeof(FieldInfo*));

										// Crow: memory copy it because we'll lose the other memory control when we unhook the dll
										if(buildinfo != NULL)
										{
											SystemPrintf("Success loading %s; Build info: %s", data.cFileName, buildinfo->BuildName);
											if(CreatureInfoLibs.find(buildinfo->BuildName) == CreatureInfoLibs.end())
												CreatureInfoLibs.insert(make_pair(buildinfo->BuildName, buildinfo));
											count++;
										}
										else
											SystemPrintfDebug("Loading %s failed, call returned null structure!", data.cFileName);
									}
								}
							}
						}break;
					case SCRIPT_TYPE_VENDOR_INFO:
						{
							exp_script_register rcall = (exp_script_register)GetProcAddress(mod, "_exp_script_register");
							exp_request_tablename tncall = (exp_request_tablename)GetProcAddress(mod, "_exp_request_tablename");
							exp_request_fieldcount fccall = (exp_request_fieldcount)GetProcAddress(mod, "_exp_request_fieldcount");
							if(rcall == NULL || tncall == NULL || fccall == NULL)
							{
								SystemPrintfDebug("Loading %s failed, structure call not found!", data.cFileName);
								FreeLibrary(mod);
							}
							else
							{
								FieldInfo* finfo;
								exp_request_fieldinfo ficall = (exp_request_fieldinfo)GetProcAddress(mod, "_exp_request_fieldinfo");
								if(ficall == NULL || (finfo = ficall()) == NULL)
								{
									SystemPrintfDebug("Loading %s failed, structure info not found!", data.cFileName);
									FreeLibrary(mod);
								}
								else
								{
									int fieldcount = fccall();
									if(fieldcount > BUILD_INFO_MAX_FIELDS)
									{
										SystemPrintfDebug("Loading %s failed, Fieldcount mismatch! (%u/%u)", data.cFileName, fieldcount, ITEM_BUILD_MAX);
										FreeLibrary(mod);
									}
									else
									{
										char *name = rcall(), *tablename = tncall();

										InsertBuildInfo* buildinfo = new InsertBuildInfo(name, tablename);
										buildinfo->maxfields = fieldcount;
										memcpy(&buildinfo->fieldinfo, &finfo, sizeof(FieldInfo*));

										// Crow: memory copy it because we'll lose the other memory control when we unhook the dll
										if(buildinfo != NULL)
										{
											SystemPrintf("Success loading %s; Build info: %s", data.cFileName, buildinfo->BuildName);
											if(VendorInfoLibs.find(buildinfo->BuildName) == VendorInfoLibs.end())
												VendorInfoLibs.insert(make_pair(buildinfo->BuildName, buildinfo));
											count++;
										}
										else
											SystemPrintfDebug("Loading %s failed, call returned null structure!", data.cFileName);
									}
								}
							}
						}break;
					case SCRIPT_TYPE_LOOT_INFO:
						{
							exp_script_register rcall = (exp_script_register)GetProcAddress(mod, "_exp_script_register");
							exp_request_tablename tncall = (exp_request_tablename)GetProcAddress(mod, "_exp_request_tablename");
							exp_request_fieldcount fccall = (exp_request_fieldcount)GetProcAddress(mod, "_exp_request_fieldcount");
							if(rcall == NULL || tncall == NULL || fccall == NULL)
							{
								SystemPrintfDebug("Loading %s failed, structure call not found!", data.cFileName);
								FreeLibrary(mod);
							}
							else
							{
								FieldInfo* finfo;
								exp_request_fieldinfo ficall = (exp_request_fieldinfo)GetProcAddress(mod, "_exp_request_fieldinfo");
								if(ficall == NULL || (finfo = ficall()) == NULL)
								{
									SystemPrintfDebug("Loading %s failed, structure info not found!", data.cFileName);
									FreeLibrary(mod);
								}
								else
								{
									int fieldcount = fccall();
									if(fieldcount > BUILD_INFO_MAX_FIELDS)
									{
										SystemPrintfDebug("Loading %s failed, Fieldcount mismatch! (%u/%u)", data.cFileName, fieldcount, ITEM_BUILD_MAX);
										FreeLibrary(mod);
									}
									else
									{
										char *name = rcall(), *tablename = tncall();

										InsertBuildInfo* buildinfo = new InsertBuildInfo(name, tablename);
										buildinfo->maxfields = fieldcount;
										memcpy(&buildinfo->fieldinfo, &finfo, sizeof(FieldInfo*));

										// Crow: memory copy it because we'll lose the other memory control when we unhook the dll
										if(buildinfo != NULL)
										{
											SystemPrintf("Success loading %s; Build info: %s", data.cFileName, buildinfo->BuildName);
											if(LootInfoLibs.find(buildinfo->BuildName) == LootInfoLibs.end())
												LootInfoLibs.insert(make_pair(buildinfo->BuildName, buildinfo));
											count++;
										}
										else
											SystemPrintfDebug("Loading %s failed, call returned null structure!", data.cFileName);
									}
								}
							}
						}break;
					case SCRIPT_TYPE_SERVER_CONNECTOR:
						{
							SystemPrintfDebug("System not available yet");
						}break;
					}
				}
			}
		}while(FindNextFile(find_handle, &data));

		FindClose(find_handle);
		SystemPrintf("Loading %u external libraries.", count);
	}
}

InsertBuildInfo* SystemManager::GetInsertBuildInfo(uint32 calltype, char* name)
{
	switch(calltype)
	{
	case SCRIPT_TYPE_ITEM_INFO:
		{
			if(!ItemInfoLibs.size())
				return NULL;

			for(BuildInfoMap::iterator itr = ItemInfoLibs.begin(); itr != ItemInfoLibs.end(); itr++)
			{
				if(strcmp(itr->first, name) == 0)
					return itr->second;
			}
		}break;
	case SCRIPT_TYPE_CREATURE_INFO:
		{
			if(!CreatureInfoLibs.size())
				return NULL;

			for(BuildInfoMap::iterator itr = CreatureInfoLibs.begin(); itr != CreatureInfoLibs.end(); itr++)
			{
				if(strcmp(itr->first, name) == 0)
					return itr->second;
			}
		}break;
	case SCRIPT_TYPE_VENDOR_INFO:
		{
			if(!VendorInfoLibs.size())
				return NULL;

			for(BuildInfoMap::iterator itr = VendorInfoLibs.begin(); itr != VendorInfoLibs.end(); itr++)
			{
				if(strcmp(itr->first, name) == 0)
					return itr->second;
			}
		}break;
	case SCRIPT_TYPE_LOOT_INFO:
		{
			if(!LootInfoLibs.size())
				return NULL;

			for(BuildInfoMap::iterator itr = LootInfoLibs.begin(); itr != LootInfoLibs.end(); itr++)
			{
				if(strcmp(itr->first, name) == 0)
					return itr->second;
			}
		}break;
	}
	return NULL;
}

bool SystemManager::GetPrefered(char* core, uint32 calltype)
{
	if(PreferedStructure == "")
		return false;

	switch(calltype)
	{
	case SCRIPT_TYPE_ITEM_INFO:
		{
			if(!ItemInfoLibs.size())
				return false;

			if(ItemInfoLibs.find(PreferedStructure) != ItemInfoLibs.end())
			{
				core = PreferedStructure;
				return true;
			}
		}break;
	case SCRIPT_TYPE_CREATURE_INFO:
		{
			if(!CreatureInfoLibs.size())
				return false;

			if(CreatureInfoLibs.find(PreferedStructure) != CreatureInfoLibs.end())
			{
				core = PreferedStructure;
				return true;
			}
		}break;
	case SCRIPT_TYPE_VENDOR_INFO:
		{
			if(!VendorInfoLibs.size())
				return false;

			if(VendorInfoLibs.find(PreferedStructure) != VendorInfoLibs.end())
			{
				core = PreferedStructure;
				return true;
			}
		}break;
	case SCRIPT_TYPE_LOOT_INFO:
		{
			if(!LootInfoLibs.size())
				return false;

			if(LootInfoLibs.find(PreferedStructure) != LootInfoLibs.end())
			{
				core = PreferedStructure;
				return true;
			}
		}break;
	}
	return false;
}

void SystemManager::ReadConfigs()
{
	SystemPrintfDebug("Reading config files...");

	FILE* config = fopen("Configuration.ini", "rb");
	if(config == NULL)
	{

		SystemPrintfDebug("Config file not found! Creating...");
		fclose(fopen("Configuration.ini", "wb")); // Create the file...
		configfile = new CIniFile("./Configuration.ini");
		configfile->WriteString("Settings", "ServerName", (ServerAdress = "wow-v.com"));
		SystemPrintfDebug("ServerName: %s", ServerAdress);

		configfile->WriteInteger("Settings", "ServerPort", (SPort = 11443));
		SystemPrintfDebug("ServerPort: %u", SPort);

		configfile->WriteString("Settings", "PreferedServer", (PreferedStructure = ""));
		SystemPrintfDebug("PreferedServer: %s", PreferedStructure);
	}
	else
	{	fclose(config);

		SystemPrintfDebug("Config file found!");
		configfile = new CIniFile("./Configuration.ini");
		ServerAdress = configfile->ReadString("Settings", "ServerName", "wow-v.com");
		SystemPrintfDebug("ServerName: %s", ServerAdress);

		SPort = configfile->ReadInteger("Settings", "ServerPort", 11443);
		SystemPrintfDebug("ServerPort: %u", SPort);

		PreferedStructure = configfile->ReadString("Settings", "PreferedServer", "");
		SystemPrintfDebug("PreferedServer: %s", PreferedStructure);
	}
}
