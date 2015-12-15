//---------------------------------------------------------------------------

#ifndef hardwareInterfaceH
#define hardwareInterfaceH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <string>
#include "PlatformSpecificLibraryHandle.h"

class TPort;

struct HardwareInterfaceException : public Exception
{
	HardwareInterfaceException(const std::string& message) :
		Exception(message.c_str()) {};
};

class HardwareInterface
{
public:
	typedef void* Handle;
public:
	HardwareInterface(const std::string& interfaceLibraryName);
	virtual ~HardwareInterface();
	LibraryHandle getHandle()
	{
		return handle;
	}
    virtual TPort* getPort();
protected:
	LibraryHandle handle;
    TPort* port;

private:
	std::string getLibraryFullPath(const std::string& interfaceLibraryName);
};

#endif
