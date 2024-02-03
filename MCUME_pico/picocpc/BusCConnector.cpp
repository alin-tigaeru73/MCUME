#include "Bus.h"

#include "BusCConnector.h"

#ifdef __cplusplus
extern "C" {
#endif

    static Bus* bus_instance = NULL;

    void setBusInstance(Bus* bus) {
        if(bus_instance == NULL || bus_instance != bus)
            bus_instance = bus;
    }

    uint8_t getKeyLine(uint8_t line) {
        return bus_instance->getKeyLine(line);
    }

    void setKeyLineReleased(uint8_t line) {
        bus_instance->setKeyLineReleased(line);
    }

#ifdef __cplusplus
}
#endif
