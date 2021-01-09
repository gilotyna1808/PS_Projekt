#pragma once

#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <conio.h>
#include <string>
#include "xyio.h"
#include "OperacjeNaProcesach.h"
#pragma warning(disable:4996)

struct TEXTMENU
{
	std::string txt; //Przechowanie tekstu
	int curX = NULL; //wspó³rzêdna X
	int curY = NULL; //wspó³rzêdna Y
	bool aktywny = false; //Przechowwyane czy aktwyne np. menu opcja usun
	int koloNieAktywny = 15; // Kolor tekstu jezeli nie aktywne
	int kolorAktywny = 4; // Kolor tekstu jezeli aktywne

	void Wypisz()
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (aktywny)
		{
			SetConsoleTextAttribute(hStdOut, (kolorAktywny | 1));
		}
		else
		{
			SetConsoleTextAttribute(hStdOut, (koloNieAktywny | 1));
		}
		xyprintf(curX, curY, txt.c_str());
		SetConsoleTextAttribute(hStdOut, (koloNieAktywny | 1));
	}
};
struct TEXTTABELA
{
	int wiersz; //Prezehowuje informacje o wierszu w którym jest wyswietlana
	bool aktywny = false; //Przechowuje informacje o tym czy opcja jest wybrana
	int koloNieAktywny = 15; // Kolor tekstu jezeli nie aktywne
	int kolorAktywny = 9; // Kolor tekstu jezeli aktywne
	int tloKoloNieAktywny = 1; // Kolor tekstu jezeli nie aktywne
	int tloKolorAktywny = 0; // Kolor tekstu jezeli aktywne

	void Wypisz(string txt)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (aktywny)
		{
			SetConsoleTextAttribute(hStdOut, (kolorAktywny | tloKolorAktywny));
		}
		else
		{
			SetConsoleTextAttribute(hStdOut, (koloNieAktywny | tloKoloNieAktywny));
		}
		xyprintf(0, wiersz, txt.c_str());
		SetConsoleTextAttribute(hStdOut, (koloNieAktywny | tloKoloNieAktywny));
	}
};

class Wyswietlanie
{
private:
	int max_x = 120;//Maksymalna wartosc wspolrzednej x
	int max_y = 30;//Maksymalna wartosc wspolrzednej y
	int kolumny[6]{ 1,5,35,47,70,76 };//Wspolrzedna x poczatku kolumny ++(Plan)Do zmiany na vektor z mozliwoscia modyfikacji
	int przesuniecie = 0;
	int nr_strony = 1;

public:

	Wyswietlanie(OperacjaNaProcesach i_procesy) :
		_procesy(i_procesy) {};
	
	void Ekran();

};

