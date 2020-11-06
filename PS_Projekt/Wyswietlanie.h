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
	Tekst menu{ "Menu" };
	Tekst opcja1{"1)Wyswielt:",true};
	Tekst opcja2{" 2)Usun"};
public:
	Wyswietlanie();
	~Wyswietlanie();

	void WyswietlOpis();
	void WyswietlTabele();
	void WyswietlMenu() 
	{
		int max_x, max_y;
		getrange(&max_x, &max_y);
		setcursor(0, max_y - 2);
		menu.Wypisz();
		opcja1.Wypisz();
		opcja2.Wypisz();

	}
	void WyswietlProcesy(OperacjaNaProcesach* dane); //Wyswietlanie danych o procesach
};

