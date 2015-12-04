//---------------------------------------------------------------------------

#include <vcl.h>
#include <registry.hpp>

#define __BORLAND__

#include <rc_util.h>

#pragma hdrstop

#define MAX_WL 7   // 850 1300 1310 1490 1550 1625 1650
#define PM2_NUM_SKIP_WAVE 0
#define PM1_NUM_SKIP_WAVE 1



#define MAX_DELTA_SM 0.2
#define MAX_DELTA_MM 0.3

#include "Unit1.h"
#include "../DllAPp/dllMainInc.h"

#include "dbmodif.h"

#pragma link "DllTest.lib"

#include "opm.h"
#include <stdio.h>
#include <fstream>

#include <json/json.h>
#include <dos.h>

#define _WINSOCK2API_
#include "w_tcp.h"
//#include "x_Port.h"





//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
instrumentPowerMeter *dev;
instrumentTunableLaserSource *dev_lsr;
instrumentWaveLenghtMeter *dev_wlm;

TPort* Port;

Measurer  *measurer;
OpmHandle handle;

DeviceConnectionRequest *mydeviceConnectionRequest;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)

{
   dev = new instrumentPowerMeter();
   dev_lsr = new instrumentTunableLaserSource();
   dev_wlm = new instrumentWaveLenghtMeter();


  init_database_path("autoprg-lts-veritech.db"); // valid path required

  char bufdb[1024*3];
  int len=1024*3;
  get_unit_string("546415", bufdb,len);
  int len2;
  len2 = strlen(bufdb);

  get_unit_param_raw("546415","W1","KWln",bufdb,len);
  len2 = strlen(bufdb);


	char bufver[32];

	 TProjectRCVersion applVersion(NULL);
	LPSTR fileVersion;
	applVersion.GetFileVersion(fileVersion);

	sscanf(fileVersion,"%s",bufver);

	Label8->Caption = AnsiString(bufver);

	srand ( time(NULL) );


 my_deviceInfoProvider = new DeviceInfoProvider(
			"opm.dll");

  LogFile = new TLogFile("test_station.log");

  n_wl = MAX_WL;

  num_wl[0] = "850";
  num_wl[1] = "1300";
  num_wl[2] = "1310";
  num_wl[3] = "1490";
  num_wl[4] = "1550";
  num_wl[5] = "1625";
  num_wl[6] = "1650";

  StringGrid1->RowCount = n_wl;

  flag_init_OPM = false;

   StringGrid2->Cells[1][0] = "Gold";
   StringGrid2->Cells[2][0] = "FX-40/45";
   StringGrid2->Cells[3][0] = "Delta";
   StringGrid2->Cells[4][0] = "Note";

  for(int i=0;i<n_wl;i++)
  {
	StringGrid1->Cells[0][i] = num_wl[i];

	StringGrid2->Cells[0][i+1] = num_wl[i];

	wchar_t * UnicodeString = new wchar_t[4]; /* ������-���������� */
	mbstowcs(UnicodeString,num_wl[i].c_str(), 4);

	RadioGroup1->Items->Add(UnicodeString);

 //	delete [] UnicodeString;

	result[i][0] = 0.0;
	result[i][1] = 0.0;
	result[i][2] = 0.0;

  }
  RadioGroup1->ItemIndex = 1;

  char buf[16];

  std::ofstream file;

  FILE *f;

  f = fopen("delta.txt","r");
  if(f)
  {

		fscanf(f,"%s",pathForResult);
		for(int i=0;i<n_wl;i++)
		{
			  fscanf(f, "%f",&delta_array[i]);

			  sprintf(buf, "%.4f",delta_array[i]);

			  StringGrid1->Cells[1][i] = AnsiString(buf);
		}


		fclose(f);
		}






}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
   delete dev;
   delete dev_lsr;

   delete dev_wlm;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::initGPIBButtonClick(TObject *Sender)
{
	int a;

	dev->setAdressGPIB(StrToInt(adressGPIB->Text));
	a = dev->GPIBInit();

	answerInsrtumentMemo->Lines->Add("Answer " + IntToStr(a));
  //	Label1->Caption = IntToStr(a);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
   int a;
   char buf[256];
   a = dev->checkIDN(buf);

   if(!a){
  // answerInsrtumentMemo->Lines->Add("My TEST");

   answerInsrtumentMemo->Lines->Add(buf);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::initInstrumentButtonClick(TObject *Sender)
{
	int a;

	dev->setAdressInstrument(StrToInt(adressInstrument->Text),0);
	a = dev->instrumnetConnect();

	answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
  //	Label1->Caption = IntToStr(a);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
   int a;
   a = dev->setUnit(StrToInt(slotNumber->Text),dBm);
   answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
   int a;
   char buf[256];
   a = dev->returnPower(StrToInt(slotNumber->Text),buf);

   if(!a)
   {
	  answerInsrtumentMemo->Lines->Add("Power Answer " + IntToStr(a));
	  answerInsrtumentMemo->Lines->Add(buf);
   }
   else
   {
	  answerInsrtumentMemo->Lines->Add("Error " + IntToStr(a));
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
   int a;
   a = dev->setUnit(StrToInt(slotNumber->Text),WATT);
   answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	int a;
	a = dev->opticalSwitch(StrToInt(switchEdit->Text));
    answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::waveLenghtButtonClick(TObject *Sender)
{
   int a;

   a = dev->setWavelenght(StrToInt(slotNumber->Text),AnsiString(waveLenghtEdit->Text).c_str());
   answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::buttonInitLaserClick(TObject *Sender)
{
	int a;

	dev_lsr->setAdressInstrument(StrToInt(laserAdress->Text),0);
	a = dev_lsr->instrumnetConnect();

	answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::laserWaveButtonClick(TObject *Sender)
{
  int a;

   a = dev_lsr->setWavelenght(AnsiString(laserWave->Text).c_str());
   answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::buttonIDNLaserClick(TObject *Sender)
{
  int a;
   char buf[256];
   a = dev_lsr->checkIDN(buf);

   if(!a){
  // answerInsrtumentMemo->Lines->Add("My TEST");

   answerInsrtumentMemo->Lines->Add(buf);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
   int a;
   if(CheckBox1->Checked)
   {
	 a = dev_lsr->enable();
   }
   else
   {
	 a = dev_lsr->disable();
   }

   answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button6Click(TObject *Sender)
{
	 flag_init_OPM = true;
	int nw;
	try{


		if( typeConnection->ItemIndex == 0 )
		{
		   measurer = my_deviceInfoProvider->connectToDevice(0);
		} else {

			std::string adr(AnsiString(ipAdressText->Text).c_str());
			measurer = my_deviceInfoProvider->connectToDeviceTcpIp(adr);
		}

		DeviceConnectionRequest::Make(0,measurer);
	}
	catch(...)
	{
		answerInsrtumentMemo->Lines->Add("Error init opm");
		flag_init_OPM = false;
	}

	if(!measurer)
	{
	   answerInsrtumentMemo->Lines->Add("measurer is nill");
	}else
	{
	   answerInsrtumentMemo->Lines->Add("Init is OK");


	   nw = measurer->getWavelengthsNum();

	   type_pm = 0;
	   if(nw==7)
	   {
		 answerInsrtumentMemo->Lines->Add("opm is PM2");
		 type_pm = PM2_NUM_SKIP_WAVE;
	   }
	   if(nw==8)
	   {
		 answerInsrtumentMemo->Lines->Add("opm is PM1");
		 type_pm = PM1_NUM_SKIP_WAVE;
	   }


	   char buf[160];
	   numberDevice = measurer->getOpticalModuleSerialNumber();
	   sprintf(buf,"internal serial number %d",numberDevice);
	   answerInsrtumentMemo->Lines->Add(buf);

	   sprintf(buf,"Number of wavelenght %d",nw);
	   answerInsrtumentMemo->Lines->Add(buf);

	   for (int i = 0; i < nw; i++) {
		 deviceWavelenght[i] = measurer->getWavelength(i);
		 sprintf(buf,"Number %d is wavelenght %d",i,deviceWavelenght[i]);
		 answerInsrtumentMemo->Lines->Add(buf);
	   }

	   numberOfWavelenghtInDevice = nw;



	}



}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
   if( flag_init_OPM)
   {
	 float pwr;
	 char str[20];
	 pwr = (float)measurer->readPower();
	 sprintf(str, "%.4g", pwr );
	 answerInsrtumentMemo->Lines->Add("Read Power=");
		answerInsrtumentMemo->Lines->Add(str);
   } else
   {
     answerInsrtumentMemo->Lines->Add("ERROR not init OPM");
   }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
	int a;
	int indexInDevice;
	char wl[10];
   int wlnumber;

   strcpy( wl, num_wl[RadioGroup1->ItemIndex].c_str());
   wlnumber = StrToInt(wl);

 	  if( flag_init_OPM )
	  {
		 bool flag_present_wave = false;
		 for(int i = 0; i < numberOfWavelenghtInDevice; i++)
		 {
			 if(wlnumber == deviceWavelenght[i] )
			 {
				 flag_present_wave = true;
				 indexInDevice = i;
				 break;
			 }
		 }
		 if( flag_present_wave )
		 {
		   // measurer->switchWavelengthByIndex(index + type_pm);
			  measurer->switchWavelengthByIndex(indexInDevice);
			  answerInsrtumentMemo->Lines->Add("Ok");
		 } else
		 {
			answerInsrtumentMemo->Lines->Add("!!! Power meter not support this wavelengh");

		 }
	   //	 measurer->switchWavelengthByValue(StrToInt(num_wl[index].c_str()));
	  } else
	  {
		answerInsrtumentMemo->Lines->Add("!!! OPM not init");

	  }




 //  measurer->switchWavelengthByValue(StrToInt(num_wl[RadioGroup1->ItemIndex].c_str()));
//   measurer->switchWavelengthByIndex(RadioGroup1->ItemIndex + type_pm);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{

   ReadPower(RadioGroup1->ItemIndex);
   char buf[256];

   if(!ReadTwoPorts->Checked)
   {

	  sprintf(buf, "gold=%.3f fx40=%.3f delta=%.3f", pwr_gold,pwr,delta );

   } else
   {
	  sprintf(buf, "agilent1=%.4f agilent2=%.4f delta=%.4f", pwr_gold,pwr,delta );

   }
   answerInsrtumentMemo->Lines->Add(buf);
}
//---------------------------------------------------------------------------
// Set wave for all button
void __fastcall TForm1::Button10Click(TObject *Sender)
{

   SetWorkingWaveLenght(RadioGroup1->ItemIndex);

}
//---------------------------------------------------------------------------
// Store delta button
void __fastcall TForm1::Button11Click(TObject *Sender)
{
   delta_array[RadioGroup1->ItemIndex] = delta;

   char buf[10];


   sprintf(buf, "%.4f",delta);

   StringGrid1->Cells[1][RadioGroup1->ItemIndex] = AnsiString(buf);
}
//---------------------------------------------------------------------------
int TForm1::SetWorkingWaveLenght(int index)
{
	int a;
	int indexInDevice;
  char wl[10];
   int wlnumber;

   strcpy( wl, num_wl[index].c_str());
   wlnumber = StrToInt(wl);

   if( ControlTLS->Checked)
   {
	  a = dev_lsr->setWavelenght(wl);
	  answerInsrtumentMemo->Lines->Add("TLS Answer " + IntToStr(a));
   }

   if(ReadTwoPorts->Checked)
   {
		a = dev->setWavelenght(1,wl);
		answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
		answerInsrtumentMemo->Lines->Add("Slot 1 set wavelenght");

		a = dev->setWavelenght(2,wl);
		answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
	  answerInsrtumentMemo->Lines->Add("Slot 2 set wavelenght");
   }  else
   {
	  if( flag_init_OPM )
	  {
		 bool flag_present_wave = false;
		 for(int i = 0; i < numberOfWavelenghtInDevice; i++)
		 {
			 if(wlnumber == deviceWavelenght[i] )
			 {
				 flag_present_wave = true;
				 indexInDevice = i;
				 break;
			 }
		 }
		 if( flag_present_wave )
		 {
		   // measurer->switchWavelengthByIndex(index + type_pm);
			  measurer->switchWavelengthByIndex(indexInDevice);
			  answerInsrtumentMemo->Lines->Add("Ok");
		 } else
		 {
			answerInsrtumentMemo->Lines->Add("!!! Power meter not support this wavelengh");
			return 2;
		 }



	   //	 measurer->switchWavelengthByValue(StrToInt(num_wl[index].c_str()));
	  } else
	  {
		answerInsrtumentMemo->Lines->Add("!!! OPM not init");
		return 1;
	  }

	  a = dev->setWavelenght(StrToInt(slotNumber->Text),wl);
	  answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
   }
   char buf[40];
   strcpy(buf,"Wavelenght=");
   strcat(buf,wl);
   answerInsrtumentMemo->Lines->Add(buf);
   return 0;


}
//---------------------------------------------------------------------------
void TForm1::ReadPower(int indexWave)
{
   int a;
   char buf[256];

   if(ReadTwoPorts->Checked)
   {
		a = dev->returnPower(2,buf);      // Read Agilent slot 2
		pwr = atof(buf);

   } else {        // Read from FX40
	  pwr = (float)measurer->readPower();
   }



   a = dev->returnPower(StrToInt(slotNumber->Text),buf);
   pwr_gold = atof(buf);


   float dl=0.0;
   if(CheckBox2->Checked)
   {
	  dl = delta_array[indexWave];
   }

 //  float delta;
   delta = pwr - pwr_gold - dl;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1SetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value)
{
  if(!Value.IsEmpty())
   {
	   float f = StrToFloat(AnsiString(Value).c_str());

		delta_array[ARow] = f;
   }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
   char buf[100];
   int res;
   for(int i=1;i<n_wl;i++)    // skip 850nm
   {
	   res = SetWorkingWaveLenght(i);
	   if(res)
	   {
		   if(res==1)
		   return;
				result[i][0] = 0;
				result[i][1] = 0;
				result[i][2] = 0;

	   } else
	   {
	   Sleep(4000);

	   ReadPower(i);
	   result[i][0] = pwr_gold + delta_array[i];
	   result[i][1] = pwr;
	   result[i][2] = delta;

	  sprintf(buf, "gold=%.4f fx40=%.4f delta=%.4f", result[i][0],result[i][1],result[i][2] );
	  answerInsrtumentMemo->Lines->Add(buf);

   /*
	   sprintf(buf, "%.4f",result[i][0]);
	   StringGrid2->Cells[1][i+1] = AnsiString(buf);

	   sprintf(buf, "%.4f",result[i][1]);
	   StringGrid2->Cells[2][i+1] = AnsiString(buf);

	   sprintf(buf, "%.4f",result[i][2]);
	   StringGrid2->Cells[3][i+1] = AnsiString(buf);
	 */
	   }
   }
   UpdateResultTable();
   flagFake = false;
   int a;

   a = dev_lsr->setWavelenght("1300");
   answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));

   answerInsrtumentMemo->Lines->Add("----------FINISHED-----------");

}
//---------------------------------------------------------------------------
void TForm1::UpdateResultTable()
{
   char buf[100];
   float max_delta;

	for(int i=0;i<n_wl;i++)
   {
	   if(i<=1)
	   {
		   max_delta = MAX_DELTA_MM;
	   }
	   else
	   {
		   max_delta = MAX_DELTA_SM;
       }
	   sprintf(buf, "%.3f",result[i][0]);
	   StringGrid2->Cells[1][i+1] = AnsiString(buf);

	   sprintf(buf, "%.3f",result[i][1]);
	   StringGrid2->Cells[2][i+1] = AnsiString(buf);

	   sprintf(buf, "%.3f",result[i][2]);
	   StringGrid2->Cells[3][i+1] = AnsiString(buf);

	   if( (result[i][2]>max_delta) || (result[i][2]<-max_delta))
	   {
		  StringGrid2->Cells[4][i+1] = "!!! FAIL";
	   }  else
		{
		  StringGrid2->Cells[4][i+1] = "";
		}
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button13Click(TObject *Sender)
{
	struct date d;
	getdate(&d);

	struct  time t;
	gettime(&t);

	char sdate[64];
	char stime[64];
	char bufNumberDevice[16];
	char buf1[16],buf2[16],buf3[16];
	float pg,pfx,delt;

	sprintf(sdate,"%d-%.2d-%.2d",d.da_year,d.da_mon,d.da_day);
	sprintf(stime,"%.2d:%.2d",t.ti_hour,t.ti_min);
	sprintf(bufNumberDevice,"%d",numberDevice);

	Json::Value root(Json::objectValue);
	root["veexSerialNumber"] = AnsiString(FileNameEdit->Text).c_str();
	root["Date"] = sdate;
	root["Time"] = stime;
	root["agizerSerialNumber"] = bufNumberDevice;
	root["jobId"] = "Device calibration";
	root["fake"] = flagFake;

	Json::Value tables(Json::arrayValue);
	Json::Value result_wl(Json::objectValue);

	for(int i=0;i<n_wl;i++)
	{

	   tables[i] = StrToInt(num_wl[i].c_str());
			result_wl["wave"] = StrToInt(num_wl[i].c_str());

			sprintf(buf1,"%.4f",result[i][0]);
			result_wl["Gold dBm"] = buf1;

			sprintf(buf2,"%.4f",result[i][1]);
			result_wl["power dBm"] = buf2;

			sscanf(buf1,"%f",&pg);
			sscanf(buf2,"%f",&pfx);
			delt = pfx - pg;

			sprintf(buf3,"%.4f",delt);   //result[i][2];
			result_wl["delta "] = buf3;

			tables[i] = result_wl;
	 }


   root["Result table"] = tables;

  //	std::cout << root << std::endl;

		char fnm[200];
		strcpy(fnm,pathForResult);
		strcat(fnm,AnsiString(FileNameEdit->Text).c_str());
		strcat(fnm,".oxlts");

		std::ofstream file;
		file.open(fnm);
		if(file.is_open())
		{
			file << root;
			file.close();


			char buf[250];
			strcpy(buf,"Result save to file: ");
			strcat(buf,fnm);
			answerInsrtumentMemo->Lines->Add(buf);


			FileNameEdit->Text = "enter number";
		}  else
		{
		   answerInsrtumentMemo->Lines->Add("-----Error save to file!!!!!");
        }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button14Click(TObject *Sender)
{

   char buf[20];

		std::ofstream file;
		file.open("delta.txt");
		if(file.is_open())
		{
			file << pathForResult;
			file << "\n";

			for(int i=0;i<n_wl;i++)
			{
			  sprintf(buf, "%.4f \n",delta_array[i]);
			  file << buf;
			}

			file.close();
		}
}
//---------------------------------------------------------------------------
// button generate
void __fastcall TForm1::Button15Click(TObject *Sender)
{
  generateFakeResult();

}
//---------------------------------------------------------------------------
void TForm1::generateFakeResult()
{


  float a;
	for(int i=0;i<n_wl;i++)
	{
	   a = ((rand() % 199) - 100 )/ 1000.0 / 2.0;    // -0.099 to + 0.099
	   result[i][1] += a;
	   a = ((rand() % 199) - 100 )/ 100.0 / 8.5;    // -0.099 to + 0.099
	   result[i][2] = a;

	   result[i][0] = result[i][1] - result[i][2];
	}

	 UpdateResultTable();
	 flagFake = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid2SetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value)
{
   if(!Value.IsEmpty())
   {
	   float f = StrToFloat(AnsiString(Value).c_str());
	   result[ARow-1][ACol-1] = f;


	   if(ARow==1)    // only for 850 nm
	   {
		 float pg = StrToFloat(AnsiString(StringGrid2->Cells[1][1]).c_str());
		 float pfx = StrToFloat(AnsiString(StringGrid2->Cells[2][1]).c_str());
		 float dl = pfx - pg;

		 result[0][0] = pg;
		 result[0][1] = pfx;
		 result[0][2] = dl;

		 char buf[12];
		 sprintf(buf, "%.3f",dl);
		 StringGrid2->Cells[3][1] = AnsiString(buf);

		 if( (result[0][2]>MAX_DELTA_MM) || (result[0][2]<-MAX_DELTA_MM))
		 {
			StringGrid2->Cells[4][1] = "FAIL";
		 }  else
		   {
			 StringGrid2->Cells[4][1] = "";
		   }
		 }

	}

}

void __fastcall TForm1::typeConnectionClick(TObject *Sender)
{
	if(typeConnection->ItemIndex == 1)
	{
		ipAdressText->Enabled = true;
	}
	else
	{
        ipAdressText->Enabled = false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button17Click(TObject *Sender)
{
   int a;

   int num;
   double pow[10];
   double wl[10];

   a = dev_wlm->MeasurePowerArray(&num,pow,wl);

	 if(!a){
  // answerInsrtumentMemo->Lines->Add("My TEST");

   answerInsrtumentMemo->Lines->Add("okkkkk");
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button18Click(TObject *Sender)
{
	int a;

	dev_wlm->setAdressInstrument(18,0);
	a = dev_wlm->instrumnetConnect();

	a = dev_wlm->resetInstument();

	answerInsrtumentMemo->Lines->Add("Instrument Answer " + IntToStr(a));
}
//---------------------------------------------------------------------------
