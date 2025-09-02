#ifndef __SERIAL_DEFINE_H__
#define __SERIAL_DEFINE_H__

#ifndef CONSOLE
#define CONSOLE Serial
#endif

#define CONSOLE_RATE 115200
// #define MIDI_PORT Serial1
#define MIDI_PORT midiSender
#define MIDI_RATE 57600
#define MIDI_INPUT_PIN 36
#define MIDI_OUTPUT_PIN 39
#define HUMAN_INTERFACE_PORT Serial2
#define HUMAN_INTERFACE_RATE 115200

#define USE_MIDI  1   // set to 1 to enable MIDI output, otherwise debug output

#if USE_MIDI // set up for direct MIDI serial output

#define DEBUG(s, x)
#define DEBUGX(s, x)
#define DEBUGS(s)

#else // don't use MIDI to allow printing debug statements

#define DEBUG(s, x)  do { Serial.print(F(s)); Serial.print(x); } while(false)
#define DEBUGX(s, x) do { Serial.print(F(s)); Serial.print(F("0x")); Serial.print(x, HEX); } while(false)
#define DEBUGS(s)    do { Serial.print(F(s)); } while (false)

#endif

#ifndef CONSOLE_PRINTF
#define CONSOLE_PRINTF(format, ...) if ((CONSOLE != NULL) && (CONSOLE.availableForWrite() > 64)) CONSOLE.printf(ARDUHAL_LOG_FORMAT(V, format), ##__VA_ARGS__)
// #define CONSOLE_PRINTF(format, ...)  do { } while (false)
#endif  // CONSOLE_PRINTF

#endif          // __SERIAL_DEFINE_H__