// =====================================================
//                 MOTOR PINS
// =====================================================

#define m11 25
#define m12 26
#define m21 32
#define m22 33


// =====================================================
//              MOTOR SPEED PINS
// =====================================================

#define L 2
#define R 4


// =====================================================
//                 IR SENSOR PINS
// =====================================================

#define IR_LEFT 34
#define IR_RIGHT 35


// =====================================================
//                    SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);

  // Motor direction pins
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);

  // Motor speed pins
  pinMode(L, OUTPUT);
  pinMode(R, OUTPUT);

  // IR sensors
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  // Motor speed
  analogWrite(L, 150);
  analogWrite(R, 150);

  // Start stopped
  stopBot();
}


// =====================================================
//                  FORWARD
// =====================================================

void forward()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);

  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}


// =====================================================
//                  BACKWARD
// =====================================================

void backward()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);

  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}


// =====================================================
//                    LEFT
// =====================================================

void left()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);

  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}


// =====================================================
//                    RIGHT
// =====================================================

void right()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);

  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}


// =====================================================
//                    STOP
// =====================================================

void stopBot()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);

  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}


// =====================================================
//                     LOOP
// =====================================================

void loop()
{
  int leftSensor  = digitalRead(IR_LEFT);
  int rightSensor = digitalRead(IR_RIGHT);

  // Serial monitor
  Serial.print("LEFT = ");
  Serial.print(leftSensor);

  Serial.print("   RIGHT = ");
  Serial.println(rightSensor);


  // =================================================
  // CONDITION 1
  // LEFT = 0
  // RIGHT = 0
  //
  // NORMAL CONDITION
  // MOVE FORWARD
  // =================================================

  if (leftSensor == LOW && rightSensor == LOW)
  {
    forward();
  }


  // =================================================
  // CONDITION 2
  // LEFT = 1
  // RIGHT = 1
  //
  // STOP 1 SEC
  // BACKWARD 1 SEC
  // RIGHT 1 SEC
  // FORWARD
  // =================================================

  else if (leftSensor == HIGH && rightSensor == HIGH)
  {
    Serial.println("BOTH SENSORS = 1");

    // Stop both motors
    stopBot();
    delay(1000);

    // Move backward
    backward();
    delay(1000);

    // Turn right
    right();
    delay(1000);

    // Continue forward
    forward();
  }


  // =================================================
  // CONDITION 3
  // LEFT = 0
  // RIGHT = 1
  //
  // LEFT 0.5 SEC
  // BACKWARD 1 SEC
  // LEFT 1 SEC
  // FORWARD
  // =================================================

  else if (leftSensor == LOW && rightSensor == HIGH)
  {
    Serial.println("LEFT = 0, RIGHT = 1");

    // Turn left for 0.5 second
    left();
    delay(500);

    // Move backward for 1 second
    backward();
    delay(1000);

    // Turn left for 1 second
    left();
    delay(1000);

    // Continue forward
    forward();
  }


  // =================================================
  // CONDITION 4
  // LEFT = 1
  // RIGHT = 0
  //
  // RIGHT 0.5 SEC
  // BACKWARD 1 SEC
  // RIGHT 1 SEC
  // FORWARD
  // =================================================

  else if (leftSensor == HIGH && rightSensor == LOW)
  {
    Serial.println("LEFT = 1, RIGHT = 0");

    // Turn right for 0.5 second
    right();
    delay(500);

    // Move backward for 1 second
    backward();
    delay(1000);

    // Turn right for 1 second
    right();
    delay(1000);

    // Continue forward
    forward();
  }


  delay(50);
}