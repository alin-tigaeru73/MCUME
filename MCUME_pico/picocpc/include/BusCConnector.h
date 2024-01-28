#ifndef BUSCCONNECTOR_H
#define BUSCCONNECTOR_H

#include "pico.h"
#ifdef __cplusplus
extern "C" {
#endif
    void setBusInstance(struct Bus* bus);
    uint8_t getKeyLine(uint8_t line);
    void setKeyLineReleased(uint8_t line);

#ifdef __cplusplus
}
#endif

#endif //BUSCCONNECTOR_H
