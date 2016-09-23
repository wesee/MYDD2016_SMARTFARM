
#include <WiFi101.h>
#include "DHT.h"
#include <ArduinoJson.h>


#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

//WiFiSSLClient sslClient;
WiFiClient client;

//static const char ssid[] = "[Your WiFi network SSID or name]";
//static const char pass[] = "[Your WiFi network WPA password or WEP key]";
static const char ssid[] = "Mydd2016";
static const char pass[] = "mydd@2016";

int status = WL_IDLE_STATUS;

DHT dht(DHTPIN, DHTTYPE);

char hostname[] = "api-m2x.att.com";
String uri = "/v2/devices/87b5f5569345d527f8a0cd5bab1b3871/streams/level/value";

void setup() {
    delay(10000);
    
    initSerial();

    initWifi();

    dht.begin();

    
}

void loop() {
    // Run the Remote Monitoring from the Azure IoT Hub C SDK
    // You must set the device id, device key, IoT Hub name and IotHub suffix in
    // remote_monitoring.c
    //remote_monitoring_run();

  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.println();
  Serial.println();

  sendEvent(t);

  delay(60000);
}

void initSerial() {
    // Start serial and initialize stdout
    Serial.begin(115200);
    //Serial.setDebugOutput(true);
}

void initWifi() {
    // Attempt to connect to Wifi network:
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected to wifi");
}


void sendEvent(float value) {

  String json = createJSON(value);
  httpPost(json);

  String response = "";
  char c;
  while (client.available()) {
    c = client.read();
    response.concat(c);
  }

  if (!response.equals("")) {
    if (response.startsWith("HTTP/1.1 201")) {
      Serial.println("Data sent to Azure"); 
    } else {
      Serial.println("Error posting " + json);
      Serial.println(response);
    }
  }

}


String createJSON(float value) {

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["value"] = String(value);

  char json[200];
  root.printTo(json, sizeof(json));
  return String(json);
}


void httpPost(String content)
{
    // close any connection before send a new request.
    client.stop();
  
    if (client.connect(hostname, 80)) {
      client.print("PUT ");
      client.print(uri);
      client.println(" HTTP/1.1"); 
      client.print("Host: "); 
      client.println(hostname);
      client.print("X-M2X-KEY: ");
      client.println("978e930b51c396e506fb6b78f7c38197"); 
      client.println("Connection: close");

      client.print("Content-Type: ");
      client.println("application/json");
      client.print("Content-Length: ");
      client.println(content.length());
      client.println();
      client.println(content);
      
      delay(200);
      
    } else {
      Serial.println("Connection failed");
    }
}





