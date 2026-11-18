#include <ESP8266WiFi.h>
#include <KiwisIoT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// =================================
// WIFI CONFIGURATION
// =================================

const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";
const char* topic = "YOUR_TOPIC_ID";

// =================================
// SENSOR CONFIGURATION
// =================================

#define SENSOR_PIN D2

OneWire oneWire(SENSOR_PIN);
DallasTemperature sensors(&oneWire);

// =================================
// KIWISIOT CONFIGURATION
// =================================

KiwisIoT kiwisiot(ssid, pass, topic);

// =================================
// TEMPERATURE SETTINGS
// =================================

const float TEMP_LIMIT = 80.0;

unsigned long lastRequest = 0;
unsigned long conversionStart = 0;

bool conversionPending = false;

const unsigned long SEND_INTERVAL = 2000;
const unsigned long CONVERSION_TIME = 750;

// =================================
// SETUP
// =================================

void setup() {

  Serial.begin(115200);

  sensors.begin();

  // Non-blocking temperature conversion
  sensors.setWaitForConversion(false);

  // Initialize KiwisIoT
  kiwisiot.begin();

  Serial.println();
  Serial.println("================================");
  Serial.println("SHIP ENGINE TEMPERATURE MONITOR");
  Serial.println("================================");

  Serial.println("DS18B20 Initialized");
  Serial.println("KiwisIoT Initialized");

}

// =================================
// MAIN LOOP
// =================================

void loop() {

  // Maintain KiwisIoT connection
  kiwisiot.run();

  unsigned long currentMillis = millis();

  // Request temperature
  if (!conversionPending &&
      currentMillis - lastRequest >= SEND_INTERVAL) {

    lastRequest = currentMillis;

    sensors.requestTemperatures();

    conversionStart = currentMillis;
    conversionPending = true;
  }

  // Read after conversion completes
  if (conversionPending &&
      currentMillis - conversionStart >= CONVERSION_TIME) {

    conversionPending = false;

    float temperature = sensors.getTempCByIndex(0);

    // Check sensor connection
    if (temperature == DEVICE_DISCONNECTED_C) {

      Serial.println("Sensor Connection Error!");

      return;
    }

    // Display temperature
    Serial.println("----------------------------");

    Serial.print("Engine Temperature: ");
    Serial.print(temperature, 2);
    Serial.println(" C");

    // =================================
    // HIGH TEMPERATURE DETECTION
    // =================================

    String status;

    if (temperature >= TEMP_LIMIT) {

      status = "1";

      Serial.println("WARNING: HIGH TEMPERATURE!");

    } else {

      status = "0";

      Serial.println("Temperature Normal");

    }

    // =================================
    // SEND DATA TO KIWISIOT
    // =================================

    // Channel 0 - Temperature
    kiwisiot.send("0", String(temperature, 2));

    // Channel 1 - Temperature Status
    kiwisiot.send("1", status);

    Serial.println("KiwisIoT Data Sent");

    Serial.println("----------------------------");

  }

}