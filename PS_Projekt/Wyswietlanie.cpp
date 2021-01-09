#include"Wyswietlanie.h"

void Wyswietlanie::Menu(TEXTMENU* menu, int size)
{
	for (int i = 0; i < size; i++)
	{
		menu[i].Wypisz();
	}
}

std::string Wyswietlanie::createLine(int* kol, std::string nr, std::string nazwa, std::string id, std::string priorytet, std::string cpu, std::string pamiec)
{
	string temp = "|";
	temp += nr;
	std::string s1(kol[0] - temp.size(), ' ');
	temp += (s1 + "|");
	temp += nazwa;
	std::string s2(kol[1] - temp.size(), ' ');
	temp += (s2 + "|");
	temp += id;
	std::string s3(kol[2] - temp.size(), ' ');
	temp += (s3 + "|");
	temp += priorytet;
	std::string s4(kol[3] - temp.size(), ' ');
	temp += (s4 + "|");
	temp += cpu;
	std::string s5(kol[4] - temp.size(), ' ');
	temp += (s5 + "|");
	temp += pamiec;
	std::string s6(kol[5] - temp.size(), ' ');
	temp += (s6 + "|");
	return temp;
}

std::string Wyswietlanie::createLineBlank(int* kol)
{
	string temp = "|";
	std::string s1(kol[0] - temp.size(), ' ');
	temp += (s1 + "|");
	std::string s2(kol[1] - temp.size(), ' ');
	temp += (s2 + "|");
	std::string s3(kol[2] - temp.size(), ' ');
	temp += (s3 + "|");
	std::string s4(kol[3] - temp.size(), ' ');
	temp += (s4 + "|");
	std::string s5(kol[4] - temp.size(), ' ');
	temp += (s5 + "|");
	std::string s6(kol[5] - temp.size(), ' ');
	temp += (s6 + "|");
	return temp;
}

string Wyswietlanie::createBorder(int* kol)
{
	string temp;
	temp += "+";
	std::string s1(kol[0] - temp.size(), '-');
	temp += (s1 + "+");
	std::string s2(kol[1] - temp.size(), '-');
	temp += (s2 + "+");
	std::string s3(kol[2] - temp.size(), '-');
	temp += (s3 + "+");
	std::string s4(kol[3] - temp.size(), '-');
	temp += (s4 + "+");
	std::string s5(kol[4] - temp.size(), '-');
	temp += (s5 + "+");
	std::string s6(kol[5] - temp.size(), '-');
	temp += (s6 + "+");
	return temp;
}

std::string Wyswietlanie::NazwaPriorytetu(DWORD i_priorytet)
{
	switch (i_priorytet)
	{
	case 4:
		return "Niski";
		break;
	case 6:
		return "Ponizej normalnego";
		break;
	case 8:
		return "Normalny";
		break;
	case 10:
		return "Powyzej normalnego";
		break;
	case 13:
		return "Wysoki";
		break;
	case 24:
		return "Czasu Rzeczywistego";
		break;
	default:
		return "Normalny";
		break;
	}
}

std::string Wyswietlanie::TextZapis(int* kol, int nr, std::string i_txt)
{
	int k, p;
	if (nr >= 0 && nr < 6) 
	{
		if (nr == 0)p = 0;
		else p = kol[nr - 1];
		k = kol[nr];
		int rozmiar = k-p;
		if (i_txt.size() >= rozmiar)
		{
			i_txt = i_txt.substr(0, rozmiar-1);
		}
		return i_txt;
	}
	return "";
}

