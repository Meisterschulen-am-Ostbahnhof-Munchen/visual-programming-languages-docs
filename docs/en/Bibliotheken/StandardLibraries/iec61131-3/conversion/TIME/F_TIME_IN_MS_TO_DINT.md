# F_TIME_IN_MS_TO_DINT

<img width="1520" height="212" alt="F_TIME_IN_MS_TO_DINT" src="https://github.com/user-attachments/assets/da759ac7-d146-48b2-aed1-730dd4e68d6e" />
* * * * * * * * * *
## Introduction

The function block `F_TIME_IN_MS_TO_DINT` converts a TIME value in milliseconds to a DINT value. This is particularly useful when time values need to be converted into numerical values for use in calculations or for control purposes.
![F_TIME_IN_MS_TO_DINT](F_TIME_IN_MS_TO_DINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request event. Used to start the conversion. Linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Execution confirmation event. Signals the completion of the conversion. Linked to data output `OUT`.

### **Data Inputs**

- **IN** (TIME): The input value in milliseconds to be converted.

### **Data Outputs**

- **OUT** (DINT): The converted numeric value.

#### **Adapters**

No adapters are available.

## Functionality

The function block performs the conversion by transforming the TIME value in milliseconds into a DINT value. The conversion occurs when the event `REQ` is triggered. After the conversion is complete, the event `CNF` is triggered, and the converted value is available at output `OUT`.

## Technical Features

- The function block uses a simple algorithm for the direct conversion of TIME to DINT.
- The conversion is deterministic and occurs without delay.

## State Overview

1. **Idle State**: Waits for the `REQ` event.
2. **Conversion State**: Performs the conversion and triggers the `CNF` event.

## Application Scenarios

- Conversion of time values for use in numerical calculations.
- Integration into control systems that require numerical time values.
- Use in logging and monitoring systems that store timestamps in numerical form.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

Use the block **`F_MULTIME`** (from the `arithmetic` category) for this purpose:

- Multiply your numeric value by the desired time base.
- **Example:** `500 * T#1ms = T#500ms`
- This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with similar function blocks

- **F_TIME_TO_UDINT**: Converts TIME to UDINT, while `F_TIME_IN_MS_TO_DINT` converts to DINT.
- **F_TIME_IN_US_TO_DINT**: Converts TIME in microseconds to DINT, while this function block uses milliseconds.

## Conclusion

The function block `F_TIME_IN_MS_TO_DINT` is a simple and efficient tool for converting time values in milliseconds to numeric DINT values. It is particularly suitable for applications requiring fast and deterministic conversion.
