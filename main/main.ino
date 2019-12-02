
//#include <NewPing.h>

// Motors control pins
const int left_positive = 6;
const int left_negative = 5;
const int right_positive = 10;
const int right_negative = 9;

// Sonar control pins
#define sonar_send A1;
#define sonar_receive A0;

const int buzzer = 13;

void play_warning();
void play_stop();
void move_front();
void move_back();
void turn_right();
void turn_left();
void stop_car();

void setup() {
  // to be run just once
  pinMode (left_positive, OUTPUT);
  pinMode (left_negative, OUTPUT);
  pinMode (right_positive, OUTPUT);
  pinMode (right_negative, OUTPUT);
}

void loop() {
  move_front();
  delay(5000);
  play_warning();
  turn_left();
  delay(1000);
  move_front();
  delay(5000);
  play_warning();
  move_back();
  delay(5000);
  play_stop();
  stop_car();
}

void move_front () {
  digitalWrite (left_positive, HIGH);
  digitalWrite (left_negative, LOW);
  digitalWrite (right_positive, HIGH);
  digitalWrite (right_negative, LOW);
}

void move_back() {
  digitalWrite (left_positive, LOW);
  digitalWrite (left_negative, HIGH);
  digitalWrite (right_positive, LOW);
  digitalWrite (right_negative, HIGH);
}

void turn_right () {
  digitalWrite (left_positive, HIGH);
  digitalWrite (left_negative, LOW);
  digitalWrite (right_positive, LOW);
  digitalWrite (right_negative, HIGH);
}

void turn_left () {
  digitalWrite (left_positive, LOW);
  digitalWrite (left_negative, HIGH);
  digitalWrite (right_positive, HIGH);
  digitalWrite (right_negative, LOW);
}

void stop_car () {
  digitalWrite (left_positive, LOW);
  digitalWrite (left_negative, LOW);
  digitalWrite (right_positive, LOW);
  digitalWrite (right_negative, LOW);  
}

void play_warning () {
  tone (buzzer, 1000);
  delay (500);
  noTone (buzzer);
  delay (500);
  tone (buzzer, 1000);
  delay (1500);
  noTone (buzzer);
}

void play_stop() {
  tone (buzzer, 4000);
  delay (400);
  noTone (buzzer);
  delay (400);
  tone (buzzer, 4000);
  delay (400);
  tone (buzzer, 4000);
  delay (400);
  noTone (buzzer);
  delay (400);
  tone (buzzer, 4000);
  delay (400);
  noTone (buzzer);
}
