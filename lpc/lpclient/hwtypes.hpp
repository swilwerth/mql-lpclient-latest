#ifndef LPC_HARDTYPES_H
#define LPC_HARDTYPES_H

#include <cinttypes>
#include <iostream>
#include <sstream>
using namespace std;

//default values
#define REQUEST_TIMEOUT         2500    //  msecs, (> 1000!)
#define REQUEST_RETRIES         3       //  Before we abandon
#define LPC_ERR_REXCEED         787
#define LPC_ERR_INVALIDHANDLE   689
#define LPC_MAX_WORKERS         65535   //max workers in this api
#define LPC_ERR_NOERROR         0

//Cross DLL boundaries types.
#define int_t    uint32_t
#define widptr_t int_t
#define char_t   char

size_t string_size(const string& s) {
    int mul = sizeof(wchar_t) / sizeof(char);
    return s.size() * mul;
}

size_t wstring_size(const wstring& s) {
    int mul = sizeof(wchar_t) / sizeof(char);
    return s.size() * mul;
}

//String marshalling from DLL call string_t* argument to std::string
void string_marshall(const wchar_t* s, string &d) {
    wstring wcstring = s;
    auto cstr = new char[wstring_size(wcstring)];
    wcstombs(cstr, s, wstring_size(wcstring));
    d = cstr;
    delete[] cstr;
}

//String de-marshalling from std::string to string_t*  DLL call argument
void string_unmarshall(const string &s, wchar_t* d) {
    auto wcstr = new wchar_t[string_size(s)];
    mbstowcs(wcstr, s.c_str(), string_size(s));
    wstring wcstring = wcstr;
    wcscpy(d,wcstring.c_str());
    delete[] wcstr;
}

#endif