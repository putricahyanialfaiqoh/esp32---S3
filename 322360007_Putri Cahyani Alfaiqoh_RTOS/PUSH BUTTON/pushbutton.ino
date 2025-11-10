#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ==================== PIN DEFINISI ====================
#define BUTTON_PIN 15   // Tombol ke GPIO 15
#define LED_PIN    5  // LED ke GPIO 2

// ==================== VARIABEL GLOBAL ====================
volatile bool buttonPressed = false;  // Flag ditekan (akses antar core)
volatile int ledState = LOW;          // Status LED (OFF = 0, ON = 1)

// ==================== HANDLE UNTUK TASK ====================
TaskHandle_t TaskCore0;  // Membaca tombol (input)
TaskHandle_t TaskCore1;  // Mengontrol LED (output)

// ==================== TASK CORE 0: Pembaca Tombol ====================
void TaskButton(void *pvParameters) {
  int lastButtonState = HIGH;
  int currentButtonState = HIGH;

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.printf("[Core %d] Button Task Started\n", xPortGetCoreID());

  for (;;) {
    lastButtonState = currentButtonState;
    currentButtonState = digitalRead(BUTTON_PIN);

    // Jika ada transisi dari HIGH → LOW (tombol ditekan)
    if (lastButtonState == HIGH && currentButtonState == LOW) {
      buttonPressed = true;
      Serial.println("[Core 0] Button Pressed");
    }

    vTaskDelay(pdMS_TO_TICKS(50)); // debounce delay
  }
}

// ==================== TASK CORE 1: Pengontrol LED ====================
void TaskLED(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);

  Serial.printf("[Core %d] LED Task Started\n", xPortGetCoreID());

  for (;;) {
    // Jika tombol ditekan (flag dari core 0)
    if (buttonPressed) {
      ledState = !ledState;  // toggle LED
      digitalWrite(LED_PIN, ledState);

      Serial.printf("[Core 1] LED is now %s\n", ledState ? "ON" : "OFF");
      buttonPressed = false; // reset flag
    }

    vTaskDelay(pdMS_TO_TICKS(10)); // waktu idle antar loop
  }
}

// ==================== SETUP ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== ESP32-S3 Dual-Core FreeRTOS: Button + LED Demo ===");

  // Membuat task untuk masing-masing core
  xTaskCreatePinnedToCore(
    TaskButton,       // fungsi task
    "TaskButton",     // nama task
    2048,             // ukuran stack
    NULL,             // parameter
    1,                // prioritas
    &TaskCore0,       // handle task
    0                 // dijalankan di core 0
  );

  xTaskCreatePinnedToCore(
    TaskLED,
    "TaskLED",
    2048,
    NULL,
    1,
    &TaskCore1,
    1                 // dijalankan di core 1
  );
}

// ==================== LOOP ====================
void loop() {
  // Kosong — semua dijalankan di task
}
