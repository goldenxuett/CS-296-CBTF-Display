#include <Queue.h>

int leds[] = {3, 5, 6, 9, 10};
int tones[] = {262, 294, 330, 349, 392};
int kMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int music_pin = 11;
int mseconds_in_day = 3000; // Change this value to adjust the length of a "day" (86400000 is default value)
Queue<int> melody_notes;
Queue<int> melody_delays;
Queue<int> melody_frequencies;
Queue<int*> cbtf_tests;
int* current_cbtf_test;
int number_days_left;
bool enabled;

void setup() {
  for (int i: leds) {
    pinMode(i, OUTPUT);
  }

  Serial.begin(9600);
  // Vivaldi Spring Rendition
  melody_delays.push(500); melody_notes.push(leds[0]); melody_frequencies.push(tones[0]);
  melody_delays.push(500); melody_notes.push(leds[2]); melody_frequencies.push(tones[2]);
  melody_delays.push(500); melody_notes.push(leds[2]); melody_frequencies.push(tones[2]);
  melody_delays.push(500); melody_notes.push(leds[2]); melody_frequencies.push(tones[2]);
  melody_delays.push(250); melody_notes.push(leds[1]); melody_frequencies.push(tones[1]);
  melody_delays.push(250); melody_notes.push(leds[0]); melody_frequencies.push(tones[0]);
  melody_delays.push(1500); melody_notes.push(leds[4]); melody_frequencies.push(tones[4]);
  melody_delays.push(250); melody_notes.push(leds[4]); melody_frequencies.push(tones[4]);
  melody_delays.push(250); melody_notes.push(leds[3]); melody_frequencies.push(tones[3]);
  melody_delays.push(500); melody_notes.push(leds[2]); melody_frequencies.push(tones[2]);
  melody_delays.push(500); melody_notes.push(leds[2]); melody_frequencies.push(tones[2]);
  melody_delays.push(500); melody_notes.push(leds[2]); melody_frequencies.push(tones[2]);
  melody_delays.push(250); melody_notes.push(leds[1]); melody_frequencies.push(tones[1]);
  melody_delays.push(250); melody_notes.push(leds[0]); melody_frequencies.push(tones[0]);
  melody_delays.push(1500); melody_notes.push(leds[4]); melody_frequencies.push(tones[4]);
  melody_delays.push(250); melody_notes.push(leds[4]); melody_frequencies.push(tones[4]);
  melody_delays.push(250); melody_notes.push(leds[3]); melody_frequencies.push(tones[3]);
  melody_delays.push(500); melody_notes.push(leds[2]); melody_frequencies.push(tones[2]);
  melody_delays.push(250); melody_notes.push(leds[3]); melody_frequencies.push(tones[3]);
  melody_delays.push(250); melody_notes.push(leds[4]); melody_frequencies.push(tones[4]);
  melody_delays.push(500); melody_notes.push(leds[3]); melody_frequencies.push(tones[3]);
  melody_delays.push(500); melody_notes.push(leds[2]); melody_frequencies.push(tones[2]);
  melody_delays.push(1000); melody_notes.push(leds[1]); melody_frequencies.push(tones[1]);
  melody_delays.lock(); melody_notes.lock(); melody_frequencies.lock();

  int first_test_date[3] = {ConvertDateToInteger(4, 23, 2020), ConvertDateToInteger(4, 29, 2020), ConvertDateToInteger(5, 6, 2020)};
//  int second_test_date[3] = {ConvertDateToInteger(4, 23, 2020), ConvertDateToInteger(4, 30, 2020), ConvertDateToInteger(5, 5, 2020)};
  cbtf_tests.push(first_test_date);
  current_cbtf_test = cbtf_tests.pop();
  enabled = true;
  number_days_left = current_cbtf_test[1] - (current_cbtf_test[0] + (millis() / (mseconds_in_day)));
}

void loop() {
  if (current_cbtf_test[2] - (current_cbtf_test[0] + (millis() / (mseconds_in_day))) == 0) {
    if (!cbtf_tests.isEmpty()) {
        current_cbtf_test = cbtf_tests.pop();
        for (int i: leds) {
        analogWrite(i, 0);
        }
    } else {
      enabled = false;
    }
  }
  number_days_left = current_cbtf_test[1] - (current_cbtf_test[0] + (millis() / (mseconds_in_day)));
  if (number_days_left == 0) {
    for (int i: leds) {
        analogWrite(i, 0);
    }
  }

  if (enabled && number_days_left <= 5) {
    if (number_days_left >= 1) {
      analogWrite(leds[number_days_left - 1], 255);
    } else {
      int current_note = melody_notes.pop();
      int current_delay = melody_delays.pop();
      tone(music_pin, melody_frequencies.pop(), current_delay);
      analogWrite(current_note, 255);
      delay(current_delay);
      analogWrite(current_note, 0);
      delay(100);
    }
  }
}

int ConvertDateToInteger(int month, int day, int year) {
  return year * 365 + ConvertMonthsToDays(month) + day;
}

int ConvertMonthsToDays(int month) {
    int current_sum = 0;
    for (int i = 0; i < month - 1; i++) {   
        current_sum += kMonths[i];
    }

    return current_sum;
}
