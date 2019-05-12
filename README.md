# esp-clock
Clock with ESP8266 and OLED display. It shows time, outside temp and inside temp with SSD1306, ESP8266 and DS18B20.

---

## HW used

- Esp01s
- 5V -> 3V3 converter
- SSD1306 128x64 (you can use other display, but you have to customize the positions of entities)
- DS18B20
- 4k7 resistor
- 2x 10 uF caps
- LM7805

---

## Setup
### WiFi
Edit lines 12 & 13 and set your WiFi connection:
```
#define SSID "Your SSID"
#define PASSWORD "Your password"
```

---

### Outside temp
Register on openweathermap.com, get API key and change line 14:
```
#define APIKEY "Your API key"
```

---

### Your location
OpenWeatherMap has many methods to get your location. I am using my ZIP code, but you can use for example GPS coordinates, city or state name. To set zip code, edit line 15:
```
#define ZIPCODE "Your ZIP code"
```
If you want to use custom method, edit line 40:
```
http.begin("http://api.openweathermap.org/data/2.5/weather?zip=ZIPCODE,cz&units=metric&APPID=APIKEY");
```

OpenWeatherMap documentation:
https://openweathermap.org/api

### Time
Edit line 16 to set your timezone.
```
#define TIMEOFFSET "Your time offset"
```

---

## Issues

- Some OLED displays have non-standard addresses. For example my is 128x64 and it should have 0x3D address, but it has 0x3C. Try to determinate your address. It is not my fault.

---

## Libraries

- https://github.com/bblanchon/ArduinoJson
- https://github.com/esp8266/Arduino
- https://github.com/ThingPulse/esp8266-oled-ssd1306
- https://github.com/PaulStoffregen/OneWire
- https://github.com/milesburton/Arduino-Temperature-Control-Library
- https://github.com/arduino-libraries/NTPClient
