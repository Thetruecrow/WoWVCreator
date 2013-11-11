
#include "StdAfx.h"

using namespace sandshroud;
extern char* SelectedCore;
extern uint32 ItemSelectionCallType;
extern BuildInfoMap ItemInfoLibs;
extern BuildInfoMap CreatureInfoLibs;
extern BuildInfoMap VendorInfoLibs;
extern BuildInfoMap LootInfoLibs;

int Master::Run()
{
	m_threadRunning = true;

	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Create the main window
	window = gcnew MainForm(this);

	// Start our DLL loading system.
	manager = gcnew SystemManager(this);
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
		window->CallWriteToSystemBox();
		if(!m_threadRunning)
			break;

		Thread::Sleep(5);
		while(m_threadRunning && !SystemText.size())
			Thread::Sleep(5);
	}
}

TableInfoStruct* m_itemValues[ITEM_BUILD_MAX];
TableInfoStruct* m_CreatureValues[ITEM_BUILD_MAX];

char* GetValueFromIndex(uint32 from, char* indexvalue);

void Master::SaveValues()
{
	char usebuild[255];
	strcpy(usebuild, (char*)(void*)Marshal::StringToHGlobalAnsi(window->CoreSelectionBox->Text));
	if(strcmp(usebuild, "Unknown") == 0)
	{
		MessageBox::Show("Core information not found!");
		return;
	}

	SystemPrintfDebug("Searching for %s", usebuild);
	InsertBuildInfo* info = manager->GetInsertBuildInfo(ItemSelectionCallType, usebuild);
	if(info == NULL)
	{
		MessageBox::Show("Core information not found!");
		return;
	}

	CreateDirectory("./output", NULL);

	switch(ItemSelectionCallType)
	{
	case SCRIPT_TYPE_ITEM_INFO:
		{
			std::string name = "./output/";
			if(m_itemValues[ITEM_BUILD_INFO_ENTRY_ID] == NULL || !strlen(m_itemValues[ITEM_BUILD_INFO_ENTRY_ID]->val))
				name += "MUSTHAVEENTRYID";
			else
				name += m_itemValues[ITEM_BUILD_INFO_ENTRY_ID]->val;

			name += "-";

			if(m_itemValues[ITEM_BUILD_INFO_NAME] == NULL || !strlen(m_itemValues[ITEM_BUILD_INFO_NAME]->val))
				name += "UNKNOWN";
			else
				name += m_itemValues[ITEM_BUILD_INFO_NAME]->val;

			name += ".sql";

			char* filename = (char*)name.c_str();
			SystemPrintf("Creating file %s", filename);

			DeleteFile(filename);
			FILE* output = fopen(filename, "wb"); // Create the file...
			fprintf(output, "-- Structure based on DLL %s\n", SelectedCore);
			if(ItemSelectionCallType == SCRIPT_TYPE_CREATURE_INFO)
			{

			}
			else
			{
				FieldInfo* fieldinfo = info->fieldinfo;
				fprintf(output, "INSERT INTO %s(", info->ItemTableName);
				bool first = true;
				for(uint32 i = 0; i < info->maxfields; i++)
				{
					if(fieldinfo->fieldname[i])
					{
						if(first)
							first = false;
						else
							fprintf(output, ", ");
						fprintf(output, "`%s`", fieldinfo->fieldname[i]);
					}
				}
				first = true;
				fprintf(output, ")\nVALUES(");
				for(uint32 i = 0; i < ITEM_BUILD_MAX; i++)
				{
					if(fieldinfo->fieldname[i])
					{
						if(first)
							first = false;
						else
							fprintf(output, ", ");

						switch(fieldinfo->fieldtype[i])
						{
						case FIELDTYPE_INT:
							{
								if(i == ITEM_BUILD_INFO_ENTRY_ID)
								{
									if(m_itemValues[i] != NULL)
									{
										int value = (int)atol(m_itemValues[i]->val);
										if(value)
											fprintf(output, "'%i'", value);
										else
											fprintf(output, "'MUSTHAVEENTRYID'");
									}
									else
										fprintf(output, "'MUSTHAVEENTRYID'");
								}
								else
								{
									if(m_itemValues[i] != NULL)
									{
										int value = (int)atol(GetValueFromIndex(i, m_itemValues[i]->val));
										fprintf(output, "'%i'", value);
									}
									else
										fprintf(output, "'0'");
								}
							}break;
						case FIELDTYPE_FLOAT:
							{
								if(m_itemValues[i] != NULL)
								{
									float value = (float)atof(m_itemValues[i]->val);
									fprintf(output, "'%f'", value);
								}
								else
									fprintf(output, "'0.0'");
							}break;
						default:
							{
								fprintf(output, "'%s'", m_itemValues[i] != NULL ? m_itemValues[i]->val : "");
							}break;
						}
					}
				}
				fprintf(output, ");");
			}

			fclose(output);
		}break;
	}
}

