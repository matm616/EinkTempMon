#include <Arduino.h>
#include <Adafruit_ThinkInk.h>
#include <ESP8266WiFi.h>
#include <Wire.h>   
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

#define SRAM_CS   16
#define EPD_CS    0
#define EPD_DC    15
#define EPD_RESET -1 // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY  -1 // can set to -1 to not use a pin (will wait a fixed delay)
#define EPD_SPI &SPI

ThinkInk_290_Grayscale4_T5 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
// Adafruit_IL0373 display(296, 128, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY, EPD_SPI); 
// #define FLEXIBLE_290


#define COLOUR1 EPD_BLACK
#define COLOUR2 EPD_DARK
#define COLOUR3 EPD_LIGHT
#define COLOUR4 EPD_WHITE

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);  


void setup() {
  WiFi.mode(WIFI_OFF);
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  Wire.begin(4, 5);   
  bmp.begin();
  display.begin(THINKINK_GRAYSCALE4);
}

float readings[20] = {-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0,-100.0};
int i = 0;
float high = -100;
float low = 100;

void loop() {
  
  sensors_event_t event;
  bmp.getEvent(&event);
  float temperature;
  bmp.getTemperature(&temperature);
  Serial.println("Starting");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("C");
  
  readings[i] = temperature;
  i++;
  float sum = 0;
  int count = 0;
  if (temperature > high) {
    high = temperature;
  }
  if (temperature < low) {
    low = temperature;
  }

  for (int j = 0; j <= 20; j++) {
    if (readings[j] == 100.0) {
      break;
    }
    sum = sum + temperature;
    count++;
  }
  float average = sum/count;


  Serial.print("Writing to display");
  // display.setRotation(3);
  display.clearBuffer();

  // print current temp
  display.setTextColor(EPD_BLACK);
  display.setTextWrap(true);
  display.setCursor(55, 30);
  display.setTextSize(5);
  display.print(String(temperature) + "C");

  // print low and high
  display.setTextColor(EPD_DARK);
  display.setTextWrap(true);
  display.setCursor(50, 100);
  display.setTextSize(2);
  display.print(String(low) + "C .. " + String(high) + "C");

  // print average
  display.setTextColor(EPD_DARK);
  display.setTextWrap(true);
  display.setCursor(215, 5);
  display.setTextSize(2);
  display.print(String(average) + "C");

  display.display();
  delay(180000);  // minimum time between display updates
}
