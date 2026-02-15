# Results and Analysis

This document presents the analysis of experimental results obtained from
different RTOS scheduling algorithms executed on the ESP32 platform.

---

## 1. Overview of Collected Data

For each scheduling algorithm, the following metrics were collected:

- Total execution time of all tasks
- Total runtime duration
- CPU active percentage
- CPU idle percentage

Each experiment consists of 500 logged task executions.

---

## 2. CPU Utilization Analysis

CPU utilization is calculated using the formula:

CPU_Active (%) = (Total_Execution_Time / Total_Runtime) × 100  
CPU_Idle (%) = 100 − CPU_Active (%)

This provides an indirect measure of system load.

---

## 3. Priority Scheduling Results

- CPU Active Percentage: Low
- CPU Idle Percentage: High
- High-priority task consistently preempts low-priority task
- Suitable for time-critical systems

Observation:
Priority scheduling ensures deterministic execution but may cause starvation
if not managed carefully.

---

## 4. Round Robin Scheduling Results

- CPU Active Percentage: Higher than priority scheduling
- Fair distribution among tasks
- Context switching overhead observed

Observation:
Round Robin improves fairness but slightly increases CPU overhead.

---

## 5. Earliest Deadline First (EDF) Results

- CPU Idle Percentage: Highest among all
- Efficient task execution under periodic deadlines
- Predictable behavior for real-time workloads

Observation:
EDF performs well for periodic real-time systems with known deadlines.

---

## 6. Comparative Summary

| Algorithm   | CPU Active | CPU Idle | Scheduling Behavior       |
| ----------- | ---------- | -------- | ------------------------- |
| Priority    | Low        | High     | Deterministic, preemptive |
| Round Robin | Medium     | Medium   | Fair, time-sliced         |
| EDF         | Low        | High     | Deadline-aware            |

---

## 7. Energy Efficiency Implications

Higher CPU idle time implies lower power consumption.

- EDF shows best energy efficiency
- Priority scheduling is acceptable for critical tasks
- Round Robin trades efficiency for fairness

---

## 8. Limitations of Analysis

- Power consumption is estimated, not directly measured
- Sensor workloads are simulated
- Results may vary with real sensor I/O and interrupts

---

## 9. Conclusion

The experiment demonstrates that scheduling choice significantly impacts
CPU utilization and system efficiency.

- Priority Scheduling is best for strict real-time constraints
- Round Robin ensures fairness at the cost of overhead
- EDF provides balanced performance and energy efficiency

---

## 10. Future Work

- Integrate real sensors
- Measure actual power consumption
- Add more complex task sets
- Extend analysis to multicore scheduling
