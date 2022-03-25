int motor1pin1 = 2;
int motor1pin2 = 3;
int ENA  = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(10, OUTPUT);  //control speed
}

void loop() {
  // put your main code here, to run repeatedly:  
  analogWrite(10, 100);  
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);


  delay(1000);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  delay(1000);
}
