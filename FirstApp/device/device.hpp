#ifndef DEVICE_HPP
#define DEVICE_HPP

/// std
#include <cassert>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdint.h>

/// optixsoft
#include <headers/iit_def.h>
#include <headers/os.h>
#include <util/tlogfile.h>

#include "HardwareInterface.h"
#include <PlatformSpecificLibraryHandle.h>


struct OpmException : public std::runtime_error
{
	explicit OpmException(const std::string& what)
	: std::runtime_error(what) { }
};

struct DeviceException : public OpmException
{
	explicit DeviceException(const std::string& what)
	: OpmException(what) { }
};

///
///
///
struct DlGuard
{
	DlGuard(HINSTANCE handle = 0) : handle(handle) {}
	~DlGuard() { if(handle) FreeLibrary(handle); }
	void reset(HINSTANCE handle) { this->handle = handle; }
	HINSTANCE handle;
};

///
///
///
struct OpmLibrary
{
	template<typename FuncType>
	FuncType getLibraryFunctionPtr(const std::string& funcName)
	{
		FuncType ret = (FuncType)GetProcAddress(opmLib, funcName.c_str());
		if(!ret) throwUnableLocateFuncException(funcName.c_str());
		return ret;
	}
	OpmLibrary(LibraryHandle handle)
		:	opmLib(handle)
	{
		connectToDevicePtr = getLibraryFunctionPtr<ConnectToDeviceFunc>("_ConnectToDevice");
		freePortPtr = getLibraryFunctionPtr<FreePortFunc>("_FreePort");
		initOpmPtr = getLibraryFunctionPtr<InitOpmFunc>("_InitOpm");
		writePendingConfigsPtr = getLibraryFunctionPtr<WritePendingConfigsFunc>("_WritePendingConfigs");
		getWavelengthsNumPtr = getLibraryFunctionPtr<GetWavelengthsNumFunc>("_GetWavelengthsNum");
		getWavelengthPtr = getLibraryFunctionPtr<GetWavelengthFunc>("_GetWavelength");
		getCurrWavelengthPtr = getLibraryFunctionPtr<GetCurrWavelengthFunc>("_GetCurrWavelength");
		switchWavelengthByIndexPtr = getLibraryFunctionPtr<SwitchWavelengthByIndexFunc>("_SwitchWavelengthByIndex");
		switchWavelengthByValuePtr = getLibraryFunctionPtr<SwitchWavelengthByValueFunc>("_SwitchWavelengthByValue");
		getModesNumPtr = getLibraryFunctionPtr<GetModesNumFunc>("_GetModesNum");
		switchModePtr = getLibraryFunctionPtr<SwitchModeFunc>("_SwitchMode");
		getModeNamePtr = getLibraryFunctionPtr<GetModeNameFunc>("_GetModeName");
		getCurrModeIndexPtr = getLibraryFunctionPtr<GetCurrModeIndexFunc>("_GetCurrModeIndex");
		readPowerPtr = getLibraryFunctionPtr<ReadPowerFunc>("_ReadPower");
		calibrateZeroPtr = getLibraryFunctionPtr<CalibrateZeroFunc>("_CalibrateZero");
		calibratePtr = getLibraryFunctionPtr<CalibrateFunc>("_Calibrate");
		flashConfigPtr = getLibraryFunctionPtr<FlashConfigFunc>("_FlashConfig");
		getPhotodiodesNumPtr = getLibraryFunctionPtr<GetPhotodiodesNumFunc>("_GetPhotodiodesNum");
		getCurrPhotodiodePtr = getLibraryFunctionPtr<GetCurrPhotodiodeFunc>("_GetCurrPhotodiode");
		switchPhotodiodeWavelengthPtr = getLibraryFunctionPtr<SwitchPhotodiodeWavelengthFunc>("_SwitchPhotodiodeWavelength");
		getPhotodiodeWavelengthsNumPtr = getLibraryFunctionPtr<GetPhotodiodeWavelengthsNumFunc>("_GetPhotodiodeWavelengthsNum");
		getPhotodiodeWavelengthPtr = getLibraryFunctionPtr<GetPhotodiodeWavelengthFunc>("_GetPhotodiodeWavelength");
		switchWaveIdModePtr = getLibraryFunctionPtr<SwitchWaveIdModeFunc>("_SwitchWaveIdMode");
		getDetectedWavelengthPtr = getLibraryFunctionPtr<GetDetectedWavelengthFunc>("_GetDetectedWavelength");
		waveIdModeActivePtr = getLibraryFunctionPtr<WaveIdModeActiveFunc>("_WaveIdModeActive");
		waveIdSignalPresentPtr = getLibraryFunctionPtr<WaveIdSignalPresentFunc>("_WaveIdSignalPresent");
		freshMeasureResultReceivedPtr = getLibraryFunctionPtr<FreshMeasureResultReceivedFunc>("_FreshMeasureResultReceived");
		getOpticalModuleSerialNumberPtr = getLibraryFunctionPtr<GetOpticalModuleSerialNumberFunc>("_GetOpticalModuleSerialNumber");
		getDetectedModulationFrequencyPtr = getLibraryFunctionPtr<GetDetectedModulationFrequencyFunc>("_GetDetectedModulationFrequency");
		getMemoryCellsNumPtr = getLibraryFunctionPtr<GetMemoryCellsNumFunc>("_GetMemoryCellsNum");
		getMemoryCellSizePtr = getLibraryFunctionPtr<GetMemoryCellSizeFunc>("_GetMemoryCellSize");
		getRawResultsPtr = getLibraryFunctionPtr<GetRawResultsFunc>("_GetRawResults");
		eraseMemoryCellPtr = getLibraryFunctionPtr<EraseMemoryCellFunc>("_EraseMemoryCell");
		// OLS
		initOlsPtr = getLibraryFunctionPtr<InitOlsFunc>("_InitOls");
		getOlsNumPtr = getLibraryFunctionPtr<GetOlsNumFunc>("_GetOlsNum");
		getOlsWavelengthPtr = getLibraryFunctionPtr<GetOlsWavelengthFunc>("_GetOlsWavelength");
		switchOlsPtr = getLibraryFunctionPtr<SwitchOlsFunc>("_SwitchOls");
		getOlsModePtr = getLibraryFunctionPtr<GetOlsModeFunc>("_GetOlsMode");
		disableOlsPtr = getLibraryFunctionPtr<DisableOlsFunc>("_DisableOls");
		isOlsEnabledPtr = getLibraryFunctionPtr<IsOlsEnabledFunc>("_IsOlsEnabled");
	}

