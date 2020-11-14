#include <iostream>
#include <Windows.h>
#include <algorithm>
#include"Wyswietlanie.h"
#include"OperacjeNaProcesach.h"
#include"Proces.h"

void main() {

	OperacjaNaProcesach oP;
	Wyswietlanie w;
	//Strony s;

	do
	{
		w.WyswietlMenu(oP.getIloscProcesow() + w.getPrzesuniecie());//testowo dane (+13)----------------------------------
		int wybor;
		std::cin >> wybor;
		switch (wybor)
		{
		case 1:
			clear();
			oP.ZaladujProcesy();
			//w.WyswietlProcesy(&oP);
			w.KontrolerWyswietlania(&oP, oP.getIloscProcesow(), false);
			break;
		case 2:
			clear();
			int procesNR;
			system("cls");
			oP.ZaladujProcesy();
			//w.WyswietlProcesy(&oP);
			w.KontrolerWyswietlania(&oP, oP.getIloscProcesow(), true);
			setcursor(0, 24);
			std::cout << "Wpisz NR Procesu do zabicia" << std::endl;
			std::cin >> procesNR;

			if (procesNR > 0 && procesNR <= oP.getIloscProcesow()) 
			{
				//Walidacja przed usuniêciem trwaj¹cego procesu
				//spe³nione je¿eli lista procesów zawiera podane ID
				system("cls");
				std::cout << "Czy na pewno chcesz zamknac proces " << procesNR << "(" + oP.getProces(procesNR).getNazwa() + ") ?" << endl;
				std::cout << "y - tak, n - nie" << endl;
				char potwierdzenieUsuniecia;
				std::cin >> potwierdzenieUsuniecia;

				switch (potwierdzenieUsuniecia)
				{
				case 'y':
					oP.ZabijProces(procesNR);
					std::cout << "Proces zostal zamkniety pomyslnie!" << endl;
					system("pause");
					break;
				case 'n':
					break;
				}
			}
			else 
			{
				std::cout << "Proces o podanym ID nie istnieje!" << endl;
				system("pause");
			}
			break;
		}
		if (wybor == 0)break;
	} while (true);

	//cout << s.dlugoscStrony << endl;
}