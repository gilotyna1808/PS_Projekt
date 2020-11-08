#pragma once

#include<vector>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

#include"Proces.h"

class OperacjaNaProcesach
{
private:
	std::vector<Proces> _listaProcesow;//Pole przechowujace procesy
	int _iloscProcesow = 0; //Pole przechowuj�ce ilosc proces�w w vektorze _listaProces�w

public:
	//Konstruktory 
	OperacjaNaProcesach();

	//Dekonstruktor
	~OperacjaNaProcesach();

	//Gettery

	int getIloscProcesow() { return _iloscProcesow;}

	//Metody
	
	void ZaladujProcesy();
	void ZabijProces(int i_id);
	Proces getProces(int i_id);
};

