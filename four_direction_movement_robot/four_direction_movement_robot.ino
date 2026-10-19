// ======================
// ESP32 Motor Movement Test
// ======================

// Motor Pins
#define m11 25
#define m12 26
#define m21 32
#define m22 33

// Enable Pins
#define L 2
#define R 4

void setup() {
  Serial.begin(115200);

  // Motor Pins
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);

  // Enable Pins
  pinMode(L, OUTPUT);
  pinMode(R, OUTPUT);

  // Motor Speed (0-255)
  analogWrite(L, 150);
  analogWrite(R, 150);
}

// -------------------
// Movement Functions
// -------------------

void forward() {
  Serial.println("Moving Forward");

  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}

void backward() {
  Serial.println("Moving Backward");

  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}

void left() {
  Serial.println("Turning Left");

  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}

void right() {
  Serial.println("Turning Right");

  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}

void stopBot() {
  Serial.println("Stopping");

  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}

// -------------------
// Main Loop
// -------------------

void loop() {

  forward();
  delay(3000);

  stopBot();
  delay(1000);

  backward();
  delay(3000);

  stopBot();
  delay(1000);

  left();
  delay(3000);

  stopBot();
  delay(1000);

  right();
  delay(3000);

  stopBot();
  delay(3000);
}