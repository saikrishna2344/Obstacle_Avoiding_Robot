#define trigPin 9
#define echoPin 10
#define leftIR A0
#define rightIR A1
#define buzzer 6
#define ledRed 7
#define ledGreen 8

// Motor pins
#define in1 2
#define in2 3
#define in3 4
#define in4 5

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);

  int left = digitalRead(leftIR);
  int right = digitalRead(rightIR);

  // Edge detection (IR)
  if (left == 0 || right == 0) {
    stopMotors();
    tone(buzzer, 1000);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    delay(1000);
    noTone(buzzer);
  }

  // Obstacle detection
  else if (distance < 15) {
    stopMotors();
    tone(buzzer, 2000);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    delay(500);
    turnRight(); // avoid
    delay(400);
    noTone(buzzer);
  }

  // Safe path
  else {
    moveForward();
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  }

  delay(100);
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
