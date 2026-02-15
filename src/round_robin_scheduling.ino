#include <Arduino.h>

// ---------- LOG CONTROL ----------
volatile int logCount = 0;
const int MAX_LOGS = 500;

// ---------- CSV LOGGER ----------
void logCSV(const char* taskName, const char* priorityOrDeadline, unsigned long execTime) {
  if (logCount >= MAX_LOGS) return;

  Serial.print(millis());
  Serial.print(",");
  Serial.print(taskName);
  Serial.print(",");
  Serial.print(priorityOrDeadline);
  Serial.print(",");
  Serial.println(execTime);

  logCount++;

  // Auto-stop after MAX_LOGS
  if (logCount >= MAX_LOGS) {
    Serial.println("=== LOGGING COMPLETE ===");
    vTaskSuspend(NULL); // suspend the current task
  }
}

// ---------- GAS TASK (ROUND ROBIN) ----------
void GasTask(void *pvParameters) {
  while (1) {
    unsigned long startTime = millis();

    // Simulated gas sensor workload
    delay(15);

    unsigned long execTime = millis() - startTime;
    logCSV("GasTask", "SAME", execTime);

    // Same period to encourage time slicing
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// ---------- TEMP TASK (ROUND ROBIN) ----------
void TempTask(void *pvParameters) {
  while (1) {
    unsigned long startTime = millis();

    // Simulated temperature sensor workload
    delay(8);

    unsigned long execTime = millis() - startTime;
    logCSV("TempTask", "SAME", execTime);

    // Same period to encourage time slicing
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  // CSV Header (must match Google Sheet)
  Serial.println("Timestamp_ms,Task_Name,Priority_or_Deadline,Exec_Time_ms");

  // -------- ROUND ROBIN: SAME PRIORITY --------
  xTaskCreate(GasTask,  "GasTask",  2048, NULL, 2, NULL);
  xTaskCreate(TempTask, "TempTask", 2048, NULL, 2, NULL);
}

void loop() {
  // RTOS scheduler controls execution
}
