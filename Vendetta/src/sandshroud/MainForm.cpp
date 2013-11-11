
#include "StdAfx.h"
#include "MainForm.h"

using namespace sandshroud;

extern BuildInfoMap ItemInfoLibs;
extern BuildInfoMap CreatureInfoLibs;
extern BuildInfoMap VendorInfoLibs;
extern BuildInfoMap LootInfoLibs;

extern TableInfoStruct* m_itemValues[ITEM_BUILD_MAX];

#define ITEM_INDEX_LIST_FIRST L"Item Details"

#define ITEM_INDEX_1_COUNT 12
#define ITEM_INDEX_1_LIST , L"Item Type", L"Item Weapon Stats", L"Item Armor Stats", L"Item Requirements", L"Item Damage", L"Item Stats", L"Item Resists", L"Item Bonuses", L"Item Sockets", L"Item Set", L"Item Value"

#define ITEM_INDEX_2_COUNT 10
#define ITEM_INDEX_2_LIST , L"Item Type", L"Item Armor Stats", L"Item Requirements", L"Item Stats", L"Item Resists", L"Item Bonuses", L"Item Sockets", L"Item Set", L"Item Value"

#define NPC_INDEX_COUNT 9
#define NPC_INDEX_LIST_FIRST L"Mob/Npc Details"
#define NPC_INDEX_LIST , L"Mob/Npc Type", L"Mob/Npc Behavior", L"Mob/Npc Stats", L"Mob/Npc Attack Stats", L"Mob/Npc Resists", L"Mob/Npc Options", L"Mob/Npc Gold Drop", L"Mob/Npc Advanced Options"

#define SUPPORTED_STAT_TYPE_NUM 43
#define SUPPORTED_STAT_TYPE_FIRST "Health"
#define SUPPORTED_STAT_TYPES , L"Agility", L"Strength", L"Intellect", L"Spirit", L"Stamina", L"Defense", L"Dodge", L"Parry", L"Block", L"Expertise", L"Resilience", L"Healing Bonus", L"Damage Bonus", L"Mana Per 5 Sec", L"Block Value", L"Health Regeneration", L"Spell Penetration", L"Armor Penetration", L"Attack Power", L"Hit Rating", L"Hit Avoidance", L"Hit Crit Rating", L"Hit Crit Avoidance", L"Hit Haste Rating", L"Melee Hit Rating", L"Melee Crit Rating", L"Melee Hit Avoidance", L"Melee Crit Avoidance", L"Melee Haste Rating", L"Ranged Attack Power", L"Ranged Hit Rating", L"Ranged Crit Rating", L"Ranged Hit Avoidance", L"Ranged Crit Avoidance", L"Ranged Haste Rating", L"Spell Hit Rating", L"Spell Crit Rating", L"Spell Hit Avoidance", L"Spell Crit Avoidance", L"Spell Haste Rating", L"Spell Power", L"Feral Attack Power"

#define GEM_INDEX_COUNT 5
#define GEM_INDEX_LIST_FIRST "None"
#define GEM_INDEX_LIST , L"Meta", L"Red", L"Yellow", L"Blue"

void ResetInputVariables(Master^ master);
void SaveCurrentVariables(Master^ master);

System::Void MainForm::SaveButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	SaveCurrentVariables(masterClass);
	masterClass->SaveValues();
}

char* SelectedCore = "";
bool SystemSet = false;

System::Void MainForm::CoreSelectionBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(!SystemSet)
		SystemSet = true;
	else
		Marshal::FreeHGlobal((System::IntPtr)(void*)SelectedCore);

	ComboBox^ comboBox = (ComboBox^)(sender);
	SelectedCore = (char*)(void*)Marshal::StringToHGlobalAnsi(comboBox->Text);

	SystemPrintfDebug("Setting core to %s", SelectedCore);
}

uint32 ExtraCallType = 0;
uint32 ItemSelectionCallType = 0;

int FieldValue[20];
int IndexFieldValues[10];
int DescriptionFieldValue[2];

bool ItemSystemSet1 = false, ItemSystemSet2 = false;

#define SET_FIELD_VALUE(field, value) FieldValue[field-1] = value
#define SET_INDEX_FIELD_VALUE(field, value) IndexFieldValues[field-1] = value
#define SET_DESCRIPTION_FIELD_VALUE(field, value) DescriptionFieldValue[field-1] = value

#define SET_TEXT(box, text) master->window->box->Text = text
#define CLEAR_RANGE(box) master->window->box->Items->Clear()
#define ADD_RANGE(box) master->window->box->Items->AddRange
#define UPDATE(box) master->window->box->Update()

#ifdef _DEBUG
#define VISIBILITY(box, visible) master->window->box->Visible = true
#else
#define VISIBILITY(box, visible) master->window->box->Visible = visible
#endif

#define ORIGINAL_SIZE_1 69
#define ORIGINAL_SIZE_2 20

#define SET_SIZE(box, size1, size2) master->window->box->Size = System::Drawing::Size(size1, size2)
#define SET_POSITION(box, point1, point2) master->window->box->Location = System::Drawing::Point(point1, point2);

