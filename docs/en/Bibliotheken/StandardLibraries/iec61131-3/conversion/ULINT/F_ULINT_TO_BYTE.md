# F_ULINT_TO_BYTE

<img width="1453" height="214" alt="F_ULINT_TO_BYTE" src="https://github.com/user-attachments/assets/f578910e-677f-4594-b1b6-3901e60763ec" />

* * * * * * * * * *
## Introduction
The function block `F_ULINT_TO_BYTE` converts a 64-bit unsigned integer value (ULINT) to an 8-bit unsigned integer value (BYTE). This block is particularly useful in scenarios where type conversion between these two data types is required.

![F_ULINT_TO_BYTE](F_ULINT_TO_BYTE.svg)

## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. It is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. Linked to the data output `OUT`.

### **Data Inputs**

- **IN** (ULINT): The 64-bit unsigned integer value to be converted.

### **Data Outputs**

- **OUT** (BYTE): The resulting 8-bit unsigned integer value after conversion.

### **Adapters**
No adapters available.

## Functionality
This function block performs the ULINT to BYTE conversion when the `REQ` event is triggered. The conversion is performed using the function `ULINT_TO_BYTE(IN)`. After successful conversion, the `CNF` event is triggered, and the converted value is available at output `OUT`.

## Technical Features
- The function block is a simple algorithm without state management.

- Data loss can occur during conversion if the ULINT value is outside the representable range of a BYTE (0 to 255).

## State Overview
Because it is a simple function block, there are no state transitions or complex state logic.

## Application Scenarios
- Type conversion in control applications where ULINT values need to be reduced to BYTEs.

- Data processing in embedded systems with limited memory capacity.


## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks like `F_DINT_TO_BYTE` or `F_UINT_TO_BYTE` perform similar conversions, but with different output data types.

- `F_ULINT_TO_BYTE` is specifically for converting 64-bit unsigned integers to 8-bit unsigned integers.

## Conclusion
The `F_ULINT_TO_BYTE` function block provides a simple and efficient way to convert ULINT values to BYTE values. It is particularly useful in applications where data width reduction is required; however, potential data loss should be considered.