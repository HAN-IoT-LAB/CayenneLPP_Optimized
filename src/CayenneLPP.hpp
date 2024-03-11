#ifndef CAYENNE_LPP_HPP
#define CAYENNE_LPP_HPP

#include <stdint.h>
#include <cassert>
#include "CayenneReferences.hpp"

#define BUFFER_MAX 0xFF

namespace PAYLOAD_ENCODER
{
  template <size_t MaxSize>
  class CayenneLPP
  {
  public:
    explicit CayenneLPP(uint8_t size) : operationalSize(size > MaxSize ? MaxSize : size)
    {
      buffer = new uint8_t[operationalSize]; // Dynamic Buffer Allocation.
      currentIndex = 0;                      // Initialize at construction.
    }

    ~CayenneLPP()
    {
      delete[] buffer; // Give the Allocated Memory back, to avoid leaks.
    };

    /* REQUIRED FUNCTIONS by ASSIGNMENT #1 */
    void reset()
    {
      currentIndex = 0; // Reset currentIndex when buffer is reset
    }

    size_t getSize(void) const
    {
      return currentIndex; // Returns the count of used bytes
    }

    /* @Brief Return buffer by returning the array pointer.
      Const return, to prevent caller of modifications (read-only).
    */
    const uint8_t *getBuffer(void)
    {
      return buffer;
    }

    uint8_t copy(uint8_t *destBuffer) const
    {
      assert(destBuffer != nullptr); // Check that destination is not null;
      if (!destBuffer)
      {
        return 0; // Safety check
      }
      std::copy(buffer, buffer + currentIndex, destBuffer);
      return static_cast<uint8_t>(currentIndex);
    }

    /* END of REQUIRED FUNCTIONS by ASSIGNMENT #1 */

    /* Additional Functionality */
    // 1) Add a Bit/Byte;
    void addWord_byte(const uint8_t byte);

    // 2) 16-bit word;
    void addWord_16b(const uint16_t word_16b);

    // 3) 32-bit word;
    void addWord_32b(const uint16_t word_16b);

    // 4) float word;
    void addFloat(const float word_decimal);
    /* END of Additional Functionality */

    template <typename T> uint8_t addField(uint8_t type, uint8_t channel, T value)
    {
      // Type definition
      uint8_t size = getDataTypeSize(type);
      uint32_t multiplier = getDataTypeMultiplier(type);
      bool isSigned = getDataTypeIsSigned(type);

      // check buffer overflow
      if ((currentIndex + size + 2) > MaxSize)
      {
        return LPP_ERROR_OVERFLOW;
      }

      // check sign
      bool sign = value < 0;
      if (sign)
        value = -value;

      // get value to store
      uint32_t v = value * multiplier;

      // format an uint32_t as if it was an int32_t
      if (isSigned & sign)
      {
        uint32_t mask = (1 << (size * 8)) - 1;
        v = v & mask;
        if (sign)
          v = mask - v + 1;
      }

      // header
      buffer[currentIndex++] = channel;
      buffer[currentIndex++] = type;

      // add bytes (MSB first)
      for (uint8_t i = 1; i <= size; i++)
      {
        buffer[currentIndex + size - i] = (v & 0xFF);
        v >>= 8;
      }

      // update & return currentIndex
      currentIndex += size;
      return currentIndex;
    }

    uint8_t addDigitalInput(uint8_t channel, uint32_t value)
    {
      return addField(DATA_TYPES::DIG_IN, channel, value);
    }

    uint8_t addDigitalOutput(uint8_t channel, uint32_t value)
    {
      return addField(DATA_TYPES::DIG_OUT, channel, value);
    }

    uint8_t addAnalogInput(uint8_t channel, float value)
    {
      return addField(DATA_TYPES::ANL_IN, channel, value);
    }

    uint8_t addAnalogOutput(uint8_t channel, float value)
    {
      return addField(DATA_TYPES::ANL_OUT, channel, value);
    }

    uint8_t addLuminosity(uint8_t channel, uint32_t value)
    {
      return addField(DATA_TYPES::ILLUM_SENS, channel, value);
    }

