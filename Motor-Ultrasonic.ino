const int trigPin = 5;
const int echoPin = 4;
const int In1 = 9;
const int In2 = 8;


void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // All motor control pins are outputs
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);

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
