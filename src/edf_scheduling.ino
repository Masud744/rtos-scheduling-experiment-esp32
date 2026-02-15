#include <Arduino.h>

// ---------- LOG CONTROL ----------
volatile int logCount = 0;
const int MAX_LOGS = 500;

// ---------- CSV LOGGER ----------
void logCSV(const char* taskName, const char* deadline, unsigned long execTime) {
  if (logCount >= MAX_LOGS) return;

  Serial.print(millis());
  Serial.print(",");
  Serial.print(taskName);
  Serial.print(",");
  Serial.print(deadline);
  Serial.print(",");
  Serial.println(execTime);

  logCount++;

  // Auto-stop after MAX_LOGS
  if (logCount >= MAX_LOGS) {
    Serial.println("=== LOGGING COMPLETE ===");
    vTaskSuspend(NULL); // suspend current task
  }
}

// ---------- GAS TASK (EDF: SHORT DEADLINE) ----------
void GasTask(void *pvParameters) {
  while (1) {
    unsigned long startTime = millis();

    // Simulated gas sensor workload
    delay(15);

    unsigned long execTime = millis() - startTime;
    logCSV("GasTask", "1s", execTime);

    // Period aligned with deadline
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// ---------- TEMP TASK (EDF: LONG DEADLINE) ----------
void TempTask(void *pvParameters) {
  while (1) {
    unsigned long startTime = millis();

    // Simulated temperature sensor workload
    delay(8);

    unsigned long execTime = millis() - startTime;
    logCSV("TempTask", "5s", execTime);

    // Period aligned with deadline
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  // CSV Header (same structure)
  Serial.println("Timestamp_ms,Task_Name,Priority_or_Deadline,Exec_Time_ms");

  // -------- EDF via Priority Mapping --------
  // Shorter deadline -> higher priority
  xTaskCreate(GasTask,  "GasTask",  2048, NULL, 3, NULL); // higher priority
  xTaskCreate(TempTask, "TempTask", 2048, NULL, 1, NULL); // lower priority
}

void loop() {
  // RTOS scheduler controls execution
}
