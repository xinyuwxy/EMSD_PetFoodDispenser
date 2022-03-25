/* Stepper Motor Control */

#include <Stepper.h>
#include <Wire.h> 
#include "SparkFun_Qwiic_Rfid.h"

#define RFID_ADDR 0x7D // Default I2C address 

//user defined
int portionSize = 3 ;


bool dispensed = 0;
bool trayOut = 0;
int id1_match = -1;
int id2_match = -1;
String tagid1 = "660229922536";
String tagid2 = "8501947214083";

//RFID constant
const int intPin = 3; 
String tag; 

//Stepper motor constant
const int stepsPerRevolution = 200;


//dc motor constants
int motor1pin1 = 5;
int motor1pin2 = 6;
int ENA  = 10;
int trayMotorRotT = 400;


Stepper myStepper(stepsPerRevolution, 9,8);
Qwiic_Rfid myRfid(RFID_ADDR);


void setup() {
   // set the speed at 60 rpm:
   myStepper.setSpeed(60);
   // initialize the serial port:
   Serial.begin(115200);
   Wire.begin(); 


   //DC motor setup
   pinMode(motor1pin1, OUTPUT);
   pinMode(motor1pin2, OUTPUT);
   pinMode(10, OUTPUT); 

   //RFID setup
   if(myRfid.begin())
     Serial.println("Ready to scan some tags!"); 
   else
     Serial.println("Could not communicate with the Qwiic RFID Reader!!!"); 

    // Put the interrupt pin in a known HIGH state. 
    pinMode(intPin, INPUT_PULLUP); 

    // Want to clear tags sitting on the Qwiic RFID card?
    myRfid.clearTags();
   
}

void loop() {
   // step one revolution in one direction:

    if(digitalRead(intPin) == LOW){
        
            tag = myRfid.getTag();
            Serial.println(tag);
            if (tag == tagid1){
                id1_match = 1;
                Serial.println("Correct id detected");
                if (dispensed == 0){
                    for(int counter = 0;counter <= portionSize-1;counter++) {
                        myStepper.step(133);
                        delay(500);
                        
                    }
                    dispensed =1 ;
                    
                }
                delay(100);

            }
            else{
                id1_match = 0;
                Serial.println("Wrong id detecetd");
            }


        
        }
    else
        {
            
            //Serial.println(digitalRead(intPin));
            if (dispensed ==1 && trayOut == 0 && id1_match == 1){
                analogWrite(10, 100);  
                digitalWrite(motor1pin1, LOW);
                digitalWrite(motor1pin2, HIGH);


                trayOut =1;
                Serial.println("Extend Tray");
                delay(trayMotorRotT);
            
            }
            else if(trayOut == 1 && id1_match == 0){
                analogWrite(10, 100);   //reverse direction
                digitalWrite(motor1pin1, HIGH);
                digitalWrite(motor1pin2, LOW);


                trayOut =0;
                Serial.println("Retract Tray");
                delay(trayMotorRotT+50);
                

            }
            else{
            Serial.println("Tray Stop");
            analogWrite(10, 0);
            //digitalWrite(motor1pin1, LOW);
            //digitalWrite(motor1pin2, LOW);
            delay(1000);
            }

            }


}
