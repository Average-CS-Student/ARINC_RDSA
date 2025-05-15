#include <iostream>
#include <Windows.h>
#include "COMCon.h"

COMCon::COMCon() {
    //COM = nullptr;
	hComm = NULL;
	error = -1;
}

COMCon::COMCon(std::string com) {
    COM = std::string(com);

    hComm = CreateFileA(COM.c_str(),
						GENERIC_READ,
						0,
						NULL,
						OPEN_EXISTING,
						0,
						NULL);

	if (hComm == INVALID_HANDLE_VALUE) {
		error = -1;
	}
	else {
		error = 0;
    }
}

COMCon::~COMCon() {
    //COM = nullptr;
	CloseHandle(hComm);
	hComm = NULL;
}

bool COMCon::ReadCOM(uint32_t& word) {
	if (error == -1) {
        return false;
	}

    return ReadFile(hComm, &word, 4, NULL, NULL);
}
