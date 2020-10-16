#include <QCoreApplication>

#include <QCommandLineParser>
#include <QDebug>
#include <QFile>
#include <QLoggingCategory>
#include <QTimer>

#include "nextionuploader.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("ITEAD Nextion Firmware uploader");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
                          {{"f", "firmware"},
                           QCoreApplication::translate("main", "Firmware file to be uploaded"),
                           QCoreApplication::translate("main", "path")},
                          {{"p", "port"},
                           QCoreApplication::translate("main", "Serial port of Nextion device."),
                           QCoreApplication::translate("main", "path")},
                          {{"b", "baudrate"},
                           QCoreApplication::translate("main", "Baudrate to upload firmware with."),
                           QCoreApplication::translate("main", "baudrate")},
                          {{"i", "init-baudrate"},
                           QCoreApplication::translate("main", "Initial baudrate of Nextion device (if different than upload baudrate."),
                           QCoreApplication::translate("main", "baudrate")},
                          {"verbose",
                           QCoreApplication::translate("main", "Output debug information.")},
                      });

    parser.process(a);

    if(!parser.isSet("firmware"))
    {
        qCritical() << "No firmware file specified";
        parser.showHelp(-1);
    }
    QString port = parser.isSet("port") ? parser.value("port") : "/dev/ttyUSB0";
    qint32 baudrate = parser.isSet("baudrate") ? parser.value("baudrate").toUInt() : 115200;
    qint32 ibaudrate = parser.isSet("init-baudrate") ? parser.value("init-baudrate").toUInt() : baudrate;
    QString firmware(parser.value("firmware"));
    if(parser.isSet("verbose") == false)
    {
        QLoggingCategory::setFilterRules("*.debug=false");
    }

    if(!QFile::exists(firmware))
    {
        qCritical() << "Firmware file:" << firmware << " does not exist";
        return -1;
    }

    NextionUploader *nex = new NextionUploader(port,baudrate,ibaudrate);

    if(int ret = nex->loadFirmwareFile(firmware))
    {
        return ret;
    }
    if(int ret = nex->connectSerial())
    {
        return ret;
    }

    QObject::connect(nex, &NextionUploader::finished, &a, &QCoreApplication::quit);
    QTimer::singleShot(0, nex, &NextionUploader::run);

    return a.exec();
}
