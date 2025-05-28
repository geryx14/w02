#ifndef LCDOLED_H
#define LCDOLED_H

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

class Oled {
public:
    Oled();
    void begin();
    void updateDisplay(float voltage, float current, float power, float energy);
    
private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
};

#endif
