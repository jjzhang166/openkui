#include "tchar.h"
#include <string>

#ifdef _UNICODE
	typedef std::wstring			STDString;
#else
	typedef std::string				STDString;
#ifdef CA2T
#undef CA2T
#endif
	#define CA2T(x,code) CString( CA2W(x, code) )
#endif