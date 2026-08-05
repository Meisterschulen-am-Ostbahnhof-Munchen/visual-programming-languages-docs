# F_TIME_IN_US_TO_UDINT
<img width="1536" height="212" alt="F_TIME_IN_US_TO_UDINT" src="https://github.com/user-attachments/assets/4ae404ca-902a-488d-8a1e-3385150b6d56" />
* * * * * * * * * *
## Introduction
The function block `F_TIME_IN_US_TO_UDINT` converts a TIME value in microseconds (µs) into a UDINT value. This conversion is particularly useful in applications where time values need to be processed further in numerical form.
![F_TIME_IN_US_TO_UDINT](F_TIME_IN_US_TO_UDINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input of type `TIME`, containing the time value to be converted in microseconds.

### **Data Outputs**
- **OUT**: The output of type `UDINT`, containing the result of the conversion.

### **Adapters**
No adapters are present.

## Functionality
This function block converts the TIME value (in µs) passed to `IN` into a UDINT value. The conversion is performed by calling the function `TIME_IN_US_TO_UDINT(IN)`. After successful conversion, the result is output to `OUT`, and the event `CNF` is triggered.

## Technical Features
- The function block has a simple structure and contains only one algorithm (`REQ`) that performs the conversion.
- There is no state machine or complex logic, as the block is solely responsible for the conversion.

## State Overview
Because it is a simple function block, there are no state transitions or state machines. The block performs the conversion on each `REQ` event and signals completion with `CNF`.

## Application Scenarios
- Time measurement and processing in control systems.
- Conversion of time values for storage or transmission in numerical form.
- Integration into systems that need to process time values in µs as UDINT.

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

Use the block **`F_MULTIME`** (from the `arithmetic` category) for this purpose:

* Multiply your numeric value by the desired time base.
* **Example:** `500 * T#1ms = T#500ms`
* This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with Similar Blocks
- Compared to other conversion blocks, `F_TIME_IN_US_TO_UDINT` specializes in converting TIME to UDINT.
- Similar blocks might support other time formats or other target data types, e.g., TIME to REAL or TIME to STRING.

## Conclusion
The `F_TIME_IN_US_TO_UDINT` function block offers a simple and efficient way to convert microsecond time values to UDINT values. Its streamlined design makes it particularly suitable for applications where performance and simplicity are paramount.