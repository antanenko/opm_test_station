//---------------------------------------------------------------------------


#pragma hdrstop

#include "DeviceConnectionRequest.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


DeviceConnectionRequest::TOnIssued DeviceConnectionRequest::OnIssued = NULL;
DeviceConnectionRequest::TOnIssuedTcpIp DeviceConnectionRequest::OnIssuedTcpIp = NULL;
