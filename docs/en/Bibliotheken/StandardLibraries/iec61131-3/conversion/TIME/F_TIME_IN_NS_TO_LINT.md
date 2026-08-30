# F_TIME_IN_NS_TO_LINT

<img width="1521" height="212" alt="F_TIME_IN_NS_TO_LINT" src="https://github.com/user-attachments/assets/2aa3f00a-29f1-4cb9-944b-381d672567a3" />
* * * * * * * * * *
## Introduction

The function block `F_TIME_IN_NS_TO_LINT` converts a time value in nanoseconds (`TIME`) into a 64-bit integer value (`LINT`). This conversion is useful when time values are needed in numerical form for calculations or comparisons.
![F_TIME_IN_NS_TO_LINT](F_TIME_IN_NS_TO_LINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: This input expects a time value of type `TIME`, specified in nanoseconds.

### **Data Outputs**

- **OUT**: This output returns the converted value as a 64-bit integer (`LINT`).

### **Adapters**

- No adapters are present.

## Operation

This function block performs the conversion when the event `REQ` is triggered. The algorithm converts the time value `IN` in nanoseconds to a value `LINT` and stores the result in `OUT`. The event `CNF` is then triggered to signal the completion of the operation.

## Technical Details

- The function block is implemented as a *SimpleFB*, meaning it has no internal state and is re-executed with each call to `REQ`.
- The conversion is performed directly by the function `TIME_IN_NS_TO_LINT`, which converts the value `TIME` to a value `LINT`.

## State Overview

Since this is a simple function block, there are no state transitions or state machines.

## Application Scenarios

- Time measurement and processing in control systems where numerical operations on time values are required.
- Integration into systems that need to store or transmit timestamps in a numerical format.

## Reverse Conversion (Numeric to TIME)

Often, a function like ``DINT_TO_TIME`` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

Use the function block **`F_MULTIME`** (from the category `arithmetic`):

- Multiply your numeric value by the desired time base.
- **Example:** `500 * T#1ms = T#500ms`
- This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with similar function blocks

- Unlike generic conversion blocks, this function block specializes in converting `TIME` to `LINT`.
- Other blocks might offer additional features such as scaling or formatting, which is not the case here.

## Conclusion

The `F_TIME_IN_NS_TO_LINT` function block provides a simple and efficient way to convert time values in nanoseconds to 64-bit integers. It is particularly useful in applications that require precise time measurements and calculations.
