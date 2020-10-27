#pragma once

#include<string>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

class Proces
{
private:
	
	//...
public:
	//Pola przechowuj¹ce informacje o procesie Chwilowo publiczne
	std::string _nazwa;
	int _idProcesu;
	//Konstruktory
	Proces(std::string i_nazwa, int i_idProcesu);

	//Metody
	void ZabijProces();
	void ZabijProcesOID(int i_id);
};
