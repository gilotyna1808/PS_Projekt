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
	int _nr;
	std::string _nazwa;
	int _idProcesu;
	DWORD _priorytetProcesu;
	//...
public:
	//Pola przechowuj¹ce informacje o procesie Chwilowo publiczne
	
	//Konstruktory
	Proces(int i_nr,std::string i_nazwa, int i_idProcesu, DWORD i_priorytetProcesu);

	//Gettery i Settery

	std::string getNazwa() { return _nazwa; }
	int getIdProcesu() { return _idProcesu; }
	DWORD getPriorytet() { return _priorytetProcesu; }
	int getNr(){ return _nr; }
	//Metody
	void ZabijProces();
	void ZabijProcesOID(int i_id);
};
