const int In1 = 8;
const int In2 = 7;
const int In3 = 6;
const int In4 = 5;
const int trigPin = 3;
const int echoPin = 2;
int frequency = 0;

#include <SPI.h>      //include the SPI bus library
#include <MFRC522.h>  //include the RFID reader library

#define SS_PIN 10  //Peripheral select pin
#define RST_PIN 9  //reset pin
#define S0 A0

#define S1 A1
#define S2 A2
#define S3 A3
#define sensorOut A4
#define OE A5

void setup()
{
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void goStraight()   //run both motors in the same direction

{

  // turn on motors

  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);



  delay(1000);

  // now turn off motors

  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW); 
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);   

  delay(1000);
  // now Turns the robot Left

  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  
  // now Turns the robot Rigjht
  delay(1000);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW); 
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  // now turn off motors

  delay(1000);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW); 

}

void loop()

{
  //goStraight();
  delay(100);
  SenseColour();
  //ReadCard();
}
