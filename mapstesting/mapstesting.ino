/*
 * This script is an HID injector meant to automate
 * logins into student Chromebooks at GrantBowler Elementary
 * for testing sessions
 *
 */
#include <Keyboard.h>

/* Modify the following definitions to fit the testing session */

#define session_name "---"
#define session_pass "---"

/* Special characters definition */
#define KEY_LEFT_CTRL  0x80
#define KEY_LEFT_SHIFT 0x81
#define KEY_LEFT_ALT   0x82
#define KEY_RIGHT_CTRL 0x84
#define KEY_RIGHT_SHIFT    0x85
#define KEY_RIGHT_ALT  0x86
#define KEY_UP_ARROW   0xDA
#define KEY_DOWN_ARROW 0xD9
#define KEY_LEFT_ARROW 0xD8
#define KEY_RIGHT_ARROW    0xD7
#define KEY_BACKSPACE  0xB2
#define KEY_TAB        0xB3
#define KEY_ENTER 0xB0
#define KEY_ESC        0xB1
#define KEY_CAPS_LOCK  0xC1

int buttonPin = 2;
int RXLED = 17;
static uint8_t __clock_prescaler = (CLKPR & (_BV(CLKPS0) | _BV(CLKPS1) | _BV(CLKPS2) | _BV(CLKPS3)));

 void setup() {
  setPrescaler(); // Set prescaler to highest clock speed
  Keyboard.begin(); // Start they keyboard emulator
  pinMode(buttonPin, INPUT);  // Set up the debugging pin. If you want to debug the code, use a length of wire to connect pins 2 and GND on the board
  digitalWrite(buttonPin, HIGH);

  pinMode(RXLED, OUTPUT); // Configure the on-board LED
  digitalWrite(RXLED, LOW);
  TXLED1;
  if (digitalRead(buttonPin) == 0) {
    showSuccess();
  }
  delay(200);
}

void bootLoop() {
  //      digitalWrite(RXLED, LOW);   // set the LED on
  TXLED0; //TX LED is not tied to a normally controlled pin
  delay(200);              // wait for a second
  TXLED1;
  delay(200);
  TXLED0; //TX LED is not tied to a normally controlled pin
  delay(200);              // wait for a second
  TXLED1;
  delay(800);
}

void loop() {
  // put your main code here, to run repeatedly:
  login();
  showSuccess();
  bootLoop();

}

void showSuccess() {
  digitalWrite(RXLED, HIGH);  // set the LED off
  while (true) {
    bootLoop();
  }
}

void login(){
  delay(500);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.write(KEY_TAB);
  delay(200);
  Keyboard.write(KEY_TAB);
  delay(200);
  Keyboard.write(KEY_TAB);
  delay(200);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.write(KEY_ENTER);
  delay(200);
  Keyboard.write(KEY_UP_ARROW);
  delay(200);
  Keyboard.write(KEY_UP_ARROW);
  delay(200);
  Keyboard.write(KEY_ENTER);
  delay(15000);
  Keyboard.write(KEY_TAB);
  delay(200);
  Keyboard.write(KEY_TAB);
  Keyboard.print(session_name);
  Keyboard.write(KEY_TAB);
  delay(200);
  Keyboard.println(session_pass);
  delay(1500);
}
void setPrescaler() {
  // Disable interrupts.
  uint8_t oldSREG = SREG;
  cli();

  // Enable change.
  CLKPR = _BV(CLKPCE); // write the CLKPCE bit to one and all the other to zero

  // Change clock division.
  CLKPR = 0x0; // write the CLKPS0..3 bits while writing the CLKPE bit to zero

  // Copy for fast access.
  __clock_prescaler = 0x0;

  // Recopy interrupt register.
  SREG = oldSREG;
}
