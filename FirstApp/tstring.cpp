#include "tstring.h"
#ifdef __MICROSOFT__
#include <winbase.h>
#endif
//---------------------------------------------------------------------------
#ifdef __LINUX__
//---------------------------------------------------------------------------
#if !defined(__ANDROID__)
#include <stdlib.h>	//for mbstowcs()
#include <wchar.h>	//for wcslen(), wcscpy()
#include <wctype.h>
#else
#warning wchar_t support on Android depends on target SDK and is not portable. Wide char related functionality will be disabled.
#endif //!defined(__ANDROID__)
#include <ctype.h>
//---------------------------------------------------------------------------
char * strupr(char * str)
{
	if(str == NULL)	return NULL;
	char * ptr = str;
	while(*ptr != 0)
	{
		*ptr = (char)toupper(*ptr);
		++ptr;
	}
	return str;
}
//---------------------------------------------------------------------------
char * strlwr(char * str)
{
	if(str == NULL)	return NULL;
	char * ptr = str;
	while(*ptr != 0)
	{		
		*ptr = (char)tolower(*ptr);
		++ptr;
	}
	return str;
}
//---------------------------------------------------------------------------
int strcmpi(const char * str1, const char * str2)
{
	if((str1 == NULL) || (str2 == NULL))	return 0;
	int d;
	while(*str1 != 0)
		if((d = tolower(*str1++) - tolower(*str2++)) != 0)
			return d;
	return tolower(*str1) - tolower(*str2);
}
//---------------------------------------------------------------------------
#ifndef __ANDROID__
wchar_t * _wcsupr(wchar_t * str)
{
	if(str == NULL)	return NULL;
	wchar_t * ptr = str;
	while(*ptr != 0)
	{
		*ptr = (wchar_t)towupper(*ptr);
		++ptr;
	}
	return str;
}
//---------------------------------------------------------------------------
wchar_t * _wcslwr(wchar_t * str)
{
	if(str == NULL)	return NULL;
	wchar_t * ptr = str;
	while(*ptr != 0)
	{
		*ptr = (wchar_t)towlower(*ptr);
		++ptr;
	}
	return str;
}
//---------------------------------------------------------------------------
int _wcsicmp(const wchar_t * str1, const wchar_t * str2)
{
	if((str1 == NULL) || (str2 == NULL))	return 0;
	int d;
	while(*str1 != 0)
		if((d = towlower(*str1++) - towlower(*str2++)) != 0)
			return d;
	return towlower(*str1) - towlower(*str2);
}
#endif
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TString::TString()
{
	len = 0;
	string = new char[1];
	string[0] = '\0';
}
//---------------------------------------------------------------------------
TString::TString(const char* str)
{
	if(str != NULL)
	{
		len = static_cast<int>(strlen(str));
		string = new char[len + 1];
		strcpy(string, str);
	}
	else
	{
		len = 0;
		string = new char[1];
		string[0] = '\0';
	}
}
//---------------------------------------------------------------------------
TString::TString(const char* str, int length)
{
	if(str != NULL)
	{
		len = length;
		string = new char[len + 1];
		string[len] = '\0';
		strncpy(string, str, len);
	}
	else
	{
		len = 0;
		string = new char[1];
		string[0] = '\0';
	}
}
//---------------------------------------------------------------------------
TString::TString(const TString& String)
{
	len = String.len;
	string = new char[len + 1];
	strcpy(string, String.string);
}
//---------------------------------------------------------------------------
TString::TString(char character)
{
	len = 1;
	string = new char[len + 1];
	string[0] = character;
	string[1] = '\0';
}
//---------------------------------------------------------------------------
TString::TString(int value)
{
	char str[TMP_BUFFER_SIZE];
	sprintf(str, "%d", value);
	len = static_cast<int>(strlen(str));
	string = new char[len + 1];
	strcpy(string, str);
}
//---------------------------------------------------------------------------
TString::TString(long value)
{
	char str[TMP_BUFFER_SIZE];
	sprintf(str, "%ld", value);
	len = static_cast<int>(strlen(str));
	string = new char[len + 1];
	strcpy(string, str);
}
//---------------------------------------------------------------------------
TString::TString(double value)
{
	char str[TMP_BUFFER_SIZE];
	sprintf(str, "%lf", value);
	len = static_cast<int>(strlen(str));
	string = new char[len + 1];
	strcpy(string, str);
}
//---------------------------------------------------------------------------
TString::~TString()
{
	if (string != NULL)
		delete[] string;
}
//---------------------------------------------------------------------------
TString& TString::operator=(const TString& String)
{
	if (this == &String)
		return *this;
	if (string != NULL)
		delete[] string;
	len = String.len;
	string = new char[len + 1];
	strcpy(string, String.string);
	return *this;
}
//---------------------------------------------------------------------------
TString& TString::operator=(const char* str)
{
	SetString(str);
	return *this;
}
//---------------------------------------------------------------------------
TString& TString::operator+=(const TString& String)
{
	len += String.len;
	char * buf = new char[len + 1];
	strcpy(buf, string);
	strcat(buf, String.string);
	if(string != NULL)
		delete[] string;
	string = buf;
	return *this;
}
//---------------------------------------------------------------------------
TString& TString::operator+=(const char* str)
{
	if(str != NULL)
	{
		len += static_cast<int>(strlen(str));
		char * buf = new char[len + 1];
		strcpy(buf, string);
		strcat(buf, str);
		if(string != NULL)
			delete[] string;
		string = buf;
	}
	return *this;
}
//---------------------------------------------------------------------------
TString TString::operator+(const TString & String) const
{
	TString str(*this);
	return str+=((TString&)String);
}
//---------------------------------------------------------------------------
TString TString::operator+(const char* str) const
{
	TString string(*this);
	return string+=str;
}
//---------------------------------------------------------------------------
int TString::operator==(const TString& String) const
{
	return !strcmp(string, String.string);
}
//---------------------------------------------------------------------------
int TString::operator==(const char* str) const
{
	if(str == NULL)
		return (len == 0);
	return !strcmp(string, str);
}
//---------------------------------------------------------------------------
//void TString::GetString(char* str) BAD IMPLEMENTATION
//{
//  str = new char[len + 1];
//  strcpy(str, string);
//}
//---------------------------------------------------------------------------
void TString::SetString(const char* str)
{
	const char* const oldString = string;
	if(str != NULL)
	{
		len = static_cast<int>(strlen(str));
		string = new char[len + 1];
		strcpy(string, str);
	}
	else
	{
		len = 0;
		string = new char[1];
		string[0] = '\0';
	}
	delete[] oldString;
}
//---------------------------------------------------------------------------
int TString::ToInt()
{
	int value = 0;
	sscanf(string, "%d", &value);
	return value;
}
//---------------------------------------------------------------------------
int TString::ToIntDef(int Default)
{
	int value = 0;
	if (sscanf(string, "%d", &value))
		return value;
	return Default;
}
//---------------------------------------------------------------------------
double TString::ToFloat()
{
	double value = 0;
	sscanf(string, "%lf", &value);
	return value;
}
//---------------------------------------------------------------------------
double TString::ToFloatDef(double Default)
{
	double value = 0;
	if (sscanf(string, "%lf", &value))
		return value;
	return Default;
}
//---------------------------------------------------------------------------
TString TString::ToUpperCase() const
{
	if(string == NULL)
		return TString();
#ifdef __MICROSOFT__
	return TString(_strupr(string));
#else
	return TString(strupr(string));
#endif
}
//---------------------------------------------------------------------------
TString TString::ToLowerCase() const
{
	if(string == NULL)
		return TString();
#ifdef __MICROSOFT__
	return TString(_strlwr(string));
#else
	return TString(strlwr(string));
#endif
}
//---------------------------------------------------------------------------
int TString::CompareNoCase(const TString& String) const
{
#ifdef __MICROSOFT__
	return _stricmp(string, String.string);
#else
	return strcmpi(string, String.string);
#endif
}
//---------------------------------------------------------------------------
int TString::Find(const char* str, int startPos /*= 0*/) const
{
	if((startPos >= len) || (startPos < 0) || (str == NULL) || (str[0] == 0)) return -1;
	char * ptr = strstr(string + startPos, str);
	if(ptr == NULL) return -1;
	return static_cast<int>(ptr - string); 
}
//---------------------------------------------------------------------------
int TString::ReverseFind(const char* str) const
{
	if(str == NULL)
		return -1;
	int flen = static_cast<int>(strlen(str)); 
	if (flen > len)
		return -1;

	char * buf = NULL;

	while ((flen <= len) && (buf == NULL))
	{
		buf = strstr (string + len - flen,  str);
		flen++;
	}
	if (buf != NULL)
		return static_cast<int>(buf - string);

	return -1;
}
//---------------------------------------------------------------------------
void TString::Delete(int index, int num /* = 1*/)
{
	if((index < 0)||(index >= len)||(num <=0))	return;
	if(index + num > len)
		num = len - index;
	char *str = new char[len + 1 - num];
	strncpy(str, string, index);
	strcpy(str + index, string + index + num);
	len -= num;
	if(string != NULL)
		delete [] string;
	string = str;
}
//---------------------------------------------------------------------------
TString TString::Trim()
{
	if(this->len == 0)  return (*this);
	char * buf = new char[this->len + 1];
	strcpy(buf, this->string);
	char * ptr = buf + this->len - 1;
	while((ptr != buf)&&((*ptr) <= ' '))
		ptr--;
	*(ptr+1) = 0;
	ptr = buf;
	while(((*ptr) != 0)&&(*ptr <= ' '))
		ptr++;
	TString retValue(ptr);
	delete[] buf;
	return retValue;
}
//---------------------------------------------------------------------------
TString TString::TrimLeft()
{
	if(this->len == 0)  return (*this);
	char * ptr = string;
	while(((*ptr) != 0)&&(*ptr <= ' '))
		ptr++;
	return ptr;
}
//---------------------------------------------------------------------------
TString TString::TrimRight()
{
	if(this->len == 0)  return (*this);
	char * buf = new char[this->len + 1];
	strcpy(buf, this->string);
	char * ptr = buf + this->len - 1;
	while((ptr >= buf)&&((*ptr) <= ' '))
		ptr--;
	*(ptr+1) = 0;
	ptr = buf;
	TString retValue(ptr);
	delete[] buf;
	return retValue;
}
//---------------------------------------------------------------------------
TString TString::SubString(int index, int length) const
{
	TString str;
	if((index < 0) || (index >= len) || (length < 0)) return str;
	str = string + index;
	if(length >= str.len)
		return str;
	str.Delete(length, str.len - length);
	return str;    
}
//---------------------------------------------------------------------------
void TString::Split(TStringArray * list, TString delimiter)
{
	if(list == NULL) return;
	int curPos = 0;
	while(curPos < this->len)
	{
		int pos = this->Find(delimiter.c_str(), curPos);
		if(pos == -1)
			pos = this->len;
		list->AddData(new TString(this->SubString(curPos, pos - curPos)));
		curPos =  pos + 1;
	}
}
//---------------------------------------------------------------------------
void TString::Format(const char * format, ...)
{
	if(format == NULL)  return;
	va_list arglist;
	va_start(arglist, format);
	int length = Vscprintf(format, arglist);
	va_end(arglist);
	if(length <= 0) return;
	va_start(arglist, format);
	char * buffer = new char[length + 1];
	if(vsprintf(buffer, format, arglist) >= 0)
	{
		if(string != NULL)
			delete [] string;
		string = buffer;
		len = length;
	}
	else
	{
		delete [] buffer;
	}
	va_end(arglist);
}
//---------------------------------------------------------------------------
int TString::Vscprintf(const char *format, va_list arglist)
{
	//  return _vscprintf(format, argptr); 
	static char buffer[32768];
	return vsprintf(buffer, format, arglist);
}
//---------------------------------------------------------------------------
TString TString::ToAnsi() const
{
	return (*this);	
}
//---------------------------------------------------------------------------
#ifndef __ANDROID__
TwString TString::ToUnicode() const
{
	wchar_t * buffer = new wchar_t[len+1];
	buffer[0] = 0;

#ifndef __LINUX__
	if(!MultiByteToWideChar(1251, 0, string, len+1, buffer, len+1))	//may be checked for errors
		MultiByteToWideChar(CP_ACP, 0, string, len+1, buffer, len+1);
#else
	mbstowcs(buffer, string, len);
	buffer[len] = 0;
#endif
	TwString retValue(buffer);
	delete [] buffer;
	return retValue;
}
#endif
//---------------------------------------------------------------------------


