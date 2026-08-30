# F_TIME_IN_NS_TO_UDINT

<img width="1538" height="212" alt="F_TIME_IN_NS_TO_UDINT" src="https://github.com/user-attachments/assets/cd46fa62-6fda-4f4a-8e2f-92db543f9c19" />
* * * * * * * * * *
## Introduction

The function block `F_TIME_IN_NS_TO_UDINT` converts a time value in nanoseconds (`TIME`) into an unsigned 32-bit integer value (`UDINT`). This conversion is particularly useful when time values are needed in a numeric format for further calculations or control purposes.
![F_TIME_IN_NS_TO_UDINT](F_TIME_IN_NS_TO_UDINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this event input is triggered, the function block performs the conversion of the time value present at `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event is triggered as soon as the converted value is output to `OUT`.

### **Data Inputs**

- **IN** (`TIME`): The input for the time value in nanoseconds to be converted.

### **Data Outputs**

- **OUT** (`UDINT`): The output to which the converted unsigned 32-bit integer value is output.

### **Adapters**

This function block does not use any adapters.

## Functionality

The function block performs the conversion by converting the nanosecond time value (`TIME`) received at `IN` into an unsigned 32-bit integer value (`UDINT`) using the function `TIME_IN_NS_TO_UDINT`. The conversion occurs synchronously with the triggering of the `REQ` event. After successful conversion, the `CNF` event is triggered, and the converted value is output to `OUT`.

## Technical Features

- The conversion is instantaneous and without delay.
- The function block is suitable for use in real-time applications.
- No additional parameters or configurations are required.

## State Overview

1. **Idle State**: The function block waits for the `REQ` event.
2. **Conversion State**: When `REQ` is triggered, the time value is converted.
3. **Acknowledgement State**: After successful conversion, `CNF` is triggered, and the function block returns to the idle state.

## Application Scenarios

- Conversion of timestamps for use in numerical calculations.
- Integration into control logic that needs to process time values in a numerical format.
- Use in diagnostic systems to display durations in a readable format.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

Use the block **`F_MULTIME`** (from the category `arithmetic`) for this purpose:

- Multiply your numeric value by the desired time base.
- **Example:** `500 * T#1ms = T#500ms`
- This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with Similar Blocks

- Unlike generic conversion blocks, this function block is specifically optimized for converting time values to nanoseconds.
- Similar blocks might offer additional parameters or configuration options, but this function block is designed for simplicity and efficiency.

## Conclusion

The `F_TIME_IN_NS_TO_UDINT` function block provides a simple and efficient way to convert nanosecond time values to unsigned 32-bit integer values. Its clear interface and direct operation make it ideal for applications requiring fast and reliable conversion.
