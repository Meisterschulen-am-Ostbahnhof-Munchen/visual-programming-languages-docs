# F_UDINT_TO_LREAL
<img width="1462" height="212" alt="F_UDINT_TO_LREAL" src="https://github.com/user-attachments/assets/d665c8a5-8333-49ed-8f5d-bd9ef9b69169" />
* * * * * * * * * *
## Introduction
The function block `F_UDINT_TO_LREAL` converts a 32-bit unsigned integer value (UDINT) into a 64-bit floating-point value (LREAL). This block is particularly useful in applications where numerical values of varying precision need to be processed.
![F_UDINT_TO_LREAL](F_UDINT_TO_LREAL.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is processed.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The converted value is available at data output `OUT`.

### **Data Inputs**
- **IN** (UDINT): The unsigned 32-bit integer value to be converted.

### **Data Outputs**
- **OUT** (LREAL): The resulting 64-bit floating-point value after conversion.

### **Adapters**
This function block does not use any adapters.

## Operation
When event input `REQ` is triggered, the value at input `IN` (of type UDINT) is read and converted to an LREAL value. The result is output at `OUT`, and event `CNF` signals successful conversion.

## Technical Features
- The algorithm is implemented directly in ST (Structured Text) and performs a simple type conversion.
- No additional error handling or limit checks are required, as UDINT values can be directly converted to LREAL.

## State Overview

1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Converts `IN` to `OUT`.

3. **Completed**: Sends `CNF` and returns to the idle state.

## Application Scenarios
- Data processing in control systems where different numeric formats need to be processed.
- Integration into larger systems that require both integer and floating-point operations.

## ⚖️ Comparison with Similar Function Blocks
- Compared to generic conversion blocks, `F_UDINT_TO_LREAL` specializes in converting UDINT to LREAL and is therefore more efficient in this specific application.
- Other blocks might offer additional functionalities such as range checks or scaling, which are not necessary here.

## Conclusion
The `F_UDINT_TO_LREAL` function block is a simple yet effective block for the specific conversion of unsigned 32-bit integers to 64-bit floating-point numbers. Its simplicity and direct implementation make it a reliable choice for such applications.