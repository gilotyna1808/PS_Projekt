#include"Proces.h"

Proces::Proces(std::string i_nazwa, int i_idProcesu) 
	:_nazwa(i_nazwa),_idProcesu(i_idProcesu)
{}


void Proces::ZabijProces() {
	HANDLE uchwyt = OpenProcess(PROCESS_TERMINATE, FALSE, _idProcesu);

    if (uchwyt == NULL)
    {
        throw ProcesExp{12,"Pusty uchwyt"};
    }
    if (TerminateProcess(uchwyt, -1))
    {}
    else {
        throw ProcesExp{ 12,"B��d zamkni�cia procesu" };
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
        throw ProcesExp{ 12,"B��d zamkni�cia procesu" };
    }

    TerminateProcess(uchwyt, -1);

    CloseHandle(uchwyt);
}