	typedef void* PortHandle;
	PortHandle connectToDevice(void* hardwareInterface, void* logFile)
	{
		assert(hardwareInterface);
		assert(logFile);
		assert(connectToDevicePtr);
		return connectToDevicePtr(hardwareInterface, logFile);
	}
    void freePort(PortHandle port)
    {
        freePortPtr(port);
    }
	typedef void* OpmHandle;
	typedef void* OlsHandle;
	static const uint32_t ContinuousOls = 1;
	static const uint32_t PulseOls = 2;

	OpmHandle initOpm(PortHandle port, const char* iniPath, void* logFile)
	{
		assert(port);
		assert(iniPath);
		assert(logFile);
		assert(initOpmPtr);
		return initOpmPtr(port, iniPath, logFile);
	}
	
	uint32_t writePendingConfigs(OpmHandle opm)
	{
		assert(opm);
		assert(writePendingConfigsPtr);
		return writePendingConfigsPtr(opm);
	}

	uint32_t getWavelengthsNum(OpmHandle opm) const
	{
		assert(opm);
		assert(getWavelengthsNumPtr);
		return getWavelengthsNumPtr(opm);
	}

	uint32_t getPhotodiodesNum(OpmHandle opm) const
	{
		assert(opm);
		assert(getPhotodiodesNumPtr);
		return getPhotodiodesNumPtr(opm);
	}

	int getCurrPhotodiode(OpmHandle opm) const
	{
		assert(opm);
		assert(getCurrPhotodiodePtr);
		return getCurrPhotodiodePtr(opm);
	}

	uint32_t getWavelength(OpmHandle opm, uint32_t index) const
	{
		assert(opm);
		assert(getWavelengthPtr);
		return getWavelengthPtr(opm, index);
	}	

	int getCurrWavelength(OpmHandle opm) const
	{
		assert(opm);
		assert(getCurrWavelengthPtr);
		return getCurrWavelengthPtr(opm);
	}

	uint32_t switchWavelengthByIndex(OpmHandle opm, uint32_t index)
	{
		assert(opm);
		assert(switchWavelengthByIndexPtr);
		return switchWavelengthByIndexPtr(opm, index);
	}

	uint32_t switchWavelengthByValue(OpmHandle opm, uint32_t valueNm)
	{
		assert(opm);
		assert(switchWavelengthByValuePtr);
		return switchWavelengthByValuePtr(opm, valueNm);
	}

	uint32_t getModesNum(OpmHandle opm)
	{
		assert(opm);
		assert(getModesNumPtr);
		return getModesNumPtr(opm);
	}

	uint32_t switchMode(OpmHandle opm, uint32_t index)
	{
		assert(opm);
		assert(switchModePtr);
		return switchModePtr(opm, index);
	}

	uint32_t getModeName(OpmHandle opm, uint32_t modeIndex,
						 char* name, uint32_t nameLen)
	{
		assert(opm);
		assert(getModeNamePtr);
		assert(name);
		assert(nameLen);
		return getModeNamePtr(opm, modeIndex, name, nameLen);
	}

