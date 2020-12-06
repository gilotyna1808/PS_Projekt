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
		printf("%s", txt.c_str());
		SetConsoleTextAttribute(hStdOut, (koloNieAktywny | 1));
	}
};

//PROBA--------------------------
struct Strony
{
	int dlugoscStrony = 20;
	OperacjaNaProcesach* operacja;
	int wszystkieProcesy = operacja->getIloscProcesow();
	int poczatkowa = 1;
	int pozostale = wszystkieProcesy - dlugoscStrony;
};



class Wyswietlanie
{
private:
	int max_x = 120;//Maksymalna wartosc wspolrzednej x
	int max_y = 30;//Maksymalna wartosc wspolrzednej y
	int kolumny[5]{ 1,5,35,47,70 };//Wspolrzedna x poczatku kolumny ++(Plan)Do zmiany na vektor z mozliwoscia modyfikacji
	int przesuniecie = 0;
	int nr_strony = 1;

public:
	Tekst menu{ "Menu: ",true };
	Tekst opcja1{ "1) Wyswietl ",true };
	Tekst opcja2{ "2) Usun " };
	vector<Proces> procesy;
	int aktualnaStrona = 1;
	int aktualnaWartoscMinimalna = 1;
	int aktualnaWartoscMaksymalna = 20;

	Wyswietlanie();
	~Wyswietlanie();

	void WyswietlOpis();
	void WyswietlTabele(int i_row);
	void WyswietlMenu(int y = 30);
	void WyswietlProcesy(OperacjaNaProcesach* dane, int min, int max); //Wyswietlanie danych o procesach
	int getPrzesuniecie();
	std::string NazwaPriorytetu(DWORD i_priorytet);
	void Wypisz(int i_poczatek, int i_koniec, std::string i_txt);
	void KontrolerWyswietlania(OperacjaNaProcesach* dane, int iloscProcesow, bool usuwanie);
};

