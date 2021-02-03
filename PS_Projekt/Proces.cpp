#include"Proces.h"

Proces::Proces(int i_nr,std::string i_nazwa, int i_idProcesu, DWORD i_priorytetProcesu, Procesor i_proce)
	:_nr(i_nr), _nazwa(i_nazwa),_idProcesu(i_idProcesu),_priorytetProcesu(i_priorytetProcesu),_proc(i_proce)
{
    int x=_proc.GetUsage(i_idProcesu);
}


void Proces::ZabijProces() {
	HANDLE uchwyt = OpenProcess(PROCESS_TERMINATE, FALSE, _idProcesu);

    if (uchwyt == NULL)
    {
        throw ProcesExp{12,"Pusty uchwyt"};
    }
    if (TerminateProcess(uchwyt, -1))
    {}
    else {
        throw ProcesExp{ 12,"Blad zamkniecia procesu" };
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

std::string Proces::getCpuUsage()
{
    std::string txt,txt2;
    double cpu= _proc.GetUsage(_idProcesu);
    if (cpu == -1) return "-----";
    txt = std::to_string(cpu);
    txt2 = txt.substr(0, txt.find("." )+3);
    return txt2;
}

SIZE_T Proces::getMem(char k)
{
    PROCESS_MEMORY_COUNTERS_EX memInfo;
    HANDLE memHANDLE = OpenProcess(PROCESS_ALL_ACCESS, TRUE, _idProcesu);
    GetProcessMemoryInfo(memHANDLE, (PROCESS_MEMORY_COUNTERS*)&memInfo, sizeof(memInfo));
    SIZE_T memUse = memInfo.WorkingSetSize;
    memUse /= 2;
    if (k == 'B')return memUse;
    else if (k == 'K') return memUse/1024;
    else if (k == 'M') return memUse/(1024*1024);
    else if (k == 'G') return memUse/(1024*1024*1024);
    return memUse;
}
