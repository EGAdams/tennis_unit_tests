#ifndef PININTERFACE_H
#define PININTERFACE_H

#include "IPinInterface.h"
#include "../PinState/PinState.h"
#include "../Arduino/Arduino.h"
#include <map>

class PinInterface : public IPinInterface {
  public:
    PinInterface( IPinState* pinState );
    virtual ~PinInterface();
    virtual void pinAnalogWrite(int pin, int value);
    virtual void pinDigitalWrite(int pin, int value);
    virtual int pinAnalogRead(int pin);
    virtual int pinDigitalRead(int pin);
    std::map<std::string, int> getPinStateMap();

  private:
    std::map<std::string, int> _pin_map;
    IPinState* _pinState; };
#endif