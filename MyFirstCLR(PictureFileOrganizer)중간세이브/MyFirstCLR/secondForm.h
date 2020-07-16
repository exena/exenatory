#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <sys/types.h>
#include<io.h>
#include<errno.h>
#include<stdlib.h>//exit()

#include <atlstr.h>
#using <mscorlib.dll>
using namespace System::Runtime::InteropServices;
#pragma once

#define MAX_FILEPATH_LENGTH 500


namespace MyFirstCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for secondForm
	/// </summary>
	public ref class secondForm : public System::Windows::Forms::Form
	{
	public:


		int copy(wchar_t* src, wchar_t* out)
		{
			//pFrom, pTo need double null at the end.
			const wchar_t *const sourceFile = src;
			const wchar_t *const outputFolder = out;

			SHFILEOPSTRUCTW fileOperation;
			memset(&fileOperation, 0, sizeof(SHFILEOPSTRUCTW));

			fileOperation.wFunc = FO_COPY;
			fileOperation.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOF_FILESONLY;
			fileOperation.pFrom = sourceFile;
			fileOperation.pTo = outputFolder;

			int result = SHFileOperationW(&fileOperation);
			if (result != 0)
			{
				printf("SHFileOperation Failure: Error%u\n", result);
				return 1;
			}

			memset(&fileOperation, 0, sizeof(SHFILEOPSTRUCTW));

			printf("Transfer complete\n");
			return 0;
		}
		secondForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		secondForm(System::String^ filedirec)
		{
			InitializeComponent();
			folderpath = filedirec;//!!!!!! get folderpath from MyForm.h !!!!!!!!!
		}
		void MarshalString(String ^ s, std::string& os) {
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		void MarshalString(String ^ s, std::wstring& os) {
			using namespace Runtime::InteropServices;
			const wchar_t* chars =
				(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~secondForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::String^ folderpath;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1_arrival;


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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1_arrival = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(19, 98);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(170, 22);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &secondForm::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(47, 63);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(195, 17);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Please enter the arrival folder";
			this->label1->Click += gcnew System::EventHandler(this, &secondForm::label1_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(107, 161);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"OK";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &secondForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(195, 97);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Search";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &secondForm::button2_Click);
			// 
			// folderBrowserDialog1_arrival
			// 
			this->folderBrowserDialog1_arrival->HelpRequest += gcnew System::EventHandler(this, &secondForm::folderBrowserDialog1_arrival_HelpRequest);
			// 
			// secondForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"secondForm";
			this->Text = L"secondForm";
			this->Load += gcnew System::EventHandler(this, &secondForm::secondForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		struct _wfinddatai64_t c_file;
		intptr_t hFile;
		wchar_t pathfirst[MAX_FILEPATH_LENGTH] = L"";
		CStringW str2(folderpath);
		wcscpy(pathfirst, str2);






		wcscat_s(pathfirst, wcslen(pathfirst) + wcslen(L"\\*.*") + 1, L"\\*.*");
		wchar_t outpath[MAX_FILEPATH_LENGTH] = L"";
		CStringW str3(textBox1->Text);
		wcscpy(outpath, str3);

		if ((hFile = _wfindfirsti64(pathfirst, &c_file)) == -1L) {
			switch (errno) {
			case ENOENT:
				break;
			case EINVAL:
				exit(1); break;
			case ENOMEM:
				exit(1); break;
			default:
				exit(1); break;
			}
		}
		else {
			int hundredcounter = 0;
			int counter = 0;
			wchar_t outpathfinal[MAX_FILEPATH_LENGTH] = L"";
			do {
				wchar_t pathfolder[MAX_FILEPATH_LENGTH] = L"";
				wcscpy(pathfolder, str2);
				wcscat_s(pathfolder, wcslen(pathfolder) + wcslen(L"\\") + 1, L"\\");
				wcscat_s(pathfolder, wcslen(pathfolder) + wcslen(c_file.name) + 1, c_file.name);
				wcscat_s(pathfolder, wcslen(pathfolder) + wcslen(L"\0\0") + 1, L"\0\0");
				if (wcscmp(c_file.name, L".") != 0 && wcscmp(c_file.name, L"..") != 0) {
					if (counter == 0) {
						wcscpy_s(outpathfinal, wcslen(outpath) + 1, outpath);
						wcscat_s(outpathfinal, wcslen(outpathfinal) + wcslen(L"\\") + 1, L"\\");
						wchar_t dum[5] = L"";
						swprintf_s(dum, L"%d", hundredcounter);
						wcscat_s(outpathfinal, wcslen(outpathfinal) + wcslen(dum) + 1, dum);
						wcscat_s(outpathfinal, wcslen(outpathfinal) + wcslen(L"\0\0") + 1, L"\0\0");
						CreateDirectoryW(outpathfinal, NULL);
					}
					copy(pathfolder, outpathfinal);
					if (copy(pathfolder, outpathfinal) == 0) {
						counter++;
						if (counter == 100) {
							counter = 0;
							hundredcounter++;
						}
					}
				}
			} while (_wfindnexti64(hFile, &c_file) == 0);
			_findclose(hFile); // return memory used for _findfirsti64(), _findnexti64()
		}
		MessageBox::Show("Transimission is done", "Message");
		Application::Exit();
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void secondForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		folderBrowserDialog1_arrival->Description = "Please Choose a Folder";
		if (folderBrowserDialog1_arrival->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			textBox1->Text = folderBrowserDialog1_arrival->SelectedPath;
		}
	}
	private: System::Void folderBrowserDialog1_arrival_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}