#include <iostream>
#include <Windows.h>
#include <algorithm>
#include"Wyswietlanie.h"
#include"OperacjeNaProcesach.h"
#include"Proces.h"

void main() {

	OperacjaNaProcesach oP;
	Wyswietlanie w(oP);
	
	w.Ekran();
}