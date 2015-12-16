//---------------------------------------------------------------------------
#ifndef __LINUX__
#	include <windows.h>
#	include <TCHAR.h>
#else
#	error Not implemented for linux yet
#endif

#include <stdio.h>
#include <tchar.h>
#include <shellapi.h>
#include <cassert>
#include "tstring.h"

#pragma hdrstop
#include "rc_util.h"

//---------------------------------------------------------------------
// TProjectRCVersion
//---------------------------------------------------------------------
inline LONG MakeLong(WORD a, WORD b)
{
   return static_cast<LONG>(a | (static_cast<DWORD>(b) << 16));
}
//---------------------------------------------------------------------
namespace  {
//---------------------------------------------------------------------
const char * ProductNameKey = "ProductName";
const char * ProductVersionKey = "ProductVersion";
const char * FileVersionKey = "FileVersion";
const char * LegalCopyrightKey = "LegalCopyright";
const char * WebSiteKey = "WebSite";
const char * EMailKey = "E-Mail";
const char * CommentsKey = "Comments";
//---------------------------------------------------------------------
#ifdef _WIN32_WCE
bool toWideChar(const wchar_t * from, size_t fromLength, std::vector<char> & to)
{
   if (fromLength == 0)
   {
      to.clear();
      return true;
   }

   enum {ALLOCATION_STEP = 10};

   to.resize(fromLength + ALLOCATION_STEP);

   DWORD convertedSize;
   while ( (convertedSize = WideCharToMultiByte(CP_ACP, 0, from, fromLength, 
                                                &to[0], to.size(), NULL, NULL)) 
            == to.size())
   {
      to.resize(to.size() + ALLOCATION_STEP);
   }

   to.resize(convertedSize);
   return !to.empty();
}
#endif // _WIN32_WCE
//---------------------------------------------------------------------
#ifndef _WIN32_WCE
DWORD getModuleFileName(HMODULE module, char * buffer, DWORD size)
{
   return GetModuleFileNameA(module, buffer, size);
}
#endif // _WIN32_WCE
//---------------------------------------------------------------------
DWORD getModuleFileName(HMODULE module, wchar_t * buffer, DWORD size)
{
   return GetModuleFileNameW(module, buffer, size);
}
//---------------------------------------------------------------------
template <typename TChar>
void getModuleFileName(HMODULE module, std::vector<TChar> & result)
{
   result.resize(MAX_PATH);
   
   DWORD size;
   while ((size = getModuleFileName(module, &result[0], result.size())) == result.size())
   {
      result.resize(result.size() * 2);
   }

   result.resize((size == 0) ? 0 : (size + 1));
}
//---------------------------------------------------------------------
}
//---------------------------------------------------------------------
TProjectRCVersion::TProjectRCVersion(HMODULE module) 
: Translations(NULL)
{
   getModuleFileName(module, ModulePathW);

#ifndef _WIN32_WCE

   getModuleFileName(module, ModulePathA);

#else

   if (!ModulePathW.empty())
      toWideChar(&ModulePathW[0], ModulePathW.size(), ModulePathA);

#endif // _WIN32_WCE

   DWORD fvHandle;
   DWORD size = GetFileVersionInfoSizeW(&ModulePathW[0], &fvHandle);
   if (size == 0)
      return;

   FVData.resize(size);

   if (!GetFileVersionInfoW(&ModulePathW[0], fvHandle, size, &FVData[0]))
      return;

   UINT notUsed = 0;
   if (!VerQueryValueW(&FVData[0], L"\\VarFileInfo\\Translation", 
                       reinterpret_cast<LPVOID*>(&Translations), &notUsed))
   {
      FVData.clear();
      return;
   }
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetModulePath(const char * & modPath)
{
   if (ModulePathA.empty())
      return false;

   modPath = &ModulePathA[0];
   return true;
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetModulePath(const wchar_t * & modPath)
{
   if (ModulePathW.empty())
      return false;

   modPath = &ModulePathW[0];
   return true;
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetProductName(const char * & prodName)
{
   return GetString(ProductNameKey, prodName);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetProductName(const wchar_t * & prodName)
{
   return GetString(ProductNameKey, prodName);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetProductVersion(const char * & prodVersion)
{
   return GetString(ProductVersionKey, prodVersion);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetProductVersion(const wchar_t * & prodVersion)
{
   return GetString(ProductVersionKey, prodVersion);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetFileVersion(const char * & fileVersion)
{
   return GetString(FileVersionKey, fileVersion);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetFileVersion(const wchar_t * & fileVersion)
{
   return GetString(FileVersionKey, fileVersion);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetCopyright(const char * & copyright)
{
   return GetString(LegalCopyrightKey, copyright);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetCopyright(const wchar_t * & copyright)
{
   return GetString(LegalCopyrightKey, copyright);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetWebSite(const char * & website)
{
   return GetString(WebSiteKey, website);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetWebSite(const wchar_t * & website)
{
   return GetString(WebSiteKey, website);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetEmail(const char * & email)
{
   return GetString(EMailKey, email);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetEmail(const wchar_t * & email)
{
   return GetString(EMailKey, email);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetComments(const char * & comments)
{
   return GetString(CommentsKey, comments);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetComments(const wchar_t * & comments)
{
   return GetString(CommentsKey, comments);
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetString(const char * name, const char * & value)
{
#ifndef _WIN32_WCE

   if (FVData.empty() || Translations == NULL)
      return false;

   char blockName[255];
   sprintf(blockName, "\\StringFileInfo\\%04x%04x\\%s", 
      Translations[0].wLanguage, Translations[0].wCodePage, name);

   UINT notUsed;
   return VerQueryValueA(&FVData[0], blockName, 
      reinterpret_cast<LPVOID*>(const_cast<char**>(&value)), &notUsed) == TRUE;

#else

   std::map<const char *, std::vector<char>>::iterator it = 
      MultibyteStrings.find(name);
   if (it == MultibyteStrings.end())
   {
      const wchar_t * wideValue;
      UINT size;
      if (!GetString(name, wideValue, &size))
         return false;
      it = MultibyteStrings.insert(std::make_pair(name, std::vector<char>())).first;
      if (!toWideChar(wideValue, size, it->second))
      {
         MultibyteStrings.erase(it);
         return false;
      }
   }

   // We are using the fact, that insering/erasing into/from std::map won't 
   // invalidate it's pointers.
   value = &(it->second)[0];
   return true;

#endif // _WIN32_WCE
}
//---------------------------------------------------------------------
bool TProjectRCVersion::GetString(const char * name, const wchar_t * & value, UINT * valueSize)
{
   if (FVData.empty() || Translations == NULL)
      return false;

   wchar_t blockName[255];
   wsprintfW(blockName, L"\\StringFileInfo\\%04x%04x\\%hs", 
      Translations[0].wLanguage, Translations[0].wCodePage, name);

   UINT notUsed;
   return VerQueryValueW(&FVData[0], 
                         blockName, 
                         reinterpret_cast<LPVOID*>(const_cast<wchar_t**>(&value)), 
                         (valueSize == NULL) ? &notUsed : valueSize) == TRUE;
}
//---------------------------------------------------------------------

