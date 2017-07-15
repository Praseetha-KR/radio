/*
 * FM Receiver listening to list of predefined frequencies
 *
 * Entering character 'n' in serial monitor will loop through the channel list
 */

#include <Wire.h>
#include <TEA5767.h>

const double channelList[] = {
  /*
   * Bangalore FM Channels List
   * source: https://en.wikipedia.org/wiki/List_of_FM_radio_stations_in_Bangalore
   */
  91.1, // Radio City (Kannada)
  91.9, // Indigo (Englist)
  92.7, // Big FM (Kannada)
  93.5, // Red FM (Hindi)
  94.3, // Radio One (English)
  95, // Radio Mirchi (Hindi)
  98.3, // Radio Mirchi (Kannada)
  100.1, // Amrutavarshini (Classical music)
  101.3, // Rainbow FM (Kannada, English & Hindi)
  102.9, // Vividh Bharati (Kannada & Hindi)
  104, // Fever (Hindi)
  106.4 // Gyanvani (by IGNOU)
};
const int listLength = sizeof(channelList);
int currentIndex = 0;
int serialInput;
TEA5767 radio;

void setup() {
  Wire.begin();
  radio.init();
  radio.set_frequency(channelList[currentIndex]);
}

void loop() {
  if (Serial.available() > 0) {
    serialInput = Serial.read();
    if (serialInput == 'n') {
      if (currentIndex == listLength) {
        currentIndex = 0;
      }
      else {
        currentIndex += 1;
      }
      radio.set_frequency(channelList[currentIndex]);
    }
  }
}
