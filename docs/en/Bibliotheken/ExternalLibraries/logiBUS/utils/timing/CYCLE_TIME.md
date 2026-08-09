# CYCLE_TIME

<img width="1186" height="212" alt="image" src="https://github.com/user-attachments/assets/9a52222d-13af-45a6-94bb-67de45036241" />
* * * * * * * * * *
## Introduction

The function block `CYCLE_TIME` is used to calculate the elapsed time between two consecutive calls. It is a useful tool for monitoring and diagnosing cycle times in real-time applications, for example, for performance analysis or for detecting unexpected delays in a control system.
![CYCLE_TIME](CYCLE_TIME.svg)
## Interface Structure

### **Event Inputs**

* **REQ**: Starts the cycle time calculation. The algorithm is executed upon this event.

### **Event Outputs**

* **CNF**: Triggered as soon as the calculation is complete. This event confirms execution and delivers the calculated values to the data outputs.

### **Data Inputs**

* **TM** (DINT): Provides the current timestamp at the time of the call. This value is typically supplied by a system clock or a timer block. The initial value is `0`.

### **Data Outputs**

* **CYCLE** (DINT): Contains the calculated cycle time, i.e., the difference between the current (`TM`) and the previous timestamp (`LAST`). The initial value is `0`.
* **LAST** (DINT): Stores the timestamp of the last call (`TM`). This value is used for the next calculation. The initial value is `0`.

### **Adapters**

This function block does not have any adapter interfaces.

## Functionality

Whenever the `REQ` event occurs, the corresponding algorithm `REQ` is executed. This algorithm performs two essential operations:

1. **Calculation of the cycle time**: The difference between the newly received time value `TM` and the stored value `LAST` (from the previous call) is calculated and output to `CYCLE`.
2. **Update of the timestamp**: The current input value `TM` is saved in the internal memory `LAST` for the next calculation cycle.

Immediately after the algorithm executes, the `CNF` event is triggered with the updated values at `CYCLE` and `LAST`.

## Technical Features

* The function block is a **Simple Function Block (Basic FB)** according to IEC 61499.
* The data types used (`DINT`) are signed 32-bit integers suitable for representing large time values (e.g., in milliseconds or microseconds).
* The initial values of `TM`, `CYCLE`, and `LAST` are set to `0`. The first valid `CYCLE` value after startup is therefore the difference `TM - 0`. This should be taken into account in the application's initialization logic.

## State Overview

The function block has a single Execution Control State (EC State) named `REQ`. Upon entering this state, the algorithm `REQ` is always executed, followed by the `CNF` event.

## Application Scenarios

* **Cycle Time Monitoring**: Continuous measurement of the execution time of a program or a specific program segment.
* **Performance Monitoring**: Identification of bottlenecks or unusually long cycle times in a control application.
* **Diagnostics**: Logging cycle times for analysis or to generate system runtime statistics.
* **Adaptive Control**: Providing the current cycle time for algorithms whose behavior depends on the available processing time.

## ⚖️ Comparison with similar modules

Compared to generic timing modules (such as `E_DELAY` or `E_CYCLE`), `CYCLE_TIME` specializes in **calculating the difference between consecutive time points**. It does not use its own timer but evaluates externally provided timestamps. Modules such as `E_SR` or `E_R_TRIG` serve fundamentally different purposes (storage, edge detection) and do not offer time difference calculation.

## 🛠️ Related Exercises

* [Exercise_072c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_072c.md)

## Conclusion

The `CYCLE_TIME` function block is a simple yet effective tool for runtime measurement in IEC 61499-based control systems. Its clear interface and straightforward operation make it a robust component for diagnostic and monitoring tasks where the accuracy and reliability of cycle time measurement are paramount.
