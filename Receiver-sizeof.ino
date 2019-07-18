//Receiver Code (Hand) - Mert Arduino and Tech

#include <Servo.h>    //the library which helps us to control the servo motor
#include <SPI.h>      //the communication interface with the modem
#include <RF24.h>     //the library which helps us to control the radio modem

//define the servo name
Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;

RF24 radio(9,10);     /*This object represents a modem connected to the Arduino. 
                      Arguments 9 and 10 are a digital pin numbers to which signals 
                      CE and CSN are connected.*/

byte addresses[][6] = {"1Node","2Node"};//the address of the modem,that will receive data from the Arduino.

bool radioNumber = 0;
bool role = 0;

int msg[4];

void setup(){

  //define the servo input pins
  myServo1.attach(3); //A1
  myServo2.attach(4); //A2
  myServo3.attach(5); //A3
  myServo4.attach(6); //A4
  
  Serial.begin(9600);
  radio.begin();   //it activates the modem.
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);   //determines the address of our modem which receive data.
  radio.startListening();           //enable receiving data via modem
  }

void loop(){
  if(radio.available()){
      
    radio.read(&msg, sizeof(msg));

    myServo1.write(msg[3]); //A1
    myServo2.write(msg[2]); //A2
    myServo3.write(msg[1]); //A3
    myServo4.write(msg[0]); //A4

    Serial.println(msg[3]);
    Serial.println(msg[2]);
    Serial.println(msg[1]);
    Serial.println(msg[0]);

    }
  }
