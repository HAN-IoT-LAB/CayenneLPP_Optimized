#ifndef CAYENNE_REFERENCES_HPP
#define CAYENNE_REFERENCES_HPP

#include <stdint.h>
#include <unordered_map>

namespace PAYLOAD_ENCODER
{
    /**
     * @brief Enum class defining data types for Cayenne LPP.
     */
    enum class DATA_TYPES : uint8_t {
        DIG_IN                  = 0,    /**< 1 bit resolution */
        DIG_OUT                 = 1,    /**< 1 bit resolution */
        ANL_IN                  = 2,    /**< 0.01 Signed */
        ANL_OUT                 = 3,    /**< 0.01 Signed */
        ILLUM_SENS              = 101,  /**< 1 Lux Unsigned MSB */
        PRSNC_SENS              = 102,  /**< 1 bit resolution */
        TEMP_SENS               = 103,  /**< 0.1 °C Signed MSB */
        HUM_SENS                = 104,  /**< 0.5 % Unsigned */
        ACCRM_SENS              = 113,  /**< 0.001 G Signed MSB per axis */
        BARO_SENS               = 115,  /**< 0.1 hPa Unsigned MSB */
        GYRO_SENS               = 134,  /**< 0.01 °/s Signed MSB per axis */
        GPS_LOC                 = 136   /**< Latitude  : 0.0001° Signed MSB 
                                        * Longitude : 0.0001° Signed MSB 
                                        * Altitude  : 0.01 meter Signed MSB */   
    };

    /**
     * @brief Enum class defining sizes of data types for Cayenne LPP.
     */
    enum class DATA_TYPES_SIZES : size_t {
        DIG_IN                  = 1,   
        DIG_OUT                 = 1,  
        ANL_IN                  = 2,   
        ANL_OUT                 = 2, 
        ILLUM_SENS              = 2, 
        PRSNC_SENS              = 1,    
        TEMP_SENS               = 2,    
        HUM_SENS                = 1,    
        ACCRM_SENS              = 6,    
        BARO_SENS               = 2,    
        GYRO_SENS               = 6,    
        GPS_LOC                 = 9     
    };

    /**
     * @brief Enum class defining multipliers of data types for Cayenne LPP.
     */
    enum class DATA_TYPES_MULTIPLIER : uint32_t {
        DIG_IN                  = 1,    
        DIG_OUT                 = 1,    
        ANL_IN                  = 100,  
        ANL_OUT                 = 100,  
        ILLUM_SENS              = 1,    
        PRSNC_SENS              = 1,    
        TEMP_SENS               = 10,   
        HUM_SENS                = 2,  
        ACCRM_SENS              = 1000, 
        BARO_SENS               = 10,   
        GYRO_SENS               = 100,  
        GPS_LAT                 = 10000,
        GPS_LON                 = 10000,
        GPS_ALT                 = 100                       
    };

    /**
     * @brief Enum class defining whether data types are signed or not for Cayenne LPP.
     */
    enum class DATA_TYPES_IS_SIGNED : bool {
        DIG_IN                  = 0,    
        DIG_OUT                 = 0,    
        ANL_IN                  = 1,    
        ANL_OUT                 = 1,    
        ILLUM_SENS              = 0,    
        PRSNC_SENS              = 0,    
        TEMP_SENS               = 1,    
        HUM_SENS                = 0,    
        ACCRM_SENS              = 1,    
        BARO_SENS               = 0,    
        GYRO_SENS               = 1,    
        GPS_LOC                 = 1       
    };

    /**
     * @brief Enum class defining error types for Cayenne LPP.
     */
    enum class ERROR_TYPES : int {
        LPP_ERROR_OK            = 0,    /**< No error */
        LPP_ERROR_OVERFLOW      = 1,    /**< Buffer overflow */
        LPP_ERROR_UNKOWN_TYPE   = 2     /**< Unknown data type */
    };

