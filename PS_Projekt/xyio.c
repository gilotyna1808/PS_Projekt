#include "xyio.h"


void setcursor(int x, int y) {
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pkt = { x,y };
	SetConsoleCursorPosition(ekran, pkt);
}

void getcursor(int* x, int* y) {
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO pkt;
	if (GetConsoleScreenBufferInfo(ekran, &pkt))
	{
		*x = (int)pkt.dwCursorPosition.X;
		*y = (int)pkt.dwCursorPosition.Y;
	}
	else {
		*x = 0;
		*y = 0;
	}


}

void getrange(int* maxx, int* maxy) {
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO pkt;
	if (GetConsoleScreenBufferInfo(ekran, &pkt))
	{
		*maxx = (int)pkt.srWindow.Right - pkt.srWindow.Left + 1;
		*maxy = (int)pkt.srWindow.Bottom - pkt.srWindow.Top + 1;
	}
	else {
		*maxx = 0;
		*maxy = 0;
	}
}

void getscreen(int* xorg, int* yorg, int* xend, int* yend) {
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO pkt;
	if (GetConsoleScreenBufferInfo(ekran, &pkt))
	{
		*xorg = pkt.srWindow.Left;
		*yorg = pkt.srWindow.Top;
		*xend = pkt.srWindow.Right;
		*yend = pkt.srWindow.Bottom;
	}
	else {
		*xorg = 0;
		*yorg = 0;
		*xend = 0;
		*yend = 0;
	}
}

int xyscanf(int x, int y, const char* format, ...)
{
	HANDLE klaw = GetStdHandle(STD_INPUT_HANDLE);
	CHAR txt[150];
	DWORD znaki;
	BOOL flag;
	va_list arg;
	int wynik;

	setcursor(x, y);
	va_start(arg, format);
	flag = ReadConsole(klaw, txt, 150, &znaki, NULL);
	if (!flag)wynik = EOF;
	else
	{
		while (znaki > 0 && (txt[znaki - 1] == "\n" || txt[znaki - 1] == '\r'))znaki--;
		txt[znaki] = '\0';
		wynik = vsscanf(txt, format, arg);
	}
	va_end(arg);
	return wynik;
}

int xyprintf(int x, int y, const char* format, ...)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CHAR txt[150];
	DWORD znaki;
	BOOL flag;

	va_list arg;
	va_start(arg, format);
	int wynik = vsprintf(txt, format, arg);
	if (wynik >= 0)
	{
		znaki = (DWORD)wynik;
		setcursor(x, y);
		flag = WriteConsole(ekran, txt, znaki, NULL, NULL);
		if (!flag)wynik = EOF;
	}
	va_end(arg);
	return wynik;
}

void clear(void)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	COORD poczatek = { 0,0 };
	DWORD znaki;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	FillConsoleOutputCharacter(ekran, ' ', bufor.dwSize.X * bufor.dwSize.Y, poczatek, &znaki);
	SetConsoleCursorPosition(ekran, poczatek);
}

BOOL ClearConsole(HANDLE ekran) // implementacja wlasna
{
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	COORD poczatek = { 0,0 };
	DWORD znaki;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	FillConsoleOutputCharacter(ekran, ' ', bufor.dwSize.X * bufor.dwSize.Y, poczatek, &znaki);
	SetConsoleCursorPosition(ekran, poczatek);
	return GetLastError() == ERROR_SUCCESS;
}