#pragma once

#include<string>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>


struct ProcesExp
{
	int linia;//Przechowuje linie wyst¹pienia wyj¹tku
	std::string txt;
	std::string className = "Proces";

};



class Proces
{
private:
	std::string _nazwa;
	int _idProcesu;
	DWORD _priorytetProcesu;
	//...
public:
	//Pola przechowuj¹ce informacje o procesie Chwilowo publiczne
	
	//Konstruktory
	Proces(std::string i_nazwa, int i_idProcesu, DWORD i_priorytetProcesu);

	//Gettery i Settery

	std::string getNazwa() { return _nazwa; }
	int getIdProcesu() { return _idProcesu; }
	DWORD getPriorytet() { return _priorytetProcesu; }
	//Metody
	void ZabijProces();
	void ZabijProcesOID(int i_id);
};
