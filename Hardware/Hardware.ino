/* LED LIGHT PARAMETERS */
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

#define LED_DISCONNECTED 10, 0, 0
#define LED_CONNECTED 0, 10, 0

/* JOYSTICK  PARAMETERS*/
#define JOYSTICK_X_PIN A0 
#define JOYSTICK_Y_PIN A1
#define JOYSTICK_BUTTON_PIN A2 

/* GENERAL PARAMETERS */
#define DISCONNECTED_TIMEOUT 1000

struct Joystick {
  byte x, y;
  bool clicked;
};

bool receiverReady = false;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(JOYSTICK_BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.setTimeout(1000);

  changeLED(LED_DISCONNECTED);
}

Joystick joystick;

void loop() {
  
  retrieveReceiverStatus();

  if (receiverReady) {
    retrieveJoystickActions(joystick);
    transmitSerialInformation(joystick);
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

  waitTime = millis(); // Stop waiting for data

  char data[2]; // One byte and a null terminator
  int bytesRead = Serial.readBytes(data, 1);
  data[bytesRead] = '\0';

  if (data[0] == '1') {
    receiverReady = true;
    changeLED(LED_CONNECTED);
  } else { 
    receiverReady = false;
    changeLED(LED_DISCONNECTED);
  }
}

void transmitSerialInformation(Joystick& joystick) {
  char binaryStr[18]; // 17 bits for integer bits + 1 for null terminator

  // Format of binary string
  // Fixed 8 bits, fixed 8 bits, fixed 1 bit
  // Preserve leading zeros for fixed sizing
  //[Joystick x, Joystick y, Button Clicked]

  // Copy over the joystick clicked information

  // Note about code
  /*
    For every for loop, we start at the end position of each data stream and go backwards
    inserting the data as a fixed binary string.
    We do this for joystick x and joystick y because we need to do this for their 8 bits (byte)
    For joystick clicked, we need one bit to represent if a button was clicked or not
  */
 
  // Copy over the joystick x
  for (int i = 0; i < 8; i++) {
    binaryStr[7 - i] = (joystick.x & (1 << i)) ? '1' : '0';
  }

  // Copy over the joystick y
  for (int i = 0; i < 8; i++) {
    binaryStr[15 - i] = (joystick.y & (1 << i)) ? '1' : '0';
  }
  
  binaryStr[16] = joystick.clicked ? '1' : '0';
  binaryStr[17] = '\0';

  Serial.println(binaryStr);
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

void debugJoystickActions(Joystick& joystick) {
  // Print debug messages when joystick has been interacted with
  if (joystick.x == 0 && joystick.y == 0 && !joystick.clicked) return;

  Serial.print("X:");
  Serial.println(joystick.x);

  Serial.print("Y:");
  Serial.println(joystick.y);

  if (joystick.clicked) {
    Serial.println("Button pressed");
  }
}

void changeLED(int red, int green, int blue) {
  // Accept regular 0-255 rgb input and scale it to 0-1023 for 
  // analogWrite

  red = constrain(red, 0, 255);
  green = constrain(green, 0, 255);
  blue = constrain(blue, 0, 255);

  analogWrite(RED_PIN, red/255.0 * 1023);
  analogWrite(GREEN_PIN, green/255.0 * 1023);
  analogWrite(BLUE_PIN, blue/255.0 * 1023);
}