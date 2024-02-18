#ifndef CAYENNE_LPP_HPP
#define CAYENNE_LPP_HPP

#define LPP_DIGITAL_INPUT 0  // 1 byte
#define LPP_DIGITAL_OUTPUT 1 // 1 byte
#define LPP_ANALOG_INPUT 2   // 2 bytes, 0.01 signed
#define LPP_ANALOG_OUTPUT 3  // 2 bytes, 0.01 signed

// Data ID + Data Type + Data Size
#define LPP_DIGITAL_INPUT_SIZE 3  // 1 byte
#define LPP_DIGITAL_OUTPUT_SIZE 3 // 1 byte
#define LPP_ANALOG_INPUT_SIZE 4   // 2 bytes, 0.01 signed
#define LPP_ANALOG_OUTPUT_SIZE 4  // 2 bytes, 0.01 signed

#include <stdint.h>
#include <memory>   // for std::unique_ptrs;

#define BUFFER_MAX 0xFF

template <size_t MaxSize>
class CayenneLPP
{
public:
    explicit CayenneLPP(uint8_t size) : operationalSize(size > MaxSize ? MaxSize : size),
                                        buffer(std::make_unique<uint8_t[]>(operationalSize))
    {
        currentIndex = 0; // Initialize at construction
    }

    ~CayenneLPP() = default;

    /* REQUIRED FUNCTIONS by ASSIGNMENT #1 */
    void reset()
    {
        buffer = std::make_unique<uint8_t[]>(operationalSize);
        currentIndex = 0; // Reset currentIndex when buffer is reset
    }

    size_t getSize(void) const
    {
        return currentIndex; // Returns the count of used bytes
    }

    const uint8_t *getBuffer(void) const
    {
        return buffer.get();
    }

    uint8_t copy(uint8_t *destBuffer) const
    {
        if (!destBuffer) {
            return 0; // Safety check
        }
        std::copy(buffer.get(), buffer.get() + currentIndex, destBuffer);
        return static_cast<uint8_t>(currentIndex);
    }

    /* END of REQUIRED FUNCTIONS by ASSIGNMENT #1 */

    /* Additional Functionality */
    // 1) Add a Bit/Byte;
    void add_word_byte(const uint8_t byte);

    // 2) 16-bit word;
    void add_word_16b(const uint16_t word_16b);

    // 3) 32-bit word;
    void add_word_32b(const uint16_t word_16b);

    // 4) float word;
    void add_float(const float word_decimal);
    /* END of Additional Functionality */

    // To be Reviewed:
    // RK: Just fancy functions of add_wordX...
    uint8_t add_digital_input(uint8_t channel, uint8_t value)
    {
        if (currentIndex + LPP_DIGITAL_INPUT_SIZE > operationalSize)
        {
            // Handle error
            return 0;
        }
        buffer[currentIndex++] = channel;
        buffer[currentIndex++] = LPP_DIGITAL_INPUT;
        buffer[currentIndex++] = value;
        return currentIndex; // Success
    }

    uint8_t add_digital_output(uint8_t channel, uint8_t value)
    {
        if ((currentIndex + LPP_DIGITAL_OUTPUT_SIZE) > operationalSize)
        {
            return 0;
        }
        buffer[currentIndex++] = channel;
        buffer[currentIndex++] = LPP_DIGITAL_OUTPUT;
        buffer[currentIndex++] = value;

        return currentIndex;
    }

    uint8_t add_analog_input(uint8_t channel, float value)
    {
        if ((currentIndex + LPP_ANALOG_INPUT_SIZE) > operationalSize)
        {
            return 0;
        }

        int16_t val = value * 100;
        buffer[currentIndex++] = channel;
        buffer[currentIndex++] = LPP_ANALOG_INPUT;
        buffer[currentIndex++] = val >> 8;
        buffer[currentIndex++] = val;

        return currentIndex;
    }

    uint8_t add_analog_output(uint8_t channel, float value)
    {
        if ((currentIndex + LPP_ANALOG_OUTPUT_SIZE) > operationalSize)
        {
            return 0;
        }
        int16_t val = value * 100;
        buffer[currentIndex++] = channel;
        buffer[currentIndex++] = LPP_ANALOG_OUTPUT;
        buffer[currentIndex++] = val >> 8;
        buffer[currentIndex++] = val;

        return currentIndex;
    }

private:
    std::unique_ptr<uint8_t[]> buffer; // Smart Pointer as buffer.
    size_t operationalSize;
    static inline size_t currentIndex = 0;
};

#endif // CAYENNE_LPP_HPP