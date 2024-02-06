#ifndef CAYENNE_LPP_HPP
#define CAYENNE_LPP_HPP

#define LPP_DIGITAL_INPUT               0   // 1 byte
#define LPP_DIGITAL_OUTPUT              1   // 1 byte
#define LPP_ANALOG_INPUT                2   // 2 bytes, 0.01 signed
#define LPP_ANALOG_OUTPUT               3   // 2 bytes, 0.01 signed

// Data ID + Data Type + Data Size
#define LPP_DIGITAL_INPUT_SIZE          3   // 1 byte
#define LPP_DIGITAL_OUTPUT_SIZE         3   // 1 byte
#define LPP_ANALOG_INPUT_SIZE           4   // 2 bytes, 0.01 signed
#define LPP_ANALOG_OUTPUT_SIZE          4   // 2 bytes, 0.01 signed

#include <stdint.h>

template <typename Size>
class CayenneLPP
{
public:
    CayenneLPP();
    ~CayenneLPP();

    void reset(void);
    uint8_t getSize(void);
    uint8_t *getBuffer(void);
    uint8_t copy(uint8_t *buffer);

    uint8_t addDigitalInput(uint8_t channel, uint8_t value);
    uint8_t addDigitalOutput(uint8_t channel, uint8_t value);

    uint8_t addAnalogInput(uint8_t channel, float value);
    uint8_t addAnalogOutput(uint8_t channel, float value);

private:
    uint8_t buffer[Size];
    uint8_t maxsize;
    uint8_t currentPtr;
};

#endif // CAYENNE_LPP_HPP