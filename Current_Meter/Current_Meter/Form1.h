/******************************************************************************/
/* 							 Include files										   */
/******************************************************************************/
/* Standard C libraries */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cstring>
/* OS specific libraries */
#ifdef _WIN32
#include<windows.h>
#endif

#include "stdafx.h"
/* Include D2XX header*/
#include "ftd2xx.h"

/* Include libMPSSE header */
#include "libMPSSE_spi.h"

#include <iostream>

using namespace std;
using namespace System;

#define false 0
#define true 1

#define TX_RX_SIZE 4096
#define MAX_BUF_SIZE TX_RX_SIZE*24
#define SPLITS 2
#define USB_BUF_SIZE 16384

#define NO_OF_LOOPS 20

#pragma once

	bool ReadSuccess;
	bool LoggingEnabled;
	bool SPI_Device_Found;
	//Dim QueueTimeOut As Byte

    int GraphIndex;
	int GraphInputIndex;
	int GraphInputPointer;

	int Y;
	int X;
	bool DeviceInit = false;
	bool ChartToZero= true;
	bool RepaintChart = true;
	bool UserInputFlag = false;

	double voltage;
	int current;
	int result16;
	int timetorun;
	int usertimeval;
	FILE *F1,*F2;
	int sizeoffset = 0;
	int scroll_by_num = 0;
	long int filesz;

	static	FT_HANDLE ftHandle; // Handle of the FTDI device
	static  FT_STATUS ftStatus; // Result of each D2XX call
	/*
	public ref class Globals {
    public:

		//static int AGlobalInteger;
	};*/

namespace Current_Meter {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	
	internal: System::Windows::Forms::GroupBox^  Chart;
	internal: System::Windows::Forms::Label^  Label31;
	internal: System::Windows::Forms::CheckBox^  CheckBox1;
	internal: System::Windows::Forms::Label^  Label30;
	internal: System::Windows::Forms::Label^  Label29;
	internal: System::Windows::Forms::Label^  Label28;
	internal: System::Windows::Forms::Label^  Label27;
	internal: System::Windows::Forms::Label^  Label26;
	internal: System::Windows::Forms::Label^  Label7;
	internal: System::Windows::Forms::Label^  Label6;
	internal: System::Windows::Forms::Panel^  Panel1;

	internal: System::Windows::Forms::Label^  Label24;




	internal: System::Windows::Forms::Label^  Label12;
	internal: System::Windows::Forms::Label^  Label13;
	internal: System::Windows::Forms::Label^  Label14;
	internal: System::Windows::Forms::Label^  Label4;
	internal: System::Windows::Forms::Label^  Label5;
	internal: System::Windows::Forms::GroupBox^  GroupBox2;
	internal: System::Windows::Forms::Label^  label9;
	internal: System::Windows::Forms::Label^  label8;
	internal: System::Windows::Forms::Label^  label10;
	internal: System::Windows::Forms::Label^  label11;
	internal: System::Windows::Forms::Label^  label16;
	internal: System::Windows::Forms::Label^  label15;
	internal: System::Windows::Forms::Label^  Label1;
	internal: System::Windows::Forms::TextBox^  TextBox1;
	internal: System::Windows::Forms::GroupBox^  GroupBox7;
	internal: System::Windows::Forms::Label^  Label35;
	internal: System::Windows::Forms::GroupBox^  GroupBox1;
	internal: System::Windows::Forms::TextBox^  TextBox3;
	internal: System::Windows::Forms::Label^  Label3;
	internal: System::Windows::Forms::TextBox^  TextBox5;
	internal: System::Windows::Forms::Label^  Label25;
	internal: System::Windows::Forms::TextBox^  TextBox2;
	internal: System::Windows::Forms::Label^  Label2;
	internal: System::Windows::Forms::Button^  Button_Exit;
	internal: System::Windows::Forms::Button^  Button_Init;

	internal: System::Windows::Forms::Button^  Button_Start;
	internal: System::Windows::Forms::Button^  Button_Export;
	internal: System::Windows::Forms::Label^  Label32;
	internal: System::Windows::Forms::PictureBox^  PictureBox1;
	internal: System::Windows::Forms::Label^  Label34;
	internal: System::Windows::Forms::TextBox^  textBox4;
	internal: System::Windows::Forms::Label^  label17;
	internal: System::Windows::Forms::CheckBox^  checkBox2;
	internal: System::ComponentModel::IContainer^  components;
	internal: System::Windows::Forms::Label^  label18;



	internal: System::Windows::Forms::TextBox^  TextBox6;

private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
   static System::Windows::Forms::Timer^ myTimer = gcnew System::Windows::Forms::Timer;
   static int alarmCounter = 1;
	private: System::Windows::Forms::HScrollBar^  hScrollBar1;
	private: System::Windows::Forms::Label^  label19;




	private: System::Windows::Forms::TextBox^  TextBox7;

	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::TextBox^  TextBox10;
	private: System::Windows::Forms::TextBox^  TextBox9;


	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::Label^  label36;
	private: System::Windows::Forms::Label^  label37;
private: System::Windows::Forms::TextBox^  TextBox11;

private: System::Windows::Forms::TextBox^  TextBox12;

private: System::Windows::Forms::TextBox^  TextBox13;

private: System::Windows::Forms::Label^  label38;
private: System::Windows::Forms::Label^  label39;
private: System::Windows::Forms::Label^  label40;
private: System::Windows::Forms::Label^  label41;

			 static bool exitFlag = false;

