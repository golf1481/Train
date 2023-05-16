#include <WiFi.h>
#include <PubSubClient.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ModbusMaster.h>

ModbusMaster node;

const char* ssid = "TP-Link_2B32";
const char* password = "58252017";
const char* mqtt_server = "192.168.1.101"; //IP Server

//////////////////////SETUP/////////////////////////
IPAddress local_IP(192, 168, 1, 208); // Static IP address
IPAddress gateway(192, 168, 1, 1); // Gateway IP address
IPAddress subnet(255, 255, 255, 0); // subnet
char machine[5] = "TB02"; //Machine name
//////////////////////SETUP/////////////////////////

WiFiClient espClient;
PubSubClient client(espClient);

#define led_connection 5
#define led_run 6
int count_connection;

void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //WiFi.mode(WIFI_STA);
  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    count_connection++;
    digitalWrite(led_connection, HIGH); delay(100); digitalWrite(led_connection, LOW); delay(100);
    Serial.print(".");
    if (count_connection > 20)
    {
      ESP.restart();
    }
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW); // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off by making the voltage HIGH
  }
}

int time_count;

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      //delay(5000);
      time_count++;
      digitalWrite(led_connection, HIGH); delay(500); digitalWrite(led_connection, LOW); delay(500);
      if (time_count >= 10)
      {
        ESP.restart();
      }
    }
  }
}

void setup()
{
  pinMode(led_connection, OUTPUT); // Initialize the BUILTIN_LED pin as an output
  pinMode(led_run, OUTPUT); ////
  Serial.begin(9600);
  Serial1.begin(9600);
  setup_wifi();
  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname(machine);
  // No authentication by default
  ArduinoOTA.setPassword("1234");
  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
  ArduinoOTA
  .onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";
    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  })
  .onEnd([]() {
    Serial.println("\nEnd");
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");

  });
  ArduinoOTA.begin();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  node.begin(1, Serial1);
}

int counter;
String rssi, d200, d201, d202, d203, d204, d205; // Add register ,d206,…….n;
char r[16], d0[16], d1[16], d2[16], d3[16], d4[16], d5[16]; // Add register ,d6[16],…….n;
int num = 1; //number of registers

void loop()
{
  ArduinoOTA.handle();
  uint8_t j, result;
  uint16_t data[num];
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  digitalWrite(led_connection, HIGH);
  Serial.println("\n---------------starting loop----------------");
  result = node.readHoldingRegisters(0, num);
  if (result == node.ku8MBSuccess)
  {
    for (j = 0; j < num; j++)
    {
      data[j] = node.getResponseBuffer(j);
    }
    d200 = String(data[0]);
    // Add register Ex. d201= String(data[1]);

    digitalWrite(led_run, LOW); delay(500); digitalWrite(led_run, HIGH); delay(500); //////
  }
  rssi = WiFi.RSSI(); // WiFi strength
  Serial.print("rssi : "); Serial.println(WiFi.RSSI());
  Serial.print("d200 : "); Serial.println(d200);
  // Add Serial Monitor

  d200.toCharArray(d0, 16); client.publish("TB01/D200", d0);
  // Add register Ex. d201.toCharArray(d1,16);client.publish("D201", d1);

  Serial.println("\n---------------finish loop------------------\n\n");
  delay(5000);
}