    /**
     * @brief Function to get the size of a data type in bytes.
     * @param dataType The data type.
     * @return The size of the data type in bytes.
     */
    constexpr size_t getDataTypeSize(DATA_TYPES dataType) {
        switch (dataType) {
            case DATA_TYPES::DIG_IN:        return static_cast<size_t>(DATA_TYPES_SIZES::DIG_IN);
            case DATA_TYPES::DIG_OUT:       return static_cast<size_t>(DATA_TYPES_SIZES::DIG_OUT);
            case DATA_TYPES::ANL_IN:        return static_cast<size_t>(DATA_TYPES_SIZES::ANL_IN);
            case DATA_TYPES::ANL_OUT:       return static_cast<size_t>(DATA_TYPES_SIZES::ANL_OUT);
            case DATA_TYPES::ILLUM_SENS:    return static_cast<size_t>(DATA_TYPES_SIZES::ILLUM_SENS);
            case DATA_TYPES::PRSNC_SENS:    return static_cast<size_t>(DATA_TYPES_SIZES::PRSNC_SENS);
            case DATA_TYPES::TEMP_SENS:     return static_cast<size_t>(DATA_TYPES_SIZES::TEMP_SENS);
            case DATA_TYPES::HUM_SENS:      return static_cast<size_t>(DATA_TYPES_SIZES::HUM_SENS);
            case DATA_TYPES::ACCRM_SENS:    return static_cast<size_t>(DATA_TYPES_SIZES::ACCRM_SENS);
            case DATA_TYPES::BARO_SENS:     return static_cast<size_t>(DATA_TYPES_SIZES::BARO_SENS);
            case DATA_TYPES::GYRO_SENS:     return static_cast<size_t>(DATA_TYPES_SIZES::GYRO_SENS);
            case DATA_TYPES::GPS_LOC:       return static_cast<size_t>(DATA_TYPES_SIZES::GPS_LOC);
            default: return 0; // Or handle unknown data type appropriately
        }
    }   

    /**
     * @brief Function to get the multiplier of a data type.
     * @param dataType The data type.
     * @return The multiplier of the data type.
     */
    constexpr uint32_t getDataTypeMultiplier(DATA_TYPES dataType) {
        switch (dataType) {
            case DATA_TYPES::DIG_IN:        return static_cast<size_t>(DATA_TYPES_MULTIPLIER::DIG_IN);
            case DATA_TYPES::DIG_OUT:       return static_cast<size_t>(DATA_TYPES_MULTIPLIER::DIG_OUT);
            case DATA_TYPES::ANL_IN:        return static_cast<size_t>(DATA_TYPES_MULTIPLIER::ANL_IN);
            case DATA_TYPES::ANL_OUT:       return static_cast<size_t>(DATA_TYPES_MULTIPLIER::ANL_OUT);
            case DATA_TYPES::ILLUM_SENS:    return static_cast<size_t>(DATA_TYPES_MULTIPLIER::ILLUM_SENS);
            case DATA_TYPES::PRSNC_SENS:    return static_cast<size_t>(DATA_TYPES_MULTIPLIER::PRSNC_SENS);
            case DATA_TYPES::TEMP_SENS:     return static_cast<size_t>(DATA_TYPES_MULTIPLIER::TEMP_SENS);
            case DATA_TYPES::HUM_SENS:      return static_cast<size_t>(DATA_TYPES_MULTIPLIER::HUM_SENS);
            case DATA_TYPES::BARO_SENS:     return static_cast<size_t>(DATA_TYPES_MULTIPLIER::BARO_SENS);
            default: return 0; // Or handle unknown data type appropriately
        }
    }

    /**
     * @brief Function to check whether a data type is signed or not.
     * @param dataType The data type.
     * @return True if the data type is signed, false otherwise.
     */
    constexpr uint32_t getDataTypeIsSigned(DATA_TYPES dataType) {
        switch (dataType) {
            case DATA_TYPES::DIG_IN:        return static_cast<size_t>(DATA_TYPES_IS_SIGNED::DIG_IN);
            case DATA_TYPES::DIG_OUT:       return static_cast<size_t>(DATA_TYPES_IS_SIGNED::DIG_OUT);
            case DATA_TYPES::ANL_IN:        return static_cast<size_t>(DATA_TYPES_IS_SIGNED::ANL_IN);
            case DATA_TYPES::ANL_OUT:       return static_cast<size_t>(DATA_TYPES_IS_SIGNED::ANL_OUT);
            case DATA_TYPES::ILLUM_SENS:    return static_cast<size_t>(DATA_TYPES_IS_SIGNED::ILLUM_SENS);
            case DATA_TYPES::PRSNC_SENS:    return static_cast<size_t>(DATA_TYPES_IS_SIGNED::PRSNC_SENS);
            case DATA_TYPES::TEMP_SENS:     return static_cast<size_t>(DATA_TYPES_IS_SIGNED::TEMP_SENS);
            case DATA_TYPES::HUM_SENS:      return static_cast<size_t>(DATA_TYPES_IS_SIGNED::HUM_SENS);
            case DATA_TYPES::BARO_SENS:     return static_cast<size_t>(DATA_TYPES_IS_SIGNED::BARO_SENS);
            default: return 0; // Or handle unknown data type appropriately
        }
    }
} // End of PAYLOAD_ENCODER Namespace.

#endif // End of CAYENNE_REFERENCES_HPP
