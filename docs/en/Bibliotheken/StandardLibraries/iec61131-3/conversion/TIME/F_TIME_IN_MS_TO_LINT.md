# F_TIME_IN_MS_TO_LINT
<img width="1520" height="212" alt="F_TIME_IN_MS_TO_LINT" src="https://github.com/user-attachments/assets/461a5741-0611-455b-92b2-5ce407357498" />
* * * * * * * * * *
## Introduction
The function block `F_TIME_IN_MS_TO_LINT` converts a time value (`TIME`) in milliseconds into a 64-bit integer value (`LINT`). This functionality is particularly useful when time values are needed in numerical form for calculations or comparisons.
![F_TIME_IN_MS_TO_LINT](F_TIME_IN_MS_TO_LINT.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion of the time value. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: This input expects a time value (`TIME`) to be converted into milliseconds.

### **Data Outputs**
- **OUT**: Outputs the converted time value as a 64-bit integer (`LINT`).

### **Adapters**
This function block does not have any adapters.


#
## **Data Inputs ... #
When the event input `REQ` is triggered, the algorithm is executed, which converts the time value `IN` into milliseconds and outputs the result as `LINT` via the output `OUT`. The event `CNF` signals the successful completion of the conversion.

## Technical Features
- The function block uses the function `TIME_IN_MS_TO_LINT` to convert the time value.
- The conversion is performed with high accuracy because the `LINT` data type is 64 bits wide.

## State Overview
The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Time measurements where the results need to be processed further in numerical form.
- Control applications that require precise time intervals in milliseconds.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is sought to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion function block does not usually exist, as this is elegantly solved using multiplication.

Use the function block **`F_MULTIME`** (from the `arithmetic` category) for this:

* Multiply your numeric value by the desired time base.
* **Example:** `500 * T#1ms = T#500ms`
* This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with similar function blocks
- Compared to other conversion function blocks that may only convert to smaller integer types, this function block offers higher accuracy by using the `LINT` data type.
- Similar function blocks might convert time to other units (e.g., seconds or microseconds), while this function block is specifically designed for milliseconds.

## Conclusion

The `F_TIME_IN_MS_TO_LINT` function block is an efficient tool for the precise conversion of time values in milliseconds to a 64-bit integer value. Its simple and direct operation makes it particularly suitable for applications that require accurate time measurements and calculations.
