#include <iostream>
#include <Windows.h>

#include"Wyswietlanie.h"
#include"OperacjeNaProcesach.h"
#include"Proces.h"

void main() {
	OperacjaNaProcesach oP;
	Wyswietlanie w;
	int x;
	w.WyswietlMenu();
	/*oP.ZaladujProcesy();
	w.WyswietlProcesy(&oP);
	std::cout << "Wpisz NR Procesu do zabicia" << std::endl;
	std::cin >> x;
	oP.ZabijProces(x);
	*/
}