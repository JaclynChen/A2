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


const int sendButtonPin = 10;
int sendButtonState = HIGH;
int sendLastButtonState = HIGH;
unsigned long sendLastDebounceTime = 0;
// if false: mode is to confirm
// if true: mode is to send
bool sendMsg = true;

const int clearButtonPin = 9;
int clearButtonState = HIGH;
int clearLastButtonState = HIGH;
unsigned long clearLastDebounceTime = 0;


// led
const int led = 8;
const int vibromotor = 7;
const int buzzer = 6;

const char* prompts[5] = { "house", "key", "wifi", "smile", "light" };


const char* letters[26]  = { "a", "b", "c", "d", "e", 
                            "f", "g", "h", "i", "j", 
                            "k", "l", "m", "n", "o", 
                            "p", "q", "r", "s", "t",
                             "u", "v", "w", "x", "y",
                             "z"};

bool newGame = true;
int currGameIndex = 0;

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };


static const unsigned char PROGMEM a[] = 
{
  // 'icons8-archer-50', 50x50px
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xc7, 0xff, 
0xff, 0xff, 0xff, 0xfc, 0xc0, 0xc1, 0xf0, 0x00, 0xff, 0xff, 0xf0, 0xc0, 0xc0, 0x00, 0x00, 0x0f, 
0xff, 0xc1, 0xc0, 0xf0, 0x00, 0x00, 0x01, 0xff, 0x81, 0xc0, 0xf0, 0x00, 0x00, 0x00, 0x7f, 0x03, 
0xc0, 0xf3, 0xff, 0xf0, 0x00, 0x3f, 0x03, 0xc0, 0xf3, 0xff, 0xfe, 0x00, 0x0f, 0x07, 0xc0, 0xf9, 
0xff, 0xff, 0x80, 0x0e, 0x0f, 0xc0, 0xf9, 0xff, 0xff, 0xe0, 0x04, 0x7f, 0xc0, 0xf9, 0xff, 0xff, 
0xf0, 0x00, 0xff, 0xc0, 0xf9, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xc0, 0xf9, 0xff, 0xff, 0xfe, 0x00, 
0xff, 0xc0, 0xf9, 0xff, 0xff, 0xff, 0x80, 0x3f, 0xc0, 0xf9, 0xff, 0xff, 0xff, 0x80, 0x3f, 0xc0, 
0xfc, 0xff, 0xff, 0xff, 0x00, 0x1f, 0xc0, 0xfc, 0xff, 0xff, 0xfe, 0x30, 0x0f, 0xc0, 0xfc, 0xff, 
0xff, 0xfc, 0x70, 0x0f, 0xc0, 0xfc, 0xff, 0xff, 0xf8, 0xf8, 0x07, 0xc0, 0xfc, 0xff, 0xff, 0xf1, 
0xfc, 0x07, 0xc0, 0xfc, 0xff, 0xff, 0xe3, 0xfc, 0x07, 0xc0, 0xfc, 0xff, 0xff, 0xc7, 0xfe, 0x03, 
0xc0, 0xfe, 0x7f, 0xff, 0x8f, 0xff, 0x03, 0xc0, 0xfe, 0x7f, 0xff, 0x1f, 0xff, 0x03, 0xc0, 0xfe, 
0x7f, 0xfe, 0x3f, 0xff, 0x83, 0xc0, 0xfe, 0x7f, 0xfc, 0x7f, 0xff, 0x81, 0xc0, 0xfe, 0x7f, 0xf8, 
0xff, 0xff, 0xc1, 0xc0, 0xfe, 0x7f, 0xf1, 0xff, 0xff, 0xc1, 0xc0, 0xfe, 0x7f, 0xe3, 0xff, 0xff, 
0xc1, 0xc0, 0xff, 0x3f, 0xc7, 0xff, 0xff, 0xe1, 0xc0, 0xff, 0x3f, 0x8f, 0xff, 0xff, 0xe1, 0xc0, 
0xff, 0x3f, 0x1f, 0xff, 0xff, 0xe1, 0xc0, 0xff, 0x0e, 0x3f, 0xff, 0xff, 0xe1, 0xc0, 0xfe, 0x02, 
0x7f, 0xff, 0xff, 0xe1, 0xc0, 0xfc, 0x07, 0xff, 0xff, 0xff, 0xe1, 0xc0, 0xf8, 0x0e, 0xff, 0xff, 
0xff, 0xe1, 0xc0, 0xf0, 0x1c, 0xff, 0xff, 0xff, 0xe1, 0xc0, 0xe0, 0x38, 0x7f, 0xff, 0xff, 0xe3, 
0xc0, 0xc0, 0x70, 0x7f, 0xff, 0xff, 0xe3, 0xc0, 0xc0, 0xe0, 0x0f, 0xff, 0xff, 0xe3, 0xc0, 0xfd, 
0xc0, 0x00, 0x1f, 0xff, 0xe3, 0xc0, 0xff, 0x80, 0xf0, 0x00, 0x3f, 0xe3, 0xc0, 0xff, 0x01, 0xff, 
0xe0, 0x00, 0x63, 0xc0, 0xff, 0x83, 0xff, 0xff, 0xc0, 0x01, 0xc0, 0xff, 0x87, 0xff, 0xff, 0xff, 
0x80, 0xc0, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xf8, 0xc0, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xf8, 0xc0, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0 }