void UpdateBasedOnInputSettings(Master^ master)
{	// 150, 20
	SaveCurrentVariables(master);
	ResetInputVariables(master);

	switch(ItemSelectionCallType)
	{
	case 1:
		{
			switch(ExtraCallType)
			{
			case 1:
				{
					m_itemValues[ITEM_BUILD_INFO_CLASS] = new TableInfoStruct("2");
					if(master->window->ItemSettingsIndex->Text == "Item Details")
					{
						SET_INDEX_FIELD_VALUE(1, ITEM_BUILD_INFO_QUALITY);
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("Quality:"));
						VISIBILITY(SelectionIndexBox1, true);
						ADD_RANGE(SelectionIndexBox1)(gcnew cli::array< System::Object^ >(9) { L"Poor", L"Common", L"Uncommon", L"Rare", L"Epic", L"Legendary", L"Artifact", L"Heirloom", L"Mega Man" });
						UPDATE(SelectionIndexBox1);
						if(m_itemValues[ITEM_BUILD_INFO_QUALITY] == NULL)
							m_itemValues[ITEM_BUILD_INFO_QUALITY] = new TableInfoStruct("Poor");
						SET_TEXT(SelectionIndexBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_QUALITY]->val));

						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_NAME);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Name:"));
						SET_SIZE(SelectionInputBox1, 140, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_NAME] != NULL && strcmp(m_itemValues[ITEM_BUILD_INFO_NAME]->val, "UNKNOWN") != 0)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_NAME]->val));
						else m_itemValues[ITEM_BUILD_INFO_NAME] = new TableInfoStruct("UNKNOWN");

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_DISPLAY_ID);
						VISIBILITY(InputBox2Title, true);
						SET_TEXT(InputBox2Title, gcnew String("Display Id:"));
						SET_SIZE(SelectionInputBox2, 120, 18);
						SET_POSITION(SelectionInputBox2, 62, 78);
						VISIBILITY(SelectionInputBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_DISPLAY_ID] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_DISPLAY_ID]->val));
						else m_itemValues[ITEM_BUILD_INFO_DISPLAY_ID] = new TableInfoStruct("");

						SET_FIELD_VALUE(12, ITEM_BUILD_INFO_ENTRY_ID);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Entry Id:"));
						SET_SIZE(SelectionInputBox12, 140, 18);
						SET_POSITION(SelectionInputBox12, 187, 78);
						VISIBILITY(SelectionInputBox12, true);
						if(m_itemValues[ITEM_BUILD_INFO_ENTRY_ID] != NULL && strcmp(m_itemValues[ITEM_BUILD_INFO_ENTRY_ID]->val, "MUSTHAVEENTRYID") != 0)
							SET_TEXT(SelectionInputBox12, gcnew String(m_itemValues[ITEM_BUILD_INFO_ENTRY_ID]->val));
						else m_itemValues[ITEM_BUILD_INFO_ENTRY_ID] = new TableInfoStruct("MUSTHAVEENTRYID");

						SET_DESCRIPTION_FIELD_VALUE(2, ITEM_BUILD_INFO_QUOTE);
						VISIBILITY(InputBox22Title, true);
						SET_TEXT(InputBox22Title, gcnew String("Quote:"));
						VISIBILITY(DescriptionBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_QUOTE] != NULL)
							SET_TEXT(DescriptionBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_QUOTE]->val));
						else m_itemValues[ITEM_BUILD_INFO_QUOTE] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Type")
					{
						SET_INDEX_FIELD_VALUE(1, ITEM_BUILD_INFO_INVENTORY_TYPE);
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("Inv Type"));
						VISIBILITY(SelectionIndexBox1, true);
						ADD_RANGE(SelectionIndexBox1)(gcnew cli::array< System::Object^ >(8) { L"One Hand", L"Main Hand", L"Off Hand", L"Two Hand", L"Bow", L"Thrown", L"Crossbow", L"Gun/Wand" });
						UPDATE(SelectionIndexBox1);
						if(m_itemValues[ITEM_BUILD_INFO_INVENTORY_TYPE] == NULL)
							m_itemValues[ITEM_BUILD_INFO_INVENTORY_TYPE] = new TableInfoStruct("One Hand");
						SET_TEXT(SelectionIndexBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_INVENTORY_TYPE]->val));

						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_DURABILITY);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Durability"));
						SET_SIZE(SelectionInputBox1, 140, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_DURABILITY] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_DURABILITY]->val));
						else m_itemValues[ITEM_BUILD_INFO_DURABILITY] = new TableInfoStruct("");

						SET_INDEX_FIELD_VALUE(2, ITEM_BUILD_INFO_SUB_CLASS);
						VISIBILITY(InputBox2Title, true);
						SET_TEXT(InputBox2Title, gcnew String("Weap Type"));
						VISIBILITY(SelectionIndexBox2, true);
						ADD_RANGE(SelectionIndexBox2)(gcnew cli::array< System::Object^ >(16) { L"1H Axe", L"2H Axe", L"Bow", L"Gun", L"1H Mace", L"2H Mace", L"Polearm", L"1H Sword", L"2H Sword", L"Staff", L"Fist", L"Dagger", L"Throwing", L"Spear", L"Crossbow", L"Wand" });
						UPDATE(SelectionIndexBox2);
						if(m_itemValues[ITEM_BUILD_INFO_SUB_CLASS] == NULL)
							m_itemValues[ITEM_BUILD_INFO_SUB_CLASS] = new TableInfoStruct("1H Axe");
						SET_TEXT(SelectionIndexBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_SUB_CLASS]->val));

						SET_INDEX_FIELD_VALUE(3, ITEM_BUILD_INFO_REPAIR_TYPE);
						VISIBILITY(InputBox3Title, true);
						SET_TEXT(InputBox3Title, gcnew String("Repair"));
						VISIBILITY(SelectionIndexBox3, true);
						ADD_RANGE(SelectionIndexBox3)(gcnew cli::array< System::Object^ >(2) { L"Weapon/Shield", L"Unrepairable" });
						UPDATE(SelectionIndexBox3);
						if(m_itemValues[ITEM_BUILD_INFO_REPAIR_TYPE] == NULL)
							m_itemValues[ITEM_BUILD_INFO_REPAIR_TYPE] = new TableInfoStruct("Weapon/Shield");
						SET_TEXT(SelectionIndexBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_REPAIR_TYPE]->val));

						SET_INDEX_FIELD_VALUE(4, ITEM_BUILD_INFO_BINDTYPE);
						VISIBILITY(InputBox4Title, true);
						SET_TEXT(InputBox4Title, gcnew String("Bind Type"));
						VISIBILITY(SelectionIndexBox4, true);
						ADD_RANGE(SelectionIndexBox4)(gcnew cli::array< System::Object^ >(4) { L"None", L"On Pickup", L"On Equip", L"On Use" });
						UPDATE(SelectionIndexBox4);
						if(m_itemValues[ITEM_BUILD_INFO_BINDTYPE] == NULL)
							m_itemValues[ITEM_BUILD_INFO_BINDTYPE] = new TableInfoStruct("None");
						SET_TEXT(SelectionIndexBox4, gcnew String(m_itemValues[ITEM_BUILD_INFO_BINDTYPE]->val));
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Weapon Stats")
					{
						SET_INDEX_FIELD_VALUE(1, ITEM_BUILD_INFO_SHEATH_TYPE);
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("Sheath"));
						VISIBILITY(SelectionIndexBox1, true);
						ADD_RANGE(SelectionIndexBox1)(gcnew cli::array< System::Object^ >(5) { L"One Handed", L"Two Handed", L"Staff", L"Ranged", L"Wand" });
						UPDATE(SelectionIndexBox1);
						if(m_itemValues[ITEM_BUILD_INFO_SHEATH_TYPE] == NULL)
							m_itemValues[ITEM_BUILD_INFO_SHEATH_TYPE] = new TableInfoStruct("One Handed");
						SET_TEXT(SelectionIndexBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_SHEATH_TYPE]->val));

						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_SPEED);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Speed"));
						SET_SIZE(SelectionInputBox1, 140, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_SPEED] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_SPEED]->val));
						else m_itemValues[ITEM_BUILD_INFO_SPEED] = new TableInfoStruct("");

						SET_INDEX_FIELD_VALUE(2, ITEM_BUILD_INFO_AMMO_TYPE);
						VISIBILITY(InputBox2Title, true);
						SET_TEXT(InputBox2Title, gcnew String("Ammo Type"));
						VISIBILITY(SelectionIndexBox2, true);
						ADD_RANGE(SelectionIndexBox2)(gcnew cli::array< System::Object^ >(4) { L"No Ammo", L"Wands", L"Bows", L"Guns" });
						UPDATE(SelectionIndexBox2);
						if(m_itemValues[ITEM_BUILD_INFO_AMMO_TYPE] == NULL)
							m_itemValues[ITEM_BUILD_INFO_AMMO_TYPE] = new TableInfoStruct("No Ammo");
						SET_TEXT(SelectionIndexBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_AMMO_TYPE]->val));
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Armor Stats")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_BLOCK);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Block"));
						SET_SIZE(SelectionInputBox1, 140, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_BLOCK] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_BLOCK]->val));
						else m_itemValues[ITEM_BUILD_INFO_BLOCK] = new TableInfoStruct("");

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_ARMOR);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Armor"));
						SET_SIZE(SelectionInputBox2, 140, 18);
						VISIBILITY(SelectionInputBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_ARMOR] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_ARMOR]->val));
						else m_itemValues[ITEM_BUILD_INFO_ARMOR] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Requirements")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_REQUIRED_LEVEL);
						SET_FIELD_VALUE(11, ITEM_BUILD_INFO_ITEM_LEVEL);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("(Req Plr)/(Item Level)"));
						SET_POSITION(InputBox11Title, 175, 16);
						VISIBILITY(SelectionInputBox1, true);
						VISIBILITY(SelectionInputBox11, true);
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_LEVEL] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_LEVEL]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_LEVEL] = new TableInfoStruct("");
						if(m_itemValues[ITEM_BUILD_INFO_ITEM_LEVEL] != NULL)
							SET_TEXT(SelectionInputBox11, gcnew String(m_itemValues[ITEM_BUILD_INFO_ITEM_LEVEL]->val));
						else m_itemValues[ITEM_BUILD_INFO_ITEM_LEVEL] = new TableInfoStruct("");

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_REQUIRED_FACTION);
						SET_FIELD_VALUE(12, ITEM_BUILD_INFO_REQUIRED_FACTION_LEVEL);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Req (Rep Id)/(Standing)"));
						SET_POSITION(InputBox12Title, 175, 58);
						VISIBILITY(SelectionInputBox2, true);
						VISIBILITY(SelectionInputBox12, true);
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION] = new TableInfoStruct("");
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION_LEVEL] != NULL)
							SET_TEXT(SelectionInputBox12, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION_LEVEL]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION_LEVEL] = new TableInfoStruct("");

						SET_FIELD_VALUE(3, ITEM_BUILD_INFO_REQUIRED_SKILL);
						SET_FIELD_VALUE(13, ITEM_BUILD_INFO_REQUIRED_SKILL_LEVEL);
						VISIBILITY(InputBox13Title, true);
						SET_TEXT(InputBox13Title, gcnew String("Req (Skill Id)/(Level)"));
						SET_POSITION(InputBox13Title, 175, 99);
						VISIBILITY(SelectionInputBox3, true);
						VISIBILITY(SelectionInputBox13, true);
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL] != NULL)
							SET_TEXT(SelectionInputBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL] = new TableInfoStruct("");
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL_LEVEL] != NULL)
							SET_TEXT(SelectionInputBox13, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL_LEVEL]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL_LEVEL] = new TableInfoStruct("");

						SET_FIELD_VALUE(4, ITEM_BUILD_INFO_REQUIRED_SPELL);
						VISIBILITY(InputBox14Title, true);
						SET_TEXT(InputBox14Title, gcnew String("Required Spell"));
						SET_POSITION(InputBox14Title, 205, 141);
						SET_SIZE(SelectionInputBox4, 140, 18);
						VISIBILITY(SelectionInputBox4, true);
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SPELL] != NULL)
							SET_TEXT(SelectionInputBox4, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SPELL]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_SPELL] = new TableInfoStruct("");

						SET_FIELD_VALUE(5, ITEM_BUILD_INFO_UNIQUE);
						SET_FIELD_VALUE(15, ITEM_BUILD_INFO_MAX_STACK);
						VISIBILITY(InputBox15Title, true);
						SET_TEXT(InputBox15Title, gcnew String("(Unique Num)/(Stack Size)"));
						SET_POSITION(InputBox15Title, 175, 183);
						VISIBILITY(SelectionInputBox5, true);
						VISIBILITY(SelectionInputBox15, true);
						if(m_itemValues[ITEM_BUILD_INFO_UNIQUE] != NULL)
							SET_TEXT(SelectionInputBox5, gcnew String(m_itemValues[ITEM_BUILD_INFO_UNIQUE]->val));
						else m_itemValues[ITEM_BUILD_INFO_UNIQUE] = new TableInfoStruct("");
						if(m_itemValues[ITEM_BUILD_INFO_MAX_STACK] != NULL)
							SET_TEXT(SelectionInputBox15, gcnew String(m_itemValues[ITEM_BUILD_INFO_MAX_STACK]->val));
						else m_itemValues[ITEM_BUILD_INFO_MAX_STACK] = new TableInfoStruct("");

						SET_FIELD_VALUE(6, ITEM_BUILD_INFO_ALLOWABLE_CLASS);
						SET_FIELD_VALUE(16, ITEM_BUILD_INFO_ALLOWABLE_RACE);
						VISIBILITY(InputBox16Title, true);
						SET_TEXT(InputBox16Title, gcnew String("Req (Class)/(Race) Mask"));
						SET_POSITION(InputBox16Title, 175, 221);
						VISIBILITY(SelectionInputBox6, true);
						VISIBILITY(SelectionInputBox16, true);
						if(m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_CLASS] != NULL)
							SET_TEXT(SelectionInputBox6, gcnew String(m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_CLASS]->val));
						else m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_CLASS] = new TableInfoStruct("");
						if(m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_RACE] != NULL)
							SET_TEXT(SelectionInputBox16, gcnew String(m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_RACE]->val));
						else m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_RACE] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Damage")
					{
						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(1, ITEM_BUILD_INFO_DAMAGE_TYPE_1);
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("Damage Type 1"));
						VISIBILITY(SelectionIndexBox1, true);
						ADD_RANGE(SelectionIndexBox1)(gcnew cli::array< System::Object^ >(7) { L"Physical", L"Holy", L"Fire", L"Nature", L"Frost", L"Shadow", L"Arcane" });
						UPDATE(SelectionIndexBox1);
						if(m_itemValues[ITEM_BUILD_INFO_DAMAGE_TYPE_1] == NULL)
							m_itemValues[ITEM_BUILD_INFO_DAMAGE_TYPE_1] = new TableInfoStruct("Physical");
						SET_TEXT(SelectionIndexBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_DAMAGE_TYPE_1]->val));

						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_DAMAGE_MIN_1);
						SET_FIELD_VALUE(11, ITEM_BUILD_INFO_DAMAGE_MAX_1);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Damage Min/Max"));
						VISIBILITY(SelectionInputBox1, true);
						VISIBILITY(SelectionInputBox11, true);

						if(m_itemValues[ITEM_BUILD_INFO_DAMAGE_MIN_1] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_DAMAGE_MIN_1]->val));
						else m_itemValues[ITEM_BUILD_INFO_DAMAGE_MIN_1] = new TableInfoStruct("");

						if(m_itemValues[ITEM_BUILD_INFO_DAMAGE_MAX_1] != NULL)
							SET_TEXT(SelectionInputBox11, gcnew String(m_itemValues[ITEM_BUILD_INFO_DAMAGE_MAX_1]->val));
						else m_itemValues[ITEM_BUILD_INFO_DAMAGE_MAX_1] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(2, ITEM_BUILD_INFO_DAMAGE_TYPE_2);
						VISIBILITY(InputBox2Title, true);
						SET_TEXT(InputBox2Title, gcnew String("Damage Type 1"));
						VISIBILITY(SelectionIndexBox2, true);
						ADD_RANGE(SelectionIndexBox2)(gcnew cli::array< System::Object^ >(7) { L"Physical", L"Holy", L"Fire", L"Nature", L"Frost", L"Shadow", L"Arcane" });
						UPDATE(SelectionIndexBox2);
						if(m_itemValues[ITEM_BUILD_INFO_DAMAGE_TYPE_2] == NULL)
							m_itemValues[ITEM_BUILD_INFO_DAMAGE_TYPE_2] = new TableInfoStruct("Physical");
						SET_TEXT(SelectionIndexBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_DAMAGE_TYPE_2]->val));

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_DAMAGE_MIN_2);
						SET_FIELD_VALUE(12, ITEM_BUILD_INFO_DAMAGE_MAX_2);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Damage Min/Max"));
						VISIBILITY(SelectionInputBox2, true);
						VISIBILITY(SelectionInputBox12, true);

						if(m_itemValues[ITEM_BUILD_INFO_DAMAGE_MIN_2] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_DAMAGE_MIN_2]->val));
						else m_itemValues[ITEM_BUILD_INFO_DAMAGE_MIN_2] = new TableInfoStruct("");

						if(m_itemValues[ITEM_BUILD_INFO_DAMAGE_MAX_2] != NULL)
							SET_TEXT(SelectionInputBox12, gcnew String(m_itemValues[ITEM_BUILD_INFO_DAMAGE_MAX_2]->val));
						else m_itemValues[ITEM_BUILD_INFO_DAMAGE_MAX_2] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Stats")
					{
						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(1, ITEM_BUILD_INFO_STAT_TYPE_1);
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("Stat Type 1"));
						VISIBILITY(SelectionIndexBox1, true);
						ADD_RANGE(SelectionIndexBox1)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox1);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_1] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_1] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_1]->val));

						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_STAT_VALUE_1);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Stat Value 1"));
						SET_SIZE(SelectionInputBox1, 140, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_1] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_1]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_1] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(2, ITEM_BUILD_INFO_STAT_TYPE_2);
						VISIBILITY(InputBox2Title, true);
						SET_TEXT(InputBox2Title, gcnew String("Stat Type 2"));
						VISIBILITY(SelectionIndexBox2, true);
						ADD_RANGE(SelectionIndexBox2)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox2);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_2] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_2] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_2]->val));

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_STAT_VALUE_2);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Stat Value 2"));
						SET_SIZE(SelectionInputBox2, 140, 18);
						VISIBILITY(SelectionInputBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_2] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_2]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_2] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(3, ITEM_BUILD_INFO_STAT_TYPE_3);
						VISIBILITY(InputBox3Title, true);
						SET_TEXT(InputBox3Title, gcnew String("Stat Type 3"));
						VISIBILITY(SelectionIndexBox3, true);
						ADD_RANGE(SelectionIndexBox3)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox3);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_3] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_3] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_3]->val));

						SET_FIELD_VALUE(3, ITEM_BUILD_INFO_STAT_VALUE_3);
						VISIBILITY(InputBox13Title, true);
						SET_TEXT(InputBox13Title, gcnew String("Stat Value 3"));
						SET_SIZE(SelectionInputBox3, 140, 18);
						VISIBILITY(SelectionInputBox3, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_3] != NULL)
							SET_TEXT(SelectionInputBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_3]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_3] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(4, ITEM_BUILD_INFO_STAT_TYPE_4);
						VISIBILITY(InputBox4Title, true);
						SET_TEXT(InputBox4Title, gcnew String("Stat Type 4"));
						VISIBILITY(SelectionIndexBox4, true);
						ADD_RANGE(SelectionIndexBox4)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox4);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_4] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_4] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox4, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_4]->val));

						SET_FIELD_VALUE(4, ITEM_BUILD_INFO_STAT_VALUE_4);
						VISIBILITY(InputBox14Title, true);
						SET_TEXT(InputBox14Title, gcnew String("Stat Value 4"));
						SET_SIZE(SelectionInputBox4, 140, 18);
						VISIBILITY(SelectionInputBox4, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_4] != NULL)
							SET_TEXT(SelectionInputBox4, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_4]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_4] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(5, ITEM_BUILD_INFO_STAT_TYPE_5);
						VISIBILITY(InputBox5Title, true);
						SET_TEXT(InputBox5Title, gcnew String("Stat Type 5"));
						VISIBILITY(SelectionIndexBox5, true);
						ADD_RANGE(SelectionIndexBox5)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox5);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_5] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_5] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox5, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_5]->val));

						SET_FIELD_VALUE(5, ITEM_BUILD_INFO_STAT_VALUE_5);
						VISIBILITY(InputBox15Title, true);
						SET_TEXT(InputBox15Title, gcnew String("Stat Value 5"));
						SET_SIZE(SelectionInputBox5, 140, 18);
						VISIBILITY(SelectionInputBox5, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_5] != NULL)
							SET_TEXT(SelectionInputBox5, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_5]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_5] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(6, ITEM_BUILD_INFO_STAT_TYPE_6);
						VISIBILITY(InputBox6Title, true);
						SET_TEXT(InputBox6Title, gcnew String("Stat Type 6"));
						VISIBILITY(SelectionIndexBox6, true);
						ADD_RANGE(SelectionIndexBox6)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox6);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_6] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_6] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox6, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_6]->val));

						SET_FIELD_VALUE(6, ITEM_BUILD_INFO_STAT_VALUE_6);
						VISIBILITY(InputBox16Title, true);
						SET_TEXT(InputBox16Title, gcnew String("Stat Value 6"));
						SET_SIZE(SelectionInputBox6, 140, 18);
						VISIBILITY(SelectionInputBox6, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_6] != NULL)
							SET_TEXT(SelectionInputBox6, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_6]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_6] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(7, ITEM_BUILD_INFO_STAT_TYPE_7);
						VISIBILITY(InputBox7Title, true);
						SET_TEXT(InputBox7Title, gcnew String("Stat Type 7"));
						VISIBILITY(SelectionIndexBox7, true);
						ADD_RANGE(SelectionIndexBox7)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox7);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_7] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_7] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox7, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_7]->val));

						SET_FIELD_VALUE(7, ITEM_BUILD_INFO_STAT_VALUE_7);
						VISIBILITY(InputBox17Title, true);
						SET_TEXT(InputBox17Title, gcnew String("Stat Value 7"));
						SET_SIZE(SelectionInputBox7, 140, 18);
						VISIBILITY(SelectionInputBox7, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_7] != NULL)
							SET_TEXT(SelectionInputBox7, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_7]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_7] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(8, ITEM_BUILD_INFO_STAT_TYPE_8);
						VISIBILITY(InputBox8Title, true);
						SET_TEXT(InputBox8Title, gcnew String("Stat Type 8"));
						VISIBILITY(SelectionIndexBox8, true);
						ADD_RANGE(SelectionIndexBox8)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox8);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_8] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_8] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox8, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_8]->val));

						SET_FIELD_VALUE(8, ITEM_BUILD_INFO_STAT_VALUE_8);
						VISIBILITY(InputBox18Title, true);
						SET_TEXT(InputBox18Title, gcnew String("Stat Value 8"));
						SET_SIZE(SelectionInputBox8, 140, 18);
						VISIBILITY(SelectionInputBox8, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_8] != NULL)
							SET_TEXT(SelectionInputBox8, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_8]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_8] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(9, ITEM_BUILD_INFO_STAT_TYPE_9);
						VISIBILITY(InputBox9Title, true);
						SET_TEXT(InputBox9Title, gcnew String("Stat Type 9"));
						VISIBILITY(SelectionIndexBox9, true);
						ADD_RANGE(SelectionIndexBox9)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox9);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_9] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_9] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox9, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_9]->val));

						SET_FIELD_VALUE(9, ITEM_BUILD_INFO_STAT_VALUE_9);
						VISIBILITY(InputBox19Title, true);
						SET_TEXT(InputBox19Title, gcnew String("Stat Value 9"));
						SET_SIZE(SelectionInputBox9, 140, 18);
						VISIBILITY(SelectionInputBox9, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_9] != NULL)
							SET_TEXT(SelectionInputBox9, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_9]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_9] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(10, ITEM_BUILD_INFO_STAT_TYPE_10);
						VISIBILITY(InputBox10Title, true);
						SET_TEXT(InputBox10Title, gcnew String("Stat Type 10"));
						VISIBILITY(SelectionIndexBox10, true);
						ADD_RANGE(SelectionIndexBox10)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox10);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_10] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_10] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox10, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_10]->val));

						SET_FIELD_VALUE(10, ITEM_BUILD_INFO_STAT_VALUE_10);
						VISIBILITY(InputBox20Title, true);
						SET_TEXT(InputBox20Title, gcnew String("Stat Value 10"));
						SET_SIZE(SelectionInputBox10, 140, 18);
						VISIBILITY(SelectionInputBox10, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_10] != NULL)
							SET_TEXT(SelectionInputBox10, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_10]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_10] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Resists")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_HOLY_RESISTANCE);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Holy Resistance"));
						SET_SIZE(SelectionInputBox1, 180, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_HOLY_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_HOLY_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_HOLY_RESISTANCE] = new TableInfoStruct("");

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_FIRE_RESISTANCE);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Fire Resistance"));
						SET_SIZE(SelectionInputBox2, 180, 18);
						VISIBILITY(SelectionInputBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_FIRE_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_FIRE_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_FIRE_RESISTANCE] = new TableInfoStruct("");

						SET_FIELD_VALUE(3, ITEM_BUILD_INFO_NATURE_RESISTANCE);
						VISIBILITY(InputBox13Title, true);
						SET_TEXT(InputBox13Title, gcnew String("Nature Resistance"));
						SET_SIZE(SelectionInputBox3, 180, 18);
						VISIBILITY(SelectionInputBox3, true);
						if(m_itemValues[ITEM_BUILD_INFO_NATURE_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_NATURE_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_NATURE_RESISTANCE] = new TableInfoStruct("");

						SET_FIELD_VALUE(4, ITEM_BUILD_INFO_FROST_RESISTANCE);
						VISIBILITY(InputBox14Title, true);
						SET_TEXT(InputBox14Title, gcnew String("Frost Resistance"));
						SET_SIZE(SelectionInputBox4, 180, 18);
						VISIBILITY(SelectionInputBox4, true);
						if(m_itemValues[ITEM_BUILD_INFO_FROST_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox4, gcnew String(m_itemValues[ITEM_BUILD_INFO_FROST_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_FROST_RESISTANCE] = new TableInfoStruct("");

						SET_FIELD_VALUE(5, ITEM_BUILD_INFO_SHADOW_RESISTANCE);
						VISIBILITY(InputBox15Title, true);
						SET_TEXT(InputBox15Title, gcnew String("Shadow Resistance"));
						SET_SIZE(SelectionInputBox5, 180, 18);
						VISIBILITY(SelectionInputBox5, true);
						if(m_itemValues[ITEM_BUILD_INFO_SHADOW_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox5, gcnew String(m_itemValues[ITEM_BUILD_INFO_SHADOW_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_SHADOW_RESISTANCE] = new TableInfoStruct("");

						SET_FIELD_VALUE(6, ITEM_BUILD_INFO_ARCANE_RESISTANCE);
						VISIBILITY(InputBox16Title, true);
						SET_TEXT(InputBox16Title, gcnew String("Arcane Resistance"));
						SET_SIZE(SelectionInputBox6, 180, 18);
						VISIBILITY(SelectionInputBox6, true);
						if(m_itemValues[ITEM_BUILD_INFO_ARCANE_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox6, gcnew String(m_itemValues[ITEM_BUILD_INFO_ARCANE_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_ARCANE_RESISTANCE] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Bonuses")
					{
						// TODO!
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("TODO"));
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Sockets")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_SOCKET_BONUS);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Socket Bonus"));
						SET_SIZE(SelectionInputBox1, 140, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_SOCKET_BONUS] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_SOCKET_BONUS]->val));
						else m_itemValues[ITEM_BUILD_INFO_SOCKET_BONUS] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(1, ITEM_BUILD_INFO_SOCKET_TYPE_1);
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("Gem Type 1"));
						VISIBILITY(SelectionIndexBox1, true);
						ADD_RANGE(SelectionIndexBox1)(gcnew cli::array< System::Object^ >(GEM_INDEX_COUNT) { GEM_INDEX_LIST_FIRST GEM_INDEX_LIST });
						UPDATE(SelectionIndexBox1);
						if(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_1] == NULL)
							m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_1] = new TableInfoStruct(GEM_INDEX_LIST_FIRST);
						SET_TEXT(SelectionIndexBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_1]->val));

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(2, ITEM_BUILD_INFO_SOCKET_TYPE_2);
						VISIBILITY(InputBox2Title, true);
						SET_TEXT(InputBox2Title, gcnew String("Gem Type 2"));
						VISIBILITY(SelectionIndexBox2, true);
						ADD_RANGE(SelectionIndexBox2)(gcnew cli::array< System::Object^ >(GEM_INDEX_COUNT) { GEM_INDEX_LIST_FIRST GEM_INDEX_LIST });
						UPDATE(SelectionIndexBox2);
						if(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_2] == NULL)
							m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_2] = new TableInfoStruct(GEM_INDEX_LIST_FIRST);
						SET_TEXT(SelectionIndexBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_2]->val));

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(3, ITEM_BUILD_INFO_SOCKET_TYPE_3);
						VISIBILITY(InputBox3Title, true);
						SET_TEXT(InputBox3Title, gcnew String("Gem Type 3"));
						VISIBILITY(SelectionIndexBox3, true);
						ADD_RANGE(SelectionIndexBox3)(gcnew cli::array< System::Object^ >(GEM_INDEX_COUNT) { GEM_INDEX_LIST_FIRST GEM_INDEX_LIST });
						UPDATE(SelectionIndexBox3);
						if(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_3] == NULL)
							m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_3] = new TableInfoStruct(GEM_INDEX_LIST_FIRST);
						SET_TEXT(SelectionIndexBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_3]->val));
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Set")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_SET_ID);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Set Id"));
						SET_SIZE(SelectionInputBox1, 140, 20);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_SET_ID] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_SET_ID]->val));
						else m_itemValues[ITEM_BUILD_INFO_SET_ID] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Value")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_BUY_PRICE);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Buy Price"));
						SET_SIZE(SelectionInputBox1, 140, 20);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_BUY_PRICE] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_BUY_PRICE]->val));
						else m_itemValues[ITEM_BUILD_INFO_BUY_PRICE] = new TableInfoStruct("");

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_SELL_PRICE);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Sell Price"));
						SET_SIZE(SelectionInputBox2, 140, 20);
						VISIBILITY(SelectionInputBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_SELL_PRICE] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_SELL_PRICE]->val));
						else m_itemValues[ITEM_BUILD_INFO_SELL_PRICE] = new TableInfoStruct("");
					}
				}break;
			case 2:
				{
					m_itemValues[ITEM_BUILD_INFO_CLASS] = new TableInfoStruct("4");
					if(master->window->ItemSettingsIndex->Text == "Item Details")
					{
						SET_INDEX_FIELD_VALUE(1, ITEM_BUILD_INFO_QUALITY);
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("Quality:"));
						VISIBILITY(SelectionIndexBox1, true);
						ADD_RANGE(SelectionIndexBox1)(gcnew cli::array< System::Object^ >(9) { L"Poor", L"Common", L"Uncommon", L"Rare", L"Epic", L"Legendary", L"Artifact", L"Heirloom", L"Mega Man" });
						UPDATE(SelectionIndexBox1);
						if(m_itemValues[ITEM_BUILD_INFO_QUALITY] == NULL)
							m_itemValues[ITEM_BUILD_INFO_QUALITY] = new TableInfoStruct("Poor");
						SET_TEXT(SelectionIndexBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_QUALITY]->val));

						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_NAME);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Name:"));
						SET_SIZE(SelectionInputBox1, 140, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_NAME] != NULL && strcmp(m_itemValues[ITEM_BUILD_INFO_NAME]->val, "UNKNOWN") != 0)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_NAME]->val));
						else m_itemValues[ITEM_BUILD_INFO_NAME] = new TableInfoStruct("UNKNOWN");

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_DISPLAY_ID);
						VISIBILITY(InputBox2Title, true);
						SET_TEXT(InputBox2Title, gcnew String("Display Id:"));
						SET_SIZE(SelectionInputBox2, 120, 18);
						SET_POSITION(SelectionInputBox2, 62, 78);
						VISIBILITY(SelectionInputBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_DISPLAY_ID] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_DISPLAY_ID]->val));
						else m_itemValues[ITEM_BUILD_INFO_DISPLAY_ID] = new TableInfoStruct("");

						SET_FIELD_VALUE(12, ITEM_BUILD_INFO_ENTRY_ID);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Entry Id:"));
						SET_SIZE(SelectionInputBox12, 140, 18);
						SET_POSITION(SelectionInputBox12, 187, 78);
						VISIBILITY(SelectionInputBox12, true);
						if(m_itemValues[ITEM_BUILD_INFO_ENTRY_ID] != NULL && strcmp(m_itemValues[ITEM_BUILD_INFO_ENTRY_ID]->val, "MUSTHAVEENTRYID") != 0)
							SET_TEXT(SelectionInputBox12, gcnew String(m_itemValues[ITEM_BUILD_INFO_ENTRY_ID]->val));
						else m_itemValues[ITEM_BUILD_INFO_ENTRY_ID] = new TableInfoStruct("MUSTHAVEENTRYID");

						SET_DESCRIPTION_FIELD_VALUE(2, ITEM_BUILD_INFO_QUOTE);
						VISIBILITY(InputBox22Title, true);
						SET_TEXT(InputBox22Title, gcnew String("Quote:"));
						VISIBILITY(DescriptionBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_QUOTE] != NULL)
							SET_TEXT(DescriptionBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_QUOTE]->val));
						else m_itemValues[ITEM_BUILD_INFO_QUOTE] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Type")
					{
						SET_INDEX_FIELD_VALUE(1, ITEM_BUILD_INFO_INVENTORY_TYPE);
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("Inv Type"));
						VISIBILITY(SelectionIndexBox1, true);
						ADD_RANGE(SelectionIndexBox1)(gcnew cli::array< System::Object^ >(8) { L"One Hand", L"Main Hand", L"Off Hand", L"Two Hand", L"Bow", L"Thrown", L"Crossbow", L"Gun/Wand" });
						UPDATE(SelectionIndexBox1);
						if(m_itemValues[ITEM_BUILD_INFO_INVENTORY_TYPE] == NULL)
							m_itemValues[ITEM_BUILD_INFO_INVENTORY_TYPE] = new TableInfoStruct("One Hand");
						SET_TEXT(SelectionIndexBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_INVENTORY_TYPE]->val));

						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_DURABILITY);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Durability"));
						SET_SIZE(SelectionInputBox1, 140, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_DURABILITY] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_DURABILITY]->val));
						else m_itemValues[ITEM_BUILD_INFO_DURABILITY] = new TableInfoStruct("");

						SET_INDEX_FIELD_VALUE(2, ITEM_BUILD_INFO_SUB_CLASS);
						VISIBILITY(InputBox2Title, true);
						SET_TEXT(InputBox2Title, gcnew String("Material"));
						VISIBILITY(SelectionIndexBox2, true);
						ADD_RANGE(SelectionIndexBox2)(gcnew cli::array< System::Object^ >(6) { L"Cloth", L"Leather", L"Mail", L"Plate", L"Buckler", L"Shield" });
						UPDATE(SelectionIndexBox2);
						if(m_itemValues[ITEM_BUILD_INFO_SUB_CLASS] == NULL)
							m_itemValues[ITEM_BUILD_INFO_SUB_CLASS] = new TableInfoStruct("Cloth");
						SET_TEXT(SelectionIndexBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_SUB_CLASS]->val));

						SET_INDEX_FIELD_VALUE(3, ITEM_BUILD_INFO_REPAIR_TYPE);
						VISIBILITY(InputBox3Title, true);
						SET_TEXT(InputBox3Title, gcnew String("Repair"));
						VISIBILITY(SelectionIndexBox3, true);
						ADD_RANGE(SelectionIndexBox3)(gcnew cli::array< System::Object^ >(2) { L"Weapon/Shield", L"Unrepairable" });
						UPDATE(SelectionIndexBox3);
						if(m_itemValues[ITEM_BUILD_INFO_REPAIR_TYPE] == NULL)
							m_itemValues[ITEM_BUILD_INFO_REPAIR_TYPE] = new TableInfoStruct("Weapon/Shield");
						SET_TEXT(SelectionIndexBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_REPAIR_TYPE]->val));

						SET_INDEX_FIELD_VALUE(4, ITEM_BUILD_INFO_BINDTYPE);
						VISIBILITY(InputBox4Title, true);
						SET_TEXT(InputBox4Title, gcnew String("Bind Type"));
						VISIBILITY(SelectionIndexBox4, true);
						ADD_RANGE(SelectionIndexBox4)(gcnew cli::array< System::Object^ >(4) { L"None", L"On Pickup", L"On Equip", L"On Use" });
						UPDATE(SelectionIndexBox4);
						if(m_itemValues[ITEM_BUILD_INFO_BINDTYPE] == NULL)
							m_itemValues[ITEM_BUILD_INFO_BINDTYPE] = new TableInfoStruct("None");
						SET_TEXT(SelectionIndexBox4, gcnew String(m_itemValues[ITEM_BUILD_INFO_BINDTYPE]->val));
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Armor Stats")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_BLOCK);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Block"));
						SET_SIZE(SelectionInputBox1, 140, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_BLOCK] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_BLOCK]->val));
						else m_itemValues[ITEM_BUILD_INFO_BLOCK] = new TableInfoStruct("");

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_ARMOR);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Armor"));
						SET_SIZE(SelectionInputBox2, 140, 18);
						VISIBILITY(SelectionInputBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_ARMOR] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_ARMOR]->val));
						else m_itemValues[ITEM_BUILD_INFO_ARMOR] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Requirements")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_REQUIRED_LEVEL);
						SET_FIELD_VALUE(11, ITEM_BUILD_INFO_ITEM_LEVEL);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("(Req Plr)/(Item Level)"));
						SET_POSITION(InputBox11Title, 175, 16);
						VISIBILITY(SelectionInputBox1, true);
						VISIBILITY(SelectionInputBox11, true);
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_LEVEL] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_LEVEL]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_LEVEL] = new TableInfoStruct("");
						if(m_itemValues[ITEM_BUILD_INFO_ITEM_LEVEL] != NULL)
							SET_TEXT(SelectionInputBox11, gcnew String(m_itemValues[ITEM_BUILD_INFO_ITEM_LEVEL]->val));
						else m_itemValues[ITEM_BUILD_INFO_ITEM_LEVEL] = new TableInfoStruct("");

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_REQUIRED_FACTION);
						SET_FIELD_VALUE(12, ITEM_BUILD_INFO_REQUIRED_FACTION_LEVEL);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Req (Rep Id)/(Standing)"));
						SET_POSITION(InputBox12Title, 175, 58);
						VISIBILITY(SelectionInputBox2, true);
						VISIBILITY(SelectionInputBox12, true);
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION] = new TableInfoStruct("");
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION_LEVEL] != NULL)
							SET_TEXT(SelectionInputBox12, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION_LEVEL]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_FACTION_LEVEL] = new TableInfoStruct("");

						SET_FIELD_VALUE(3, ITEM_BUILD_INFO_REQUIRED_SKILL);
						SET_FIELD_VALUE(13, ITEM_BUILD_INFO_REQUIRED_SKILL_LEVEL);
						VISIBILITY(InputBox13Title, true);
						SET_TEXT(InputBox13Title, gcnew String("Req (Skill Id)/(Level)"));
						SET_POSITION(InputBox13Title, 175, 99);
						VISIBILITY(SelectionInputBox3, true);
						VISIBILITY(SelectionInputBox13, true);
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL] != NULL)
							SET_TEXT(SelectionInputBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL] = new TableInfoStruct("");
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL_LEVEL] != NULL)
							SET_TEXT(SelectionInputBox13, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL_LEVEL]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_SKILL_LEVEL] = new TableInfoStruct("");

						SET_FIELD_VALUE(4, ITEM_BUILD_INFO_REQUIRED_SPELL);
						VISIBILITY(InputBox14Title, true);
						SET_TEXT(InputBox14Title, gcnew String("Required Spell"));
						SET_POSITION(InputBox14Title, 205, 141);
						SET_SIZE(SelectionInputBox4, 140, 18);
						VISIBILITY(SelectionInputBox4, true);
						if(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SPELL] != NULL)
							SET_TEXT(SelectionInputBox4, gcnew String(m_itemValues[ITEM_BUILD_INFO_REQUIRED_SPELL]->val));
						else m_itemValues[ITEM_BUILD_INFO_REQUIRED_SPELL] = new TableInfoStruct("");

						SET_FIELD_VALUE(5, ITEM_BUILD_INFO_UNIQUE);
						SET_FIELD_VALUE(15, ITEM_BUILD_INFO_MAX_STACK);
						VISIBILITY(InputBox15Title, true);
						SET_TEXT(InputBox15Title, gcnew String("(Unique Num)/(Stack Size)"));
						SET_POSITION(InputBox15Title, 175, 183);
						VISIBILITY(SelectionInputBox5, true);
						VISIBILITY(SelectionInputBox15, true);
						if(m_itemValues[ITEM_BUILD_INFO_UNIQUE] != NULL)
							SET_TEXT(SelectionInputBox5, gcnew String(m_itemValues[ITEM_BUILD_INFO_UNIQUE]->val));
						else m_itemValues[ITEM_BUILD_INFO_UNIQUE] = new TableInfoStruct("");
						if(m_itemValues[ITEM_BUILD_INFO_MAX_STACK] != NULL)
							SET_TEXT(SelectionInputBox15, gcnew String(m_itemValues[ITEM_BUILD_INFO_MAX_STACK]->val));
						else m_itemValues[ITEM_BUILD_INFO_MAX_STACK] = new TableInfoStruct("");

						SET_FIELD_VALUE(6, ITEM_BUILD_INFO_ALLOWABLE_CLASS);
						SET_FIELD_VALUE(16, ITEM_BUILD_INFO_ALLOWABLE_RACE);
						VISIBILITY(InputBox16Title, true);
						SET_TEXT(InputBox16Title, gcnew String("Req (Class)/(Race) Mask"));
						SET_POSITION(InputBox16Title, 175, 221);
						VISIBILITY(SelectionInputBox6, true);
						VISIBILITY(SelectionInputBox16, true);
						if(m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_CLASS] != NULL)
							SET_TEXT(SelectionInputBox6, gcnew String(m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_CLASS]->val));
						else m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_CLASS] = new TableInfoStruct("");
						if(m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_RACE] != NULL)
							SET_TEXT(SelectionInputBox16, gcnew String(m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_RACE]->val));
						else m_itemValues[ITEM_BUILD_INFO_ALLOWABLE_RACE] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Stats")
					{
						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(1, ITEM_BUILD_INFO_STAT_TYPE_1);
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("Stat Type 1"));
						VISIBILITY(SelectionIndexBox1, true);
						ADD_RANGE(SelectionIndexBox1)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox1);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_1] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_1] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_1]->val));

						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_STAT_VALUE_1);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Stat Value 1"));
						SET_SIZE(SelectionInputBox1, 140, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_1] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_1]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_1] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(2, ITEM_BUILD_INFO_STAT_TYPE_2);
						VISIBILITY(InputBox2Title, true);
						SET_TEXT(InputBox2Title, gcnew String("Stat Type 2"));
						VISIBILITY(SelectionIndexBox2, true);
						ADD_RANGE(SelectionIndexBox2)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox2);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_2] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_2] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_2]->val));

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_STAT_VALUE_2);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Stat Value 2"));
						SET_SIZE(SelectionInputBox2, 140, 18);
						VISIBILITY(SelectionInputBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_2] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_2]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_2] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(3, ITEM_BUILD_INFO_STAT_TYPE_3);
						VISIBILITY(InputBox3Title, true);
						SET_TEXT(InputBox3Title, gcnew String("Stat Type 3"));
						VISIBILITY(SelectionIndexBox3, true);
						ADD_RANGE(SelectionIndexBox3)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox3);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_3] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_3] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_3]->val));

						SET_FIELD_VALUE(3, ITEM_BUILD_INFO_STAT_VALUE_3);
						VISIBILITY(InputBox13Title, true);
						SET_TEXT(InputBox13Title, gcnew String("Stat Value 3"));
						SET_SIZE(SelectionInputBox3, 140, 18);
						VISIBILITY(SelectionInputBox3, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_3] != NULL)
							SET_TEXT(SelectionInputBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_3]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_3] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(4, ITEM_BUILD_INFO_STAT_TYPE_4);
						VISIBILITY(InputBox4Title, true);
						SET_TEXT(InputBox4Title, gcnew String("Stat Type 4"));
						VISIBILITY(SelectionIndexBox4, true);
						ADD_RANGE(SelectionIndexBox4)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox4);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_4] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_4] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox4, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_4]->val));

						SET_FIELD_VALUE(4, ITEM_BUILD_INFO_STAT_VALUE_4);
						VISIBILITY(InputBox14Title, true);
						SET_TEXT(InputBox14Title, gcnew String("Stat Value 4"));
						SET_SIZE(SelectionInputBox4, 140, 18);
						VISIBILITY(SelectionInputBox4, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_4] != NULL)
							SET_TEXT(SelectionInputBox4, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_4]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_4] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(5, ITEM_BUILD_INFO_STAT_TYPE_5);
						VISIBILITY(InputBox5Title, true);
						SET_TEXT(InputBox5Title, gcnew String("Stat Type 5"));
						VISIBILITY(SelectionIndexBox5, true);
						ADD_RANGE(SelectionIndexBox5)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox5);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_5] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_5] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox5, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_5]->val));

						SET_FIELD_VALUE(5, ITEM_BUILD_INFO_STAT_VALUE_5);
						VISIBILITY(InputBox15Title, true);
						SET_TEXT(InputBox15Title, gcnew String("Stat Value 5"));
						SET_SIZE(SelectionInputBox5, 140, 18);
						VISIBILITY(SelectionInputBox5, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_5] != NULL)
							SET_TEXT(SelectionInputBox5, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_5]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_5] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(6, ITEM_BUILD_INFO_STAT_TYPE_6);
						VISIBILITY(InputBox6Title, true);
						SET_TEXT(InputBox6Title, gcnew String("Stat Type 6"));
						VISIBILITY(SelectionIndexBox6, true);
						ADD_RANGE(SelectionIndexBox6)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox6);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_6] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_6] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox6, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_6]->val));

						SET_FIELD_VALUE(6, ITEM_BUILD_INFO_STAT_VALUE_6);
						VISIBILITY(InputBox16Title, true);
						SET_TEXT(InputBox16Title, gcnew String("Stat Value 6"));
						SET_SIZE(SelectionInputBox6, 140, 18);
						VISIBILITY(SelectionInputBox6, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_6] != NULL)
							SET_TEXT(SelectionInputBox6, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_6]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_6] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(7, ITEM_BUILD_INFO_STAT_TYPE_7);
						VISIBILITY(InputBox7Title, true);
						SET_TEXT(InputBox7Title, gcnew String("Stat Type 7"));
						VISIBILITY(SelectionIndexBox7, true);
						ADD_RANGE(SelectionIndexBox7)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox7);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_7] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_7] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox7, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_7]->val));

						SET_FIELD_VALUE(7, ITEM_BUILD_INFO_STAT_VALUE_7);
						VISIBILITY(InputBox17Title, true);
						SET_TEXT(InputBox17Title, gcnew String("Stat Value 7"));
						SET_SIZE(SelectionInputBox7, 140, 18);
						VISIBILITY(SelectionInputBox7, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_7] != NULL)
							SET_TEXT(SelectionInputBox7, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_7]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_7] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(8, ITEM_BUILD_INFO_STAT_TYPE_8);
						VISIBILITY(InputBox8Title, true);
						SET_TEXT(InputBox8Title, gcnew String("Stat Type 8"));
						VISIBILITY(SelectionIndexBox8, true);
						ADD_RANGE(SelectionIndexBox8)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox8);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_8] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_8] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox8, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_8]->val));

						SET_FIELD_VALUE(8, ITEM_BUILD_INFO_STAT_VALUE_8);
						VISIBILITY(InputBox18Title, true);
						SET_TEXT(InputBox18Title, gcnew String("Stat Value 8"));
						SET_SIZE(SelectionInputBox8, 140, 18);
						VISIBILITY(SelectionInputBox8, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_8] != NULL)
							SET_TEXT(SelectionInputBox8, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_8]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_8] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(9, ITEM_BUILD_INFO_STAT_TYPE_9);
						VISIBILITY(InputBox9Title, true);
						SET_TEXT(InputBox9Title, gcnew String("Stat Type 9"));
						VISIBILITY(SelectionIndexBox9, true);
						ADD_RANGE(SelectionIndexBox9)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox9);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_9] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_9] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox9, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_9]->val));

						SET_FIELD_VALUE(9, ITEM_BUILD_INFO_STAT_VALUE_9);
						VISIBILITY(InputBox19Title, true);
						SET_TEXT(InputBox19Title, gcnew String("Stat Value 9"));
						SET_SIZE(SelectionInputBox9, 140, 18);
						VISIBILITY(SelectionInputBox9, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_9] != NULL)
							SET_TEXT(SelectionInputBox9, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_9]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_9] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(10, ITEM_BUILD_INFO_STAT_TYPE_10);
						VISIBILITY(InputBox10Title, true);
						SET_TEXT(InputBox10Title, gcnew String("Stat Type 10"));
						VISIBILITY(SelectionIndexBox10, true);
						ADD_RANGE(SelectionIndexBox10)(gcnew cli::array< System::Object^ >(SUPPORTED_STAT_TYPE_NUM) { SUPPORTED_STAT_TYPE_FIRST SUPPORTED_STAT_TYPES });
						UPDATE(SelectionIndexBox10);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_10] == NULL)
							m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_10] = new TableInfoStruct(SUPPORTED_STAT_TYPE_FIRST);
						SET_TEXT(SelectionIndexBox10, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_TYPE_10]->val));

						SET_FIELD_VALUE(10, ITEM_BUILD_INFO_STAT_VALUE_10);
						VISIBILITY(InputBox20Title, true);
						SET_TEXT(InputBox20Title, gcnew String("Stat Value 10"));
						SET_SIZE(SelectionInputBox10, 140, 18);
						VISIBILITY(SelectionInputBox10, true);
						if(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_10] != NULL)
							SET_TEXT(SelectionInputBox10, gcnew String(m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_10]->val));
						else m_itemValues[ITEM_BUILD_INFO_STAT_VALUE_10] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Resists")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_HOLY_RESISTANCE);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Holy Resistance"));
						SET_SIZE(SelectionInputBox1, 180, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_HOLY_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_HOLY_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_HOLY_RESISTANCE] = new TableInfoStruct("");

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_FIRE_RESISTANCE);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Fire Resistance"));
						SET_SIZE(SelectionInputBox2, 180, 18);
						VISIBILITY(SelectionInputBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_FIRE_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_FIRE_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_FIRE_RESISTANCE] = new TableInfoStruct("");

						SET_FIELD_VALUE(3, ITEM_BUILD_INFO_NATURE_RESISTANCE);
						VISIBILITY(InputBox13Title, true);
						SET_TEXT(InputBox13Title, gcnew String("Nature Resistance"));
						SET_SIZE(SelectionInputBox3, 180, 18);
						VISIBILITY(SelectionInputBox3, true);
						if(m_itemValues[ITEM_BUILD_INFO_NATURE_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_NATURE_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_NATURE_RESISTANCE] = new TableInfoStruct("");

						SET_FIELD_VALUE(4, ITEM_BUILD_INFO_FROST_RESISTANCE);
						VISIBILITY(InputBox14Title, true);
						SET_TEXT(InputBox14Title, gcnew String("Frost Resistance"));
						SET_SIZE(SelectionInputBox4, 180, 18);
						VISIBILITY(SelectionInputBox4, true);
						if(m_itemValues[ITEM_BUILD_INFO_FROST_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox4, gcnew String(m_itemValues[ITEM_BUILD_INFO_FROST_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_FROST_RESISTANCE] = new TableInfoStruct("");

						SET_FIELD_VALUE(5, ITEM_BUILD_INFO_SHADOW_RESISTANCE);
						VISIBILITY(InputBox15Title, true);
						SET_TEXT(InputBox15Title, gcnew String("Shadow Resistance"));
						SET_SIZE(SelectionInputBox5, 180, 18);
						VISIBILITY(SelectionInputBox5, true);
						if(m_itemValues[ITEM_BUILD_INFO_SHADOW_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox5, gcnew String(m_itemValues[ITEM_BUILD_INFO_SHADOW_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_SHADOW_RESISTANCE] = new TableInfoStruct("");

						SET_FIELD_VALUE(6, ITEM_BUILD_INFO_ARCANE_RESISTANCE);
						VISIBILITY(InputBox16Title, true);
						SET_TEXT(InputBox16Title, gcnew String("Arcane Resistance"));
						SET_SIZE(SelectionInputBox6, 180, 18);
						VISIBILITY(SelectionInputBox6, true);
						if(m_itemValues[ITEM_BUILD_INFO_ARCANE_RESISTANCE] != NULL)
							SET_TEXT(SelectionInputBox6, gcnew String(m_itemValues[ITEM_BUILD_INFO_ARCANE_RESISTANCE]->val));
						else m_itemValues[ITEM_BUILD_INFO_ARCANE_RESISTANCE] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Bonuses")
					{
						// TODO!
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("TODO"));
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Sockets")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_SOCKET_BONUS);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Socket Bonus"));
						SET_SIZE(SelectionInputBox1, 140, 18);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_SOCKET_BONUS] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_SOCKET_BONUS]->val));
						else m_itemValues[ITEM_BUILD_INFO_SOCKET_BONUS] = new TableInfoStruct("");

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(1, ITEM_BUILD_INFO_SOCKET_TYPE_1);
						VISIBILITY(InputBox1Title, true);
						SET_TEXT(InputBox1Title, gcnew String("Gem Type 1"));
						VISIBILITY(SelectionIndexBox1, true);
						ADD_RANGE(SelectionIndexBox1)(gcnew cli::array< System::Object^ >(GEM_INDEX_COUNT) { GEM_INDEX_LIST_FIRST GEM_INDEX_LIST });
						UPDATE(SelectionIndexBox1);
						if(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_1] == NULL)
							m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_1] = new TableInfoStruct(GEM_INDEX_LIST_FIRST);
						SET_TEXT(SelectionIndexBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_1]->val));

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(2, ITEM_BUILD_INFO_SOCKET_TYPE_2);
						VISIBILITY(InputBox2Title, true);
						SET_TEXT(InputBox2Title, gcnew String("Gem Type 2"));
						VISIBILITY(SelectionIndexBox2, true);
						ADD_RANGE(SelectionIndexBox2)(gcnew cli::array< System::Object^ >(GEM_INDEX_COUNT) { GEM_INDEX_LIST_FIRST GEM_INDEX_LIST });
						UPDATE(SelectionIndexBox2);
						if(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_2] == NULL)
							m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_2] = new TableInfoStruct(GEM_INDEX_LIST_FIRST);
						SET_TEXT(SelectionIndexBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_2]->val));

						//////////////////////
						///
						SET_INDEX_FIELD_VALUE(3, ITEM_BUILD_INFO_SOCKET_TYPE_3);
						VISIBILITY(InputBox3Title, true);
						SET_TEXT(InputBox3Title, gcnew String("Gem Type 3"));
						VISIBILITY(SelectionIndexBox3, true);
						ADD_RANGE(SelectionIndexBox3)(gcnew cli::array< System::Object^ >(GEM_INDEX_COUNT) { GEM_INDEX_LIST_FIRST GEM_INDEX_LIST });
						UPDATE(SelectionIndexBox3);
						if(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_3] == NULL)
							m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_3] = new TableInfoStruct(GEM_INDEX_LIST_FIRST);
						SET_TEXT(SelectionIndexBox3, gcnew String(m_itemValues[ITEM_BUILD_INFO_SOCKET_TYPE_3]->val));
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Set")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_SET_ID);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Set Id"));
						SET_SIZE(SelectionInputBox1, 140, 20);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_SET_ID] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_SET_ID]->val));
						else m_itemValues[ITEM_BUILD_INFO_SET_ID] = new TableInfoStruct("");
					}
					else if(master->window->ItemSettingsIndex->Text == "Item Value")
					{
						SET_FIELD_VALUE(1, ITEM_BUILD_INFO_BUY_PRICE);
						VISIBILITY(InputBox11Title, true);
						SET_TEXT(InputBox11Title, gcnew String("Buy Price"));
						SET_SIZE(SelectionInputBox1, 140, 20);
						VISIBILITY(SelectionInputBox1, true);
						if(m_itemValues[ITEM_BUILD_INFO_BUY_PRICE] != NULL)
							SET_TEXT(SelectionInputBox1, gcnew String(m_itemValues[ITEM_BUILD_INFO_BUY_PRICE]->val));
						else m_itemValues[ITEM_BUILD_INFO_BUY_PRICE] = new TableInfoStruct("");

						SET_FIELD_VALUE(2, ITEM_BUILD_INFO_SELL_PRICE);
						VISIBILITY(InputBox12Title, true);
						SET_TEXT(InputBox12Title, gcnew String("Sell Price"));
						SET_SIZE(SelectionInputBox2, 140, 20);
						VISIBILITY(SelectionInputBox2, true);
						if(m_itemValues[ITEM_BUILD_INFO_SELL_PRICE] != NULL)
							SET_TEXT(SelectionInputBox2, gcnew String(m_itemValues[ITEM_BUILD_INFO_SELL_PRICE]->val));
						else m_itemValues[ITEM_BUILD_INFO_SELL_PRICE] = new TableInfoStruct("");
					}
				}break;
			case 3:
				{

				}break;
			case 4:
				{

				}break;
			}
		}break;
	case 2:
		{
//			master->window->SelectionInputBox1->Visible = true;
		}break;
	case 3:
		{
//			master->window->SelectionInputBox1->Visible = true;
		}break;
	case 4:
		{
//			master->window->SelectionInputBox1->Visible = true;
		}break;
	}
	SystemPrintfDebug("Item Settings Index Changed!");
}

