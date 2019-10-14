//Linear Actuator Segment
#include <EEPROM.h> //Include library for storing past servo position to carry value between turning Arduino on and off
#include <Servo.h>
#define LINEARACTUATORPIN 8
//#define LINEARACTUATORPIN_LEFT 9
#define interruptPin = 2

const int LINEARSTEP = 50;//step size in ms for servos
const int HYSTERESIS = 100;//delta to move up or down
const int SERVOMAX = 1800;
const int SERVOMIN = 1050;
const int FLEX_PIN1 = A0; // Pin connected to voltage divider output
const int FLEX_PIN2 = A1; //Pin connected to voltage divider output for second flex sensor
//const int FSR_PIN = A2; 

Servo LINEARACTUATOR;

int linearValue = SERVOMAX;
//float PAST_SERVO_POS = 0;

//Current Sensor Initializations

//int left_disconnected = 0;
int right_disconnected = 0;

//float servoPosition;
//float servoPosition_left;



void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);

//  linearValue = EEPROM.get(PAST_SERVO_POS,linearValue);  

//2000 extended, 1100 retracted
  LINEARACTUATOR.attach(LINEARACTUATORPIN, SERVOMIN, SERVOMAX); //(pin, min, max)
}

void loop() 
{
  ///Initialize Flex Sensor portion of code
  // Read the ADC
  int flexADC1 = analogRead(FLEX_PIN1); 
  int flexADC2 = analogRead(FLEX_PIN2);

//  if (right_disconnected == 0)
//  {
    if ((flexADC1 - flexADC2 > HYSTERESIS)&&(linearValue < SERVOMAX))
    {
     linearValue = linearValue + LINEARSTEP;
    }
    if ((flexADC2 - flexADC1 > HYSTERESIS)&&(linearValue > SERVOMIN))
    { 
      linearValue = linearValue - LINEARSTEP;
    }
      LINEARACTUATOR.writeMicroseconds(linearValue);

//  servoPosition = LINEARACTUATOR.read();
//  EEPROM.put(PAST_SERVO_POS,linearValue);

//  Serial.println(flexADC1);
//  Serial.println(flexADC2);
//  Serial.println("Right linear value: "+ String(linearValue));
//Serial.println(linearValue);

  delay(100);
  
}
