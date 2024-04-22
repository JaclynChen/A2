int limitSwitch = 11;

void setup() {
  Serial.begin(9600);
  pinMode(limitSwitch, INPUT_PULLUP);
}

void loop() {
  int limitVal = digitalRead(limitSwitch);

  if (limitVal == LOW) {
   Serial.println("pressed");
  } else {
    Serial.println("not pressed");
  }
}
