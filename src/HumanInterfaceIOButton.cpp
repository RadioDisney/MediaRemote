#include "HumanInterfaceIOButton.h"
#include "SerialDefine.h"

HumanInterfaceIOButton::HumanInterfaceIOButton(int16_t pin)
{
    pin_ = pin;
    pinMode(pin_, INPUT);
}

HumanInterfaceIOButton::HumanInterfaceIOButton()
{
}

void HumanInterfaceIOButton::loop()
{
  if (enabled_)
  {
    bool buttonValue = digitalRead(pin_);
    // Serial.printf("HumanInterfaceButton::loop pin_%u : %u\n", pin_, buttonValue);
    switch (buttonState_)
    {
      case released:
        {
          if (buttonValue == LOW)
          {
            buttonState_ = press;
          }
        }
        break;
      case press:
        {
          // CONSOLE_PRINTF("IOButtoon %u : press\n", pin_);
          if (buttonValue == LOW)
          {
            buttonState_ = pressed;
            if (OnButton != nullptr)
            {
              // CONSOLE_PRINTF("IOButtoon %u : press %p\n", pin_, OnButton);
              OnButton(pin_, press, millis() - releaseTimeMs_);
            }
            pressTimeMs_ = millis();
          }
          else
          {
            buttonState_ = released;
          }
        }
        break;
      case pressed:
        {
          if (OnButton != nullptr)
          {
            // CONSOLE_PRINTF("IOButtoon %u : pressed %p\n", pin_, OnButton);
            OnButton(pin_, pressed, millis() - pressTimeMs_);
          }
          if (buttonValue == HIGH)
          {
            buttonState_ = release;
          }
        }
        break;
      case release:
        {
          // CONSOLE_PRINTF("IOButtoon %u : release\n", pin_);
          if (buttonValue == HIGH)
          {
            buttonState_ = released;
            if (OnButton != nullptr)
            {
              // CONSOLE_PRINTF("IOButtoon %u : release %p\n", pin_, OnButton);
              OnButton(pin_, release, millis() - pressTimeMs_);
            }
            releaseTimeMs_ = millis();
          }
          else
          {
            buttonState_ = pressed;
          }
        }
        break;
    }
  }
}
