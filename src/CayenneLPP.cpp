#include "CayenneLPP.h"

CayenneLPP::CayenneLPP()
{
    buffer = (uint8_t *)malloc(Size);
    currentPtr = 0;
}

CayenneLPP::~CayenneLPP(void)
{
    free(buffer);
}

void CayenneLPP::reset(void)
{
    currentPtr = 0;
}

uint8_t CayenneLPP::getSize(void)
{
    return currentPtr;
}

uint8_t *CayenneLPP::getBuffer(void)
{
    return buffer;
}

uint8_t CayenneLPP::copy(uint8_t *dst)
{
    memcpy(dst, buffer, currentPtr);
    return currentPtr;
}

uint8_t CayenneLPP::addDigitalInput(uint8_t channel, uint8_t value)
{
    if ((currentPtr + LPP_DIGITAL_INPUT_SIZE) > maxsize)
    {
        return 0;
    }
    buffer[currentPtr++] = channel;
    buffer[currentPtr++] = LPP_DIGITAL_INPUT;
    buffer[currentPtr++] = value;

    return currentPtr;
}

uint8_t CayenneLPP::addDigitalOutput(uint8_t channel, uint8_t value)
{
    if ((currentPtr + LPP_DIGITAL_OUTPUT_SIZE) > maxsize)
    {
        return 0;
    }
    buffer[currentPtr++] = channel;
    buffer[currentPtr++] = LPP_DIGITAL_OUTPUT;
    buffer[currentPtr++] = value;

    return currentPtr;
}

uint8_t CayenneLPP::addAnalogInput(uint8_t channel, float value)
{
    if ((currentPtr + LPP_ANALOG_INPUT_SIZE) > maxsize)
    {
        return 0;
    }

    int16_t val = value * 100;
    buffer[currentPtr++] = channel;
    buffer[currentPtr++] = LPP_ANALOG_INPUT;
    buffer[currentPtr++] = val >> 8;
    buffer[currentPtr++] = val;

    return currentPtr;
}

uint8_t CayenneLPP::addAnalogOutput(uint8_t channel, float value)
{
    if ((currentPtr + LPP_ANALOG_OUTPUT_SIZE) > maxsize)
    {
        return 0;
    }
    int16_t val = value * 100;
    buffer[currentPtr++] = channel;
    buffer[currentPtr++] = LPP_ANALOG_OUTPUT;
    buffer[currentPtr++] = val >> 8;
    buffer[currentPtr++] = val;

    return currentPtr;
}