#ifndef __ANDROID__
//---------------------------------------------------------------------------
TwString::TwString()
{
	len = 0;
	string = new wchar_t[1];
	string[0] = L'\0';
}
//---------------------------------------------------------------------------
TwString::TwString(const wchar_t* str)
{
	if(str != NULL)
	{
		len = static_cast<int>(wcslen(str));
		string = new wchar_t[len + 1];
		wcscpy(string, str);
	}
	else
	{
		len = 0;
		string = new wchar_t[1];
		string[0] = L'\0';
	}
}
//---------------------------------------------------------------------------
TwString::TwString(const TwString& String)
{
	len = String.len;
	string = new wchar_t[len + 1];
	wcscpy(string, String.string);
}
//---------------------------------------------------------------------------
TwString::TwString(int value)
{
	wchar_t str[TMP_BUFFER_SIZE];
#if defined(__LINUX__) || (defined(__MICROSOFT__) && (_MSC_VER >= 1700))
	swprintf(str, TMP_BUFFER_SIZE, L"%d", value);
#else
	swprintf(str, L"%d", value);
#endif
	len = static_cast<int>(wcslen(str));
	string = new wchar_t[len + 1];
	wcscpy(string, str);
}
//---------------------------------------------------------------------------
TwString::TwString(double value)
{
	wchar_t str[TMP_BUFFER_SIZE];
#if defined(__LINUX__) || (defined(__MICROSOFT__) && (_MSC_VER >= 1700))
	swprintf(str, TMP_BUFFER_SIZE, L"%d", value);
#else
	swprintf(str, L"%d", value);
#endif
	len = static_cast<int>(wcslen(str));
	string = new wchar_t[len + 1];
	wcscpy(string, str);
}
//---------------------------------------------------------------------------
TwString::~TwString()
{
	if (string != NULL)
		delete string;
}
//---------------------------------------------------------------------------
TwString& TwString::operator=(const TwString& String)
{
	if (this == &String)
		return *this;
	if (string != NULL)
		delete[] string;
	len = String.len;
	string = new wchar_t[len + 1];
	wcscpy(string, String.string);
	return *this;
}
//---------------------------------------------------------------------------
TwString& TwString::operator=(const wchar_t* str)
{
	SetString(str);
	return *this;
}
//---------------------------------------------------------------------------
TwString& TwString::operator+=(TwString& String)
{
	len += String.len;
	wchar_t * buf = new wchar_t[len + 1];
	wcscpy(buf, string);
	wcscat(buf, String.string);
	if(string != NULL)
		delete string;
	string = buf;
	return *this;
}
//---------------------------------------------------------------------------
TwString& TwString::operator+=(const wchar_t* str)
{                                           
	if(str != NULL)
	{
		len += static_cast<int>(wcslen(str));
		wchar_t * buf = new wchar_t[len + 1];
		wcscpy(buf, string);
		wcscat(buf, str);
		if(string != NULL)
			delete string;
		string = buf;
	}
	return *this;
}
//---------------------------------------------------------------------------
TwString TwString::operator+(TwString & String) const
{
	TwString str(*this);
	return str+=((TwString&)String);}
