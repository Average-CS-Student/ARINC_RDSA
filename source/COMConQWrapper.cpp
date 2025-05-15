#include "COMConQWrapper.h"

#define INITIAL_lpTP_SIZE 5000

QCOMCon::QCOMCon(QObject *parent) {
    //com = COMCon();
    activeBuffer = new std::map<uint16_t, Arinc429>();
    running.storeRelaxed(false);
    hasStoped.storeRelaxed(true);
}

QCOMCon::~QCOMCon() {
    activeBuffer = nullptr;
}

void QCOMCon::StartReceiving() {
    COMCon COMCon(com);
    if (COMCon.error) {
        emit ErrorOccured();
        return;
    }

    uint32_t comData;
    Arinc429 arinc429;

    running.storeRelaxed(true);
    hasStoped.storeRelaxed(false);

    while (running) {
        COMCon.ReadCOM(comData);
        if (!COMCon.error) {
            arinc429 = Arinc429(comData);

            if (arinc429.error == 0) {
                emit WordReceived(arinc429);

                // Sets unique map element based on label and SDI
                (*activeBuffer)[(arinc429.labelBNR << 2) | arinc429.SDI] = arinc429;
            }
        }
    }

    hasStoped.storeRelaxed(true);
    emit HasStoped();
}

void QCOMCon::StopReceiving() {
    running.storeRelaxed(false);
}

void QCOMCon::SetCOM(std::string comName) {
    com = std::string(comName);
}

void QCOMCon::GetAvailableCOMPorts(std::vector<std::string> *listOfPorts, std::vector<std::string> *portDetails) {

    listOfPorts->clear();
    portDetails->clear();

    size_t lpTPSize = INITIAL_lpTP_SIZE;
    wchar_t* lpTargetPath = static_cast<wchar_t*>(malloc(lpTPSize * sizeof(wchar_t)));
    if (!lpTargetPath) {
        return;
    }

    DWORD test;

    for(int i = 0; i < 255; i++) // checking ports from COM0 to COM255
    {
        std::string ComName = "COM" + std::to_string(i);

        test = QueryDosDeviceW((std::wstring(ComName.begin(), ComName.end())).c_str(), lpTargetPath, lpTPSize);

        // Test the return value and error if any
        if(test != 0) // QueryDosDevice returns zero if it didn't find an object
        {
            listOfPorts->emplace_back(ComName); // Add to list

            std::string details = "";
            if (lpTargetPath) {
                // Calculate required buffer size
                int bufferSize = WideCharToMultiByte(
                    CP_UTF8,
                    0,
                    lpTargetPath,
                    -1,
                    nullptr,
                    0,
                    nullptr, nullptr
                    );

                if (!bufferSize) {
                    std::string narrowStr(bufferSize, 0);
                    WideCharToMultiByte(
                        CP_UTF8, 0, lpTargetPath, -1,
                        &narrowStr[0], bufferSize, nullptr, nullptr
                        );

                    narrowStr.resize(bufferSize - 1);  // Remove trailing null
                    details = narrowStr;
                }
            }

            portDetails->emplace_back(details);
        }

        DWORD error = GetLastError();
        if(error == ERROR_INSUFFICIENT_BUFFER)
        {
            lpTPSize *= 2;
            wchar_t* newBuffer = static_cast<wchar_t*>(realloc(lpTargetPath, lpTPSize * sizeof(wchar_t)));
            if (!newBuffer) {
                free(lpTargetPath);
                // Handle memory allocation failure
                return;
            }
            lpTargetPath = newBuffer;
            i--;
        }
    }

    free(lpTargetPath);
}

void QCOMCon::UpdateSharedBuffer() {
    StopReceiving();
    while(!hasStoped) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::shared_ptr<std::map<uint16_t, Arinc429>> copy(activeBuffer);
    {
        std::lock_guard<std::mutex> lock(bufferMutex);
        buffer = copy;
    }
    StartReceiving();
}
