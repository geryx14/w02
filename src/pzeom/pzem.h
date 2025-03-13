#ifndef PZEM_SENSOR_H
#define PZEM_SENSOR_H

#include <Arduino.h>
#include <PZEM004Tv30.h>

#define PZEM_RX_PIN 16  
#define PZEM_TX_PIN 17  
#define PZEM_SERIAL Serial2

class PZEMSensor {
public:
    PZEMSensor();      // Konstruktor
    void begin();      // Inisialisasi sensor
    void update();     // Update data sensor
    float getVoltage();
    float getCurrent();
    float getPower();
    float getEnergy();
    float getFrequency();
    float getPF();

private:
    PZEM004Tv30 pzem;
    float voltage, current, power, energy, frequency, pf;
    unsigned long lastUpdate;
};

#endif
