#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// NRF24L01 Pins
#define CE_PIN 7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

// ADXL335 Pins
#define X_PIN A0
#define Y_PIN A1
#define Z_PIN A2

struct ControlData {
  char dir;
  int speed;
};

ControlData data;

// Smooth speed variables
int currentSpeed = 0;
int targetSpeed = 0;

void setup() {
  Serial.begin(9600);

  if (!radio.begin()) {
    Serial.println("nRF24L01 not detected!");
    while (1);
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();

  Serial.println("Gesture Transmitter Ready");
}

void loop() {

  int xValue = analogRead(X_PIN);
  int yValue = analogRead(Y_PIN);

  // Default stop
  data.dir = 'S';
  targetSpeed = 0;

  // Center values around 512
  int xOffset = xValue - 512;
  int yOffset = yValue - 512;

  // Dead zone
  if (abs(xOffset) < 40) xOffset = 0;
  if (abs(yOffset) < 40) yOffset = 0;

  // Calculate proportional speed
  int tiltAmount = max(abs(xOffset), abs(yOffset));

  targetSpeed = map(tiltAmount, 0, 350, 0, 255);
  targetSpeed = constrain(targetSpeed, 0, 255);

  // Gesture detection

  // Forward
  if (yOffset > 80) {
    data.dir = 'F';
  }

  // Backward
  else if (yOffset < -80) {
    data.dir = 'B';
  }

  // Right
  else if (xOffset > 80) {
    data.dir = 'R';
  }

  // Left
  else if (xOffset < -80) {
    data.dir = 'L';
  }

  // Stop
  else {
    data.dir = 'S';
    targetSpeed = 0;
  }

  // Smooth acceleration / deceleration
  if (currentSpeed < targetSpeed) {
    currentSpeed += 3;
  }

  else if (currentSpeed > targetSpeed) {
    currentSpeed -= 3;
  }

  currentSpeed = constrain(currentSpeed, 0, 255);

  // Send smoothed speed
  data.speed = currentSpeed;

  // Transmit data
  radio.write(&data, sizeof(data));

  // Debugging
  Serial.print("X: ");
  Serial.print(xValue);

  Serial.print(" Y: ");
  Serial.print(yValue);

  Serial.print(" Dir: ");
  Serial.print(data.dir);

  Serial.print(" Speed: ");
  Serial.println(data.speed);

  delay(20);
}
