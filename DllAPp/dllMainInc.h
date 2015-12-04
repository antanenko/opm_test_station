#ifndef DLLMAININC_H
#define DLLMAININC_H


#define GPIB0        0               // Board handle

#define INSTR_ARRAYSIZE          1024     // Size of read buffer

#define PRIMARY_ADDR_OF_SCOPE 10     // Primary address of device
#define PRIMARY_ADDR_OF_LASER 21     // Primary address of device
#define NO_SECONDARY_ADDR     0     // Secondary address of device
#define TIMEOUT               T10s  // Timeout value = 10 seconds
#define EOTMODE               1     // Enable the END message
#define EOSMODE               0     // Disable the EOS mode


#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) int init(const int a);




__declspec(dllexport) class deviceGPIB {
public:
	__declspec(dllexport) deviceGPIB();
	__declspec(dllexport)  ~deviceGPIB();
	__declspec(dllexport) int GPIBInit();
	__declspec(dllexport) int GPIBDisconnect();

	__declspec(dllexport) void setAdressGPIB(int adr);
	__declspec(dllexport) void setAdressInstrument(int primAdr,int secondAdr);

	__declspec(dllexport) int instrumnetConnect();

	__declspec(dllexport) int checkIDN(char *buf);
	__declspec(dllexport) int resetInstument();
private:
	int  gpibAdress;
	int  Dev;
	int  primaryAdress;
	int  secondaryAdress;
	char ValueStr[INSTR_ARRAYSIZE+1];
protected:
	__declspec(dllexport) int writeCommandInstrument(const char *cmnd);
	__declspec(dllexport) int readAnswerInstrument(char *str);

};

#define dBm 0
#define WATT 1


__declspec(dllexport) class instrumentPowerMeter : public deviceGPIB
{
public:
   __declspec(dllexport) instrumentPowerMeter();
   __declspec(dllexport) ~instrumentPowerMeter();

   __declspec(dllexport) int setUnit(int channel,int unit);
   __declspec(dllexport) int returnPower(int channel,char *buf);
   __declspec(dllexport) int setWavelenght(int channel,char *buf);

   __declspec(dllexport) int opticalSwitch(int channel);
};

__declspec(dllexport) class instrumentTunableLaserSource : public deviceGPIB
{
public:
   __declspec(dllexport) instrumentTunableLaserSource();
   __declspec(dllexport) ~instrumentTunableLaserSource();

   __declspec(dllexport) int enable();
   __declspec(dllexport) int disable();
   __declspec(dllexport) int setWavelenght(char *buf);


};


__declspec(dllexport) class instrumentWaveLenghtMeter : public deviceGPIB
{
public:
   __declspec(dllexport) instrumentWaveLenghtMeter();
   __declspec(dllexport) ~instrumentWaveLenghtMeter();

  __declspec(dllexport) int MeasurePowerArray(int *num, double *pow,double *wl);
//   __declspec(dllexport) int disable();
//   __declspec(dllexport) int setWavelenght(char *buf);


};


#ifdef __cplusplus
}
#endif



#endif // DLLMAININC_H

