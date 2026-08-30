# F_TIME_IN_NS_TO_LREAL

<img width="1538" height="212" alt="F_TIME_IN_NS_TO_LREAL" src="https://github.com/user-attachments/assets/c94f3148-26d5-44a8-88fc-e5eeb5938a75" />
* * * * * * * * * *
## Introduction

The function block `F_TIME_IN_NS_TO_LREAL` is used to convert a time value in nanoseconds (`TIME`) into a floating-point value (`LREAL`). This conversion is particularly useful in control applications where time values need to be used in mathematical calculations.
![F_TIME_IN_NS_TO_LREAL](F_TIME_IN_NS_TO_LREAL.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input expects a time value in nanoseconds (`TIME`).

### **Data Outputs**

- **OUT**: Returns the converted floating-point value (`LREAL`).

#### **Adapters**

- No adapters are available.

## Functionality

This function block converts the nanosecond time value `IN` (`TIME`) into a floating-point value (`LREAL`). The conversion occurs every time the event `REQ` is triggered. After successful conversion, the event `CNF` is triggered, and the result value is available at output `OUT`.

## Technical Features

- The function block is implemented as a simple FB (`SimpleFB`).
- The conversion is performed using the built-in function `TIME_IN_NS_TO_LREAL`.

## State Overview

The function block has no internal states. Execution occurs immediately upon the occurrence of the `REQ` event.

## Application Scenarios

- Time measurements in control systems that require further processing in mathematical expressions.
- Integration into control loops where time values are required as floating-point numbers.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

Use the block **`F_MULTIME`** (from the `arithmetic` category) for this purpose:

- Multiply your numeric value by the desired time base.
- **Example:** `500 * T#1ms = T#500ms`
- This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with Similar Building Blocks

- Unlike generic conversion blocks, `F_TIME_IN_NS_TO_LREAL` is specifically optimized for converting time values in nanoseconds to floating-point numbers.
- Other blocks, such as `F_TIME_TO_LREAL`, might offer similar functionality, but without explicitly specifying the nanosecond unit.

## Conclusion

The `F_TIME_IN_NS_TO_LREAL` function block provides an efficient and specialized solution for converting time values to floating-point numbers. Its ease of use and direct integration make it ideal for applications requiring precise time processing.
