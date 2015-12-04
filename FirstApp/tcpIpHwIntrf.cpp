//---------------------------------------------------------------------------


#pragma hdrstop

#include "tcpIpHwIntrf.h"
#include "PlatformSpecificFunctionLoader.h"
#include "x_Port.h"

//---------------------------------------------------------------------------

TcpIpHardwareInterface::TcpIpHardwareInterface(const std::string& addr)
	:	HardwareInterface("id_tcp.dll")
{
	connect = PlatformSpecificFunctionLoader<ConnectFunc>()(handle, "_Connect");
    void* portHandle = 0;
    const int connectError = connect(&portHandle, addr.c_str(), 1500, 5000);
	if(!portHandle || (connectError != ceOK)) throw Exception("Was unable to "
        "connect to OPM");
	port = static_cast<TPort*>(portHandle);
	bool resetError = port->Reset();
	if(resetError != true) throw Exception("Was unable to reset OPM port");
}

TcpIpHardwareInterface::~TcpIpHardwareInterface()
{
	if(port)
    {
		delete port;
        port = 0;
    }
}


