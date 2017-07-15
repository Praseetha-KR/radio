#include <Wire.h>
#include <TEA5767.h>

const double freq = 91.9;
TEA5767 radio;

void setup() {
  Wire.begin();
  radio.init();
  radio.set_frequency(freq);
}

void loop() {}
