#pragma once

using namespace std;

extern bool printingSystem;

extern vector<std::string> SystemText;

namespace sandshroud
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		Master^ masterClass;
	public:
		MainForm(Master^ master)
		{
			masterClass = master;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

		/*************
		 * System Box
		 */
	public:
		void SystemBoxClear()
		{
			SystemBox->Text = "\r\n";
			SystemBox->Update();
		}

		void CallSystemBoxClear()
		{
			MethodInvoker^ action = gcnew MethodInvoker(this, &MainForm::SystemBoxClear);
			SystemBox->BeginInvoke(action);
		}

		void WriteToSystemBox()
		{
			printingSystem = true;
			vector<std::string>::iterator itr = SystemText.begin();
			for(; itr != SystemText.end(); itr++)
				SystemBox->Text += (gcnew System::String((*itr).c_str()));

			SystemText.clear();
			SystemBox->Update();
			printingSystem = false;
		}

		void CallWriteToSystemBox()
		{
			if(!SystemText.size() || printingSystem)
				return;

			MethodInvoker^ action = gcnew MethodInvoker(this, &MainForm::WriteToSystemBox);
			SystemBox->BeginInvoke(action);
		}

		void WriteToSystemBox(System::String^ str)
		{
			SystemBox->Text += str;
			SystemBox->Update();
		}

	public:
		array<System::Drawing::Point>^ StartingLoc;

		System::Windows::Forms::Label^  CoreTypeTitle;
		System::Windows::Forms::Label^  SystemInfoBoxTitle;

		System::Windows::Forms::Label^  CreditsInspiration;
		System::Windows::Forms::Label^  CreditsCreatedBy;

		System::Windows::Forms::TextBox^  SystemBox;

		System::Windows::Forms::Button^  WeaponCreatorButton;
		System::Windows::Forms::Button^  ArmorCreatorButton;
		System::Windows::Forms::Button^  JewelCreatorButton;
		System::Windows::Forms::Button^  MiscItemCreatorButton;
		System::Windows::Forms::Button^  NPCCreatorButton;
		System::Windows::Forms::Button^  VendorCreatorButton;
		System::Windows::Forms::Button^  LootCreatorButton;
		System::Windows::Forms::Button^  QuestCreatorButton;

		System::Windows::Forms::LinkLabel^  ForumLink;
		System::Windows::Forms::LinkLabel^  WebsiteLink;
		System::Windows::Forms::LinkLabel^  CreationPageLink;

		System::Windows::Forms::ComboBox^  CoreSelectionBox;
		System::Windows::Forms::ComboBox^  ItemSettingsIndex;

		System::Windows::Forms::Label^  InputBox1Title;
		System::Windows::Forms::Label^  InputBox2Title;
		System::Windows::Forms::Label^  InputBox3Title;
		System::Windows::Forms::Label^  InputBox4Title;
		System::Windows::Forms::Label^  InputBox5Title;
		System::Windows::Forms::Label^  InputBox6Title;
		System::Windows::Forms::Label^  InputBox7Title;
		System::Windows::Forms::Label^  InputBox8Title;
		System::Windows::Forms::Label^  InputBox9Title;
		System::Windows::Forms::Label^  InputBox10Title;
		System::Windows::Forms::Label^  InputBox11Title;
		System::Windows::Forms::Label^  InputBox12Title;
		System::Windows::Forms::Label^  InputBox13Title;
		System::Windows::Forms::Label^  InputBox14Title;
		System::Windows::Forms::Label^  InputBox15Title;
		System::Windows::Forms::Label^  InputBox16Title;
		System::Windows::Forms::Label^  InputBox17Title;
		System::Windows::Forms::Label^  InputBox18Title;
		System::Windows::Forms::Label^  InputBox19Title;
		System::Windows::Forms::Label^  InputBox20Title;
		System::Windows::Forms::Label^  InputBox22Title;
		System::Windows::Forms::Label^  InputBox21Title;

		System::Windows::Forms::Label^  WarningText;

		System::Windows::Forms::TextBox^  DescriptionBox1;
		System::Windows::Forms::TextBox^  DescriptionBox2;

		System::Windows::Forms::ComboBox^  SelectionIndexBox1;
		System::Windows::Forms::ComboBox^  SelectionIndexBox2;
		System::Windows::Forms::ComboBox^  SelectionIndexBox3;
		System::Windows::Forms::ComboBox^  SelectionIndexBox4;
		System::Windows::Forms::ComboBox^  SelectionIndexBox5;
		System::Windows::Forms::ComboBox^  SelectionIndexBox6;
		System::Windows::Forms::ComboBox^  SelectionIndexBox7;
		System::Windows::Forms::ComboBox^  SelectionIndexBox8;
		System::Windows::Forms::ComboBox^  SelectionIndexBox9;
		System::Windows::Forms::ComboBox^  SelectionIndexBox10;

		System::Windows::Forms::TextBox^  SelectionInputBox1;
		System::Windows::Forms::TextBox^  SelectionInputBox2;
		System::Windows::Forms::TextBox^  SelectionInputBox3;
		System::Windows::Forms::TextBox^  SelectionInputBox4;
		System::Windows::Forms::TextBox^  SelectionInputBox5;
		System::Windows::Forms::TextBox^  SelectionInputBox6;
		System::Windows::Forms::TextBox^  SelectionInputBox7;
		System::Windows::Forms::TextBox^  SelectionInputBox8;
		System::Windows::Forms::TextBox^  SelectionInputBox9;
		System::Windows::Forms::TextBox^  SelectionInputBox10;
		System::Windows::Forms::TextBox^  SelectionInputBox11;
		System::Windows::Forms::TextBox^  SelectionInputBox12;
		System::Windows::Forms::TextBox^  SelectionInputBox13;
		System::Windows::Forms::TextBox^  SelectionInputBox14;
		System::Windows::Forms::TextBox^  SelectionInputBox15;
		System::Windows::Forms::TextBox^  SelectionInputBox16;
		System::Windows::Forms::TextBox^  SelectionInputBox17;
		System::Windows::Forms::TextBox^  SelectionInputBox18;
		System::Windows::Forms::TextBox^  SelectionInputBox19;
		System::Windows::Forms::TextBox^  SelectionInputBox20;

		System::Windows::Forms::Panel^  SelectionPanel;
		System::Windows::Forms::Panel^  MascotPanel;

		System::Windows::Forms::Button^  SaveButton;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->SystemBox = (gcnew System::Windows::Forms::TextBox());
			this->SystemInfoBoxTitle = (gcnew System::Windows::Forms::Label());
			this->WeaponCreatorButton = (gcnew System::Windows::Forms::Button());
			this->ArmorCreatorButton = (gcnew System::Windows::Forms::Button());
			this->JewelCreatorButton = (gcnew System::Windows::Forms::Button());
			this->MiscItemCreatorButton = (gcnew System::Windows::Forms::Button());
			this->NPCCreatorButton = (gcnew System::Windows::Forms::Button());
			this->VendorCreatorButton = (gcnew System::Windows::Forms::Button());
			this->WebsiteLink = (gcnew System::Windows::Forms::LinkLabel());
			this->ForumLink = (gcnew System::Windows::Forms::LinkLabel());
			this->CreationPageLink = (gcnew System::Windows::Forms::LinkLabel());
			this->CreditsInspiration = (gcnew System::Windows::Forms::Label());
			this->CreditsCreatedBy = (gcnew System::Windows::Forms::Label());
			this->SelectionInputBox20 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox19 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox18 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox13 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox14 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox15 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox17 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox16 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox12 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox11 = (gcnew System::Windows::Forms::TextBox());
			this->InputBox10Title = (gcnew System::Windows::Forms::Label());
			this->InputBox9Title = (gcnew System::Windows::Forms::Label());
			this->InputBox8Title = (gcnew System::Windows::Forms::Label());
			this->InputBox7Title = (gcnew System::Windows::Forms::Label());
			this->InputBox6Title = (gcnew System::Windows::Forms::Label());
			this->InputBox5Title = (gcnew System::Windows::Forms::Label());
			this->InputBox4Title = (gcnew System::Windows::Forms::Label());
			this->InputBox3Title = (gcnew System::Windows::Forms::Label());
			this->InputBox2Title = (gcnew System::Windows::Forms::Label());
			this->SelectionInputBox10 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox9 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox8 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox3 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox4 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox5 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox7 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox6 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionInputBox2 = (gcnew System::Windows::Forms::TextBox());
			this->InputBox1Title = (gcnew System::Windows::Forms::Label());
			this->ItemSettingsIndex = (gcnew System::Windows::Forms::ComboBox());
			this->SelectionInputBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->CoreSelectionBox = (gcnew System::Windows::Forms::ComboBox());
			this->CoreTypeTitle = (gcnew System::Windows::Forms::Label());
			this->LootCreatorButton = (gcnew System::Windows::Forms::Button());
			this->SelectionPanel = (gcnew System::Windows::Forms::Panel());
			this->InputBox22Title = (gcnew System::Windows::Forms::Label());
			this->InputBox21Title = (gcnew System::Windows::Forms::Label());
			this->InputBox11Title = (gcnew System::Windows::Forms::Label());
			this->InputBox12Title = (gcnew System::Windows::Forms::Label());
			this->InputBox13Title = (gcnew System::Windows::Forms::Label());
			this->InputBox14Title = (gcnew System::Windows::Forms::Label());
			this->InputBox15Title = (gcnew System::Windows::Forms::Label());
			this->InputBox16Title = (gcnew System::Windows::Forms::Label());
			this->InputBox17Title = (gcnew System::Windows::Forms::Label());
			this->InputBox18Title = (gcnew System::Windows::Forms::Label());
			this->InputBox19Title = (gcnew System::Windows::Forms::Label());
			this->InputBox20Title = (gcnew System::Windows::Forms::Label());
			this->DescriptionBox1 = (gcnew System::Windows::Forms::TextBox());
			this->WarningText = (gcnew System::Windows::Forms::Label());
			this->DescriptionBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SelectionIndexBox8 = (gcnew System::Windows::Forms::ComboBox());
			this->SelectionIndexBox9 = (gcnew System::Windows::Forms::ComboBox());
			this->SelectionIndexBox10 = (gcnew System::Windows::Forms::ComboBox());
			this->SelectionIndexBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->SelectionIndexBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->SelectionIndexBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->SelectionIndexBox5 = (gcnew System::Windows::Forms::ComboBox());
			this->SelectionIndexBox6 = (gcnew System::Windows::Forms::ComboBox());
			this->SelectionIndexBox7 = (gcnew System::Windows::Forms::ComboBox());
			this->SelectionIndexBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->QuestCreatorButton = (gcnew System::Windows::Forms::Button());
			this->MascotPanel = (gcnew System::Windows::Forms::Panel());
			this->SelectionPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// SystemBox
			// 
			this->SystemBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(36)), 
				static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SystemBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->SystemBox->Cursor = System::Windows::Forms::Cursors::Default;
			this->SystemBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(153)), 
				static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SystemBox->Location = System::Drawing::Point(416, 53);
			this->SystemBox->Multiline = true;
			this->SystemBox->Name = L"SystemBox";
			this->SystemBox->ReadOnly = true;
			this->SystemBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->SystemBox->Size = System::Drawing::Size(127, 508);
			this->SystemBox->TabIndex = 2;
			// 
			// SystemInfoBoxTitle
			// 
			this->SystemInfoBoxTitle->AutoSize = true;
			this->SystemInfoBoxTitle->Font = (gcnew System::Drawing::Font(L"Segoe Script", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->SystemInfoBoxTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(186)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->SystemInfoBoxTitle->Location = System::Drawing::Point(416, 19);
			this->SystemInfoBoxTitle->Name = L"SystemInfoBoxTitle";
			this->SystemInfoBoxTitle->Size = System::Drawing::Size(131, 31);
			this->SystemInfoBoxTitle->TabIndex = 3;
			this->SystemInfoBoxTitle->Text = L"System Info";
			// 
			// WeaponCreatorButton
			// 
			this->WeaponCreatorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(186)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->WeaponCreatorButton->Location = System::Drawing::Point(550, 12);
			this->WeaponCreatorButton->Name = L"WeaponCreatorButton";
			this->WeaponCreatorButton->Size = System::Drawing::Size(114, 48);
			this->WeaponCreatorButton->TabIndex = 4;
			this->WeaponCreatorButton->Text = L"Weapon Creator";
			this->WeaponCreatorButton->UseVisualStyleBackColor = false;
			this->WeaponCreatorButton->Click += gcnew System::EventHandler(this, &MainForm::WeaponCreatorButton_Click);
			// 
			// ArmorCreatorButton
			// 
			this->ArmorCreatorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(186)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->ArmorCreatorButton->Location = System::Drawing::Point(550, 66);
			this->ArmorCreatorButton->Name = L"ArmorCreatorButton";
			this->ArmorCreatorButton->Size = System::Drawing::Size(114, 48);
			this->ArmorCreatorButton->TabIndex = 6;
			this->ArmorCreatorButton->Text = L"Armor Creator";
			this->ArmorCreatorButton->UseVisualStyleBackColor = false;
			this->ArmorCreatorButton->Click += gcnew System::EventHandler(this, &MainForm::ArmorCreatorButton_Click);
			// 
			// JewelCreatorButton
			// 
			this->JewelCreatorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(186)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->JewelCreatorButton->Enabled = false;
			this->JewelCreatorButton->Location = System::Drawing::Point(550, 120);
			this->JewelCreatorButton->Name = L"JewelCreatorButton";
			this->JewelCreatorButton->Size = System::Drawing::Size(114, 48);
			this->JewelCreatorButton->TabIndex = 7;
			this->JewelCreatorButton->Text = L"Jewelry Creator";
			this->JewelCreatorButton->UseVisualStyleBackColor = false;
			this->JewelCreatorButton->Click += gcnew System::EventHandler(this, &MainForm::JewelCreatorButton_Click);
			// 
			// MiscItemCreatorButton
			// 
			this->MiscItemCreatorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(186)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->MiscItemCreatorButton->Enabled = false;
			this->MiscItemCreatorButton->Location = System::Drawing::Point(550, 174);
			this->MiscItemCreatorButton->Name = L"MiscItemCreatorButton";
			this->MiscItemCreatorButton->Size = System::Drawing::Size(114, 48);
			this->MiscItemCreatorButton->TabIndex = 8;
			this->MiscItemCreatorButton->Text = L"Misc Item Creator";
			this->MiscItemCreatorButton->UseVisualStyleBackColor = false;
			this->MiscItemCreatorButton->Click += gcnew System::EventHandler(this, &MainForm::MiscItemCreatorButton_Click);
			// 
			// NPCCreatorButton
			// 
			this->NPCCreatorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->NPCCreatorButton->Enabled = false;
			this->NPCCreatorButton->Location = System::Drawing::Point(670, 12);
			this->NPCCreatorButton->Name = L"NPCCreatorButton";
			this->NPCCreatorButton->Size = System::Drawing::Size(114, 48);
			this->NPCCreatorButton->TabIndex = 9;
			this->NPCCreatorButton->Text = L"NPC Creator";
			this->NPCCreatorButton->UseVisualStyleBackColor = false;
			this->NPCCreatorButton->Click += gcnew System::EventHandler(this, &MainForm::NPCCreatorButton_Click);
			// 
			// VendorCreatorButton
			// 
			this->VendorCreatorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(186)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->VendorCreatorButton->Enabled = false;
			this->VendorCreatorButton->Location = System::Drawing::Point(670, 66);
			this->VendorCreatorButton->Name = L"VendorCreatorButton";
			this->VendorCreatorButton->Size = System::Drawing::Size(114, 48);
			this->VendorCreatorButton->TabIndex = 10;
			this->VendorCreatorButton->Text = L"Vendor Creator";
			this->VendorCreatorButton->UseVisualStyleBackColor = false;
			this->VendorCreatorButton->Click += gcnew System::EventHandler(this, &MainForm::VendorCreatorButton_Click);
			// 
			// WebsiteLink
			// 
			this->WebsiteLink->AutoSize = true;
			this->WebsiteLink->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->WebsiteLink->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->WebsiteLink->LinkColor = System::Drawing::Color::Yellow;
			this->WebsiteLink->Location = System::Drawing::Point(550, 424);
			this->WebsiteLink->Name = L"WebsiteLink";
			this->WebsiteLink->Size = System::Drawing::Size(159, 25);
			this->WebsiteLink->TabIndex = 13;
			this->WebsiteLink->TabStop = true;
			this->WebsiteLink->Text = L"WoW-V Website";
			this->WebsiteLink->VisitedLinkColor = System::Drawing::Color::White;
			this->WebsiteLink->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainForm::WebsiteLink_LinkClicked);
			// 
			// ForumLink
			// 
			this->ForumLink->AutoSize = true;
			this->ForumLink->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ForumLink->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->ForumLink->LinkColor = System::Drawing::Color::Yellow;
			this->ForumLink->Location = System::Drawing::Point(550, 449);
			this->ForumLink->Name = L"ForumLink";
			this->ForumLink->Size = System::Drawing::Size(155, 25);
			this->ForumLink->TabIndex = 14;
			this->ForumLink->TabStop = true;
			this->ForumLink->Text = L"WoW-V Forums";
			this->ForumLink->VisitedLinkColor = System::Drawing::Color::White;
			this->ForumLink->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainForm::ForumLink_LinkClicked);
			// 
			// CreationPageLink
			// 
			this->CreationPageLink->AutoSize = true;
			this->CreationPageLink->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->CreationPageLink->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->CreationPageLink->LinkColor = System::Drawing::Color::Yellow;
			this->CreationPageLink->Location = System::Drawing::Point(550, 399);
			this->CreationPageLink->Name = L"CreationPageLink";
			this->CreationPageLink->Size = System::Drawing::Size(213, 25);
			this->CreationPageLink->TabIndex = 15;
			this->CreationPageLink->TabStop = true;
			this->CreationPageLink->Text = L"WoW-V Creation Page";
			this->CreationPageLink->VisitedLinkColor = System::Drawing::Color::White;
			this->CreationPageLink->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainForm::CreationPageLink_LinkClicked);
			// 
			// CreditsInspiration
			// 
			this->CreditsInspiration->AutoSize = true;
			this->CreditsInspiration->Location = System::Drawing::Point(552, 473);
			this->CreditsInspiration->Name = L"CreditsInspiration";
			this->CreditsInspiration->Size = System::Drawing::Size(157, 13);
			this->CreditsInspiration->TabIndex = 16;
			this->CreditsInspiration->Text = L"Design inspired by WoW-V.com";
			// 
			// CreditsCreatedBy
			// 
			this->CreditsCreatedBy->AutoSize = true;
			this->CreditsCreatedBy->Location = System::Drawing::Point(552, 490);
			this->CreditsCreatedBy->Name = L"CreditsCreatedBy";
			this->CreditsCreatedBy->Size = System::Drawing::Size(153, 13);
			this->CreditsCreatedBy->TabIndex = 17;
			this->CreditsCreatedBy->Text = L"Created by Crow@Sandshroud";
			// 
			// SelectionInputBox20
			// 
			this->SelectionInputBox20->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox20->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox20->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox20->Location = System::Drawing::Point(259, 409);
			this->SelectionInputBox20->Name = L"SelectionInputBox20";
			this->SelectionInputBox20->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox20->TabIndex = 56;
			this->SelectionInputBox20->Visible = false;
			// 
			// SelectionInputBox19
			// 
			this->SelectionInputBox19->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox19->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox19->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox19->Location = System::Drawing::Point(259, 369);
			this->SelectionInputBox19->Name = L"SelectionInputBox19";
			this->SelectionInputBox19->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox19->TabIndex = 55;
			this->SelectionInputBox19->Visible = false;
			// 
			// SelectionInputBox18
			// 
			this->SelectionInputBox18->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox18->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox18->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox18->Location = System::Drawing::Point(259, 326);
			this->SelectionInputBox18->Name = L"SelectionInputBox18";
			this->SelectionInputBox18->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox18->TabIndex = 54;
			this->SelectionInputBox18->Visible = false;
			// 
			// SelectionInputBox13
			// 
			this->SelectionInputBox13->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox13->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox13->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox13->Location = System::Drawing::Point(259, 118);
			this->SelectionInputBox13->Name = L"SelectionInputBox13";
			this->SelectionInputBox13->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox13->TabIndex = 53;
			this->SelectionInputBox13->Visible = false;
			// 
			// SelectionInputBox14
			// 
			this->SelectionInputBox14->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox14->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox14->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox14->Location = System::Drawing::Point(259, 162);
			this->SelectionInputBox14->Name = L"SelectionInputBox14";
			this->SelectionInputBox14->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox14->TabIndex = 52;
			this->SelectionInputBox14->Visible = false;
			// 
			// SelectionInputBox15
			// 
			this->SelectionInputBox15->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox15->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox15->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox15->Location = System::Drawing::Point(259, 201);
			this->SelectionInputBox15->Name = L"SelectionInputBox15";
			this->SelectionInputBox15->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox15->TabIndex = 51;
			this->SelectionInputBox15->Visible = false;
			// 
			// SelectionInputBox17
			// 
			this->SelectionInputBox17->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox17->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox17->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox17->Location = System::Drawing::Point(259, 282);
			this->SelectionInputBox17->Name = L"SelectionInputBox17";
			this->SelectionInputBox17->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox17->TabIndex = 50;
			this->SelectionInputBox17->Visible = false;
			// 
			// SelectionInputBox16
			// 
			this->SelectionInputBox16->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox16->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox16->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox16->Location = System::Drawing::Point(259, 241);
			this->SelectionInputBox16->Name = L"SelectionInputBox16";
			this->SelectionInputBox16->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox16->TabIndex = 49;
			this->SelectionInputBox16->Visible = false;
			// 
			// SelectionInputBox12
			// 
			this->SelectionInputBox12->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox12->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox12->Location = System::Drawing::Point(259, 78);
			this->SelectionInputBox12->Name = L"SelectionInputBox12";
			this->SelectionInputBox12->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox12->TabIndex = 48;
			this->SelectionInputBox12->Visible = false;
			// 
			// SelectionInputBox11
			// 
			this->SelectionInputBox11->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox11->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox11->Location = System::Drawing::Point(259, 36);
			this->SelectionInputBox11->Name = L"SelectionInputBox11";
			this->SelectionInputBox11->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox11->TabIndex = 47;
			this->SelectionInputBox11->Visible = false;
			// 
			// InputBox10Title
			// 
			this->InputBox10Title->AutoSize = true;
			this->InputBox10Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox10Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox10Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox10Title->Location = System::Drawing::Point(80, 389);
			this->InputBox10Title->Name = L"InputBox10Title";
			this->InputBox10Title->Size = System::Drawing::Size(82, 17);
			this->InputBox10Title->TabIndex = 46;
			this->InputBox10Title->Text = L"InputBox10";
			this->InputBox10Title->Visible = false;
			// 
			// InputBox9Title
			// 
			this->InputBox9Title->AutoSize = true;
			this->InputBox9Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox9Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox9Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox9Title->Location = System::Drawing::Point(80, 348);
			this->InputBox9Title->Name = L"InputBox9Title";
			this->InputBox9Title->Size = System::Drawing::Size(74, 17);
			this->InputBox9Title->TabIndex = 45;
			this->InputBox9Title->Text = L"InputBox9";
			this->InputBox9Title->Visible = false;
			// 
			// InputBox8Title
			// 
			this->InputBox8Title->AutoSize = true;
			this->InputBox8Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox8Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox8Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox8Title->Location = System::Drawing::Point(80, 306);
			this->InputBox8Title->Name = L"InputBox8Title";
			this->InputBox8Title->Size = System::Drawing::Size(74, 17);
			this->InputBox8Title->TabIndex = 44;
			this->InputBox8Title->Text = L"InputBox8";
			this->InputBox8Title->Visible = false;
			// 
			// InputBox7Title
			// 
			this->InputBox7Title->AutoSize = true;
			this->InputBox7Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox7Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox7Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox7Title->Location = System::Drawing::Point(80, 262);
			this->InputBox7Title->Name = L"InputBox7Title";
			this->InputBox7Title->Size = System::Drawing::Size(74, 17);
			this->InputBox7Title->TabIndex = 43;
			this->InputBox7Title->Text = L"InputBox7";
			this->InputBox7Title->Visible = false;
			// 
			// InputBox6Title
			// 
			this->InputBox6Title->AutoSize = true;
			this->InputBox6Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox6Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox6Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox6Title->Location = System::Drawing::Point(80, 221);
			this->InputBox6Title->Name = L"InputBox6Title";
			this->InputBox6Title->Size = System::Drawing::Size(74, 17);
			this->InputBox6Title->TabIndex = 42;
			this->InputBox6Title->Text = L"InputBox6";
			this->InputBox6Title->Visible = false;
			// 
			// InputBox5Title
			// 
			this->InputBox5Title->AutoSize = true;
			this->InputBox5Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox5Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox5Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox5Title->Location = System::Drawing::Point(80, 183);
			this->InputBox5Title->Name = L"InputBox5Title";
			this->InputBox5Title->Size = System::Drawing::Size(74, 17);
			this->InputBox5Title->TabIndex = 41;
			this->InputBox5Title->Text = L"InputBox5";
			this->InputBox5Title->Visible = false;
			// 
			// InputBox4Title
			// 
			this->InputBox4Title->AutoSize = true;
			this->InputBox4Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox4Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox4Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox4Title->Location = System::Drawing::Point(80, 141);
			this->InputBox4Title->Name = L"InputBox4Title";
			this->InputBox4Title->Size = System::Drawing::Size(74, 17);
			this->InputBox4Title->TabIndex = 40;
			this->InputBox4Title->Text = L"InputBox4";
			this->InputBox4Title->Visible = false;
			// 
			// InputBox3Title
			// 
			this->InputBox3Title->AutoSize = true;
			this->InputBox3Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox3Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox3Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox3Title->Location = System::Drawing::Point(80, 99);
			this->InputBox3Title->Name = L"InputBox3Title";
			this->InputBox3Title->Size = System::Drawing::Size(74, 17);
			this->InputBox3Title->TabIndex = 39;
			this->InputBox3Title->Text = L"InputBox3";
			this->InputBox3Title->Visible = false;
			// 
			// InputBox2Title
			// 
			this->InputBox2Title->AutoSize = true;
			this->InputBox2Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox2Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox2Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox2Title->Location = System::Drawing::Point(80, 58);
			this->InputBox2Title->Name = L"InputBox2Title";
			this->InputBox2Title->Size = System::Drawing::Size(74, 17);
			this->InputBox2Title->TabIndex = 38;
			this->InputBox2Title->Text = L"InputBox2";
			this->InputBox2Title->Visible = false;
			// 
			// SelectionInputBox10
			// 
			this->SelectionInputBox10->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox10->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox10->Location = System::Drawing::Point(187, 409);
			this->SelectionInputBox10->Name = L"SelectionInputBox10";
			this->SelectionInputBox10->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox10->TabIndex = 37;
			this->SelectionInputBox10->Visible = false;
			// 
			// SelectionInputBox9
			// 
			this->SelectionInputBox9->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox9->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox9->Location = System::Drawing::Point(187, 369);
			this->SelectionInputBox9->Name = L"SelectionInputBox9";
			this->SelectionInputBox9->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox9->TabIndex = 36;
			this->SelectionInputBox9->Visible = false;
			// 
			// SelectionInputBox8
			// 
			this->SelectionInputBox8->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox8->Location = System::Drawing::Point(187, 326);
			this->SelectionInputBox8->Name = L"SelectionInputBox8";
			this->SelectionInputBox8->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox8->TabIndex = 35;
			this->SelectionInputBox8->Visible = false;
			// 
			// SelectionInputBox3
			// 
			this->SelectionInputBox3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox3->Location = System::Drawing::Point(187, 118);
			this->SelectionInputBox3->Name = L"SelectionInputBox3";
			this->SelectionInputBox3->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox3->TabIndex = 34;
			this->SelectionInputBox3->Visible = false;
			// 
			// SelectionInputBox4
			// 
			this->SelectionInputBox4->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox4->Location = System::Drawing::Point(187, 162);
			this->SelectionInputBox4->Name = L"SelectionInputBox4";
			this->SelectionInputBox4->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox4->TabIndex = 33;
			this->SelectionInputBox4->Visible = false;
			// 
			// SelectionInputBox5
			// 
			this->SelectionInputBox5->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox5->Location = System::Drawing::Point(187, 201);
			this->SelectionInputBox5->Name = L"SelectionInputBox5";
			this->SelectionInputBox5->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox5->TabIndex = 32;
			this->SelectionInputBox5->Visible = false;
			// 
			// SelectionInputBox7
			// 
			this->SelectionInputBox7->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox7->Location = System::Drawing::Point(187, 282);
			this->SelectionInputBox7->Name = L"SelectionInputBox7";
			this->SelectionInputBox7->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox7->TabIndex = 31;
			this->SelectionInputBox7->Visible = false;
			// 
			// SelectionInputBox6
			// 
			this->SelectionInputBox6->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox6->Location = System::Drawing::Point(187, 241);
			this->SelectionInputBox6->Name = L"SelectionInputBox6";
			this->SelectionInputBox6->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox6->TabIndex = 30;
			this->SelectionInputBox6->Visible = false;
			// 
			// SelectionInputBox2
			// 
			this->SelectionInputBox2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox2->Location = System::Drawing::Point(187, 78);
			this->SelectionInputBox2->Name = L"SelectionInputBox2";
			this->SelectionInputBox2->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox2->TabIndex = 26;
			this->SelectionInputBox2->Visible = false;
			// 
			// InputBox1Title
			// 
			this->InputBox1Title->AutoSize = true;
			this->InputBox1Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox1Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox1Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox1Title->Location = System::Drawing::Point(80, 16);
			this->InputBox1Title->Name = L"InputBox1Title";
			this->InputBox1Title->Size = System::Drawing::Size(74, 17);
			this->InputBox1Title->TabIndex = 24;
			this->InputBox1Title->Text = L"InputBox1";
			this->InputBox1Title->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->InputBox1Title->Visible = false;
			// 
			// ItemSettingsIndex
			// 
			this->ItemSettingsIndex->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(36)), 
				static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->ItemSettingsIndex->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ItemSettingsIndex->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->ItemSettingsIndex->FormattingEnabled = true;
			this->ItemSettingsIndex->Items->AddRange(gcnew cli::array< System::Object^  >(1) {L"Unknown"});
			this->ItemSettingsIndex->Location = System::Drawing::Point(555, 228);
			this->ItemSettingsIndex->Name = L"ItemSettingsIndex";
			this->ItemSettingsIndex->Size = System::Drawing::Size(220, 21);
			this->ItemSettingsIndex->TabIndex = 23;
			this->ItemSettingsIndex->Visible = false;
			this->ItemSettingsIndex->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::ItemSettingsIndex_SelectedIndexChanged);
			// 
			// SelectionInputBox1
			// 
			this->SelectionInputBox1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->SelectionInputBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionInputBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionInputBox1->Location = System::Drawing::Point(187, 36);
			this->SelectionInputBox1->Name = L"SelectionInputBox1";
			this->SelectionInputBox1->Size = System::Drawing::Size(69, 20);
			this->SelectionInputBox1->TabIndex = 0;
			this->SelectionInputBox1->Visible = false;
			// 
			// SaveButton
			// 
			this->SaveButton->Enabled = false;
			this->SaveButton->Location = System::Drawing::Point(663, 510);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(116, 52);
			this->SaveButton->TabIndex = 20;
			this->SaveButton->Text = L"Save";
			this->SaveButton->UseVisualStyleBackColor = true;
			this->SaveButton->Click += gcnew System::EventHandler(this, &MainForm::SaveButton_Click);
			// 
			// CoreSelectionBox
			// 
			this->CoreSelectionBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(36)), 
				static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->CoreSelectionBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->CoreSelectionBox->Enabled = false;
			this->CoreSelectionBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(153)), 
				static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->CoreSelectionBox->FormattingEnabled = true;
			this->CoreSelectionBox->Items->AddRange(gcnew cli::array< System::Object^  >(1) {L"Unknown"});
			this->CoreSelectionBox->Location = System::Drawing::Point(550, 540);
			this->CoreSelectionBox->Name = L"CoreSelectionBox";
			this->CoreSelectionBox->Size = System::Drawing::Size(107, 21);
			this->CoreSelectionBox->TabIndex = 21;
			this->CoreSelectionBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::CoreSelectionBox_SelectedIndexChanged);
			// 
			// CoreTypeTitle
			// 
			this->CoreTypeTitle->AutoSize = true;
			this->CoreTypeTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 14.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->CoreTypeTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->CoreTypeTitle->Location = System::Drawing::Point(550, 512);
			this->CoreTypeTitle->Name = L"CoreTypeTitle";
			this->CoreTypeTitle->Size = System::Drawing::Size(106, 25);
			this->CoreTypeTitle->TabIndex = 22;
			this->CoreTypeTitle->Text = L"Core Type";
			// 
			// LootCreatorButton
			// 
			this->LootCreatorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->LootCreatorButton->Enabled = false;
			this->LootCreatorButton->Location = System::Drawing::Point(670, 120);
			this->LootCreatorButton->Name = L"LootCreatorButton";
			this->LootCreatorButton->Size = System::Drawing::Size(114, 48);
			this->LootCreatorButton->TabIndex = 23;
			this->LootCreatorButton->Text = L"Loot Creator";
			this->LootCreatorButton->UseVisualStyleBackColor = false;
			this->LootCreatorButton->Click += gcnew System::EventHandler(this, &MainForm::LootCreatorButton_Click);
			// 
			// SelectionPanel
			// 
			this->SelectionPanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->SelectionPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->SelectionPanel->Controls->Add(this->WarningText);
			this->SelectionPanel->Controls->Add(this->InputBox22Title);
			this->SelectionPanel->Controls->Add(this->InputBox21Title);
			this->SelectionPanel->Controls->Add(this->InputBox11Title);
			this->SelectionPanel->Controls->Add(this->InputBox12Title);
			this->SelectionPanel->Controls->Add(this->InputBox13Title);
			this->SelectionPanel->Controls->Add(this->InputBox14Title);
			this->SelectionPanel->Controls->Add(this->InputBox15Title);
			this->SelectionPanel->Controls->Add(this->InputBox16Title);
			this->SelectionPanel->Controls->Add(this->InputBox17Title);
			this->SelectionPanel->Controls->Add(this->InputBox18Title);
			this->SelectionPanel->Controls->Add(this->InputBox19Title);
			this->SelectionPanel->Controls->Add(this->InputBox20Title);
			this->SelectionPanel->Controls->Add(this->DescriptionBox1);
			this->SelectionPanel->Controls->Add(this->DescriptionBox2);
			this->SelectionPanel->Controls->Add(this->SelectionIndexBox8);
			this->SelectionPanel->Controls->Add(this->SelectionIndexBox9);
			this->SelectionPanel->Controls->Add(this->SelectionIndexBox10);
			this->SelectionPanel->Controls->Add(this->SelectionIndexBox2);
			this->SelectionPanel->Controls->Add(this->SelectionIndexBox3);
			this->SelectionPanel->Controls->Add(this->SelectionIndexBox4);
			this->SelectionPanel->Controls->Add(this->SelectionIndexBox5);
			this->SelectionPanel->Controls->Add(this->SelectionIndexBox6);
			this->SelectionPanel->Controls->Add(this->SelectionIndexBox7);
			this->SelectionPanel->Controls->Add(this->SelectionIndexBox1);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox20);
			this->SelectionPanel->Controls->Add(this->InputBox1Title);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox19);
			this->SelectionPanel->Controls->Add(this->InputBox2Title);
			this->SelectionPanel->Controls->Add(this->InputBox3Title);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox18);
			this->SelectionPanel->Controls->Add(this->InputBox4Title);
			this->SelectionPanel->Controls->Add(this->InputBox5Title);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox13);
			this->SelectionPanel->Controls->Add(this->InputBox6Title);
			this->SelectionPanel->Controls->Add(this->InputBox7Title);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox14);
			this->SelectionPanel->Controls->Add(this->InputBox8Title);
			this->SelectionPanel->Controls->Add(this->InputBox9Title);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox15);
			this->SelectionPanel->Controls->Add(this->InputBox10Title);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox2);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox17);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox6);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox7);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox16);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox5);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox4);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox12);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox1);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox3);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox11);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox8);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox9);
			this->SelectionPanel->Controls->Add(this->SelectionInputBox10);
			this->SelectionPanel->Location = System::Drawing::Point(12, 12);
			this->SelectionPanel->Name = L"SelectionPanel";
			this->SelectionPanel->Size = System::Drawing::Size(398, 549);
			this->SelectionPanel->TabIndex = 20;
			// 
			// InputBox22Title
			// 
			this->InputBox22Title->AutoSize = true;
			this->InputBox22Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox22Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox22Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox22Title->Location = System::Drawing::Point(12, 492);
			this->InputBox22Title->Name = L"InputBox22Title";
			this->InputBox22Title->Size = System::Drawing::Size(82, 17);
			this->InputBox22Title->TabIndex = 81;
			this->InputBox22Title->Text = L"InputBox22";
			this->InputBox22Title->Visible = false;
			// 
			// InputBox21Title
			// 
			this->InputBox21Title->AutoSize = true;
			this->InputBox21Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox21Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox21Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox21Title->Location = System::Drawing::Point(12, 435);
			this->InputBox21Title->Name = L"InputBox21Title";
			this->InputBox21Title->Size = System::Drawing::Size(82, 17);
			this->InputBox21Title->TabIndex = 80;
			this->InputBox21Title->Text = L"InputBox21";
			this->InputBox21Title->Visible = false;
			// 
			// InputBox11Title
			// 
			this->InputBox11Title->AutoSize = true;
			this->InputBox11Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox11Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox11Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox11Title->Location = System::Drawing::Point(215, 16);
			this->InputBox11Title->Name = L"InputBox11Title";
			this->InputBox11Title->Size = System::Drawing::Size(82, 17);
			this->InputBox11Title->TabIndex = 70;
			this->InputBox11Title->Text = L"InputBox11";
			this->InputBox11Title->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->InputBox11Title->Visible = false;
			// 
			// InputBox12Title
			// 
			this->InputBox12Title->AutoSize = true;
			this->InputBox12Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox12Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox12Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox12Title->Location = System::Drawing::Point(215, 58);
			this->InputBox12Title->Name = L"InputBox12Title";
			this->InputBox12Title->Size = System::Drawing::Size(82, 17);
			this->InputBox12Title->TabIndex = 71;
			this->InputBox12Title->Text = L"InputBox12";
			this->InputBox12Title->Visible = false;
			// 
			// InputBox13Title
			// 
			this->InputBox13Title->AutoSize = true;
			this->InputBox13Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox13Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox13Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox13Title->Location = System::Drawing::Point(215, 99);
			this->InputBox13Title->Name = L"InputBox13Title";
			this->InputBox13Title->Size = System::Drawing::Size(82, 17);
			this->InputBox13Title->TabIndex = 72;
			this->InputBox13Title->Text = L"InputBox13";
			this->InputBox13Title->Visible = false;
			// 
			// InputBox14Title
			// 
			this->InputBox14Title->AutoSize = true;
			this->InputBox14Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox14Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox14Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox14Title->Location = System::Drawing::Point(215, 141);
			this->InputBox14Title->Name = L"InputBox14Title";
			this->InputBox14Title->Size = System::Drawing::Size(82, 17);
			this->InputBox14Title->TabIndex = 73;
			this->InputBox14Title->Text = L"InputBox14";
			this->InputBox14Title->Visible = false;
			// 
			// InputBox15Title
			// 
			this->InputBox15Title->AutoSize = true;
			this->InputBox15Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox15Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox15Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox15Title->Location = System::Drawing::Point(215, 183);
			this->InputBox15Title->Name = L"InputBox15Title";
			this->InputBox15Title->Size = System::Drawing::Size(82, 17);
			this->InputBox15Title->TabIndex = 74;
			this->InputBox15Title->Text = L"InputBox15";
			this->InputBox15Title->Visible = false;
			// 
			// InputBox16Title
			// 
			this->InputBox16Title->AutoSize = true;
			this->InputBox16Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox16Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox16Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox16Title->Location = System::Drawing::Point(215, 221);
			this->InputBox16Title->Name = L"InputBox16Title";
			this->InputBox16Title->Size = System::Drawing::Size(82, 17);
			this->InputBox16Title->TabIndex = 75;
			this->InputBox16Title->Text = L"InputBox16";
			this->InputBox16Title->Visible = false;
			// 
			// InputBox17Title
			// 
			this->InputBox17Title->AutoSize = true;
			this->InputBox17Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox17Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox17Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox17Title->Location = System::Drawing::Point(215, 262);
			this->InputBox17Title->Name = L"InputBox17Title";
			this->InputBox17Title->Size = System::Drawing::Size(82, 17);
			this->InputBox17Title->TabIndex = 76;
			this->InputBox17Title->Text = L"InputBox17";
			this->InputBox17Title->Visible = false;
			// 
			// InputBox18Title
			// 
			this->InputBox18Title->AutoSize = true;
			this->InputBox18Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox18Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox18Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox18Title->Location = System::Drawing::Point(215, 306);
			this->InputBox18Title->Name = L"InputBox18Title";
			this->InputBox18Title->Size = System::Drawing::Size(82, 17);
			this->InputBox18Title->TabIndex = 77;
			this->InputBox18Title->Text = L"InputBox18";
			this->InputBox18Title->Visible = false;
			// 
			// InputBox19Title
			// 
			this->InputBox19Title->AutoSize = true;
			this->InputBox19Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox19Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox19Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox19Title->Location = System::Drawing::Point(215, 348);
			this->InputBox19Title->Name = L"InputBox19Title";
			this->InputBox19Title->Size = System::Drawing::Size(82, 17);
			this->InputBox19Title->TabIndex = 78;
			this->InputBox19Title->Text = L"InputBox19";
			this->InputBox19Title->Visible = false;
			// 
			// InputBox20Title
			// 
			this->InputBox20Title->AutoSize = true;
			this->InputBox20Title->BackColor = System::Drawing::Color::Transparent;
			this->InputBox20Title->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->InputBox20Title->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(186)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->InputBox20Title->Location = System::Drawing::Point(215, 389);
			this->InputBox20Title->Name = L"InputBox20Title";
			this->InputBox20Title->Size = System::Drawing::Size(82, 17);
			this->InputBox20Title->TabIndex = 79;
			this->InputBox20Title->Text = L"InputBox20";
			this->InputBox20Title->Visible = false;
			// 
			// DescriptionBox1
			// 
			this->DescriptionBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(36)), 
				static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->DescriptionBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(153)), 
				static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->DescriptionBox1->Location = System::Drawing::Point(100, 435);
			this->DescriptionBox1->Multiline = true;
			this->DescriptionBox1->Name = L"DescriptionBox1";
			this->DescriptionBox1->Size = System::Drawing::Size(283, 50);
			this->DescriptionBox1->TabIndex = 69;
			this->DescriptionBox1->Visible = false;
			// 
			// WarningText
			// 
			this->WarningText->AutoSize = true;
			this->WarningText->BackColor = System::Drawing::Color::Transparent;
			this->WarningText->Font = (gcnew System::Drawing::Font(L"Segoe UI Symbol", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->WarningText->Location = System::Drawing::Point(58, 0);
			this->WarningText->Name = L"WarningText";
			this->WarningText->Size = System::Drawing::Size(264, 21);
			this->WarningText->TabIndex = 68;
			this->WarningText->Text = L"Remember to use \\\' instead of \'!";
			this->WarningText->Visible = false;
			// 
			// DescriptionBox2
			// 
			this->DescriptionBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), static_cast<System::Int32>(static_cast<System::Byte>(36)), 
				static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->DescriptionBox2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), static_cast<System::Int32>(static_cast<System::Byte>(153)), 
				static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->DescriptionBox2->Location = System::Drawing::Point(100, 492);
			this->DescriptionBox2->Multiline = true;
			this->DescriptionBox2->Name = L"DescriptionBox2";
			this->DescriptionBox2->Size = System::Drawing::Size(283, 50);
			this->DescriptionBox2->TabIndex = 67;
			this->DescriptionBox2->Visible = false;
			// 
			// SelectionIndexBox8
			// 
			this->SelectionIndexBox8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionIndexBox8->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SelectionIndexBox8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionIndexBox8->FormattingEnabled = true;
			this->SelectionIndexBox8->Location = System::Drawing::Point(62, 327);
			this->SelectionIndexBox8->Name = L"SelectionIndexBox8";
			this->SelectionIndexBox8->Size = System::Drawing::Size(120, 21);
			this->SelectionIndexBox8->TabIndex = 66;
			this->SelectionIndexBox8->Visible = false;
			// 
			// SelectionIndexBox9
			// 
			this->SelectionIndexBox9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionIndexBox9->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SelectionIndexBox9->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionIndexBox9->FormattingEnabled = true;
			this->SelectionIndexBox9->Location = System::Drawing::Point(62, 370);
			this->SelectionIndexBox9->Name = L"SelectionIndexBox9";
			this->SelectionIndexBox9->Size = System::Drawing::Size(120, 21);
			this->SelectionIndexBox9->TabIndex = 65;
			this->SelectionIndexBox9->Visible = false;
			// 
			// SelectionIndexBox10
			// 
			this->SelectionIndexBox10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionIndexBox10->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SelectionIndexBox10->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionIndexBox10->FormattingEnabled = true;
			this->SelectionIndexBox10->Location = System::Drawing::Point(62, 409);
			this->SelectionIndexBox10->Name = L"SelectionIndexBox10";
			this->SelectionIndexBox10->Size = System::Drawing::Size(120, 21);
			this->SelectionIndexBox10->TabIndex = 64;
			this->SelectionIndexBox10->Visible = false;
			// 
			// SelectionIndexBox2
			// 
			this->SelectionIndexBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionIndexBox2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SelectionIndexBox2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionIndexBox2->FormattingEnabled = true;
			this->SelectionIndexBox2->Location = System::Drawing::Point(62, 78);
			this->SelectionIndexBox2->Name = L"SelectionIndexBox2";
			this->SelectionIndexBox2->Size = System::Drawing::Size(120, 21);
			this->SelectionIndexBox2->TabIndex = 63;
			this->SelectionIndexBox2->Visible = false;
			// 
			// SelectionIndexBox3
			// 
			this->SelectionIndexBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionIndexBox3->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SelectionIndexBox3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionIndexBox3->FormattingEnabled = true;
			this->SelectionIndexBox3->Location = System::Drawing::Point(62, 119);
			this->SelectionIndexBox3->Name = L"SelectionIndexBox3";
			this->SelectionIndexBox3->Size = System::Drawing::Size(120, 21);
			this->SelectionIndexBox3->TabIndex = 62;
			this->SelectionIndexBox3->Visible = false;
			// 
			// SelectionIndexBox4
			// 
			this->SelectionIndexBox4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionIndexBox4->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SelectionIndexBox4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionIndexBox4->FormattingEnabled = true;
			this->SelectionIndexBox4->Location = System::Drawing::Point(62, 163);
			this->SelectionIndexBox4->Name = L"SelectionIndexBox4";
			this->SelectionIndexBox4->Size = System::Drawing::Size(120, 21);
			this->SelectionIndexBox4->TabIndex = 61;
			this->SelectionIndexBox4->Visible = false;
			// 
			// SelectionIndexBox5
			// 
			this->SelectionIndexBox5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionIndexBox5->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SelectionIndexBox5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionIndexBox5->FormattingEnabled = true;
			this->SelectionIndexBox5->Location = System::Drawing::Point(62, 202);
			this->SelectionIndexBox5->Name = L"SelectionIndexBox5";
			this->SelectionIndexBox5->Size = System::Drawing::Size(120, 21);
			this->SelectionIndexBox5->TabIndex = 60;
			this->SelectionIndexBox5->Visible = false;
			// 
			// SelectionIndexBox6
			// 
			this->SelectionIndexBox6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionIndexBox6->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SelectionIndexBox6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionIndexBox6->FormattingEnabled = true;
			this->SelectionIndexBox6->Location = System::Drawing::Point(62, 242);
			this->SelectionIndexBox6->Name = L"SelectionIndexBox6";
			this->SelectionIndexBox6->Size = System::Drawing::Size(120, 21);
			this->SelectionIndexBox6->TabIndex = 59;
			this->SelectionIndexBox6->Visible = false;
			// 
			// SelectionIndexBox7
			// 
			this->SelectionIndexBox7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionIndexBox7->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SelectionIndexBox7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionIndexBox7->FormattingEnabled = true;
			this->SelectionIndexBox7->Location = System::Drawing::Point(62, 283);
			this->SelectionIndexBox7->Name = L"SelectionIndexBox7";
			this->SelectionIndexBox7->Size = System::Drawing::Size(120, 21);
			this->SelectionIndexBox7->TabIndex = 58;
			this->SelectionIndexBox7->Visible = false;
			// 
			// SelectionIndexBox1
			// 
			this->SelectionIndexBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(2)), 
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->SelectionIndexBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SelectionIndexBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(75)), 
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			this->SelectionIndexBox1->FormattingEnabled = true;
			this->SelectionIndexBox1->Location = System::Drawing::Point(62, 37);
			this->SelectionIndexBox1->Name = L"SelectionIndexBox1";
			this->SelectionIndexBox1->Size = System::Drawing::Size(120, 21);
			this->SelectionIndexBox1->TabIndex = 57;
			this->SelectionIndexBox1->Visible = false;
			// 
			// QuestCreatorButton
			// 
			this->QuestCreatorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(186)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->QuestCreatorButton->Enabled = false;
			this->QuestCreatorButton->Location = System::Drawing::Point(670, 174);
			this->QuestCreatorButton->Name = L"QuestCreatorButton";
			this->QuestCreatorButton->Size = System::Drawing::Size(114, 48);
			this->QuestCreatorButton->TabIndex = 24;
			this->QuestCreatorButton->Text = L"Quest Creator";
			this->QuestCreatorButton->UseVisualStyleBackColor = false;
			// 
			// MascotPanel
			// 
			this->MascotPanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"MascotPanel.BackgroundImage")));
			this->MascotPanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->MascotPanel->Location = System::Drawing::Point(539, 263);
			this->MascotPanel->Name = L"MascotPanel";
			this->MascotPanel->Size = System::Drawing::Size(256, 136);
			this->MascotPanel->TabIndex = 25;
			// 
			// MainForm
			// 
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)), static_cast<System::Int32>(static_cast<System::Byte>(101)), 
				static_cast<System::Int32>(static_cast<System::Byte>(129)));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ClientSize = System::Drawing::Size(784, 562);
			this->Controls->Add(this->QuestCreatorButton);
			this->Controls->Add(this->LootCreatorButton);
			this->Controls->Add(this->CoreTypeTitle);
			this->Controls->Add(this->CoreSelectionBox);
			this->Controls->Add(this->SaveButton);
			this->Controls->Add(this->CreditsCreatedBy);
			this->Controls->Add(this->CreditsInspiration);
			this->Controls->Add(this->CreationPageLink);
			this->Controls->Add(this->ForumLink);
			this->Controls->Add(this->WebsiteLink);
			this->Controls->Add(this->VendorCreatorButton);
			this->Controls->Add(this->NPCCreatorButton);
			this->Controls->Add(this->MiscItemCreatorButton);
			this->Controls->Add(this->JewelCreatorButton);
			this->Controls->Add(this->ArmorCreatorButton);
			this->Controls->Add(this->ItemSettingsIndex);
			this->Controls->Add(this->WeaponCreatorButton);
			this->Controls->Add(this->SystemInfoBoxTitle);
			this->Controls->Add(this->SystemBox);
			this->Controls->Add(this->SelectionPanel);
			this->Controls->Add(this->MascotPanel);
			this->DoubleBuffered = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(800, 600);
			this->MinimumSize = System::Drawing::Size(800, 600);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"WoW-V Creator";
			this->SelectionPanel->ResumeLayout(false);
			this->SelectionPanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		System::Void WebsiteLink_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e)
		{
			System::Diagnostics::Process::Start( gcnew String(L"http://wow-v.com/") );
		}

		System::Void ForumLink_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e)
		{
			System::Diagnostics::Process::Start( gcnew String(L"http://wow-v.com/forums/") );
		}

		System::Void CreationPageLink_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e)
		{
			System::Diagnostics::Process::Start( gcnew String(L"http://wow-v.com/create.php") );
		}

		System::Void SaveButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void CoreSelectionBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);

		// Creator buttons
		System::Void WeaponCreatorButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void ArmorCreatorButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void JewelCreatorButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void MiscItemCreatorButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void VendorCreatorButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void NPCCreatorButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void LootCreatorButton_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void ItemSettingsIndex_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	};
}
