# F_TIME_IN_S_TO_UDINT

<img width="1520" height="212" alt="F_TIME_IN_S_TO_UDINT" src="https://github.com/user-attachments/assets/9fd11a62-281e-43ec-9520-98d7cc20671c" />

* * * * * * * * * *
## Introduction
The function block `F_TIME_IN_S_TO_UDINT` converts a TIME value in seconds to a UDINT value. This conversion is useful when time values are needed in numerical operations or for further processing steps.

![F_TIME_IN_S_TO_UDINT](F_TIME_IN_S_TO_UDINT.svg)

## Interface Structure
### **Event Inputs**
- **REQ**: Normal execution request. Triggers the conversion.

### **Event Outputs**

- **CNF**: Execution confirmation. Triggered after successful conversion.

### **Data Inputs**

- **IN**: TIME value in seconds to be converted.


### **Data Outputs**

- **OUT**: Converted UDINT value.

## **Adapters**
No adapters available.

## Functionality
This function block converts the incoming TIME value (IN) in seconds into a UDINT value (OUT). The conversion is performed by calling the function `TIME_IN_S_TO_UDINT(IN)` in the algorithm. When the REQ event is triggered, the conversion is carried out and the CNF event is triggered.

## Technical Features
- The function block is simple and efficient because it directly uses the built-in function `TIME_IN_S_TO_UDINT`.

- No additional states or complex logic are required.

## State Overview
The function block has no internal states. The conversion occurs immediately upon triggering the REQ event.

## Application Scenarios

- Conversion of time values for numerical calculations.

- Integration into control systems where time values are required as numeric values.

## Reverse Conversion (Numeric to TIME)
Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

Use the function block **`F_MULTIME`** (from the category `arithmetic`) for this purpose:

* Multiply your numeric value by the desired time base.


``` * **Example:** `500 * T#1ms = T#500ms`

* This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with similar function blocks

- Compared to other conversion function blocks, this one is specifically optimized for converting TIME to UDINT.

- Other function blocks might offer additional features such as scaling or limit checking, which is not the case here.

## Conclusion
The `F_TIME_IN_S_TO_UDINT` function block is a simple and efficient function block for converting TIME values to UDINT. It is ideally suited for applications where time values are required in numerical form.