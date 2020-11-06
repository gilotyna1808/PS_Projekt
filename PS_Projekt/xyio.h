#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#ifdef UNICODE
# undef UNICODE
# define _MBCS
#endif

#ifndef __cplusplus
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#else
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
using namespace std;
#endif
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1800)
	static int vsscanf(const char* s, const char* fmt, va_list ap); /* brak implementacji przed VC++ 12 (VS 2013) */
#endif

	void setcursor(int x, int y);
	void getcursor(int* x, int* y);
	void getrange(int* maxx, int* maxy);
	void getscreen(int* xorg, int* yorg, int* xend, int* yend);
	int xyscanf(int x, int y, const char* format, ...);
	int xyprintf(int x, int y, const char* format, ...);
	void clear(void);

#ifdef __cplusplus
}
#endif