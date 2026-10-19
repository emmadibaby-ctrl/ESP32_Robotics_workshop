// =====================================================
//              ESP32 CLAP CONTROL ROBOT
// =====================================================

// ================= SOUND SENSOR =================

#define SOUND_AO 39
#define SOUND_DO 19

// ================= MOTOR PINS ====================

#define IN1 25
#define IN2 26
#define IN3 32
#define IN4 33

// ================= ENABLE PINS ===================

#define ENA 2
#define ENB 4

// ================= SPEED =========================

int speedForward  = 255;
int speedBackward = 240;
int speedTurn     = 220;

// ================= CLAP SETTINGS =================

int clapCount = 0;

unsigned long lastClapTime = 0;

const unsigned long clapDelay = 700;

// Used to detect only one transition per clap
bool previousSoundState = HIGH;


// =====================================================
//                        SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  // Sound sensor
  pinMode(SOUND_AO, INPUT);
  pinMode(SOUND_DO, INPUT);

  // Motor direction pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Motor enable pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Start with motors stopped
  stopMotors();

  Serial.println();
  Serial.println("==============================");
  Serial.println("   CLAP CONTROL ROBOT");
  Serial.println("==============================");
  Serial.println("1 Clap  -> Forward");
  Serial.println("2 Claps -> Backward");
  Serial.println("3 Claps -> Left");
  Serial.println("4 Claps -> Right");
  Serial.println("==============================");
}


// =====================================================
//                         LOOP
// =====================================================

void loop() {

  // Read digital sound output
  int soundState = digitalRead(SOUND_DO);

  // Read analog sound level
  int soundValue = analogRead(SOUND_AO);


  // Print analog value occasionally if needed
  // Serial.println(soundValue);


  // ===================================================
  // Detect a NEW clap
  // ===================================================

  if (previousSoundState == HIGH && soundState == LOW) {

    clapCount++;

    lastClapTime = millis();

    Serial.print("CLAP DETECTED | Count = ");
    Serial.print(clapCount);

    Serial.print(" | AO = ");
    Serial.println(soundValue);

    // Small debounce delay
    delay(100);
  }

  previousSoundState = soundState;


  // ===================================================
  // Wait until clap sequence is finished
  // ===================================================

  if (clapCount > 0 &&
      millis() - lastClapTime > clapDelay) {

    Serial.println();
    Serial.println("Executing command...");


    // =================================================
    // 1 CLAP
    // =================================================

    if (clapCount == 1) {

      Serial.println("1 Clap -> FORWARD");

      forward();

      delay(500);

      stopMotors();
    }


    // =================================================
    // 2 CLAPS
    // =================================================

    else if (clapCount == 2) {

      Serial.println("2 Claps -> BACKWARD");

      backward();

      delay(500);

      stopMotors();
    }


    // =================================================
    // 3 CLAPS
    // =================================================

    else if (clapCount == 3) {

      Serial.println("3 Claps -> LEFT");

      leftTurn();

      delay(500);

      stopMotors();
    }


    // =================================================
    // 4 CLAPS
    // =================================================

    else if (clapCount == 4) {

      Serial.println("4 Claps -> RIGHT");

      rightTurn();

      delay(500);

      stopMotors();
    }


    // =================================================
    // INVALID
    // =================================================

    else {

      Serial.print(clapCount);
      Serial.println(" Claps -> INVALID COMMAND");

      stopMotors();
    }


    // Reset clap counter
    clapCount = 0;

    Serial.println("Ready for next command.");
    Serial.println();
  }
}


// =====================================================
//                     FORWARD
// =====================================================

void forward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, speedForward);
  analogWrite(ENB, speedForward);
}


// =====================================================
//                     BACKWARD
// =====================================================

void backward() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, speedBackward);
  analogWrite(ENB, speedBackward);
}


// =====================================================
//                     LEFT TURN
// =====================================================

void leftTurn() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, speedTurn);
  analogWrite(ENB, speedTurn);
}


// =====================================================
//                     RIGHT TURN
// =====================================================

void rightTurn() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, speedTurn);
  analogWrite(ENB, speedTurn);
}


// =====================================================
//                     STOP MOTORS
// =====================================================

void stopMotors() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}