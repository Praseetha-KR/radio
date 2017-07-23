#include <Wire.h>
#include <TEA5767.h>

const int BAUDRATE = 9600;
const char DELIMITER = '\n';
const char READY_SYMBOL = 'R';

const double DEFAULT_FREQUENCY = 91.1;
const char DUMMY_CHAR = '-';
const int BUFFER_SIZE = 5;

TEA5767 radio;
double freq;
char buf[BUFFER_SIZE];

void resetBuf() {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    buf[i] = DUMMY_CHAR;
  }
}

void setup() {
  Serial.begin(BAUDRATE);
  radio.init();
  radio.set_frequency(DEFAULT_FREQUENCY);
  resetBuf();
  Serial.write(READY_SYMBOL);
}

void loop() {
  if (Serial.readBytesUntil(DELIMITER, buf, BUFFER_SIZE) > 0) {
    freq = atof(buf);
    radio.set_frequency(freq);
    Serial.println(freq);
    Serial.write(READY_SYMBOL);
  }
  Serial.flush();
  resetBuf();
}
