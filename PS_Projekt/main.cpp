#include <iostream>
#include <Windows.h>

#include"Wyswietlanie.h"
#include"OperacjeNaProcesach.h"
#include"Proces.h"

void main() {
	Proces temp("test", 0);//Testowe do usuniecia
	OperacjaNaProcesach oP;
	Wyswietlanie w;
	int x;
	oP.ZaladujProcesy();
	w.Wyswietl(&oP);
	std::cout << "Wpisz id Procesu do zabicia" << std::endl;
	std::cin >> x;
	temp.ZabijProcesOID(x);
}