# F_TIME_IN_US_TO_LREAL
<img width="1536" height="212" alt="F_TIME_IN_US_TO_LREAL" src="https://github.com/user-attachments/assets/ece70afa-d5af-4a67-a95e-e1c2a79fc167" />
* * * * * * * * * *
## Introduction
The function block `F_TIME_IN_US_TO_LREAL` converts a time value in microseconds (`TIME`) into a double-precision floating-point number (`LREAL`). This conversion is particularly useful in control applications where time values are needed for further calculations.
![F_TIME_IN_US_TO_LREAL](F_TIME_IN_US_TO_LREAL.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Trigger for the conversion. Upon this event, the input value `IN` is processed, and the result is output to `OUT`.

### **Event Outputs**
- **CNF**: Confirms successful completion of the conversion. This event is output along with the converted value `OUT`.

### **Data Inputs**
- **IN** (`TIME`): The input value in microseconds to be converted to a `LREAL` value.

### **Data Outputs**
- **OUT** (`LREAL`): The converted value as a double-precision floating-point number.

### **Adapters**
This function block does not use adapters.

#
## ## Functionality

The function block performs the conversion by transforming the `TIME` input value `IN` into a `LREAL` value using the function `TIME_IN_US_TO_LREAL`. The result is passed to the output `OUT` and confirmed by the event `CNF`.

## Technical Features
- The conversion is performed directly and without any additional delay.
- The function block is optimized for real-time applications and supports precise time measurements.

## State Overview
The function block has no internal states. The conversion is performed every time the `REQ` event occurs.

## Application Scenarios
- Conversion of time durations for mathematical calculations.
- Integration into control systems that require floating-point values for control algorithms.

## Reverse Conversion (Numeric to TIME)
Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

Use the function block **`F_MULTIME`** (from the category `arithmetic`) for this purpose:

* Multiply your numeric value by the desired time base.

`` * **Example:** `500 * T#1ms = T#500ms`

* This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with Similar Blocks
- Unlike generic conversion blocks, this function block specializes in converting `TIME` to `LREAL` and therefore offers optimized performance.
- Other blocks might have additional parameters or states, which is not the case here.

## Conclusion
The `F_TIME_IN_US_TO_LREAL` function block is an efficient tool for the precise conversion of time values to floating-point numbers. Its simple and direct operation makes it ideal for applications that require fast and accurate conversions.
