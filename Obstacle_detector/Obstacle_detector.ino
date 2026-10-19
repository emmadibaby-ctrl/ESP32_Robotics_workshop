// =====================================================
//                    MOTOR PINS
// =====================================================

#define m11 25
#define m12 26
#define m21 32
#define m22 33


// =====================================================
//                 MOTOR SPEED PINS
// =====================================================

#define L 2
#define R 4


// =====================================================
//                ULTRASONIC PINS
// =====================================================

#define TRIG_PIN 16
#define ECHO_PIN 15


// =====================================================
//                     SETUP
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

  // Ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Motor speed
  analogWrite(L, 150);
  analogWrite(R, 150);

  // Make sure ultrasonic trigger starts LOW
  digitalWrite(TRIG_PIN, LOW);

  // Start stopped
  stopBot();
}


// =====================================================
//                    FORWARD
// =====================================================

void forward()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);

  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}


// =====================================================
//                    BACKWARD
// =====================================================

void backward()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);

  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}


// =====================================================
//                     RIGHT
// =====================================================

void right()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);

  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}


// =====================================================
//                      STOP
// =====================================================

void stopBot()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);

  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}


// =====================================================
//              GET ULTRASONIC DISTANCE
// =====================================================

float getDistance()
{
  // Send trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // No echo received
  if (duration == 0)
  {
    return 999;
  }

  // Calculate distance in cm
  float distance = duration * 0.0343 / 2;

  return distance;
}


// =====================================================
//                       LOOP
// =====================================================

void loop()
{
  float distance = getDistance();

  // Print distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // =================================================
  //       NO OBSTACLE / OBJECT MORE THAN 10 CM
  // =================================================

  if (distance > 10)
  {
    forward();
  }


  // =================================================
  //       OBJECT DETECTED LESS THAN 10 CM
  // =================================================

  else
  {
    Serial.println("OBSTACLE DETECTED!");

    // -----------------------------------------------
    // STOP FOR 1 SECOND
    // -----------------------------------------------

    stopBot();
    delay(1000);


    // -----------------------------------------------
    // MOVE BACKWARD FOR 1 SECOND
    // -----------------------------------------------

    backward();
    delay(1000);


    // -----------------------------------------------
    // TURN RIGHT FOR 0.5 SECOND
    // -----------------------------------------------

    right();
    delay(500);


    // -----------------------------------------------
    // MOVE FORWARD
    // -----------------------------------------------

    forward();
  }


  delay(50);
}