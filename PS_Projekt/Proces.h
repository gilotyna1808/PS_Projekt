#pragma once

#include<string>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>


class Proces
{
private:
	std::string _nazwa;
	int _idProcesu;
	//...
public:
	//Pola przechowuj¹ce informacje o procesie Chwilowo publiczne
	
	//Konstruktory
	Proces(std::string i_nazwa, int i_idProcesu);

	//Gettery i Settery

	std::string getNazwa() { return _nazwa; }
	int getIdProcesu() { return _idProcesu; }

	//Metody
	void ZabijProces();
	void ZabijProcesOID(int i_id);
};
