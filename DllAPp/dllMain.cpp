//---------------------------------------------------------------------------

#include <windows.h>
#include <vcl.h>

#include "dllMainInc.h"
#include "ni4882.h"
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
int init(const int a)
{
  return 5;
}
//---------------------------------------------------------------------------
deviceGPIB::deviceGPIB(void)
{
	gpibAdress = 0;

	primaryAdress = PRIMARY_ADDR_OF_SCOPE;
	secondaryAdress = NO_SECONDARY_ADDR;
}
//---------------------------------------------------------------------------
deviceGPIB::~deviceGPIB(void)
{
   ibonl(Dev, 0);
   ibonl(gpibAdress, 0);
}
//---------------------------------------------------------------------------
void deviceGPIB::setAdressGPIB(int adr)
{
  gpibAdress = adr;
}
//---------------------------------------------------------------------------
void deviceGPIB::setAdressInstrument(int primAdr,int secondAdr)
{
	primaryAdress = primAdr;
	secondaryAdress = secondAdr;
}
//---------------------------------------------------------------------------
int deviceGPIB::GPIBInit()
{
   SendIFC(gpibAdress);
   if (Ibsta() & ERR)
   {
	 // GPIBCleanup(GPIB0, "Unable to open board");
	  return 1;
   }
 return 0;
}
//---------------------------------------------------------------------------
int deviceGPIB::GPIBDisconnect()
{
   ibonl(gpibAdress, 0);
   return 0;
}
//---------------------------------------------------------------------------
int deviceGPIB::instrumnetConnect()
{
   Dev = ibdev(gpibAdress, primaryAdress, secondaryAdress,
			   TIMEOUT, EOTMODE, EOSMODE);
   if (Ibsta() & ERR)
   {
   //	  printf("Unable to open device\nibsta = 0x%x iberr = %d\n",
   //			 Ibsta(), Iberr());
	  return 1;
   }

   ibclr(Dev);
   if (Ibsta() & ERR)
   {
	//  GPIBCleanup(Dev, "Unable to clear device");
	  return 2;
   }
   return 0;
}
//---------------------------------------------------------------------------
int deviceGPIB::writeCommandInstrument(const char *cmnd)
{
   int size;
   size = strlen(cmnd);

   ibwrt(Dev, cmnd, size);
   if (Ibsta() & ERR)
   {
	 // GPIBCleanup(Dev2, "Unable to set oscilloscope");
	 // return 1;
   }
   return 0;
}
//---------------------------------------------------------------------------
int deviceGPIB::readAnswerInstrument(char *str)
{

  ibrd(Dev, ValueStr, INSTR_ARRAYSIZE);
   if (Ibsta() & ERR)
   {
	 // GPIBCleanup(Dev2, "Unable to read data from oscilloscope");
	  return 1;
   }
   ValueStr[Ibcnt() - 1] = '\0';
   //printf("Data read: %s\n", ValueStr);
   strcpy(str,ValueStr);
 //  str = ValueStr;
   return 0;
}
//---------------------------------------------------------------------------
int deviceGPIB::checkIDN(char *buf)
{
  int i;
  i = writeCommandInstrument("*IDN?\n");
  if (i) {
	 return i;
  }
  i = readAnswerInstrument(buf);
  if (i) {
	return i;
  }
  return 0;
}
//---------------------------------------------------------------------------
int deviceGPIB::resetInstument()
{
  int i;
  i = writeCommandInstrument("*RST\n");
  if (i) {
	 return i;
  }

  return 0;
}
//---------------------------------------------------------------------------
instrumentPowerMeter::instrumentPowerMeter()
{

}
//---------------------------------------------------------------------------
instrumentPowerMeter::~instrumentPowerMeter()
{

}
//---------------------------------------------------------------------------
int instrumentPowerMeter::setUnit(int channel,int unit)
{
  // String ch;
  int a;
  char cmd[128]={":SENSE1:CHAN"};
  if(channel==1)
	strcat(cmd,"1");
  else
	strcat(cmd,"2");

  if(unit==dBm)
	strcat(cmd,":POW:UNIT 0\n");
  else
	strcat(cmd,":POW:UNIT 1\n");

  // ch = IntToStr(channel);
  a = writeCommandInstrument(cmd);
  return a;
}
//---------------------------------------------------------------------------
int instrumentPowerMeter::setWavelenght(int channel,char *buf)
{
   int a;
   char cmd[128]={":SENSE1:CHAN"};
   if(channel==1)
	 strcat(cmd,"1");
   else
	 strcat(cmd,"2");

   strcat(cmd,":POW:WAV ");
   strcat(cmd,buf);
   strcat(cmd,"NM\n");

   a = writeCommandInstrument(cmd);

   return a;

}
//---------------------------------------------------------------------------
int instrumentPowerMeter::returnPower(int channel,char *buf)
{
  int a;
  char cmd[128]={"FETCH1:CHAN"};
  if(channel==1)
	strcat(cmd,"1");
  else
	strcat(cmd,"2");

  strcat(cmd,":POW?\n");
  a = writeCommandInstrument(cmd);
  if(a)
	return a;

  a = readAnswerInstrument(buf);
  if (a) {
	return a;
  }
  return 0;

}
//---------------------------------------------------------------------------
int instrumentPowerMeter::opticalSwitch(int channel)
{
   int a;
   char cmd[128]={"ROUT4:CHAN1 A,"};
   char b[2]={0,0};
   b[0] = char(channel+'0');
   strcat(cmd,b);
   strcat(cmd,"\n");

   a = writeCommandInstrument(cmd);
   if(a)
	 return a;

   return 0;
}
//---------------------------------------------------------------------------
instrumentTunableLaserSource::instrumentTunableLaserSource()
{

}
//---------------------------------------------------------------------------
instrumentTunableLaserSource::~instrumentTunableLaserSource()
{

}
//---------------------------------------------------------------------------
instrumentTunableLaserSource::enable()
{
   int a;
   a = writeCommandInstrument("ENAB 1\n");

   return a;
}
//---------------------------------------------------------------------------
instrumentTunableLaserSource::disable()
{
   int a;
   a = writeCommandInstrument("ENAB 0\n");

   return a;
}
//---------------------------------------------------------------------------
instrumentTunableLaserSource::setWavelenght(char *buf)
{
   int a;
   char cmd[128]={"WAV "};

   strcat(cmd,buf);
   strcat(cmd,"\n");

   a = writeCommandInstrument(cmd);
   return a;

}
//---------------------------------------------------------------------------
instrumentWaveLenghtMeter::instrumentWaveLenghtMeter()
{

}
//---------------------------------------------------------------------------
instrumentWaveLenghtMeter::~instrumentWaveLenghtMeter()
{

}
//---------------------------------------------------------------------------
int instrumentWaveLenghtMeter::MeasurePowerArray(int *num, double *pow,double *wl)
{
  int i,j,l;
  char bufPw[1024];
  char bufWl[1024];
  char buf[32];
  i = writeCommandInstrument(":MEAS:ARR:POW?\n");
  if (i) {
	 return i;
  }

  i = readAnswerInstrument(bufPw);
  if (i) {
	return i;
  }

 i = writeCommandInstrument(":FETCH:ARR:POW:WAV?\n");
  if (i) {
	 return i;
  }

	i = readAnswerInstrument(bufWl);
  if (i) {
	return i;
  }

  i=0;
  j=0;
  while(bufPw[i]!=',')
  {
	 buf[j++] = bufPw[i++];
  }
  buf[j]=0;

  i++;
  l = i;

  *num = atoi(buf);

  if(*num>0)
  {

	  for(int k=0;k<*num;k++)
	  {
		 j=0;
		 while( (bufPw[i]!=','))
		 {
			if(bufPw[i]==0) break;

			buf[j++] = bufPw[i++];
		 }
		 i++;
		 buf[j] = 0;
		 pow[k] = atof(buf);
	  }

	  i = l;
	  for(int k=0;k<*num;k++)
	  {
		 j=0;
		 while( (bufWl[i]!=','))
		 {
			if(bufWl[i]==0) break;

			buf[j++] = bufWl[i++];
		 }
		 i++;
		 buf[j] = 0;
		 wl[k] = atof(buf);
	  }

  }



  return 0;

}