void UpdateInputSettings(Master^ master, uint32 calltype, uint8 extra);
void UpdateCoreSelectionList(Master^ master, uint32 calltype);

void RedundantScreenUpdates(Master^ master, uint32 calltype, uint8 extra = 0)
{
	ItemSystemSet1 = false;
	for(int index = 0; index < ITEM_BUILD_MAX; index++)
	{
		if(m_itemValues[index] != NULL)
		{
			delete m_itemValues[index];
			m_itemValues[index] = NULL;
		}
	}

	memset(m_itemValues, 0, sizeof(TableInfoStruct*)*ITEM_BUILD_MAX);
	memset(FieldValue, -1, sizeof(int)*20);
	memset(IndexFieldValues, -1, sizeof(int)*10);
	memset(DescriptionFieldValue, -1, sizeof(int)*2);
	UpdateCoreSelectionList(master, calltype);
	UpdateInputSettings(master, calltype, extra);
}

System::Void MainForm::WeaponCreatorButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	RedundantScreenUpdates(masterClass, SCRIPT_TYPE_ITEM_INFO, 1);
	Button^ Creator = (Button^)(sender);
	this->SaveButton->Enabled = true;
	this->CoreSelectionBox->Enabled = true;
}

System::Void MainForm::ArmorCreatorButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	RedundantScreenUpdates(masterClass, SCRIPT_TYPE_ITEM_INFO, 2);
	Button^ Creator = (Button^)(sender);
	this->SaveButton->Enabled = true;
	this->CoreSelectionBox->Enabled = true;
}

