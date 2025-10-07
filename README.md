# Spark MIDI Captain

Use ESP32, Spark amp and Midi Captain pedal       
Now two versions, one for ESP32 and separate USBHost board, the other for an ESP32 S3 with onboard USB Host capability (plus an OTG cable)     
See https://github.com/paulhamsh/SparkMIDI for all ther other information about this project.   
    
## Dependencies:

```
NimBLE-Arduino               2.3.6   OR   1.4.3                     
SSD1306 by Adafruit          2.5.14     
ESP32 Dev Module board       3.2.0   
Adafruit GFX                 1.12.1
USB Host Shield Library 2.0  1.7.0   
```

USB Host Shield is here: https://yuuichiakagawa.github.io/USBH_MIDI/  and  https://github.com/felis/USB_Host_Shield_2.0        

With the ESP32 S3 the on-board host USB is used. These two libraries were invaluable for integrating this:

https://github.com/enudenki/esp32-usb-host-midi-library   
(and https://www.hackster.io/ndenki/esp32-usb-host-midi-library-032d95)  
https://github.com/touchgadget/esp32-usb-host-demos    

I used code from the touchgadget github - either would have been great!!!   
The touchgadget one has a lot of useful information about obtaining 5v for the USB host - although the S3 has a solder bridge on the bottom for this purpose.    



This works fully with NimBLE 1.4.3 (src/v143) and 2.3.6 (src/v236).    

MidiCaptainv3 only works with NimBLE 2.3.6 and the ESP32 S3.
  

On startup, you should see this - turn on the Spark amp first!:     

```
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x1 (POWERON),boot:0x8 (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x118c
load:0x403c8700,len:0x4
load:0x403c8704,len:0xc20
load:0x403cb700,len:0x30e0
entry 0x403c88b8
Spark MIDI Captain
==================
Scanning for Spark
Found 'Spark MINI BLE'
Scanning for BLE MIDI device
Spark connected
connect_spark(): Spark connected
Available for app to connect...
Bluetooth library is NimBLE
SparkIO version: CircularArray and malloc
SPARK TYPE: Spark MINI
Got serial number
Got firmware version
Got checksum
Got serial number
Got preset: 0
Got preset: 1
Got preset: 2
Got preset: 3
Missed preset: 256
CLEARED SPARK
Got preset: 9
End of setup
Starting
MIDI (SERIAL DIN MIDI) 0x0 255 255
MIDI (USB S3) 0x90 57 41
MIDI (USB S3) 0x80 57 0
Toggle noisegate
Message: 315
Got message 315
MIDI (USB S3) 0x90 55 10
MIDI (USB S3) 0x80 55 0
MIDI (USB S3) 0x90 53 1
MIDI (USB S3) 0x80 53 0
```












