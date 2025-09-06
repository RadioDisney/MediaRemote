#include <melody_player.h>
#include <melody_factory.h>
#include <BleKeyboard.h>
#include "HumanInterface.h"
#include "RD_Coroutine.h"
#include "GpioDefine.h"

#define SECOND_INTERVAL 1000
#define MINUTE_INTERVAL (60 * 1000)
#define POWER_OFF_TIMEOUT (10 * 60 * 1000) // 10 minutes

uint64_t secondTimer;
uint64_t minuteTimer;


const char melodyString[] = "intel:d=8,o=6,b=180:4g,p,c,e,c,4c7.";

MelodyPlayer player(BUZZER_PIN);
BleKeyboard bleKeyboard("RMT-NWS10B", "RD", 100);

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  pinMode(POWER_HOLD_PIN, OUTPUT);
  digitalWrite(POWER_HOLD_PIN, HIGH);

  Melody melody = MelodyFactory.loadRtttlString(melodyString);
  if (melody)
  {
    Serial.println("Done!");
    Serial.print("Playing ");
    Serial.print(melody.getTitle());
    Serial.print("... ");
    player.play(melody);
    Serial.println("Done!");
  }
  else
  {
    Serial.println("Error");
  }

  // 2000 is a frequency, it will be changed at the first play
  ledcAttachChannel(BUZZER_PIN, 1000, 8, 1);
  ledcWriteTone(BUZZER_PIN, 0);

  bleKeyboard.begin();
  humanInterface.begin();
}

void loop()
{
  humanInterface.loop();
  rd_coroutine.loop();

  if (millis() > secondTimer)
  {
    secondTimer += SECOND_INTERVAL;
    // Serial.println("Second timer");
  }

  if (millis() > minuteTimer)
  {
    minuteTimer += MINUTE_INTERVAL;
    // Serial.println("Minute timer");

    if ((millis() - humanInterface.GetLastInputTimeMs() > POWER_OFF_TIMEOUT))
    {
      digitalWrite(POWER_HOLD_PIN, LOW);
    }
  }
  
  delay(10);
}