System::Void MainForm::JewelCreatorButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	RedundantScreenUpdates(masterClass, SCRIPT_TYPE_ITEM_INFO, 3);
	Button^ Creator = (Button^)(sender);
	this->SaveButton->Enabled = true;
	this->CoreSelectionBox->Enabled = true;
}

System::Void MainForm::MiscItemCreatorButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	RedundantScreenUpdates(masterClass, SCRIPT_TYPE_ITEM_INFO, 4);
	Button^ Creator = (Button^)(sender);
	this->SaveButton->Enabled = true;
	this->CoreSelectionBox->Enabled = true;
}

System::Void MainForm::NPCCreatorButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	RedundantScreenUpdates(masterClass, SCRIPT_TYPE_CREATURE_INFO);
	Button^ Creator = (Button^)(sender);
	this->SaveButton->Enabled = true;
	this->CoreSelectionBox->Enabled = true;
}

System::Void MainForm::VendorCreatorButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	RedundantScreenUpdates(masterClass, SCRIPT_TYPE_VENDOR_INFO);
	Button^ Creator = (Button^)(sender);
	this->SaveButton->Enabled = true;
	this->CoreSelectionBox->Enabled = true;
}

System::Void MainForm::LootCreatorButton_Click(System::Object^  sender, System::EventArgs^  e)
{
	RedundantScreenUpdates(masterClass, SCRIPT_TYPE_LOOT_INFO);
	Button^ Creator = (Button^)(sender);
	this->SaveButton->Enabled = true;
	this->CoreSelectionBox->Enabled = true;
}

