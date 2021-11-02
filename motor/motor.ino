int M1P1 = 3;
int M1P2 = 4;
int M1PWM = 5;
int M2PWM = 6;
int M2P1 = 7;
int M2P2 = 8;
int randomPin = 18;
int forwardPin = A3;
int delaytime = 25;
int i = 0;
int random_state = 0;

void motors(bool m1, bool m2, bool m3, bool m4) {
  digitalWrite(M1P1, m1);
  digitalWrite(M1P2, m2);
  digitalWrite(M2P1, m3);
  digitalWrite(M2P2, m4);
}

void motor_way(String x) {
  if (x == "f") {
    motors(HIGH, LOW, LOW, HIGH); //forward
  }
  else if (x == "b") {
    motors(LOW, HIGH, HIGH, LOW); //back
  }
  else if (x == "r") {
    Serial.write("test");
    motors(HIGH, LOW, HIGH, LOW); //right
  }
  else if (x == "l") {
    motors(LOW, HIGH, LOW, HIGH); //left
  }
  else if (x == "fl") {
    motors(LOW, LOW, LOW, HIGH); //forward-left
  }
  else if (x == "fr") {
    motors(HIGH, LOW, LOW, LOW); //forward-right
  }
  else if (x == "bl") {
    motors(LOW, LOW, HIGH, LOW); //back-left
  }
  else if (x == "br") {
    motors(LOW, HIGH, LOW, LOW); //back-right
  }
  else if (x == "s") {
    motors(LOW, LOW, LOW, LOW); //stop
  }
}

void motor_random () {
  for (i; i <= 2; i++) {
    motor_way("r");
    delay(100);
    motor_way("l");
    delay(100);
    motor_way("s");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(M1P1, OUTPUT);
  pinMode(M1P2, OUTPUT);
  pinMode(M1PWM, OUTPUT);
  pinMode(M2PWM, OUTPUT);
  pinMode(M2P1, OUTPUT);
  pinMode(M2P2, OUTPUT);
  pinMode(randomPin, INPUT);
  pinMode(forwardPin, OUTPUT);

  analogWrite(M1PWM, 127);
  analogWrite(M2PWM, 127);
  motor_random();
}

void random_loop() {
  if (random_state == 1) {
    analogWrite(forwardPin, 0);
    motor_random();
    if (digitalRead(randomPin) == HIGH) {
      i = 0;
    }
  }
}

void loop() {
  random_loop();
}
