//---------------------------------------------------------------------------
#pragma hdrstop

//#include <hard/x_Port.h>
#include "hardwareInterface.h"
#include "paths.h"

//---------------------------------------------------------------------------
struct LibraryLoadingException : public HardwareInterfaceException
{
	LibraryLoadingException() : HardwareInterfaceException(
		"Unable to load hardware interface library") {}
};


HardwareInterface::HardwareInterface(const std::string& interfaceLibraryName)
	:	handle(LoadLibraryA(getLibraryFullPath(interfaceLibraryName).c_str())),
    	port(0)
{
	if(handle == 0)
	{
		DWORD lastError = GetLastError();
		throw LibraryLoadingException();
	}
}

std::string HardwareInterface::getLibraryFullPath(const std::string& interfaceLibraryName)
{
	const std::string libPath = ApplicationPaths::getLibPath() + interfaceLibraryName;
	return libPath;
}

HardwareInterface::~HardwareInterface()
{
	FreeLibrary(handle);
    handle = 0;
}

TPort* HardwareInterface::getPort()
{
	return port;
}

