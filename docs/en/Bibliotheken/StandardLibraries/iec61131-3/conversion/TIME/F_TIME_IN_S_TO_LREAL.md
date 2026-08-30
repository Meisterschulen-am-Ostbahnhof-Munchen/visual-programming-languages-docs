# F_TIME_IN_S_TO_LREAL

<img width="1518" height="212" alt="F_TIME_IN_S_TO_LREAL" src="https://github.com/user-attachments/assets/918c65c5-b8f3-4a1c-8b73-11ee40e82859" />
* * * * * * * * * *
## Introduction

The function block `F_TIME_IN_S_TO_LREAL` converts a time value in seconds (`TIME`) into a floating-point value (`LREAL`). This conversion is useful when time values are needed in mathematical calculations or for further processing steps.
![F_TIME_IN_S_TO_LREAL](F_TIME_IN_S_TO_LREAL.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input expects a time value of type `TIME` in seconds, which is to be converted.

### **Data Outputs**

- **OUT**: Outputs the converted value as a floating-point number (`LREAL`).

#### **Adapters**

- No adapters are available.

## Functionality

The function block performs the conversion from `TIME` to `LREAL` as soon as the event `REQ` is triggered. The conversion is performed using the function ``TIME_IN_S_TO_LREAL``, which converts the time value in seconds into a corresponding floating-point value. Upon completion of the conversion, the event ``CNF`` is triggered.

## Technical Features

- The function block is a simple algorithm (``SimpleFB``) and does not perform any complex state transitions.
- The conversion is instantaneous and without any additional delay.

## State Overview

Since it is a simple function block, there are no state transitions. The conversion occurs immediately upon triggering ``REQ``.

## Application Scenarios

- Conversion of time values for mathematical operations.
- Integration into control logic where time values are required as floating-point numbers.
- Use in control engineering or data processing where precise time measurements are necessary.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

Use the block **`F_MULTIME`** (from the `arithmetic` category) for this purpose:

- Multiply your numeric value by the desired time base.
- **Example:** `500 * T#1ms = T#500ms`
- This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with Similar Function Blocks

- Unlike other conversion blocks that may require additional parameters or states, `F_TIME_IN_S_TO_LREAL` is designed for a specific and direct conversion.
- Similar function blocks could be, for example, `TIME_TO_STRING` or `TIME_TO_INT`, which, however, provide different output types.

## Conclusion

The `F_TIME_IN_S_TO_LREAL` function block offers an efficient and direct way to convert time values in seconds to floating-point numbers. Its simple structure and fast execution make it ideal for applications that require precise and straightforward conversion.
