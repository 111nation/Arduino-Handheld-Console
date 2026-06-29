//#define DEBUG

/* LED LIGHT PARAMETERS */
constexpr int RED_PIN = 6;
constexpr int GREEN_PIN = 9;
constexpr int BLUE_PIN = 10;

#define LED_DISCONNECTED 10, 0, 0
#define LED_CONNECTED 0, 10, 0

/* JOYSTICK  PARAMETERS*/
constexpr int JOYSTICK_X_PIN = A0;
constexpr int JOYSTICK_Y_PIN = A1;
constexpr int JOYSTICK_BUTTON_PIN = A2;

/* BUTTON PARAMETERS */
constexpr int BUTTON_A_PIN = A3;

/* GENERAL PARAMETERS */
constexpr int DISCONNECTED_TIMEOUT = 1000;

struct Joystick {
  byte x, y;
  bool clicked;
};

struct Control {
  Joystick joystick;
  bool buttonAClicked;
};

bool receiverReady = false;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(JOYSTICK_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_A_PIN, INPUT);

  Serial.begin(9600);
  Serial.setTimeout(1000);

  changeLED(LED_DISCONNECTED);

}

Control control;

void loop() {
  retrieveReceiverStatus();

  if (receiverReady) {
    receiverReady = false;
    retrieveControlActions(control);
    transmitSerialInformation(control);
  } else {
  }

}

void retrieveReceiverStatus() {
  static unsigned long waitTime = 0;

  if (Serial.available() <= 0) {
    unsigned long currentTime = millis();
    unsigned long timeDelta = currentTime - waitTime;

    if (waitTime != currentTime && timeDelta >= DISCONNECTED_TIMEOUT) {
      changeLED(LED_DISCONNECTED);
      receiverReady = false;
      waitTime = millis();
    }

    return;
  }

  waitTime = millis();  // Stop waiting for data

  char data[2];  // One byte and a null terminator
  int bytesRead = Serial.readBytes(data, 1);
  data[bytesRead] = '\0';

  if (data[0] == '1') {
    receiverReady = true;
    changeLED(LED_CONNECTED);
  } else {
    receiverReady = false;
    //changeLED(LED_DISCONNECTED);
  }
}

void transmitSerialInformation(Control& control) {
  char binaryStr[19];  // 18 bits for integer bits + 1 for null terminator

  // Format of binary string
  // Fixed 8 bits, fixed 8 bits, fixed 1 bit, fixed 1 bit
  // Preserve leading zeros for fixed sizing
  //[Joystick x, Joystick y, Joystick Clicked, ButtonA Clicked]

  // Copy over the joystick clicked information

  // Note about code
  /*
    For every for loop, we start at the end position of each data stream and go backwards
    inserting the data as a fixed binary string.
    We do this for joystick x and joystick y because we need to do this for their 8 bits (byte)
    For joystick clicked, we need one bit to represent if a button was clicked or not
  */
  Joystick& joystick = control.joystick;

  // Copy over the joystick x
  for (int i = 0; i < 8; i++) {
    binaryStr[7 - i] = (joystick.x & (1 << i)) ? '1' : '0';
  }

  // Copy over the joystick y
  for (int i = 0; i < 8; i++) {
    binaryStr[15 - i] = (joystick.y & (1 << i)) ? '1' : '0';
  }

  binaryStr[16] = joystick.clicked ? '1' : '0';
  binaryStr[17] = control.buttonAClicked ? '1' : '0';
  binaryStr[18] = '\0';

  Serial.println(binaryStr);
}

void retrieveControlActions(Control& control) {
  retrieveJoystickActions(control.joystick);
  control.buttonAClicked = (digitalRead(BUTTON_A_PIN) == HIGH);
}

void retrieveJoystickActions(Joystick& joystick) {
  int x = map(analogRead(JOYSTICK_X_PIN), 0, 1023, -100, 100);
  int y = map(analogRead(JOYSTICK_Y_PIN), 0, 1023, -100, 100);

  // Account for drift -4 to 4 doesnt count as input
  if (x < 5 && x > -5) {
    joystick.x = 0;
  } else {
    joystick.x = x;
  }

  if (y < 5 && y > -5) {
    joystick.y = 0;
  } else {
    joystick.y = y;
  }

  joystick.clicked = (digitalRead(JOYSTICK_BUTTON_PIN) == 0);
}

void changeLED(int red, int green, int blue) {
  // Accept regular 0-255 rgb input and scale it to 0-1023 for
  // analogWrite

  red = constrain(red, 0, 255);
  green = constrain(green, 0, 255);
  blue = constrain(blue, 0, 255);

  analogWrite(RED_PIN, red / 255.0 * 1023);
  analogWrite(GREEN_PIN, green / 255.0 * 1023);
  analogWrite(BLUE_PIN, blue / 255.0 * 1023);
}

#ifdef DEBUG
  void debugControlActions(Control& control) {
    debugJoystickActions(control.joystick);
    
    if (control.buttonAClicked) {
      Serial.println(F("Button A Clicked"));
    }
  }

  void debugJoystickActions(Joystick& joystick) {
    // Print debug messages when joystick has been interacted with
    if (joystick.x == 0 && joystick.y == 0 && !joystick.clicked) return;

    Serial.print(f("X:"));
    Serial.println(joystick.x);

    Serial.print(F("Y:"));
    Serial.println(joystick.y);

    if (joystick.clicked) {
      Serial.println(F("Joystick pressed"));
    }
  }
#endif