#pragma once

#include<vector>
#include <map>
#include <windows.h>
#include <Psapi.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <algorithm>
#include <iostream>

#include"Proces.h"


class OperacjaNaProcesach
{
private:
	std::map<std::string, std::vector<Proces>> _listaProcesow2;
	std::vector<Proces> _listaProcesow;//Pole przechowujace procesy
	int _iloscProcesow = 0; //Pole przechowujące ilosc procesów w vektorze _listaProcesów
	int _iloscProcesorow = -1;

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
	bool czySystemowy(Proces i_proces);

	void Genocide();

};

