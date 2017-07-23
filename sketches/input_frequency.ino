#include <Wire.h>
#include <TEA5767.h>

const double defaultFreq = 91.1;
const int dataRate = 9600;
const char dummyChar = '-';

TEA5767 radio;
double freq;

const int bSize = 5;
char buf[bSize];

void resetBuf() {
  for (int i = 0; i < bSize; i++) {
    buf[i] = dummyChar;
  }
}

void setup() {
  Serial.begin(dataRate);
  radio.init();
  radio.set_frequency(defaultFreq);
  resetBuf();
  Serial.write('R');
}

void loop() {
  if (Serial.readBytesUntil('\n', buf, bSize) > 0) {
    freq = atof(buf);
    radio.set_frequency(freq);
    Serial.println(freq);
    Serial.write('R');
  }
  Serial.flush();
  resetBuf();
}
