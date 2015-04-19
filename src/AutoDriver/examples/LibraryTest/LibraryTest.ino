#include <AutoDriver.h>
#include "notes.h"

// Test sketch for the L6470 AutoDriver library. This program instantiates three
//  AutoDriver boards and uses them to play Jonathon Coulton's "Want You Gone" from
//  the Portal 2 soundtrack. In a more general sense, it adds support for playing
//  music with stepper motors. Not all notes can be played, of course- at too high
//  a steps/sec rate, the motors will slip and dogs and cats will live together.


// Create our AutoDriver instances. The parameters are pin numbers in
//  Arduino-speke for CS, reset, and busy.
AutoDriver boardA(10, 8);
AutoDriver boardB(14, 8);

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello world");
  dSPINConfig();
  pinMode(4, INPUT_PULLUP);
  
}

// loop() waits for a character- any character- and then plays the song.
void loop()
{
  if (digitalRead(4) == LOW)
  {
    Serial.read();
    Serial.println("Poop!");
    wantYouGone();
    Serial.println("Done pooping!");
  }
}