	int getCurrModeIndex(OpmHandle opm)
	{
		assert(opm);
		assert(getCurrModeIndexPtr);
		return getCurrModeIndexPtr(opm);
	}

	uint32_t readPower(OpmHandle opm, double* power) const
	{
		assert(opm);
		assert(power);
		assert(readPowerPtr);
		return readPowerPtr(opm, power);
	}

	uint32_t calibrateZero(OpmHandle opm)
	{
		assert(opm);
		assert(calibrateZeroPtr);
		return calibrateZeroPtr(opm);
	}

	uint32_t calibrate(OpmHandle opm, double measuredPower, double actualPower)
	{
		assert(opm);
		assert(calibratePtr);
		return calibratePtr(opm, measuredPower, actualPower);
	}

	uint32_t flashConfig(OpmHandle opm, const char* config)
	{
		assert(opm);
		assert(config);
		assert(flashConfigPtr);
		return flashConfigPtr(config);
	}
	uint32_t switchPhotodiodeWavelength(OpmHandle opm, int photodiode, int wavelength) const
	{
		assert(opm);
		assert(switchPhotodiodeWavelengthPtr);
		return switchPhotodiodeWavelengthPtr(opm, photodiode, wavelength);
	}

	uint32_t getPhotodiodeWavelengthsNum(OpmHandle opm, int photodiode)
	{
		assert(opm);
		assert(getPhotodiodeWavelengthsNumPtr);
		return getPhotodiodeWavelengthsNumPtr(opm, photodiode);
	}

	uint32_t getPhotodiodeWavelength(OpmHandle opm, int photodiode, int wavelength)
	{
		assert(opm);
		assert(getPhotodiodeWavelengthPtr);
		return getPhotodiodeWavelengthPtr(opm, photodiode, wavelength);
	}
	uint32_t switchWaveIdMode(OpmHandle opm, bool enabled) const
	{
		assert(opm);
		assert(switchWaveIdModePtr);
		return switchWaveIdModePtr(opm, enabled ? 1 : 0);
	}
	uint32_t getDetectedWavelength(OpmHandle opm) const
	{
		assert(opm);
		assert(getDetectedWavelengthPtr);
		return getDetectedWavelengthPtr(opm);
	}
	bool waveIdModeActive(OpmHandle opm) const
	{
		assert(opm);
		return (waveIdModeActivePtr(opm) != 0);
	}

	bool waveIdSignalPresent(OpmHandle opm) const
	{
		assert(opm);
		return (waveIdSignalPresentPtr(opm) != 0);
	}

	bool freshMeasureResultReceived(OpmHandle opm) const
	{
		assert(opm);
		return (freshMeasureResultReceivedPtr(opm) != 0);
	}

	unsigned getOpticalModuleSerialNumber(OpmHandle opm) const
	{
		assert(opm);
		return getOpticalModuleSerialNumberPtr(opm);
	}

	unsigned getDetectedModulationFrequency(OpmHandle opm) const
	{
		assert(opm);
		return getDetectedModulationFrequencyPtr(opm);
	}
	unsigned getMemoryCellsNum(OpmHandle opm) const
	{
		assert(opm);
		return getMemoryCellsNumPtr(opm);
	}
	unsigned getMemoryCellSize(OpmHandle opm) const
	{
		assert(opm);
		return getMemoryCellSizePtr(opm);
	}
	uint32_t getRawResults(OpmHandle opm, size_t firstCell, size_t lastCell,
		unsigned char* buffer, size_t length) const
	{
		assert(opm);
		return getRawResultsPtr(opm, firstCell, lastCell, buffer, length);
	}

	uint32_t eraseMemoryCell(OpmHandle opm, size_t cellIndex)
	{
		assert(opm);
		return eraseMemoryCellPtr(opm, cellIndex);
	}

	//OLS
	OlsHandle initOls(PortHandle port, void* logFile)
	{
		assert(port);
		assert(logFile);
		assert(initOlsPtr);
		return initOlsPtr(port, logFile);
	}

	uint32_t getOlsNum(OlsHandle ols) const
	{
		assert(ols);
		assert(getOlsNumPtr);
		return getOlsNumPtr(ols);
	}
	
	uint32_t getOlsWavelength(OlsHandle ols, uint32_t index) const
	{
		assert(ols);
		assert(index < getOlsNum(ols));
		assert(getOlsWavelengthPtr);
		return getOlsWavelengthPtr(ols, index);
	}

	uint32_t switchOls(OlsHandle ols, uint32_t index, uint32_t mode, uint32_t frequencyIndex)
	{
		assert(ols);
		assert(index < getOlsNum(ols));
		assert(switchOlsPtr);
		return switchOlsPtr(ols, index, mode, frequencyIndex);
	}
	
