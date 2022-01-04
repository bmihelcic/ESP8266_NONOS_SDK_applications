# !!! IMPORTANT !!!
- To build any of the applications you have to manually copy whole application folder to ESP8266\_NONOS\_SDK submodule and run _gen\_misc.sh_ file from there. This is because of complex SDK's "Makefile recursion magic". Even official SDK's example projects require the same procedure. Plan is to write custom makefiles in order to keep submodule clean, but that's currently low on priority list. 
- For example to build _esp8266\_smart\_switch_ project:
  - copy _esp8266\_smart\_switch_ folder to ESP8266\_NONOS\_SDK
  - go to ESP8266\_NONOS\_SDK/esp8266\_smart\_switch and 
  - run _gen\_misc.sh_.
- ESP8266\_NONOS\_SDK submoudle is checked out to release/v2.2.x which requires python2 during the build process. You can easily create virtual environment which uses python2 for that purpose.


## Useful commands

> Note: Create virtual environment (python2) in folder .venv

```
virtualenv -p python2 .venv
```

> Note: activate virtualenvironment

```
source .venv/bin/activate
```

> Note: Erase flash

```
esptool.py erase_flash
```

> Note: program ESP8266 application binaries

```
esptool.py -p /dev/ttyUSB0 write_flash -ff 40m -fm qio -fs 1MB 0x0 bin/eagle.flash.bin 0x10000 bin/eagle.irom0text.bin
```

> Note: program some default binaries to ESP8266

```
esptool.py -p /dev/ttyUSB0 write_flash -ff 40m -fm qio -fs 1MB 0xfb000 bin/blank.bin 0xfc000 bin/esp_init_data_default_v08.bin 0xfe000 bin/blank.bin
```

> Note: connect to serial port

```
picocom -b 115200 /dev/ttyUSB0
```

> Note: read flash from address 0x79000, 305 bytes, save it to .bin file

```
esptool.py read_flash 0x79000 305 mem_dump_0x79000.bin
```

> Note: output memory_dump

```
hexdump -C mem_dump_0x79000.bin
```