void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // set up the button pin as input with internal pull-up resistor
  pinMode(sendButtonPin, INPUT_PULLUP);
  pinMode(clearButtonPin, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(vibromotor, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); // initialize serial communication


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
}

void loop() {

  if (newGame) {
    startNewRound();
  }

   if (Serial.available() > 0) {
    String serialData = Serial.readStringUntil('/n');
    serialData.trim();
    
    // Serial.println(serialData);
    // Serial.println(prompts[currGameIndex]);
  
    if (serialData.equals(String(prompts[currGameIndex]))) {
      Serial.println("Yay! You guessed the word :)");
      newGame = true;
    } else {
      Serial.println("Sorry! That's incorrect :( Try again");
    }
  
  }


  int reading = digitalRead(buttonPin); // read the state of the switch into a local variable
  int sendReading = digitalRead(sendButtonPin);
  int clearReading = digitalRead(clearButtonPin);

  // check to see if you just pressed the button
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if (sendReading != sendLastButtonState) {
    sendLastDebounceTime = millis();
  }

  if (clearReading != clearLastButtonState) {
    clearLastDebounceTime = millis();
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

         if ((millis() - pressedTime) > 500) { // Detect long press (half second)
          longPressDetected = true;
        }
      }
    }
  }

  if ((millis() - sendLastDebounceTime) > debounceDelay) {
    if (sendReading != sendButtonState) {
      sendButtonState = sendReading;
    

    if (sendButtonState == LOW) {
      sendMsg = !sendMsg;

      if (!sendMsg) {
        // confirm msg
        Serial.print("Do you want to send the message?: ");
        Serial.println(savedCode);
        Serial.println("Press the button again to send or press the clear button to restart");
      } else {
        // do led, vibromotor thing
        Serial.print("Relaying message: ");
        Serial.println(savedCode);
        relaySavedCode();
      }

    }

    }
  }

  if ((millis() - clearLastDebounceTime) > debounceDelay) {
    if (clearReading != clearButtonState) {
      clearButtonState = clearReading;
    

    if (clearButtonState == LOW) {
      Serial.println("Clearing saved code");
      sendMsg = true;
      savedCode = "";
      // delay(50);
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
  sendLastButtonState = sendReading;
  clearLastButtonState = clearReading;
}

void startNewRound() {
  // dislay icon
  displayRandomIcon();
  newGame = false;

 

  // prompt for serial feedback

}


void displayRandomIcon() {

  int16_t x, y;
  uint16_t textWidth, textHeight;
  const char strHello[] = "love u too";

  int randomIndex = random(0, sizeof(prompts) / sizeof(prompts[0]));
  currGameIndex = randomIndex;
  // Setup text rendering parameters
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);

  // Measure the text with those parameters. Pass x, y, textWidth, and textHeight
  // by reference so that they are set within the function itself.
  display.getTextBounds(strHello, 0, 0, &x, &y, &textWidth, &textHeight);

  // Center the text on the display (both horizontally and vertically)
  display.setCursor(display.width() / 2 - textWidth / 2, display.height() / 2 - textHeight / 2);

  // Print out the string
  // display.print(strHello);
  display.print(prompts[randomIndex]);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);

}

void drawIcon() {
  
}



void relaySavedCode() {

  for (int i = 0; i < savedCode.length(); i++) {
    char currChar = savedCode.charAt(i);

    digitalWrite(led, HIGH);
    digitalWrite(vibromotor, HIGH);
    tone(buzzer, 85); //Set the voltage to high and makes a noise

    if (currChar == '.') {
      delay(500);
    } else {
      delay (1500);
    }
    digitalWrite(led, LOW);
    digitalWrite(vibromotor, LOW);
    noTone(buzzer);//Sets the voltage to low and makes no noise
    delay(500);
  }
  
}
