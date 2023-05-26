#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setLight();
    SetEnabledFalse();
    TurnOFF();
    ButtonOFF();
    //showFullScreen();
    SendResponse();
}

/**
 * @brief Строковая переменная для хранения единиц измерения температуры
 */
QString degrees;

/**
 * @brief Строковая переменная для хранения единиц измерения давления
 */
QString pressureUnit;

/**
 * @brief Строковая переменная для хранения текущей темы интерфейса
 */
QString theme;

/**
 * @brief Объект для создания TCP-сервера
 */
QTcpServer server;

/**
 * @brief Таймер для периодического обновления данных на экране
 */
QTimer timer;

/**
 * @brief Строковая переменная для хранения состояния системы
 */
QString state;

/**
 * @brief Переменная для хранения значения температуры
 */
float temperature;

/**
 * @brief Переменная для хранения значения угла поворота
 */
int angle;

/**
 * @brief Переменная для хранения значения влажности
 */
int humidity;

/**
 * @brief Переменная для хранения значения давления
 */
int pressure;

/**
 * @brief Файл для записи и чтения значений в формате XML
 */
QFile file("values.xml");


MainWindow::~MainWindow()
{
    delete ui;
}

void SetDegrees(QString &degrees, QString _degrees)
{
    /**
     * @brief Устанавливает значение переменной degrees
     * @param degrees Ссылка на переменную degrees
     * @param _degrees Новое значение для переменной degrees
     */
    degrees = _degrees;
}
void SetPressureUnit(QString &pressureUnit, QString _pressureUnit)
{
    /**
     * @brief Устанавливает значение переменной pressureUnit
     * @param pressureUnit Ссылка на переменную pressureUnit
     * @param _pressureUnit Новое значение для переменной pressureUnit
     */
    pressureUnit = _pressureUnit;
}
void SetTemperature(float &temperature, float _temperature)
{
    /**
     * @brief Устанавливает значение переменной temperature
     * @param temperature Ссылка на переменную temperature
     * @param _temperature Новое значение для переменной temperature
     */
    temperature = _temperature;
}
void SetAngle(int &angle, int _angle)
{
    /**
     * @brief Устанавливает значение переменной angle
     * @param angle Ссылка на переменную angle
     * @param _angle Новое значение для переменной angle
     */
    angle = _angle;
}
void SetHumidity(int &humidity, int _humidity)
{
    /**
     * @brief Устанавливает значение переменной humidity
     * @param humidity Ссылка на переменную humidity
     * @param _humidity Новое значение для переменной humidity
     */
    humidity = _humidity;
}
void SetPressure(int &pressure, int _pressure)
{
    /**
     * @brief Устанавливает значение переменной pressure
     * @param pressure Ссылка на переменную pressure
     * @param _pressure Новое значение для переменной pressure
     */
    pressure = _pressure;
}
void SetTheme(QString &theme, QString _theme)
{
    /**
     * @brief Устанавливает значение переменной theme
     * @param theme Ссылка на переменную theme
     * @param _theme Новое значение для переменной theme
     */
    theme = _theme;
}
void SetState(QString &state, QString _state)
{
    /**
     * @brief Устанавливает значение переменной state
     * @param state Ссылка на переменную state
     * @param _state Новое значение для переменной state
     */
    state = _state;
}

