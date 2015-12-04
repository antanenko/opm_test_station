//---------------------------------------------------------------------------

#ifndef DeviceConnectionRequestH
#define DeviceConnectionRequestH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include "device/device.hpp"

class DeviceConnectionRequest
{
public:
	typedef void __fastcall (__closure *TOnIssued)(unsigned int deviceIndex, Measurer*& measurer);
	typedef void __fastcall (__closure *TOnIssuedTcpIp)(const std::string& addr, Measurer*& measurer);
	static TOnIssued OnIssued;
	static TOnIssuedTcpIp OnIssuedTcpIp;
	static void __fastcall Make(unsigned int deviceIndex, Measurer*& measurer)
	{
		if(OnIssued)
		{
			OnIssued(deviceIndex, measurer);
		}
	}
	static void __fastcall Make(const std::string& addr, Measurer*& measurer)
	{
		if(OnIssuedTcpIp)
		{
			OnIssuedTcpIp(addr, measurer);
		}
	}
private:
	DeviceConnectionRequest();
	DeviceConnectionRequest& operator=(const DeviceConnectionRequest&);
};


#endif
