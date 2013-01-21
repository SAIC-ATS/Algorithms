/*==============================================================================
 
 Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ==============================================================================*/
 
// VALUES FROM THE COMPASS
// all the stats are calculated using this single pass method
// http://en.wikipedia.org/wiki/Yamartino_method
float compassHeadingDegrees = 0; // the compass heading in degrees
// history buffer
const int historyLength = 100; // change to set size of array
float historyCos[historyLength]; // we keep track of X and Y 
float historySin[historyLength];
// history buffer statistics
float compassAvg = 0;
float compassStd = 0;

void setup(){
  // fill the history buffer with zeros, or else you won't
  // know what is in there.  it could take the values from
  // the last time the program ran, which will restult in
  // potentially odd startup behavior.
  for(int i = 0; i < historyLength; i++) {
    historyCos[i] = 0;
    historySin[i] = 0;
  }
}  

void loop() {

  compassHeadingDegrees = readCompassHeading(); // get the compass reading as degrees
  addCompassReadingToHistoryBuffer(compassHeadingDegrees); // this will add the values to the buffer
  analyzeHistoryBuffer(); // this will calculate the current mean and standard 
  // we don't really need to calculate this every time, but we will for
  // debugging purposes. we really only need to caculate it when we know
  // that we can actually choose a track.  but for 
  // the moment, we should just leave it here to help debug.

  /////// DEBUGGING // REMOVE WHEN ANNOYING OR WHEN MP3 IS HOOKED UP
  Serial.print("CURRENT HEADING = ");
  Serial.print(compassHeadingDegrees);
  Serial.print(" AVG = ");
  Serial.print(degrees(compassAvg));
  Serial.print(" STDEV = ");
  Serial.println(degrees(compassStd));
  /////// DEBUGGING // REMOVE WHEN ANNOYING OR WHEN MP3 IS HOOKED UP

  delay(25); // you'll need some delay in there to keep sane.  maybe more, maybe less
}

float addCompassReadingToHistoryBuffer(float valueDegrees) {
  float valueRadians = radians(valueDegrees); // convert to radians to use w/ sin/cos

  // move everyone value to the right by iterating through
  // the array starting at the second item and placing  
  // the last (i-1) value in the current position
  // the new value takes the 0th position.
  // we must keep the SIN and COS in order to calculate the
  // angular averages + stdevs correctly (see YAMARTINO METHOD)

  for (int i = historyLength - 1; i >= 0; i--) {
    if(i == 0) {
      historyCos[0] = cos(valueRadians); // put new val in the 0 position
      historySin[0] = sin(valueRadians); // put new val in the 0 position
    } 
    else {
      historyCos[i] = historyCos[i-1];
      historySin[i] = historySin[i-1];
    }
  } 
}

void analyzeHistoryBuffer() {

  float sumX = 0;
  float sumY = 0;

  for (int i = 0; i < historyLength; i++) {
    sumX += historyCos[i];
    sumY += historySin[i];
  }

  // calculate the average value in the history
  float t = atan2(sumY, sumX);
 
  compassAvg = t > 0 ? t : 2 * PI + t;

  // calculate the standard deviation
  float avgX = sumX / historyLength;
  float avgY = sumY / historyLength;

  //  METHOD FOR STANDARD DEVIATION!!
  // http://en.wikipedia.org/wiki/Yamartino_method
  float eps = sqrt(1 - (avgX*avgX + avgY*avgY));
  eps = isnan(eps) ? 0 : eps; // correct for NANs

   compassStd = asin(eps)* (1 + (2 / sqrt(3) - 1) * (eps * eps * eps));
}

float readCompassHeading() {
  return compassHeadingDegrees + random(-20,20); // a random walk ... your sensor reading code should be in here
}






