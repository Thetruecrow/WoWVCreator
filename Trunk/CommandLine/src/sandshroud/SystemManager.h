
#pragma once

ref class SystemManager;

typedef void(*exp_script_register)(SystemManager^ mgr);
typedef uint32(*exp_get_script_type)();
typedef void(*exp_script_update)();
typedef uint32(*exp_get_version)();

#define DLL_WORLD_RUNNER 0x42

struct ScriptDLLs
{
#ifdef WIN32
	HMODULE Handle;
#else
	void* Handle;
#endif
	exp_script_register InitializeCall;
	exp_script_update UpdateCall;
	uint32 Type;
	uint32 highrev;
	uint32 lowrev;
};

extern vector<ScriptDLLs> DLLScriptVector;

public ref class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	/*********************************************************************************
	 * Runs our thread, also handles updating of any DLLs that aren't multithreaded. *
	 *********************************************************************************/
	void Run();

	/***************************************************************
	 * Fills our DLL list, assigning our world DLL and any others. *
	 ***************************************************************/
	void Init();

	/************************************************
	 * Console writing commands, prints information *
	 ************************************************/
	void WriteConsole(const char* message);
	void WriteConsole(std::string str) { WriteConsole(str.c_str()); };
private:
	Thread^ Main;
};
