/* TO DO:
 * - Work out exact distances up and down for pickup function and convert to step value
 * - maybe at initialisation have lift move to the top (use limit switch)
 * - 
 */


#include <Stepper.h>
#include <stdio.h>
#include <avr/io.h>

/* WHEELS */

int spd = 256;

#define M_STOP      0
#define M_FORWARD   1
#define M_BACKWARD  2
int whileCounter=0;
int capture_toggle;

//WHAT IS THE BELOW???
class MOTOR 
{
  private:
    byte IN1, IN2, EN;
  public:
    MOTOR(byte in1, byte in2, byte en);
    void set_speed(byte en, byte spd);
};
MOTOR::MOTOR(byte in1, byte in2, byte en) {
  IN1 = in1;
  IN2 = in2;
  EN = en;
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN, OUTPUT);
}
void MOTOR::set_speed (byte dir, byte spd) {
  if(spd<0||spd>255) return;
  switch(dir)
  {
    case M_FORWARD:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      break;
    case M_BACKWARD:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      break;
   case M_STOP:
   default:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      break;
  }
  analogWrite(EN,spd);
}

MOTOR M_FrontLeft(9, 10, 8),                           //Setup the Pins for four motors
      M_FrontRight(A3, A4, A5),                      //Red wires left for power, facing input for power in driver
      M_RearLeft(12, 11, 13),        
      M_RearRight(A2, A1, A0);    

/*LIFT*/

#define StepPin 22
#define DirPin 24
#define Slp 26
 
int stepset=0;
int stepspd = 500;

/* SWITCHES */

const int Button = 6;
const int Button2 = 7;

int ButtonState = 0;
int ButtonState2 = 0;
int ButtonCount = 0;
// Define Constants
 
// Number of steps per internal motor revolution 
const float STEPS_PER_REV = 32; 
 
//  Amount of Gear Reduction
const float GEAR_RED = 64;
 
// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;
 
// Define Variables
 
// Number of Steps Required
int StepsRequired;
 
// Create Instance of Stepper Class
// Specify Pins used for motor coils
// The pins used are 8,9,10,11 
// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-3-2-4 for proper step sequencing
 
//Stepper steppermotor1(STEPS_PER_REV, , 24, 23, 25);
Stepper steppermotor2(STEPS_PER_REV, 2, 3, 4, 5);

 
void StringRelease()
{
   // Rotate CW 1/2 turn slowly
  StepsRequired  =  STEPS_PER_OUT_REV * 0.7 ; 
  steppermotor2.setSpeed(1000);   
  steppermotor2.step(StepsRequired);
  delay(1000);
 
}
void setup() 
{
  Serial.begin (9600); //sets the data rate in bits per second (baud) for serial data transmission
                        // opens serial port, sets data rate to 9600 bps
/* ARDUINO MEGA EXAMPLE: (MIGHT NEED THIS)
 *    Serial.begin(9600);
      Serial1.begin(38400);
      Serial2.begin(19200);
      Serial3.begin(4800);
    
      Serial.println("Hello Computer");
      Serial1.println("Hello Serial 1");
      Serial2.println("Hello Serial 2");
      Serial3.println("Hello Serial 3");
 */

 // DC MOTORS

//SWITCHES

//LIFT
   lift_setup();
   pinMode (Button, INPUT);
}

void loop() 
{
delay(1000);
ButtonState = digitalRead (Button);
ButtonState2 = digitalRead (Button2);


//MoveRight(175);

TemplateRun();
//Serial.print("about to pickup");
//PickupFunction();
//Serial.print("Is picking up");
//StringRelease();
delay(150000);

//MoveForwardTrigger();
//Stop();
//CustomRight();
//MoveBackward(255);
//MoveForward(220);

}

