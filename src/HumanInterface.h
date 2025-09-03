#ifndef __HUMAN_INTERFACE_H__
#define __HUMAN_INTERFACE_H__

#include <Arduino.h>
#include <map>
#include "HumanInterfaceIOButton.h"

#define DOWN_BUTTON_PIN 35
#define M5_BUTTON_PIN 37
#define UP_BUTTON_PIN 39

class HumanInterface
{
private:
    bool enabled_ = true;

public:    
    std::map<int16_t, HumanInterfaceIOButton> ioButtons = 
    {
        {DOWN_BUTTON_PIN, HumanInterfaceIOButton(DOWN_BUTTON_PIN)},
        {M5_BUTTON_PIN, HumanInterfaceIOButton(M5_BUTTON_PIN)},
        {UP_BUTTON_PIN, HumanInterfaceIOButton(UP_BUTTON_PIN)}
    };

    HumanInterface(/* args */);
    void begin();

    void loop();

    void SetEnable(bool enable);

    ~HumanInterface();
};

extern HumanInterface humanInterface;

#endif