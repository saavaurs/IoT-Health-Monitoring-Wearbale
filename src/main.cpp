#define BLYNK_TEMPLATE_ID "TMPL6jUKbNh-a"
#define BLYNK_TEMPLATE_NAME "Smart Health Wearable"
#define BLYNK_AUTH_TOKEN "WsqkJ9vi87CDjpUdI1L2rIVOQRAAqA6s"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050_tockn.h>

// WiFi Wokwi
const char* ssid = "Wokwi-GUEST"; // SSID WiFi simulasi Wokwi
const char* pass = "";            // Password WiFi simulasi Wokwi

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Objek OLED

// MPU6050
MPU6050 mpu(Wire);                // Objek sensor MPU6050
#define MPU6050_ADDR 0x68         // Alamat I2C MPU6050

// Pin
#define BUTTON_PIN 2              // Pin pushbutton
#define POT_PIN 4                 // Pin potensiometer (simulasi sensor)
#define LED_PIN 15                // Pin LED indikator

// Variabel debounce tombol
bool buttonState = HIGH;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Timer untuk Blynk
BlynkTimer timer;

// Fungsi membaca dan mengirim data sensor ke OLED & Blynk
void readHealthSensor() {
  // Simulasi heart rate dan SpO2 dari potensiometer
  int heartRate = map(analogRead(POT_PIN), 0, 4095, 70, 180); // HR simulasi
  int spo2 = map(analogRead(POT_PIN), 0, 4095, 95, 99);        // SpO2 simulasi

  // Simulasi akselerometer (juga dari potensiometer)
  double ax = map(analogRead(POT_PIN), 0, 4095, -2, 2) / 10.0;
  double ay = map(analogRead(POT_PIN), 0, 4095, -2, 2) / 10.0;
  double az = map(analogRead(POT_PIN), 0, 4095, 8, 12) / 10.0;

  // Kirim data ke Blynk (V1: HR, V2: SpO2, V3-V5: akselerometer)
  Blynk.virtualWrite(V1, heartRate);
  Blynk.virtualWrite(V2, spo2);
  Blynk.virtualWrite(V3, ax);
  Blynk.virtualWrite(V4, ay);
  Blynk.virtualWrite(V5, az);

  // Tampilkan data ke OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Heart Rate: ");
  display.println(heartRate);
  display.print("SpO2: ");
  display.println(spo2);
  display.print("AccX: ");
  display.println(ax, 2);
  display.print("AccY: ");
  display.println(ay, 2);
  display.print("AccZ: ");
  display.println(az, 2);
  display.display();
}

// Fungsi untuk membaca status tombol, mengirim ke Blynk, dan mengontrol LED
void checkButton() {
  int reading = digitalRead(BUTTON_PIN); // Baca status tombol
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Reset waktu debounce jika status berubah
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      // Kirim status tombol ke Blynk (V0)
      Blynk.virtualWrite(V0, buttonState == LOW ? 1 : 0);
      // Kontrol LED indikator: ON saat tombol ditekan, OFF saat dilepas
      digitalWrite(LED_PIN, buttonState == LOW ? HIGH : LOW);
      Serial.println(buttonState == LOW ? "Button Pressed" : "Button Released");
    }
  }
  lastButtonState = reading;
}

void setup() {
  Serial.begin(115200); // Mulai serial monitor

  // Inisialisasi I2C dengan SDA 21 dan SCL 19 (sesuai diagram.json)
  Wire.begin(21, 19, 100000);
  delay(100);

  pinMode(BUTTON_PIN, INPUT);  // Konfigurasi pin tombol (dengan resistor eksternal pull-down)
  pinMode(POT_PIN, INPUT);     // Konfigurasi pin potensiometer
  pinMode(LED_PIN, OUTPUT);    // Konfigurasi pin LED

  // Inisialisasi OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED not found");
    while (1); // Berhenti jika OLED gagal
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Smartband ");
  display.println("Health Monitoring ");
  display.println("Ready");
  display.display();

  // Inisialisasi MPU6050 (tidak digunakan untuk simulasi, tapi tetap diinisialisasi)
  mpu.begin();
  delay(100);
  mpu.calcGyroOffsets(true);

  // Hubungkan ke Blynk Cloud
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timer: update sensor setiap 500ms, cek tombol setiap 50ms
  timer.setInterval(500L, readHealthSensor);
  timer.setInterval(50L, checkButton);
}

void loop() {
  Blynk.run();   // Jalankan Blynk
  timer.run();   // Jalankan timer
}