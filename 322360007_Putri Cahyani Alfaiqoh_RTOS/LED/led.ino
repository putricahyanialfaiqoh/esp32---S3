#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ==================== DEFINISI PIN ====================
#define LED1 4   // LED di Core 1 (utama)
#define LED2 5   // LED di Core 0
#define LED3 6   // LED tambahan di Core 1

// ==================== HANDLE TASK ====================
TaskHandle_t TaskCore0;
TaskHandle_t TaskCore1;

// ==================== TASK CORE 0 ====================
// LED2 di Core 0 (kedip cepat)
void Core0Task(void *pvParameters) {
  pinMode(LED2, OUTPUT);
  for (;;) {
    digitalWrite(LED2, HIGH);
    Serial.printf("[Core %d] LED2 ON\n", xPortGetCoreID());
    vTaskDelay(300 / portTICK_PERIOD_MS);

    digitalWrite(LED2, LOW);
    Serial.printf("[Core %d] LED2 OFF\n", xPortGetCoreID());
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

// ==================== TASK CORE 1 ====================
// LED1 dan LED3 di Core 1 (bergantian)
void Core1Task(void *pvParameters) {
  pinMode(LED1, OUTPUT);
  pinMode(LED3, OUTPUT);

  for (;;) {
    // LED1 ON - LED3 OFF
    digitalWrite(LED1, HIGH);
    digitalWrite(LED3, LOW);
    Serial.printf("[Core %d] LED1 ON | LED3 OFF\n", xPortGetCoreID());
    vTaskDelay(500 / portTICK_PERIOD_MS);

    // LED1 OFF - LED3 ON
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, HIGH);
    Serial.printf("[Core %d] LED1 OFF | LED3 ON\n", xPortGetCoreID());
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// ==================== SETUP ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32-S3 Dual-Core 3 LED (FreeRTOS) Demo");

  // Buat task untuk masing-masing core
  xTaskCreatePinnedToCore(
    Core0Task,         // fungsi task
    "Core0Task",       // nama task
    2048,              // ukuran stack (byte)
    NULL,              // parameter
    1,                 // prioritas
    &TaskCore0,        // handle
    0                  // dijalankan di Core 0
  );

  xTaskCreatePinnedToCore(
    Core1Task,
    "Core1Task",
    2048,
    NULL,
    1,
    &TaskCore1,
    1                  // dijalankan di Core 1
  );
}

// ==================== LOOP ====================
void loop() {
  // Tidak digunakan, karena semua dijalankan oleh FreeRTOS Task
}
