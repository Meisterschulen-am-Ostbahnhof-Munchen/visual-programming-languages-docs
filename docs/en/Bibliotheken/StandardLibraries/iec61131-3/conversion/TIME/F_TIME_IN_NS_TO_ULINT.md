# F_TIME_IN_NS_TO_ULINT
<img width="1538" height="212" alt="F_TIME_IN_NS_TO_ULINT" src="https://github.com/user-attachments/assets/8f77a80e-b99a-4045-87db-8e4bb1e7fc74" />
* * * * * * * * * *
## Introduction
The function block `F_TIME_IN_NS_TO_ULINT` converts a `TIME` value in nanoseconds to a `ULINT` value. This conversion is particularly useful when time values are needed in numerical calculations or for further processing steps.
![F_TIME_IN_NS_TO_ULINT](F_TIME_IN_NS_TO_ULINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the execution of the function block. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input expects a `TIME` value in nanoseconds, which is to be converted.

### **Data Outputs**
- **OUT**: Outputs the converted `ULINT` value.

### **Adapters**
No adapters are available.

### ## Functionality

The function block converts the nanosecond value `TIME` (`IN`) to a nanosecond value `ULINT` (`OUT`) as soon as the event `REQ` is triggered. The conversion is performed using the function `TIME_IN_NS_TO_ULINT`. After the conversion is complete, the event `CNF` is triggered.

## Technical Features
- The function block has a simple structure and contains only one algorithm for the conversion.
- The conversion is direct and without any additional delay.

## State Overview
The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Conversion of time values for use in numerical calculations.
- Integration into control systems where time values need to be further processed as numerical values.

## Reverse Conversion (Numeric to TIME)
Often, a function like `DINT_TO_TIME` is sought to convert a numerical value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block does not usually exist, as this is elegantly solved using multiplication.

Use the function block **`F_MULTIME`** (from the category `arithmetic`) for this:

* Multiply your numeric value by the desired time base.
* **Example:** `500 * T#1ms = T#500ms`
* This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with similar function blocks
- Compared to other conversion function blocks, this one is specifically designed to convert `TIME` to `ULINT`.
- Similar function blocks might use different data types or units, but this one is optimized for nanoseconds.

## Conclusion

The `F_TIME_IN_NS_TO_ULINT` function block offers a simple and efficient way to convert time values in nanoseconds into `ULINT` values. Its clear interface and direct functionality make it a useful component in automation technology.