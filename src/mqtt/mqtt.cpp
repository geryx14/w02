#include "mqtt.h"

MqttClient::MqttClient(String server, int port, String user, String password) 
    : mqttServer(server), mqttPort(port), mqttUser(user), mqttPassword(password), mqttClient(espClient) {}

void MqttClient::init() {
    WiFi.begin();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");
    
    macAddress = WiFi.macAddress();
    mqttClient.setServer(mqttServer.c_str(), mqttPort);
}

void MqttClient::reconnect() {
    while (!mqttClient.connected()) {
        Serial.print("Menghubungkan ke MQTT...");
        if (mqttClient.connect("ESP32Client", mqttUser.c_str(), mqttPassword.c_str())) {
            Serial.println("Terhubung!");
        } else {
            Serial.print("Gagal, kode: ");
            Serial.print(mqttClient.state());
            Serial.println(" Coba lagi dalam 5 detik...");
            delay(5000);
        }
    }
}

void MqttClient::publish(String topic, String time, String voltage, String current, String power, String energy, String frequency, String pf) {
    if (!mqttClient.connected()) {
        reconnect();
    }
    
    String payload = "{";
    payload += "\"time\":\"" + time + "\",";
    payload += "\"voltage\":\"" + voltage + "\",";
    payload += "\"current\":\"" + current + "\",";
    payload += "\"power\":\"" + power + "\",";
    payload += "\"energy\":\"" + energy + "\",";
    payload += "\"frequency\":\"" + frequency + "\",";
    payload += "\"pf\":\"" + pf + "\"";
    payload += "}";

    mqttClient.publish(topic.c_str(), payload.c_str());
    Serial.println("Data Published:");
    Serial.println(payload);
}


void MqttClient::loop() {
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop();
}
