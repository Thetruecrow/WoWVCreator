
#include "StdAfx.h"

using namespace sandshroud;

int Master::Run()
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Create the main window
	window = gcnew MainForm();

	// Start our DLL loading system.
	manager = gcnew SystemManager();
	Thread^ ManagerThread = manager->Run();

	// Create our Console Logs :P
	Thread^ consolethread = gcnew Thread(gcnew ThreadStart(this, &Master::StartLog));
	consolethread->Start();

	// Start our thread work, run the window.
	Application::Run(window);
	m_threadRunning = false;
	manager->Shutdown();

	delete ManagerThread;
	delete consolethread;
	delete manager;
	return 0;
}

void Master::StartLog()
{
	while(m_threadRunning)
	{
		window->CallWriteToConsole();
		Thread::Sleep(5);
	}
}