System::Void MainForm::ItemSettingsIndex_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	UpdateBasedOnInputSettings(masterClass);
}

bool printingSystem;

std::vector<std::string> SystemText;

void SystemPrint(char* format)
{
	while(printingSystem) {}

	string str = string(format);
	str += "\r\n\r\n";
	SystemText.push_back(str);
}

void SystemPrintf(char* format, ...)
{
	va_list ap;
	char buf[32768];
	va_start(ap, format);
	vsnprintf(buf, 32768, format, ap);
	va_end(ap);

	SystemPrint(buf);
}

void SystemPrintfDebug(char* format, ...)
{
#ifdef _DEBUG
	va_list ap;
	char buf[32768];
	va_start(ap, format);
	vsnprintf(buf, 32768, format, ap);
	va_end(ap);

	SystemPrint(buf);
#endif
}

void SaveCurrentVariables(Master^ master)
{
	if(FieldValue[0] >= 0 && m_itemValues[FieldValue[0]] != NULL)
	{
		char* text = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox1->Text);
		if(FieldValue[0] == ITEM_BUILD_INFO_NAME)
		{
			if(strlen(text) || atol(text) || atof(text))
				m_itemValues[FieldValue[0]]->val = text;
			else
			{
				SET_TEXT(SelectionInputBox1, "");
				m_itemValues[FieldValue[0]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi("UNKNOWN");
			}
		}
		else m_itemValues[FieldValue[0]]->val = text;
	}

	if(FieldValue[4] >= 0 && m_itemValues[FieldValue[4]] != NULL)
	{
		char* text = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox5->Text);
		if(FieldValue[4] == ITEM_BUILD_INFO_ENTRY_ID)
		{
			if(strlen(text) || atol(text) || atof(text))
				m_itemValues[FieldValue[4]]->val = text;
			else
			{
				SET_TEXT(SelectionInputBox5, "");
				m_itemValues[FieldValue[4]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi("MUSTHAVEENTRYID");
			}
		}
		else m_itemValues[FieldValue[4]]->val = text;
	}

	if(FieldValue[1] >= 0 && m_itemValues[FieldValue[1]] != NULL) { m_itemValues[FieldValue[1]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox2->Text); }
	if(FieldValue[2] >= 0 && m_itemValues[FieldValue[2]] != NULL) { m_itemValues[FieldValue[2]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox3->Text); }
	if(FieldValue[3] >= 0 && m_itemValues[FieldValue[3]] != NULL) { m_itemValues[FieldValue[3]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox4->Text); }
	if(FieldValue[5] >= 0 && m_itemValues[FieldValue[5]] != NULL) { m_itemValues[FieldValue[5]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox6->Text); }
	if(FieldValue[6] >= 0 && m_itemValues[FieldValue[6]] != NULL) { m_itemValues[FieldValue[6]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox7->Text); }
	if(FieldValue[7] >= 0 && m_itemValues[FieldValue[7]] != NULL) { m_itemValues[FieldValue[7]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox8->Text); }
	if(FieldValue[8] >= 0 && m_itemValues[FieldValue[8]] != NULL) { m_itemValues[FieldValue[8]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox9->Text); }
	if(FieldValue[9] >= 0 && m_itemValues[FieldValue[9]] != NULL) { m_itemValues[FieldValue[9]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox10->Text); }
	if(FieldValue[10] >= 0 && m_itemValues[FieldValue[10]] != NULL) { m_itemValues[FieldValue[10]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox11->Text); }
	if(FieldValue[11] >= 0 && m_itemValues[FieldValue[11]] != NULL) { m_itemValues[FieldValue[11]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox12->Text); }
	if(FieldValue[12] >= 0 && m_itemValues[FieldValue[12]] != NULL) { m_itemValues[FieldValue[12]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox13->Text); }
	if(FieldValue[13] >= 0 && m_itemValues[FieldValue[13]] != NULL) { m_itemValues[FieldValue[13]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox14->Text); }
	if(FieldValue[14] >= 0 && m_itemValues[FieldValue[14]] != NULL) { m_itemValues[FieldValue[14]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox15->Text); }
	if(FieldValue[15] >= 0 && m_itemValues[FieldValue[15]] != NULL) { m_itemValues[FieldValue[15]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox16->Text); }
	if(FieldValue[16] >= 0 && m_itemValues[FieldValue[16]] != NULL) { m_itemValues[FieldValue[16]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox17->Text); }
	if(FieldValue[17] >= 0 && m_itemValues[FieldValue[17]] != NULL) { m_itemValues[FieldValue[17]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox18->Text); }
	if(FieldValue[18] >= 0 && m_itemValues[FieldValue[18]] != NULL) { m_itemValues[FieldValue[18]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox19->Text); }
	if(FieldValue[19] >= 0 && m_itemValues[FieldValue[19]] != NULL) { m_itemValues[FieldValue[19]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionInputBox20->Text); }

	if(IndexFieldValues[0] >= 0 && m_itemValues[IndexFieldValues[0]] != NULL) { m_itemValues[IndexFieldValues[0]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionIndexBox1->Text); }
	if(IndexFieldValues[1] >= 0 && m_itemValues[IndexFieldValues[1]] != NULL) { m_itemValues[IndexFieldValues[1]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionIndexBox2->Text); }
	if(IndexFieldValues[2] >= 0 && m_itemValues[IndexFieldValues[2]] != NULL) { m_itemValues[IndexFieldValues[2]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionIndexBox3->Text); }
	if(IndexFieldValues[3] >= 0 && m_itemValues[IndexFieldValues[3]] != NULL) { m_itemValues[IndexFieldValues[3]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionIndexBox4->Text); }
	if(IndexFieldValues[5] >= 0 && m_itemValues[IndexFieldValues[5]] != NULL) { m_itemValues[IndexFieldValues[5]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionIndexBox5->Text); }
	if(IndexFieldValues[6] >= 0 && m_itemValues[IndexFieldValues[6]] != NULL) { m_itemValues[IndexFieldValues[6]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionIndexBox6->Text); }
	if(IndexFieldValues[7] >= 0 && m_itemValues[IndexFieldValues[7]] != NULL) { m_itemValues[IndexFieldValues[7]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionIndexBox7->Text); }
	if(IndexFieldValues[8] >= 0 && m_itemValues[IndexFieldValues[8]] != NULL) { m_itemValues[IndexFieldValues[8]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionIndexBox8->Text); }
	if(IndexFieldValues[9] >= 0 && m_itemValues[IndexFieldValues[9]] != NULL) { m_itemValues[IndexFieldValues[9]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->SelectionIndexBox9->Text); }

	if(DescriptionFieldValue[0] >= 0 && m_itemValues[DescriptionFieldValue[0]] != NULL) { m_itemValues[DescriptionFieldValue[0]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->DescriptionBox1->Text); }
	if(DescriptionFieldValue[1] >= 0 && m_itemValues[DescriptionFieldValue[1]] != NULL) { m_itemValues[DescriptionFieldValue[1]]->val = (char*)(void*)Marshal::StringToHGlobalAnsi(master->window->DescriptionBox2->Text); }

	memset(FieldValue, -1, sizeof(int)*20);
	memset(IndexFieldValues, -1, sizeof(int)*10);
	memset(DescriptionFieldValue, -1, sizeof(int)*2);
}

