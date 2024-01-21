# E-Ink Temperature Monitor

A temperature monitor using an Adafruit 2.9" 4 colour Grayscale E-Ink/EPD feather shield, an Adafruit HUZZAH ESP8266 and an I2C BME280.
Made using the PlatformIO ecosystem, using the ESP8266 Arduino framework.

## Features

* It updates every 3 minutes
* Keeps a rolling average temperature from that last hour
* Shows lowest temperature from the last hour
* Shows highest temperature from the last hour

## Installation

Building and uploading is done via PlatformIO.

Clone the project, open it with VS Code and use the PlatformIO Extension to build and upload.
