// #include <user_config.h>
#include "wifimanager.h"
// #include "webserver.h"
// #include "mopidy.h"
// #include "ir.h"
// #include <AppSettings.h>

// #define SERIAL_DEBUG true

// bool initialized = false;

// void onConnected() {
// 	Mopidy::isConnected = true;
// 	if (!initialized) {
// 		IR::start();
// 		initialized = true;
// 	}
// }

// void onDisconnected() {
// 	Mopidy::isConnected = false;
// }

// void onReady() {
// 	WebServer::start();
// 	WifiManager::start(onConnected, onDisconnected);
// }

// void init()
// {
// 	spiffs_mount();

// 	Serial.begin(SERIAL_BAUD_RATE);
// 	Serial.systemDebugOutput(SERIAL_DEBUG);

// 	AppSettings.load();
	
// 	WifiManager::configAccessPoint(true);

// 	System.onReady(onReady);
// }

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "wifi-12-private";
const char* password = "9263777101";

ESP8266WebServer server(80);

void setup(void){
  Serial.begin(115200);
  WifiManager::configAccessPoint(true);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}