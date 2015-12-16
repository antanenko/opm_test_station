#pragma hdrstop

#include "paths.h"

#include <Classes.hpp>
#include <Forms.hpp>

std::string ApplicationPaths::getLibPath()
{
	const UnicodeString rootPath = ExtractFilePath(Application->ExeName);
	return std::string(AnsiString(rootPath).c_str()) + std::string("lib\\");
}

std::string ApplicationPaths::getConfigPath()
{
	const UnicodeString rootPath = ExtractFilePath(Application->ExeName);
	return std::string(AnsiString(rootPath).c_str()) + std::string("etc\\");
}

std::string ApplicationPaths::getAppRootPath()
{
	const UnicodeString rootPath = ExtractFilePath(Application->ExeName);
	return std::string(AnsiString(rootPath).c_str());
}



