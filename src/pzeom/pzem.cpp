#include "pzem.h"

PZEMSensor::PZEMSensor() : pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN, 0x01), lastUpdate(0) {}

void PZEMSensor::begin() {
    Serial.begin(115200);
    Serial.println("Membaca data dari PZEM-004T...");
}

void PZEMSensor::update() {
    if (millis() - lastUpdate >= 2000) {  
        lastUpdate = millis();
        voltage = pzem.voltage();
        current = pzem.current();
        power = pzem.power();
        energy = pzem.energy();
        frequency = pzem.frequency();
        pf = pzem.pf();
    }
}

float PZEMSensor::getVoltage() { return voltage; }
float PZEMSensor::getCurrent() { return current; }
float PZEMSensor::getPower() { return power; }
float PZEMSensor::getEnergy() { return energy; }
float PZEMSensor::getFrequency() { return frequency; }
float PZEMSensor::getPF() { return pf; }
