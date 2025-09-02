#include "MediaController.h"

#include <BleKeyboard.h>
#include "SerialDefine.h"
#include "RD_Coroutine.h"

extern BleKeyboard bleKeyboard;


void BleKeyboardWrite_KEY_MEDIA_PLAY_PAUSE(void * pData)
{
    if (bleKeyboard.isConnected())
        bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
}

void BleKeyboardWrite_KEY_MEDIA_NEXT_TRACK(void * pData)
{
    if (bleKeyboard.isConnected())
        bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
}

void BleKeyboardWrite_KEY_MEDIA_PREVIOUS_TRACK(void * pData)
{
    if (bleKeyboard.isConnected())
        bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
}

std::multimap<uint32_t, RD_Coroutine::Func_Arg>::iterator coroutinHandle = std::multimap<uint32_t, RD_Coroutine::Func_Arg>::iterator{};

void OnM5Button(int16_t pin, ButtonState state, uint32_t durationMs)
{
    static uint8_t actionCount = 0;
    switch (state)
    {
    case release:
    {
        // CONSOLE_PRINTF("durationMs : %u\n", durationMs);
        if (durationMs < BUTTON_ACTION_INTERVAL)
        {
            actionCount++;
        }
        else
        {
            actionCount = 0;
        }

        switch (actionCount)
        {
            case 2:
                {
                    rd_coroutine.Remove (coroutinHandle);
                    coroutinHandle = rd_coroutine.Add (BleKeyboardWrite_KEY_MEDIA_PLAY_PAUSE, nullptr, BUTTON_ACTION_INTERVAL * 2 + 20);
                }
                break;
            case 4:
                {
                    rd_coroutine.Remove (coroutinHandle);
                    coroutinHandle = rd_coroutine.Add (BleKeyboardWrite_KEY_MEDIA_NEXT_TRACK, nullptr, BUTTON_ACTION_INTERVAL * 2 + 20);
                }
                break;
            case 6:
                if (bleKeyboard.isConnected())
                {
                    rd_coroutine.Remove (coroutinHandle);
                    coroutinHandle = rd_coroutine.Add (BleKeyboardWrite_KEY_MEDIA_PREVIOUS_TRACK, nullptr, BUTTON_ACTION_INTERVAL * 2 + 20);
                }
                break;
            default:
                break;
        }
    }
    break;
    case press:
    {
        // CONSOLE_PRINTF("durationMs : %u\n", durationMs);
        if (durationMs < BUTTON_ACTION_INTERVAL)
        {
            actionCount++;
        }
        else
        {
            actionCount = 1;
        }
    }
    break;

    default:
        break;
    }
}



        // if (durationMs < 700) // durationMs < 700
        // {
        //     if (bleKeyboard.isConnected())
        //     {
        //         bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
        //     }
        // }