#pragma once

#include<vector>
#include <map>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <algorithm>
#include <cctype>
#include <string>

#include"Proces.h"


class OperacjaNaProcesach
{
private:
	std::map<std::string, std::vector<Proces>> _listaProcesow2;
	std::vector<Proces> _listaProcesow;//Pole przechowujace procesy
	int _iloscProcesow = 0; //Pole przechowuj¹ce ilosc procesów w vektorze _listaProcesów

public:
	//std::vector<int> listaIdProcesow;

	//Konstruktory 
	OperacjaNaProcesach();

	//Dekonstruktor
	~OperacjaNaProcesach();

	//Gettery

	int getIloscProcesow() { return _iloscProcesow; }

	//Metody

	void ZaladujProcesy();
	void ZabijProces(int i_id);
	Proces getProces(int i_id);
	Proces getProcesSort(int i_id);
};

