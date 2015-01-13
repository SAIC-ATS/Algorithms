Yamartino Arduino Library
===
An Arduino Library that uses the [Yamartino
Method](http://en.wikipedia.org/wiki/Yamartino_method) to calculate
average wind direction and standard deviation.

General Usage
---
1. [Install](http://arduino.cc/en/Guide/Libraries) the Yamartino Library
2. Add the library to your sketch (Sketch -> Import Library).
3. Create a Yamartino object and define the numer of data points.
4. Periodically add wind direction headings to the data set.
5. Call averageHeading() or standardDeviation() to analyze the data.

Example
---
Add header:

	#include "Yamartino.h"

Instantiate.  Use 60 readings taken every second to obtain per-minute
averages:

	Yamartino yamartino(60);

In the main loop, read the heading once per second:

  float heading = getWindDirection(); /* user-define */
  yamartino.add(heading);
  delay(1000);  

Anytime you want an average, just use:

  float avg = yamartino.averageHeading());
  float std = yamartino.standardDeviation());

After installing the Yamartino Library (and restarting the Arduino IDE), see
File -> Examples -> Yamartino -> AverageWind for a complete example.
