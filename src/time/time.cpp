#include "time.h"

NTPTime::NTPTime(const char* ntpServer, long gmtOffset_sec, int daylightOffset_sec)
    : _ntpServer(ntpServer), _gmtOffset_sec(gmtOffset_sec), _daylightOffset_sec(daylightOffset_sec), lastUpdateMillis(0), currentTime("00:00:00") {}

void NTPTime::begin() {
    configTime(_gmtOffset_sec, _daylightOffset_sec, _ntpServer);
}

void NTPTime::update() {
    unsigned long currentMillis = millis();
    
    // Perbarui waktu dari NTP setiap 1 detik
    if (currentMillis - lastUpdateMillis >= 1000 || lastUpdateMillis == 0) {
        if (getLocalTime(&timeinfo)) {
            char buffer[10];
            sprintf(buffer, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
            currentTime = String(buffer);
            lastUpdateMillis = currentMillis;
        }
    }
}

String NTPTime::getTimeString() {
    return currentTime;  // Mengembalikan waktu terbaru
}

String NTPTime::getCurrentTime() {
    return currentTime;
}