#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// NRF24
#define CE_PIN 7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

// ADXL345
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

struct ControlData {
  char dir;
  int speed;
};

ControlData data;

int currentSpeed = 0;
int targetSpeed = 0;

void setup() {

  Serial.begin(9600);

  // Initialize ADXL345
  if (!accel.begin()) {
    Serial.println("ADXL345 not detected!");
    while (1);
  }

  accel.setRange(ADXL345_RANGE_16_G);

  // Initialize NRF24
  if (!radio.begin()) {
    Serial.println("NRF24L01 not detected!");
    while (1);
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();

  Serial.println("Gesture Controller Ready");
}

void loop() {

  sensors_event_t event;
  accel.getEvent(&event);

  float x = event.acceleration.x;
  float y = event.acceleration.y;

  data.dir = 'S';
  targetSpeed = 0;

  // Calculate tilt strength
  float tilt = max(abs(x), abs(y));

  targetSpeed = map(tilt * 10, 0, 100, 0, 255);
  targetSpeed = constrain(targetSpeed, 0, 255);

  // Forward
  if (y > 3) {
    data.dir = 'F';
  }

  // Backward
  else if (y < -3) {
    data.dir = 'B';
  }

  // Right
  else if (x > 3) {
    data.dir = 'R';
  }

  // Left
  else if (x < -3) {
    data.dir = 'L';
  }

  // Stop
  else {
    data.dir = 'S';
    targetSpeed = 0;
  }

  // Smooth acceleration
  if (currentSpeed < targetSpeed)
    currentSpeed += 3;

  if (currentSpeed > targetSpeed)
    currentSpeed -= 3;

  currentSpeed = constrain(currentSpeed, 0, 255);

  data.speed = currentSpeed;

  // Send data
  radio.write(&data, sizeof(data));

  // Debug
  Serial.print("X: ");
  Serial.print(x);

  Serial.print(" Y: ");
  Serial.print(y);

  Serial.print(" Dir: ");
  Serial.print(data.dir);

  Serial.print(" Speed: ");
  Serial.println(data.speed);

  delay(20);
}
