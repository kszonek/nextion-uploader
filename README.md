# nextion-uploader
Command line tool to upload TFT firmware to ITEAD Nextion HMI.

## Building

Project uses QT and cmake, can be build in QTCreator, or from commend line.

### Linux

```
$ git clone git@github.com:kszonek/nextion-uploader.git
$ cd nextion-uploader/build
$ cmake ..
$ make
```

### Windows

Never tested, but if you made it work, please submit PR or create Issue with notes.

### MacOS

Never tested, but if you made it work, please submit PR or create Issue with notes.

## Running

Tool allows to choose different baudrate settings for connecting with HMI display (Nextion default is 9600) and for uploading the firmware.

Allowed range for upload varies depending on device model, for Enhanced "K" series it is up to 115200.

```
$ nextion-uploader --help
Usage: ./nextion-uploader [options]
ITEAD Nextion TFT Firmware uploader

Options:
  -h, --help                      Displays help on commandline options.
  --help-all                      Displays help including Qt specific options.
  -v, --version                   Displays version information.
  -f, --firmware <path>           Firmware file to be uploaded
  -p, --port <path>               Serial port of Nextion device.
  -b, --baudrate <baudrate>       Baudrate to upload firmware with.
  -i, --init-baudrate <baudrate>  Initial baudrate of Nextion device (if
                                  different than upload baudrate.
```
