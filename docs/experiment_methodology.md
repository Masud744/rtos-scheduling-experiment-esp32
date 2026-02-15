# Experiment Methodology

This document describes the experimental methodology used to evaluate
different RTOS scheduling algorithms on an ESP32-based embedded system.

The goal of this experiment is to analyze how scheduling policies affect
CPU utilization, task execution behavior, and overall system efficiency.

---

## 1. Experimental Objective

The primary objectives of this experiment are:

- To compare different RTOS scheduling algorithms
- To observe task execution timing behavior
- To measure CPU active and idle percentages
- To collect structured execution data for analysis

---

## 2. Hardware Setup

- Microcontroller: ESP32 Dev Module
- Clock Frequency: Default ESP32 configuration
- Power Source: USB
- Sensors: Simulated Gas and Temperature Tasks
- Communication Interface: USB Serial

---

## 3. Software Environment

- Operating System: FreeRTOS (ESP32 built-in)
- Programming Language: C / C++
- Development Tools:
  - Arduino IDE (for firmware upload)
  - Visual Studio Code (for serial monitoring)
- Serial Baud Rate: 115200

---

## 4. Task Design

Two periodic tasks are used to simulate real-world workloads:

### 4.1 GasTask (High Priority)

- Priority: High
- Period: 1000 ms
- Execution Time: ~15 ms
- Represents time-critical sensor data acquisition

### 4.2 TempTask (Low Priority)

- Priority: Low
- Period: 5000 ms
- Execution Time: ~8 ms
- Represents non-critical background sensing

---

## 5. Scheduling Algorithms Evaluated

The following scheduling algorithms were implemented and tested:

1. Priority Scheduling
2. Round Robin Scheduling
3. Earliest Deadline First (EDF)

Each algorithm was tested independently under identical task conditions.

---

## 6. Data Logging Strategy

To ensure clean and analyzable data:

- Tasks output execution logs in CSV format
- Each log entry contains:
  - Timestamp (ms)
  - Task Name
  - Priority or Deadline
  - Execution Time (ms)
- Logging is limited to a fixed number of entries (500)
- Serial output is automatically saved using VS Code Serial Monitor

---

## 7. Experimental Procedure

1. Upload firmware implementing a single scheduling algorithm
2. Start serial monitoring with file logging enabled
3. Allow the system to run until logging limit is reached
4. Save the generated log file
5. Convert log file to CSV format
6. Repeat steps for each scheduling algorithm

---

## 8. Data Integrity Considerations

- Debug messages are excluded from CSV output
- All experiments use identical task parameters
- Arduino IDE is closed during logging to avoid port conflicts
- Logging stops automatically to prevent buffer overflow

---

## 9. Assumptions and Limitations

- Sensor readings are simulated using delays
- Power consumption is estimated indirectly via CPU idle time
- External interrupts and network tasks are not included

---

## 10. Summary

This methodology ensures reproducible, structured, and fair comparison
between RTOS scheduling algorithms, enabling meaningful performance analysis.
