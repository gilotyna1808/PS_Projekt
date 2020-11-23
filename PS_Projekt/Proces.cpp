#include"Proces.h"

Proces::Proces(int i_nr,std::string i_nazwa, int i_idProcesu, DWORD i_priorytetProcesu)
	:_nr(i_nr), _nazwa(i_nazwa),_idProcesu(i_idProcesu),_priorytetProcesu(i_priorytetProcesu)
{}


void Proces::ZabijProces() {
	HANDLE uchwyt = OpenProcess(PROCESS_TERMINATE, FALSE, _idProcesu);

    if (uchwyt == NULL)
    {
        //throw ProcesExp{12,"Pusty uchwyt"};
    }
    if (TerminateProcess(uchwyt, -1))
    {}
    else {
        //throw ProcesExp{ 12,"Blad zamkniecia procesu" };
    }

    TerminateProcess(uchwyt, -1);
    CloseHandle(uchwyt);
}

void Proces::ZabijProcesOID(int i_id) {
    HANDLE uchwyt = OpenProcess(PROCESS_TERMINATE, FALSE, i_id);

    if (uchwyt == NULL)
    {
        throw ProcesExp{ 12,"Pusty uchwyt" };
    }
    if (TerminateProcess(uchwyt, -1))
    {
    }
    else {
        throw ProcesExp{ 12,"Blad zamkniecia procesu" };
    }

    TerminateProcess(uchwyt, -1);

    CloseHandle(uchwyt);
}