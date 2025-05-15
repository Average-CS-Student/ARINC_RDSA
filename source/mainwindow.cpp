#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , com(new QCOMCon())
    , comThread(new QThread(this))
    , BPRYARAView(new BodyPRYARA())
    , AlEFIView(new AltitudeEFI())
    , SpeedView(new SpeedWidget())
    , HeadingView(new HeadingWidget())
{
    ui->setupUi(this);
    ui->pushButton_2->setEnabled(false);
    setCentralWidget(ui->gridLayoutWidget);

    // BPRYARAView
    {
        ui->widget = QWidget::createWindowContainer(BPRYARAView, this);
        //ui->widget->setMinimumSize(QSize(400, 200));
        ui->widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->gridLayout->addWidget(ui->widget);

        QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, [this](){
            this->BPRYARAView->SetPlanePitch(30);
        });

        QObject::connect(ui->pushButton_4, &QPushButton::clicked, this, [this](){
            this->BPRYARAView->SetPlaneRoll(30);
        });

        QObject::connect(ui->pushButton_5, &QPushButton::clicked, this, [this](){
            this->BPRYARAView->SetPlaneAoA(30);
        });
    }

    // AlEFIView
    {
        ui->widget_2 = QWidget::createWindowContainer(AlEFIView, this);
        //ui->widget_2->setMinimumSize(QSize(400, 200));
        ui->widget_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->gridLayout->addWidget(ui->widget_2);
    }

    // SpeedView
    ui->gridLayout->addWidget(SpeedView);

    // HeadingView
    ui->gridLayout->addWidget(HeadingView);

    com->moveToThread(comThread);

    QObject::connect(comThread, &QThread::started, com, &QCOMCon::StartReceiving);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::StartButtonClick);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::StopButtonClick);


    QObject::connect(com, &QCOMCon::WordReceived, this, &MainWindow::UpdateUi);
    connect(com, &QCOMCon::HasStoped, this, [this]() {
        qDebug() << "worker stopped";
        comThread->quit();
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
    });

    std::string port = "\\\\.\\COM3";
    com->SetCOM(port);
}

void MainWindow::UpdateUi(Arinc429 word) {
    //ui->listWidget->addItem(QString(word.parameter.c_str()));
    switch(word.labelBNR) {
    case 0b00101011: // Pitch
        BPRYARAView->SetPlanePitch(word.value);
        break;
    case 0b10101011: // Roll
        BPRYARAView->SetPlaneRoll(word.value);
        break;
    case 0b10001001: // AoA
        BPRYARAView->SetPlaneAoA(word.value);
        break;
    case 0b00010101: // AoS
        BPRYARAView->SetPlaneAoS(word.value);
        break;
    case 0b11000001: // Altitude
        AlEFIView->SetPlaneAltitude(word.value);
        break;
    case 0b01110101: // EAS
        SpeedView->SetEAS(word.value);
        break;
    case 0b01100001: // CAS
        SpeedView->SetCAS(word.value);
        break;
    case 0b00010001: // TAS
        SpeedView->SetTAS(word.value);
        break;
    case 0b01010011: // GS
        SpeedView->SetGS(word.value);
        break;
    case 0b00110011: // True Heading
        HeadingView->SetTrueHeading(word.value);
        break;
    case 0b00001011: // Magnetic Heading
        HeadingView->SetMagHeading(word.value);
        break;
    }
}

void MainWindow::ShowMessageBox(QString msg) {
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void MainWindow::StartButtonClick()
{
    if (!comThread->isRunning()) {
        comThread->start();
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
        qDebug() << "Worker thread started";
    }
}

void MainWindow::StopButtonClick()
{
    if (comThread->isRunning()) {
        com->StopReceiving();
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        qDebug() << "Stopping worker...";
    }
}

MainWindow::~MainWindow() {
    delete BPRYARAView;
    delete AlEFIView;
    delete ui;
}


