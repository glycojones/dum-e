
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
#define max_distance 800

NewPing sonar(sonar_send, sonar_receive, max_distance);

void play_jinglebells();
void play_rampup (int times);
void move_forward ();
void move_backward();
void turn_left();
void turn_right();
void rotate_right();
void rotate_left();
void stop_car();
void self_drive();

void setup() {
  // to be run just once
  pinMode (left_positive, OUTPUT);
  pinMode (left_negative, OUTPUT);
  pinMode (right_positive, OUTPUT);
  pinMode (right_negative, OUTPUT);
}

void loop() {
  self_drive();
}

void move_forward () {
  digitalWrite (left_positive, HIGH);
  digitalWrite (left_negative, LOW);
  digitalWrite (right_positive, HIGH);
  digitalWrite (right_negative, LOW);
}

void move_backward () {
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
  char names[] = { 'c', 'd', 'e', 'f', 'g' };
  int  tones[] = { 2100, 1870, 1670, 1580, 1400 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      NewTone(buzzer, tones[i], duration);
    }
  }
}

void play_jinglebells() {

  int  length = 26;
  char notes[] = "eeeeeeegcde fffffeeeeddedg";
  int  beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
  int  tempo = 200;
  
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      play_note(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
    delay((tempo * 2) * beats[i]); 
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


void self_drive () {
  move_forward();
  float distance = sonar.ping_cm ( );
  while ( distance == 0.0 )
    distance = sonar.ping_cm ( ); // we want a valid measurement

  if ( distance < 50.0 ) {
    turn_right();
    delay(500); // to be determined
    float new_distance = sonar.ping_cm ( );
    while ( new_distance == 0.0 )
      new_distance = sonar.ping_cm ( );
    if ( new_distance <= distance )
      turn_left();
    
    delay(300);
  }

  if ( distance < 5.0 ) {
    stop_car();
    play_rampup(3);
    play_jinglebells ();
  }
}
