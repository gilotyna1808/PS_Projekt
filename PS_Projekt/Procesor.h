#pragma once

#include <Windows.h>
#include <iostream>
class Procesor
{
private:

	ULONGLONG czas(const FILETIME& i_czasP, const FILETIME& i_czasK);
	bool czyPonowicPomiar();
	inline bool czyPierwszeUruchomienie()const { return (_lastRun == 0); }

	FILETIME _czasSystemowyJadro;
	FILETIME _czasSystemowyUzytkownik;

	FILETIME _czasProcesuJadro;
	FILETIME _czasProcesuUzytkownik;

	double _cpuUse;
	ULONGLONG _lastRun;
	volatile long _iloscPrzejsc;

public:

	Procesor();

	int GetUsage();
	double GetUsage(int);
};