//To set an individual wheel as ON/OFF use following; M_FrontRight.set_speed(M_FORWARD,spd);
void Stop() {
  M_FrontLeft.set_speed(M_STOP,0);
  M_FrontRight.set_speed(M_STOP,0);
  M_RearLeft.set_speed(M_STOP,0);
  M_RearRight.set_speed(M_STOP,0);
}
void MoveForward(byte spd) {
  M_FrontLeft.set_speed(M_FORWARD,spd);
  M_FrontRight.set_speed(M_FORWARD,spd);
  M_RearLeft.set_speed(M_FORWARD,spd);
  M_RearRight.set_speed(M_FORWARD,spd);
}
void MoveBackward(byte spd) {
  M_FrontLeft.set_speed(M_BACKWARD,spd);
  M_FrontRight.set_speed(M_BACKWARD,spd);
  M_RearLeft.set_speed(M_BACKWARD,spd);
  M_RearRight.set_speed(M_BACKWARD,spd);
}
void MoveLeft(byte spd) {
  M_FrontLeft.set_speed(M_BACKWARD,spd);
  M_FrontRight.set_speed(M_FORWARD,spd);
  M_RearLeft.set_speed(M_FORWARD,spd);
  M_RearRight.set_speed(M_BACKWARD,spd);
}
void MoveRight(byte spd) {
  M_FrontLeft.set_speed(M_FORWARD,spd);
  M_FrontRight.set_speed(M_BACKWARD,spd);
  M_RearLeft.set_speed(M_BACKWARD,spd);
  M_RearRight.set_speed(M_FORWARD,spd);
}
void MoveLeftForward(byte spd) {
  M_FrontLeft.set_speed(M_STOP,0);
  M_FrontRight.set_speed(M_FORWARD,spd);
  M_RearLeft.set_speed(M_FORWARD,spd);
  M_RearRight.set_speed(M_STOP,0);
}
void MoveRightForward(byte spd) {
  M_FrontLeft.set_speed(M_FORWARD,spd);
  M_FrontRight.set_speed(M_STOP,0);
  M_RearLeft.set_speed(M_STOP,0);
  M_RearRight.set_speed(M_FORWARD,spd);
}
void MoveLeftBackward(byte spd) {
  M_FrontLeft.set_speed(M_BACKWARD,spd);
  M_FrontRight.set_speed(M_STOP,0);
  M_RearLeft.set_speed(M_STOP,0);
  M_RearRight.set_speed(M_BACKWARD,spd);
}
void MoveRightBackward(byte spd) {
  M_FrontLeft.set_speed(M_STOP,0);
  M_FrontRight.set_speed(M_BACKWARD,spd);
  M_RearLeft.set_speed(M_BACKWARD,spd);
  M_RearRight.set_speed(M_STOP,0);
}
void RotateLeft(byte spd) {
  M_FrontLeft.set_speed(M_BACKWARD,spd);
  M_FrontRight.set_speed(M_FORWARD,spd);
  M_RearLeft.set_speed(M_BACKWARD,spd);
  M_RearRight.set_speed(M_FORWARD,spd);
}
void RotateRight(byte spd) {
  M_FrontLeft.set_speed(M_FORWARD,spd);
  M_FrontRight.set_speed(M_BACKWARD,spd);
  M_RearLeft.set_speed(M_FORWARD,spd);
  M_RearRight.set_speed(M_BACKWARD,spd);
}
int cab=130;
void CustomRight(){
  M_FrontLeft.set_speed(M_FORWARD,cab);
  M_FrontRight.set_speed(M_BACKWARD,cab);
  M_RearLeft.set_speed(M_BACKWARD,140);
  M_RearRight.set_speed(M_FORWARD,cab);
}

//LIFT STUFF //82mm for 2000 steps  Beep beep im a sheep Qwack Qwack im a duck Meaow meaow im a cow

