
#pragma once

namespace sandshroud
{
	typedef int(*exp_get_script_type)();
	typedef char*(*exp_script_register)();
	typedef char*(*exp_request_tablename)();
	typedef int(*exp_request_fieldcount)();
	typedef FieldInfo*(*exp_request_fieldinfo)();

	public ref class SystemManager
	{
	private:
		Master^ masterClass;

	public:
		CIniFile* configfile;

	public:
		InsertBuildInfo* GetInsertBuildInfo(uint32 calltype, char* name);
		bool GetPrefered(char* core, uint32 calltype);
		char* ServerAdress;
		unsigned int SPort;

	private:
		bool m_threadRunning;
		void ReadConfigs();

	public:
		SystemManager(Master^ master);
		~SystemManager();

		void ReloadLibraries();

		Thread^ Run();
		void Init();
		void Shutdown();
	};
}
