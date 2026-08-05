# F_TIME_IN_US_TO_ULINT
<img width="1536" height="212" alt="F_TIME_IN_US_TO_ULINT" src="https://github.com/user-attachments/assets/30c49e6f-e058-49c6-84cf-c4478d9a7c69" />
* * * * * * * * * *
## Introduction
The function block `F_TIME_IN_US_TO_ULINT` converts a time value in microseconds (`TIME`) into an unsigned 64-bit integer value (`ULINT`). This is particularly useful when time values need to be converted for numerical calculations or further processing.
![F_TIME_IN_US_TO_ULINT](F_TIME_IN_US_TO_ULINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**
- **IN**: This input expects a time value of type `TIME` (in microseconds) to be converted.

### **Data Outputs**
- **OUT**: Returns the converted value as an unsigned 64-bit integer (`ULINT`).

### **Adapters**
- No adapters are available.

### **Adapters**

### **Adapters**

### **Inputs**: ... ## Functionality

The function block uses the algorithm `REQ` to convert the incoming `TIME` value into a `ULINT` value in microseconds. The conversion is performed by the function `TIME_IN_US_TO_ULINT(IN)`. Once the conversion is complete, the event `CNF` is triggered to signal successful completion.

## Technical Features
- The function block has a simple structure and contains only one algorithm.
- The conversion is direct and requires no additional parameters or state management.

## State Overview
Because it is a simple function block, there are no complex state transitions. The block responds to the `REQ` event, performs the conversion, and signals completion with `CNF`.

## Application Scenarios
- Time measurement and processing in control systems.
- Conversion of time values for use in calculations or logging systems.
- Integration into larger control algorithms that require numeric time values.

## Reverse Conversion (Numeric to TIME)
Often, a function like `DINT_TO_TIME` is needed to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block is not usually available, as this is elegantly solved using multiplication.

Use the function block **`F_MULTIME`** (from the category `arithmetic`) for this:

* Multiply your numeric value by the desired time base.
* **Example:** `500 * T#1ms = T#500ms`
* This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).

## ⚖️ Comparison with similar function blocks
- Compared to generic conversion blocks, `F_TIME_IN_US_TO_ULINT` specializes in converting `TIME` to `ULINT`.
- Other blocks might offer additional features such as scaling or filtering, which is not the case here.

## Conclusion

The function block `F_TIME_IN_US_TO_ULINT` is a simple yet effective tool for converting microsecond time values into numerical values. Its simplicity and direct operation make it a reliable component in control applications that require precise time processing.