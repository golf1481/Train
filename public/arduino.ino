#include <Arduino.h>
#if defined(ESP32) || defined(PICO_RP2040)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>

#include <addons/TokenHelper.h>

#include <addons/RTDBHelper.h>
#include <Wire.h>
#include "Adafruit_SHT4x.h"
const int SCLpin = 40;
const int SDApin = 41;
Adafruit_SHT4x sht4 = Adafruit_SHT4x();

#define WIFI_SSID "MIC_2.4GHz"
#define WIFI_PASSWORD "999999999"

#define API_KEY "AIzaSyCL1c8gSblusSfFoePq0HHUkyCfzEcxdZE"

#define DATABASE_URL "cucumber-20a25-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

#define USER_EMAIL "teeraponete148@gmail.com"
#define USER_PASSWORD "123456"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif

unsigned long lastMsg = 0;

void setupwifi()
{
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  multi.addAP(WIFI_SSID, WIFI_PASSWORD);
  multi.run();
#else
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif
  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    if (millis() - ms > 10000)
      break;
#endif
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
#if defined(ESP8266)
  fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 2048 /* Tx buffer size in bytes from 512 - 16384 */);
#endif
  fbdo.setResponseSize(2048);
  Firebase.begin(&config, &auth);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  config.wifi.clearAP();
  config.wifi.addAP(WIFI_SSID, WIFI_PASSWORD);
#endif
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(5);
  config.timeout.serverResponse = 10 * 1000;
}

void setup()
{
  Serial.begin(115200);
  setupwifi();
  Wire1.begin(SDApin, SCLpin);
  sht4.begin(&Wire1);
  Serial.println("Adafruit SHT4x test");
  if (! sht4.begin(&Wire1)) {
    Serial.println("Couldn't find SHT4x");
    while (1) delay(1);
  }
  Serial.println("Found SHT4x sensor");
  Serial.print("Serial number 0x");
  Serial.println(sht4.readSerial(), HEX);
}
int count1;
void loop()
{
  float temp1, hum1;
  unsigned long now = millis();
  if (now - lastMsg > 5000 )
  {
    lastMsg = now;
    sensors_event_t humidity, temp;
    sht4.getEvent(&humidity, &temp);
    Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
    Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
    String t1 = String(temp.temperature);
    String h1 = String(humidity.relative_humidity);
    temp1 = t1.toFloat();
    hum1 = h1.toFloat();
  }

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0) )
  {
    count1++;
    sendDataPrevMillis = millis();
    if (temp1 > 0.001 && hum1 > 0.001)
    {
      Serial.printf("Set temp... %s\n", Firebase.RTDB.setFloat(&fbdo, F("/test/temp"), temp1) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Set humidity... %s\n", Firebase.RTDB.setFloat(&fbdo, F("/test/hum"), hum1) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Set humidity... %s\n", Firebase.RTDB.setFloat(&fbdo, F("/test/timestamp"), count1) ? "ok" : fbdo.errorReason().c_str());
    }
    
  }
}
