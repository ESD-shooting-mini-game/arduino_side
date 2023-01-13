//#define buzzer 8

//const int button = 10;
const int button1 = 2;
const int IN1 = 6;
const int IN2 = 7;
const int buzzer = 8;
const int sw = 3; // limit switch

int score = 0;
volatile bool hit = false;
volatile long score_time = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(sw, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sw), hitTriggered, FALLING);
  
}

void loop() {
  bool button_state = digitalRead(button1);

  if (button_state == LOW) {
    tone(buzzer, 1047);
    delay(800);
    noTone(buzzer);
    delay(200);
    tone(buzzer, 1047);
    delay(800);
    noTone(buzzer);
    delay(200);
    tone(buzzer, 1865);
    delay(1000);
    noTone(buzzer);

    Serial.println("1");
    hit = false;
    shoot_mode();
    Serial.println("0");
  }
}

void shoot_mode() {
  digitalWrite(IN1, LOW); // Extend
  digitalWrite(IN2, HIGH);

  unsigned long program_time = millis();
  unsigned long  prev_time = millis();
  unsigned long  music_time = millis();
  int mode = 1;

  while (millis() - program_time < 30000) { // DURATION OF A ROUND

    if (millis() - prev_time > 12000) { // DURATION BEFORE ACTUATOR CYCLES
      if (mode < 0) {
        digitalWrite(IN1, LOW); // Extend
        digitalWrite(IN2, HIGH);
      } else {
        digitalWrite(IN1, HIGH); // Retract
        digitalWrite(IN2, LOW);

      } prev_time = millis();
      mode = -mode;
    }

    // SENSOR CODE
    if (hit) {
      if (millis() - score_time > 200) {
        score += 1;
        Serial.println("2");
        hit = false;
        tone(buzzer, 2960);
        music_time = millis();
      }
    }

    if (millis() - music_time > 500) { // DURATION OF SOUND
      noTone(buzzer);
    }
    //    Serial.println(score);

  }


  digitalWrite(IN1, HIGH); // Retract
  digitalWrite(IN2, LOW);

  tone(buzzer, 1047);
  delay(100);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1319);
  delay(500);
  noTone(buzzer);
  return;
}

void extend(int x) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(x);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void retract(int x) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(x);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

// ISR
void hitTriggered() {
  hit = true;
  score_time = millis();
}
