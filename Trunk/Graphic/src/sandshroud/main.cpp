// sandshroud.cpp : main project file.

#include "stdafx.h"

using namespace sandshroud;
using namespace System::Threading;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	return (gcnew Master())->Run();
}
