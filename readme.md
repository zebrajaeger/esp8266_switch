## hardware

* esp-01
* program adapter (USB to serial, 3,3V Regulator with program and reset switch)

## modify esp-01

* Buy a flash memory chip mit 32Mbit (4MByte) and replace it with the existing one

## build frontend

install node

cd frontend_ap
npm install
npm run build

cd ../frontend_ap
npm install
npm run build

## build and flash esp

install atom with platformio-ide plugin and httpclang
see http://docs.platformio.org/en/latest/ide/atom.html
install expressif8266 plugin

Go to .platfromio in user directory and search for a file with name 'esp01_1m.json'
i.E. C:\Users\lars\.platformio\platforms\espressif8266\boards\esp01_1m.json

Parallel to this file create a new one:

touch esp01_4m.json and copy this content in:

{
  "build": {
    "core": "esp8266",
    "extra_flags": "-DESP8266 -DARDUINO_ARCH_ESP8266 -DARDUINO_ESP8266_ESP01",
    "f_cpu": "80000000L",
    "f_flash": "40000000L",
    "flash_mode": "qio",
    "ldscript": "eagle.flash.4m.ld",
    "mcu": "esp8266",
    "variant": "generic"
  },
  "connectivity": [
    "wifi"
  ],
  "frameworks": [
    "arduino",
    "esp8266-rtos-sdk",
    "esp8266-nonos-sdk"
  ],
  "name": "Espressif Generic ESP8266 ESP-01 1M",
  "upload": {
    "maximum_ram_size": 81920,
    "maximum_size": 4194304,
    "require_upload_port": true,
    "resetmethod": "ck",
    "speed": 115200
  },
  "url": "http://www.esp8266.com/wiki/doku.php?id=esp8266-module-family",
  "vendor": "Espressif"
}

* Now open the bootstrap project and flash it via usb
* start it and see on serial monitor the output
* the ip address is important. you will need it to configure the firmware project

* open the firmware project
* change or add the line of code with the ip you got from the previous step
** upload_port = 192.168.178.27
* Transfer frontend Files into flash
** Atom -> PlatformIO -> Run other target -> PIO Upload SPIFFS Image
* Write firmware
** Atom -> PlatformIO -> Upload

## Run
Reboot esp

Take a mobile device like a smartphone. Open Wifi settings and connect to the "ESP8266 AP"
Open a Browser und put in some url like foo.bar (a domain thats ip is not cached like a non existing domain) 
Choose a Network, enter pasword
Reboot
Your Router shold say what ip the esp has
open a browser and connect to http://<ip>
