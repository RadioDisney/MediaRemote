#include "SerialDefine.h"
#include "HumanInterface.h"
#include "HumanInterfaceIOButton.h"
#include "MediaController.h"

#include "esp_debug_helpers.h"


HumanInterface humanInterface;

HumanInterface::HumanInterface(/* args */)
{
}

void HumanInterface::begin()
{
    ioButtons[M5_BUTTON_PIN].OnButton = OnM5Button;
    ioButtons[UP_BUTTON_PIN].OnButton = OnUpButton;
    ioButtons[DOWN_BUTTON_PIN].OnButton = OnDownButton;
}

HumanInterface::~HumanInterface()
{
}

void HumanInterface::SetEnable(bool enable)
{
    enabled_ = enable;
    // DEBUG_LOG("HumanInterface::SetEnable(%d)\n", enable);

    for (std::map<int16_t, HumanInterfaceIOButton>::iterator it = ioButtons.begin();
         it != ioButtons.end(); ++it)
    {
        it->second.SetEnable(enable);
    }
}

uint64_t HumanInterface::GetLastInputTimeMs()
{
    uint64_t lastInputTimeMs = 0;

    for (std::map<int16_t, HumanInterfaceIOButton>::iterator it = ioButtons.begin();
         it != ioButtons.end(); ++it)
    {
        if (it->second.GetReleaseTimeMs() > lastInputTimeMs)
        {
            lastInputTimeMs = it->second.GetReleaseTimeMs();
        }
    }
    
    return lastInputTimeMs;
}

void HumanInterface::loop()
{
    for (std::map<int16_t, HumanInterfaceIOButton>::iterator it = ioButtons.begin();
            it != ioButtons.end(); ++it)
    {
        it->second.loop();
    }
}
