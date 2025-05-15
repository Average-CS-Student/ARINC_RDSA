#pragma once
#include "Windows.h"
#include <string>

class COMCon {
public:
	COMCon();

	COMCon(std::string com);

	~COMCon();

    bool ReadCOM(uint32_t& word);

	int error;
	
private:
    //const char* COM;
    std::string COM;

	HANDLE hComm;
};
