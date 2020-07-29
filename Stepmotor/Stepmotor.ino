
#include <stdio.h>
#include <avr/io.h>

#define StepPin 22
#define DirPin 24
#define Slp 26
 
int stepset=0;
int stepspd = 1000;
 
void setup() 
{
  pinMode(StepPin,OUTPUT);
  pinMode(DirPin,OUTPUT);
  pinMode(Slp,OUTPUT);
  digitalWrite(Slp,LOW);
}
 
void loop() 
{
  A_clockwise();
  delay(1000);
  clockwise();
  delay(1000);
}


void A_clockwise()
{
   digitalWrite(Slp,HIGH);                 //turns on driver
   digitalWrite(DirPin,HIGH);
   for(stepset=0;stepset<200;stepset++)
   {
    digitalWrite(StepPin,HIGH);            //initialize step   
    delayMicroseconds(stepspd);               //step speed
    digitalWrite(StepPin,LOW);
    delayMicroseconds(stepspd);
   } 
   digitalWrite(Slp,LOW);                  //turns off driver
}

void clockwise()
{
   digitalWrite(Slp,HIGH);                  //turns on driver
   digitalWrite(DirPin,LOW);
   for(stepset=0;stepset<200;stepset++)
   {
    digitalWrite(StepPin,HIGH);
    delayMicroseconds(stepspd);
    digitalWrite(StepPin,LOW);
    delayMicroseconds(stepspd);
   }
   digitalWrite(Slp,LOW);                   //turns off driver
}
