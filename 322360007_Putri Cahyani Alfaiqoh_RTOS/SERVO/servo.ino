#include <Arduino.h>
#include <Servo.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

Servo myServo;

TaskHandle_t TaskCore0;
TaskHandle_t TaskCore1;

void TaskServoCW(void *pvParameters) {
  while (true) {
    for (int pos = 0; pos <= 180; pos += 10) {
      myServo.write(pos);
      Serial.printf("[Core %d] Servo ke %d° (CW)\n", xPortGetCoreID(), pos);
      vTaskDelay(pdMS_TO_TICKS(500));
    }
  }
}

void TaskServoCCW(void *pvParameters) {
  while (true) {
    for (int pos = 180; pos >= 0; pos -= 10) {
      myServo.write(pos);
      Serial.printf("[Core %d] Servo ke %d° (CCW)\n", xPortGetCoreID(), pos);
      vTaskDelay(pdMS_TO_TICKS(500));
    }
  }
}

void setup() {
  Serial.begin(115200);
  myServo.attach(15); // Gunakan pin GPIO 15 untuk sinyal servo

  Serial.println("ESP32 FreeRTOS Servo Dual Core Demo");

  // Task untuk memutar searah jarum jam di Core 0
  xTaskCreatePinnedToCore(TaskServoCW, "TaskServoCW", 2048, NULL, 1, &TaskCore0, 0);

  // Task untuk memutar berlawanan arah jarum jam di Core 1
  xTaskCreatePinnedToCore(TaskServoCCW, "TaskServoCCW", 2048, NULL, 1, &TaskCore1, 1);
}

void loop() {
  // kosong, semua kerja di task FreeRTOS
}
