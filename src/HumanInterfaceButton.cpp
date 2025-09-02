#include "HumanInterfaceButton.h"

HumanInterfaceButton::HumanInterfaceButton()
{
}

HumanInterfaceButton::~HumanInterfaceButton()
{
}

void HumanInterfaceButton::SetEnable(bool enable)
{
    buttonState_ = released;
    enabled_ = enable;
    releaseTimeMs_ = millis();
}