//---------------------------------------------------------------------------
#pragma hdrstop

#include "winUsbHwIntrf.h"
#include "PlatformSpecificFunctionLoader.h"
#include "x_Port.h"

struct InterfaceNotInitializedException : public HardwareInterfaceException
{
	InterfaceNotInitializedException() : HardwareInterfaceException(
		"Hardware interface is not initialized") {}
};

//---------------------------------------------------------------------------
WinUsbHardwareInterface::WinUsbHardwareInterface()
	:	HardwareInterface("id_usbW.dll"),
    	connectByIndex(0),
        disconnect(0),
        deviceIndex(-1)
{
}

WinUsbHardwareInterface::WinUsbHardwareInterface(int deviceIndex)
	:	HardwareInterface("id_usbW.dll"),
    	deviceIndex(deviceIndex)
{
	connectByIndex = PlatformSpecificFunctionLoader<ConnectFunc>()(handle, "_Connect");
    disconnect = PlatformSpecificFunctionLoader<DisconnectFunc>()(handle, "_Disconnect");
    void* portHandle = 0;
    const int connectError = connectByIndex(&portHandle, "", deviceIndex, 100000);
    if(!portHandle || (connectError != ceOK)) throw Exception("Was unable to "
        "connect to OPM");
	port = static_cast<TPort*>(portHandle);
	bool resetError = port->Reset();
	if(resetError != true) throw Exception("Was unable to reset OPM port");
}

WinUsbHardwareInterface::~WinUsbHardwareInterface()
{
	if(port && disconnect)
    {
		disconnect(port);
    }
}

TPort* WinUsbHardwareInterface::getPort()
{
	if(!port || !connectByIndex || !disconnect || (deviceIndex == -1))
    {
		throw InterfaceNotInitializedException();
    }
	return HardwareInterface::getPort();
}


