#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ==================== PIN DEFINISI ====================
#define POT_PIN 4  // pin analog potensiometer

// ==================== TASK HANDLES ====================
TaskHandle_t TaskCore0;  // membaca potensiometer
TaskHandle_t TaskCore1;  // menampilkan pesan sistem

// ==================== TASK CORE 0 ====================
// Membaca nilai analog potensiometer
void Core0Task(void *pvParameters) {
  for (;;) {
    int potValue = analogRead(POT_PIN);
    Serial.printf("[Core %d] Potentiometer Value: %d\n", xPortGetCoreID(), potValue);
    vTaskDelay(200 / portTICK_PERIOD_MS); // baca setiap 200 ms
  }
}

// ==================== TASK CORE 1 ====================
// Menampilkan pesan sistem tiap beberapa detik
void Core1Task(void *pvParameters) {
  for (;;) {
    Serial.printf("[Core %d] System Running Smoothly...\n", xPortGetCoreID());
    vTaskDelay(3000 / portTICK_PERIOD_MS); // tampil tiap 3 detik
  }
}

// ==================== SETUP ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32-S3 Dual Core FreeRTOS Potentiometer Only Demo");

  // Jalankan task di core berbeda
  xTaskCreatePinnedToCore(Core0Task, "Core0Task", 2048, NULL, 1, &TaskCore0, 0); // Core 0
  xTaskCreatePinnedToCore(Core1Task, "Core1Task", 2048, NULL, 1, &TaskCore1, 1); // Core 1
}

// ==================== LOOP ====================
void loop() {
  // kosong — semua dijalankan lewat task
}
