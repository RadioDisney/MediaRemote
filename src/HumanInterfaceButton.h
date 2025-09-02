#ifndef __HUMAN_INTERFACE_BUTTON_H__
#define __HUMAN_INTERFACE_BUTTON_H__

#include <Arduino.h>

enum ButtonState
{
  released,   // 释放常态
  press,      // 按下动作过程中
  pressed,    // 按下常态
  release,    // 释放动作过程中
  double_click, // 双击状态
};

class HumanInterfaceButton
{
protected:
    ButtonState buttonState_ = released;
    uint32_t pressTimeMs_ = 0;
    uint32_t releaseTimeMs_ = 0;
    virtual void loop() = 0;

    bool enabled_ = true;

public:
    HumanInterfaceButton();
    virtual~HumanInterfaceButton();

    virtual void SetEnable (bool enable);
    virtual bool GetEnable() { return enabled_; }
};

#endif