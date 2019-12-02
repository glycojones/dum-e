
//#include <NewPing.h>

// Motors control pins
const int left_positive = 6;
const int left_negative = 5;
const int right_positive = 10;
const int right_negative = 9;

// Sonar control pins
const int sonar_send = 2;
const int sonar_receive = 3;

const int buzzer = 13;

void setup() {
  // to be run just once
  pinMode (left_positive, OUTPUT);
  pinMode (left_negative, OUTPUT);
  pinMode (right_positive, OUTPUT);
  pinMode (right_negative, OUTPUT);

}

void loop() {
  digitalWrite (left_positive, HIGH);
  digitalWrite (left_negative, LOW);
  digitalWrite (right_positive, HIGH);
  digitalWrite (right_negative, LOW);
  noTone(buzzer);
  tone (buzzer, 1000);
  delay (1000);
  tone (buzzer, 2000);
  delay (1000);
  tone (buzzer, 2500);
  delay(1000);
  noTone (buzzer);
  delay (5000);
}
