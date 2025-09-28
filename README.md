# Spark MIDI Captain

Use ESP32, Spark amp and Midi Captain pedal    
Now two versions, one for ESP32 and separate USBHost board, the other for an ESP32 S3 with onboard USB Host capability (plus an OTG cable)   

    
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

I used code from the latter one - either would have been great!!!



This works fully with NimBLE 1.4.3 (src/v143) and 2.3.6 (src/v236).    

MidiCaptainv3 only works with NimBLE 2.3.6 and the ESP32 S3.
  

On startup, you should see this - turn on the Spark amp first!:     

```
Spark MIDI Captain
==================
Scanning...
Found 'Spark 2 BLE'
Spark connected
connect_spark(): Spark connected
Available for app to connect...
Bluetooth library is NimBLE
SparkIO version: CircularArray and malloc
SPARK TYPE Got serial number
Got firmware version
Failed to get checksum
Got serial number
Got preset: 0
Got preset: 1
Got preset: 2
Got preset: 3
Got preset: 9
End of setup
Starting
```








