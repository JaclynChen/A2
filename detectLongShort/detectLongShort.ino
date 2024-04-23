const int buttonPin = 11;    // the pin that the button is attached to
int buttonState = HIGH;     // the current reading from the input pin
int lastButtonState = HIGH; // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

unsigned long pressedTime = 0;
String savedCode = "";

bool buttonPressed = false;
bool buttonReleased = false;
bool longPressDetected = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // set up the button pin as input with internal pull-up resistor
  Serial.begin(9600); // initialize serial communication
}

void loop() {
  int reading = digitalRead(buttonPin); // read the state of the switch into a local variable

  // check to see if you just pressed the button
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // if the button is pressed
      if (buttonState == LOW) {
        pressedTime = millis();
        buttonPressed = true;
        longPressDetected = false;
      } else {
        buttonReleased = true;

         if ((millis() - pressedTime) > 500) { // Detect long press (1 second)
          longPressDetected = true;
        }
      }
    }
  }

  // Check for actions based on button state
  if (buttonPressed) {
    buttonPressed = false;
  }

  if (buttonReleased) {
   // Serial.print("Button released: ");
    if (longPressDetected) {
      //Serial.println("Long press detected");
      savedCode += "-";
      Serial.println("-");
      longPressDetected = false;
    } else {
      // Serial.print("longPressState is: ");
      // Serial.print(longPressDetected);
      savedCode += ".";
      Serial.println(".");

    }
    buttonReleased = false;
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
