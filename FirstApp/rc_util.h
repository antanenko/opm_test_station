//---------------------------------------------------------------------------
#ifndef rc_utilH
#define rc_utilH
#include <vector>
#include <map>
//---------------------------------------------------------------------------
class TProjectRCVersion
{
public:
  TProjectRCVersion  (HMODULE module);

  bool GetModulePath     (const char * & modPath);
  bool GetModulePath     (const wchar_t * & modPath);
  bool GetProductName    (const char * & prodName);
  bool GetProductName    (const wchar_t * & prodName);
  bool GetProductVersion (const char * & prodVersion);
  bool GetProductVersion (const wchar_t * & prodVersion);
  bool GetFileVersion    (const char * & fileVersion);
  bool GetFileVersion    (const wchar_t * & fileVersion);
  bool GetCopyright      (const char * & copyright);
  bool GetCopyright      (const wchar_t * & copyright);
  bool GetWebSite        (const char * & website);
  bool GetWebSite        (const wchar_t * & website);
  bool GetEmail          (const char * & email);
  bool GetEmail          (const wchar_t * & email);
  bool GetComments       (const char * & comments);
  bool GetComments       (const wchar_t * & comments);

private:
  bool GetString(const char * name, const char * & value);
  bool GetString(const char * name, const wchar_t * & value, UINT * valueSize = NULL);

  struct TranslationInfo {
     WORD wLanguage;
     WORD wCodePage;
  };
  TranslationInfo * Translations;
  std::vector<unsigned char> FVData;
  std::vector<wchar_t> ModulePathW;
  std::vector<char> ModulePathA;
#ifdef _WIN32_WCE
  std::map<const char *, std::vector<char>> MultibyteStrings;
#endif
};
//---------------------------------------------------------------------------
#endif

 