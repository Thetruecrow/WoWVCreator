#pragma once

class Master
{
public:
	Master();
	~Master();
	int Run(int argc, char ** argv);

	static volatile bool m_stopEvent;

private:
	void _HookSignals();
	void _UnhookSignals();

	static void _OnSignal(int s);
};
