#include "CayenneLPP.h"

CayenneLPP::CayenneLPP(uint8_t size) : maxsize(size) {
    buffer = (uint8_t*) malloc(size);
    cursor = 0;
}

CayenneLPP::~CayenneLPP(void) {
    free(buffer);
}

void CayenneLPP::reset(void) {
    cursor = 0;
}

uint8_t CayenneLPP::getSize(void) {
    return cursor;
}

/* What's going-on here, why does this function have commented code? */
uint8_t* CayenneLPP::getBuffer(void) {
//    uint8_t[cursor] result;
//    memcpy(result, buffer, cursor);
//    return result;
    return buffer;
}

uint8_t CayenneLPP::copy(uint8_t* dst) {
    memcpy(dst, buffer, cursor);
    return cursor;
}