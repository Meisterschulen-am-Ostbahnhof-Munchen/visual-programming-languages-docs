# F_ULINT_TO_LWORD
<img width="1466" height="214" alt="F_ULINT_TO_LWORD" src="https://github.com/user-attachments/assets/8b0a2f9e-ac50-43f3-b73b-dadfee3ccecb" />
* * * * * * * * * *
## Introduction
The function block `F_ULINT_TO_LWORD` converts a ULINT data type (64-bit unsigned integer) to an LWORD data type (64-bit bit string). This block is particularly useful in applications where direct type conversion between these two data types is required.
![F_ULINT_TO_LWORD](F_ULINT_TO_LWORD.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the execution of the conversion. When activated, the input value `IN` is read and processed.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output value `OUT` is available at this time.

### **Data Inputs**
- **IN**: ULINT (64-bit unsigned integer) - The input value to be converted to an LWORD.

### **Data Outputs**
- **OUT**: LWORD (64-bit bit string) - The result of the conversion.

### **Adapters**
This function block does not use any adapters.

## Functionality
The function block performs the conversion by transforming the ULINT input value `IN` into an LWORD output value `OUT`. The conversion is performed directly without any further processing. When the event input `REQ` is activated, the algorithm is executed and the result is signaled via the event output `CNF`.

## Technical Features
- The conversion is direct and without data loss, as both data types are 64 bits wide.
- The function block is deterministic and has no internal states.

## State Overview

The function block has no internal states. Execution occurs immediately upon activation of the `REQ` event.

## Application Scenarios
- Type conversion in control applications where ULINT values must be processed as bit strings.
- Communication between systems that use different data types.
- Debugging and logging where bit representations of numeric values are required.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks like `F_DINT_TO_LWORD` or `F_UDINT_TO_LWORD`, this block works with the larger ULINT data type.
- Similar blocks might offer additional features like scaling or formatting, but this block specializes in pure type conversion.

## Conclusion
The `F_ULINT_TO_LWORD` function block is a simple and efficient block for directly converting ULINT to LWORD. Its deterministic and stateless nature makes it reliable and easy to integrate into existing applications.