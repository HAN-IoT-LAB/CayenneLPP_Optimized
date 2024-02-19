#ifndef CAYENNE_REFERENCES_HPP
#define CAYENNE_REFERENCES_HPP

#include <stdint.h>
#include <unordered_map>

namespace PAYLOAD_ENCODER
{
    enum class DATA_TYPES : uint8_t {
        DIG_IN          = 0,        /* DIGITAL INPUT */      
        DIG_OUT         = 1,        /* DITIAL OUTPUT */
        ANL_IN          = 2,        /* ANALOG INPUT */
        ANL_OUT         = 3,        /* ANALOG OUTPUT */
        ILLUM_SENS      = 101,      /* ILLUMINATION SENSOR */
        PRSNC_SENS      = 102,      /* PRESCENCE SENSOR */
        TEMP_SENS       = 103,      /* TEMPERATURE SENSOR */
        HUM_SENS        = 104,      /* HUMIDITY SENSOR */
        ACCRM_SENS      = 113,      /* ACCELEROMETER */
        BARO_SENS       = 115,      /* BAROMETER */
        GYRO_SENS       = 134,      /* GYROMETER */
        GPS_LOC         = 136       /* GPS LOCATION METER */      
    };

    enum class DATA_TYPES_SIZES : uint8_t {
        DIG_IN          = 1,        /* 1 bit resolution */
        DIG_OUT         = 1,        /* 1 bit resolution */
        ANL_IN          = 2,        /* 0.01 Signed */
        ANL_OUT         = 2,        /* 0.01 Signed */
        ILLUM_SENS      = 2,        /* 1 Lux Unsigned MSB */
        PRSNC_SENS      = 1,        /* 1 bit resolution */
        TEMP_SENS       = 2,        /* 0.1 °C Signed MSB */
        HUM_SENS        = 1,        /* 0.5 % Unsigned */
        ACCRM_SENS      = 6,        /* 0.001 G Signed MSB per axis */
        BARO_SENS       = 2,        /* 0.1 hPa Unsigned MSB */
        GYRO_SENS       = 6,        /* 0.01 °/s Signed MSB per axis */
        GPS_LOC         = 9         /* Latitude  : 0.0001° Signed MSB 
                                     * Longitude : 0.0001° Signed MSB 
                                     * Altitude  : 0.01 meter Signed MSB */   
    };

    // Function to create a mapping between data types reference and respective size in bytes;
    std::unordered_map<DATA_TYPES, DATA_TYPES_SIZES> createDataTypeMap() {
        std::unordered_map<DATA_TYPES, DATA_TYPES_SIZES> dataTypeMap = {
            {DATA_TYPES::DIG_IN,        DATA_TYPES_SIZES::DIG_IN},
            {DATA_TYPES::DIG_OUT,       DATA_TYPES_SIZES::DIG_OUT},
            {DATA_TYPES::ANL_IN,        DATA_TYPES_SIZES::ANL_IN},
            {DATA_TYPES::ANL_OUT,       DATA_TYPES_SIZES::ANL_OUT},
            {DATA_TYPES::ILLUM_SENS,    DATA_TYPES_SIZES::ILLUM_SENS},
            {DATA_TYPES::PRSNC_SENS,    DATA_TYPES_SIZES::PRSNC_SENS},
            {DATA_TYPES::TEMP_SENS,     DATA_TYPES_SIZES::TEMP_SENS},
            {DATA_TYPES::HUM_SENS,      DATA_TYPES_SIZES::HUM_SENS},
            {DATA_TYPES::ACCRM_SENS,    DATA_TYPES_SIZES::ACCRM_SENS},
            {DATA_TYPES::BARO_SENS,     DATA_TYPES_SIZES::BARO_SENS},
            {DATA_TYPES::GYRO_SENS,     DATA_TYPES_SIZES::GYRO_SENS},
            {DATA_TYPES::GPS_LOC,       DATA_TYPES_SIZES::GPS_LOC}
        };
        return dataTypeMap;
    }
} // End of PAYLOAD_ENCODER Namespace.

#endif // End of CAYENNE_REFERENCES_HPP