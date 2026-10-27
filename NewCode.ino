#include <SPI.h>      //include the SPI bus library
#include <MFRC522.h>  //include the RFID reader library
#include <QTRSensors.h>

const int In1 = 9;
const int In2 = 8;
const int In3 = 7;
const int In4 = 6;
const int trigPin = 3;
const int echoPin = 2;
QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];
int frequency = 0;
String test = "LLRRFFBB";
char moves [64]; //this is the buffer

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
	qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){13, 12, 11, 10}, SensorCount);

}

void Forward()   //run both motors in the same direction
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  delay(100);

  // now turn off motors
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW); 
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);   

  delay(1000);
}
void Left() // now Turns the robot Left
{
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  delay(100);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
}

void Right() // now Turns the robot Right
{
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  delay(100);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

  void Back()   //run both motors in reverse
{
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);

  delay(100);

  // now turn off motors
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW); 
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);   

  delay(1000);
}
void SenseColour()
{
  // Setting red filtered photodiodes to be read
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
  delay(100);

}
void LinePlacement(){
	qtr.read(sensorValues);

  	for (uint8_t i = 0; i < SensorCount; i++){

    	Serial.print(sensorValues[i]);

    	Serial.print('\t');
  }

  Serial.println();

  delay(250);
}

void DetectDistance()
{
  // Variables for duration of ping and the distance in cm
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
	
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

void loop()

{
  test.toCharArray(moves, test.length());

  for (int i = 0; i < test.length(); i++){
    if(moves[i] == 'L'){
      Left();
    }
    else if (moves[i] == 'R'){
      Right();
    }
    else if (moves[i] == 'F'){
      Forward();
    }
    else if (moves[i] == 'B'){
      Back();
    }
  }
  SenseColour();
  //DetectDistance();
	//LinePlacement();
}
