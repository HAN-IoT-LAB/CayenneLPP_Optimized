#ifndef CAYENNE_REFERENCES_HPP
#define CAYENNE_REFERENCES_HPP

#include <stdint.h>
#include <unordered_map>

namespace PAYLOAD_ENCODER
{
    enum class DATA_TYPES : uint8_t {
        DIG_IN                  = 0,        /* DIGITAL INPUT */      
        DIG_OUT                 = 1,        /* DITIAL OUTPUT */
        ANL_IN                  = 2,        /* ANALOG INPUT */
        ANL_OUT                 = 3,        /* ANALOG OUTPUT */
        ILLUM_SENS              = 101,      /* ILLUMINATION SENSOR */
        PRSNC_SENS              = 102,      /* PRESCENCE SENSOR */
        TEMP_SENS               = 103,      /* TEMPERATURE SENSOR */
        HUM_SENS                = 104,      /* HUMIDITY SENSOR */
        ACCRM_SENS              = 113,      /* ACCELEROMETER */
        BARO_SENS               = 115,      /* BAROMETER */
        GYRO_SENS               = 134,      /* GYROMETER */
        GPS_LOC                 = 136       /* GPS LOCATION METER */      
    };

    enum class DATA_TYPES_SIZES : size_t {
        DIG_IN                  = 1,        /* 1 bit resolution */
        DIG_OUT                 = 1,        /* 1 bit resolution */
        ANL_IN                  = 2,        /* 0.01 Signed */
        ANL_OUT                 = 2,        /* 0.01 Signed */
        ILLUM_SENS              = 2,        /* 1 Lux Unsigned MSB */
        PRSNC_SENS              = 1,        /* 1 bit resolution */
        TEMP_SENS               = 2,        /* 0.1 °C Signed MSB */
        HUM_SENS                = 1,        /* 0.5 % Unsigned */
        ACCRM_SENS              = 6,        /* 0.001 G Signed MSB per axis */
        BARO_SENS               = 2,        /* 0.1 hPa Unsigned MSB */
        GYRO_SENS               = 6,        /* 0.01 °/s Signed MSB per axis */
        GPS_LOC                 = 9         /* Latitude  : 0.0001° Signed MSB 
                                     * Longitude : 0.0001° Signed MSB 
                                     * Altitude  : 0.01 meter Signed MSB */   
    };

    enum class DATA_TYPES_MULTIPLIER : uint32_t {
        DIG_IN                  = 1,        /* 1 bit resolution */
        DIG_OUT                 = 1,        /* 1 bit resolution */
        ANL_IN                  = 100,      /* 0.01 Signed */
        ANL_OUT                 = 100,      /* 0.01 Signed */
        ILLUM_SENS              = 1,        /* 1 Lux Unsigned MSB */
        PRSNC_SENS              = 1,        /* 1 bit resolution */
        TEMP_SENS               = 10,       /* 0.1 °C Signed MSB */
        HUM_SENS                = 2,        /* 0.5 % Unsigned */
        ACCRM_SENS              = 1000,     /* 0.001 G Signed MSB per axis */
        BARO_SENS               = 10,       /* 0.1 hPa Unsigned MSB */
        GYRO_SENS               = 100,      /* 0.01 °/s Signed MSB per axis */
        GPS_LAT                 = 10000,    /* Latitude  : 0.0001° Signed MSB */ 
        GPS_LON                 = 10000,    /* Longitude : 0.0001° Signed MSB */
        GPS_ALT                 = 100       /* Altitude  : 0.01 meter Signed MSB */                            
    };

    enum class DATA_TYPES_IS_SIGNED : bool {
        DIG_IN                  = 0,    /* 1 bit resolution */
        DIG_OUT                 = 0,    /* 1 bit resolution */
        ANL_IN                  = 1,    /* 0.01 Signed */
        ANL_OUT                 = 1,    /* 0.01 Signed */
        ILLUM_SENS              = 0,    /* 1 Lux Unsigned MSB */
        PRSNC_SENS              = 0,    /* 1 bit resolution */
        TEMP_SENS               = 1,    /* 0.1 °C Signed MSB */
        HUM_SENS                = 0,    /* 0.5 % Unsigned */
        ACCRM_SENS              = 1,    /* 0.001 G Signed MSB per axis */
        BARO_SENS               = 0,    /* 0.1 hPa Unsigned MSB */
        GYRO_SENS               = 1,    /* 0.01 °/s Signed MSB per axis */
        GPS_LOC                 = 1     /* Latitude  : 0.0001° Signed MSB 
                                        * Longitude : 0.0001° Signed MSB 
                                        * Altitude  : 0.01 meter Signed MSB */   
    };

    enum class ERROR_TYPES : int {
        LPP_ERROR_OK            = 0,
        LPP_ERROR_OVERFLOW      = 1,
        LPP_ERROR_UNKOWN_TYPE   = 2
    };

    // Function to create a mapping between data types reference and respective size in bytes;
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

    // Function to create a mapping between data types reference and respective size in bytes;
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

    // Function to create a mapping between data types reference and respective size in bytes;
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