   // This is the method to run when the timer is raised. 
   static void TimerEventProcessor( Object^ /*myObject*/, EventArgs^ /*myEventArgs*/ )
   {
      myTimer->Stop();

      // Displays a message box asking whether to continue running the timer. 
      if ( MessageBox::Show( "Continue running?", String::Format( "Count is: {0}", alarmCounter ), MessageBoxButtons::YesNo ) == System::Windows::Forms::DialogResult::Yes )
      {
         // Restarts the timer and increments the counter.
         alarmCounter += 1;
         myTimer->Enabled = true;
		 timetorun = timetorun + usertimeval*1000;
      }
      else
      {

         // Stops the timer.
         exitFlag = true;
      }
   }


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->Chart = (gcnew System::Windows::Forms::GroupBox());
			this->TextBox9 = (gcnew System::Windows::Forms::TextBox());
			this->TextBox10 = (gcnew System::Windows::Forms::TextBox());
			this->TextBox11 = (gcnew System::Windows::Forms::TextBox());
			this->TextBox12 = (gcnew System::Windows::Forms::TextBox());
			this->TextBox13 = (gcnew System::Windows::Forms::TextBox());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->TextBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->hScrollBar1 = (gcnew System::Windows::Forms::HScrollBar());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->Label31 = (gcnew System::Windows::Forms::Label());
			this->Label30 = (gcnew System::Windows::Forms::Label());
			this->Label29 = (gcnew System::Windows::Forms::Label());
			this->CheckBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->Label28 = (gcnew System::Windows::Forms::Label());
			this->Label27 = (gcnew System::Windows::Forms::Label());
			this->Label26 = (gcnew System::Windows::Forms::Label());
			this->Label7 = (gcnew System::Windows::Forms::Label());
			this->Label6 = (gcnew System::Windows::Forms::Label());
			this->Panel1 = (gcnew System::Windows::Forms::Panel());
			this->Label24 = (gcnew System::Windows::Forms::Label());
			this->Label12 = (gcnew System::Windows::Forms::Label());
			this->Label13 = (gcnew System::Windows::Forms::Label());
			this->Label14 = (gcnew System::Windows::Forms::Label());
			this->Label4 = (gcnew System::Windows::Forms::Label());
			this->Label5 = (gcnew System::Windows::Forms::Label());
			this->GroupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->Label1 = (gcnew System::Windows::Forms::Label());
			this->TextBox1 = (gcnew System::Windows::Forms::TextBox());
			this->GroupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->Label35 = (gcnew System::Windows::Forms::Label());
			this->GroupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->TextBox2 = (gcnew System::Windows::Forms::TextBox());
			this->Label2 = (gcnew System::Windows::Forms::Label());
			this->TextBox3 = (gcnew System::Windows::Forms::TextBox());
			this->Label3 = (gcnew System::Windows::Forms::Label());
			this->TextBox5 = (gcnew System::Windows::Forms::TextBox());
			this->Label25 = (gcnew System::Windows::Forms::Label());
			this->Button_Exit = (gcnew System::Windows::Forms::Button());
			this->Button_Init = (gcnew System::Windows::Forms::Button());
			this->Button_Start = (gcnew System::Windows::Forms::Button());
			this->Button_Export = (gcnew System::Windows::Forms::Button());
			this->Label32 = (gcnew System::Windows::Forms::Label());
			this->PictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->Label34 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->TextBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->Chart->SuspendLayout();
			this->GroupBox2->SuspendLayout();
			this->GroupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// Chart
			// 
			this->Chart->Controls->Add(this->TextBox9);
			this->Chart->Controls->Add(this->TextBox10);
			this->Chart->Controls->Add(this->TextBox11);
			this->Chart->Controls->Add(this->TextBox12);
			this->Chart->Controls->Add(this->TextBox13);
			this->Chart->Controls->Add(this->label40);
			this->Chart->Controls->Add(this->label41);
			this->Chart->Controls->Add(this->label39);
			this->Chart->Controls->Add(this->TextBox7);
			this->Chart->Controls->Add(this->label38);
			this->Chart->Controls->Add(this->label33);
			this->Chart->Controls->Add(this->label36);
			this->Chart->Controls->Add(this->label37);
			this->Chart->Controls->Add(this->label23);
			this->Chart->Controls->Add(this->label22);
			this->Chart->Controls->Add(this->label21);
			this->Chart->Controls->Add(this->label20);
			this->Chart->Controls->Add(this->label19);
			this->Chart->Controls->Add(this->hScrollBar1);
			this->Chart->Controls->Add(this->label15);
			this->Chart->Controls->Add(this->label16);
			this->Chart->Controls->Add(this->label11);
			this->Chart->Controls->Add(this->label10);
			this->Chart->Controls->Add(this->label9);
			this->Chart->Controls->Add(this->label8);
			this->Chart->Controls->Add(this->Label31);
			this->Chart->Controls->Add(this->Label30);
			this->Chart->Controls->Add(this->Label29);
			this->Chart->Controls->Add(this->CheckBox1);
			this->Chart->Controls->Add(this->Label28);
			this->Chart->Controls->Add(this->Label27);
			this->Chart->Controls->Add(this->Label26);
			this->Chart->Controls->Add(this->Label7);
			this->Chart->Controls->Add(this->Label6);
			this->Chart->Controls->Add(this->Panel1);
			this->Chart->Location = System::Drawing::Point(12, 145);
			this->Chart->Name = L"Chart";
			this->Chart->Size = System::Drawing::Size(1237, 579);
			this->Chart->TabIndex = 57;
			this->Chart->TabStop = false;
			this->Chart->Text = L"Current Chart";
			// 
			// TextBox9
			// 
			this->TextBox9->BackColor = System::Drawing::SystemColors::Window;
			this->TextBox9->Enabled = false;
			this->TextBox9->Location = System::Drawing::Point(138, 540);
			this->TextBox9->Name = L"TextBox9";
			this->TextBox9->ReadOnly = true;
			this->TextBox9->Size = System::Drawing::Size(32, 20);
			this->TextBox9->TabIndex = 52;
			this->TextBox9->TabStop = false;
			// 
			// TextBox10
			// 
			this->TextBox10->BackColor = System::Drawing::SystemColors::Window;
			this->TextBox10->Enabled = false;
			this->TextBox10->Location = System::Drawing::Point(182, 540);
			this->TextBox10->Name = L"TextBox10";
			this->TextBox10->ReadOnly = true;
			this->TextBox10->Size = System::Drawing::Size(33, 20);
			this->TextBox10->TabIndex = 53;
			this->TextBox10->TabStop = false;
			// 
			// TextBox11
			// 
			this->TextBox11->BackColor = System::Drawing::SystemColors::Window;
			this->TextBox11->Enabled = false;
			this->TextBox11->Location = System::Drawing::Point(1193, 540);
			this->TextBox11->Name = L"TextBox11";
			this->TextBox11->ReadOnly = true;
			this->TextBox11->Size = System::Drawing::Size(25, 20);
			this->TextBox11->TabIndex = 59;
			this->TextBox11->TabStop = false;
			// 
			// TextBox12
			// 
			this->TextBox12->BackColor = System::Drawing::SystemColors::Window;
			this->TextBox12->Enabled = false;
			this->TextBox12->Location = System::Drawing::Point(1161, 540);
			this->TextBox12->Name = L"TextBox12";
			this->TextBox12->ReadOnly = true;
			this->TextBox12->Size = System::Drawing::Size(25, 20);
			this->TextBox12->TabIndex = 58;
			this->TextBox12->TabStop = false;
			// 
			// TextBox13
			// 
			this->TextBox13->BackColor = System::Drawing::SystemColors::Window;
			this->TextBox13->Enabled = false;
			this->TextBox13->Location = System::Drawing::Point(1130, 540);
			this->TextBox13->Name = L"TextBox13";
			this->TextBox13->ReadOnly = true;
			this->TextBox13->Size = System::Drawing::Size(25, 20);
			this->TextBox13->TabIndex = 57;
			this->TextBox13->TabStop = false;
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(1153, 544);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(10, 13);
			this->label40->TabIndex = 65;
			this->label40->Text = L":";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(1185, 544);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(10, 13);
			this->label41->TabIndex = 66;
			this->label41->Text = L":";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(171, 544);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(10, 13);
			this->label39->TabIndex = 64;
			this->label39->Text = L":";
			// 
			// TextBox7
			// 
			this->TextBox7->BackColor = System::Drawing::SystemColors::Window;
			this->TextBox7->Enabled = false;
			this->TextBox7->Location = System::Drawing::Point(104, 540);
			this->TextBox7->Name = L"TextBox7";
			this->TextBox7->ReadOnly = true;
			this->TextBox7->Size = System::Drawing::Size(25, 20);
			this->TextBox7->TabIndex = 48;
			this->TextBox7->TabStop = false;
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(128, 544);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(10, 13);
			this->label38->TabIndex = 63;
			this->label38->Text = L":";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(1197, 561);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(18, 13);
			this->label33->TabIndex = 62;
			this->label33->Text = L"us";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(1163, 561);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(20, 13);
			this->label36->TabIndex = 61;
			this->label36->Text = L"ms";
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(1130, 562);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(26, 13);
			this->label37->TabIndex = 60;
			this->label37->Text = L"Sec";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(182, 561);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(18, 13);
			this->label23->TabIndex = 56;
			this->label23->Text = L"us";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(139, 561);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(20, 13);
			this->label22->TabIndex = 55;
			this->label22->Text = L"ms";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(103, 561);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(26, 13);
			this->label21->TabIndex = 54;
			this->label21->Text = L"Sec";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(1071, 545);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(55, 13);
			this->label20->TabIndex = 51;
			this->label20->Text = L"End Time:";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(42, 543);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(58, 13);
			this->label19->TabIndex = 50;
			this->label19->Text = L"Start Time:";
			// 
			// hScrollBar1
			// 
			this->hScrollBar1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->hScrollBar1->LargeChange = 10000;
			this->hScrollBar1->Location = System::Drawing::Point(39, 522);
			this->hScrollBar1->Maximum = 100000000;
			this->hScrollBar1->Name = L"hScrollBar1";
			this->hScrollBar1->Size = System::Drawing::Size(1200, 19);
			this->hScrollBar1->SmallChange = 500;
			this->hScrollBar1->TabIndex = 47;
			this->hScrollBar1->ValueChanged += gcnew System::EventHandler(this, &Form1::ScrollValueChanged);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label15->Location = System::Drawing::Point(42, 312);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(25, 13);
			this->label15->TabIndex = 43;
			this->label15->Text = L"400";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label16->Location = System::Drawing::Point(43, 411);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(25, 13);
			this->label16->TabIndex = 42;
			this->label16->Text = L"200";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label11->Location = System::Drawing::Point(43, 362);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(25, 13);
			this->label11->TabIndex = 40;
			this->label11->Text = L"300";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label10->Location = System::Drawing::Point(43, 263);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(25, 13);
			this->label10->TabIndex = 39;
			this->label10->Text = L"500";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label9->Location = System::Drawing::Point(43, 164);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(25, 13);
			this->label9->TabIndex = 38;
			this->label9->Text = L"700";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label8->Location = System::Drawing::Point(43, 65);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(25, 13);
			this->label8->TabIndex = 37;
			this->label8->Text = L"900";
			// 
			// Label31
			// 
			this->Label31->AutoSize = true;
			this->Label31->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->Label31->Location = System::Drawing::Point(5, 215);
			this->Label31->Name = L"Label31";
			this->Label31->Size = System::Drawing::Size(41, 13);
			this->Label31->TabIndex = 35;
			this->Label31->Text = L"Current";
			// 
			// Label30
			// 
			this->Label30->AutoSize = true;
			this->Label30->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->Label30->Location = System::Drawing::Point(10, 231);
			this->Label30->Name = L"Label30";
			this->Label30->Size = System::Drawing::Size(28, 13);
			this->Label30->TabIndex = 34;
			this->Label30->Text = L"(mA)";
			// 
			// Label29
			// 
			this->Label29->AutoSize = true;
			this->Label29->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->Label29->Location = System::Drawing::Point(43, 362);
			this->Label29->Name = L"Label29";
			this->Label29->Size = System::Drawing::Size(25, 13);
			this->Label29->TabIndex = 33;
			this->Label29->Text = L"400";
			// 
			// CheckBox1
			// 
			this->CheckBox1->AutoSize = true;
			this->CheckBox1->Location = System::Drawing::Point(579, 542);
			this->CheckBox1->Name = L"CheckBox1";
			this->CheckBox1->Size = System::Drawing::Size(87, 17);
			this->CheckBox1->TabIndex = 36;
			this->CheckBox1->TabStop = false;
			this->CheckBox1->Text = L"Enable Chart";
			this->CheckBox1->UseVisualStyleBackColor = true;
			// 
			// Label28
			// 
			this->Label28->AutoSize = true;
			this->Label28->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->Label28->Location = System::Drawing::Point(43, 461);
			this->Label28->Name = L"Label28";
			this->Label28->Size = System::Drawing::Size(25, 13);
			this->Label28->TabIndex = 32;
			this->Label28->Text = L"100";
			// 
			// Label27
			// 
			this->Label27->AutoSize = true;
			this->Label27->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->Label27->Location = System::Drawing::Point(43, 214);
			this->Label27->Name = L"Label27";
			this->Label27->Size = System::Drawing::Size(25, 13);
			this->Label27->TabIndex = 31;
			this->Label27->Text = L"600";
			// 
			// Label26
			// 
			this->Label26->AutoSize = true;
			this->Label26->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->Label26->Location = System::Drawing::Point(43, 115);
			this->Label26->Name = L"Label26";
			this->Label26->Size = System::Drawing::Size(25, 13);
			this->Label26->TabIndex = 30;
			this->Label26->Text = L"800";
			// 
			// Label7
			// 
			this->Label7->AutoSize = true;
			this->Label7->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->Label7->Location = System::Drawing::Point(51, 510);
			this->Label7->Name = L"Label7";
			this->Label7->Size = System::Drawing::Size(13, 13);
			this->Label7->TabIndex = 29;
			this->Label7->Text = L"0";
			// 
			// Label6
			// 
			this->Label6->AutoSize = true;
			this->Label6->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->Label6->Location = System::Drawing::Point(36, 16);
			this->Label6->Name = L"Label6";
			this->Label6->Size = System::Drawing::Size(31, 13);
			this->Label6->TabIndex = 28;
			this->Label6->Text = L"1000";
			// 
			// Panel1
			// 
			this->Panel1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->Panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Panel1->Location = System::Drawing::Point(68, 19);
			this->Panel1->MaximumSize = System::Drawing::Size(1150, 503);
			this->Panel1->Name = L"Panel1";
			this->Panel1->Size = System::Drawing::Size(1150, 503);
			this->Panel1->TabIndex = 27;
			this->Panel1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::Scroll_Event);
			this->Panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Panel1_Paint);
			// 
			// Label24
			// 
			this->Label24->AutoSize = true;
			this->Label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label24->Location = System::Drawing::Point(178, 519);
			this->Label24->Name = L"Label24";
			this->Label24->Size = System::Drawing::Size(162, 16);
			this->Label24->TabIndex = 59;
			this->Label24->Text = L"FT232H SPI Current Meter";
			// 
			// Label12
			// 
			this->Label12->AutoSize = true;
			this->Label12->Location = System::Drawing::Point(116, 120);
			this->Label12->Name = L"Label12";
			this->Label12->Size = System::Drawing::Size(90, 13);
			this->Label12->TabIndex = 21;
			this->Label12->Text = L"Current Bar graph";
			// 
			// Label13
			// 
			this->Label13->AutoSize = true;
			this->Label13->Location = System::Drawing::Point(279, 120);
			this->Label13->Name = L"Label13";
			this->Label13->Size = System::Drawing::Size(40, 13);
			this->Label13->TabIndex = 22;
			this->Label13->Text = L"500mA";
			// 
			// Label14
			// 
			this->Label14->AutoSize = true;
			this->Label14->Location = System::Drawing::Point(13, 120);
			this->Label14->Name = L"Label14";
			this->Label14->Size = System::Drawing::Size(28, 13);
			this->Label14->TabIndex = 23;
			this->Label14->Text = L"0mA";
			// 
			// Label4
			// 
			this->Label4->BackColor = System::Drawing::SystemColors::Control;
			this->Label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label4->Location = System::Drawing::Point(161, 16);
			this->Label4->Name = L"Label4";
			this->Label4->Size = System::Drawing::Size(55, 48);
			this->Label4->TabIndex = 9;
			this->Label4->Text = L"mA";
			this->Label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// Label5
			// 
			this->Label5->BackColor = System::Drawing::SystemColors::Control;
			this->Label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label5->Location = System::Drawing::Point(75, 16);
			this->Label5->Name = L"Label5";
			this->Label5->Size = System::Drawing::Size(79, 48);
			this->Label5->TabIndex = 14;
			this->Label5->Text = L"0";
			this->Label5->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// GroupBox2
			// 
			this->GroupBox2->Controls->Add(this->Label5);
			this->GroupBox2->Controls->Add(this->Label4);
			this->GroupBox2->Controls->Add(this->Label14);
			this->GroupBox2->Controls->Add(this->Label13);
			this->GroupBox2->Controls->Add(this->Label12);
			this->GroupBox2->Location = System::Drawing::Point(12, 68);
			this->GroupBox2->Name = L"GroupBox2";
			this->GroupBox2->Size = System::Drawing::Size(309, 71);
			this->GroupBox2->TabIndex = 52;
			this->GroupBox2->TabStop = false;
			this->GroupBox2->Text = L"Current";
			// 
			// Label1
			// 
			this->Label1->Location = System::Drawing::Point(6, 13);
			this->Label1->Name = L"Label1";
			this->Label1->Size = System::Drawing::Size(112, 16);
			this->Label1->TabIndex = 3;
			this->Label1->Text = L"Number of Devices:";
			this->Label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// TextBox1
			// 
			this->TextBox1->BackColor = System::Drawing::SystemColors::Window;
			this->TextBox1->Enabled = false;
			this->TextBox1->Location = System::Drawing::Point(119, 13);
			this->TextBox1->Name = L"TextBox1";
			this->TextBox1->ReadOnly = true;
			this->TextBox1->Size = System::Drawing::Size(144, 20);
			this->TextBox1->TabIndex = 1;
			this->TextBox1->TabStop = false;
			// 
			// GroupBox7
			// 
			this->GroupBox7->Location = System::Drawing::Point(-159, 154);
			this->GroupBox7->Name = L"GroupBox7";
			this->GroupBox7->Size = System::Drawing::Size(200, 100);
			this->GroupBox7->TabIndex = 25;
			this->GroupBox7->TabStop = false;
			this->GroupBox7->Text = L"GroupBox7";
			// 
			// Label35
			// 
			this->Label35->AutoSize = true;
			this->Label35->Location = System::Drawing::Point(91, 99);
			this->Label35->Name = L"Label35";
			this->Label35->Size = System::Drawing::Size(0, 13);
			this->Label35->TabIndex = 0;
			// 
			// GroupBox1
			// 
			this->GroupBox1->Controls->Add(this->TextBox2);
			this->GroupBox1->Controls->Add(this->Label2);
			this->GroupBox1->Controls->Add(this->TextBox3);
			this->GroupBox1->Controls->Add(this->Label3);
			this->GroupBox1->Controls->Add(this->TextBox5);
			this->GroupBox1->Controls->Add(this->Label25);
			this->GroupBox1->Controls->Add(this->Label35);
			this->GroupBox1->Controls->Add(this->GroupBox7);
			this->GroupBox1->Controls->Add(this->TextBox1);
			this->GroupBox1->Controls->Add(this->Label1);
			this->GroupBox1->Location = System::Drawing::Point(12, 12);
			this->GroupBox1->Name = L"GroupBox1";
			this->GroupBox1->Size = System::Drawing::Size(1241, 44);
			this->GroupBox1->TabIndex = 55;
			this->GroupBox1->TabStop = false;
			this->GroupBox1->Text = L"Device Details";
			// 
			// TextBox2
			// 
			this->TextBox2->BackColor = System::Drawing::SystemColors::Window;
			this->TextBox2->Enabled = false;
			this->TextBox2->Location = System::Drawing::Point(363, 13);
			this->TextBox2->Name = L"TextBox2";
			this->TextBox2->ReadOnly = true;
			this->TextBox2->Size = System::Drawing::Size(144, 20);
			this->TextBox2->TabIndex = 40;
			this->TextBox2->TabStop = false;
			// 
			// Label2
			// 
			this->Label2->Location = System::Drawing::Point(279, 16);
			this->Label2->Name = L"Label2";
			this->Label2->Size = System::Drawing::Size(136, 23);
			this->Label2->TabIndex = 41;
			this->Label2->Text = L"Serial Number:";
			// 
			// TextBox3
			// 
			this->TextBox3->BackColor = System::Drawing::SystemColors::Window;
			this->TextBox3->Enabled = false;
			this->TextBox3->Location = System::Drawing::Point(647, 12);
			this->TextBox3->Name = L"TextBox3";
			this->TextBox3->ReadOnly = true;
			this->TextBox3->Size = System::Drawing::Size(144, 20);
			this->TextBox3->TabIndex = 39;
			this->TextBox3->TabStop = false;
			// 
			// Label3
			// 
			this->Label3->Location = System::Drawing::Point(567, 13);
			this->Label3->Name = L"Label3";
			this->Label3->Size = System::Drawing::Size(128, 23);
			this->Label3->TabIndex = 38;
			this->Label3->Text = L"Description:";
			// 
			// TextBox5
			// 
			this->TextBox5->BackColor = System::Drawing::SystemColors::Window;
			this->TextBox5->Enabled = false;
			this->TextBox5->Location = System::Drawing::Point(906, 12);
			this->TextBox5->Name = L"TextBox5";
			this->TextBox5->ReadOnly = true;
			this->TextBox5->Size = System::Drawing::Size(144, 20);
			this->TextBox5->TabIndex = 35;
			this->TextBox5->TabStop = false;
			// 
			// Label25
			// 
			this->Label25->AutoSize = true;
			this->Label25->Location = System::Drawing::Point(837, 15);
			this->Label25->Name = L"Label25";
			this->Label25->Size = System::Drawing::Size(40, 13);
			this->Label25->TabIndex = 34;
			this->Label25->Text = L"Status:";
			// 
			// Button_Exit
			// 
			this->Button_Exit->Location = System::Drawing::Point(1032, 775);
			this->Button_Exit->Name = L"Button_Exit";
			this->Button_Exit->Size = System::Drawing::Size(166, 30);
			this->Button_Exit->TabIndex = 51;
			this->Button_Exit->Text = L"Exit";
			this->Button_Exit->Click += gcnew System::EventHandler(this, &Form1::Button_Exit_Click);
			// 
			// Button_Init
			// 
			this->Button_Init->Location = System::Drawing::Point(510, 775);
			this->Button_Init->Name = L"Button_Init";
			this->Button_Init->Size = System::Drawing::Size(158, 30);
			this->Button_Init->TabIndex = 49;
			this->Button_Init->Text = L"Initialise";
			this->Button_Init->UseVisualStyleBackColor = true;
			this->Button_Init->Click += gcnew System::EventHandler(this, &Form1::Button_Init_Click);
			// 
			// Button_Start
			// 
			this->Button_Start->Location = System::Drawing::Point(687, 775);
			this->Button_Start->Name = L"Button_Start";
			this->Button_Start->Size = System::Drawing::Size(162, 30);
			this->Button_Start->TabIndex = 50;
			this->Button_Start->Text = L"Start";
			this->Button_Start->Click += gcnew System::EventHandler(this, &Form1::Button_Start_Click);
			// 
			// Button_Export
			// 
			this->Button_Export->Location = System::Drawing::Point(863, 775);
			this->Button_Export->Name = L"Button_Export";
			this->Button_Export->Size = System::Drawing::Size(163, 30);
			this->Button_Export->TabIndex = 62;
			this->Button_Export->Text = L"Export Data";
			this->Button_Export->UseVisualStyleBackColor = true;
			this->Button_Export->Click += gcnew System::EventHandler(this, &Form1::Button_Export_Click);
			// 
			// Label32
			// 
			this->Label32->AutoSize = true;
			this->Label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label32->Location = System::Drawing::Point(266, 746);
			this->Label32->Name = L"Label32";
			this->Label32->Size = System::Drawing::Size(82, 18);
			this->Label32->TabIndex = 64;
			this->Label32->Text = L"Version 1.0";
			// 
			// PictureBox1
			// 
			this->PictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"PictureBox1.Image")));
			this->PictureBox1->Location = System::Drawing::Point(12, 730);
			this->PictureBox1->Name = L"PictureBox1";
			this->PictureBox1->Size = System::Drawing::Size(200, 75);
			this->PictureBox1->TabIndex = 63;
			this->PictureBox1->TabStop = false;
			// 
			// Label34
			// 
			this->Label34->AutoSize = true;
			this->Label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label34->Location = System::Drawing::Point(253, 774);
			this->Label34->Name = L"Label34";
			this->Label34->Size = System::Drawing::Size(122, 18);
			this->Label34->TabIndex = 65;
			this->Label34->Text = L"http://www.ti.com";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(534, 94);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(144, 20);
			this->textBox4->TabIndex = 66;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &Form1::textBox4_TextChanged);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(352, 96);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(179, 13);
			this->label17->TabIndex = 67;
			this->label17->Text = L"Time to run (in seconds) [Max. <=60]";
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(726, 96);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(89, 17);
			this->checkBox2->TabIndex = 68;
			this->checkBox2->Text = L"Enable Relay";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// TextBox6
			// 
			this->TextBox6->BackColor = System::Drawing::SystemColors::Window;
			this->TextBox6->Enabled = false;
			this->TextBox6->Location = System::Drawing::Point(972, 93);
			this->TextBox6->Name = L"TextBox6";
			this->TextBox6->ReadOnly = true;
			this->TextBox6->Size = System::Drawing::Size(144, 20);
			this->TextBox6->TabIndex = 69;
			this->TextBox6->TabStop = false;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(860, 96);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(107, 13);
			this->label18->TabIndex = 70;
			this->label18->Text = L"Bin File size (in bytes)";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1261, 808);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->TextBox6);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->Label32);
			this->Controls->Add(this->PictureBox1);
			this->Controls->Add(this->Label34);
			this->Controls->Add(this->Button_Export);
			this->Controls->Add(this->Chart);
			this->Controls->Add(this->GroupBox1);
			this->Controls->Add(this->Button_Start);
			this->Controls->Add(this->Label24);
			this->Controls->Add(this->Button_Init);
			this->Controls->Add(this->GroupBox2);
			this->Controls->Add(this->Button_Exit);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Chart->ResumeLayout(false);
			this->Chart->PerformLayout();
			this->GroupBox2->ResumeLayout(false);
			this->GroupBox2->PerformLayout();
			this->GroupBox1->ResumeLayout(false);
			this->GroupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


