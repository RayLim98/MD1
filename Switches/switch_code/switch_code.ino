const int Button = 2;
const int Button2 = 3;
const int LED = 13;

int ButtonState = 0;
int ButtonState2 = 0;

void setup() {
  
  pinMode (Button, INPUT);
  pinMode (LED, OUTPUT);
  
}

void loop() {
  
ButtonState = digitalRead (Button);
ButtonState2 = digitalRead (Button2);

  if ((ButtonState == HIGH) && (ButtonState2 == HIGH)) {
    digitalWrite (LED, HIGH) ;
  }
  
  else {
    digitalWrite (LED, LOW);
  }
  
}
