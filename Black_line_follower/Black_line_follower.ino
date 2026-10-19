#define m11 25
#define m12 26
#define m21 32 
#define m22 33

#define L 2
#define R 4

#define IR_LEFT 34
#define IR_RIGHT 35

void setup() {
  Serial.begin(115200);

  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);

  pinMode(L, OUTPUT);
  pinMode(R, OUTPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  analogWrite(L, 150);
  analogWrite(R, 150);
}

// -------- MOTOR FUNCTIONS --------
void forward() {
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
}

void left() {
  digitalWrite(m11,HIGH);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
}

void right() {
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,HIGH);
  digitalWrite(m22,LOW);
}

void stopBot() {
  digitalWrite(m11,LOW);
  digitalWrite(m12,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m22,LOW);
}
// --------------------------------

void loop() {

  int leftSensor = digitalRead(IR_LEFT);
  int rightSensor = digitalRead(IR_RIGHT);

  Serial.print("Left: ");
  Serial.print(leftSensor);
  Serial.print(" | Right: ");
  Serial.println(rightSensor);

  // 🧠 Line Following Logic
  if(leftSensor == LOW && rightSensor == LOW) {
    forward();   // on track
  }
  else if(leftSensor == LOW && rightSensor == HIGH) {
    left();      // adjust left
  }
  else if(rightSensor == LOW && leftSensor == HIGH) {
    right();     // adjust right
  }
  else {
    stopBot();   // both on line
  }

  delay(50);
}