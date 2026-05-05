#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin
#define CLK 2
#define DT 3
#define SW 4
#define BUZZER 5
#define LED_PIN 6
#define SERVO_PIN 9

// Rotary Encoder
Encoder encoder(CLK, DT);
#define ENCODER_STEPS_PER_TICK 4
long lastRawEncoder = 0;

int readEncoderStep() {
  long newRaw = encoder.read();
  long delta = newRaw - lastRawEncoder;
  int step = 0;
  if (delta >= ENCODER_STEPS_PER_TICK) {
    step = 1;
    lastRawEncoder += ENCODER_STEPS_PER_TICK;
  } else if (delta <= -ENCODER_STEPS_PER_TICK) {
    step = -1;
    lastRawEncoder -= ENCODER_STEPS_PER_TICK;
  }
  return step;
}

// ====== PIN KUNCI =====
const int PIN_LENGTH = 4;
int correctPIN[PIN_LENGTH] = {1, 2, 3, 4}; // PIN rahasia
int inputPIN[PIN_LENGTH];
int inputIndex = 0;
int currentDigit = 0;

// ====== STATE =====
bool swPressed = false;
int errorCount = 0;
bool inCooldown = false;
unsigned long cooldownStart = 0;
int cooldownTime = 0; // dalam detik

// ====== SERVO ======
Servo lockServo;

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SW, INPUT_PULLUP);

  lockServo.attach(SERVO_PIN);
  lockServo.write(0); // posisi terkunci

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Alamat I2C standar untuk SSD1306
    for (;;) ; // Loop forever jika gagal
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Digital Lock");
  display.display();
  delay(1500);
}

void loop() {
  if (inCooldown) {
    handleCooldown();
    return;
  }

  int step = readEncoderStep();
  if (step != 0) {
    currentDigit = (currentDigit + step + 10) % 10; // 0-9
  }

  // Tombol encoder
  if (digitalRead(SW) == LOW && !swPressed) {
    swPressed = true;
    inputPIN[inputIndex] = currentDigit;
    inputIndex++;
    tone(BUZZER, 1200, 100);

    if (inputIndex >= PIN_LENGTH) {
      checkPIN();
    }
  } else if (digitalRead(SW) == HIGH && swPressed) {
    swPressed = false; // Reset saat tombol dilepas
  }

  drawScreen();
}

// ====== CEK PIN ======
void checkPIN() {
  bool correct = true;
  for (int i = 0; i < PIN_LENGTH; i++) {
    if (inputPIN[i] != correctPIN[i]) {
      correct = false;
      break;
    }
  }

  if (correct) {
    tone(BUZZER, 1500, 200);
    digitalWrite(LED_PIN, HIGH);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("PIN Benar!");
    display.display();

    lockServo.write(90); // buka kunci
    delay(3000);

    lockServo.write(0); // tutup lagi
    digitalWrite(LED_PIN, LOW);
    errorCount = 0;
  } else {
    errorCount++;
    tone(BUZZER, 400, 400);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("PIN Salah!");
    display.display();
    delay(1500);

    if (errorCount % 3 == 0) {
      int batch = errorCount / 3;
      cooldownTime = batch * 60; // 1 menit per batch
      cooldownStart = millis();
      inCooldown = true;
    }
  }

  inputIndex = 0;
  currentDigit = 0;
}

// ====== HANDLE COOLDOWN ======
void handleCooldown() {
  unsigned long elapsed = (millis() - cooldownStart) / 1000;
  int remaining = cooldownTime - elapsed;

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Terlalu Banyak Salah");
  display.setCursor(0, 16);
  display.print("Tunggu: ");
  display.print(remaining);
  display.println(" dtk");
  display.display();

  if (remaining <= 0) {
    inCooldown = false;
  }
}

// ====== OLED UI ======
void drawScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Masukkan PIN");

  // tampilkan input progres
  for (int i = 0; i < PIN_LENGTH; i++) {
    display.setCursor(i * 20, 20);
    if (i < inputIndex) {
      display.print("*");
    } else if (i == inputIndex) {
      display.print(currentDigit);
    } else {
      display.print("_");
    }
  }
  display.display();
}