void ResetInputVariables(Master^ master)
{
	VISIBILITY(WarningText, true);

	SystemPrintfDebug("Resetting Input Box Info");
	VISIBILITY(InputBox1Title, false);
	VISIBILITY(InputBox2Title, false);
	VISIBILITY(InputBox3Title, false);
	VISIBILITY(InputBox4Title, false);
	VISIBILITY(InputBox5Title, false);
	VISIBILITY(InputBox6Title, false);
	VISIBILITY(InputBox7Title, false);
	VISIBILITY(InputBox8Title, false);
	VISIBILITY(InputBox9Title, false);
	VISIBILITY(InputBox10Title, false);
	VISIBILITY(InputBox11Title, false);
	VISIBILITY(InputBox12Title, false);
	VISIBILITY(InputBox13Title, false);
	VISIBILITY(InputBox14Title, false);
	VISIBILITY(InputBox15Title, false);
	VISIBILITY(InputBox16Title, false);
	VISIBILITY(InputBox17Title, false);
	VISIBILITY(InputBox18Title, false);
	VISIBILITY(InputBox19Title, false);
	VISIBILITY(InputBox20Title, false);
	VISIBILITY(InputBox21Title, false);
	VISIBILITY(InputBox22Title, false);

	SET_POSITION(InputBox1Title, 80, 16);
	SET_POSITION(InputBox2Title, 80, 58);
	SET_POSITION(InputBox3Title, 80, 99);
	SET_POSITION(InputBox4Title, 80, 141);
	SET_POSITION(InputBox5Title, 80, 183);
	SET_POSITION(InputBox6Title, 80, 221);
	SET_POSITION(InputBox7Title, 80, 262);
	SET_POSITION(InputBox8Title, 80, 306);
	SET_POSITION(InputBox9Title, 80, 348);
	SET_POSITION(InputBox10Title, 80, 389);
	SET_POSITION(InputBox11Title, 215, 16);
	SET_POSITION(InputBox12Title, 215, 58);
	SET_POSITION(InputBox13Title, 215, 99);
	SET_POSITION(InputBox14Title, 215, 141);
	SET_POSITION(InputBox15Title, 215, 183);
	SET_POSITION(InputBox16Title, 215, 221);
	SET_POSITION(InputBox17Title, 215, 262);
	SET_POSITION(InputBox18Title, 215, 306);
	SET_POSITION(InputBox19Title, 215, 348);
	SET_POSITION(InputBox20Title, 215, 389);
	SET_POSITION(InputBox21Title, 12, 435);
	SET_POSITION(InputBox22Title, 12, 492);

	SystemPrintfDebug("Resetting Selection Index Info");
	VISIBILITY(SelectionIndexBox1, false);
	VISIBILITY(SelectionIndexBox2, false);
	VISIBILITY(SelectionIndexBox3, false);
	VISIBILITY(SelectionIndexBox4, false);
	VISIBILITY(SelectionIndexBox5, false);
	VISIBILITY(SelectionIndexBox6, false);
	VISIBILITY(SelectionIndexBox7, false);
	VISIBILITY(SelectionIndexBox8, false);
	VISIBILITY(SelectionIndexBox9, false);
	VISIBILITY(SelectionIndexBox10, false);

	CLEAR_RANGE(SelectionIndexBox1);
	CLEAR_RANGE(SelectionIndexBox2);
	CLEAR_RANGE(SelectionIndexBox3);
	CLEAR_RANGE(SelectionIndexBox4);
	CLEAR_RANGE(SelectionIndexBox5);
	CLEAR_RANGE(SelectionIndexBox6);
	CLEAR_RANGE(SelectionIndexBox7);
	CLEAR_RANGE(SelectionIndexBox8);
	CLEAR_RANGE(SelectionIndexBox9);
	CLEAR_RANGE(SelectionIndexBox10);

	SET_POSITION(SelectionIndexBox1, 62, 37);
	SET_POSITION(SelectionIndexBox2, 62, 78);
	SET_POSITION(SelectionIndexBox3, 62, 119);
	SET_POSITION(SelectionIndexBox4, 62, 163);
	SET_POSITION(SelectionIndexBox5, 62, 202);
	SET_POSITION(SelectionIndexBox6, 62, 242);
	SET_POSITION(SelectionIndexBox7, 62, 283);
	SET_POSITION(SelectionIndexBox8, 62, 327);
	SET_POSITION(SelectionIndexBox9, 62, 370);
	SET_POSITION(SelectionIndexBox10, 62, 409);

	SystemPrintfDebug("Resetting Input Box Info");
	SET_TEXT(InputBox1Title, "InputBox1");
	SET_TEXT(InputBox2Title, "InputBox2");
	SET_TEXT(InputBox3Title, "InputBox3");
	SET_TEXT(InputBox4Title, "InputBox4");
	SET_TEXT(InputBox5Title, "InputBox5");
	SET_TEXT(InputBox6Title, "InputBox6");
	SET_TEXT(InputBox7Title, "InputBox7");
	SET_TEXT(InputBox8Title, "InputBox8");
	SET_TEXT(InputBox9Title, "InputBox9");
	SET_TEXT(InputBox10Title, "InputBox10");

	SET_TEXT(InputBox11Title, "InputBox11");
	SET_TEXT(InputBox12Title, "InputBox12");
	SET_TEXT(InputBox13Title, "InputBox13");
	SET_TEXT(InputBox14Title, "InputBox14");
	SET_TEXT(InputBox15Title, "InputBox15");
	SET_TEXT(InputBox16Title, "InputBox16");
	SET_TEXT(InputBox17Title, "InputBox17");
	SET_TEXT(InputBox18Title, "InputBox18");
	SET_TEXT(InputBox19Title, "InputBox19");
	SET_TEXT(InputBox20Title, "InputBox20");
	SET_TEXT(InputBox21Title, "InputBox21");
	SET_TEXT(InputBox22Title, "InputBox22");

	VISIBILITY(SelectionInputBox1, false);
	VISIBILITY(SelectionInputBox2, false);
	VISIBILITY(SelectionInputBox3, false);
	VISIBILITY(SelectionInputBox4, false);
	VISIBILITY(SelectionInputBox5, false);
	VISIBILITY(SelectionInputBox6, false);
	VISIBILITY(SelectionInputBox7, false);
	VISIBILITY(SelectionInputBox8, false);
	VISIBILITY(SelectionInputBox9, false);
	VISIBILITY(SelectionInputBox10, false);
	VISIBILITY(SelectionInputBox11, false);
	VISIBILITY(SelectionInputBox12, false);
	VISIBILITY(SelectionInputBox13, false);
	VISIBILITY(SelectionInputBox14, false);
	VISIBILITY(SelectionInputBox15, false);
	VISIBILITY(SelectionInputBox16, false);
	VISIBILITY(SelectionInputBox17, false);
	VISIBILITY(SelectionInputBox18, false);
	VISIBILITY(SelectionInputBox19, false);
	VISIBILITY(SelectionInputBox20, false);

	SET_POSITION(SelectionInputBox1, 187, 36);
	SET_POSITION(SelectionInputBox2, 187, 78);
	SET_POSITION(SelectionInputBox3, 187, 118);
	SET_POSITION(SelectionInputBox4, 187, 162);
	SET_POSITION(SelectionInputBox5, 187, 201);
	SET_POSITION(SelectionInputBox6, 187, 241);
	SET_POSITION(SelectionInputBox7, 187, 282);
	SET_POSITION(SelectionInputBox8, 187, 326);
	SET_POSITION(SelectionInputBox9, 187, 369);
	SET_POSITION(SelectionInputBox10, 187, 409);
	SET_POSITION(SelectionInputBox11, 259, 36);
	SET_POSITION(SelectionInputBox12, 259, 78);
	SET_POSITION(SelectionInputBox13, 259, 118);
	SET_POSITION(SelectionInputBox14, 259, 162);
	SET_POSITION(SelectionInputBox15, 259, 201);
	SET_POSITION(SelectionInputBox16, 259, 241);
	SET_POSITION(SelectionInputBox17, 259, 282);
	SET_POSITION(SelectionInputBox18, 259, 326);
	SET_POSITION(SelectionInputBox19, 259, 369);
	SET_POSITION(SelectionInputBox20, 259, 409);

	VISIBILITY(DescriptionBox1, false);
	VISIBILITY(DescriptionBox2, false);

	SET_SIZE(SelectionInputBox1, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox2, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox3, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox4, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox5, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox6, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox7, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox8, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox9, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox10, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox11, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox12, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox13, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox14, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox15, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox16, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox17, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox18, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox19, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);
	SET_SIZE(SelectionInputBox20, ORIGINAL_SIZE_1, ORIGINAL_SIZE_2);

	SET_SIZE(DescriptionBox1, 283, 50);
	SET_SIZE(DescriptionBox2, 283, 50);

	SET_TEXT(SelectionInputBox1, "");
	SET_TEXT(SelectionInputBox2, "");
	SET_TEXT(SelectionInputBox3, "");
	SET_TEXT(SelectionInputBox4, "");
	SET_TEXT(SelectionInputBox5, "");
	SET_TEXT(SelectionInputBox6, "");
	SET_TEXT(SelectionInputBox7, "");
	SET_TEXT(SelectionInputBox8, "");
	SET_TEXT(SelectionInputBox9, "");
	SET_TEXT(SelectionInputBox10, "");
	SET_TEXT(SelectionInputBox11, "");
	SET_TEXT(SelectionInputBox12, "");
	SET_TEXT(SelectionInputBox13, "");
	SET_TEXT(SelectionInputBox14, "");
	SET_TEXT(SelectionInputBox15, "");
	SET_TEXT(SelectionInputBox16, "");
	SET_TEXT(SelectionInputBox17, "");
	SET_TEXT(SelectionInputBox18, "");
	SET_TEXT(SelectionInputBox19, "");
	SET_TEXT(SelectionInputBox20, "");

	SET_TEXT(DescriptionBox1, "");
	SET_TEXT(DescriptionBox2, "");
}

