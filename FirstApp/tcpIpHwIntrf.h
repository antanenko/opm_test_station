//---------------------------------------------------------------------------

#ifndef tcpIpHwIntrfH
#define tcpIpHwIntrfH

#include <hardwareInterface.h>
//---------------------------------------------------------------------------


class TcpIpHardwareInterface : public HardwareInterface
{
	typedef int (*ConnectFunc)(void** , const char* , long , long );
	ConnectFunc connect;

public:
	~TcpIpHardwareInterface();
    TcpIpHardwareInterface(const std::string& addr);

};

#endif