void Wyswietlanie::Tabela(TEXTTABELA* tabela, int* kol,bool* sort, int strona, int ilWierszy)
{
	string tab[4];
	tab[0] = createBorder(kol);
	tab[1] = createLine
	(
		kol,
		TextZapis(kol, 0, "NR"),
		TextZapis(kol, 1, "Nazwa"),
		TextZapis(kol, 2, "ID Procesu"),
		TextZapis(kol, 3, "Priorytet"),
		TextZapis(kol, 4, "CPU[%%]"),
		TextZapis(kol, 5, "Pamiec[K]")
	);
	tab[2] = createBorder(kol);
	tab[3] = createBorder(kol);

	for (int i = 0; i < 24; i++)
	{
		if (i < 3)tabela[i].Wypisz(tab[i]);
		else if (i == 23)tabela[i].Wypisz(tab[3]);
		else
		{
			if (i < ilWierszy + 2) 
			{
				try
				{
					Proces p;
					if (sort[0])	p = _procesy.getProces((i - 2) + (strona * 20));
					if (sort[1]) p = _procesy.getProcesSort((i - 2) + (strona * 20));
					p.getCpuUsage();
					string str = createLine(
						kol,
						TextZapis(kol, 0, std::to_string(p.getNr())),
						TextZapis(kol, 1, p.getNazwa()),
						TextZapis(kol, 2, std::to_string(p.getIdProcesu())),
						TextZapis(kol, 3, NazwaPriorytetu(p.getPriorytet())),
						TextZapis(kol, 4, p.getCpuUsage()),
						TextZapis(kol, 5, std::to_string(p.getMem('K')))
					);
					tabela[i].Wypisz(str);
				}
				catch (const std::exception&)
				{

				}
			}
			else tabela[i].Wypisz(createLineBlank(kol));
		}
	}
}

void Wyswietlanie::ZmianaTabeli(int* kol)
{
	clear();
	int x = 200;
	int k = 0;
	std::cout << "Nowy wyglad tabeli: " << std::endl;
	while (x > 95 || x < 2)
	{
		std::cout << "Podaj dlugosc kolumny nr [2-95]:" << std::endl;
		std::cin >> x;
	}
	kol[0] = x;
	x = 200;

	k = (100 - kol[0] - 2);
	while (x > k || x < 1)
	{
		std::cout << "Podaj dlugosc kolumny nazwa [2-" << k << "]:" << std::endl;
		std::cin >> x;
	}
	kol[1] = kol[0] + x;
	x = 200;

	k = (100 - kol[1] - 3);
	while (x > k || x < 2)
	{
		std::cout << "Podaj dlugosc kolumny ID Procesu [2-" << k << "]:" << std::endl;
		std::cin >> x;
	}
	kol[2] = kol[1] + x;
	x = 200;

	k = (100 - kol[2] - 3);
	while (x > k || x < 2)
	{
		std::cout << "Podaj dlugosc kolumny Priorytet [2-" << k << "]:" << std::endl;
		std::cin >> x;
	}
	kol[3] = kol[2] + x;
	x = 200;

	k = (100 - kol[3] - 2);
	while (x > k || x < 2)
	{
		std::cout << "Podaj dlugosc kolumny Cpu[%%] [2-" << k << "]:" << std::endl;
		std::cin >> x;
	}
	kol[4] = kol[3] + x;
	x = 200;

	k = (100 - kol[4]);
	while (x > k || x < 2)
	{
		std::cout << "Podaj dlugosc kolumny Pamiec [2-" << k << "]:" << std::endl;
		std::cin >> x;
	}
	kol[5] = kol[4] + x;
}

void Wyswietlanie::DialogZamykanieProcesu(int wyborTabela,int strona,bool* sortowanie)
{
	//Czyszczenie Ekranu
	clear();
	//Zmienne 
	Proces p;
	int wybor=0;
	bool flagWybor=false;
	bool flagTak=false;
	//Pobieranie wybranego procesu

	if (sortowanie[0])p = _procesy.getProces(wyborTabela + 1 + (20 * strona));
	if (sortowanie[1])p = _procesy.getProcesSort(wyborTabela + 1 + (20 * strona));
	
	std::cout << "Czy chcesz zamknac: " << p.getNazwa() << std::endl;
	while (!flagWybor)
	{
		TEXTMENU tak = TEXTMENU{ "Tak",50,15,flagTak,15,4 };
		TEXTMENU nie = TEXTMENU{ "Nie",57,15,!flagTak,15,4 };
		tak.Wypisz();
		nie.Wypisz();
		wybor = getch();
		switch (wybor)
		{
		case 'a':
			flagTak = true;
			break;
		case 'd':
			flagTak = false;
			break;
		case 13:
			flagWybor = true;
			break;
		default:
			break;
		}
	}
	if (flagTak)p.ZabijProces();
}