void UpdateInputSettings(Master^ master, uint32 calltype, uint8 extra)
{
	switch(calltype)
	{
	case SCRIPT_TYPE_ITEM_INFO:
		{
			master->window->ItemSettingsIndex->Visible = true;
			if(ExtraCallType != extra || ItemSelectionCallType != SCRIPT_TYPE_ITEM_INFO)
			{
				ExtraCallType = extra;
				CLEAR_RANGE(ItemSettingsIndex);

				ItemSelectionCallType = SCRIPT_TYPE_ITEM_INFO;
				if(extra == 1)
					master->window->ItemSettingsIndex->Items->AddRange(gcnew cli::array< System::Object^ >(ITEM_INDEX_1_COUNT) { ITEM_INDEX_LIST_FIRST ITEM_INDEX_1_LIST });
				else if(extra == 2)
					master->window->ItemSettingsIndex->Items->AddRange(gcnew cli::array< System::Object^ >(ITEM_INDEX_2_COUNT) { ITEM_INDEX_LIST_FIRST ITEM_INDEX_2_LIST });
				else if(extra == 3)
					master->window->ItemSettingsIndex->Items->AddRange(gcnew cli::array< System::Object^ >(ITEM_INDEX_2_COUNT) { ITEM_INDEX_LIST_FIRST ITEM_INDEX_2_LIST });
				else if(extra == 4)
					master->window->ItemSettingsIndex->Items->AddRange(gcnew cli::array< System::Object^ >(ITEM_INDEX_2_COUNT) { ITEM_INDEX_LIST_FIRST ITEM_INDEX_2_LIST });

				master->window->ItemSettingsIndex->Text = gcnew String(ITEM_INDEX_LIST_FIRST);
				master->window->ItemSettingsIndex->Update();
			}
		}break;
	case SCRIPT_TYPE_CREATURE_INFO:
		{
			master->window->ItemSettingsIndex->Visible = true;
			if(ItemSelectionCallType != SCRIPT_TYPE_CREATURE_INFO)
			{
				CLEAR_RANGE(ItemSettingsIndex);

				ItemSelectionCallType = SCRIPT_TYPE_CREATURE_INFO;
				master->window->ItemSettingsIndex->Items->AddRange(gcnew cli::array< System::Object^ >(NPC_INDEX_COUNT) { NPC_INDEX_LIST_FIRST NPC_INDEX_LIST });
				master->window->ItemSettingsIndex->Text = gcnew String(NPC_INDEX_LIST_FIRST);
				master->window->ItemSettingsIndex->Update();
			}
		}break;
	case SCRIPT_TYPE_VENDOR_INFO:
		{
			master->window->ItemSettingsIndex->Visible = false;
			if(ItemSelectionCallType != SCRIPT_TYPE_VENDOR_INFO)
			{
				CLEAR_RANGE(ItemSettingsIndex);
				ItemSelectionCallType = SCRIPT_TYPE_VENDOR_INFO;
				UpdateBasedOnInputSettings(master);
			}
		}break;
	case SCRIPT_TYPE_LOOT_INFO:
		{
			master->window->ItemSettingsIndex->Visible = false;
			if(ItemSelectionCallType != SCRIPT_TYPE_LOOT_INFO)
			{
				CLEAR_RANGE(ItemSettingsIndex);
				ItemSelectionCallType = SCRIPT_TYPE_LOOT_INFO;
				UpdateBasedOnInputSettings(master);
			}
		}break;
	default:
		{
			CLEAR_RANGE(ItemSettingsIndex);
			ItemSelectionCallType = 0;
		}
	}
}