void MainWindow::on_TemperatureBox_activated(int index) //Handles the selection of the unit of measure in the TemperatureBox
{
    /**
     * @brief Обрабатывает выбор единицы измерения в поле TemperatureBox
     * @param index Индекс выбранной единицы измерения
     * Функция проверяет выбранную единицу измерения и текущее значение переменной degrees.
     * В зависимости от этого она устанавливает новое значение для переменной degrees и пересчитывает значение температуры.
     * Результат записывается в переменную temperature и отображается на экране.
     */
    if(index == 0 && degrees == "")
    {
        SetDegrees(degrees, "Celsius");
        SetTemperature(temperature, ui->TemperatureSlider->value());
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " celsius");
    }
    else if(index == 0 && degrees == "Kelvin") {

        SetDegrees(degrees, "Celsius");
        SetTemperature(temperature, ui->TemperatureSlider->value());
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " celsius");
    }
    else if(index == 0 && degrees == "Fharenheit")
    {
        SetDegrees(degrees, "Celsius");
        SetTemperature(temperature, ui->TemperatureSlider->value());
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " celsius");
    }
    else if(index == 2 && degrees == "")
    {
        SetDegrees(degrees, "Kelvin");
        SetTemperature(temperature, ui->TemperatureSlider->value() + 273);
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " kelvin");
    }
    else if (index == 2 && degrees == "Celsius") {

        SetTemperature(temperature, ui->TemperatureSlider->value() + 273);
        SetDegrees(degrees, "Kelvin");
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " kelvin");
    }
    else if(index == 2 && degrees == "Fharenheit")
    {
        SetDegrees(degrees, "Kelvin");
        SetTemperature(temperature, ui->TemperatureSlider->value() +273);
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " kelvin");
    }
    else if(index == 1 && degrees == "")
    {
        SetDegrees(degrees, "Fharenheit");
        SetTemperature(temperature, 9*ui->TemperatureSlider->value()/5 + 32);
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " fharenheit");
    }
    else if(index == 1 && degrees == "Celsius")
    {
        SetDegrees(degrees, "Fharenheit");
        SetTemperature(temperature, 9*ui->TemperatureSlider->value()/5 + 32);
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " fharenheit");
    }
    else if(index == 1 && degrees == "Kelvin")
    {
        SetDegrees(degrees, "Fharenheit");
        SetTemperature(temperature, 9*ui->TemperatureSlider->value()/5 + 32);
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " fharenheit");
    }
}

void MainWindow::on_TemperatureSlider_valueChanged(int value) //Handles position changes of the "TemperatureSlider" slider
{
    /**
     * @brief Обрабатывает изменение положения слайдера TemperatureSlider
     * @param value Новое значение слайдера
     * Функция проверяет текущую единицу измерения (Celsius, Kelvin или Fharenheit) и в зависимости от этого пересчитывает значение температуры.
     * Результат записывается в переменную temperature и отображается на экране в соответствующей единице измерения.
     */
    if(degrees == "Celsius"){
        SetTemperature(temperature, value);
    ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " celsius");
    }
    else if(degrees == "Kelvin")
    {
        SetTemperature(temperature, value + 273);
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " kelvin");
    }
    else if(degrees == "Fharenheit")
    {
        SetTemperature(temperature, 9*value/5 + 32);
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " fharenheit");
    }
}

void MainWindow::on_PressureBox_activated(int index) //Handles the selection of the unit of measure in the PressureBox
{

    /**
     * @brief Обрабатывает выбор единицы измерения давления в PressureBox
     * @param index Индекс выбранной единицы измерения
     * Функция проверяет текущую единицу измерения (Kilopascals или mm. of mercury) и в зависимости от выбора пользователя пересчитывает значение давления.
     * Результат записывается в переменную pressure и отображается на экране в соответствующей единице измерения.
     */
    if(index == 0 && pressureUnit == "")
    {
        SetPressureUnit(pressureUnit, "Kilopascals");
        SetPressure(pressure, ui->PressureSlider->value());
        ui->PressureLabel->setText("Pressure: " + QString::number(pressure)  + " kilopascals");
    }
    else if(index == 0 && pressureUnit == "mm. of mercury")
    {
        SetPressureUnit(pressureUnit, "Kilopascals");
        SetPressure(pressure, ui->PressureSlider->value());
        ui->PressureLabel->setText("Pressure: " + QString::number(pressure) + " kilopascals");
    }
    else if (index == 1 && pressureUnit == "")
    {
        SetPressureUnit(pressureUnit, "mm. of mercury");
        SetPressure(pressure, ui->PressureSlider->value() *7.5006156);
        ui->PressureLabel->setText("Pressure: " + QString::number(pressure) + " mm. of mercury");
    }
    else if(index == 1 && pressureUnit == "Kilopascals")
    {
        SetPressureUnit(pressureUnit, "mm. of mercury");
        SetPressure(pressure, ui->PressureSlider->value() *7.5006156);
        ui->PressureLabel->setText("Pressure: " + QString::number(pressure) + " mm. of mercury");
    }
}

