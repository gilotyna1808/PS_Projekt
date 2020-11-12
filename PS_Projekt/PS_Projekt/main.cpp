#include <iostream>
#include <Windows.h>

#include"Wyswietlanie.h"
#include"OperacjeNaProcesach.h"
#include"Proces.h"

void main() {

	OperacjaNaProcesach oP;
	Wyswietlanie w;
	//Strony s;

	do
	{
		w.WyswietlMenu(oP.getIloscProcesow()+w.getPrzesuniecie());//testowo dane (+13)----------------------------------
		int wybor;
		std::cin >> wybor;
		switch (wybor)
		{
		case 1:
			clear();
			oP.ZaladujProcesy();
			w.WyswietlProcesy(&oP);
			w.WyswietlOpis();
			break;
		case 2:
			clear();
			int procesID;
			system("cls");
			oP.ZaladujProcesy();
			w.WyswietlProcesy(&oP);
			w.WyswietlOpis();
			setcursor(0, oP.getIloscProcesow()+2);
			std::cout << "Wpisz NR Procesu do zabicia" << std::endl;
			std::cin >> procesID;
			oP.ZabijProces(procesID);
			break;
		}
		if (wybor == 0)break;
	} while (true);

	//cout << s.dlugoscStrony << endl;
}