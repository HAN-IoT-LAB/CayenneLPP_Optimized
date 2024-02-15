#include <CayenneLPP.hpp>

CayenneLPP::CayenneLPP(size_t size) : bufferSize(0) {
    buffer = new uint8_t[size];
}

CayenneLPP::~CayenneLPP() {
    delete[] buffer;
}

// uint8_t CayenneLPP::getSize(void) const {
//     return static_cast<uint8_t>(buffer.size());
// }

// const uint8_t* CayenneLPP::getBuffer(void) const {
//     return buffer.data();
// }

// void CayenneLPP::reset(void) {
//     buffer.clear();
// }

// bool CayenneLPP::ensureCapacity(size_t additionalSize) {
//     return (buffer.size() + additionalSize) <= maxBufferSize;
// }

// template<size_t Size>
// uint8_t CayenneLPP<Size>::addDigitalInput(uint8_t channel, uint8_t value)
// {
//     if ((bufferSize + LPP_DIGITAL_INPUT_SIZE) > Size)
//     {
//         return 0;
//     }
//     buffer[bufferSize++] = channel;
//     buffer[bufferSize++] = LPP_DIGITAL_INPUT;
//     buffer[bufferSize++] = value;

//     return bufferSize;
// }

// template<size_t Size>
// uint8_t CayenneLPP<Size>::addDigitalOutput(uint8_t channel, uint8_t value)
// {
//     if ((bufferSize + LPP_DIGITAL_OUTPUT_SIZE) > Size)
//     {
//         return 0;
//     }
//     buffer[bufferSize++] = channel;
//     buffer[bufferSize++] = LPP_DIGITAL_OUTPUT;
//     buffer[bufferSize++] = value;

//     return bufferSize;
// }

// template<size_t Size>
// uint8_t CayenneLPP<Size>::addAnalogInput(uint8_t channel, float value)
// {
//     if ((bufferSize + LPP_ANALOG_INPUT_SIZE) > Size)
//     {
//         return 0;
//     }

//     int16_t val = value * 100;
//     buffer[bufferSize++] = channel;
//     buffer[bufferSize++] = LPP_ANALOG_INPUT;
//     buffer[bufferSize++] = val >> 8;
//     buffer[bufferSize++] = val;

//     return bufferSize;
// }

// template<size_t Size>
// uint8_t CayenneLPP<Size>::addAnalogOutput(uint8_t channel, float value)
// {
//     if ((bufferSize + LPP_ANALOG_OUTPUT_SIZE) > Size)
//     {
//         return 0;
//     }
//     int16_t val = value * 100;
//     buffer[bufferSize++] = channel;
//     buffer[bufferSize++] = LPP_ANALOG_OUTPUT;
//     buffer[bufferSize++] = val >> 8;
//     buffer[bufferSize++] = val;

//     return bufferSize;
// }