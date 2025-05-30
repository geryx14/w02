#include <Arduino.h>
#include "pzeom/pzem.h"
#include "oled/oled.h"
#include "mqtt/mqtt.h"

#define WIFI_SSID "Bubur ayam"
#define WIFI_PASSWORD "14072002"

#define MQTT_SERVER "13.250.11.63"
#define MQTT_PORT 1883
#define MQTT_USER ""
#define MQTT_PASSWORD ""

#define MQTT_TOPIC "sensor/pzem"
#define PUBLISH_INTERVAL 5000 

MqttClient mqttClient(MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASSWORD);
unsigned long lastPublishTime = 0;

//Oled oled;
PZEMSensor sensor;

void setup() {
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");

    mqttClient.init();
    sensor.begin();
    //oled.begin();
}

void loop() {
    mqttClient.loop();  
    unsigned long currentMillis = millis(); 

    sensor.update();
    float voltage = sensor.getVoltage();
    float current = sensor.getCurrent();
    float power = sensor.getPower();
    float energy = sensor.getEnergy();
    float frequency = sensor.getFrequency();
    float pf = sensor.getPF();
    //oled.updateDisplay(voltage, current, power, energy, frequency, pf);
    if (currentMillis - lastPublishTime >= PUBLISH_INTERVAL) {
        lastPublishTime = currentMillis; 

        String time = String(currentMillis);  
        String voltageStr = String(voltage, 2);
        String currentStr = String(current, 2);
        String powerStr = String(power, 2);
        String energyStr = String(energy, 3);
        String frequencyStr = String(frequency, 1);
        String pfStr = String(pf, 2);

        mqttClient.publish(MQTT_TOPIC,voltageStr, currentStr, powerStr, energyStr, frequencyStr, pfStr);
        
        Serial.println("Data Published to MQTT!");
    }
}
