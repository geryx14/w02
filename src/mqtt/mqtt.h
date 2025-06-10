#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

class MqttClient {
private:
    WiFiClient espClient;         
    PubSubClient mqttClient;        
    String mqttServer;              
    int mqttPort;                   
    String mqttUser;               
    String mqttPassword;     
    String macAddress;    

    void reconnect();  // Fungsi untuk memastikan koneksi tetap aktif

public:
    /**
     * Konstruktor untuk inisialisasi MQTT client
     */
    explicit MqttClient(String server, int port, String user, String password);

    /**
     * Inisialisasi koneksi WiFi dan MQTT
     */
    void init();

    /**
     * Mengirim pesan ke topik tertentu
     */
    void publish(String topic,String timestamp,String voltage, String current, String power, String energy, String frequency, String pf);


    /**
     * Menangani loop MQTT dan menjaga koneksi tetap aktif
     */
    void loop();

};

#endif
