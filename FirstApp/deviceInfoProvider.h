//---------------------------------------------------------------------------

#ifndef deviceInfoProviderH
#define deviceInfoProviderH
//---------------------------------------------------------------------------
#include <memory>
#include <vector>
#include <windows.h>
#include <Classes.hpp>
#include "hardwareInterface.h"
#include "PlatformSpecificLibraryHandle.h"
#include "device/device.hpp"
#include "DeviceRepresentation.h"


class DeviceInfoProviderException : public Exception
{
public:
	DeviceInfoProviderException(const std::string& message)
		:	Exception(message.c_str()) {};
};

class DeviceInfoProvider
{
	typedef void* (*CreateDeviceInfoProviderPtr)(void* hardwareInterfaceHandle);
	typedef void (*FreeDeviceInfoProviderPtr)(void* deviceInfoHandle);
	typedef uint32_t (*FindConnectedDevicesPtr)(void* deviceInfoHandle);
	typedef uint32_t (*GetConnectedDevicesNumberPtr)(void* );
	typedef uint32_t (*GetDeviceSerialNumberPtr)(void*, size_t deviceIndex, char* buff, size_t buffLen);
	typedef uint32_t (*GetDeviceModelPtr)(void*, size_t deviceIndex, char* buff, size_t buffLen);
	typedef void* DeviceInfoHandle;
public:
	DeviceInfoProvider(const std::string& opmLibraryPath);
	~DeviceInfoProvider();
public:
	size_t getAttachedDevicesCount();
	Measurer* connectToDevice(size_t deviceIndex);
    Measurer* connectToDeviceTcpIp(const std::string& addr);
	DeviceRepresentationList getDevicesList();
	size_t findAttachedDevices();
	void DeviceInfoProvider::releasePort();
private:
	DeviceInfoHandle createDeviceInfoProvider(LibraryHandle hiHandle);
	void freeDeviceInfoProvider(DeviceInfoHandle devInfoHandle);
	std::string getDeviceSerialNumber(DeviceInfoHandle devInfoHandle, size_t index);
	std::string getDeviceModel(DeviceInfoHandle devInfoHandle, size_t index);
	HINSTANCE opmLibraryHandle;
	std::auto_ptr<HardwareInterface> hardwareInterface;
	std::auto_ptr<DeviceBuilder> deviceBuilder;
    DeviceRepresentationList devicesList;
};

#endif
