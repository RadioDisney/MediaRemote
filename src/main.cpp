#include <melody_player.h>
#include <melody_factory.h>
#include <BleKeyboard.h>
#include "HumanInterface.h"
#include "RD_Coroutine.h"

#define POWER_HOLD_PIN 4
#define BUZZER_PIN 2

const char melodyString[] = "intel:d=8,o=6,b=180:4g,p,c,e,c,4c7.";

MelodyPlayer player(BUZZER_PIN);
BleKeyboard bleKeyboard("MediaRemote", "RD", 100);

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  pinMode(POWER_HOLD_PIN, OUTPUT);
  digitalWrite(POWER_HOLD_PIN, HIGH);

  Melody melody = MelodyFactory.loadRtttlString(melodyString);
  if (melody) {
    Serial.println("Done!");
    Serial.print("Playing ");
    Serial.print(melody.getTitle());
    Serial.print("... ");
    player.play(melody);
    Serial.println("Done!");
  } else {
    Serial.println("Error");
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