	uint32_t getOlsMode(OlsHandle ols, uint32_t index) const
	{
		assert(ols);
		assert(index < getOlsNum(ols));
		assert(getOlsModePtr);
		return getOlsModePtr(ols, index);
	}
	
	uint32_t disableOls(OlsHandle ols)
	{
		assert(ols);
		assert(disableOlsPtr);
		return disableOlsPtr(ols);
	}
	
	uint32_t isOlsEnabled(OlsHandle ols, uint32_t index) const
	{
		assert(ols);
		assert(index < getOlsNum(ols));
		return isOlsEnabledPtr(ols, index);
	}

private:
	void throwUnableLocateFuncException(const std::string& funcName)
	{
		throw DeviceException(std::string("Was unable to locate ") +
			funcName + std::string(" in opm library"));
	}
	LibraryHandle opmLib;

	typedef void* (*ConnectToDeviceFunc)(void*, void*);
	ConnectToDeviceFunc connectToDevicePtr;
    typedef void (*FreePortFunc)(PortHandle);
    FreePortFunc freePortPtr;
	typedef void* (*InitOpmFunc)(void*, const char*, void*);
	InitOpmFunc initOpmPtr;	

	typedef uint32_t (*WritePendingConfigsFunc)(OpmHandle);
	WritePendingConfigsFunc writePendingConfigsPtr;

	typedef uint32_t (*GetWavelengthsNumFunc)(OpmHandle);
	GetWavelengthsNumFunc getWavelengthsNumPtr;

	typedef uint32_t (*GetWavelengthFunc)(OpmHandle, uint32_t);
	GetWavelengthFunc getWavelengthPtr;

	typedef int (*GetCurrWavelengthFunc)(OpmHandle);
	GetCurrWavelengthFunc getCurrWavelengthPtr;

	typedef uint32_t (*ReadPowerFunc)(OpmHandle, double*);
	ReadPowerFunc readPowerPtr;

	typedef uint32_t (*CalibrateZeroFunc)(OpmHandle);
	CalibrateZeroFunc calibrateZeroPtr;

	typedef uint32_t (*CalibrateFunc)(OpmHandle, double, double);
	CalibrateFunc calibratePtr;

	typedef uint32_t (*FlashConfigFunc)(const char*);
	FlashConfigFunc flashConfigPtr;

	typedef uint32_t (*SwitchWavelengthByIndexFunc)(OpmHandle, uint32_t);
	SwitchWavelengthByIndexFunc switchWavelengthByIndexPtr;

	typedef uint32_t (*SwitchWavelengthByValueFunc)(OpmHandle, uint32_t);
	SwitchWavelengthByValueFunc switchWavelengthByValuePtr;

	typedef uint32_t (*GetModesNumFunc)(OpmHandle);
	GetModesNumFunc getModesNumPtr;

	typedef uint32_t (*SwitchModeFunc)(OpmHandle, uint32_t);
	SwitchModeFunc switchModePtr;

	typedef uint32_t (*GetModeNameFunc)(OpmHandle, uint32_t, char* , uint32_t);
	GetModeNameFunc getModeNamePtr;

	typedef int (*GetCurrModeIndexFunc)(OpmHandle);
	GetCurrModeIndexFunc getCurrModeIndexPtr;

	typedef uint32_t (*GetPhotodiodesNumFunc)(OpmHandle);
	GetPhotodiodesNumFunc getPhotodiodesNumPtr;

	typedef int (*GetCurrPhotodiodeFunc)(OpmHandle);
	GetCurrPhotodiodeFunc getCurrPhotodiodePtr;

	typedef uint32_t (*SwitchPhotodiodeWavelengthFunc)(OpmHandle, int, int);
	SwitchPhotodiodeWavelengthFunc switchPhotodiodeWavelengthPtr;

	typedef uint32_t (*GetPhotodiodeWavelengthsNumFunc)(OpmHandle, int);
	GetPhotodiodeWavelengthsNumFunc getPhotodiodeWavelengthsNumPtr;

	typedef uint32_t (*GetPhotodiodeWavelengthFunc)(OpmHandle, int, int);
	GetPhotodiodeWavelengthFunc getPhotodiodeWavelengthPtr;

	typedef uint32_t (*SwitchWaveIdModeFunc)(OpmHandle, int);
	SwitchWaveIdModeFunc switchWaveIdModePtr;

	typedef uint32_t (*GetDetectedWavelengthFunc)(OpmHandle);
	GetDetectedWavelengthFunc getDetectedWavelengthPtr;

	typedef uint32_t (*WaveIdModeActiveFunc)(OpmHandle);
	WaveIdModeActiveFunc waveIdModeActivePtr;