void MainWindow::on_PressureSlider_valueChanged(int value) //Handles position changes of the "PressureSlider" slider
{
    /**
     * @brief Обрабатывает изменение положения слайдера давления в PressureBox
     * @param value Значение, выбранное пользователем на слайдере
     * Функция проверяет текущую единицу измерения (килопаскали или миллиметры ртутного столба) и в зависимости от
     * выбора пользователя пересчитывает значение давления.
     * Результат записывается в переменную pressure и отображается на экране в соответствующей единице измерения.
     */
    if(pressureUnit == "Kilopascals")
    {
        SetPressure(pressure, value );
        ui->PressureLabel->setText("Pressure: " + QString::number(pressure) + " kilopascals");
    }
    else if(pressureUnit == "mm. of mercury")
    {
        SetPressure(pressure, value *7.5006156);
        ui->PressureLabel->setText("Pressure: " + QString::number(pressure) + " mm. of mercury");
    }
}

void MainWindow::on_AngleSlider_valueChanged(int value) //Handles position changes of the "AngleSlider" slider
{

    /**
     * @brief Обрабатывает изменение положения слайдера угла поворота в MainWindow
     * @param value Значение, выбранное пользователем на слайдере
     * Функция вызывает функцию SetAngle, которая устанавливает значение угла поворота в соответствии с выбранным пользователем значением.
     * Затем функция проверяет значение выбранного пользователем угла поворота и, в зависимости от этого значения, выводит текстовое описание на экран.
     */
    SetAngle(angle, value);
    if(value == 0){
    ui->AngleLabel->setText("Angle of rotation: " + QString::number(angle));
    }
    else if(value < 0) {
        ui->AngleLabel->setText("Angle of rotation: " + QString::number((-1)*angle) + " left");
    }
    else if(value > 0) {
        ui->AngleLabel->setText("Angle of rotation: " + QString::number(angle) + " right");
    }
}

void MainWindow::on_HumiditySlider_valueChanged(int value) //Handles position changes of the "HumiditySlider" slider
{
    /**
     * @brief Обрабатывает изменение положения слайдера влажности в MainWindow
     * @param value Значение, выбранное пользователем на слайдере
     * Функция вызывает функцию SetHumidity, которая устанавливает значение влажности в соответствии с выбранным пользователем значением.
     * Затем функция выводит текстовое описание на экран, содержащее текущее значение влажности.
     */
    SetHumidity(humidity, value);
    ui->HumidityLabel->setText("Humidity: " + QString::number(humidity) + "%");
}

