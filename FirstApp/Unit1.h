//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H

#ifndef __BORLAND__
#define __BORLAND__

#endif


#include "DeviceConnectionRequest.h"

#include "deviceInfoProvider.h"


//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Sockets.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *answerInsrtumentMemo;
	TStringGrid *StringGrid1;
	TButton *Button11;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TLabel *Label1;
	TEdit *adressGPIB;
	TButton *initGPIBButton;
	TLabel *Label2;
	TEdit *adressInstrument;
	TButton *initInstrumentButton;
	TLabel *Label5;
	TEdit *laserAdress;
	TButton *buttonInitLaser;
	TButton *Button3;
	TButton *buttonIDNLaser;
	TLabel *Label3;
	TEdit *slotNumber;
	TButton *Button1;
	TButton *Button4;
	TButton *Button2;
	TLabel *Label4;
	TEdit *switchEdit;
	TButton *Button5;
	TEdit *waveLenghtEdit;
	TButton *waveLenghtButton;
	TRadioGroup *RadioGroup1;
	TButton *Button10;
	TButton *Button9;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox1;
	TEdit *laserWave;
	TButton *laserWaveButton;
	TCheckBox *ControlTLS;
	TCheckBox *ReadTwoPorts;
	TTabSheet *TabSheet2;
	TStringGrid *StringGrid2;
	TButton *Button12;
	TLabel *Label6;
	TEdit *FileNameEdit;
	TButton *Button13;
	TButton *Button14;
	TButton *Button15;
	TButton *Button16;
	TLabel *Label7;
	TLabel *Label8;
	TRadioGroup *typeConnection;
	TEdit *ipAdressText;
	TLabel *Label9;
	TTabSheet *TabSheet3;
	TButton *Button17;
	TButton *Button18;
	TCheckBox *CheckBoxCh850;
	TCheckBox *CheckBoxCh1300;
	TCheckBox *CheckBoxCh1310;
	TCheckBox *CheckBoxCh1490;
	TCheckBox *CheckBoxCh1550;
	TCheckBox *CheckBoxCh1625;
	TCheckBox *CheckBoxCh1650;
	TButton *Button19;
	TCheckBox *CheckBoxEnableChange;
	TButton *Button20;
	void __fastcall initGPIBButtonClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall initInstrumentButtonClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall waveLenghtButtonClick(TObject *Sender);
	void __fastcall buttonInitLaserClick(TObject *Sender);
	void __fastcall laserWaveButtonClick(TObject *Sender);
	void __fastcall buttonIDNLaserClick(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);

	void __fastcall StringGrid1SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall StringGrid2SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall typeConnectionClick(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall Button20Click(TObject *Sender);



private:	// User declarations
  //  std::auto_ptr<DeviceInfoProvider> deviceInfoProvider;
	int n_wl;
	AnsiString num_wl[MAX_WL];

	float wl_delta;
	bool flag_init_OPM;
	bool flag_init_TLS;
	bool flag_init_GOLDOPM;
	float delta;
	float pwr,pwr_gold;
	bool flagFake;

	float delta_array[MAX_WL];

	float result[MAX_WL][4];   // [][0] - gold_device, [][1] - power OPM, [][2] - delta, [][3] -koeffFromDB

	char pathForResult[128];
	char pathForDb[256];

	int type_pm;    // 0 - pm2,  1 - pm1
	unsigned numberDevice;
	unsigned deviceWavelenght[20];
	float deviceKoeff[20];
	int numberOfWavelenghtInDevice;

	int SetWorkingWaveLenght(int index,int *indexInDevice);
	int ReturnDeviceIndexOfWave(int wlnumber);
	void ReadPower(int indexWave);
	void ChangeInDataBase(char *buffSerialNumber,int n);

	void UpdateResultTable();
	void generateFakeResult();

	DeviceInfoProvider *my_deviceInfoProvider;
   //	DeviceConnectionRequest *mydeviceConnectionRequest;
 //	Measurer *my_measurer;

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
