# F_TIME_IN_US_TO_DINT

<img width="1520" height="212" alt="F_TIME_IN_US_TO_DINT" src="https://github.com/user-attachments/assets/f69e17a7-e3ae-4ca9-ac0d-e8c66d9c31ce" />
* * * * * * * * * *
## Introduction

The function block `F_TIME_IN_US_TO_DINT` converts a TIME value in microseconds (µs) to a DINT value. This conversion is particularly useful when time values are to be used in numerical calculations or for control purposes.
![F_TIME_IN_US_TO_DINT](F_TIME_IN_US_TO_DINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. Upon this event, the input value `IN` is processed, and the result is output at `OUT`.

### **Event Outputs**

- **CNF**: Signals the successful completion of the conversion. This event, along with the converted value, is output at `OUT`.

### **Data Inputs**

- **IN**: The input value of type `TIME`, specified in microseconds, to be converted to a DINT value.

### **Data Outputs**

- **OUT**: The converted value of type `DINT`, representing the result of converting the TIME value to microseconds.

#### **Adapters**

This function block does not use any adapters.

## Operation

The function block performs the conversion by transforming the TIME value in microseconds into a DINT value. The conversion occurs synchronously with the arrival of the `REQ` event. The result is immediately output at `OUT` and confirmed by the `CNF` event.

## Technical Features

- The conversion is performed directly and without delay.
- The function block is suitable for use in real-time applications.
- No additional parameters or configurations are required.

## State Overview

1. **Idle State**: The function block waits for the `REQ` event.
2. **Active State**: Upon receipt of `REQ`, the conversion is performed and the result is output.
3. **Confirmation State**: The `CNF` event is triggered to signal successful conversion.

## Application Scenarios

- Conversion of time values for use in numerical calculations.
- Integration into control algorithms that require time values in a different format.
- Use in systems that process timestamps or durations in microseconds.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is sought to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block does not usually exist, as this is elegantly solved using multiplication.

For this purpose, use the block **`F_MULTIME`** (from the category `arithmetic`):

- Multiply your numeric value by the desired time base.
- **Example:** `500 * T#1ms = T#500ms`
- This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with similar function blocks

- Compared to generic conversion function blocks, this function block specializes in converting TIME to DINT.
- Other function blocks might offer additional features such as scaling or filtering, which is not the case here.

## Conclusion

The `F_TIME_IN_US_TO_DINT` function block is a simple and efficient tool for converting time values in microseconds to a DINT value. Its simple interface and direct functionality make it ideal for applications that require fast and reliable conversion.
