#ifndef NTP_TIME_H
#define NTP_TIME_H

#include <Arduino.h>
#include "time.h"

class NTPTime {
public:
    NTPTime(const char* ntpServer, long gmtOffset_sec, int daylightOffset_sec);
    void begin();
    void update();  
    String getTimeString();
    String getCurrentTime();  // Getter untuk variabel waktu terbaru

private:
    const char* _ntpServer;
    long _gmtOffset_sec;
    int _daylightOffset_sec;
    struct tm timeinfo;
    unsigned long lastUpdateMillis;
    String currentTime;
};

#endif