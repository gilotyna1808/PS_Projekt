#include "Procesor.h"

Procesor::Procesor() :
	_cpuUse(-1), _lastRun(0), _iloscPrzejsc(0) 
{
	ZeroMemory(&_czasProcesuJadro, sizeof(FILETIME));
	ZeroMemory(&_czasProcesuUzytkownik, sizeof(FILETIME));
	ZeroMemory(&_czasSystemowyJadro, sizeof(FILETIME));
	ZeroMemory(&_czasSystemowyUzytkownik, sizeof(FILETIME));
}

int Procesor::GetUsage() 
{
	int tempCpu = _cpuUse;

	if (::InterlockedIncrement(&_iloscPrzejsc) == 1)
	{
		if (!czyPonowicPomiar()) {
			::InterlockedIncrement(&_iloscPrzejsc);
			return tempCpu;
		}

		FILETIME czasSysBez, czasSysJ, czasSysU, czasProcS, czasProcK, czasProcJ, czasProcU;
		if (!GetSystemTimes(&czasSysBez, &czasSysJ, &czasSysU) || !GetProcessTimes(GetCurrentProcess(), &czasProcS, &czasProcK, &czasProcJ, &czasProcU)) 
		{
			::InterlockedIncrement(&_iloscPrzejsc);
			return tempCpu;
		}

		if(!czyPierwszeUruchomienie())
		{
			ULONGLONG sysKarnelDiff = czas(czasSysJ, _czasSystemowyJadro);
			ULONGLONG sysUserDiff = czas(czasSysU, _czasSystemowyUzytkownik);
			ULONGLONG procKarnelDiff = czas(czasProcJ, _czasProcesuJadro);
			ULONGLONG procUserDiff = czas(czasProcU, _czasProcesuUzytkownik);

			ULONGLONG sysCalosc = sysKarnelDiff + sysUserDiff;
			ULONGLONG procCalosc = procKarnelDiff + procUserDiff;

			if (sysCalosc > 0) {
				_cpuUse = (int)((100.0 * procCalosc) / sysCalosc);
			}
		}
		
		_czasProcesuJadro = czasProcJ;
		_czasProcesuUzytkownik = czasProcU;
		_czasSystemowyJadro = czasSysJ;
		_czasSystemowyUzytkownik = czasSysU;

		_lastRun = GetTickCount64();
		tempCpu = _cpuUse;
	}
	::InterlockedDecrement(&_iloscPrzejsc);
	return tempCpu;
}


double Procesor::GetUsage(int i_pid)
{
	double tempCpu = _cpuUse;

	if (::InterlockedIncrement(&_iloscPrzejsc) == 1)
	{
		if (!czyPonowicPomiar()) {
			::InterlockedDecrement(&_iloscPrzejsc);
			return tempCpu;
		}
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, i_pid);
		FILETIME czasSysBez, czasSysJ, czasSysU, czasProcS, czasProcK, czasProcJ, czasProcU;
		if (!GetSystemTimes(&czasSysBez, &czasSysJ, &czasSysU) || !GetProcessTimes(hProcess, &czasProcS, &czasProcK, &czasProcJ, &czasProcU))
		{
			::InterlockedDecrement(&_iloscPrzejsc);
			return tempCpu;
		}

		if (!czyPierwszeUruchomienie())
		{
			ULONGLONG sysKarnelDiff = czas(czasSysJ, _czasSystemowyJadro);
			ULONGLONG sysUserDiff = czas(czasSysU, _czasSystemowyUzytkownik);
			ULONGLONG procKarnelDiff = czas(czasProcJ, _czasProcesuJadro);
			ULONGLONG procUserDiff = czas(czasProcU, _czasProcesuUzytkownik);

			ULONGLONG sysCalosc = sysKarnelDiff + sysUserDiff;
			ULONGLONG procCalosc = procKarnelDiff + procUserDiff;
			
			if (sysCalosc > 0) {
				_cpuUse = (double)((100.0 * procCalosc) / sysCalosc);
				//std::cout << _cpuUse << std::endl;
			}
			
		}

		_czasProcesuJadro = czasProcJ;
		_czasProcesuUzytkownik = czasProcU;
		_czasSystemowyJadro = czasSysJ;
		_czasSystemowyUzytkownik = czasSysU;

		_lastRun = GetTickCount64();

		tempCpu = _cpuUse;
	}
	::InterlockedDecrement(&_iloscPrzejsc);
	
	return tempCpu;
}

ULONGLONG Procesor::czas(const FILETIME& i_czasP, const FILETIME& i_czasK) 
{
	LARGE_INTEGER pocztek, koniec;
	pocztek.LowPart = i_czasP.dwLowDateTime;
	pocztek.HighPart = i_czasP.dwHighDateTime;

	koniec.LowPart = i_czasK.dwLowDateTime;
	koniec.HighPart = i_czasK.dwHighDateTime;

	return pocztek.QuadPart - koniec.QuadPart;
}

bool Procesor::czyPonowicPomiar() 
{
	const int czasMin = 0;
	ULONGLONG tickCount = GetTickCount64();
	return (tickCount - _lastRun) > czasMin;
}