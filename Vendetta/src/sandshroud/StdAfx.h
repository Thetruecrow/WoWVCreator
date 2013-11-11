// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

#define _CRT_SECURE_NO_WARNINGS

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
using namespace System::Runtime::InteropServices; // for class Marshal
using namespace std;

void SystemPrintf(char* format, ...);
void SystemPrintfDebug(char* format, ...);

struct TableInfoStruct
{
	TableInfoStruct(char* base) { val = (char*)(void*)Marshal::StringToHGlobalAnsi(gcnew System::String(base)); };
	~TableInfoStruct() { Marshal::FreeHGlobal((System::IntPtr)(void*)val); };
	char* val;
};

namespace sandshroud
{
	ref class Master;
}

#define FIELDTYPE_INT 1
#define FIELDTYPE_CHAR 2
#define FIELDTYPE_FLOAT 3

enum ItemBuildInfo
{
	 ITEM_BUILD_INFO_NAME = 0,
	 ITEM_BUILD_INFO_QUOTE,
	 ITEM_BUILD_INFO_QUALITY,
	 ITEM_BUILD_INFO_DISPLAY_ID,
	 ITEM_BUILD_INFO_ENTRY_ID,
	 ITEM_BUILD_INFO_INVENTORY_TYPE,
	 ITEM_BUILD_INFO_CLASS,
	 ITEM_BUILD_INFO_SUB_CLASS,
	 ITEM_BUILD_INFO_REPAIR_TYPE,
	 ITEM_BUILD_INFO_DURABILITY,
	 ITEM_BUILD_INFO_BINDTYPE,
	 ITEM_BUILD_INFO_SHEATH_TYPE,
	 ITEM_BUILD_INFO_AMMO_TYPE,
	 ITEM_BUILD_INFO_SPEED,
	 ITEM_BUILD_INFO_BLOCK,
	 ITEM_BUILD_INFO_ARMOR,
	 ITEM_BUILD_INFO_REQUIRED_LEVEL,
	 ITEM_BUILD_INFO_ITEM_LEVEL,
	 ITEM_BUILD_INFO_REQUIRED_FACTION,
	 ITEM_BUILD_INFO_REQUIRED_FACTION_LEVEL,
	 ITEM_BUILD_INFO_REQUIRED_SKILL,
	 ITEM_BUILD_INFO_REQUIRED_SKILL_LEVEL,
	 ITEM_BUILD_INFO_REQUIRED_SPELL,
	 ITEM_BUILD_INFO_UNIQUE,
	 ITEM_BUILD_INFO_MAX_STACK,
	 ITEM_BUILD_INFO_ALLOWABLE_CLASS,
	 ITEM_BUILD_INFO_ALLOWABLE_RACE,
	 ITEM_BUILD_INFO_DAMAGE_MIN_1,
	 ITEM_BUILD_INFO_DAMAGE_MAX_1,
	 ITEM_BUILD_INFO_DAMAGE_TYPE_1,
	 ITEM_BUILD_INFO_DAMAGE_MIN_2,
	 ITEM_BUILD_INFO_DAMAGE_MAX_2,
	 ITEM_BUILD_INFO_DAMAGE_TYPE_2,
	 ITEM_BUILD_INFO_STAT_TYPE_1,
	 ITEM_BUILD_INFO_STAT_VALUE_1,
	 ITEM_BUILD_INFO_STAT_TYPE_2,
	 ITEM_BUILD_INFO_STAT_VALUE_2,
	 ITEM_BUILD_INFO_STAT_TYPE_3,
	 ITEM_BUILD_INFO_STAT_VALUE_3,
	 ITEM_BUILD_INFO_STAT_TYPE_4,
	 ITEM_BUILD_INFO_STAT_VALUE_4,
	 ITEM_BUILD_INFO_STAT_TYPE_5,
	 ITEM_BUILD_INFO_STAT_VALUE_5,
	 ITEM_BUILD_INFO_STAT_TYPE_6,
	 ITEM_BUILD_INFO_STAT_VALUE_6,
	 ITEM_BUILD_INFO_STAT_TYPE_7,
	 ITEM_BUILD_INFO_STAT_VALUE_7,
	 ITEM_BUILD_INFO_STAT_TYPE_8,
	 ITEM_BUILD_INFO_STAT_VALUE_8,
	 ITEM_BUILD_INFO_STAT_TYPE_9,
	 ITEM_BUILD_INFO_STAT_VALUE_9,
	 ITEM_BUILD_INFO_STAT_TYPE_10,
	 ITEM_BUILD_INFO_STAT_VALUE_10,
	 ITEM_BUILD_INFO_HOLY_RESISTANCE,
	 ITEM_BUILD_INFO_FIRE_RESISTANCE,
	 ITEM_BUILD_INFO_NATURE_RESISTANCE,
	 ITEM_BUILD_INFO_FROST_RESISTANCE,
	 ITEM_BUILD_INFO_SHADOW_RESISTANCE,
	 ITEM_BUILD_INFO_ARCANE_RESISTANCE,
	 ITEM_BUILD_INFO_SPELLID_1,
	 ITEM_BUILD_INFO_SPELL_TRIGGER_1,
	 ITEM_BUILD_INFO_SPELL_CHARGES_1,
	 ITEM_BUILD_INFO_SPELL_COOLDOWN_1,
	 ITEM_BUILD_INFO_SPELL_CATEGORY_1,
	 ITEM_BUILD_INFO_SPELL_SPELL_CATEGORY_1,
	 ITEM_BUILD_INFO_SPELLID_2,
	 ITEM_BUILD_INFO_SPELL_TRIGGER_2,
	 ITEM_BUILD_INFO_SPELL_CHARGES_2,
	 ITEM_BUILD_INFO_SPELL_COOLDOWN_2,
	 ITEM_BUILD_INFO_SPELL_CATEGORY_2,
	 ITEM_BUILD_INFO_SPELL_SPELL_CATEGORY_2,
	 ITEM_BUILD_INFO_SPELLID_3,
	 ITEM_BUILD_INFO_SPELL_TRIGGER_3,
	 ITEM_BUILD_INFO_SPELL_CHARGES_3,
	 ITEM_BUILD_INFO_SPELL_COOLDOWN_3,
	 ITEM_BUILD_INFO_SPELL_CATEGORY_3,
	 ITEM_BUILD_INFO_SPELL_SPELL_CATEGORY_3,
	 ITEM_BUILD_INFO_SPELLID_4,
	 ITEM_BUILD_INFO_SPELL_TRIGGER_4,
	 ITEM_BUILD_INFO_SPELL_CHARGES_4,
	 ITEM_BUILD_INFO_SPELL_COOLDOWN_4,
	 ITEM_BUILD_INFO_SPELL_CATEGORY_4,
	 ITEM_BUILD_INFO_SPELL_SPELL_CATEGORY_4,
	 ITEM_BUILD_INFO_SPELLID_5,
	 ITEM_BUILD_INFO_SPELL_TRIGGER_5,
	 ITEM_BUILD_INFO_SPELL_CHARGES_5,
	 ITEM_BUILD_INFO_SPELL_COOLDOWN_5,
	 ITEM_BUILD_INFO_SPELL_CATEGORY_5,
	 ITEM_BUILD_INFO_SPELL_SPELL_CATEGORY_5,
	 ITEM_BUILD_INFO_SOCKET_TYPE_1,
	 ITEM_BUILD_INFO_SOCKET_TYPE_2,
	 ITEM_BUILD_INFO_SOCKET_TYPE_3,
	 ITEM_BUILD_INFO_SOCKET_BONUS,
	 ITEM_BUILD_INFO_SET_ID,
	 ITEM_BUILD_INFO_BUY_PRICE,
	 ITEM_BUILD_INFO_SELL_PRICE,
	 ITEM_BUILD_MAX
};

