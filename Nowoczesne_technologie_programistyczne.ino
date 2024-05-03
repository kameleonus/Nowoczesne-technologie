#include "Arduino.h"
#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "coolverticarg12.h"
TFT_eSPI tft = TFT_eSPI();
String message="Nazwa:\nESP32 wiadomosci\nHaslo:\npassword\nIP: 192.168.1.1";
String processor(const String& var){
String returnMessage=message;
return returnMessage;
return String(); 
}

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
AsyncWebServer  server(80);

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
const char *ssid = "ESP32 wiadomosci";
const char *password = "password";

const char* PARAM_INPUT_1 = "message";

const char HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Nowoczesne technologie programistyczne</title>
  <meta charset="UTF-8" name="viewport" content="width=device-width, initial-scale=2">
  </head><body>
  Napisz wiadomość do wysłania<br>
  <form action="/get">
    <textarea name="message" style="width: 200px; height: 150px;">%returnMessage%</textarea><br><br>
    <input type="submit" value="Submit">
  </form><br>
  </body></html>
)rawliteral";



void setup(void) {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
    tft.setCursor(0,5);
    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(3);
    tft.loadFont(coolverticarg12);
    tft.setTextSize(1);
  tft.println("Nazwa:\nESP32 wiadomości\n");
  tft.println("Haslo:\npassword\n");
 
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
 
  server.begin();

  Serial.println("Server started");
  tft.println("IP: 192.168.1.1");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", HTML,processor);
  });
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      message=inputMessage;
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(0,5);
      tft.println(message);

    }request->redirect("/");
  });
}

void loop() {
  
}

