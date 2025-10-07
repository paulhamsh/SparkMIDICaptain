# Spark MIDI Captain

Use ESP32, Spark amp and Midi Captain pedal       
Now two versions, one for ESP32 and separate USBHost board, the other for an ESP32 S3 with onboard USB Host capability (plus an OTG cable)     
See https://github.com/paulhamsh/SparkMIDI for all other information about this project.   
Also see https://github.com/paulhamsh/SparkIO6   
    
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
Starting
MIDI (SERIAL DIN MIDI) 0x0 255 255
MIDI (USB S3) 0x90 58 104
MIDI (USB S3) 0x80 58 0
MIDI (USB S3) 0x90 59 47
MIDI (USB S3) 0x80 59 0
Toggle comp
Message: 315
Got message 315
MIDI (USB S3) 0x90 60 16
MIDI (USB S3) 0x80 60 0
Toggle drive
Message: 315
Got message 315
MIDI (USB S3) 0x90 60 44
MIDI (USB S3) 0x80 60 0
Toggle drive
Message: 315
Got message 315
MIDI (USB S3) 0x90 62 12
MIDI (USB S3) 0x80 62 0
Toggle mod
Message: 315
Got message 315
MIDI (USB S3) 0x90 62 37
MIDI (USB S3) 0x80 62 0
Toggle mod
Message: 315
Got message 315
MIDI (USB S3) 0x90 64 48
MIDI (USB S3) 0x80 64 0
Toggle delay
Message: 315
Got message 315
MIDI (USB S3) 0x90 64 4
MIDI (USB S3) 0x80 64 0
Toggle delay
Message: 315
Got message 315
```














