#include"Wyswietlanie.h"

Wyswietlanie::Wyswietlanie()
{
}

Wyswietlanie::~Wyswietlanie()
{
}



void Wyswietlanie::WyswietlProcesy(OperacjaNaProcesach* dane) {
	int iloscProcesow = dane->getIloscProcesow();
	for (int i = 0; i < iloscProcesow;i++) {

		std::cout <<"NR: "<< i<< " Proces: " << dane->getProces(i).getNazwa() << "ID:" << dane->getProces(i).getIdProcesu() << std::endl;
	}
}