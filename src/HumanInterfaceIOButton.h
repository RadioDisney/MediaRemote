#ifndef __HUMAN_INTERFACE_IO_BUTTON_H__
#define __HUMAN_INTERFACE_IO_BUTTON_H__

#include <Arduino.h>
#include "HumanInterfaceButton.h"

class HumanInterfaceIOButton : public HumanInterfaceButton
{
private:
    int16_t pin_;

protected:
    void loop() override;

friend class HumanInterface;

public:
    void (*OnButton)(int16_t pin, ButtonState state, uint32_t durationMs) = nullptr;

    HumanInterfaceIOButton(int16_t pin);
    HumanInterfaceIOButton();
};

#endif  // __HUMAN_INTERFACE_IO_BUTTON_H__