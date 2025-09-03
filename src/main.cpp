#include <BleKeyboard.h>
#include "HumanInterface.h"
#include "RD_Coroutine.h"

#define POWER_HOLD_PIN 4
#define BUZZER_PIN 2

BleKeyboard bleKeyboard("MediaRemote", "RD", 100);

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  pinMode(POWER_HOLD_PIN, OUTPUT);
  digitalWrite(POWER_HOLD_PIN, HIGH);

  pinMode(BUZZER_PIN, OUTPUT);

  for (uint16_t i = 0; i < 200; i++)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1);
    digitalWrite(BUZZER_PIN, LOW);
    delay(1);
  }

  bleKeyboard.begin();
  humanInterface.begin();
}

void loop()
{
  humanInterface.loop();
  rd_coroutine.loop();
  
  delay(10);
}