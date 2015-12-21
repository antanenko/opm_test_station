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
	TButton *buttonStoreDelta;
	TButton *buttonSaveDeltaToFile;
	TLabel *Label7;
	TLabel *Label8;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label5;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *adressGPIB;
	TButton *initGPIBButton;
	TEdit *adressInstrument;
	TButton *initInstrumentButton;
	TEdit *laserAdress;
	TButton *buttonInitLaser;
	TButton *buttonIDNPowerMeter;
	TButton *buttonIDNLaser;
	TEdit *slotNumber;
	TButton *buttonDBm;
	TButton *buttonWatt;
	TButton *buttonPower;
	TEdit *switchEdit;
	TButton *buttonSwitch;
	TEdit *waveLenghtEdit;
	TButton *waveLenghtButton;
	TRadioGroup *RadioGroup1;
	TButton *buttonSetWaveForAll;
	TButton *buttonReadTwo;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox1;
	TEdit *laserWave;
	TButton *laserWaveButton;
	TCheckBox *ControlTLS;
	TCheckBox *ReadTwoPorts;
	TTabSheet *TabSheet2;
	TLabel *Label6;
	TStringGrid *StringGrid2;
	TButton *ButtonStart;
	TEdit *FileNameEdit;
	TButton *buttonSaveResult;
	TButton *buttonGenerateFake;
	TButton *buttonInitOPMAutoMode;
	TCheckBox *CheckBoxCh850;
	TCheckBox *CheckBoxCh1300;
	TCheckBox *CheckBoxCh1310;
	TCheckBox *CheckBoxCh1490;
	TCheckBox *CheckBoxCh1550;
	TCheckBox *CheckBoxCh1625;
	TCheckBox *CheckBoxCh1650;
	TButton *buttonChangeCoeff;
	TCheckBox *CheckBoxEnableChange;
	TButton *buttonReleasePort;
	TTabSheet *TabSheet3;
	TButton *Button17;
	TButton *Button18;
	TGroupBox *GroupBox1;
	TButton *ButtonSetZero;
	TButton *buttonSetWavelenght;
	TButton *ButtonReadOPM;
	TButton *buttonInitOPM;
	TRadioGroup *typeConnection;
	TLabel *Label9;
	TEdit *ipAdressText;
	void __fastcall initGPIBButtonClick(TObject *Sender);
	void __fastcall buttonIDNPowerMeterClick(TObject *Sender);
	void __fastcall initInstrumentButtonClick(TObject *Sender);
	void __fastcall buttonDBmClick(TObject *Sender);
	void __fastcall buttonPowerClick(TObject *Sender);
	void __fastcall buttonWattClick(TObject *Sender);
	void __fastcall buttonSwitchClick(TObject *Sender);
	void __fastcall waveLenghtButtonClick(TObject *Sender);
	void __fastcall buttonInitLaserClick(TObject *Sender);
	void __fastcall laserWaveButtonClick(TObject *Sender);
	void __fastcall buttonIDNLaserClick(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall buttonInitOPMClick(TObject *Sender);
	void __fastcall ButtonReadOPMClick(TObject *Sender);
	void __fastcall buttonSetWavelenghtClick(TObject *Sender);
	void __fastcall buttonReadTwoClick(TObject *Sender);
	void __fastcall buttonSetWaveForAllClick(TObject *Sender);
	void __fastcall buttonStoreDeltaClick(TObject *Sender);

	void __fastcall StringGrid1SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall ButtonStartClick(TObject *Sender);
	void __fastcall buttonSaveResultClick(TObject *Sender);
	void __fastcall buttonSaveDeltaToFileClick(TObject *Sender);
	void __fastcall buttonGenerateFakeClick(TObject *Sender);
	void __fastcall StringGrid2SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall typeConnectionClick(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall buttonChangeCoeffClick(TObject *Sender);
	void __fastcall buttonReleasePortClick(TObject *Sender);
	void __fastcall ButtonSetZeroClick(TObject *Sender);



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
