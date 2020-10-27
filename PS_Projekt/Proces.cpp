#include"Proces.h"

Proces::Proces(std::string i_nazwa, int i_idProcesu) 
	:_nazwa(i_nazwa),_idProcesu(i_idProcesu)
{}


void Proces::ZabijProces() {
	HANDLE uchwyt = OpenProcess(PROCESS_TERMINATE, FALSE, _idProcesu);
    if (uchwyt == NULL)
    {
        wprintf(L"Cannot open process with ID % d, error code : % d\n", _idProcesu, GetLastError());
    }
    if (TerminateProcess(uchwyt, -1))
    {
        wprintf(L"Process with ID % d has been terminated\n", _idProcesu, GetLastError());
    }
    else {
        wprintf(L"Termination of the process with ID % d failed, error code : % d\n", _idProcesu, GetLastError());
    }
    CloseHandle(uchwyt);
}

void Proces::ZabijProcesOID(int i_id) {
    HANDLE uchwyt = OpenProcess(PROCESS_TERMINATE, FALSE, i_id);
    if (uchwyt == NULL)
    {
        wprintf(L"Cannot open process with ID % d, error code : % d\n", i_id, GetLastError());
    }
    if (TerminateProcess(uchwyt, -1))
    {
        wprintf(L"Process with ID % d has been terminated\n", i_id, GetLastError());
    }
    else {
        wprintf(L"Termination of the process with ID % d failed, error code : % d\n", i_id, GetLastError());
    }
    CloseHandle(uchwyt);
}