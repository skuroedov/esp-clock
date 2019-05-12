#include <DallasTemperature.h>
#include <OneWire.h>
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SSD1306.h>
#include <SSD1306Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>

#define SSID "Your SSID"
#define PASSWORD "Your password"
#define APIKEY "Your API key"
#define ZIPCODE "Your ZIP code"

SSD1306 display(0x3c, 0, 2);
HTTPClient http;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 2*3600);
OneWire oneWire(3);
DallasTemperature sensors(&oneWire);
String temp;
String _time;
int tempOutsideLast = 0;

void setup() {
 display.init();
 display.flipScreenVertically();

 WiFi.mode(WIFI_STA);
 WiFi.begin(SSID, PASSWORD);
 while(WiFi.status() != WL_CONNECTED) delay(300);
 timeClient.begin();
 sensors.begin();
}

String tempOutside() {
  http.begin("http://api.openweathermap.org/data/2.5/weather?zip=ZIPCODE,cz&units=metric&APPID=APIKEY");
  if(http.GET() > 0) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    String res = doc["main"]["temp"];
    tempOutsideLast = millis();
    return res;
  }
}

void printTime() {
  display.setFont(ArialMT_Plain_24);
  timeClient.update();
  if(timeClient.getMinutes() < 10) {
    _time = String(timeClient.getHours()) + ":0" + String(timeClient.getMinutes());
  } else {
    _time = String(timeClient.getHours()) + ":" + String(timeClient.getMinutes());
  }
  display.drawString(32, 0, _time);
}

void printOutsideTemp() {
  display.setFont(ArialMT_Plain_16);
  if(millis() - tempOutsideLast > 300000 || tempOutsideLast < 5000) temp = tempOutside();
  display.drawString(0, 48, temp + " °C");
}

void printInsideTemp() {
  display.setFont(ArialMT_Plain_16);
  sensors.requestTemperatures();
  int _temp = sensors.getTempCByIndex(0);
  display.drawString(80, 48, String(_temp) + " °C");
}

void loop() {
  display.clear();
  
  printTime();
  printOutsideTemp();
  printInsideTemp();

  display.display();
  delay(5000);
}
