#include <QTRSensors.h>
QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];
const int trigPin = 7;
const int echoPin = 6;
const int In1 = 9;
const int In2 = 8;


void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // All motor control pins are outputs
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);

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

  delay(2000);

  // now turn off motors
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);  
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
