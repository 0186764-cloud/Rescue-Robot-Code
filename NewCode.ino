const int In1 = 8;
const int In2 = 7;
const int In3 = 6;
const int In4 = 5;
const int trigPin = 3;
const int echoPin = 2;
int frequency = 0;
const int CSPin = 10;

#include <SPI.h>      //include the SPI bus library
#include <MFRC522.h>  //include the RFID reader library
#include <SD.h>

File myFile;


#define SS_PIN 10  //Peripheral select pin
#define RST_PIN 9  //reset pin
#define S0 A0

#define S1 A1
#define S2 A2
#define S3 A3
#define sensorOut A4
#define OE A5

MFRC522 mfrc522(SS_PIN, RST_PIN);  // instantiate a MFRC522 reader object.
MFRC522::MIFARE_Key key;          //create a MIFARE_Key struct named 'key', which will hold the card information

//this is the block number we will write into and then read.
int block=2;  

byte blockcontent[16] = {"Last-Minute-Engg"};  //an array with 16 bytes to be written into one of the 64 card blocks is defined
//byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  //all zeros. This can be used to delete a block.

//This array is used for reading out a block.
byte readbackblock[18];

void setup()
{
  Serial.begin(9600);
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

  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card (in case you wonder what PCD means: proximity coupling device)
  Serial.println("Scan a MIFARE Classic card");

  // Prepare the security key for the read and write functions.
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;  //keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  // All motor control pins are outputs
  }
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
  digitalWrite(In2, HIGH); 
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);

  // now turn off motors

  delay(1000);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW); 

}

void ReadCard()
{

  Serial.begin(9600);

  Serial.print("Initializing SD card...");

  

// Note that even if it's not used as the CS pin, the hardware SS pin 

  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 

  // or the SD library functions will not work. 

   pinMode(CSPin, OUTPUT);

 

  if (!SD.begin(CSPin)) {

    Serial.println("initialization failed!");

    return;

  }

  Serial.println("initialization done.");

 

  // open the file. note that only one file can be open at a time,

  // so you have to close this one before opening another.

  myFile = SD.open("test.txt", FILE_WRITE);

 

  // if the file opened okay, write to it:

  if (myFile) {

    Serial.print("Writing to test.txt...");

    myFile.println("testing 1, 2, 3.");

  // close the file:

    myFile.close();

    Serial.println("done.");

  } else {

    // if the file didn't open, print an error:

    Serial.println("error opening test.txt");

  }
}
void loop()

{
  //goStraight();
  delay(100);
  SenseColour();
  //ReadCard();
}