    uint8_t addPresence(uint8_t channel, uint32_t value)
    {
      return addField(DATA_TYPES::PRSNC_SENS, channel, value);
    }

    uint8_t addTemperature(uint8_t channel, float value)
    {
      return addField(DATA_TYPES::EMP_SENS, channel, value);
    }

    uint8_t addRelativeHumidity(uint8_t channel, float value)
    {
      return addField(DATA_TYPES::HUM_SENS, channel, value);
    }

    uint8_t addBarometricPressure(uint8_t channel, float value)
    {
      return addField(DATA_TYPES::BARO_SENS, channel, value);
    }

    uint8_t addAccelerometer(uint8_t channel, float x, float y, float z)
    {

      // check buffer overflow
      if ((currentIndex + DATA_TYPES_SIZES::ACCRM_SENS + 2) > MaxSize)
      {
        return ERROR_TYPES::LPP_ERROR_OVERFLOW;
      }

      int16_t vx = x * DATA_TYPES_MULTIPLIER::ACCRM_SENS;
      int16_t vy = y * DATA_TYPES_MULTIPLIER::ACCRM_SENS;
      int16_t vz = z * DATA_TYPES_MULTIPLIER::ACCRM_SENS;

      buffer[currentIndex++] = channel;
      buffer[currentIndex++] = DATA_TYPES::ACCRM_SENS;
      buffer[currentIndex++] = vx >> 8;
      buffer[currentIndex++] = vx;
      buffer[currentIndex++] = vy >> 8;
      buffer[currentIndex++] = vy;
      buffer[currentIndex++] = vz >> 8;
      buffer[currentIndex++] = vz;

      return currentIndex;
    }

    uint8_t addGyrometer(uint8_t channel, float x, float y, float z)
    {

      // check buffer overflow
      if ((currentIndex + DATA_TYPES_SIZES::GYRO_SENS + 2) > MaxSize)
      {
        return ERROR_TYPES::LPP_ERROR_OVERFLOW;
      }

      int16_t vx = x * DATA_TYPES_MULTIPLIER::GYRO_SENS;
      int16_t vy = y * DATA_TYPES_MULTIPLIER::GYRO_SENS;
      int16_t vz = z * DATA_TYPES_MULTIPLIER::GYRO_SENS;

      buffer[currentIndex++] = channel;
      buffer[currentIndex++] = DATA_TYPES::GYRO_SENS;
      buffer[currentIndex++] = vx >> 8;
      buffer[currentIndex++] = vx;
      buffer[currentIndex++] = vy >> 8;
      buffer[currentIndex++] = vy;
      buffer[currentIndex++] = vz >> 8;
      buffer[currentIndex++] = vz;

      return currentIndex;
    }

    uint8_t addGPS(uint8_t channel, float latitude, float longitude, float altitude)
    {

      // check buffer overflow
      if ((currentIndex + DATA_TYPES_SIZES::GPS_LOC + 2) > MaxSize)
      {
        return ERROR_TYPES::LPP_ERROR_OVERFLOW;
      }

      int32_t lat = latitude * DATA_TYPES_MULTIPLIER::GPS_LAT;
      int32_t lon = longitude * DATA_TYPES_MULTIPLIER::GPS_LON;
      int32_t alt = altitude * DATA_TYPES_MULTIPLIER::GPS_ALT;

      buffer[currentIndex++] = channel;
      buffer[currentIndex++] = DATA_TYPES::GPS_LOC;
      buffer[currentIndex++] = lat >> 16;
      buffer[currentIndex++] = lat >> 8;
      buffer[currentIndex++] = lat;
      buffer[currentIndex++] = lon >> 16;
      buffer[currentIndex++] = lon >> 8;
      buffer[currentIndex++] = lon;
      buffer[currentIndex++] = alt >> 16;
      buffer[currentIndex++] = alt >> 8;
      buffer[currentIndex++] = alt;

      return currentIndex;
    }

  private:
    uint8_t *buffer;
    size_t operationalSize;
    static inline size_t currentIndex = 0;
  }; // End of class CayenneLPP.
} // End of Namespace PAYLOAD_ENCODER.
#endif // CAYENNE_LPP_HPP