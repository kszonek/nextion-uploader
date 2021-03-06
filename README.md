# nextion-uploader
Command line tool to upload TFT firmware to ITEAD Nextion HMI.

## Building

Project is written in QT5 and uses cmake, can be build in QTCreator or from command line.

### Linux

![Linux Build](https://github.com/kszonek/nextion-uploader/workflows/Linux%20Build/badge.svg)   

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

## Usage

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

## Getting your file

Tool requires you to provide generated TFT firmware ("compiled"), not the HMI file that can be edited in Nextion Editor. To get the TFT out of your HMI, navigate to File -> TFT Output in your Nextion Editor and press Generate.

If you know any other way to generate TFTs, let me know :)
