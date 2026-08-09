# F_TIME_IN_S_TO_LINT

<img width="1506" height="212" alt="F_TIME_IN_S_TO_LINT" src="https://github.com/user-attachments/assets/a16343bd-1465-4473-a54f-da877aa2e16a" />
* * * * * * * * * *
## Introduction

The function block `F_TIME_IN_S_TO_LINT` converts a time value in seconds (`TIME`) into a 64-bit integer value (`LINT`). This conversion is particularly useful when time values are needed in numerical form for calculations or comparisons.
![F_TIME_IN_S_TO_LINT](F_TIME_IN_S_TO_LINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion of the time value. This event input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input for the time value in seconds (`TIME`) to be converted.

### **Data Outputs**

- **OUT**: The output for the converted 64-bit integer value (`LINT`).

### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion by transforming the time value in seconds (`TIME`) into a 64-bit integer value (`LINT`). The conversion occurs when the ``REQ`` event is triggered, and the result is output via the ``OUT`` data output, followed by a ``CNF`` event.

## Technical Features

- The function block uses the standard ``61499-1``.
- The conversion is performed using the function ``TIME_IN_S_TO_LINT``, which is implemented in the function block's algorithm.
- The function block is part of the ``iec61131::conversion`` package.

## State Overview

The function block does not have complex states. It reacts to the `REQ` event, performs the conversion, and signals completion with the `CNF` event.

## Application Scenarios

- Conversion of time values for numerical calculations.
- Integration into control systems that require time values in a numerical format.
- Use in systems that require high precision in time measurement.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block is not usually available, as this is elegantly solved using multiplication.

Use the function block **`F_MULTIME`** (from the category `arithmetic`) for this:

* Multiply your numeric value by the desired time base.
* **Example:** `500 * T#1ms = T#500ms`
* This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with similar function blocks

- Compared to other conversion function blocks that may support different data types, this function block is specifically designed for converting `TIME` to `LINT`.

Other function blocks might offer conversion to other integer types (e.g., `INT` or `DINT`), but this block offers higher precision by using `LINT`.

## Conclusion

The `F_TIME_IN_S_TO_LINT` function block is an efficient tool for converting time values in seconds to 64-bit integers. Its simple and straightforward operation makes it a reliable component in control systems that require precise time measurements and calculations.
