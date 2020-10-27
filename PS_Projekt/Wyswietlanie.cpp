#include"Wyswietlanie.h"

Wyswietlanie::Wyswietlanie()
{
}

Wyswietlanie::~Wyswietlanie()
{
}


void Wyswietlanie::Wyswietl(OperacjaNaProcesach* dane) {
	for (Proces p : dane->_listaProcesow) {

		std::cout << "Proces: " << p._nazwa << " ID:" <<p._idProcesu << std::endl;
	}
}