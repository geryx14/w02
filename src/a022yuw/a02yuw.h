#ifndef A02YYUW_H
#define A02YYUW_H

#include <Arduino.h>

#define MIN_DISTANCE 30
#define MAX_DISTANCE 4500

#define SERIAL_BAUD_RATE 9600
#define SERIAL_HEAD_DATA 0xff

#define SERIAL_AVAILABLE_CHECK_DELAY 50
#define SERIAL_AVAILABLE_CHECK_CICLES 10

enum
{
    A02YYUW_MEASSUREMENT_STATUS_OK = 0,
    A02YYUW_MEASSUREMENT_STATUS_ERROR_CHECK_SUM = -1,
    A02YYUW_MEASSUREMENT_STATUS_ERROR_MAX_LIMIT = -2,
    A02YYUW_MEASSUREMENT_STATUS_ERROR_MIN_LIMIT = -3,
    A02YYUW_MEASSUREMENT_STATUS_ERROR_SERIAL = -4
};

typedef int A02YYUW_MEASSUREMENT_STATUS;

class A02YYUW
{
private:
    Stream *_stream;
    unsigned int minimalDistance;
    unsigned int maximalDistance;
    unsigned int _distance;
    void _flushSerialInput();

public:
    A02YYUW(Stream * _stream);
    A02YYUW(Stream * _stream, unsigned int minDistance, unsigned int maxDistance);
    A02YYUW_MEASSUREMENT_STATUS meassure();
    String getDistance();
    String getDistanceString();
    bool checkSum(unsigned char data[]);
};

#endif
