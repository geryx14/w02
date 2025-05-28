#include "oled.h"

Oled::Oled() : u8g2(U8G2_R0) {}

void Oled::begin() {
    u8g2.begin();
}

void Oled::updateDisplay(float voltage, float current, float power, float energy) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_5x7_tf);

    u8g2.setCursor(10, 10);  u8g2.print("Power Monitoring");
    u8g2.setCursor(10, 20);  u8g2.print("Tegangan : "); u8g2.print(voltage); u8g2.print(" V");
    u8g2.setCursor(10, 30);  u8g2.print("Arus     : "); u8g2.print(current); u8g2.print(" A");
    u8g2.setCursor(10, 40);  u8g2.print("Daya     : "); u8g2.print(power); u8g2.print(" W");
    u8g2.setCursor(10, 50);  u8g2.print("Energi   : "); u8g2.print(energy, 3); u8g2.print(" kWh");
    u8g2.sendBuffer();
}
