# SCALE

<img width="668" height="239" alt="SCALE" src="https://github.com/user-attachments/assets/b3a2d282-98ec-47f2-a311-70f4d8aa9d90" />

* * * * * * * * * *
## Introduction
The SCALE function block is used to scale an input value from an input range to an output range. This is particularly useful in signal processing when values from one measurement range need to be transformed into another.

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the scaling operation. It is linked to the data inputs IN, MAX_IN, MIN_IN, MAX_OUT, and MIN_OUT.

### **Event Outputs**

- **CNF**: Signals the completion of the scaling operation.

### **Data Inputs**

- **IN**: The input value to be scaled (REAL).

- **MAX_IN**: The maximum value of the input range (REAL).

- **MIN_IN**: The minimum value of the input range (REAL).

- **MAX_OUT**: The maximum value of the output range (REAL).

- **MIN_OUT**: The minimum value of the output range (REAL).

### **Data Outputs**

- **(unnamed)**: The scaled output value (REAL).

### **Adapters**
No adapters available.

## Functionality
The SCALE function block calculates the scaled value using the following formula:

```
SCALE := (IN - MIN_IN) * (MAX_OUT - MIN_OUT) / (MAX_IN - MIN_IN) + MIN_OUT;
```
This formula linearly transforms the input value from the input range [MIN_IN, MAX_IN] to the output range [MIN_OUT, MAX_OUT].

## Technical Features
- The function block is implemented in ST (Structured Text).

- The calculation is performed in a single step, ensuring high efficiency.

- No state management is required, as this is a static transformation.

## State Overview

The function block has no internal states. The operation is re-executed with each REQ event.

## Application Scenarios
- Scaling of sensor values (e.g., from 4-20 mA to 0-100%).

- Transformation of measured values for display or further processing.

- General signal processing in industrial control systems.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other scaling function blocks, SCALE is particularly easy and straightforward to use.

- No additional parameters or complex settings are required.

Ideal for simple linear scaling without additional logic.

## 🛠️ Related Exercises

* [Exercise_042](../../../Uebungen/test_B/Uebungen_doc/Uebung_042.md)

## Conclusion
The SCALE function block offers an efficient and simple solution for linear scaling tasks. Its clear interface and direct implementation make it a valuable component in signal processing.