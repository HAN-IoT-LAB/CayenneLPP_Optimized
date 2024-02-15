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
#include <array>

#ifndef PAYLOAD_BUFFER_MAX_SIZE
#define PAYLOAD_BUFFER_MAX_SIZE 256
#endif

template<size_t Capacity>
class CayenneLPP {
public:
    explicit CayenneLPP();
    ~CayenneLPP();

    void reset(void);
    uint8_t getSize(void) const;
    const uint8_t* getBuffer(void) const;
    uint8_t copy(uint8_t *buffer) const;

    uint8_t addDigitalInput(uint8_t channel, uint8_t value);
    uint8_t addDigitalOutput(uint8_t channel, uint8_t value);
    uint8_t addAnalogInput(uint8_t channel, float value);
    uint8_t addAnalogOutput(uint8_t channel, float value);

private:
    static inline const size_t maxBufferSize = Capacity;
    static inline std::array<uint8_t, MAX_PAYLOAD_SIZE> buffer;
    static size_t currentIndex;
};

#endif // CAYENNE_LPP_HPP