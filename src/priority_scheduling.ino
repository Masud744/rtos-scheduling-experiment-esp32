#include <Arduino.h>

// ---------- LOG CONTROL ----------
volatile int logCount = 0;
const int MAX_LOGS = 500;

// ---------- CSV Logger ----------
void logCSV(const char* taskName, const char* priority, unsigned long execTime) {
  if (logCount >= MAX_LOGS) return;

  Serial.print(millis());
  Serial.print(",");
  Serial.print(taskName);
  Serial.print(",");
  Serial.print(priority);
  Serial.print(",");
  Serial.println(execTime);

  logCount++;

  // Stop everything after 500 logs
  if (logCount >= MAX_LOGS) {
    Serial.println("=== LOGGING COMPLETE ===");
    vTaskSuspend(NULL);  // suspend current task
  }
}

// ---------- GAS SENSOR TASK (HIGH PRIORITY) ----------
void GasTask(void *pvParameters) {
  while (1) {
    unsigned long startTime = millis();

    delay(15);  // Simulated gas sensor read

    unsigned long execTime = millis() - startTime;
    logCSV("GasTask", "HIGH", execTime);

    vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second period
  }
}

// ---------- TEMP SENSOR TASK (LOW PRIORITY) ----------
void TempTask(void *pvParameters) {
  while (1) {
    unsigned long startTime = millis();

    delay(8); // Simulated temperature sensor read

    unsigned long execTime = millis() - startTime;
    logCSV("TempTask", "LOW", execTime);

    vTaskDelay(pdMS_TO_TICKS(5000)); // 5 second period
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("Timestamp_ms,Task_Name,Priority_or_Deadline,Exec_Time_ms");

  xTaskCreate(GasTask, "GasTask", 2048, NULL, 3, NULL);
  xTaskCreate(TempTask, "TempTask", 2048, NULL, 1, NULL);
}

void loop() {
  // RTOS handles execution
}
