#ifndef __COROUTINE_H__
#define __COROUTINE_H__

#include <Arduino.h>
#include "HumanInterfaceIOButton.h"

#define BUTTON_ACTION_INTERVAL 300

void OnM5Button(int16_t pin, ButtonState state, uint32_t durationMs);
void OnUpButton(int16_t pin, ButtonState state, uint32_t durationMs);
void OnDownButton(int16_t pin, ButtonState state, uint32_t durationMs);

#endif  // __COROUTINE_H__