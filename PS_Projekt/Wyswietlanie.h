#pragma once

#include<iostream>
#include<string>

#include "OperacjeNaProcesach.h"
#include "xyio.h"

struct Tekst
{
	std::string txt; //Przechowanie tekstu
	bool nowaLinia = false; //Przechowywanie czy wypisane w nowej lini
	bool aktywny = false; //Przechowwyane czy aktwyne np. menu opcja usun
	int koloNieAktywny = 15; // Kolor tekstu jezeli nie aktywne
	int kolorAktywny = FOREGROUND_GREEN; // Kolor tekstu jezeli aktywne
	void Wypisz()
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (nowaLinia)printf("\n");
		if (aktywny) 
		{
			SetConsoleTextAttribute(hStdOut, (kolorAktywny | 1));
		}
		else
		{
			SetConsoleTextAttribute(hStdOut, (koloNieAktywny | 1));
		}
		printf("%s",txt.c_str());
		SetConsoleTextAttribute(hStdOut, (koloNieAktywny | 1));
	}
};

class Wyswietlanie
{
private:
	int max_x=100;//Maksymalna wartosc wspolrzednej x
	int max_y=30;//Maksymalna wartosc wspolrzednej y
	int kolumny[4]{1,5,75,90};//Wspolrzedna x poczastku kolumny ++(Plan)Do zmiany na vektor z mozliwoscia modyfikacji
	
public:
	Tekst menu{ "Menu:",true };
	Tekst opcja1{ "1)Wyswielt",true };
	Tekst opcja2{ " 2)Usun" };

	Wyswietlanie();
	~Wyswietlanie();

	void WyswietlOpis();
	void WyswietlTabele(int i_row);
	void WyswietlMenu(int y=30);
	void WyswietlProcesy(OperacjaNaProcesach* dane); //Wyswietlanie danych o procesach
};

