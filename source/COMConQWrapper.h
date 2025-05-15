#ifndef COMCONQWRAPPER_H
#define COMCONQWRAPPER_H

#include "COMCon.h"
#include "Arinc429.h"
#include "SharedBuffer.h"
#include <QObject>
#include <qtmetamacros.h>
#include <map>

class QCOMCon : public QObject {

    Q_OBJECT

public:
    QCOMCon(QObject *parent = nullptr);
    ~QCOMCon();

private:
    QAtomicInteger<bool> running, hasStoped;
    std::string com;
    std::map<uint16_t, Arinc429> *activeBuffer;

public slots:
    void StartReceiving();
    void StopReceiving();
    void SetCOM(std::string comName);
    void GetAvailableCOMPorts(std::vector<std::string> *listOfPorts, std::vector<std::string> *portDetails);
    void UpdateSharedBuffer();

signals:
    void WordReceived(Arinc429 word);
    void HasStoped();
    void ErrorOccured();
};

#endif // COMCONQWRAPPER_H