	typedef uint32_t (*WaveIdSignalPresentFunc)(OpmHandle);
	WaveIdSignalPresentFunc waveIdSignalPresentPtr;

	typedef uint32_t (*FreshMeasureResultReceivedFunc)(OpmHandle);
	FreshMeasureResultReceivedFunc freshMeasureResultReceivedPtr;

	typedef uint32_t (*GetOpticalModuleSerialNumberFunc)(OpmHandle);
	GetOpticalModuleSerialNumberFunc getOpticalModuleSerialNumberPtr;

	typedef uint32_t (*GetDetectedModulationFrequencyFunc)(OpmHandle);
	GetDetectedModulationFrequencyFunc getDetectedModulationFrequencyPtr;

	typedef uint32_t (*GetMemoryCellsNumFunc)(OpmHandle);
	GetMemoryCellsNumFunc getMemoryCellsNumPtr;

	typedef uint32_t (*GetMemoryCellSizeFunc)(OpmHandle);
	GetMemoryCellSizeFunc getMemoryCellSizePtr;

	typedef uint32_t (*GetRawResultsFunc)(OpmHandle, uint32_t, uint32_t,
		unsigned char*, uint32_t);
	GetRawResultsFunc getRawResultsPtr;

	typedef uint32_t (*EraseMemoryCellFunc)(OpmHandle, uint32_t);
	EraseMemoryCellFunc eraseMemoryCellPtr;
	//
	//OLS
	typedef OlsHandle (*InitOlsFunc)(PortHandle port, void* logFile);
	InitOlsFunc initOlsPtr;
	typedef uint32_t (*GetOlsNumFunc)(OlsHandle ols);
	GetOlsNumFunc getOlsNumPtr;
	typedef uint32_t (*GetOlsWavelengthFunc)(OlsHandle ols, uint32_t index);
	GetOlsWavelengthFunc getOlsWavelengthPtr;
	typedef uint32_t (*SwitchOlsFunc)(OlsHandle ols, uint32_t index, uint32_t mode, uint32_t frequencyIndex);
	SwitchOlsFunc switchOlsPtr;
	typedef uint32_t (*GetOlsModeFunc)(OlsHandle ols, uint32_t index);
	GetOlsModeFunc getOlsModePtr;
	typedef uint32_t (*DisableOlsFunc)(OlsHandle ols);
	DisableOlsFunc disableOlsPtr;
	typedef uint32_t (*IsOlsEnabledFunc)(OlsHandle ols, uint32_t index);
	IsOlsEnabledFunc isOlsEnabledPtr;


};


///
///
///
class Measurer
{
public:
	typedef std::vector<unsigned char> MemoryBlock;
	virtual ~Measurer() { }
	virtual void writePendingConfigs() = 0;
	virtual size_t getWavelengthsNum() const = 0;
	virtual unsigned getWavelength(size_t index) const = 0;
	virtual int getCurrWavelength() const = 0;
	virtual int getWavelengthIndexByValue(unsigned nanometers) const = 0;
	virtual size_t getModesNum() const = 0;
	virtual void switchMode(uint32_t modeIndex) const = 0;
	virtual std::string getModeName(uint32_t modeIndex) const = 0;
	virtual int getCurrModeIndex() const = 0;
	virtual void switchWavelengthByIndex(size_t index) const = 0;
	virtual void switchWavelengthByValue(size_t nanometers) const = 0;
	virtual double readPower() const = 0;
	virtual void calibrateZero() = 0;
	virtual void calibrate(double measuredPower, double actualPower) = 0;
	/// TODO: Move to other class
	virtual double getReferenceLevel(size_t wavelengthIndex) const = 0;
	/// TODO: Move to other class
	virtual void setReferenceLevel(size_t wavelengthIndex, double power) = 0;
	virtual void flashConfig(const std::string& config) = 0;
	virtual size_t getPhotodiodesNum() const = 0;
	virtual int getCurrPhotodiode() const = 0;
	virtual void switchPhotodiodeWavelength(int photodiode, int wavelength) const = 0;
	virtual size_t getPhotodiodeWavelengthsNum(int photodiode) const = 0;
	virtual unsigned getPhotodiodeWavelength(int photodiode, int wavelength) const = 0;
	virtual void switchWaveIdMode(bool enabled) const = 0;
	virtual unsigned getDetectedWavelength() const = 0;
	virtual bool waveIdModeActive() const = 0;
	virtual bool waveIdSignalPresent() const = 0;
	virtual bool freshMeasureResultReceived() const = 0;
	virtual unsigned getOpticalModuleSerialNumber() const = 0;
	virtual unsigned getDetectedModulationFrequency() const = 0;
	virtual size_t getMemoryCellsNum() const = 0;
	virtual MemoryBlock getRawResults(size_t firstCell, size_t lastCell) const = 0;
	virtual void eraseMemoryCell(size_t cellIndex) = 0;
};