//---------------------------------------------------------------------------
TwString TwString::operator+(const wchar_t* str) const
{
	TwString string(*this);
	return string+=str;
}
//---------------------------------------------------------------------------
int TwString::operator==(const TwString& String) const
{
	return !wcscmp(string, String.string);
}
//---------------------------------------------------------------------------
int TwString::operator==(const wchar_t* str) const
{
	if(str == NULL)
		return (len == 0);
	return !wcscmp(string, str);
}
//---------------------------------------------------------------------------
//void TwString::GetString(wchar_t* str) BAD IMPLEMENTATION
//{
//  str = new wchar_t[len + 1];
//  wcscpy(str, string);
//}
//---------------------------------------------------------------------------
void TwString::SetString(const wchar_t* str)
{
	const wchar_t* const oldString = string;
	if(str != NULL)
	{
		len = static_cast<int>(wcslen(str));
		string = new wchar_t[len + 1];
		wcscpy(string, str);
	}
	else
	{
		len = 0;
		string = new wchar_t[1];
		string[0] = L'\0';
	}
	delete[] oldString;
}
//---------------------------------------------------------------------------
int TwString::ToInt()
{
	int value = 0;
	swscanf(string, L"%d", &value);
	return value;
}
//---------------------------------------------------------------------------
int TwString::ToIntDef(int Default)
{
	int value = 0;
	if (swscanf(string, L"%d", &value))
		return value;
	return Default;
}
//---------------------------------------------------------------------------
double TwString::ToFloat()
{
	double value = 0;
	swscanf(string, L"%lf", &value);
	return value;
}
//---------------------------------------------------------------------------
double TwString::ToFloatDef(double Default)
{
	double value = 0;
	if (swscanf(string, L"%lf", &value))
		return value;
	return Default;
}
//---------------------------------------------------------------------------
TwString TwString::ToUpperCase() const
{
	if(string == NULL)
		return TwString();
	return TwString(_wcsupr(string));
}
//---------------------------------------------------------------------------
TwString TwString::ToLowerCase() const
{
	if(string == NULL)
		return TwString();
	return TwString(_wcslwr(string));
}
//---------------------------------------------------------------------------
int TwString::CompareNoCase(const TwString& String) const
{
	return _wcsicmp(string, String.string);
}
//---------------------------------------------------------------------------
TString TwString::ToAnsi() const
{
	char * buffer = new char[len+1];
	buffer[0] = 0;
#ifndef __LINUX__
	if(!WideCharToMultiByte(1251, 0, string, len+1, buffer, len+1, NULL, NULL))	//may be checked for errors
		WideCharToMultiByte(CP_ACP, 0, string, len+1, buffer, len+1, NULL, NULL);	//may be checked for errors
#else
	wcstombs(buffer, string, len);
	buffer[len] = 0;
#endif
	TString retValue(buffer);
	delete [] buffer;
	return retValue;
}
//---------------------------------------------------------------------------
TwString TwString::ToUnicode() const
{
	return (*this);
}
//---------------------------------------------------------------------------
int TwString::ReverseFind(const wchar_t* str) const
{
	if(str == NULL)
		return -1;
	int flen = static_cast<int>(wcslen(str));
	if (flen > len)
		return -1;

	wchar_t * buf = NULL;

	while ((flen <= len) && (buf == NULL))
	{
		buf = wcsstr (string + len - flen,  str);
		flen++;
	}
	if (buf != NULL)
		return static_cast<int>(buf - string);

	return -1;
}
//---------------------------------------------------------------------------
void TwString::Delete(int index, int num /* = 1*/)
{
	if((index < 0)||(index >= len)||(num <=0))	return;
	if(index + num > len)
		num = len - index;
	wchar_t *str = new wchar_t[len + 1 - num];
	wcsncpy(str, string, index);
	wcscpy(str + index, string + index + num);
	len -= num;
	delete string;
	string = str;
}
//---------------------------------------------------------------------------
TwString TwString::SubString(int index, int length) const
{
	TwString str;
	if((index < 0) || (index >= len) || (length < 0)) return str;
	str = string + index;
	if(length >= str.len)
		return str;
	str.Delete(length, str.len - length);
	return str;    
}
//---------------------------------------------------------------------------
#endif

