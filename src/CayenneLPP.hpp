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
  /**
   * @brief Template class for CayenneLPP payload encoder.
   * 
   * @tparam MaxSize Maximum size of the buffer.
   */
  public:
  /**
     * @brief Constructor for CayenneLPP.
     * 
     * @param size Size of the buffer.
     */
    explicit CayenneLPP(uint8_t size) : operationalSize(size > MaxSize ? MaxSize : size)
    {
      buffer = new uint8_t[operationalSize]; // Dynamic Buffer Allocation.
      currentIndex = 0;                      // Initialize at construction.
    }

    /**
     * @brief Destructor for CayenneLPP.
     */
    ~CayenneLPP()
    {
      delete[] buffer; // Give the Allocated Memory back, to avoid leaks.
    };

    /**
     * @brief Resets the buffer.
     */    
    void reset()
    {
      currentIndex = 0; // Reset currentIndex when buffer is reset
    }

    /**
     * @brief Gets the size of the buffer.
     * 
     * @return size_t Size of the buffer.
     */
    size_t getSize(void) const
    {
      return currentIndex; // Returns the count of used bytes
    }

    /**
     * @brief Returns the buffer.
     * 
     * @return const uint8_t* Pointer to the buffer.
     */
    const uint8_t *getBuffer(void)
    {
      return buffer;
    }

    /**
     * @brief Copies the buffer to the destination buffer.
     * 
     * @param destBuffer Destination buffer.
     * @return uint8_t Number of bytes copied.
     */
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

    /**
     * @brief Adds a field to the buffer.
     * 
     * @tparam T Data type of the field.
     * @param type Type of the field.
     * @param channel Channel of the field.
     * @param value Value of the field.
     * @return uint8_t New currentIndex.
     */
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

    /**
     * @brief Adds digital input field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param value Value of the field.
     * @return uint8_t New currentIndex.
     */
    uint8_t addDigitalInput(uint8_t channel, uint32_t value)
    {
      return addField(DATA_TYPES::DIG_IN, channel, value);
    }

    /**
     * @brief Adds digital output field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param value Value of the field.
     * @return uint8_t New currentIndex.
     */
    uint8_t addDigitalOutput(uint8_t channel, uint32_t value)
    {
      return addField(DATA_TYPES::DIG_OUT, channel, value);
    }

    /**
     * @brief Adds analog input field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param value Value of the field.
     * @return uint8_t New currentIndex.
     */
    uint8_t addAnalogInput(uint8_t channel, float value)
    {
      return addField(DATA_TYPES::ANL_IN, channel, value);
    }

    /**
     * @brief Adds analog output field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param value Value of the field.
     * @return uint8_t New currentIndex.
     */
    uint8_t addAnalogOutput(uint8_t channel, float value)
    {
      return addField(DATA_TYPES::ANL_OUT, channel, value);
    }

    /**
     * @brief Adds luminosity field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param value Value of the field.
     * @return uint8_t New currentIndex.
     */
    uint8_t addLuminosity(uint8_t channel, uint32_t value)
    {
      return addField(DATA_TYPES::ILLUM_SENS, channel, value);
    }

    /**
     * @brief Adds presence field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param value Value of the field.
     * @return uint8_t New currentIndex.
     */
    uint8_t addPresence(uint8_t channel, uint32_t value)
    {
      return addField(DATA_TYPES::PRSNC_SENS, channel, value);
    }

    /**
     * @brief Adds temperature field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param value Value of the field.
     * @return uint8_t New currentIndex.
     */
    uint8_t addTemperature(uint8_t channel, float value)
    {
      return addField(DATA_TYPES::EMP_SENS, channel, value);
    }

    /**
     * @brief Adds relative humidity field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param value Value of the field.
     * @return uint8_t New currentIndex.
     */
    uint8_t addRelativeHumidity(uint8_t channel, float value)
    {
      return addField(DATA_TYPES::HUM_SENS, channel, value);
    }

    /**
     * @brief Adds barometric pressure field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param value Value of the field.
     * @return uint8_t New currentIndex.
     */
    uint8_t addBarometricPressure(uint8_t channel, float value)
    {
      return addField(DATA_TYPES::BARO_SENS, channel, value);
    }

    /**
     * @brief Adds accelerometer field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param x X-axis value of the accelerometer.
     * @param y Y-axis value of the accelerometer.
     * @param z Z-axis value of the accelerometer.
     * @return uint8_t New currentIndex.
     */
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

    /**
     * @brief Adds gyrometer field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param x X-axis value of the gyrometer.
     * @param y Y-axis value of the gyrometer.
     * @param z Z-axis value of the gyrometer.
     * @return uint8_t New currentIndex.
     */
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

    /**
     * @brief Adds GPS location field to the buffer.
     * 
     * @param channel Channel of the field.
     * @param latitude Latitude value.
     * @param longitude Longitude value.
     * @param altitude Altitude value.
     * @return uint8_t New currentIndex.
     */
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