#include "CayenneLPP.h"

CayenneLPP::CayenneLPP(uint8_t size) : maxsize(size)
{
    buffer = (uint8_t *)malloc(size);
    cursor = 0;
}

CayenneLPP::~CayenneLPP(void)
{
    free(buffer);
}

void CayenneLPP::reset(void)
{
    cursor = 0;
}

uint8_t CayenneLPP::getSize(void)
{
    return cursor;
}

uint8_t *CayenneLPP::getBuffer(void)
{
    return buffer;
}

uint8_t CayenneLPP::copy(uint8_t *dst)
{
    memcpy(dst, buffer, cursor);
    return cursor;
}

uint8_t CayenneLPP::addDigitalInput(uint8_t channel, uint8_t value)
{
    if ((cursor + LPP_DIGITAL_INPUT_SIZE) > maxsize)
    {
        return 0;
    }
    buffer[cursor++] = channel;
    buffer[cursor++] = LPP_DIGITAL_INPUT;
    buffer[cursor++] = value;

    return cursor;
}

uint8_t CayenneLPP::addDigitalOutput(uint8_t channel, uint8_t value)
{
    if ((cursor + LPP_DIGITAL_OUTPUT_SIZE) > maxsize)
    {
        return 0;
    }
    buffer[cursor++] = channel;
    buffer[cursor++] = LPP_DIGITAL_OUTPUT;
    buffer[cursor++] = value;

    return cursor;
}

uint8_t CayenneLPP::addAnalogInput(uint8_t channel, float value)
{
    if ((cursor + LPP_ANALOG_INPUT_SIZE) > maxsize)
    {
        return 0;
    }

    int16_t val = value * 100;
    buffer[cursor++] = channel;
    buffer[cursor++] = LPP_ANALOG_INPUT;
    buffer[cursor++] = val >> 8;
    buffer[cursor++] = val;

    return cursor;
}

uint8_t CayenneLPP::addAnalogOutput(uint8_t channel, float value)
{
    if ((cursor + LPP_ANALOG_OUTPUT_SIZE) > maxsize)
    {
        return 0;
    }
    int16_t val = value * 100;
    buffer[cursor++] = channel;
    buffer[cursor++] = LPP_ANALOG_OUTPUT;
    buffer[cursor++] = val >> 8;
    buffer[cursor++] = val;

    return cursor;
}