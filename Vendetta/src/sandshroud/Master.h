
#ifndef MASTER_H
#define MASTER_H

namespace sandshroud
{
	public ref class Master
	{
	public:
		bool m_threadRunning;
		SystemManager^ manager;
		MainForm^ window;

	public:
		Master() {};
		~Master() {};

		void SaveValues();

	public:
		int Run();
		void StartLog();
	};
}

//#define sMaster Master::getSingleton()

#endif // MASTER_H
