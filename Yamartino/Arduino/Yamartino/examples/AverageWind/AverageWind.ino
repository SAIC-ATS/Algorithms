/**
 * AverageWind - Yamartino Library Demo
 * Copyright 2015, Andrew Bythell <abythell@ieee.org>
 */
 
#include "Yamartino.h"

Yamartino yamartino(60);

void setup() {
  Serial.begin(9600);
}

float getWindDirection() {
  /* TODO: read your sensor and return value in degrees */
  return 0;	
}

void loop() {
  float heading = getWindDirection();
  yamartino.add(heading);
  
  Serial.print("Current Wind Direction: ");
  Serial.println(heading);
  Serial.print("Average Wind Direction: ");
  Serial.println(yamartino.averageHeading());
  Serial.print("Standard Deviation: ");
  Serial.println(yamartino.standardDeviation());
  Serial.println("");
  
  delay(1000);
}
