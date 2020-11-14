#include"OperacjeNaProcesach.h"

OperacjaNaProcesach::OperacjaNaProcesach()
{
}

OperacjaNaProcesach::~OperacjaNaProcesach()
{
}

void OperacjaNaProcesach::ZaladujProcesy() {

    _listaProcesow.clear(); //Czyszczenie vektora z procesami
    //Zmienne przechowuj¹ce uchwyty
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Pobieranie obrazu wszystkich procesów
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) //Sprawdzanie czy pobranie obrazu siê powiod³o
    {
        throw std::string("B³ad");
    }

    // Ustawianie wielkoœci struktury
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Pobór informacji o pierwszym procesie
    if (!Process32First(hProcessSnap, &pe32))//Test powodzenia pobrania informacji o procesie
    {
        throw std::string("B³ad");
        CloseHandle(hProcessSnap);//Zamykanie uchwytu
    }

    //Pêtla przechodz¹ca po wszystkich procesach
    do
    {
        int id; //Zmienna przechowuj¹ca id procesu
        std::wstring ws(pe32.szExeFile);//Pobranie nazwy procesu
        std::string nazwa(ws.begin(), ws.end()); //Zmienna przechowuj¹ca nazwê procesu w formacji string

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
        throw std::string("Z³y nr procesu");
    }
    _listaProcesow[i_id].ZabijProces();
}

Proces OperacjaNaProcesach::getProces(int i_id)
{
    if (i_id >= _listaProcesow.size() || i_id < 1)  //BLAD ROWNIEZ PRZY WARTOSCI 0
    {
        throw std::string("Z³y nr procesu");
    }
    return _listaProcesow[i_id];
}