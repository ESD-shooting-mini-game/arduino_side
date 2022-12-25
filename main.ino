const int button = 10;                        //Button to start program
const int IN1 = 7;
const int IN2 = 8;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  bool button_state = digitalRead(button);

  if (button_state == LOW) {                  //If button is pressed
    shoot_mode();
  }

}

void shoot_mode() {
  unsigned long program_time = millis();
  unsigned long  prev_time = millis();
  int mode = 1;
  digitalWrite(IN1, LOW); // Extend
  digitalWrite(IN2, HIGH);

  while (millis() - program_time < 30000) {   // DURATION OF A ROUND

    if (millis() - prev_time > 12000) {       // DURATION BEFORE ACTUATOR CYCLES
      if (mode < 0) {
        digitalWrite(IN1, LOW);               // Extend
        digitalWrite(IN2, HIGH);
      } else {
        digitalWrite(IN1, HIGH);              // Retract
        digitalWrite(IN2, LOW);
      } 
      prev_time = millis();
      mode = -mode;
    }

                                              // CODE SENSOR SINI
  }

  digitalWrite(IN1, HIGH);                    // Retract
  digitalWrite(IN2, LOW);
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
