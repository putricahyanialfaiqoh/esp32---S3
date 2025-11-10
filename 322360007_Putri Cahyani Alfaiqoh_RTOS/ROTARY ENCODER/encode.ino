    #include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// ==================== Pin Definisi ====================
#define CLK_PIN 15
#define DT_PIN  16
#define SW_PIN  17

// ==================== Variabel Global ====================
volatile int encoderValue = 0;
int lastCLKState;
int lastSWState;

// Task handle untuk monitoring
TaskHandle_t TaskEncoderCore0;
TaskHandle_t TaskButtonCore1;

// ==================== CORE 0: Rotary Encoder ====================
void TaskEncoder(void *pvParameters) {
  Serial.printf("[Core %d] Encoder Task Started\n", xPortGetCoreID());
  for (;;) {
    int currentCLK = digitalRead(CLK_PIN);
    int currentDT  = digitalRead(DT_PIN);

    if (currentCLK != lastCLKState) {
      if (currentDT != currentCLK) encoderValue++;
      else encoderValue--;
      Serial.printf("[Core %d] Encoder Value: %d\n", xPortGetCoreID(), encoderValue);
    }

    lastCLKState = currentCLK;
    vTaskDelay(pdMS_TO_TICKS(5)); // delay kecil biar responsif
  }
}

// ==================== CORE 1: Button Press ====================
void TaskButton(void *pvParameters) {
  Serial.printf("[Core %d] Button Task Started\n", xPortGetCoreID());
  for (;;) {
    int currentSW = digitalRead(SW_PIN);

    if (lastSWState == HIGH && currentSW == LOW) {
      encoderValue++; // tombol menaikkan nilai encoder
      Serial.printf("[Core %d] BUTTON PRESSED → Encoder Value: %d\n",
                    xPortGetCoreID(), encoderValue);
      vTaskDelay(pdMS_TO_TICKS(300)); // debounce
    }

    lastSWState = currentSW;
    vTaskDelay(pdMS_TO_TICKS(10)); // jeda kecil
  }
}

// ==================== SETUP ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== Dual-Core FreeRTOS Encoder + Button Demo ===");

  // Inisialisasi pin
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);

  lastCLKState = digitalRead(CLK_PIN);
  lastSWState  = digitalRead(SW_PIN);

  // Buat Task di masing-masing core
  xTaskCreatePinnedToCore(
    TaskEncoder,        // fungsi task
    "EncoderTask",      // nama task
    2048,               // stack size
    NULL,               // parameter
    1,                  // prioritas
    &TaskEncoderCore0,  // handle
    0                   // Core 0
  );

  xTaskCreatePinnedToCore(
    TaskButton,
    "ButtonTask",
    2048,
    NULL,
    1,
    &TaskButtonCore1,
    1                   // Core 1
  );
}

// ==================== LOOP ====================
void loop() {
  // Kosong, semua dijalankan di task
}
