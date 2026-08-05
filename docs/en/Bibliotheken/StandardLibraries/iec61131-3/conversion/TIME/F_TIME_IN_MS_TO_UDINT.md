# F_TIME_IN_MS_TO_UDINT

<img width="1531" height="212" alt="F_TIME_IN_MS_TO_UDINT" src="https://github.com/user-attachments/assets/142405a6-cd3f-4140-b2ae-e38e692d620f" />

* * * * * * * * * *
## Introduction
The function block `F_TIME_IN_MS_TO_UDINT` converts a `TIME` value in milliseconds to a `UDINT` value. This is particularly useful when time values are to be used in numerical calculations or for control purposes.

![F_TIME_IN_MS_TO_UDINT](F_TIME_IN_MS_TO_UDINT.svg)

## Interface Structure
### **Event Inputs**
- **REQ**: Normal execution request. Triggers the conversion.

### **Event Outputs**
- **CNF**: Execution confirmation. Triggered after successful conversion.


### **Data Inputs**

- **IN**: Input of type `TIME`. The time value in milliseconds to be converted.

### **Data Outputs**

- **OUT**: Output of type `UDINT`. The converted numeric value.

### **Adapters**
No adapters are available.

## Functionality
The function block performs the conversion by transforming the `TIME` value in milliseconds into a `UDINT` value. The conversion occurs synchronously with the triggering of the `REQ` event. After the conversion is complete, the `CNF` event is triggered.


## Technical Features
- The function block is simple and has no internal states.

- The conversion is immediate and instantaneous.

## State Overview
Since it is a simple function block, there are no state transitions or complex state logic.

## Application Scenarios
- Conversion of time values for numerical calculations.

- Integration into control logic that requires numerical time values.

## Reverse Conversion (Numeric to TIME)
Often, a function like ``DINT_TO_TIME`` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block does not usually exist, as this is elegantly solved using multiplication.


Use the function block **`F_MULTIME`** (from the category `arithmetic`):

* Multiply your numeric value by the desired time base.

* **Example:** `500 * T#1ms = T#500ms`

* This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with similar function blocks

- Compared to other conversion function blocks, this one is specifically designed for converting `TIME` to `UDINT`.

- Other function blocks might offer additional features such as scaling or filtering, which is not the case here.


## Conclusion

The `F_TIME_IN_MS_TO_UDINT` function block is a simple and efficient tool for converting time values in milliseconds into numerical values. It is particularly suitable for applications where a fast and direct conversion is required.