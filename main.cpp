#include <stdio.h>
#include <iostream>

#include "src/CayenneLPP.hpp"

int main() {    
    CayenneLPP<100> buf(15); // Max size is 128, but dynamically allocates only for 10 elements
    buf.add_digital_input(4,80);

    std::unique_ptr<uint8_t[]> copyBuf = std::make_unique<uint8_t[]>(buf.getSize());
    auto source = buf.getBuffer();
    std::copy(source, source + buf.getSize(), copyBuf.get());
    
    // Test whether we get the same values back.
    for (size_t i = 0; i < buf.getSize(); i++) {
        std::cout << static_cast<int>(copyBuf[i]) << std::endl;
    }
    
    // buf.addDigitalInput(4,80);
    // size_t sizeTest = buf.getSize();
    // std::cout << "Hello" << std::endl;
    // std::cout << sizeTest << std::endl;
    return 0;
}