///
///
///
class ActualMeasurer : public Measurer
{
public:
	ActualMeasurer(OpmLibrary& library, OpmLibrary::PortHandle port, const std::string&
		iniDirPath, TLogFile& logFile) 
	: library(library), opm(0)
	{ 
		assert(port);
		opm = library.initOpm(port, iniDirPath.c_str(), &logFile);
		if(!opm) throw DeviceException("Was unable to initialize opm");
		referenceLevels.resize(getWavelengthsNum());
	}

	virtual void writePendingConfigs()
	{
		const uint32_t success = library.writePendingConfigs(opm);
		if(!success) throw DeviceException("Error during writing pending configs");
	}

	virtual size_t getPhotodiodesNum() const
	{
		return library.getPhotodiodesNum(opm);
	}
	virtual int getCurrPhotodiode() const
	{
		return library.getCurrPhotodiode(opm);
	}
	virtual size_t getWavelengthsNum() const
	{
		return library.getWavelengthsNum(opm);
 	}
	virtual unsigned getWavelength(size_t index) const
	{
		assert(index < getWavelengthsNum());
		return library.getWavelength(opm, index);
	}
	virtual int getCurrWavelength() const
	{
		return library.getCurrWavelength(opm);
	}
	virtual int getWavelengthIndexByValue(unsigned nanometers) const
	{
		int ret = -1;
		const int wavelengthNum = getWavelengthsNum();
		for(int index = 0; index < wavelengthNum; index++)
		{
			if(nanometers == getWavelength(index))
			{
				ret = index;
				break;
			}
		}
		return ret;
	}

	virtual void switchWavelengthByIndex(size_t index) const
	{
		assert(index < getWavelengthsNum());
		const uint32_t success = library.switchWavelengthByIndex(opm, index);
		if(!success) throw DeviceException(
					"Error during switching wavelength by index");
	}

	virtual void switchWavelengthByValue(size_t nanometers) const
	{
		const uint32_t success = library.switchWavelengthByValue(
					opm, nanometers);
		if(!success) throw DeviceException(
					"Error during switching wavelength by value");
	}

	virtual void switchPhotodiodeWavelength(int photodiode, int wavelength) const
	{
		assert(photodiode < getPhotodiodesNum() && wavelength < getWavelengthsNum());
		const uint32_t success = library.switchPhotodiodeWavelength(
					opm, photodiode, wavelength);
		if(!success) throw DeviceException(
					"Error during photodiode and wavelength switching");
	}

	virtual size_t getModesNum() const
	{
		const uint32_t modesNum = library.getModesNum(opm);
		if(modesNum == 0) throw DeviceException(
					"No operation mode found for the OPM device.\n"
					"Unable to continue measuring");
		return modesNum;
	}

	virtual void switchMode(size_t modeIndex) const
	{
		assert(modeIndex < getModesNum());
		const unsigned int success = library.switchMode(opm, modeIndex);
		if(!success) throw DeviceException(
					"Unable to switch device operation mode");

	}

	virtual std::string getModeName(uint32_t modeIndex) const
	{
		char nameBuff[100] = {0};
		const uint32_t charsNum = library.getModeName(
					opm, modeIndex, nameBuff, sizeof(nameBuff));
		if(!charsNum)
		{
			std::stringstream ss;
			ss << "Unable to retrieve device operation "
				  "mode with index " << modeIndex << ".";
			throw DeviceException(ss.str());
		}
		return std::string(nameBuff);
	}

	virtual int getCurrModeIndex() const
	{
		int currIndex = library.getCurrModeIndex(opm);
		return currIndex;
	}

	virtual double readPower() const
	{
		double result = 0.0;
		const uint32_t success = library.readPower(opm, &result);
		if(!success) throw DeviceException("Error during power reading");
		return result;
	}

	virtual void calibrateZero() 
	{
		const uint32_t success = library.calibrateZero(opm);
		if(!success) throw DeviceException("Error during zero calibration");
	}

	virtual void calibrate(double measuredPower, double actualPower)
	{
		const uint32_t success = library.calibrate(opm, measuredPower, actualPower);
		if(!success) throw DeviceException("Error during calibration");
	}

	virtual double getReferenceLevel(size_t wavelengthIndex) const
	{
		assert(wavelengthIndex < referenceLevels.size());
		return referenceLevels[wavelengthIndex];
	}

	virtual void setReferenceLevel(size_t wavelengthIndex, double power)
	{
		assert(wavelengthIndex < referenceLevels.size());
		referenceLevels[wavelengthIndex] = power;
	}
	virtual void flashConfig(const std::string& config)
	{
		const uint32_t success = library.flashConfig(opm, config.c_str());
		if(!success) throw DeviceException("Error during flashing the configuration file");
	}

