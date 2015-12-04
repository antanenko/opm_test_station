#ifndef winUsbHwIntrfH
#define winUsbHwIntrfH

#include "device/hardwareInterface.h"

class WinUsbHardwareInterface : public HardwareInterface
{
	typedef int (*ConnectFunc)(void** , char* , long , long );
	typedef void (*DisconnectFunc)(void*);
	ConnectFunc connectByIndex;
    DisconnectFunc disconnect;

public:
	~WinUsbHardwareInterface();
    WinUsbHardwareInterface();
    WinUsbHardwareInterface(int deviceIndex);
    virtual TPort* getPort();
private:
	const int deviceIndex;
};

#endif
