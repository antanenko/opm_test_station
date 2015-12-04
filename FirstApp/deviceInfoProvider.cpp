//---------------------------------------------------------------------------
#pragma hdrstop

#include "deviceInfoProvider.h"
#include <PlatformSpecificFunctionLoader.h>
#include "winUsbHwIntrf.h"
#include "tcpIpHwIntrf.h"
#include "paths.h"

struct OpmLibraryLoadingException : public DeviceInfoProviderException
{
	OpmLibraryLoadingException() : DeviceInfoProviderException(
		"Unable to load OPM dynamic library.") {};

};

struct HardwareInterfaceInitializationException : public DeviceInfoProviderException
{
	HardwareInterfaceInitializationException() :
		DeviceInfoProviderException("Unable to initialize hardware communication interface") {}
};

struct DeviceSearchingException : public DeviceInfoProviderException
{
	DeviceSearchingException() :
		DeviceInfoProviderException("Cannot find connected power meters") {}
};


struct InvalidDevicesNumberException : public DeviceInfoProviderException
{
	InvalidDevicesNumberException() :
		DeviceInfoProviderException("Requested number of connected devices is invalid") {}
};


DeviceInfoProvider::DeviceInfoProvider(const std::string& opmLibraryPath)
	: 	opmLibraryHandle(LoadLibraryA(opmLibraryPath.c_str())),
		hardwareInterface(new WinUsbHardwareInterface())
{
	if(opmLibraryHandle == NULL)
	{
		throw OpmLibraryLoadingException();
	}
	deviceBuilder.reset(new DeviceBuilder(opmLibraryHandle));
	findAttachedDevices();
}

DeviceInfoProvider::~DeviceInfoProvider()
{
	deviceBuilder->release();
	FreeLibrary(opmLibraryHandle);
    opmLibraryHandle = NULL;
}

DeviceInfoProvider::DeviceInfoHandle DeviceInfoProvider::createDeviceInfoProvider(
	LibraryHandle hiHandle)
{
	CreateDeviceInfoProviderPtr func =
		PlatformSpecificFunctionLoader<CreateDeviceInfoProviderPtr>()(opmLibraryHandle,
			"_CreateDeviceInfoProvider");

	DeviceInfoHandle ret = func(hiHandle);
	if(!ret)
	{
		throw HardwareInterfaceInitializationException();
	}
	return ret;
}

void DeviceInfoProvider::freeDeviceInfoProvider(DeviceInfoHandle devInfoHandle)
{
	FreeDeviceInfoProviderPtr func =
		PlatformSpecificFunctionLoader<FreeDeviceInfoProviderPtr>()(opmLibraryHandle,
			"_FreeDeviceInfoProvider");
	func(devInfoHandle);
}

size_t DeviceInfoProvider::findAttachedDevices()
{
	devicesList.clear();
	DeviceInfoHandle devInfoHandle = createDeviceInfoProvider(hardwareInterface->getHandle());
	if(!devInfoHandle)
	{
		throw Exception("Unable to create device enumerator.");
	}
	FindConnectedDevicesPtr func =
		PlatformSpecificFunctionLoader<FindConnectedDevicesPtr>()(opmLibraryHandle,
			"_FindConnectedDevices");
	const uint32_t devicesNumber = func(devInfoHandle);
   	if(devicesNumber == 0xffffffff)
	{
		throw DeviceSearchingException();
	}
	for(size_t deviceIndex = 0; deviceIndex < devicesNumber; deviceIndex++)
	{
		DeviceRepresentation device;
		device.name = getDeviceModel(devInfoHandle, deviceIndex);
		device.serialNumber = getDeviceSerialNumber(devInfoHandle, deviceIndex);
		devicesList.push_back(device);
	}
	freeDeviceInfoProvider(devInfoHandle);
	return devicesNumber;
}
size_t DeviceInfoProvider::getAttachedDevicesCount()
{
	return devicesList.size();
}
std::string DeviceInfoProvider::getDeviceSerialNumber(
	DeviceInfoHandle devInfoHandle, size_t index)
{
	GetDeviceSerialNumberPtr func =
		PlatformSpecificFunctionLoader<GetDeviceSerialNumberPtr>()(opmLibraryHandle,
			"_GetDeviceSerialNumber");
	std::string buff;
	buff.resize(20, 0);
	uint32_t ret = func(devInfoHandle, index, &buff[0], buff.size());
	if(ret == 0xffffffff)
	{
		throw DeviceInfoProviderException("Unable to retrieve device serial number");
	}
	return buff.c_str();
}
std::string DeviceInfoProvider::getDeviceModel(
	DeviceInfoHandle devInfoHandle, size_t index)
{
	GetDeviceModelPtr func =
		PlatformSpecificFunctionLoader<GetDeviceModelPtr>()(opmLibraryHandle,
			"_GetDeviceName");
	std::string buff;
	buff.resize(20, 0);
	uint32_t ret = func(devInfoHandle, index, &buff[0], buff.size());
	if(ret == 0xffffffff)
	{
		throw DeviceInfoProviderException("Unable to retrieve device model");
	}
	return buff.c_str();
}

Measurer* DeviceInfoProvider::connectToDevice(size_t deviceIndex)
{
	deviceBuilder->release();
	hardwareInterface.reset(0);
    hardwareInterface.reset(new WinUsbHardwareInterface(deviceIndex));
	deviceBuilder->initOpm(hardwareInterface.get(),
    	ApplicationPaths::getConfigPath(), *LogFile);
	return deviceBuilder->getMeasurer();
}

void DeviceInfoProvider::releasePort()
{
   hardwareInterface.reset(0);
}

DeviceRepresentationList DeviceInfoProvider::getDevicesList()
{
    return devicesList;
}

Measurer* DeviceInfoProvider::connectToDeviceTcpIp(const std::string& addr)
{
	deviceBuilder->release();
	hardwareInterface.reset(0);
    hardwareInterface.reset(new TcpIpHardwareInterface(addr));
	deviceBuilder->initOpm(hardwareInterface.get(),
    	ApplicationPaths::getConfigPath(), *LogFile);
	return deviceBuilder->getMeasurer();
}