	virtual size_t getPhotodiodeWavelengthsNum(int photodiode) const
	{
		assert(photodiode < getPhotodiodesNum());
		return library.getPhotodiodeWavelengthsNum(opm, photodiode);
	}

	virtual unsigned getPhotodiodeWavelength(int photodiode, int wavelength) const
	{
		assert(photodiode < getPhotodiodesNum() &&
			   wavelength < getPhotodiodeWavelengthsNum(photodiode));
		return library.getPhotodiodeWavelength(opm, photodiode, wavelength);
	}
	virtual void switchWaveIdMode(bool enabled) const
	{
		const uint32_t success = library.switchWaveIdMode(opm, enabled);
		if(!success) throw DeviceException(std::string("Failed to switch Wave ID mode ") +
										   (std::string(enabled ? "ON." : "OFF.")));
	}
	virtual unsigned getDetectedWavelength() const
	{
		return library.getDetectedWavelength(opm);
	}

	virtual bool waveIdModeActive() const
	{
		return library.waveIdModeActive(opm);
	}

	virtual bool waveIdSignalPresent() const
	{
		return library.waveIdSignalPresent(opm);
	}

	virtual bool freshMeasureResultReceived() const
	{
		return library.freshMeasureResultReceived(opm);
	}

	virtual unsigned getOpticalModuleSerialNumber() const
	{
		return library.getOpticalModuleSerialNumber(opm);
	}

	virtual unsigned getDetectedModulationFrequency() const
	{
		return library.getDetectedModulationFrequency(opm);
	}
	virtual size_t getMemoryCellsNum() const
	{
		return library.getMemoryCellsNum(opm);
	}
	virtual size_t getMemoryCellSize() const
	{
		return library.getMemoryCellSize(opm);
	}
	virtual MemoryBlock getRawResults(size_t firstCell, size_t lastCell) const
	{
		assert(firstCell <= lastCell);
		const size_t blockLength = getMemoryCellSize() * (lastCell - firstCell + 1);
		MemoryBlock block(blockLength, 0);
		uint32_t ret = library.getRawResults(opm, firstCell, lastCell, &block[0], block.size());
		if(!ret)
		{
			throw DeviceException("Unable to read device memory");
		}
		return block;
	}
	virtual void eraseMemoryCell(size_t cellIndex)
	{
		uint32_t ret = library.eraseMemoryCell(opm, cellIndex);
		if(!ret)
		{
            throw DeviceException("Unable to erase device memory");
        }
	}

private:
	OpmLibrary& library;
	OpmLibrary::OpmHandle opm;
	std::vector<double> referenceLevels;
};

///
///
///
class FakeMeasurer : public Measurer
{
public:
	FakeMeasurer() : currWavelength(0), laserEnabled(false)
	{ 
		referenceLevels.resize(getWavelengthsNum());
	}

	virtual void writePendingConfigs() { }

	virtual size_t getWavelengthsNum() const
	{
		return 3;
	}

	virtual unsigned getWavelength(size_t index) const
	{
		const unsigned ws[] = { 500, 1000, 1500 };
		assert(index < getWavelengthsNum());
		return ws[index];
	}

	virtual int getCurrWavelength() const
	{
		return currWavelength;
	}

	virtual void switchWavelength(size_t index)
	{
		assert(index < getWavelengthsNum());
		this->currWavelength = index;
	}

	virtual double readPower() const
	{
		static const double offsets[] = { 0.01, 0.05, 0.09 };
		static size_t i = -1;
		i += 1;
		double baseValue = 0.0;
		switch(currWavelength)
		{
		case 0: baseValue = -25.1; break;
		case 1: baseValue = -31.2; break;
		case 2: baseValue = -44.7; break;
		default: baseValue = -51.0; break;
		}
		return baseValue - offsets[i % (sizeof(offsets)/sizeof(offsets[0]))];
	}

	virtual void calibrateZero()
	{
		// do nothing
	}

	virtual void calibrate(double /*measuredPower*/, double /*actualPower*/) { }

	virtual void enableLaser(bool enable)
	{
		this->laserEnabled = enable;
	}
	
	virtual bool isLaserEnabled() const
	{
		return laserEnabled;
	}

	virtual double getReferenceLevel() const
	{
		assert(getCurrWavelength() < referenceLevels.size());
		return referenceLevels[getCurrWavelength()];
	}

	virtual void setReferenceLevel(double power)
	{
		assert(getCurrWavelength() < referenceLevels.size());
		referenceLevels[getCurrWavelength()] = power;
	}

private:
	std::vector<double> referenceLevels;
	size_t currWavelength;
	bool laserEnabled;
};



