#include <QTRSensors.h>
QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];
const int trigPin = 7;
const int echoPin = 6;
const int In1 = 9;
const int In2 = 8;
const int In3 = 10;
const int In4 = 11;

#define S0 A0
#define S1 A1
#define S2 A2
#define S3 A3
#define sensorOut A4
#define OE A5

int frequency = 0;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // All motor control pins are outputs
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
	
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(sensorOut, INPUT);
	
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  //digitalWrite(OE, LOW);

  Serial.begin(9600);
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){2, 3, 4, 5}, SensorCount);

  // initialize serial communication:
  Serial.begin(9600);
}
void goStraight()   //run both motors in the same direction
{
  // turn on motor A
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);

  delay(2000);

  // now turn off motors
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);  
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void loop()
{
  goStraight();
  delay(100);
  // Variables for duration of ping and the distance in cm
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  qtr.read(sensorValues);
    for (uint8_t i = 0; i < SensorCount; i++){

      Serial.print(sensorValues[i]);

      Serial.print('\t');

    }

    Serial.println();

    delay(250);

	
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimetres(duration);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();  
  delay(100);
}

long microsecondsToCentimetres(long microseconds)
{
  return microseconds / 29 / 2;
}
//Setting red filtered photodiodes to be read

digitalWrite(S2,LOW);
digitalWrite(S3,LOW);
// Reading the output frequency
frequency = pulseIn(sensorOut, LOW);

// Printing the value on the serial monitor

Serial.print("R= ");//printing name
Serial.print(frequency);//printing RED color frequency
Serial.print("  ");
delay(100);

// Setting Green filtered photodiodes to be read
digitalWrite(S2,HIGH);
digitalWrite(S3,HIGH);

// Reading the output frequency
frequency = pulseIn(sensorOut, LOW);

// Printing the value on the serial monitor
Serial.print("G= ");//printing name
Serial.print(frequency);//printing Green color frequency
Serial.print("  ");
delay(100);

// Setting Blue filtered photodiodes to be read
digitalWrite(S2,LOW);
digitalWrite(S3,HIGH);

// Reading the output frequency
frequency = pulseIn(sensorOut, LOW);

// Printing the value on the serial monitor
Serial.print("B= ");//printing name
Serial.print(frequency);//printing Blue color frequency
Serial.println("  ");
delay(1000);
