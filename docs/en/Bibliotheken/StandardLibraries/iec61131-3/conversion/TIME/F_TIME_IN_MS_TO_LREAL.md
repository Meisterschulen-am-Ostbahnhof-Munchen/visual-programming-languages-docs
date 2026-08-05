# F_TIME_IN_MS_TO_LREAL
<img width="1520" height="212" alt="F_TIME_IN_MS_TO_LREAL" src="https://github.com/user-attachments/assets/fd32035d-3e73-424b-9bef-32b3ce7a10d8" />
* * * * * * * * * *
## Introduction
The function block `F_TIME_IN_MS_TO_LREAL` is used to convert a TIME value in milliseconds to an LREAL value. This is particularly useful when time values are needed for further calculations or analyses with higher precision.
![F_TIME_IN_MS_TO_LREAL](F_TIME_IN_MS_TO_LREAL.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Normal execution request. Triggers the conversion.

### **Event Outputs**
- **CNF**: Execution confirmation. Triggered after successful conversion.

### **Data Inputs**
- **IN**: Input variable of type `TIME`. The time value to be converted in milliseconds.

### **Data Outputs**
- **OUT**: Output variable of type `LREAL`. The converted value is a floating-point number.

### **Adapters**
- No adapters are available.

## Functionality
The function block performs the conversion by transforming the incoming TIME value in milliseconds into an LREAL value. The conversion is performed using the algorithm `REQ`, which uses the function `TIME_IN_MS_TO_LREAL`.

## Technical Features
- The function block has a simple structure and contains only one algorithm for the conversion.
- The conversion is performed directly and without any additional delay.

## State Overview
The function block has no internal state. The conversion is re-executed with each `REQ` event.

## Application Scenarios
- Conversion of time values for precise calculations.
- Integration into control systems that require floating-point values for time measurements.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

Use the block **`F_MULTIME`** (from the category `arithmetic`) for this purpose:

* Multiply your numeric value by the desired time base.

`` * **Example:** `500 * T#1ms = T#500ms`

* This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with similar function blocks
- Compared to other conversion function blocks, this one is specifically designed for converting TIME to LREAL and therefore offers a simple and direct solution for this use case.

## Conclusion
The `F_TIME_IN_MS_TO_LREAL` function block is a simple and efficient tool for converting time values in milliseconds to floating-point numbers. Its clear interface and direct functionality make it a reliable component in control systems.