uint32 selectionIndex = 1;

void UpdateCoreSelectionList(Master^ master, uint32 calltype)
{
	CLEAR_RANGE(CoreSelectionBox);
	master->window->CoreSelectionBox->Items->AddRange(gcnew cli::array< System::Object^ >(1) { (gcnew System::String("Unknown")) });
	selectionIndex = 1;

	BuildInfoMap::iterator itr;
	switch(calltype)
	{
	case SCRIPT_TYPE_ITEM_INFO:
		{
			if(ItemInfoLibs.size())
			{
				for(itr = ItemInfoLibs.begin(); itr != ItemInfoLibs.end(); itr++)
				{
					selectionIndex++;
					master->window->CoreSelectionBox->Items->AddRange(gcnew cli::array< System::Object^ >(1) { (gcnew System::String(itr->first)) });
				}
				itr = ItemInfoLibs.begin();
			}
		}break;
	case SCRIPT_TYPE_CREATURE_INFO:
		{
			if(CreatureInfoLibs.size())
			{
				for(itr = CreatureInfoLibs.begin(); itr != CreatureInfoLibs.end(); itr++)
				{
					selectionIndex++;
					master->window->CoreSelectionBox->Items->AddRange(gcnew cli::array< System::Object^ >(1) { (gcnew System::String(itr->first)) });
				}
				itr = CreatureInfoLibs.begin();
			}
		}break;
	case SCRIPT_TYPE_VENDOR_INFO:
		{
			if(VendorInfoLibs.size())
			{
				for(itr = VendorInfoLibs.begin(); itr != VendorInfoLibs.end(); itr++)
				{
					selectionIndex++;
					master->window->CoreSelectionBox->Items->AddRange(gcnew cli::array< System::Object^ >(1) { (gcnew System::String(itr->first)) });
				}
				itr = VendorInfoLibs.begin();
			}
		}break;
	case SCRIPT_TYPE_LOOT_INFO:
		{
			if(LootInfoLibs.size())
			{
				for(itr = LootInfoLibs.begin(); itr != LootInfoLibs.end(); itr++)
				{
					selectionIndex++;
					master->window->CoreSelectionBox->Items->AddRange(gcnew cli::array< System::Object^ >(1) { (gcnew System::String(itr->first)) });
				}
				itr = LootInfoLibs.begin();
			}
		}break;
	}

	SystemSet = false;
	if(master->manager->GetPrefered(SelectedCore, calltype))
	{ }
	else if(selectionIndex > 1)
		SelectedCore = itr->first;
	else
		SelectedCore = "Unknown";

	master->window->CoreSelectionBox->Text = gcnew String(string(SelectedCore).c_str());
	master->window->CoreSelectionBox->Update();
}