private: System::Void Button_Init_Click(System::Object^  sender, System::EventArgs^  e) {
			DWORD DeviceCount; // The number of devices
			unsigned int uiDevIndex; // The device in the list that we'll use
			BYTE byOutputBuffer[MAX_BUF_SIZE]; // Buffer to hold MPSSE commands and data

			// to be sent to the FT2232H
			BYTE byInputBuffer[MAX_BUF_SIZE]; // Buffer to hold data read from the FT2232H
			DWORD DeviceIndex; // General loop index
			DWORD dwNumBytesToSend; // Index to the output buffer
			DWORD dwNumBytesSent; // Count of actual bytes sent - used with FT_Write
			DWORD dwNumBytesToRead; // Number of bytes available to read

			// in the driver's input buffer
			DWORD dwNumBytesRead; // Count of actual bytes read - used with FT_Read
			DWORD dwClockDivisor; // Value of clock divisor, SCL Frequency

		// Code for INIT button
		// -----------------------------------------------------------
		// Variables
		// -----------------------------------------------------------
		char tempstring1[50]="";
		char tempstring2[50]="";

		// 60/((1+N)*2) (MHz) = 1Mhz
		bool bCommandEchod = false;

		char FT_Serial_Number[50], FT_Description[50];
		char pcSerialNumber[50],  pcDescription[50];
		
		unsigned long lpdwFlags, lpdwType, lpdwID, lpdwLocId;

		uint16 data = 0;
		DeviceCount = 0;
		DeviceIndex = 0; // General loop index
		dwNumBytesToSend = 0; // Index to the output buffer
		dwNumBytesSent = 0; // Count of actual bytes sent - used with FT_Write
		dwNumBytesToRead = 0; // Number of bytes available to read
        dwNumBytesRead = 0; // Count of actual bytes read - used with FT_Read
		dwClockDivisor = 0x04;
		
		LoggingEnabled = false;
		SPI_Device_Found = false;
		//Binary file to dump Read data
		F1 = fopen("./readdata.bin","w+b");
		//Csv file to plot data
		F2 = fopen("./Final_data.csv","w");
		//############################################################################################################
        // Initialise the MPSSE
        //############################################################################################################

        // Prevent user clicking any buttons on user interface until Init complete
        this->Button_Start->Enabled = false;
        this->Button_Exit->Enabled = false;
        this->Button_Init->Enabled = false;

		if(UserInputFlag == false)
		{
				usertimeval = 1;
				this->textBox4->Text = "1";
				timetorun = usertimeval*1000;
		}
        // Set the focus to the Init button since the user has just clicked it
        this->Button_Init->Focus();

        //************************************************************************************************************
        // Get the number of FTDI devices attached
        //************************************************************************************************************

        // Check the number of FTDI devices
		printf("Checking for FTDI devices...\n");
		ftStatus = FT_CreateDeviceInfoList(&DeviceCount);

		if (ftStatus != FT_OK) // Did the command execute OK?
		{
			printf("FT_CreateDeviceInfoList failed! Error in getting the number of devices\n");
			//return -1; // Exit with error
		}

		// Inform user if no devices connected and exit this subroutine
        // Enable buttons to allow user to re-try Init or to Exit 
		if (DeviceCount < 1) // Exit if we don't see any
		{
			printf("%d",DeviceCount);
			CommLostError("There are no FTDI devices installed\n");
			this->TextBox1->Text = "0";
			this->TextBox5->Text = "No FTDI Devices Found";
			
			this->Button_Start->Enabled = false;
			this->Button_Exit->Enabled = true;
			this->Button_Init->Enabled = true;

			this->Button_Init->Focus();
			return;	 // Exit with error
		}
		// Otherwise display device count returned by FT_GetNumberOfDevices on form
		else
			this->TextBox1->Text = DeviceCount.ToString();            
		
        //************************************************************************************************************
        // Get a handle to the "FT232H SPI Demo" by checking the String returned by each FTDI device
        //************************************************************************************************************

        // Go through each FTDI device and check text string to see if it is the SPI Demo 
        // Increment device index until all devices found were checked or until device found with the correct string
        // Note: If more than one FTDI device with the string FT232H SPI Demo is found, the first will be opened

        DeviceIndex = 0;
        SPI_Device_Found = false;

        // Do for Index = 0 to Index = (number of devices found - 1)
        while((DeviceIndex < DeviceCount) && (SPI_Device_Found == false))
		{
			pin_ptr<FT_HANDLE> p = &ftHandle;
		
			//Get device details
			ftStatus = FT_GetDeviceInfoDetail(DeviceIndex, &lpdwFlags,&lpdwType,&lpdwID,&lpdwLocId,pcSerialNumber,\
				pcDescription,p);

			// Check if the function failed...
			if(ftStatus != FT_OK)
			{
				CommLostError("GetDeviceString Failed");
				return;
			}

            // Check if device is the matching
			if(strcmp(pcDescription,"FT2232H MiniModule A")==0)
			{
				strcpy_s(FT_Serial_Number,pcSerialNumber);
                strcpy_s(FT_Description,pcDescription);
				String ^tempsystemstring1 = gcnew String(FT_Serial_Number);
				String ^tempsystemstring2 = gcnew String(FT_Description);
                this->TextBox3->Text = tempsystemstring1;
                this->TextBox2->Text = tempsystemstring2;
				
				// Set flag to show that device was found and we can stop looking
                SPI_Device_Found = true;
			}

			else
				// Otherwise try the next index
                DeviceIndex = DeviceIndex + 1;
		}

		// Tell user if no FT232H SPI Demo device found. Allow them to re-try the init or to exit
		if(SPI_Device_Found == false)
		{
			this->TextBox5->Text = "No SPI Devices Found";
			this->Button_Start->Enabled = false;
			this->Button_Exit->Enabled = true;
			this->Button_Init->Enabled = true;
			
			this->Button_Init->Focus();
			//return -1;
		}

		//************************************************************************************************************
        // Open the device using the index which was found above
        //************************************************************************************************************

        // Open the SPI Demo using the index found above
		pin_ptr<FT_HANDLE> p = &ftHandle;
		
		ftStatus = FT_Open(DeviceIndex, p);

		// Check if the function failed...
		if(ftStatus != FT_OK)
		{
			CommLostError("GetDeviceString Failed");
			return;
		}


        //************************************************************************************************************
        // Configure the MPSSE in the device
        //************************************************************************************************************
		// Configure port parameters
		printf("\nConfiguring port for MPSSE use...\n");
		ftStatus |= FT_ResetDevice(ftHandle);
		//Reset USB device
		//Purge USB receive buffer first by reading out all old data from FT2232H receive buffer
		ftStatus |= FT_GetQueueStatus(ftHandle, &dwNumBytesToRead);
		// Get the number of bytes in the FT2232H
		// receive buffer
		if ((ftStatus == FT_OK) && (dwNumBytesToRead > 0))
			FT_Read(ftHandle, &byInputBuffer, dwNumBytesToRead, &dwNumBytesRead);
		//Read out the data from FT2232H receive buffer
		ftStatus |= FT_SetUSBParameters(ftHandle, USB_BUF_SIZE, USB_BUF_SIZE);
		//Set USB request transfer sizes to 64K
		ftStatus |= FT_SetChars(ftHandle, false, 0, false, 0);
		//Disable event and error characters
		ftStatus |= FT_SetTimeouts(ftHandle, 5000, 5000);
		//Sets the read and write timeouts in milliseconds
		ftStatus |= FT_SetLatencyTimer(ftHandle, 1);
		//Set the latency timer to 1mS (default is 16mS)
		ftStatus |= FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0x00, 0x00);
		//Turn on flow control to synchronize IN requests
		ftStatus |= FT_SetBitMode(ftHandle, 0x0, 0x00);
		//Reset controller
		ftStatus |= FT_SetBitMode(ftHandle, 0x0, 0x02);
		//Enable MPSSE mode
		
		if (ftStatus != FT_OK)
		{
			CommLostError("Error in initializing the MPSSE\n");
			FT_Close(ftHandle);
			return; // Exit with error
		}
		
		Sleep(50); // Wait for all the USB stuff to complete and work

		// -----------------------------------------------------------
		// Configure the MPSSE settings for JTAG
		// Multple commands can be sent to the MPSSE with one FT_Write
		// -----------------------------------------------------------
		dwNumBytesToSend = 0; // Start with a fresh index
		// Set up the Hi-Speed specific commands for the FTx232H
		byOutputBuffer[dwNumBytesToSend++] = 0x8A;
		// Use 60MHz master clock (disable divide by 5)
		byOutputBuffer[dwNumBytesToSend++] = 0x97;
		// Turn off adaptive clocking (may be needed for ARM)
		byOutputBuffer[dwNumBytesToSend++] = 0x8D;
		// Disable three-phase clocking
		ftStatus = FT_Write(ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
		// Send off the HS-specific commands
		dwNumBytesToSend = 0; // Reset output buffer pointer
		
		if (ftStatus != FT_OK)
		{
			CommLostError("Error in initializing the Clock");
			FT_Close(ftHandle);
			return; // Exit with error
		}

		// Set TCK frequency
		// TCK = 60MHz /((1 + [(1 +0xValueH*256) OR 0xValueL])*2)
		byOutputBuffer[dwNumBytesToSend++] = '\x86';
		// Command to set clock divisor
		byOutputBuffer[dwNumBytesToSend++] = dwClockDivisor & 0xFF;
		// Set 0xValueL of clock divisor
		byOutputBuffer[dwNumBytesToSend++] = (dwClockDivisor >> 8) & 0xFF;
		// Set 0xValueH of clock divisor
		ftStatus = FT_Write(ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
		// Send off the clock divisor commands
		dwNumBytesToSend = 0; // Reset output buffer pointer
		// Set initial states of the MPSSE interface
		// - low byte, both pin directions and output values
		// Pin name Signal Direction Config Initial State Config
		// ADBUS0 TCK/SK output 1 high 1
		// ADBUS1 TDI/DO output 1 low 0
		// ADBUS2 TDO/DI input 0 0
		// ADBUS3 TMS/CS output 1 high 1
		// ADBUS4 GPIOL0 output 1 low 0
		// ADBUS5 GPIOL1 output 1 low 0
		// ADBUS6 GPIOL2 output 1 high 1
		// ADBUS7 GPIOL3 output 1 high 1
		byOutputBuffer[dwNumBytesToSend++] = 0x80;
		// Configure data bits low-byte of MPSSE port
		byOutputBuffer[dwNumBytesToSend++] = 0xC1; //was c9
		// Initial state config above
		byOutputBuffer[dwNumBytesToSend++] = 0xDB;
		// Direction config above
		ftStatus = FT_Write(ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
		// Send off the low GPIO config commands
		dwNumBytesToSend = 0; // Reset output buffer pointer
		// Note that since the data in subsequent sections will be clocked on the rising edge, the
		// inital clock state of high is selected. Clocks will be generated as high-low-high.
		// For example, in this case, data changes on the rising edge to give it enough time
		// to have it available at the device, which will accept data *into* the target device
		// on the falling edge.
		// Set initial states of the MPSSE interface
		// - high byte, both pin directions and output values
		// Pin name Signal Direction Config Initial State Config
		// ACBUS0 GPIOH0 input 0 0
		// ACBUS1 GPIOH1 input 0 0
		// ACBUS2 GPIOH2 input 0 0
		// ACBUS3 GPIOH3 input 0 0
		// ACBUS4 GPIOH4 input 0 0
		// ACBUS5 GPIOH5 input 0 0
		// ACBUS6 GPIOH6 input 0 0
		// ACBUS7 GPIOH7 input 0 0
		byOutputBuffer[dwNumBytesToSend++] = 0x82;

		// Configure data bits low-byte of MPSSE port
		byOutputBuffer[dwNumBytesToSend++] = 0x00;
		// Initial state config above
		byOutputBuffer[dwNumBytesToSend++] = 0x00;
		// Direction config above
		ftStatus = FT_Write(ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
		// Send off the high GPIO config commands
		dwNumBytesToSend = 0; // Reset output buffer pointer
		for(DeviceIndex = 0; DeviceIndex < 8; DeviceIndex++)
		{ // Clear out the input and output buffers
			byInputBuffer[DeviceIndex] = 0x00;
			byOutputBuffer[DeviceIndex] = 0x00;
		}


		// -----------------------------------------------------------
		// Synchronize the MPSSE by sending a bogus opcode (0xAB),
		// The MPSSE will respond with "Bad Command" (0xFA) followed by
		// the bogus opcode itself.
		// -----------------------------------------------------------
		byOutputBuffer[dwNumBytesToSend++] = 0xAB;
		//Add bogus command ‘0xAB’ to the queue
		ftStatus = FT_Write(ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
		// Send off the BAD command
		dwNumBytesToSend = 0; // Reset output buffer pointer
		do
		{
			ftStatus = FT_GetQueueStatus(ftHandle, &dwNumBytesToRead);
			// Get the number of bytes in the device input buffer
		} while ((dwNumBytesToRead == 0) && (ftStatus == FT_OK));
	
		//or Timeout
		bCommandEchod = false;
		ftStatus = FT_Read(ftHandle, &byInputBuffer, dwNumBytesToRead, &dwNumBytesRead);
		//Read out the data from input buffer
		for (DeviceIndex = 0; DeviceIndex < dwNumBytesRead - 1; DeviceIndex++)
		//Check if Bad command and echo command are received
		{
			if ((byInputBuffer[DeviceIndex] == 0xFA) && (byInputBuffer[DeviceIndex+1] == 0xAB))
			{
				bCommandEchod = true;
				break;
			}
		}

		if (bCommandEchod == false)
		{
			CommLostError("Error in synchronizing the MPSSE\n");
			FT_Close(ftHandle);
			return; // Exit with error
		}

		// Disable internal loop-back
		byOutputBuffer[dwNumBytesToSend++] = 0x85;
		// Disable loopback
		ftStatus = FT_Write(ftHandle, byOutputBuffer,\
		dwNumBytesToSend, &dwNumBytesSent);
		// Send off the loopback command
		dwNumBytesToSend = 0; // Reset output buffer pointer
		// Check the receive buffer - it should be empty
		ftStatus = FT_GetQueueStatus(ftHandle, &dwNumBytesToRead);
		// Get the number of bytes in
		// the FT2232H receive buffer
		if (dwNumBytesToRead != 0)
		{
			CommLostError("Error - MPSSE receive buffer should be empty\n");
			FT_SetBitMode(ftHandle, 0x0, 0x00);
			// Reset the port to disable MPSSE
			FT_Close(ftHandle); // Close the USB port
			return; // Exit with error
		}

		dwNumBytesToRead = 0;
		byOutputBuffer[dwNumBytesToSend++] = 0x80;
		// Configure data bits low-byte of MPSSE port
		byOutputBuffer[dwNumBytesToSend++] = 0xC1; //was c9
		// Initial state config above
		byOutputBuffer[dwNumBytesToSend++] = 0xDB;
		// Direction config above
		ftStatus = FT_Write(ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
		// Send off the low GPIO config commands
		dwNumBytesToSend = 0; // Reset output buffer pointer

        //************************************************************************************************************
        // Set flag to show that device now initialised
        //************************************************************************************************************

        DeviceInit = true;                           // Device is now initialised

        this->TextBox5->Text = "Device Ready";              // Show that the device is now ready
		 
        this->Button_Start->Enabled = true;          // Allow user to start new measurement run
        this->Button_Init->Enabled = false;
        this->Button_Exit->Enabled = true;           // Allow user to exit program
 
        this->Button_Start->Focus();                  // Switch focus to the start button

        ChartToZero = true;                          // Run chart plot routine - all values zero to set starting state
        RepaintChart = true;						 // Authorise re-paint of chart when the refresh routine is called
        Panel1->Refresh();                             // Cause the re-paint to occur

        Update();                                    // Update the dialog box
        Application::DoEvents();
	 }

/***********************************************************************************************************************************/
private: System::Void Button_Start_Click(System::Object^  sender, System::EventArgs^  e) {

			BYTE byOutputBuffer[MAX_BUF_SIZE]; // Buffer to hold MPSSE commands and data

			// to be sent to the FT2232H
			BYTE byInputBuffer[MAX_BUF_SIZE]; // Buffer to hold data read from the FT2232H
			DWORD DeviceIndex; // General loop index
			DWORD dwNumBytesToSend; // Index to the output buffer
			DWORD dwNumBytesSent; // Count of actual bytes sent - used with FT_Write
			DWORD dwNumBytesToRead; // Number of bytes available to read

			// in the driver's input buffer
			DWORD dwNumBytesRead; // Count of actual bytes read - used with FT_Read
		
			unsigned int total_written;
			unsigned int total_read;

		// Code for the START button
		int i = 0;
		int j = 0;
		int k = 0;
		int temp1 = 0;
		int temp2 = 0;
		int prin_control=0;

        // Configure the buttons on the user form
		this->Button_Start->Enabled = false;             // Prevent user initialising device whilst running measurements
        this->Button_Init->Enabled = false;				 // Prevent user starting a new measurement run whilst this one is running
        this->Button_Exit->Enabled = false;				 // Prevent user exiting program whilst the measurement is running
        this->hScrollBar1->Enabled = true;

        //############################################################################################################
        // Take readings from the port pins and then ADCs (ADC0 in Chip Select 0 first, then ADC1 on Chip Select 1)
        //############################################################################################################

        this->TextBox5->Text = "Running";                       // Update status to tell user that measurement is running

        LoggingEnabled = true;                           // Logging will run whilst this is True, Stop button will set it to false

		//************************************************************************************************************
        // Set idle condition with LED on and no chip selects asserted
		//************************************************************************************************************
		dwNumBytesToSend = 0;
		byOutputBuffer[dwNumBytesToSend++] = 0x80;
		// Configure data bits low-byte of MPSSE port
		byOutputBuffer[dwNumBytesToSend++] = 0xC1; //was c9
		// Initial state config above
		byOutputBuffer[dwNumBytesToSend++] = 0xFB;
		// Direction config above
		ftStatus = FT_Write(ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
		// Send off the low GPIO config commands
		dwNumBytesToSend = 0;
		if(ftStatus != FT_OK)
		{
			CommLostError("Pin Write failed in Start Button");
			return;
		}

		byOutputBuffer[dwNumBytesToSend++] = 0x82;

		// Configure data bits low-byte of MPSSE port
		byOutputBuffer[dwNumBytesToSend++] = 0x00;
		// Initial state config above
		byOutputBuffer[dwNumBytesToSend++] = 0x00;
		// Direction config above
		ftStatus = FT_Write(ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
		// Send off the high GPIO config commands
		dwNumBytesToSend = 0; // Reset output buffer pointer
		for(DeviceIndex = 0; DeviceIndex < MAX_BUF_SIZE; DeviceIndex++)
		{ // Clear out the input and output buffers
			byInputBuffer[DeviceIndex] = 0x00;
			byOutputBuffer[DeviceIndex] = 0x00;
		}

		// Check if the function failed...
		if(ftStatus != FT_OK)
		{
			CommLostError("Pin Write failed in Start Button");
			return;
		}

		// Short delay
		Sleep(10);

		while(LoggingEnabled == true)
		{
			if(1)//RepaintChart == false)		// Don't run again until chart has finished re-painting
			{
				dwNumBytesToRead = 0;
				dwNumBytesToSend = 0;

				for (i = 0; i < TX_RX_SIZE; i++)
				{
					byOutputBuffer[dwNumBytesToSend++] = 0x80;
					// Set data bits low-byte of MPSSE port
					byOutputBuffer[dwNumBytesToSend++] = 0xCF;
					// Only change TMS/CS bit to zero
					byOutputBuffer[dwNumBytesToSend++] = 0xDB;
					// Direction config is still needed for each GPIO write

					byOutputBuffer[dwNumBytesToSend++] = 0x80;
					// Set data bits low-byte of MPSSE port
					byOutputBuffer[dwNumBytesToSend++] = 0xCF;
					// Only change TMS/CS bit to zero
					byOutputBuffer[dwNumBytesToSend++] = 0xDB;
					// Direction config is still needed for each GPIO write

					byOutputBuffer[dwNumBytesToSend++] = 0x80;
					// Set data bits low-byte of MPSSE port
					byOutputBuffer[dwNumBytesToSend++] = 0xCF;
					// Only change TMS/CS bit to zero
					byOutputBuffer[dwNumBytesToSend++] = 0xDB;
					// Direction config is still needed for each GPIO write
					
					byOutputBuffer[dwNumBytesToSend++] = 0x80;
					// Set data bits low-byte of MPSSE port
					byOutputBuffer[dwNumBytesToSend++] = 0xC7;
					// Only change TMS/CS bit to zero
					byOutputBuffer[dwNumBytesToSend++] = 0xDB;


					byOutputBuffer[dwNumBytesToSend++] = 0x20; // was 0x34
					// Output on rising clock, input on falling clock
					// MSB first, clock a number of bytes out
					byOutputBuffer[dwNumBytesToSend++] = 0x01; // Length L
					byOutputBuffer[dwNumBytesToSend++] = 0x00; // Length H
				}

				total_written = 0;
				total_read = 0;
						
				Form1::TimerFun();
				
				  // Runs the timer, and raises the event. 
				  while ( exitFlag == false )
				  {
					 // Processes all the events in the queue.
					 ftStatus = FT_Write(ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
					 Application::DoEvents();
					 ftStatus = FT_GetQueueStatus(ftHandle, &dwNumBytesToRead);
					 FT_Read(ftHandle, &byInputBuffer, dwNumBytesToRead, &dwNumBytesRead);

					 total_written = total_written + TX_RX_SIZE * 2;
					 total_written = total_read + dwNumBytesRead;

					 fwrite(byInputBuffer, dwNumBytesRead,1,F1);
				  }

				  if(exitFlag == true)
				  {
					  LoggingEnabled = false;  
				  }
				
				filesz = ftell(F1);
				if(filesz % 2 !=0) filesz--;
				fclose(F1);
				this->TextBox6->Text = filesz.ToString();
				this->hScrollBar1->Maximum = filesz;		//Updated  button size
				Update();

				Panel1->Refresh();

				F1 = fopen("./readdata.bin","r+b");
				//temp1 = sz/1150;	
				RepaintChart = true;
				sizeoffset = 0;
				this->TextBox7->Text="0";
				this->TextBox9->Text="0";
				this->TextBox10->Text="0";
				Panel1->Refresh();
			}			
		Update();
		Application::DoEvents();
		}

        // When code gets here, LoggingEnabled = False and so the Stop button has been pressed

        this->Button_Init->Enabled = true;
        this->Button_Start->Enabled = false;
        this->Button_Exit->Enabled = true;
        this->Button_Init->Focus();
		this->Button_Exit->Focus();

        this->TextBox5->Text = "Stopped"; // Update the status
	 }

private: System::Void Button_Export_Click(System::Object^  sender, System::EventArgs^  e) {
				F1 = fopen("./readdata.bin","r+b");
				int temp2 = 0;
				current = 0;
				BYTE byInputBuffer[MAX_BUF_SIZE];
				temp2 = filesz;

				while(temp2>0)
				{			
					fread(byInputBuffer,2,1,F1);
					current = byInputBuffer[0];
					current = current << 8;
					current = current + byInputBuffer[1];
					if(current > 32768)
						current = current-65536;
					current = current + 32768;
					fprintf(F2,"%d\n", current);
					temp2--;
				}
				fclose(F1);
				fclose(F2);			 
		 }


private: System::Void ScrollValueChanged(System::Object^  sender, System::EventArgs^  e) {
		long float num1,num2;
		sizeoffset= (int)( "hScrollBar Value:(OnValueChanged Event) {0}", hScrollBar1->Value );
		RepaintChart = true;
		num1 = (long float)sizeoffset*timetorun/filesz;		//time in ms
		num2 = num1+(long float)1150*timetorun/filesz;
		this->TextBox7->Text=((int)num1/1000).ToString();
		this->TextBox9->Text=((int)num1%1000).ToString();
		this->TextBox10->Text=((int)((num1-(int)num1)*1000)).ToString();
		this->TextBox13->Text=((int)num2/1000).ToString();
		this->TextBox12->Text=((int)num2%1000).ToString();
		this->TextBox11->Text=((int)((num2-(int)num2)*1000)).ToString();
		Update();
		Panel1->Refresh();
	}

private: System::Void Panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) { 
		BYTE byInputBuffer[MAX_BUF_SIZE]; // Buffer to hold data read from the FT2232H
		Graphics^ g = e->Graphics;
		int CurrentArray[1150];
		/*
		' This subroutine re-draws the entire chart using the data from the CurrentArray array
        ' It is called every time a new reading is taken since the graph needs to be re-drawn each time it scrolls

        ' The panel is 500 pixels high (plus one for the X axis line) and so each pixel is 2mA.
        ' A Y value of 500 is the bottom of the chart (0mA) and a Y value of 0 is the top of the chart (500mA)

        ' It uses a kind of circular buffer where the Y values are passed in an array
        ' The measurement routine adds new values to the array in a circular fashion and updates GraphInputPointer
        ' to show the last point added

        ' This paint routine draws a chart from X values 0 to 1149. It uses the last point added plus 1 as the starting point
        ' and then draws the 340 points (including wrapping back to location zero in the array once location 1149 is reached)
        ' This means that the last point added is always at the right-hand side of the chart and so it scrolls right to left
		*/
		
		int PaintLoopCounter;
		int Xval1,Xval2,Yval1,Yval2;
		int temp3 = 0;
		//int scrollOffset;
        /*
		' This ensures that the chart is only re-painted once a new reading is taken in case the routine is called at other 
        ' times. RepaintChart is set True when new data is put in the buffer or when the chart is being initialised with zeros
		*/
		//g->Clear(Color::AntiqueWhite);
 
	   Pen^ redPen = gcnew Pen(Color::Red);
	   redPen->Width = 1;

	   Pen^ bluePen = gcnew Pen(Color::Blue);
	   bluePen->Width = 1;

	   Pen^ blackPen = gcnew Pen(Color::Black);
	   blackPen->Width = 5;
	   	   	   
	   if(RepaintChart == true)
		{
			// Create a graphics object
            g = Panel1->CreateGraphics();
			/*
            ' draw horizontal lines for the current scale 
            ' Y coordinates start from the top of the chart
			*/
				g->DrawLine(bluePen, 0, 0, 1149, 0);				//0 = 1000mA line
				g->DrawLine(bluePen, 0, 50, 1149, 50);			//50  = 900mA line
				g->DrawLine(bluePen, 0, 100, 1149, 100);			//100 = 800mA line
				g->DrawLine(bluePen, 0, 150, 1149, 150);			//150 = 700mA line
				g->DrawLine(bluePen, 0, 200, 1149, 200);			//200 = 600mA line
				g->DrawLine(bluePen, 0, 250, 1149, 250);			//250 = 500mA line
				g->DrawLine(bluePen, 0, 300, 1149, 300);			//300 = 400mA line
				g->DrawLine(bluePen, 0, 350, 1149, 350);			//350 = 300mA line
				g->DrawLine(bluePen, 0, 400, 1149, 400);			//400 = 200mA line
				g->DrawLine(bluePen, 0, 450, 1149, 450);			//450 = 100mA line
				g->DrawLine(bluePen, 0, 500, 1149, 500);			//500 = 0mA line

				// Draw the small black tickmark next to each current value on the scale
				g->DrawLine(blackPen, 0, 0, 1, 0);				
				g->DrawLine(blackPen, 0, 50, 1, 50);			
				g->DrawLine(blackPen, 0, 100, 1, 100);			
				g->DrawLine(blackPen, 0, 150, 1, 150);	
				g->DrawLine(blackPen, 0, 200, 1, 200);
				g->DrawLine(blackPen, 0, 250, 1, 250);
				g->DrawLine(blackPen, 0, 300, 1, 300);
				g->DrawLine(blackPen, 0, 350, 1, 350);
				g->DrawLine(blackPen, 0, 400, 1, 400);
				g->DrawLine(blackPen, 0, 450, 1, 450);
				g->DrawLine(blackPen, 0, 500, 1, 500);

            /*
			' If starting the program or if the chart is disabled by the checkbox, set all datapoints to zero
            ' This means fill CurrentArray with the value 250 since Y starts from the top of the chart and it is 250 pixels high
			*/
			if((ChartToZero == true) || (CheckBox1->Checked == false))
			{
				GraphInputPointer = 0;
                GraphIndex = 0;
				
				// This loop fills all 340 X values of the chart with the Y value 250 (== 0mA)
				while(GraphIndex < 1149)
				{
					CurrentArray[GraphIndex] = 500;
					GraphIndex = GraphIndex + 1;
				}
				
				// Clear the flag so that we can start drawing the graph the next time this subroutine is called
				ChartToZero = false;
				GraphInputPointer = 0;
				GraphIndex = 0;
			}
			else
			{
				temp3 = 0;

				if(F1 != NULL)
					fclose(F1);
				
				F1 = fopen("./readdata.bin","r+b");
				fseek (F1 , sizeoffset*2 , SEEK_SET );
				while(temp3 < 1150)
				{
					current = 0;
					fread(byInputBuffer,2,1,F1);

					current = byInputBuffer[0];
					current = current << 8;
					current = current + byInputBuffer[1];

					if(current > 32768)
						current = current-65536;

					current = current + 32768;
					
					//************************************************************************************************************
					// Update screen
					//************************************************************************************************************
					// Meter display
					this->Label5->Text = current.ToString();
					// Put current value into bar graph
					
					Update();
					/* 
					' Add the current vaue in mA into the buffer used by the chart plotting routine
					' The chart Y direction is reversed and has 2mA increments and so 
					' 0mA is stored as 500, 100mA as 450, 200mA as 400, 500mA as 250, 1000mA as 0
					' Note: Chart height is 501 pixels so 0mA (y = 500 on the chart) will still be visible above the axis 
					*/

					CurrentArray[GraphInputPointer] = (500 - (current / 200));    //' 500 instead of 501 so visible when zero

					/*
					' Increment the index value so that the result is put into the next location in the array
					' this is also read by the chart plotting routine
					' Allow for wrap-around if last value was 1149
					*/
					if(GraphInputPointer == 1150)
					{
						GraphInputPointer = 0;
					}
					else
						GraphInputPointer++;

					RepaintChart = true;	
					temp3++;
				}


                /*
				' If this is a normal painting cycle, then draw the chart 
                ' The CurrentArray has 1150 values, which are the Y values for the chart

                ' The measurement routine writes new values one-at-a-time into the array. It updates the
                ' GraphInputPointer value to show where the last value was added
                ' This paint routine starts at that location plus one and draws the 1150 points of the chart

                ' Because we do not always start painting at index 0 of the incoming data, we use this 
                ' variable as a 0 - 1149 X value 
				*/
                PaintLoopCounter = 0;

                /*
				' Set the starting point in the circular buffer based upon the last data added by the measurement subroutine
                ' GraphInputPointer is the index of the last value added from the measurement subroutine
                ' GraphIndex is a copy of this taken by this paint routine and will be used to point to the values to draw the chart
				*/
				
				if(GraphInputPointer < 1149)
					GraphIndex = GraphInputPointer + 1;      // Select the first point index for drawing the chart (last data added plus one)
				else
					GraphIndex = 0;                          // Wrap around if the input pointer was 1149
				
				/*
                ' Now paint the 1150 points in the chart
                ' For each point plotted, we draw a line FROM the previous point TO the current point 
                ' to make a continuous chart
				*/
				while(PaintLoopCounter < 1149)
				{
                    // Set the TO x and y coordinates to the current point
                    Xval2 = PaintLoopCounter;
                    Yval2 = (CurrentArray[GraphIndex]);

					/*
                    ' Now set the FROM x and y values using the previous point 

                    ' If the index is zero, the previous point (x-1) was 1149 due to wrap-around
                    ' otherwise, previous point is the index minus 1
					*/
					if(GraphIndex == 0)
					{
						Yval1 = CurrentArray[0];
                        Xval1 = PaintLoopCounter - 1;
					}
					else
					{
						Yval1 = CurrentArray[GraphIndex - 1];
                        Xval1 = PaintLoopCounter - 1;
					}

                    // Draw a line from the previous point to the current point 
					g->DrawLine(redPen, Xval1, Yval1, Xval2, Yval2);
                    
                    // Increment the index allowing for wrap-around at 1149
                    if(GraphIndex < 1149)
						GraphIndex = GraphIndex + 1;
					else
						GraphIndex = 0;
					
                    // Move on to the next chart point
                    PaintLoopCounter = PaintLoopCounter + 1;
				}
			}

			Update();
            // Clear the flag to show chart has been updated and allow the next measurement to be taken
            // Acts as handshaking
            RepaintChart = false;
		}
    }


private: System::Void Button_Exit_Click(System::Object^  sender, System::EventArgs^  e) {
			BYTE byOutputBuffer[MAX_BUF_SIZE]; // Buffer to hold MPSSE commands and data
			DWORD dwNumBytesToSend; // Index to the output buffer
			DWORD dwNumBytesSent; // Count of actual bytes sent - used with FT_Write


		//Code for the EXIT button

        this->Button_Start->Enabled = false;
        this->Button_Exit->Enabled = false;
        this->Button_Init->Enabled = false;

        LoggingEnabled = false;

        //************************************************************************************************************
        // Set the pins back to idle states
        //************************************************************************************************************
		dwNumBytesToSend = 0;
		byOutputBuffer[dwNumBytesToSend++] = 0x80;
		// Configure data bits low-byte of MPSSE port
		byOutputBuffer[dwNumBytesToSend++] = 0x08; //was c9
		// Initial state config above
		byOutputBuffer[dwNumBytesToSend++] = 0xFF;
		// Direction config above
		ftStatus = FT_Write(ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
		// Send off the low GPIO config commands
		dwNumBytesToSend = 0;

		// Check if the function failed...
		if(ftStatus != FT_OK)
		{
			CommLostError("No device to close");
		}
        
        // If device was initialised, then close it before exiting
		if(DeviceInit == true)
		{
			ftStatus = FT_Close(ftHandle);
			if(ftStatus == FT_OK)
			     this->TextBox5->Text = "Interface Closed";
        }
		Sleep(100);
		if(F1!=NULL)
		fclose(F1);
		if(F2!=NULL)
		fclose(F2);
		Close(); //To close form
 }


private: System::Void CommLostError(char *messagestring) {
		String ^tempsystemstring = gcnew String(messagestring);
        MessageBox::Show(tempsystemstring);
        this->Button_Init->Enabled = true;
        this->Button_Start->Enabled = false;
        this->Button_Exit->Enabled = true;
        this->TextBox5->Text = tempsystemstring;
		 }

private: System::Void Receive_Error(){
        MessageBox::Show("Receive Error");
        this->Button_Init->Enabled = true;
        this->Button_Start->Enabled = false;
        this->Button_Exit->Enabled = true;
        this->TextBox5->Text = "Receive Error";
		 }

private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
        // Initialise the variables, buttons and progress bar when the form loads
        this->Button_Init->Enabled = true;
        this->Button_Start->Enabled = false;
        this->Button_Exit->Enabled = true;
		this->hScrollBar1->Enabled = false;

        DeviceInit = false;          // Not yet initialised

        LoggingEnabled = false;      // Not logging yet

        this->TextBox5->Text = "Unconfigured";            

        this->CheckBox1->Checked = true;

        this->Button_Init->Focus();         // Put focus on the Init button since it will be pressed first

        //'' Draw the FTDI logo, which should be in the same directory as the .exe file
        //'' Logo now added as a project resource so commented out
        //' PictureBox1.Image = System.Drawing.Bitmap.FromFile( _
        //' My.Application.Info.DirectoryPath & "\FTDI.bmp")

        //' Set the entire scrolling chart to zero and trigger re-paint
        ChartToZero = true;
        RepaintChart = true;

        Panel1->Refresh();
        Update();
        Application::DoEvents();
	 }

private: System::Void textBox4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(this->textBox4->Text == "")
			 {
				 usertimeval = 1;
			 }
			 else
				 usertimeval =  int::Parse(this->textBox4->Text);

			 timetorun = usertimeval * 1000;		//convert to milli-seconds from seconds
			 UserInputFlag = true;
		 }

public:
   static void TimerFun()
   {int i = 0;

      /* Adds the event and the event handler for the method that will 
                process the timer event to the timer. */
      myTimer->Tick += gcnew EventHandler( TimerEventProcessor );

      // Sets the timer interval to timetorun seconds.
      myTimer->Interval = timetorun;
      myTimer->Start();
   }
  
   /*
   if (MessageBox::Show("Do you want to exit?","My Application", MessageBoxButtons::YesNo,MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
		 {
			Application::Exit();
		 }*/

private: System::Void Scroll_Event(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
//			 scroll_by_num = ;
		 }
};
}