#define BUILD_INFO_MAX_FIELDS 150

struct FieldInfo
{
	FieldInfo()
	{
		memset(&fieldtype, 0, sizeof(int)*ITEM_BUILD_MAX);
		memset(&fieldname, 0, sizeof(char*)*ITEM_BUILD_MAX);
	}

	int fieldtype[ITEM_BUILD_MAX];
	char* fieldname[ITEM_BUILD_MAX];
};

struct InsertBuildInfo
{
	InsertBuildInfo(char* name, char* tablename)
	{
		BuildName = name;
		ItemTableName = tablename;
		maxfields = 0;
		fieldinfo = new FieldInfo();
	};

	InsertBuildInfo(char* name, char* tablename, unsigned int _maxfields, int* _fieldtype, char** _fieldname)
	{
		BuildName = name;
		ItemTableName = tablename;
		maxfields = _maxfields;
		fieldinfo = new FieldInfo();
	};

	char* BuildName;
	char* ItemTableName;
	unsigned int maxfields;
	FieldInfo* fieldinfo;
};

typedef std::map<char*, InsertBuildInfo*> BuildInfoMap;

#define SCRIPT_TYPE_ITEM_INFO 1
#define SCRIPT_TYPE_CREATURE_INFO 2
#define SCRIPT_TYPE_VENDOR_INFO 3
#define SCRIPT_TYPE_LOOT_INFO 4
#define SCRIPT_TYPE_SERVER_CONNECTOR 5

#include "IniFiles.h"
#include "MainForm.h"
#include "SystemManager.h"
#include "Master.h"
