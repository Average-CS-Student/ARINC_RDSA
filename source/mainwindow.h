#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "COMConQWrapper.h"
#include "bodypryara.h"
#include "altitudeefi.h"
#include "speedwidget.h"
#include "headingwidget.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QCOMCon *com;
    QThread *comThread;
    BodyPRYARA *BPRYARAView;
    AltitudeEFI *AlEFIView;
    SpeedWidget *SpeedView;
    HeadingWidget *HeadingView;

private slots:
    void UpdateUi(Arinc429 word);
    void ShowMessageBox(QString msg);
    void StartButtonClick();
    void StopButtonClick();

};
#endif // MAINWINDOW_H
