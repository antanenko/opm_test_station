//---------------------------------------------------------------------------

#ifndef pathsH
#define pathsH

#include <string>

class ApplicationPaths
{
public:
	static std::string getLibPath();
	static std::string getConfigPath();
	static std::string getAppRootPath();
};

#endif