void Wyswietlanie::WypiszInformacje(int wyborTabela, int strona, bool* sortowanie)
{
	//Czyszczenie Ekranu
	clear();
	//Zmienne 
	Proces p;
	int wybor = 0;
	bool flagWybor = false;
	bool flagTak = false;
	//Pobieranie wybranego procesu

	if (sortowanie[0])p = _procesy.getProces(wyborTabela + 1 + (20 * strona));
	if (sortowanie[1])p = _procesy.getProcesSort(wyborTabela + 1 + (20 * strona));
	//Wypisywanie

	std::cout << "Nazwa Procesu:" << std::endl;
	std::cout << p.getNazwa() << std::endl;
	std::cout << "NR ID Procesu:" << std::endl;
	std::cout << p.getIdProcesu() << std::endl;
	std::cout << "Priorytet Procesu" << std::endl;
	std::cout << NazwaPriorytetu(p.getPriorytet()) << std::endl;
	std::cout << "Zuzycie procesora:" << std::endl;
	std::cout << p.getCpuUsage()<< std::endl;
	std::cout << "Zuzycie pamieci[kB]:" << std::endl;
	std::cout << p.getMem('K') << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Nacisnij dowolny klawisz aby kontynuowac" << std::endl;
	getch();
}

void Wyswietlanie::Ekran()
{
	//Czyszczenie ekranu
	setcursor(0, 0);
	for (int i = 0; i < 30; i++)std::cout << "" << std::endl;

	//Ustawienia Tabeli
	int kol[6]{ 4,34,45,55,62,100 };
	TEXTMENU menu[10] = {
		TEXTMENU { "+------------+",105,0,false },
		TEXTMENU { "+    MENU    +",105,1,false },
		TEXTMENU { "+------------+",105,2,false },
		TEXTMENU { "+ ZAMKNIJ    +",105,3,false },
		TEXTMENU { "+ PODGLAD    +",105,4,false },
		TEXTMENU { "+ SORT A     +",105,5,false },
		TEXTMENU { "+ SORT NR    +",105,6,false },
		TEXTMENU { "+ WYGLAD TAB +",105,7,false },
		TEXTMENU { "+ ZAMKNIJ W  +",105,8,false },
		TEXTMENU { "+------------+",105,9,false }
	};
	TEXTTABELA tabela[24] = {
		TEXTTABELA {0,false},
		TEXTTABELA {1,false},
		TEXTTABELA {2,false},
		TEXTTABELA {3,false},
		TEXTTABELA {4,false},
		TEXTTABELA {5,false},
		TEXTTABELA {6,false},
		TEXTTABELA {7,false},
		TEXTTABELA {8,false},
		TEXTTABELA {9,false},
		TEXTTABELA {10,false},
		TEXTTABELA {11,false},
		TEXTTABELA {12,false},
		TEXTTABELA {13,false},
		TEXTTABELA {14,false},
		TEXTTABELA {15,false},
		TEXTTABELA {16,false},
		TEXTTABELA {17,false},
		TEXTTABELA {18,false},
		TEXTTABELA {19,false},
		TEXTTABELA {20,false},
		TEXTTABELA {21,false},
		TEXTTABELA {22,false},
		TEXTTABELA {23,false}
	};

	//Zmienne sterujace
	bool flagMenu = false;
	bool flagTab = true;
	bool flag1enter = false;
	bool sortowanie[2]{
		true, //Sortowanie wg NR
		false //Sortowanie wg Nazwy
	};

	int key = 's';
	int wyborMenu = 0;
	int wyborTabela = 0;
	int strona = 0;
	int stronaMax = 1;

	//Dane
	_procesy.ZaladujProcesy();
	int rozmiar = _procesy.getIloscProcesow();
	while (key != 'k')
	{
		//Wypisywanie Legendy
		xyprintf(0, 25, "LEGENDA:");
		xyprintf(0, 26, "w- Do gory, s- Na dol, ENTER- wybierz");
		xyprintf(0, 27, "a- poprzednia strona, d- nastepna strona");
		xyprintf(0, 28, "t- przejdz do tabeli, m- przejdz do menu");
		xyprintf(0, 29, "k- koniec");

		//Tworzenie zbioru do wyswietlania
		_procesy.ZaladujProcesy();
		rozmiar = _procesy.getIloscProcesow();
		string daneWej[20]{};
		stronaMax = rozmiar / 20;
		if (rozmiar % 20)stronaMax++;

		//Wypisywanie Tabeli
		setcursor(0, 1);
		Tabela(tabela, kol,sortowanie, strona, (rozmiar - (strona * 20)));
		std::string str = ("Strona " + std::to_string(strona + 1) + "/" + std::to_string(stronaMax));
		xyprintf(0, 24, "                                                                         ");
		xyprintf(0, 24, str.c_str());

		//Wypisywanie Menu
		Menu(menu, 10);
		setcursor(20, 29);

		//Sterowanie
		key = getch();
		switch (key)
		{
		case 'w':
			if (flagMenu && wyborMenu > 0)wyborMenu--;
			if (flagTab && wyborTabela > 0)wyborTabela--;
			break;
		case 's':
			if (flagMenu && wyborMenu < 5)wyborMenu++;
			if (flagTab && wyborTabela < 20)wyborTabela++;
			break;
		case 'a':
			if (strona > 0)strona--;
			if (strona > stronaMax)strona = stronaMax;
			break;
		case 'd':
			if (strona + 1 < stronaMax)strona++;
			if (strona > stronaMax)strona = stronaMax;
			break;
		case 't':
			flagMenu = false;
			flagTab = true;
			flag1enter = false;
			break;
		case 'm':
			flagMenu = true;
			flagTab = false;
			flag1enter = false;
			break;
		case 13:
			if (flagMenu)
			{
				if (flag1enter)
				{
					if (wyborMenu == 0)
					{
						//Dialog Zamykania procesu
						if (rozmiar >= wyborTabela + (strona * 20)) 
						{
							DialogZamykanieProcesu(wyborTabela,strona,sortowanie);
						}
						flag1enter = false;
						flagMenu = false;
						flagTab = true;
					}
					else if (wyborMenu == 1)
					{
						//Wyswietlenie Pelnej nazwy
						if (rozmiar >= wyborTabela + (strona * 20))
						{
							WypiszInformacje(wyborTabela, strona, sortowanie);
						}
						flag1enter = false;
						flagMenu = false;
						flagTab = true;
					}
				}
				if (wyborMenu == 2)
				{
					//Sort Alfabetyczne
					clear();
					int xa;
					std::cout << "Zmiana sortowania na alfabetyczne: " << std::endl;
					sortowanie[0] = false;
					sortowanie[1] = true;
					strona = 0;
					xa = getch();
				}
				else if (wyborMenu == 3)
				{
					//Sortowanie wg nr
					clear();
					int xa;
					std::cout << "Zmiana sortowania na wg nr: " << std::endl;
					sortowanie[0] = true;
					sortowanie[1] = false;
					strona = 0;
					xa = getch();
				}
				else if (wyborMenu == 4)
				{
					//Dialog zmiany ustawien tabeli
					try {
					ZmianaTabeli(kol);
					}
					catch (exception e) {}
					strona = 0;
					flag1enter = false;
					flagMenu = false;
					flagTab = true;
				}
				else if (wyborMenu == 5)//Do zrobienia
				{
					// Zamykanie wszystkich procesow
					clear();
					int xa;
					std::cout << "Zamykanie wszystkich procesow: " << std::endl;
					xa = getch();
				}
				flag1enter = false;
			}
			else if (flagTab)
			{
				flagTab = false;
				flagMenu = true;
				flag1enter = true;
			}
			break;
		case 'k':
			break;
		default:
			break;
		}

		//Zmiana zanaczonego elementu
		menu[(3 + (wyborMenu % 6))].aktywny = true;
		tabela[(3 + (wyborTabela % 20))].aktywny = true;
		for (int x = 3; x < 10; x++)if (x != wyborMenu + 3 || !flagMenu)menu[x].aktywny = false;
		for (int x = 3; x < 23; x++)if (x != wyborTabela + 3) tabela[x].aktywny = false;
	}
}
