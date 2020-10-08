#ifndef NEXTIONUPLOADER_HPP
#define NEXTIONUPLOADER_HPP

#include <QByteArray>
#include <QObject>
#include <QSerialPort>

class NextionUploader : public QObject
{
    Q_OBJECT
public:
    explicit NextionUploader(QString &port, qint32 baudrate, qint32 ibauudrate, QObject *parent = nullptr);

    int connectSerial();
    int loadFirmwareFile(const QString &filename);

private:
    QSerialPort serial;
    QString serialName;
    qint32 serialUploadBaudrate;
    qint32 serialInitBaudrate;
    QByteArray firmware;

    void sendCommand(const QByteArray &cmd);
    QByteArray waitForResponse(const int timeout = 1000);

public slots:
    void run(void);

signals:
    void finished(void);
};

#endif // NEXTIONUPLOADER_HPP
