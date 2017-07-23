#include <Wire.h>
#include <TEA5767.h>

const int BAUDRATE = 9600;
const char DELIMITER = '\n';
const char READY_SYMBOL = 'R';

const double defaultFreq = 91.1;
const char dummyChar = '-';
const int bufSize = 5;

TEA5767 radio;
double freq;
char buf[bufSize];

void resetBuf() {
  for (int i = 0; i < bufSize; i++) {
    buf[i] = dummyChar;
  }
}

void setup() {
  Serial.begin(BAUDRATE);
  radio.init();
  radio.set_frequency(defaultFreq);
  resetBuf();
  Serial.write(READY_SYMBOL);
}

void loop() {
  if (Serial.readBytesUntil(DELIMITER, buf, bufSize) > 0) {
    freq = atof(buf);
    radio.set_frequency(freq);
    Serial.println(freq);
    Serial.write(READY_SYMBOL);
  }
  Serial.flush();
  resetBuf();
}