void MainWindow::on_Turn_ON_OFF_clicked() //Handles the ON/OFF button.
{
    /**
     * @brief Обрабатывает нажатие кнопки ON/OFF в MainWindow
     * Функция открывает XML-файл и считывает из него значения параметров. Если файл не может быть открыт для чтения,
     * функция выводит сообщение об ошибке.
     *
     * Если кнопка имеет надпись "Turn ON", функция вызывает функцию TurnON, которая включает устройство и
     * устанавливает значения параметров в соответствии с XML-файлом.
     *
     * Если кнопка имеет надпись "Turn OFF", функция записывает значения параметров в XML-файл и вызывает функцию
     * TurnOFF, которая выключает устройство.
     */
   QFile file("values.xml");
   if(ui->Turn_ON_OFF->text() == "Turn ON")
  {
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) //Reading parameters from the XML file
        {
            qDebug() << "ERROR: File could not be opened for reading.";
            return;
        }
        QXmlStreamReader reader(&file);

        while(!reader.atEnd() && !reader.hasError())
        {

            QXmlStreamReader::TokenType token = reader.readNext();
            if(token == QXmlStreamReader::StartDocument)
            {
                continue;
            }
            if(token == QXmlStreamReader::StartElement)
            {
                if(reader.name() == "degrees")
                {
                    SetDegrees(degrees, reader.readElementText());
                    qDebug() << "Degrees: " << degrees;
                }
                else if(reader.name() == "pressureUnit")
                {
                    SetPressureUnit(pressureUnit, reader.readElementText());
                    qDebug() << "Pressure Unit: " << pressureUnit;
                }
                else if(reader.name() == "temperature")
                {
                    SetTemperature(temperature, reader.readElementText().toInt());
                    qDebug() << "Temperature: " << temperature;
                }
                else if(reader.name() == "angle")
                {
                    SetAngle(angle, reader.readElementText().toInt());
                    qDebug() << "Angle: " << angle;
                }
                else if(reader.name() == "humidity")
                {
                    SetHumidity(humidity, reader.readElementText().toInt());
                    qDebug() << "Humidity: " << humidity;
                }
                else if(reader.name() == "pressure")
                {
                    SetPressure(pressure, reader.readElementText().toInt());
                    qDebug() << "Pressure: " << pressure;
                }
            }
        }
        file.close();
        reader.clear();
        TurnON();
    }
    else if(ui->Turn_ON_OFF->text() == "Turn OFF") //Writing parameters in the XML file
    {

        QFile file("values.xml");
            if (file.open(QIODevice::WriteOnly))
            {
                QXmlStreamWriter xmlWriter(&file);
                xmlWriter.setAutoFormatting(true);
                xmlWriter.writeStartDocument();
                xmlWriter.writeStartElement("values");
                xmlWriter.writeTextElement("degrees", degrees);
                xmlWriter.writeTextElement("pressureUnit", pressureUnit);
                xmlWriter.writeTextElement("temperature", QString::number(temperature));
                xmlWriter.writeTextElement("angle", QString::number(angle));
                xmlWriter.writeTextElement("humidity", QString::number(humidity));
                xmlWriter.writeTextElement("pressure", QString::number(pressure));
                xmlWriter.writeEndElement();
                xmlWriter.writeEndDocument();
                file.close();
            }
            TurnOFF();
    }
}
void MainWindow::SetEnabledTrue() //ON buttons
{
    /**
     * @brief Включает все элементы интерфейса, связанные с изменением параметров
     * Функция устанавливает свойство enabled в true для всех элементов интерфейса, связанных с изменением параметров.
     */
    ui->AngleChangeLabel->setEnabled(true);
    ui->AngleLabel->setEnabled(true);
    ui->AngleSlider->setEnabled(true);
    ui->HumidityChangeLabel->setEnabled(true);
    ui->HumidityLabel->setEnabled(true);
    ui->HumiditySlider->setEnabled(true);
    ui->PressureBox->setEnabled(true);
    ui->PressureLabel->setEnabled(true);
    ui->PressureSlider->setEnabled(true);
    ui->TemperatureBox->setEnabled(true);
    ui->TemperatureLabel->setEnabled(true);
    ui->TemperatureSlider->setEnabled(true);
    ui->ThemeBox->setEnabled(true);
    ui->ResolutionBox->setEnabled(true);
}
void MainWindow::SetEnabledFalse() //OFF buttons
{
    /**
     * @brief Выключает все элементы интерфейса, связанные с изменением параметров
     * Функция устанавливает свойство enabled в false для всех элементов интерфейса, связанных с изменением параметров.
     */
    ui->AngleChangeLabel->setEnabled(false);
    ui->AngleLabel->setEnabled(false);
    ui->AngleSlider->setEnabled(false);
    ui->HumidityChangeLabel->setEnabled(false);
    ui->HumidityLabel->setEnabled(false);
    ui->HumiditySlider->setEnabled(false);
    ui->PressureBox->setEnabled(false);
    ui->PressureLabel->setEnabled(false);
    ui->PressureSlider->setEnabled(false);
    ui->TemperatureBox->setEnabled(false);
    ui->TemperatureLabel->setEnabled(false);
    ui->TemperatureSlider->setEnabled(false);
    ui->ThemeBox->setEnabled(false);
    ui->ResolutionBox->setEnabled(false);
}

void MainWindow::on_ThemeBox_activated(int index) //Handles the color theme selection box
{

    /**
     * @brief Обрабатывает выбор пользователем цветовой темы
     * Функция вызывается при изменении выбранной пользователем цветовой темы.
     * @param index Индекс выбранной пользователем цветовой темы
     */
    if(index == 0) { setLight(); SetTheme(theme, "Light");}
    else if( index == 1) { setDark(); SetTheme(theme, "Dark");}
}

void MainWindow::on_ResolutionBox_activated(int index) //Handles the screen resolution selection box
{
    /**
     * @brief Обрабатывает выбор пользователем разрешения экрана
     * Функция вызывается при изменении выбранного пользователем разрешения экрана.
     * @param index Индекс выбранного пользователем разрешения экрана
     */
    if(index == 0) { setFixedSize(800,600); }
    else if(index == 1) { setFixedSize(1024,768); }
}

