#include <stdio.h>
#include <iostream>

#include "src/CayenneLPP.hpp"
#include "src/CayenneReferences.hpp"

int main() {    
    PAYLOAD_ENCODER::CayenneLPP<100> payload(15); // Max size is 128, but dynamically allocates only for 10 elements
    payload.addDigitalInput(4,80);
    payload.addDigitalOutput(5,15);

    const uint8_t* copyBuf = payload.getBuffer();
    
    // Test whether we get the same values back.
    for (size_t i = 0; i < payload.getSize(); i++) {
        std::cout << static_cast<int>(copyBuf[i]) << std::endl;
    }
    return 0;
}