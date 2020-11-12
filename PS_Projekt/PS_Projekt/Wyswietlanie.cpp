#include"Wyswietlanie.h"

Wyswietlanie::Wyswietlanie()
{
	int x, y;
	getrange(&x, &y);
	max_x = x;
	max_y = y;
}

Wyswietlanie::~Wyswietlanie()
{
}

void Wyswietlanie::WyswietlMenu(int y)
{
	setcursor(0, y);
	menu.Wypisz();
	opcja1.Wypisz();
	opcja2.Wypisz();
	printf("\n");
}

void Wyswietlanie::WyswietlOpis()
{
	setcursor(kolumny[0] - 1, 1);
	printf("|");
	printf("%d", 0);
	setcursor(kolumny[1] - 1, 1);
	printf("|");
	setcursor(kolumny[2] - 1, 1);
	printf("|");
	setcursor(kolumny[3], 1);
	printf("|");

	setcursor(kolumny[0], 1);
	printf("NR");
	setcursor(kolumny[1], 1);
	printf("Nazwa");
	setcursor(kolumny[2], 1);
	printf("ID Procesu");
}
void Wyswietlanie::WyswietlTabele(int i_row)
{
	setcursor(0, i_row);
	for (size_t i = 0; i < kolumny[3]; i++)
	{
		if (i == (kolumny[0] - 1) || i == (kolumny[1] - 1) || i == (kolumny[2] - 1))printf("+");
		else printf("-");
	}
	printf("+");
}






void Wyswietlanie::WyswietlProcesy(OperacjaNaProcesach* dane) {
	int iloscProcesow = dane->getIloscProcesow();
	int licznik = 0;
	//int przesuniecie = 0;
	//przesuniecie
	int j = 1;
	WyswietlTabele(0);
	for (int i = 1; i < iloscProcesow;i++) { //ZREZYGNOWANIE Z WYSWIETLANIA PROCESU o numerze 0
		setcursor(kolumny[0]-1, j+1);
		printf("|");
		printf("%d", i);
		setcursor(kolumny[1]-1, j+1);
		printf("|");
		printf("%s",dane->getProces(i).getNazwa().c_str());
		setcursor(kolumny[2]-1, j+1);
		printf("|");
		printf("%d", dane->getProces(i).getIdProcesu());
		setcursor(kolumny[3], j + 1);
		printf("|");
		//std::cout << "NR: " << i << " Proces: " << dane->getProces(i).getNazwa() << "ID:" << dane->getProces(i).getIdProcesu() << std::endl;
		licznik++;
		j++;
		if (licznik == 20)
		{
			licznik = 0;
			przesuniecie++;
			setcursor(kolumny[0] - 1, j + 1);
			//printf("|");
			printf("%s", " ");
			setcursor(kolumny[1] - 1, j + 1);
			//printf("|");
			printf("%s", " ");
			setcursor(kolumny[2] - 1, j + 1);
			//printf("|");
			printf("%s", " ");
			setcursor(kolumny[3], j + 1);
			//printf("|");
			j++;
		}
	}
	WyswietlTabele(iloscProcesow + przesuniecie);  //zmiany: (+20) "na brudno"


}
int Wyswietlanie::getPrzesuniecie()
{
	return przesuniecie;
}