#include <Servo.h>
 
Servo servo1; 
Servo servo2;
Servo servo3;
Servo servo4;
 
const int button1 = 5; 
const int button2 = 6;
 
int button1deger = 0; 
boolean button2deger = false;
 
const int pot1 = A0; 
const int pot2 = A1; 
const int pot3 = A2;
const int pot4 = A3;
 
int pot1deger; 
int pot2deger;
int pot3deger;
int pot4deger;
int pot1aci;
int pot2aci;
int pot3aci;
int pot4aci;
 
int servo1Poskayit = 1; 
int servo2Poskayit = 1;
int servo3Poskayit = 1;
int servo4Poskayit = 1;
 
void setup() {
  servo1.attach(9); 
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(12);
   
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
 
  Serial.begin(9600);
}
 
void loop() {
  
  pot1deger = analogRead(pot1); 
  pot1aci = map(pot1deger,0,1023,0,180);
  pot2deger = analogRead(pot2); 
  pot2aci = map(pot2deger,0,1023,0,180);
  pot3deger = analogRead(pot3);
  pot3aci = map(pot3deger,0,1023,0,180);
  pot4deger = analogRead(pot4);
  pot4aci = map(pot4deger,0,1023,0,180);
   
  servo1.write(pot1aci); 
  servo2.write(pot2aci);
  servo3.write(pot3aci);
  servo4.write(pot4aci);
   
  if(digitalRead(button1) == HIGH){ 
    
        servo1Poskayit = pot1aci;
        servo2Poskayit = pot2aci;
        servo3Poskayit = pot3aci;
        servo4Poskayit = pot4aci;
        Serial.println("Pos Kayit");
        
    
  }
 
  if(digitalRead(button2) == HIGH){ 
     servo1.write(servo1Poskayit);
     servo2.write(servo2Poskayit);
     servo3.write(servo3Poskayit);
     servo4.write(servo4Poskayit);
     Serial.println("Potansiyometre acilari:");
     Serial.println(servo1Poskayit);
     Serial.println(servo2Poskayit);
     Serial.println(servo3Poskayit);
     Serial.println(servo4Poskayit);
     delay(1000);
      }
  
  delay(1000);
}
