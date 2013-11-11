
#include "StdAfx.h"

using namespace sandshroud;

SystemManager::SystemManager()
{
	m_threadRunning = true;
}

SystemManager::~SystemManager()
{

}

Thread^ SystemManager::Run()
{
	Thread^ ThreadThis = gcnew Thread(gcnew ThreadStart(this, &SystemManager::Init));
	ThreadThis->Start();
	return ThreadThis;
}

void SystemManager::Init()
{
	LogSet.insert("Starting System Manager...\r\n");
	while(m_threadRunning)
	{
		Thread::Sleep(5);
	}
}

void SystemManager::Shutdown()
{
	m_threadRunning = false;
}