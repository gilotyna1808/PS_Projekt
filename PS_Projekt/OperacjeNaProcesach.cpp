#include"OperacjeNaProcesach.h"

OperacjaNaProcesach::OperacjaNaProcesach()
{
}

OperacjaNaProcesach::~OperacjaNaProcesach()
{
}

void OperacjaNaProcesach::ZaladujProcesy() {

    _listaProcesow.clear(); //Czyszczenie vektora z procesami
    _listaProcesow2.clear();
    //Zmienne przechowuj¹ce uchwyty
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    int licznik = 0;
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
        DWORD priorytet=0; //Zmienna przechowuj¹ca informacje o priorytecie
        Procesor proc;
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
        //Pobieranie informacji
        id = pe32.th32ProcessID;
        priorytet = pe32.pcPriClassBase;
        //Wpisywanie informacji
        Proces temp(licznik++,nazwa, id, priorytet,proc);
        _listaProcesow.push_back(temp);
        //Zmiana nazwy na male litery
        std::transform(nazwa.begin(), nazwa.end(), nazwa.begin(), [](unsigned char c) { return std::tolower(c); });
        _listaProcesow2[nazwa.substr(0,15)].push_back(temp);
        
        
        //listaIdProcesow.push_back(id);

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

Proces OperacjaNaProcesach::getProcesSort(int i_id){
    if (i_id >= _listaProcesow.size() || i_id < 1)  //BLAD ROWNIEZ PRZY WARTOSCI 0
    {
        throw std::string("Z³y nr procesu");
    }
    std::map<std::string, std::vector<Proces>>::const_iterator iterator = _listaProcesow2.begin();
    int poczatekVektora = 0;
    int wskaznikWektora = 0;
    for (size_t i = 1; i < i_id+1; i++)
    {
        if(iterator->second.size()>wskaznikWektora)wskaznikWektora++;
        if (iterator->second.size() + poczatekVektora == i) {
            if (iterator!=_listaProcesow2.end())iterator++;
            wskaznikWektora = 0;
            poczatekVektora = i;
        }
    }
    Proces temp = iterator->second[wskaznikWektora];
    return temp;
}

bool OperacjaNaProcesach::czySystemowy(Proces i_proces)
{
    std::vector<std::string> procesySys;
    procesySys.push_back("smss.exe");
    procesySys.push_back("csrss.exe");
    procesySys.push_back("wininit.exe");
    procesySys.push_back("services.exe");
    procesySys.push_back("lsass.exe");
    procesySys.push_back("svchost.exe");
    procesySys.push_back("lsm.exe");
    procesySys.push_back("winlogon.exe");
    procesySys.push_back("explorer.exe");
    procesySys.push_back("Registry");
    procesySys.push_back("StartMenuExperienceHost.exe");
    procesySys.push_back("RuntimeBroker.exe");
    procesySys.push_back("msvsmon.exe");
    procesySys.push_back("conhost.exe");
    procesySys.push_back("PS_Projekt.exe"); //Wykluczenie projektu
    procesySys.push_back("Taskmgr.exe"); //Wykluczenie menadzera zadan
    procesySys.push_back("obs64.exe"); //Wykuczenie programu do nagrywania
    procesySys.push_back("obs-ffmpeg-mux.exe"); //Wykluczenie programu do nagrywania
    
    
    for (std::string s : procesySys) {
        if (s == i_proces.getNazwa())return true;
    }
    return false;
}


void OperacjaNaProcesach::Genocide() 
{
    system("cls");
    
    for (Proces p : _listaProcesow) {
        bool flag;
        flag = czySystemowy(p);
        if(!flag)//Zabijanie je¿eli nie systemowy
        {
            //
            try
            {
                //std::cout << p.getNazwa()<<std::endl;
                //getchar();
                p.ZabijProces();
            }
            catch (ProcesExp exp)
            {
                //std::cout <<"+++++++ "<< exp.txt << std::endl;
            }
            
        }
    }
}
