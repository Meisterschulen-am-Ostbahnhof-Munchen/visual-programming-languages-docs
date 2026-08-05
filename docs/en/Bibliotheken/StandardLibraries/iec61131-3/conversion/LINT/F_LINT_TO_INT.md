# F_LINT_TO_INT

<img width="1421" height="214" alt="F_LINT_TO_INT" src="https://github.com/user-attachments/assets/59a9a468-b60b-4e33-9018-cc20619801a8" />

* * * * * * * * * *
## Introduction
The function block `F_LINT_TO_INT` is used to convert a 64-bit integer value (LINT) to a 16-bit integer value (INT). This conversion is useful when data needs to be exchanged or processed between systems with different word lengths.

![F_LINT_TO_INT](F_LINT_TO_INT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the successful completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (LINT): The 64-bit integer value to be converted.

### **Data Outputs**

- **OUT** (INT): The resulting 16-bit integer value after conversion.

#### **Adapters**
- No adapters are present.

## Functionality
This function block performs the conversion from a LINT to an INT value as soon as the event `REQ` is received. The conversion is carried out by the function `LINT_TO_INT(IN)`, which converts the value of `IN` to an INT value and outputs the result to `OUT`. The event `CNF` is then triggered to signal successful conversion.

## Technical Details
- Data loss can occur during conversion if the original LINT value is outside the representable range of an INT value (-32,768 to 32,767).

- The function block has a simple structure and contains only one conversion algorithm.

## State Overview
1. **Idle State**: Waits for the event `REQ`.

2. **Conversion State**: Performs the conversion and outputs the result.

3. **Acknowledge State**: Sends the event `CNF` and returns to the idle state.

## Application Scenarios
- Data communication between systems with different word widths.

- Reduced memory usage when full 64-bit precision is not required.

- Integration into control systems that can only process 16-bit integers.

## ⚖️ Comparison with similar function blocks

- **F_LINT_TO_DINT**: Converts LINT to DINT (32-bit integer).

- **F_LINT_TO_UDINT**: Converts LINT to UDINT (32-bit unsigned integer).

- **F_LINT_TO_ULINT**: Converts LINT to ULINT (64-bit unsigned integer).

## Conclusion
The `F_LINT_TO_INT` function block provides a simple and efficient way to convert 64-bit integer values to 16-bit integer values. It is particularly useful in scenarios where reducing data width is necessary, however, the possibility of data loss during conversion should be considered.