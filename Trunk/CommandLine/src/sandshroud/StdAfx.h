// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

#ifdef WIN32
#define _INLINE __forceinline
#else
#define _INLINE inline
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include <errno.h>

#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
#	define WIN32_LEAN_AND_MEAN
#	define _WIN32_WINNT 0x0500
#	define NOMINMAX
#	include <windows.h>
#else
#	include <string.h>
#	define MAX_PATH 1024
#endif

#include <set>
#include <list>
#include <string>
#include <map>
#include <queue>
#include <sstream>
#include <algorithm>

#include <list>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <fstream>
#include <iosfwd>
#include <search.h>
#include <fcntl.h>
#include <signal.h>

#define COMPILER_MICROSOFT	0
#define COMPILER_GNU		1
#define COMPILER_BORLAND	2
#define COMPILER_INTEL		3

#ifdef _MSC_VER
#	define COMPILER COMPILER_MICROSOFT
#elif defined( __INTEL_COMPILER )
#	define COMPILER COMPILER_INTEL
#elif defined( __BORLANDC__ )
#	define COMPILER COMPILER_BORLAND
#elif defined( __GNUC__ )
#	define COMPILER COMPILER_GNU
#else
#	pragma error "FATAL ERROR: Unknown compiler."
#endif

#if COMPILER != COMPILER_GNU

typedef signed __int64 int64;
typedef signed __int32 int32;
typedef signed __int16 int16;
typedef signed __int8 int8;

typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef unsigned __int16 uint16;
typedef unsigned __int8 uint8;

#else

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
typedef uint32_t DWORD;

#endif

using namespace System;
using namespace System::Threading;
using namespace std;

#include "SystemManager.h"
#include "Master.h"
