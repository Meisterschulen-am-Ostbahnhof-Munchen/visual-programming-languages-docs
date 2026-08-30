# F_TIME_IN_US_TO_LINT

<img width="1522" height="212" alt="F_TIME_IN_US_TO_LINT" src="https://github.com/user-attachments/assets/ec011268-cf2a-49c0-8b92-65bb95c903f0" />
* * * * * * * * * *
## Introduction

The function block `F_TIME_IN_US_TO_LINT` converts a TIME value in microseconds (µs) into a LINT value (64-bit integer). This conversion is useful when time values are needed in numerical calculations or for further processing.
![F_TIME_IN_US_TO_LINT](F_TIME_IN_US_TO_LINT.svg)
## Interface Structure

### **Event Inputs**

- `REQ` (Normal Execution Request): Starts the execution of the function block. Linked to input `IN`.

### **Event Outputs**

- `CNF` (Execution Confirmation): Signals the completion of the conversion. Linked to output `OUT`.

### **Data Inputs**

- `IN` (TIME): The input value in microseconds (µs) to be converted into a LINT value.

### **Data Outputs**

- `OUT` (LINT): The converted 64-bit integer value.

### **Adapters**

This function block does not use adapters.

## Functionality

The function block performs the conversion by transforming the TIME input value (`IN`) in microseconds into a LINT value (`OUT`). The conversion occurs when the `REQ` event is triggered and is confirmed by the `CNF` event.

## Technical Features

- The algorithm uses the function `TIME_IN_US_TO_LINT` to perform the conversion.
- The function block is suitable for use in real-time applications.

## State Overview

The function block has a simple state machine:

1. **Idle State**: Waits for the `REQ` event.
2. **Execution State**: Performs the conversion and triggers the `CNF` event.

## Application Scenarios

- Time measurement and processing in control systems.
- Integration of time values into numerical calculations.
- Logging and analysis of time durations.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block does not usually exist, as this is elegantly solved using multiplication.

Use the function block **`F_MULTIME`** (from the category `arithmetic`) for this:

- Multiply your numeric value by the desired time base.
- **Example:** `500 * T#1ms = T#500ms`
- This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with similar function blocks

- Compared to other conversion function blocks, this one is specifically optimized for converting TIME to LINT.
- Similar function blocks might use different data types or units, e.g., milliseconds instead of microseconds.

## Conclusion

The `F_TIME_IN_US_TO_LINT` function block provides an efficient and reliable way to convert time values in microseconds to 64-bit integers. Its simple interface and clear functionality make it ideal for a wide range of applications in automation technology.
