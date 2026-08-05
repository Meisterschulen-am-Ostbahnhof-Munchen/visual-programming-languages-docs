# OFFSET_UDINT

<img width="1747" height="246" alt="image" src="https://github.com/user-attachments/assets/03bc479b-bcf2-4609-90d0-c235966f16a4" />

* * * * * * * * * *
## Introduction
The function block `OFFSET_UDINT` is used to calculate an offset value. On the first execution with an input value greater than zero, the block stores this value as a reference (`FIRST`). On each subsequent call, the difference between the current input value and this stored reference value is calculated as the output (`OUT`). This is particularly useful for determining relative changes compared to an initial starting value.

![OFFSET_UDINT](OFFSET_UDINT.svg)

## Interface Structure

### **Event Inputs**

* **REQ**: Starts the normal execution of the algorithm. Linked to the data input `IN`.


### **Event Outputs**

* **CNF**: Signals the completion of the calculation. Linked to the data outputs `OUT` and `FIRST`.

### **Data Inputs**

* **IN** (UDINT): The input value. On the first call with a value > 0, this value is stored in `FIRST`. The initial value is `0`.

### **Data Outputs**

* **OUT** (UDINT): The result of the calculation `IN - FIRST`. The initial value is `0`.

* **FIRST** (UDINT): The reference value stored on the first call (with `IN` > 0). The initial value is `0`.

### **Adapters**
This function block does not use any adapters.

## Functionality
The `OFFSET_UDINT` is a simple function block (Simple FB) with a single state (`REQ`). Whenever the `REQ` event occurs, the associated algorithm `REQ` is executed.

The algorithm first checks whether the output `FIRST` still has the initial value `0`. If so, the current value of `IN` is stored in `FIRST`. The difference `OUT = IN - FIRST` is then calculated. After the calculation is complete, the `CNF` event is triggered, outputting the updated values of `OUT` and `FIRST`.

**Important:** The check `FIRST = 0` ensures that the value is only set on the *first* call where `IN` has a value greater than 0. A subsequent `IN` call from `0` will no longer change `FIRST`.

## Technical Features
* **Data Type:** The block works exclusively with unsigned 32-bit integers (`UDINT`).

* **Initialization:** Both `FIRST` and `OUT` are initialized with `0`. The block is ready for operation immediately after startup.

* **One-Time Setting:** The variable `FIRST` is set exactly once (on the first `REQ` with `IN` > 0) and then remains constant for the lifetime of the function block instance, unless the function block is reinitialized.


* ## State Overview

The function block has a single, stable state:

* **REQ:** Waits for the incoming `REQ` event. Upon receipt, the algorithm is executed, and immediately afterward, the `CNF` event is triggered. The function block remains in the `REQ` state.

## Application Scenarios

* **Reference Point Establishment in Measurement Chains:** In a system that provides absolute position values (e.g., from an encoder), this block can store the first valid measurement as the zero point (offset). All subsequent values are output relative to this starting point.

* **Initial Value Compensation:** To eliminate a system-related default offset (e.g., a bias) during the first valid measurement.

* **Counter Start Normalization:** If a counter does not start at 0, the first value can be stored and subtracted from all subsequent values to simulate counting from 0.

## ⚖️ Comparison with Similar Blocks

* **SUB / DIF Blocks:** Standard subtraction blocks always calculate the difference between two variable inputs. `OFFSET_UDINT`, however, freezes one of the operands (`FIRST`) after the first operation and uses it as a fixed subtrahend thereafter.

* **Shift Registers (FIFO) or Delay Blocks:** These store a history of values. `OFFSET_UDINT`, on the other hand, only permanently stores a single, initial value.

* **Blocks with Markers (SR, RS):** These store a binary state. `OFFSET_UDINT` stores a specific numeric (`UDINT`) starting value.

## 🛠️ Related Exercises

* [Exercise_072c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_072c.md)]

## Conclusion
The `OFFSET_UDINT` function block is a specialized and efficient function block for applications where a single measured starting value serves as the basis for all subsequent relative calculations. Its strength lies in its simplicity and the reliable, one-time setting of the reference value, eliminating the need for manual logic to detect the "first cycle." It is ideal for initialization and normalization tasks in control applications.