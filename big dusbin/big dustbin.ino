#include<HCSR04.h>
#include<Servo.h>
UltraSonicDistanceSensor distanceSensor(13, 12);
Servo servo;
int ServoPin=9;
void setup() 
{
      servo.attach(ServoPin);
      Serial.begin(9600);
}

void loop() 
{
 float distance=distanceSensor.measureDistanceCm();
 Serial.println(distanceSensor.measureDistanceCm());
 if(distance<=40)
  { 
    servo.attach(ServoPin); 
    servo.write(180);
    delay(4000);
    servo.write(0);
    delay(1000);
    servo.detach();
    }
  }
