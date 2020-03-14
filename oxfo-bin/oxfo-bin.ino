
#include <LiquidCrystal.h>
#include <HCSR04.h>
#include <Servo.h>

Servo myservo;

UltraSonicDistanceSensor distanceSensor(13, 12);  // Initialize sensor that uses digital pins 13 (trig)  and 12 (echo.
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(2,3,4,5,6,7);
 /* The circuit:
 * LCD RS pin to digital pin 2
 * LCD E pin to digital pin  3
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * 10K resistor: ends to  ground and VO of LCD
 *   LED K to ground 
 * LED A to 200 ohm  resistor and +5V
 * VSS to GND
 * VDD to +5V
 * 
 * */
int Pirsensor= 11;
int ServoPin = 9;
void setup() 
{
    myservo.attach(ServoPin); 
    Serial.begin(9600);
    lcd.begin(16, 4); // stsrting the communication with ARDUINO
    
    pinMode(10, OUTPUT); // for BUZZER  
    pinMode(11, INPUT); // for PIR sensor 
 }

void loop() 
{
  lcd.clear();
  lcd.setCursor(0,4);
  float distance= distanceSensor.measureDistanceCm();
  lcd.print("OXFO-BIN"); // Branding line oxford College Dustbin 
  float percent= (distance/18)*100;
  int Data = digitalRead(Pirsensor); //reading the data from the Pir sensor.
  if (Data == HIGH)  // checking the condition from the PIR
  {
    myservo.attach(ServoPin);
    delay(1);
    lcd.setCursor(1,3);
    myservo.write(0); 
    Serial.println("Throw Dust");
    lcd.setCursor(2,3);
    Serial.print("Rem= ");
    Serial.print(percent);
    Serial.println("%");
    lcd.setCursor(3,0); 
    Serial.println(",KEEP CITY CLEAN");
    delay(5000);
    digitalWrite( 10, HIGH);
    myservo.write(180);
    delay(1000);
    digitalWrite( 10, LOW); 
    myservo.detach();
  
  }
  else 
  { 
    myservo.attach(ServoPin);
    delay(1);
    myservo.write(180);
    lcd.setCursor(1,5);
    Serial.println ("USE ME");
    lcd.setCursor(2,3);
    Serial.print("Rem= ");
    Serial.print(percent);
    Serial.println("%");
    lcd.setCursor(3,0); 
    Serial.println("KEEP CITY CLEAN");
    delay(1000);
    myservo.detach();
    }
}
   