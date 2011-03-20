#include "tchar.h"
#include <string>

#ifdef _UNICODE
	typedef std::wstring			STDString;
#else
	typedef std::string				STDString;
#endif