char* GetValueFromIndex(uint32 from, char* indexvalue)
{
	if(from == ITEM_BUILD_INFO_QUALITY)
	{
		// Item Qualities
		if(strcmp(indexvalue, "Poor") == 0)
			return "0";
		if(strcmp(indexvalue, "Common") == 0)
			return "1";
		if(strcmp(indexvalue, "Uncommon") == 0)
			return "3";
		if(strcmp(indexvalue, "Rare") == 0)
			return "4";
		if(strcmp(indexvalue, "Epic") == 0)
			return "5";
		if(strcmp(indexvalue, "Legendary") == 0)
			return "6";
		if(strcmp(indexvalue, "Artifact") == 0)
			return "7";
		if(strcmp(indexvalue, "Heirloom") == 0)
			return "8";
		if(strcmp(indexvalue, "Mega Man") == 0)
			return "9";
	}

	if( from == ITEM_BUILD_INFO_INVENTORY_TYPE )
	{
		if(strcmp(indexvalue, "One Hand") == 0)
			return "13";
		if(strcmp(indexvalue, "Main Hand") == 0)
			return "21";
		if(strcmp(indexvalue, "Off Hand") == 0)
			return "22";
		if(strcmp(indexvalue, "Two Hand") == 0)
			return "17";
		if(strcmp(indexvalue, "Bow") == 0)
			return "15";
		if(strcmp(indexvalue, "Thrown") == 0)
			return "25";
		if(strcmp(indexvalue, "Crossbow") == 0)
			return "26";
		if(strcmp(indexvalue, "Gun/Wand") == 0)
			return "26";
	}

	if( from == ITEM_BUILD_INFO_SUB_CLASS )
	{
		// Weapon Subclass
		if(strcmp(indexvalue, "1H Axe") == 0)
			return "0";
		if(strcmp(indexvalue, "2H Axe") == 0)
			return "1";
		if(strcmp(indexvalue, "Bow") == 0)
			return "2";
		if(strcmp(indexvalue, "Gun") == 0)
			return "3";
		if(strcmp(indexvalue, "1H Mace") == 0)
			return "4";
		if(strcmp(indexvalue, "2H Mace") == 0)
			return "5";
		if(strcmp(indexvalue, "Polearm") == 0)
			return "6";
		if(strcmp(indexvalue, "1H Sword") == 0)
			return "7";
		if(strcmp(indexvalue, "2H Sword") == 0)
			return "8";
		if(strcmp(indexvalue, "Staff") == 0)
			return "10";
		if(strcmp(indexvalue, "Fist") == 0)
			return "13";
		if(strcmp(indexvalue, "Dagger") == 0)
			return "15";
		if(strcmp(indexvalue, "Throwing") == 0)
			return "16";
		if(strcmp(indexvalue, "Spear") == 0)
			return "17";
		if(strcmp(indexvalue, "Crossbow") == 0)
			return "18";
		if(strcmp(indexvalue, "Wand") == 0)
			return "19";
		if(strcmp(indexvalue, "Fishing Pole") == 0)
			return "20";

		// Armor Subclass
		if(strcmp(indexvalue, "Cloth") == 0)
			return "1";
		if(strcmp(indexvalue, "Leather") == 0)
			return "2";
		if(strcmp(indexvalue, "Mail") == 0)
			return "3";
		if(strcmp(indexvalue, "Plate") == 0)
			return "4";
		if(strcmp(indexvalue, "Buckler") == 0)
			return "5";
		if(strcmp(indexvalue, "Shield") == 0)
			return "6";
	}

	if( from == ITEM_BUILD_INFO_BINDTYPE )
	{
		if(strcmp(indexvalue, "None") == 0)
			return "0";
		if(strcmp(indexvalue, "On Pickup") == 0)
			return "1";
		if(strcmp(indexvalue, "On Equip") == 0)
			return "2";
		if(strcmp(indexvalue, "On Use") == 0)
			return "3";
	}

	if( from == ITEM_BUILD_INFO_SHEATH_TYPE )
	{
		if(strcmp(indexvalue, "One Handed") == 0)
			return "3";
		if(strcmp(indexvalue, "Two Handed") == 0)
			return "1";
		if(strcmp(indexvalue, "Staff") == 0)
			return "2";
		if(strcmp(indexvalue, "Ranged") == 0)
			return "0";
		if(strcmp(indexvalue, "Wand") == 0)
			return "0";
	}

	if( from == ITEM_BUILD_INFO_AMMO_TYPE )
	{
		if(strcmp(indexvalue, "No Ammo") == 0)
			return "0";
		if(strcmp(indexvalue, "Wands") == 0)
			return "0";
		if(strcmp(indexvalue, "Bows") == 0)
			return "2";
		if(strcmp(indexvalue, "Guns") == 0)
			return "3";
	}

	if( from >= ITEM_BUILD_INFO_STAT_TYPE_1 && from <= ITEM_BUILD_INFO_STAT_TYPE_10)
	{
		// Items Stats
		if(strcmp(indexvalue, "Mana") == 0)
			return "0";
		if(strcmp(indexvalue, "Health") == 0)
			return "1";
		if(strcmp(indexvalue, "Agility") == 0)
			return "3";
		if(strcmp(indexvalue, "Strength") == 0)
			return "4";
		if(strcmp(indexvalue, "Intellect") == 0)
			return "5";
		if(strcmp(indexvalue, "Spirit") == 0)
			return "6";
		if(strcmp(indexvalue, "Stamina") == 0)
			return "7";
		if(strcmp(indexvalue, "Weapon Skill") == 0)
			return "11";
		if(strcmp(indexvalue, "Defense Rating") == 0)
			return "12";
		if(strcmp(indexvalue, "Dodge Rating") == 0)
			return "13";
		if(strcmp(indexvalue, "Parry Rating") == 0)
			return "14";
		if(strcmp(indexvalue, "Shield Block Rating") == 0)
			return "15";
		if(strcmp(indexvalue, "Melee Hit Rating") == 0)
			return "16";
		if(strcmp(indexvalue, "Ranged Hit Rating") == 0)
			return "17";
		if(strcmp(indexvalue, "Spell Hit Rating") == 0)
			return "18";
		if(strcmp(indexvalue, "Melee Crit Rating") == 0)
			return "19";
		if(strcmp(indexvalue, "Ranged Crit Rating") == 0)
			return "20";
		if(strcmp(indexvalue, "Spell Crit Rating") == 0)
			return "21";
		if(strcmp(indexvalue, "Melee Dodge Rating") == 0)
			return "22";
		if(strcmp(indexvalue, "Ranged Dodge Rating") == 0)
			return "23";
		if(strcmp(indexvalue, "Spell Dodge Rating") == 0)
			return "24";
		if(strcmp(indexvalue, "Melee Resilience Rating") == 0)
			return "25";
		if(strcmp(indexvalue, "Ranged Resilience Rating") == 0)
			return "26";
		if(strcmp(indexvalue, "Spell Resilience Rating") == 0)
			return "27";
		if(strcmp(indexvalue, "Melee Haste Rating") == 0)
			return "28";
		if(strcmp(indexvalue, "Ranged Haste Rating") == 0)
			return "29";
		if(strcmp(indexvalue, "Spell Haste Rating") == 0)
			return "30";
		if(strcmp(indexvalue, "Hit Rating") == 0)
			return "31";
		if(strcmp(indexvalue, "Crit Rating") == 0)
			return "32";
		if(strcmp(indexvalue, "Dodge Rating") == 0)
			return "33";
		if(strcmp(indexvalue, "Crit Resilience Rating") == 0)
			return "34";
		if(strcmp(indexvalue, "Resilience Rating") == 0)
			return "35";
		if(strcmp(indexvalue, "Haste Rating") == 0)
			return "36";
		if(strcmp(indexvalue, "Expertise Rating") == 0)
			return "37";
		if(strcmp(indexvalue, "Attack Power") == 0)
			return "38";
		if(strcmp(indexvalue, "Ranged Attack Power") == 0)
			return "39";
		if(strcmp(indexvalue, "Feral Attack Power") == 0)
			return "40";
		if(strcmp(indexvalue, "Spell Healing Done") == 0)
			return "41";
		if(strcmp(indexvalue, "Spell Damage Done") == 0)
			return "42";
		if(strcmp(indexvalue, "MP5 Rating") == 0)
			return "43";
		if(strcmp(indexvalue, "Armor Pen Rating") == 0)
			return "44";
		if(strcmp(indexvalue, "Spell Power") == 0)
			return "45";
		if(strcmp(indexvalue, "HP5 Rating") == 0)
			return "46";
		if(strcmp(indexvalue, "Spell Pen Rating") == 0)
			return "47";
		if(strcmp(indexvalue, "Block Value") == 0)
			return "48";
	}

	if( from >= ITEM_BUILD_INFO_SOCKET_TYPE_1 && from <= ITEM_BUILD_INFO_SOCKET_TYPE_3 )
	{
		// Gem Types
		if(strcmp(indexvalue, "None") == 0)
			return "0";
		if(strcmp(indexvalue, "Meta") == 0)
			return "1";
		if(strcmp(indexvalue, "Red") == 0)
			return "2";
		if(strcmp(indexvalue, "Yellow") == 0)
			return "4";
		if(strcmp(indexvalue, "Blue") == 0)
			return "8";
	}

	return indexvalue;
}
