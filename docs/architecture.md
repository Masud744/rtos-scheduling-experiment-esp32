# System Architecture

This document describes the overall system architecture of the
RTOS Scheduling Experiment implemented on the ESP32 platform.

The architecture is designed to experimentally evaluate different
RTOS scheduling algorithms under identical task conditions.

---

## 1. Architectural Overview

The system follows a layered architecture to ensure fairness,
modularity, and reproducibility.

The main architectural layers are:

- Application Layer
- RTOS Scheduling Layer
- Hardware Execution Layer
- Data Logging Layer
- Offline Analysis Layer

---

## 2. High-Level Architecture Diagram

+--------------------------------------------------+

Application Layer
GasTask (High Priority) TempTask (Low Priority)
+---------------------+----------------------------+
|
v
+--------------------------------------------------+

RTOS Scheduling Layer
Priority Scheduling
+---------------------+----------------------------+
|
v
+--------------------------------------------------+

Hardware Execution Layer
ESP32 CPU (FreeRTOS)
+---------------------+----------------------------+
|
v
+--------------------------------------------------+

Data Logging Layer
Serial CSV Logger (USB Serial)
+---------------------+----------------------------+
|
v
+--------------------------------------------------+

Offline Analysis Layer
CSV Dataset → CPU Utilization → Energy Analysis
+--------------------------------------------------+

---

## 3. Application Layer

The application layer consists of periodic tasks that simulate
real-world IoT sensor workloads.

### 3.1 GasTask

- Role: Time-critical sensing task
- Priority: High
- Period: 1000 ms
- Execution Time: Approximately 15 ms
- Behavior: Preempts lower-priority tasks when scheduled

### 3.2 TempTask

- Role: Background sensing task
- Priority: Low
- Period: 5000 ms
- Execution Time: Approximately 8 ms
- Behavior: Executes when CPU resources are available

---

## 4. RTOS Scheduling Layer

The RTOS scheduling layer is implemented using FreeRTOS.

The following scheduling algorithms are evaluated:

- Priority-Based Scheduling
- Round Robin Scheduling
- Earliest Deadline First (EDF)

Each scheduling algorithm is executed independently to avoid
cross-interference and ensure fair comparison.

---

## 5. Hardware Execution Layer

- Platform: ESP32 Dev Module
- Processor: Xtensa Dual-Core (single core utilized)
- Clock Configuration: Default ESP32 settings
- Power Source: USB

The hardware layer executes RTOS-managed tasks and provides
timing support for execution measurements.

---

## 6. Data Logging Architecture

To ensure structured and reliable data collection:

- Task execution data is printed in CSV format
- Serial communication is used for data transfer
- Logging is limited to a fixed number of entries (500)
- VS Code Serial Monitor is used for automatic file logging

Each CSV record contains:

- Timestamp (ms)
- Task Name
- Priority or Deadline
- Execution Time (ms)

---

## 7. Data Analysis Pipeline

The collected CSV data is analyzed offline using spreadsheet tools.

Analysis steps include:

1. Importing CSV logs
2. Calculating total execution time
3. Computing CPU active percentage
4. Computing CPU idle percentage
5. Comparing scheduling algorithms
6. Visualizing results using graphs

---

## 8. Design Rationale

The architecture is designed based on the following principles:

- Modularity: Each layer is logically separated
- Fairness: Identical task parameters across experiments
- Reproducibility: Fixed dataset size and structured logging
- Simplicity: Minimal overhead beyond scheduling logic

---

## 9. Scalability and Future Extensions

The architecture can be extended to:

- Add additional RTOS tasks
- Integrate real hardware sensors
- Measure actual power consumption
- Explore multicore scheduling behavior
- Include network and interrupt-driven workloads

---

## 10. Summary

This system architecture provides a clean, extensible, and
experimentally sound framework for evaluating RTOS scheduling
algorithms on embedded systems using real execution data.
