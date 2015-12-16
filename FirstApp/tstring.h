//---------------------------------------------------------------------------
#ifndef tstringH
#define tstringH
//---------------------------------------------------------------------------
// TODO: This peace of shit should be completely removed in favor of std::string, std::wstring.
//       UTF-8 encoding should be used to store string data in SOR.
//---------------------------------------------------------------------------
#ifndef __LINUX__
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif
#	include <Windows.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef __BORLAND__
#include <vcl.h>
#endif

#include "tarray.h"
//---------------------------------------------------------------------------
class TString;
typedef TOxArray<TString, TString*> TStringArray;
//---------------------------------------------------------------------------
#ifndef __ANDROID__
class TwString;				// see declaration below
#endif
class TString
{
protected:
	char* string;
	int   len;
public:
	TString();
	TString(const char* str);
	TString(const char* str, int length);
	TString(const TString& String);
	TString(char character);
	TString(int value);
	TString(long value);
	TString(double value);
	~TString();

	TString& operator=(const TString& String);
	TString& operator=(const char* str);
	TString& operator+=(const TString& String);
	TString& operator+=(const char* str);
	TString operator+(const TString& String) const;
	TString operator+(const char* str) const;
	int operator==(const TString& String) const;
	int operator==(const char* str) const;
	inline int operator!=(const TString& String) const {return operator==(String) == 0 ? 1 : 0;}
	inline int operator!=(const char* str) const {return operator==(str) == 0 ? 1 : 0;}
	inline operator const char * () const {return string;} 
#ifdef __BORLAND__
	operator AnsiString(){return AnsiString(string);}
#endif

	char* c_str()
	{
		return string;
	}

	const char* c_str() const 
	{
		return string;
	}

	int Len() const {return len;};
	int GetStringLen() const {return len;}
	//  void GetString(char* str); BAD IMPLEMENTATION
	void SetString(const char* str);

	int ToInt();
	int ToIntDef(int Default);
	double ToFloat();
	double ToFloatDef(double Default);
	TString ToUpperCase() const;
	TString ToLowerCase() const;
	int CompareNoCase(const TString& String) const;
	TString Trim();
	TString TrimLeft();
	TString TrimRight();
	int Find(const char* str, int startPos = 0) const;
	char* LastChar(void)  {return len ? &string[len - 1] : NULL;}

	TString ToAnsi() const;			// for compatibility with TwString
#ifndef __ANDROID__
	TwString ToUnicode() const;			// for _explicit_ conversation to TwString
#endif

	int ReverseFind(const char* str) const;
	void Delete(int index, int num = 1);
	TString SubString(int index, int length) const;
	void Split(TStringArray * list, TString delimiter);
	void Format(const char * format, ...);
	int Vscprintf(const char *format, va_list argptr);
};
//---------------------------------------------------------------------------
//char* operator+(const char* str, TString& String);
//---------------------------------------------------------------------------
#ifndef __ANDROID__
class TwString
{
protected:
	wchar_t* string;
	int   len;
public:
	TwString();
	TwString(const wchar_t* str);
	TwString(const TwString& String);
	TwString(int value);
	TwString(double value);
	~TwString();

	TwString& operator=(const TwString& String);
	TwString& operator=(const wchar_t* str);
	TwString& operator+=(TwString& String);
	TwString& operator+=(const wchar_t* str);
	TwString operator+(TwString& String) const;
	TwString operator+(const wchar_t* str) const;
	int operator==(const TwString& String) const;
	int operator==(const wchar_t* str) const;
	operator const wchar_t *() const {return string;}

	const wchar_t* c_str() const { return string; }
	wchar_t* c_str() {return string;};
	int Len() const {return len;};
	int GetStringLen() const {return len;}
	//  void GetString(wchar_t* str); BAD IMPLEMENTATION
	void SetString(const wchar_t* str);

	int ToInt();
	int ToIntDef(int Default);
	double ToFloat();
	double ToFloatDef(double Default);

	TwString ToUpperCase() const;
	TwString ToLowerCase() const;
	int CompareNoCase(const TwString& String) const;

	TString ToAnsi() const;				// for _explicit_ conversation to TString
	TwString ToUnicode() const;			// for compatibility with TString

	int ReverseFind(const wchar_t* str) const;
	void Delete(int index, int num = 1);
	TwString SubString(int index, int length) const;
};
#endif
//---------------------------------------------------------------------------
//wchar_t* operator+(const wchar_t* str, TwString& String);
//---------------------------------------------------------------------------
#ifdef UNICODE

	typedef TwString TxString;
#	define XSTRING(string) string.ToUnicode()

#else

	typedef TString TxString;
#	define XSTRING(string) string.ToAnsi()

#endif

#define TMP_BUFFER_SIZE 64

#endif

