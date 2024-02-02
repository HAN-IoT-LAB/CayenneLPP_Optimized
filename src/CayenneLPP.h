#ifndef _CAYENNE_LPP_H_
#define _CAYENNE_LPP_H_

#include "LoRaWAN_constants.hpp"

class CayenneLPP {
    public:
        CayenneLPP(uint8_t size);
        ~CayenneLPP();
        
        void reset(void);
        uint8_t getSize(void);
        uint8_t* getBuffer(void);
        uint8_t copy(uint8_t* buffer);
    
    private:
        uint8_t *buffer;
        uint8_t maxsize;
        uint8_t cursor;
};

#endif