void MainWindow::setColorButton_ON_OFF() //Changes the color of the "Turn_ON_OFF" button depending on the selected color theme
{

    /**
     * @brief Изменяет цвет кнопки "Turn_ON_OFF" в зависимости от выбранной цветовой темы
     * Функция вызывается при изменении выбранной пользователем цветовой темы.
     */
    QPalette pal = palette();
    if(ui->Turn_ON_OFF->text() == "Turn OFF" && theme == "Light")
    {
        ui->Turn_ON_OFF->setStyleSheet(QString("background-color: rgb(168, 180, 224)"));
    }
    else if(ui->Turn_ON_OFF->text() == "Turn OFF" && theme == "Dark")
    {
        ui->Turn_ON_OFF->setStyleSheet(QString("background-color: rgb(132, 143, 181)"));
    }
    else if(ui->Turn_ON_OFF->text() == "Turn ON" && theme == "Light")
    {
        ui->Turn_ON_OFF->setStyleSheet(QString("background-color: rgb(214, 66, 66)"));
    }
    else if(ui->Turn_ON_OFF->text() == "Turn ON" && theme == "Dark")
    {
        ui->Turn_ON_OFF->setStyleSheet(QString("background-color: rgb(189, 58, 58)"));
    }
}

void MainWindow::setLight() //Changes the color theme of the interface to light
{
    /**
     * @brief Изменяет цветовую тему интерфейса на светлую
     * Функция изменяет цвет фона окна, цвет кнопок, цвет текста на кнопках и цвет текста заголовка окна.
     * Затем вызывает функцию SetTheme() с указанием выбранной темы и названия "Light" и функцию setColorButton_ON_OFF().
     */
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(180, 186, 207));
    pal.setColor(QPalette::Button, QColor(157, 164, 199));
    pal.setColor(QPalette::ButtonText, QColor(242, 245, 252));
    pal.setColor(QPalette::WindowText, QColor(242, 245, 252));
    setPalette(pal);
    SetTheme(theme, "Light");
    setColorButton_ON_OFF();
}

void MainWindow::setDark() //Changes the color theme of the interface to dark
{
    /**
     * @brief Изменяет цветовую тему интерфейса на темную
     * Функция изменяет цвет фона окна, цвет кнопок, цвет текста на кнопках и цвет текста заголовка окна.
     * Затем вызывает функцию SetTheme() с указанием выбранной темы и названия "Dark" и функцию setColorButton_ON_OFF().
     */
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(99, 107, 133));
    pal.setColor(QPalette::Button, QColor(99, 107, 133));
    pal.setColor(QPalette::ButtonText, QColor(224, 231, 255));
    pal.setColor(QPalette::WindowText, QColor(224, 231, 255));
    setPalette(pal);
    SetTheme(theme, "Dark");
    setColorButton_ON_OFF();
}

