
int spd = 256;

#define M_STOP      0
#define M_FORWARD   1
#define M_BACKWARD  2
int whileCounter=0;


class MOTOR {
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
   
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  //  DC Motors

}

void loop() {
  //Need implementation of sensors, build a base code to work with them (possible distance sensor as well?)
  //Replace specific delays for forward movement all with sensor triggers (make a void, will be the same for all)
  //
  delay(3000);
  //MoveRight(175);

//MoveBackward(255);
CustomRight();
//TemplateRun();

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

void CustomRight(){
  M_FrontLeft.set_speed(M_FORWARD,175);
  M_FrontRight.set_speed(M_BACKWARD,175);
  M_RearLeft.set_speed(M_BACKWARD,175);
  M_RearRight.set_speed(M_FORWARD,175);
}
void TemplateRun(){
Stop();
delay(3000);
Serial.print("Moving Forward Go\n");
MoveForward(255);
delay(10500);
Stop();
Serial.print("Pickup Function Go\n");
//PickupFunction();
delay(1000);
MoveBackward(255);
delay(1000);
Serial.print("Moving Right\n");
MoveRight(175);
delay(6000);
MoveForward(255);
delay(1000);
Stop();
Serial.print("Pickup Function Go\n");
//PickupFunction();
delay(3000);
MoveBackward(255);
delay(1000);
MoveRight(175);
Serial.print("Move Right\n");
delay(6000);
MoveForward(255);
delay(1000);
Stop();
Serial.print("Pickup Function Go\n");
//PickupFunction();
delay(1000);
Serial.print("Move Backwards\n");
MoveBackward(255);
delay(10500);
Serial.print("Roate Left\n");
RotateRight(255);
delay(11200);
Serial.print("Moving Forward\n");
MoveForward(255);
delay(8500);
Stop();
Serial.print("String Release\n");
//StringRelease();
Serial.print("Finished Operation\n");
delay(10000);
}  
