# F_TIME_IN_S_TO_DINT

<img width="1506" height="212" alt="F_TIME_IN_S_TO_DINT" src="https://github.com/user-attachments/assets/3154c79d-5b35-46bb-8057-39d2ce513a57" />
* * * * * * * * * *
## Introduction

The function block `F_TIME_IN_S_TO_DINT` converts a time value in seconds (`TIME`) into a signed integer value (`DINT`). This conversion is useful when time values need to be used in numerical calculations or for control purposes.
![F_TIME_IN_S_TO_DINT](F_TIME_IN_S_TO_DINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input expects a time value of type `TIME` in seconds.

### **Data Outputs**

- **OUT**: The output returns the converted value as a signed integer (`DINT`).

#### **Adapters**

No adapters are used.

## Functionality

The function block performs the conversion when the event `REQ` is triggered. The algorithm converts the time value `IN` in seconds to a `DINT` value and stores the result in `OUT`. After the conversion is complete, the event `CNF` is triggered.

## Technical Features

- The function block uses the function `TIME_IN_S_TO_DINT` for the conversion.
- The block is simple and efficient because it is directly based on the ST algorithm.

## State Overview

The function block has no internal states. The conversion occurs immediately after `REQ` is triggered.

## Application Scenarios

- Conversion of time values for numerical calculations.
- Integration into control logic that requires numerical time values.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

Use the block **`F_MULTIME`** (from the `arithmetic` category) for this purpose:

* Multiply your numeric value by the desired time base.
* **Example:** `500 * T#1ms = T#500ms`
* This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with Similar Building Blocks

- Compared to other conversion blocks, this one is specifically designed to convert `TIME` to `DINT`.
- Simpler and more direct than general conversion blocks, which may require additional parameters.

## Conclusion

The `F_TIME_IN_S_TO_DINT` function block offers an efficient and simple solution for converting time values in seconds to signed integers. Its clear interface and direct functionality make it ideal for control applications.