void MainWindow::TurnON() //ON the application and changes colors depending on the selected color theme
{
    /**
     * @brief Включает приложение и изменяет цвета в зависимости от выбранной цветовой темы
     * Функция устанавливает состояние "ON" и текст на кнопке "Turn_ON_OFF" в "Turn OFF",
     * вызывает функцию setColorButton_ON_OFF() для изменения цвета кнопки "Turn_ON_OFF".
     * Затем происходит обновление значений на слайдерах и метках для влажности, давления и температуры.
     * В зависимости от выбранной единицы измерения давления и температуры, значения на слайдерах и метках обновляются соответствующим образом.
     * Затем функция изменяет цвет текста на кнопках в зависимости от выбранной цветовой темы.
     */
    UnHiding();
    SetEnabledTrue();
    SetState(state, "ON");
    ui->Turn_ON_OFF->setText("Turn OFF");
    setColorButton_ON_OFF();

    ui->HumidityLabel->setText("Humidity: " + QString::number(humidity) + "%");
    ui->HumiditySlider->setValue(humidity);

    if(angle == 0) { ui->AngleLabel->setText("Angle of rotation: " + QString::number(angle)); }
    else if(angle < 0) { ui->AngleLabel->setText("Angle of rotation: " + QString::number((-1)*angle) + " left"); }
    else if(angle > 0) { ui->AngleLabel->setText("Angle of rotation: " + QString::number(angle) + " right"); }
    ui->AngleSlider->setValue(angle);

    if(pressureUnit == "Kilopascals")
    {
        ui->PressureLabel->setText("Pressure: " + QString::number(pressure) + " kilopascals");
        ui->PressureSlider->setValue(pressure);
        ui->PressureBox->setCurrentIndex(0);
    }
    else if(pressureUnit == "mm. of mercury")
    {
        ui->PressureLabel->setText("Pressure: " + QString::number(pressure) + " mm. of mercury");
        ui->PressureSlider->setValue(pressure / 10 * 1.34331);
        ui->PressureBox->setCurrentIndex(1);
    }

    if(degrees == "Celsius")
    {
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " celsius");
        ui->TemperatureSlider->setValue(temperature);
        ui->TemperatureBox->setCurrentIndex(0);
    }
    else if(degrees == "Fharenheit")
    {
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " fharenheit");
        ui->TemperatureSlider->setValue((temperature - 32) * 5 /9);
        ui->TemperatureBox->setCurrentIndex(1);
    }
    else if(degrees == "Kelvin")
    {
        ui->TemperatureLabel->setText("Temperature: " + QString::number(temperature) + " kelvin");
        ui->TemperatureSlider->setValue(temperature - 273);
        ui->TemperatureBox->setCurrentIndex(2);
    }
    QPalette pal1 = palette();

    if(theme == "Light")
    {
        pal1.setColor(QPalette::ButtonText, QColor(242, 245, 252));
        setPalette(pal1);
    }
    else if(theme == "Dark")
    {
        pal1.setColor(QPalette::ButtonText, QColor(224, 231, 255));
        setPalette(pal1);
    }
}

void MainWindow::TurnOFF() //OFF the application and changes colors depending on the selected color theme
{

    /**
     * @brief Выключает приложение и изменяет цвета в зависимости от выбранной цветовой темы
     * Функция устанавливает состояние "OFF" и текст на кнопке "Turn_ON_OFF" в "Turn ON",
     * вызывает функцию setColorButton_ON_OFF() для изменения цвета кнопки "Turn_ON_OFF".
     * Затем происходит обновление значений на слайдерах и метках для влажности, давления и температуры.
     * В зависимости от выбранной единицы измерения давления и температуры, значения на слайдерах и метках обновляются соответствующим образом.
     * Затем функция изменяет цвет текста на кнопках в зависимости от выбранной цветовой темы.
     */
    Hiding();
    SetEnabledFalse();
    SetState(state, "OFF");
    ui->Turn_ON_OFF->setText("Turn ON");
    setColorButton_ON_OFF();
    QPalette pal1 = palette();
    if(theme == "Light")
    {
        pal1.setColor(QPalette::ButtonText, QColor(157, 164, 199));
        setPalette(pal1);
    }
    else if(theme == "Dark")
    {
        pal1.setColor(QPalette::ButtonText, QColor(114, 127, 171));
        setPalette(pal1);
    }
    ui->Turn_ON_OFF->setText("Turn ON");
    ui->PressureLabel->setText("Pressure: ");
    ui->TemperatureLabel->setText("Temperature: ");
    ui->AngleLabel->setText("Angle of rotation: ");
    ui->HumidityLabel->setText("Humidity: ");
}

