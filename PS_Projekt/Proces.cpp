#include"Proces.h"

Proces::Proces(std::string i_nazwa, int i_idProcesu) 
	:_nazwa(i_nazwa),_idProcesu(i_idProcesu)
{}


void Proces::ZabijProces() {
	HANDLE uchwyt = OpenProcess(PROCESS_TERMINATE, FALSE, _idProcesu);
    TerminateProcess(uchwyt, -1);
    CloseHandle(uchwyt);
}

void Proces::ZabijProcesOID(int i_id) {
    HANDLE uchwyt = OpenProcess(PROCESS_TERMINATE, FALSE, i_id);
    TerminateProcess(uchwyt, -1);
    CloseHandle(uchwyt);
}