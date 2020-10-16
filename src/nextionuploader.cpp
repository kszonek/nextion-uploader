#include "nextionuploader.hpp"

#include <QDebug>
#include <QFile>
#include <QThread>

NextionUploader::NextionUploader(QString &port, qint32 baudrate, qint32 ibaudrate, QObject *parent) :
    QObject(parent),
    serial(this),
    serialPortName(port),
    serialUploadBaudrate(baudrate),
    serialInitBaudrate(ibaudrate)
{
}

int NextionUploader::connectSerial()
{
    serial.setPortName(serialPortName);
    serial.setBaudRate(serialInitBaudrate);
    serial.open(QSerialPort::ReadWrite);
    if(!serial.isOpen() || !serial.isWritable())
    {
        qCritical() << "Unable to open serial port" << serial.portName();
        emit finished();
        return -1;
    }
    qInfo() << "Serial port" << serialPortName << "opened with baudrate" << serialInitBaudrate;
    return 0;
}

int NextionUploader::loadFirmwareFile(const QString &filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    if(!file.isReadable())
    {
        qCritical() << "Error opening firmware file";
        return -2;
    }
    firmware = file.readAll();
    file.close();
    firmwareSize = firmware.size();
    return 0;
}

void NextionUploader::sendCommand(const QByteArray &cmd)
{
    serial.write(cmd);
    serial.write(QByteArray(3,0xFF));
}

QByteArray NextionUploader::waitForResponse(const int timeout)
{
    QByteArray incomming;
    serial.waitForReadyRead(timeout);
    if(serial.bytesAvailable())
    {
        do
            incomming += serial.readAll();
        while(serial.waitForReadyRead(25));
    }
    if(incomming.size() == 0)
    {
        qWarning() << "Read timeout";
        return QByteArray();
    }
    else
    {
        return incomming;
    }
}

void NextionUploader::run()
{
    qDebug() << "Uploading firmware to serial port";
    qDebug() << "Connecting...";
    QThread::sleep(3);
    sendCommand("connect");
    waitForResponse(2000);      // "comok 1,101,NX4024T032_011R,52,61488,D264B8204F0E1828,16777216" or simmilar
    qDebug() << "Initializing...";
    sendCommand("");
    waitForResponse();
    qDebug() << "Sending firmware info...";
    QByteArray whmi_wri = "whmi-wri ";
    whmi_wri += QString::number(firmware.size());
    whmi_wri += ",";
    whmi_wri += QString::number(serialUploadBaudrate);
    whmi_wri += ",0";
    sendCommand(whmi_wri);
    waitForResponse(2000);   // 0x05

    if(serialInitBaudrate != serialUploadBaudrate)
    {
        serial.close();
        serial.setBaudRate(serialUploadBaudrate);
        serial.open(QSerialPort::ReadWrite);
        QThread::sleep(2);
    }

    qDebug() << "Sending firmware...";
    while(firmware.size())
    {
        qDebug().noquote().nospace()
                << "Remaing data: " << firmware.size()
                << " bytes (" << QString::number(100.-100.*firmware.size()/firmwareSize,'f',2) << "%)";
        QByteArray chunk = firmware.left(4096);
        serial.write(chunk);
        serial.waitForBytesWritten();
        firmware.remove(0,chunk.size());
        waitForResponse(1000);
    }
    qDebug() << "Firmware flashed";
    serial.close();
    emit finished();
}
