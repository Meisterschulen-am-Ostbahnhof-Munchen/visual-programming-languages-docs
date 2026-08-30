# F_TIME_IN_S_TO_ULINT

<img width="1520" height="212" alt="F_TIME_IN_S_TO_ULINT" src="https://github.com/user-attachments/assets/60c0a628-bf00-4bf4-b81c-1397cad4dd61" />
* * * * * * * * * *
## Introduction

The function block `F_TIME_IN_S_TO_ULINT` converts a TIME value in seconds to a ULINT value. This is particularly useful when time values need to be converted into numerical formats for use in calculations or further processing.
![F_TIME_IN_S_TO_ULINT](F_TIME_IN_S_TO_ULINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request event. This event triggers the conversion and is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Confirmation event after successful execution. This event is output along with the data output `OUT`.

### **Data Inputs**

- **IN**: Input of type `TIME` containing the time value to be converted in seconds.

### **Data Outputs**

- **OUT**: Output of type `ULINT` containing the converted numeric value.

#### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion by transforming the TIME value (in seconds) into a ULINT value. The conversion occurs when the `REQ` event is triggered, and the result is output via the `OUT` output, accompanied by the `CNF` event.

## Technical Features

- The function block uses the standard algorithm `TIME_IN_S_TO_ULINT` for the conversion.
- The function block is part of the `iec61131::conversion` package.

## State Overview

The function block has no internal states. Execution occurs immediately upon the occurrence of the `REQ` event.

## Application Scenarios

- Conversion of time values for use in numerical calculations.
- Integration into control systems that need to process time values in numerical form.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

Use the block **`F_MULTIME`** (from the category `arithmetic`) for this purpose:

- Multiply your numeric value by the desired time base.
- **Example:** `500 * T#1ms = T#500ms`
- This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with Similar Function Blocks

- Unlike generic conversion blocks, this function block specializes in converting TIME to ULINT.
- Other blocks might offer different output types or additional functionality, such as conversion to other numeric formats.

## Conclusion

The `F_TIME_IN_S_TO_ULINT` function block provides a simple and efficient way to convert time values to ULINT numeric values. Its clear interface and straightforward functionality make it ideal for applications that require such conversions.
