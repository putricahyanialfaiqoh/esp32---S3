#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C  // Alamat OLED di Wokwi

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

TaskHandle_t TaskCore0;
TaskHandle_t TaskCore1;
SemaphoreHandle_t xOLEDMutex;

// --- Task untuk Core 0 ---
void Task0(void *pvParameters) {
  for (;;) {
    if (xSemaphoreTake(xOLEDMutex, portMAX_DELAY)) {
      Serial.printf("Task0 jalan di Core %d\n", xPortGetCoreID());
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(10, 20);
      display.println("CORE 0: aktif");
      display.display();
      xSemaphoreGive(xOLEDMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));  // delay 2 detik
  }
}

// --- Task untuk Core 1 ---
void Task1(void *pvParameters) {
  for (;;) {
    if (xSemaphoreTake(xOLEDMutex, portMAX_DELAY)) {
      Serial.printf("Task1 jalan di Core %d\n", xPortGetCoreID());
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(10, 20);
      display.println("CORE 1: aktif");
      display.display();
      xSemaphoreGive(xOLEDMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(3000));  // delay 3 detik
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(17, 18);  // SDA=17, SCL=18 (ESP32-S3 default di Wokwi)

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("Gagal inisialisasi OLED!");
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("OLED Ready!");
  display.display();
  delay(1000);

  xOLEDMutex = xSemaphoreCreateMutex();

  // Buat dua task di core berbeda
  xTaskCreatePinnedToCore(Task0, "Task0", 4096, NULL, 1, &TaskCore0, 0);
  xTaskCreatePinnedToCore(Task1, "Task1", 4096, NULL, 1, &TaskCore1, 1);
}

void loop() {
  // kosong
}
