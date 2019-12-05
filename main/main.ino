
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
void try_to_unstuck();
void self_drive();

void setup() {
  // to be run just once
  pinMode (left_positive, OUTPUT);
  pinMode (left_negative, OUTPUT);
  pinMode (right_positive, OUTPUT);
  pinMode (right_negative, OUTPUT);
  pinMode (buzzer, OUTPUT);
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
  int  tones[] = { 1047, 1175, 1319, 1397, 1568 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 5; i++) {
    if (names[i] == note) {
      NewTone(buzzer, tones[i]);
      delay(duration);
      noNewTone(buzzer);
    }
  }
}

void play_jinglebells() {

  int  length = 26;
  char notes[] = "eeeeeeegcde fffffeeeeddedg";
  int  beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
  int  tempo = 80;
  
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

void play_rampup (int speed = 1)
{
  if (speed < 1)
    speed = 1;
    
  for (unsigned long freq = 80; freq <= 6000; freq += 10 * speed) { 
    NewTone(buzzer, freq);
    delay(1); 
  }
  for (unsigned long freq = 4000; freq > 60; freq -= 15 * speed) { 
    NewTone(buzzer, freq);
    delay(1); 
  }
  noNewTone(buzzer);
}

void try_to_unstuck () {
  stop_car();
  play_rampup(3);
  move_backward();
  delay(300); // try different values
  rotate_right();
  delay(1000);
  move_forward();
}

void self_drive () {
  move_forward();
  float distance = sonar.ping_cm ( );
  while ( distance == 0.0 )
    distance = sonar.ping_cm ( ); // we want a valid measurement

  if ( distance < 50.0 ) {
    turn_right();
    delay(100); // to be determined
    float new_distance = sonar.ping_cm ( );
    while ( new_distance == 0.0 )
      new_distance = sonar.ping_cm ( );
    if ( new_distance <= distance )
      turn_left();
    
    while ( new_distance < distance ) {
      delay(10);
      new_distance = sonar.ping_cm();   
    
      if ( new_distance < 10.0 ) {
        try_to_unstuck();
    
        float final_distance = sonar.ping_cm ( );
        if ( final_distance < 5.0 ) {
          stop_car();
          play_rampup(1);
          play_jinglebells ();
          while (1); // End here
        }
      }
    }
  }
}
