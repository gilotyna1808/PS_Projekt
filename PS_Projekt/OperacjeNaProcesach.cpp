#include"OperacjeNaProcesach.h"

OperacjaNaProcesach::OperacjaNaProcesach()
{
}

OperacjaNaProcesach::~OperacjaNaProcesach()
{
}

void OperacjaNaProcesach::ZaladujProcesy() {

    _listaProcesow.clear(); //Czyszczenie vektora z procesami
    //Zmienne przechowuj�ce uchwyty
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Pobieranie obrazu wszystkich proces�w
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) //Sprawdzanie czy pobranie obrazu si� powiod�o
    {
        throw std::string("B�ad");
    }

    // Ustawianie wielko�ci struktury
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Pob�r informacji o pierwszym procesie
    if (!Process32First(hProcessSnap, &pe32))//Test powodzenia pobrania informacji o procesie
    {
        throw std::string("B�ad");
        CloseHandle(hProcessSnap);//Zamykanie uchwytu
    }

    //P�tla przechodz�ca po wszystkich procesach
    do
    {
        int id; //Zmienna przechowuj�ca id procesu
        std::wstring ws(pe32.szExeFile);//Pobranie nazwy procesu
        std::string nazwa(ws.begin(), ws.end()); //Zmienna przechowuj�ca nazw� procesu w formacji string

        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
        id = pe32.th32ProcessID;
        Proces temp(nazwa, id);
        _listaProcesow.push_back(temp);
        listaIdProcesow.push_back(id);

    } while (Process32Next(hProcessSnap, &pe32));//Kontynuuj do poki istnieje nastepna

    _iloscProcesow = _listaProcesow.size();
    CloseHandle(hProcessSnap);//Zamkniecie uchwytu
}

void OperacjaNaProcesach::ZabijProces(int i_id)
{
    if (i_id >= _listaProcesow.size() || i_id < 1)   //BLAD ROWNIEZ PRZY WARTOSCI 0
    {
        throw std::string("Z�y nr procesu");
    }
    _listaProcesow[i_id].ZabijProces();
}

Proces OperacjaNaProcesach::getProces(int i_id)
{
    if (i_id >= _listaProcesow.size() || i_id < 1)  //BLAD ROWNIEZ PRZY WARTOSCI 0
    {
        throw std::string("Z�y nr procesu");
    }
    return _listaProcesow[i_id];
}