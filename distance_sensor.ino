#include <Arduino.h>

#define TRIGGER_PIN 5
#define ECHO_PIN 6
#define MAX_DISTANCE 200
#define DEEP_SLEEP 5 * 60 * 1000000
//#define DEBUG
#define SERVO_PIN 11
#define UPPER_LIMIT 200
#define LOWER_LIMIT 90
#define UPPER_PING 400
#define STEP_SIZE 1

long testDistance();
void sleepNow();
int angle = 0;

void setup() {
  Serial.begin(115200);
  pinMode(SERVO_PIN, OUTPUT);

  // Lower the boom gate to start
  analogWrite(SERVO_PIN, angle = LOWER_LIMIT);
  Serial.println("Reset");
}

void loop() {
  long ping = testDistance();

  delay(50);

  if(UPPER_PING > ping){
    // Lower the boom gate
    while(angle < UPPER_LIMIT){
      analogWrite(SERVO_PIN, angle);
      angle += STEP_SIZE;
      delay(10);
    }

    while(testDistance() > UPPER_PING){
      delay(10);
    }
    
    delay(4000); // Wait for the car to drive out
    
  }else{
    // Raise the boom gate
    while(angle > LOWER_LIMIT){
      analogWrite(SERVO_PIN, angle);
      angle -= STEP_SIZE;
      delay(10);
    }
  }
  
#ifdef DEBUG
  Serial.print("Ping: ");
  Serial.print(ping);
  Serial.println("cm");

  Serial.print("Angle: ");
  Serial.println(angle);
#endif
 
}

long testDistance(){
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(5);

  pinMode(ECHO_PIN, INPUT);
  long duration = pulseIn(ECHO_PIN, HIGH);

  return duration;
}




