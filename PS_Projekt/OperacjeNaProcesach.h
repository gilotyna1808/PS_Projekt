#pragma once

#include<vector>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#include"Proces.h"

class OperacjaNaProcesach
{
private:

	

public:
	std::vector<Proces> _listaProcesow;//Chwilowo publiczne
	OperacjaNaProcesach();
	~OperacjaNaProcesach();

	void ZaladujProcesy();
};

