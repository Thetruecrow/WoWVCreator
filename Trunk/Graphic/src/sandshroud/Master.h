
#ifndef MASTER_H
#define MASTER_H

namespace sandshroud
{
	public ref class Master
	{
		bool m_threadRunning;
		SystemManager^ manager;
		MainForm^ window;
	public:
		Master() { m_threadRunning = true; };
		~Master() {};

	public:
		int Run();
		void StartLog();
	};
}

//#define sMaster Master::getSingleton()

#endif // MASTER_H
