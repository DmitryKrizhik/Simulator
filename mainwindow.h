#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QTouchEvent>
#include <QtXml/QtXml>
#include <QtXml/QDomDocument>
#include <QtXml/QDomAttr>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDebug>
#include <QTouchEvent>
#include <QDesktopWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <thread>
#include <string>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool event(QEvent *event);
    bool touchEvent(QTouchEvent *event);
    //static QFile file;
private slots:

    void on_ResolutionBox_activated(int index);
    void on_ThemeBox_activated(int index);
    void on_TemperatureSlider_valueChanged(int value);
    void on_TemperatureBox_activated(int index);
    void on_AngleSlider_valueChanged(int value);
    void on_HumiditySlider_valueChanged(int value);
    void on_PressureBox_activated(int index);
    void on_PressureSlider_valueChanged(int value);
    void on_Turn_ON_OFF_clicked();
    void setLight();
    void setDark();
    void setColorButton_ON_OFF();
    void SetEnabledTrue();
    void SetEnabledFalse();
    void TurnON();
    void TurnOFF();
    void SendResponse();
    void Hiding();
    void UnHiding();
    void ButtonOFF();
    void ButtonON();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
