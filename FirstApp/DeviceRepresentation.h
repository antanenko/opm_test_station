//---------------------------------------------------------------------------

#ifndef DeviceRepresentationH
#define DeviceRepresentationH

#include <memory>
#include <vector>
#include <string>
#include <Classes.hpp>
#include <pngimage.hpp>

//---------------------------------------------------------------------------

class DeviceRepresentation
{
public:
	DeviceRepresentation(){};
	DeviceRepresentation(const std::string& name,
		const std::string& serialNumber)
		:	name(name),
			serialNumber(serialNumber)
	{
	}
	std::string name;
	std::string serialNumber;
};

typedef std::vector<DeviceRepresentation> DeviceRepresentationList;


#endif