void PickupFunction () // NEED TO WORK OUT EXACT VALUES FOR DISTANCES UP & DOWN  use 2000 for now              
{
  lift_A_clockwise();
  delay(500);
  lift_clockwise();

}
void lift_setup()
{
  pinMode(StepPin,OUTPUT);
  pinMode(DirPin,OUTPUT);
  pinMode(Slp,OUTPUT);
  digitalWrite(Slp,LOW);
}
void lift_A_clockwise()
{
   digitalWrite(Slp,HIGH);                 //turns on driver
   digitalWrite(DirPin,HIGH);
   for(stepset=0;stepset<3100;stepset++)
   {
    digitalWrite(StepPin,HIGH);            //initialize step   
    delayMicroseconds(stepspd);               //step speed
    digitalWrite(StepPin,LOW);
    delayMicroseconds(stepspd);
   } 
   digitalWrite(Slp,LOW);                  //turns off driver
}

void lift_clockwise()
{
   digitalWrite(Slp,HIGH);                  //turns on driver
   digitalWrite(DirPin,LOW);
   for(stepset=0;stepset<3100;stepset++)
   {
    digitalWrite(StepPin,HIGH);
    delayMicroseconds(stepspd);
    digitalWrite(StepPin,LOW);
    delayMicroseconds(stepspd);
   }
   digitalWrite(Slp,LOW);                   //turns off driver
}

void ButtonRead(){
 ButtonState = digitalRead (Button);
ButtonState2 = digitalRead (Button2);
}

void MoveForwardTrigger(){
while (ButtonCount<=2)
{
MoveForward(255);
ButtonRead();

    Serial.print("Button 1 =");

  Serial.print(ButtonState);
  Serial.print("        Button 2 =");
  Serial.print(ButtonState2);
    Serial.print("\n");
if ((ButtonState==HIGH) && (ButtonState2 == HIGH)){
  ButtonCount++;
  Serial.print(ButtonCount);
  Serial.print("\n");
}
  else{
    ButtonCount=0;
  }
}
  

}
void TemplateRun(){
//Approach First Batch
Stop();

Serial.print("Moving Forward Go\n");
MoveForwardTrigger();

Stop();
MoveBackward(255);
Serial.print("Move Backward\n");
delay(1000);
MoveRight(175);
Serial.print("Move Right\n");
delay(400);
Stop();
ButtonRead();
ButtonCount=0;
MoveForwardTrigger();
//Pickup First Batch
Serial.print("Pickup Function Go\n");
Stop();
PickupFunction();

MoveBackward(255);
//Approach Second Batch
Serial.print("Move Backward\n");
delay(1000);
ButtonRead();
ButtonCount=0;
Serial.print("Moving Right\n");
MoveRight(175);
delay(5900);

Serial.print("Move Forward\n");
MoveForwardTrigger();

Stop();
//Pickup Second Batch
Serial.print("Pickup Function Go\n");
PickupFunction();
//Approach Third Batch
MoveBackward(255);
Serial.print("Move Backward\n");
delay(1000);
ButtonRead();
ButtonCount=0;
MoveRight(175);
Serial.print("Move Right\n");
delay(6000);
Serial.print("Move Forward\n");
MoveForwardTrigger();
Stop();
//Pickup Third Batch
Serial.print("Pickup Function Go\n");
PickupFunction();
delay(1000);
//Travel to Inland Compound
Serial.print("Move Backwards\n");
MoveBackward(255);
delay(10000);
ButtonRead();
ButtonCount=0;
Serial.print("Roate Left\n");
RotateRight(255);
delay(8700);

Serial.print("Moving Forward\n");
MoveForwardTrigger();

Stop();
//Release String and "bounce" to ensure release
Serial.print("String Release\n");
StringRelease();
delay(500);
MoveBackward(255);
delay(200);
ButtonRead();
ButtonCount=0;
MoveForwardTrigger();
Stop();
delay(200);
MoveBackward(255);
ButtonRead();
ButtonCount=0;
MoveForwardTrigger();
MoveBackward(255);
delay(300);
ButtonRead();
ButtonCount=0;
MoveForwardTrigger();
Stop();
Serial.print("Finished Operation\n");
delay(10000);
}  
