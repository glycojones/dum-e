
#include <NewPing.h>
#include <NewTone.h>

// Motors control pins
const int left_positive = 6;
const int left_negative = 5;
const int right_positive = 10;
const int right_negative = 9;
const int buzzer = 13;

// Sonar control values
#define sonar_send A1
#define sonar_receive A0
#define max_distance 200

NewPing sonar(sonar_send, sonar_receive, max_distance);

void play_jinglebells();
void play_rampup (int times);
void move_front();
void move_back();
void turn_left();
void turn_right();
void rotate_right();
void rotate_left();
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
  turn_left();
  delay(1000);
  move_front();
  delay(5000);
  move_back();
  delay(5000);
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

void rotate_right () {
  digitalWrite (left_positive, HIGH);
  digitalWrite (left_negative, LOW);
  digitalWrite (right_positive, LOW);
  digitalWrite (right_negative, HIGH);
}

void rotate_left () {
  digitalWrite (left_positive, LOW);
  digitalWrite (left_negative, HIGH);
  digitalWrite (right_positive, HIGH);
  digitalWrite (right_negative, LOW);
}

void turn_right () {
  digitalWrite (left_positive, HIGH);
  digitalWrite (left_negative, LOW);
  digitalWrite (right_positive, LOW);
  digitalWrite (right_negative, LOW);
}

void turn_left () {
  digitalWrite (left_positive, LOW);
  digitalWrite (left_negative, LOW);
  digitalWrite (right_positive, HIGH);
  digitalWrite (right_negative, LOW);
}

void stop_car () {
  digitalWrite (left_positive, LOW);
  digitalWrite (left_negative, LOW);
  digitalWrite (right_positive, LOW);
  digitalWrite (right_negative, LOW);  
}

void play_note ( char note, int duration ) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int  tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      NewTone(buzzer, tones[i], duration);
    }
  }
}

void play_jinglebells() {

  int length = 26;
  char notes[] = "eeeeeeegcde fffffeeeeddedg";
  int  beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
  int  tempo = 300;
  
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      play_note(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
    delay(tempo / 2); 
  }
}


void play_rampup (int times)
{
  for (int i = 0; i < times; i++) {
    for (unsigned long freq = 125; freq <= 15000; freq += 10) { 
      NewTone(buzzer, freq); 
      delay(1);
    }
    delay(500); // need to test this value 
  }
}
