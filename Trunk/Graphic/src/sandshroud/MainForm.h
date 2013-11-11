#pragma once

using namespace std;

extern set<std::string> LogSet;

namespace sandshroud {

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
	public:
		MainForm(void)
		{
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
	public:
		System::Windows::Forms::TextBox^  Console;

		void WriteToConsole()
		{
			set<std::string>::iterator itr = LogSet.begin();
			for(; itr != LogSet.end(); itr++)
				Console->Text += (gcnew System::String((*itr).c_str()));
			LogSet.clear();
			Console->Update();
		}

		void CallWriteToConsole()
		{
			if(!LogSet.size())
				return;

			MethodInvoker^ action = gcnew MethodInvoker(this, &MainForm::WriteToConsole);
			Console->BeginInvoke(action);
		}

		void WriteToConsole(System::String^ str)
		{
			Console->Text += str;
			Console->Update();
		}
	protected:

	protected:

	protected:

	protected:

	private:
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
			this->Console = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// Console
			// 
			this->Console->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Console->ForeColor = System::Drawing::Color::Ivory;
			this->Console->Location = System::Drawing::Point(391, 12);
			this->Console->Multiline = true;
			this->Console->Name = L"Console";
			this->Console->ReadOnly = true;
			this->Console->Size = System::Drawing::Size(381, 538);
			this->Console->TabIndex = 1;

			// 
			// MainForm
			// 
			this->ClientSize = System::Drawing::Size(784, 562);
			this->Controls->Add(this->Console);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
	};
}
