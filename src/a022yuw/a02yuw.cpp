#include "a02yuw.h"

A02YYUW::A02YYUW(Stream * stream) : A02YYUW(stream, MIN_DISTANCE, MAX_DISTANCE)
{
}

A02YYUW::A02YYUW(Stream * stream, unsigned int minDistance, unsigned int maxDistance)
{
    _stream = stream;
    minimalDistance = minDistance;
    maximalDistance = maxDistance;
}

A02YYUW_MEASSUREMENT_STATUS A02YYUW::meassure()
{
    unsigned long startTime = millis();
    unsigned char data[4] = {};
    int i = 0;
    unsigned int meassuredDistance;

    _flushSerialInput();

    _distance = minimalDistance;

    while (!_stream->available() && i < SERIAL_AVAILABLE_CHECK_CICLES)
    {
        i++;
        delay(SERIAL_AVAILABLE_CHECK_DELAY);
    }

    i = 0;

    while (_stream->available() && i < 4)
    {
        data[i] = _stream->read();

        i++;

        if (data[0] != SERIAL_HEAD_DATA)
        {
            i = 0;
        }
    }

    if (i != 4)
    {
        return A02YYUW_MEASSUREMENT_STATUS_ERROR_SERIAL;
    }

    if (!checkSum(data))
    {
        return A02YYUW_MEASSUREMENT_STATUS_ERROR_CHECK_SUM;
    }

    meassuredDistance = ((data[1] << 8) + data[2]);

    if (meassuredDistance < minimalDistance)
    {
        return A02YYUW_MEASSUREMENT_STATUS_ERROR_MIN_LIMIT;
    }

    if (meassuredDistance > maximalDistance)
    {
        return A02YYUW_MEASSUREMENT_STATUS_ERROR_MAX_LIMIT;
    }

    _distance = meassuredDistance;

    return A02YYUW_MEASSUREMENT_STATUS_OK;
}

String A02YYUW::getDistance() {

    Serial.print("Jarak: ");
    Serial.print(_distance);
    Serial.println(" cm");
  return String(_distance);
}

bool A02YYUW::checkSum(unsigned char data[]) {
  return ((data[0] + data[1] + data[2])& 0x00FF) == data[3];
}

void A02YYUW::_flushSerialInput() {
  unsigned long startTime = millis();

  while (_stream->available()) {
    _stream->read();
  }
}