void MainWindow::SendResponse() //Sends a response to a request from the Software
{
    /**
     * @brief Отправляет ответ на запрос от программного обеспечения
     *
     * Функция устанавливает сервер для прослушивания всех IP-адресов на порту 8080.
     * При подключении нового клиента, функция считывает запрос и отправляет ответ в зависимости от запроса.
     */
    server.listen(QHostAddress::Any, 8080);
    connect(&server, &QTcpServer::newConnection, [&]() {
        QTcpSocket* socket = server.nextPendingConnection();
        if (socket->waitForReadyRead()) {
            QString request = socket->readAll();
            if (request == "get_data") {
                QString response = QString::number(temperature) + "," + QString::number(pressure) + ","
                + QString::number(angle) + "," + QString::number(humidity) + "," + state + "," + degrees + "," + pressureUnit;
                socket->write(response.toUtf8());
                socket->flush();
                socket->waitForBytesWritten();
            }
            else if(request == "ON" && state == "OFF")
            {
                qDebug() << "Simulator turn ON by Software";
                UnHiding();
                SetEnabledTrue();
                ButtonON();
            }
            else if(request == "ON" && state == "ON")
            {
                qDebug() << "Simulator is already turned ON";
                UnHiding();
                SetEnabledTrue();
                ButtonON();
            }
            else if(request == "OFF" && state == "ON")
            {
                qDebug() << "Simulator turn OFF by Software";
                Hiding();
                SetEnabledFalse();
                ButtonOFF();
            }
            else if(request == "OFF" && state == "OFF")
            {
                qDebug() << "Simulator is already turned OFF";
                Hiding();
                SetEnabledFalse();
                ButtonOFF();
            }
        }
        socket->close();
    });
}
void MainWindow::UnHiding() //UnHides application fields
{
    /**
     * @brief Раскрывает скрытые поля приложения
     * Функция изменяет цвет текста и фона элементов интерфейса приложения, чтобы раскрыть скрытые поля.
     */
    QPalette pal1 = palette();
    if(theme == "Light")
    {
        pal1.setColor(QPalette::ButtonText, QColor(252, 255, 252));
        pal1.setColor(QPalette::WindowText, QColor(252, 255, 252));
        setPalette(pal1);
    }
    else if(theme == "Dark")
    {
        pal1.setColor(QPalette::ButtonText, QColor(224, 231, 255));
        pal1.setColor(QPalette::WindowText, QColor(224, 231, 255));
        setPalette(pal1);
    }
}
void MainWindow::Hiding() //Hides application fields
{
    /**
     * @brief Скрывает поля приложения
     * Функция изменяет цвет текста и фона элементов интерфейса приложения, чтобы скрыть поля.
     */
    QPalette pal1 = palette();
    if(theme == "Light")
    {
        pal1.setColor(QPalette::ButtonText, QColor(157, 164, 199));
        pal1.setColor(QPalette::WindowText, QColor(180, 186, 207));
        setPalette(pal1);
    }
    else if(theme == "Dark")
    {
        pal1.setColor(QPalette::ButtonText, QColor(99, 107, 133));
        pal1.setColor(QPalette::WindowText, QColor(99, 107, 133));
        setPalette(pal1);
    }
}
void MainWindow::ButtonOFF() //Makes the "Turn_ON_OFF" button inactive
{
    /**
     * @brief Делает кнопку "Turn_ON_OFF" неактивной
     * Функция устанавливает состояние кнопки "Turn_ON_OFF" в неактивное.
     */
    ui->Turn_ON_OFF->setEnabled(false);
}
void MainWindow::ButtonON() //Makes the "Turn_ON_OFF" button active
{
    /**
     * @brief Делает кнопку "Turn_ON_OFF" активной
     * Функция устанавливает состояние кнопки "Turn_ON_OFF" в активное.
     */
    ui->Turn_ON_OFF->setEnabled(true);
}

bool MainWindow::event(QEvent *event) //Redefining "event" for successful working of the program on the touch screen
{

    /**
     * @brief Переопределение функции "event" для успешной работы программы на сенсорном экране
     * Эта функция переопределяет функцию "event" для обработки событий касания.
     * @param event(событие), которое нужно обработать
     * @return True, если это событие касания, false - если нет
     */
    if (event->type() == QEvent::TouchBegin ||
        event->type() == QEvent::TouchUpdate ||
        event->type() == QEvent::TouchEnd) {
        return true;
    }
    return QWidget::event(event);
}

bool MainWindow::touchEvent(QTouchEvent *event) //Redefining "touchEvent" for successful working of the program on the touch screen
{
    /**
     * @brief Переопределение функции "touchEvent" для успешной работы программы на сенсорном экране
     * Эта функция переопределяет функцию "touchEvent" для обработки событий касания.
     * Она проверяет состояние точек касания и всегда возвращает true.
     * @param event Событие касания, которое нужно обработать
     * @return True
     */
    if (event->touchPointStates() & Qt::TouchPointPressed) {
    } else if (event->touchPointStates() & Qt::TouchPointMoved) {

    } else if (event->touchPointStates() & Qt::TouchPointReleased) {

    }
    return true;
}
