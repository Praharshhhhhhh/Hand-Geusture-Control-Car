#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define IN1 4
#define IN2 5
#define ENA 6   // Left motors

#define IN3 7
#define IN4 9
#define ENB 10  // Right motors

#define CE_PIN 2
#define CSN_PIN 3

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

struct ControlData {
  char dir;
  int speed;
};

ControlData data;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);\

  Serial.begin(9600);

  if (!radio.begin()) {
    Serial.println("nRF24L01 not detected!");
    while (1);
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));

    int spd = constrain(data.speed, 0, 255);

    switch (data.dir) {
      case 'F': // forward
        digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
        analogWrite(ENA, spd);
        analogWrite(ENB, spd);
        break;
      case 'B': // backward
        digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
        analogWrite(ENA, spd);
        analogWrite(ENB, spd);
        break;
      case 'L': // left
        digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
        analogWrite(ENA, spd);
        analogWrite(ENB, spd);
        break;
      case 'R': // right
        digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
        analogWrite(ENA, spd);
        analogWrite(ENB, spd);
        break;
      default:  // stop
        digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
        analogWrite(ENA, 0);
        analogWrite(ENB, 0);
        break;
    }

    Serial.print("Dir: "); Serial.print(data.dir);
    Serial.print("  Speed: "); Serial.println(spd);
  }
}
