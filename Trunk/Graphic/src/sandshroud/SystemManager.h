
#pragma once

namespace sandshroud
{
	public ref class SystemManager
	{
		bool m_threadRunning;
	public:
		SystemManager();
		~SystemManager();

		Thread^ Run();
		void Init();
		void Shutdown();
	};
}
