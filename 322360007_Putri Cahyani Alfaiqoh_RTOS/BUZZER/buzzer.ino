#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUZZER_PIN 13  // Pin buzzer aktif HIGH

TaskHandle_t TaskCore0;
TaskHandle_t TaskCore1;

// ===== CORE 0: Buzzer Lambat =====
void Core0Task(void *pvParameters) {
  for (;;) {
    tone(BUZZER_PIN, 800); // frekuensi 800 Hz
    Serial.printf("[Core %d] Buzzer Slow Beep (800 Hz)\n", xPortGetCoreID());
    vTaskDelay(500 / portTICK_PERIOD_MS); // bunyi 0.5 detik
    noTone(BUZZER_PIN);
    vTaskDelay(500 / portTICK_PERIOD_MS); // diam 0.5 detik
  }
}

// ===== CORE 1: Buzzer Cepat =====
void Core1Task(void *pvParameters) {
  for (;;) {
    tone(BUZZER_PIN, 1200); // frekuensi 1200 Hz
    Serial.printf("[Core %d] Buzzer Fast Beep (1200 Hz)\n", xPortGetCoreID());
    vTaskDelay(200 / portTICK_PERIOD_MS); // bunyi 0.2 detik
    noTone(BUZZER_PIN);
    vTaskDelay(200 / portTICK_PERIOD_MS); // diam 0.2 detik
  }
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32-S3 Dual Core FreeRTOS Buzzer (Normal Mode)");

  pinMode(BUZZER_PIN, OUTPUT);

  // Jalankan task di dua core berbeda
  xTaskCreatePinnedToCore(Core0Task, "Core0Task", 2048, NULL, 1, &TaskCore0, 0); // Core 0
  xTaskCreatePinnedToCore(Core1Task, "Core1Task", 2048, NULL, 1, &TaskCore1, 1); // Core 1
}

void loop() {
  // Kosong, semua dijalankan oleh task
}
