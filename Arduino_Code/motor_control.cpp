// motor_control.cpp - Basic motor control with IR sensor feedback
// Use this with Arduino IDE by including in a .ino project if needed

const int leftMotor1 = 5;
const int leftMotor2 = 6;
const int rightMotor1 = 9;
const int rightMotor2 = 10;

const int irSensor = A0;

void setup() {
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(irSensor, INPUT);

  Serial.begin(9600);
}

void loop() {
  int irValue = analogRead(irSensor);
  Serial.println(irValue);  // For serial monitoring or Python use

  if (irValue > 500) {
    moveForward();
  } else {
    stopMotors();
  }

  delay(200);
}

void moveForward() {
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}

void stopMotors() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}
