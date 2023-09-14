#include <Servo.h>
Servo servo1, servo2, servo3, servo4;
const int record = 5;
const int play = 6;
const int pot1 = A0;
const int pot2 = A1;
const int pot3 = A2;
const int pot4 = A3;
int pot1value, pot2value, pot3value, pot4value, pot1angle, pot2angle, pot3angle, pot4angle;
const int maxStep = 100;
const int numPotentiometers = 4;
int potArray[4]={pot1,pot2,pot3,pot4};
int recordStep[numPotentiometers][maxStep];
int potAngles[numPotentiometers][maxStep];
bool isRecording = false;
void setup() {
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(12);
  pinMode(record, INPUT);
  pinMode(play, INPUT);
  Serial.begin(9600);
}
void loop() {
  if (digitalRead(record) == HIGH) {
    isRecording = true;
    recordFunction();
  } else if (digitalRead(play) == HIGH) {
    isRecording = false;
    while (true) {
      playFunction();
    }
  } else if (!isRecording) {
    normalMovement();
  }
}
void normalMovement() {
  for (int i = 0; i < numPotentiometers; i++) {
    int potValue = analogRead(potArray[i]);
    int potAngle = map(potValue, 0, 1023, 0, 180);
    if (i == 0) {
      servo1.write(potAngle);
    } else if (i == 1) {
      servo2.write(potAngle);
    } else if (i == 2) {
      servo3.write(potAngle);
    } else if (i == 3) {
      servo4.write(potAngle);
    }
  }
}
void recordFunction() {
  reset();
  Serial.println("start record");
  for (int step = 0; step < maxStep; step++) {
    
    recordStep[0][step] = map(analogRead(potArray[0]), 0, 1023, 0, 180);
    recordStep[1][step] = map(analogRead(potArray[1]), 0, 1023, 0, 180);
    recordStep[2][step] = map(analogRead(potArray[2]), 0, 1023, 0, 180);
    recordStep[3][step] = map(analogRead(potArray[3]), 0, 1023, 0, 180);

    servo1.write(recordStep[0][step]);
    servo2.write(recordStep[1][step]);
    servo3.write(recordStep[2][step]);
    servo4.write(recordStep[3][step]);

    Serial.println(recordStep[0][step]);
    Serial.println(recordStep[1][step]);
    Serial.println(recordStep[2][step]);
    Serial.println(recordStep[3][step]);

    delay(100);
  }
  Serial.println("Recorded!");
}
void playFunction() {
  Serial.println("start play");
  for (int step = 0; step < maxStep; step++) {
  
    servo1.write(recordStep[0][step]);
    servo2.write(recordStep[1][step]);
    servo3.write(recordStep[2][step]);
    servo4.write(recordStep[3][step]);
  
    Serial.println(recordStep[0][step]);
    Serial.println(recordStep[1][step]);
    Serial.println(recordStep[2][step]);
    Serial.println(recordStep[3][step]);
    delay(100);
  }
  
  Serial.println("Playback complete!");
  delay(1000);
}
void reset() {
  for (int i = 0; i < numPotentiometers; i++) {
    for (int j = 0; j < maxStep; j++) {
      recordStep[i][j] = 0;
    }
  }
  delay(10);
}