///
/// TODO: We can't throw from the slots!!! Refactor to other error reporting
/// strategy.
///
class Device
{
public:
	enum Mode { Continuous, Pulse };
	class DeviceObserver
	{
	public:
		virtual void laserWasSwitched(size_t index, Device::Mode mode, size_t frequencyIndex) = 0;
		virtual void lasersWasDisabled() = 0;
	};

public:
	Device(DeviceObserver* observer) : observer(observer){}
	virtual ~Device() { }
	virtual size_t getLasersNum() const = 0;
	virtual unsigned getLaserWavelength(size_t index) const = 0;
	virtual Mode getLaserMode(size_t index) const = 0;
	void switchLaser(size_t index, Mode mode, size_t frequencyIndex)
	{
		assert(index < getLasersNum());
		switchLaserImpl(index, mode, frequencyIndex);
		observer->laserWasSwitched(index, mode, frequencyIndex);
	}
	void disableLasers()
	{
		disableLasersImpl();
		observer->lasersWasDisabled();
	}

public:
	virtual bool isLaserEnabled(size_t index) const = 0;

protected:
	DeviceObserver* observer;
private:
	virtual void switchLaserImpl(size_t index, Mode mode, size_t frequencyIndex) = 0;
	virtual void disableLasersImpl() = 0;
};

///
///
///
class ActualDevice : public Device
{
public:
	ActualDevice(DeviceObserver* observer, OpmLibrary& library,
		OpmLibrary::PortHandle port, const std::string& iniDirPath,
			TLogFile& logFile)
		: Device(observer), library(library), ols(0)
	{ 
		assert(port);
		ols = library.initOls(port, &logFile);
		if(!ols) throw DeviceException("Was unable to initialize ols");		
	}
	virtual size_t getLasersNum() const
	{
		return library.getOlsNum(ols);
	}
	virtual unsigned getLaserWavelength(size_t index) const
	{
		const uint32_t wavelen = library.getOlsWavelength(ols, index);
		if(wavelen == 0) throw DeviceException("Error during retreiving laser "
			"wavelength");
		return wavelen;
	}
	virtual Mode getLaserMode(size_t index) const
	{
		return rawModeToMode(library.getOlsMode(ols, index));
	}
	virtual bool isLaserEnabled(size_t index) const
	{
		return library.isOlsEnabled(ols, index);
	}
private:
	virtual void switchLaserImpl(size_t index, Mode mode, size_t frequencyIndex)
	{
		const uint32_t success = library.switchOls(ols, index, modeToRawMode(mode), frequencyIndex);
		if(!success) throw DeviceException("There were error during switching laser"
			" mode");
	}
	virtual void disableLasersImpl()
	{
		const uint32_t success = library.disableOls(ols);
		if(!success) throw DeviceException("Wasn't able to disable all lasers");
	}
	static uint32_t modeToRawMode(Mode mode)
	{
		switch(mode)
		{
		case Continuous: return OpmLibrary::ContinuousOls;
		case Pulse: return OpmLibrary::PulseOls;
		default: assert(false); return OpmLibrary::ContinuousOls;
		}
	}
	static Mode rawModeToMode(uint32_t mode)
	{
		switch(mode)
		{
		case OpmLibrary::ContinuousOls: return Continuous;
		case OpmLibrary::PulseOls: return Pulse;
		default: 
			throw DeviceException("Wrong raw mode specified");
			return Continuous;
		}		
	}

	OpmLibrary& library;
	OpmLibrary::OlsHandle ols;
};

///
///
///
struct DeviceBuilder
{
	DeviceBuilder(LibraryHandle libHandle)
		:	port(0),
			library(new OpmLibrary(libHandle))
	{}
	/// @throw DeviceException if there were major error
	void initOpm(HardwareInterface* hardwareInterface, const std::string& iniDirPath,
		TLogFile& logFile)
	{
		//TODO: move to the HardwareInterface class
		HardwareInterface::Handle hardwarePortHandle = hardwareInterface->getPort();
		port = library->connectToDevice(hardwarePortHandle, &logFile);

		if(!port) throw DeviceException("Was unable to connect to device");
		measurer.reset(new ActualMeasurer(*library, port, iniDirPath, logFile));
		if(measurer.get())
		{
			logFile.Message('U', "Measurer initialized successfully", "");
		}
	}
	/// @return device pointer or null if device wasn't initialized
	Measurer* getMeasurer()
	{
		return measurer.get();
	}
	void release()
	{
		measurer.reset(0);
	}
    typedef int (*ConnectFunc)(void** , char* , long , long );
private:
	typedef std::auto_ptr<OpmLibrary> OpmLibraryPtr;
	OpmLibraryPtr library;
	OpmLibrary::PortHandle port;
	typedef std::auto_ptr<Measurer> MeasurerPtr;
	MeasurerPtr measurer;
};

#endif

