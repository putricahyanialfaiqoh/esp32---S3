#include <Arduino.h>
#include <AccelStepper.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Stepper Pins
#define STEP_PIN 18
#define DIR_PIN 19
#define EN_PIN 20

// Button Pin
#define BTN_PIN 12

// Stepper object (driver mode)
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// Flag & state
volatile bool motorDirection = true; // true = kanan, false = kiri
bool lastBtn = HIGH;

// Batas posisi
const long MAX_POS = 800;
const long MIN_POS = 0;

// Task handles
TaskHandle_t TaskStepper;
TaskHandle_t TaskButton;

void taskStepper(void *pvParameters) {
  while (1) {
    stepper.run(); 
    vTaskDelay(1);
  }
}

void taskButton(void *pvParameters) {
  while (1) {
    bool readBtn = digitalRead(BTN_PIN);

    if (readBtn == LOW && lastBtn == HIGH) {
      motorDirection = !motorDirection;  

      long currentPos = stepper.currentPosition();
      long targetPos = (motorDirection) ? MAX_POS : MIN_POS;

      stepper.moveTo(targetPos);

      Serial.print("Arah: ");
      Serial.println(motorDirection ? ">> Kanan" : "<< Kiri");

      vTaskDelay(200 / portTICK_PERIOD_MS);
    }

    lastBtn = readBtn;

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);

  pinMode(BTN_PIN, INPUT_PULLUP);

  stepper.setMaxSpeed(900);
  stepper.setAcceleration(400);

  xTaskCreatePinnedToCore(taskStepper, "StepperTask", 4096, NULL, 2, &TaskStepper, 1);
  xTaskCreatePinnedToCore(taskButton, "ButtonTask", 4096, NULL, 1, &TaskButton, 0);

  Serial.println("Sistem Siap — Tekan tombol untuk ganti arah");
}

void loop() {}
