# F_LREAL_TO_REAL
<img width="1453" height="214" alt="F_LREAL_TO_REAL" src="https://github.com/user-attachments/assets/460d2ce1-b841-4ad8-ad35-6599f1a8d70c" />
* * * * * * * * * *
## Introduction
The function block `F_LREAL_TO_REAL` converts an LREAL value (64-bit floating-point number) to a REAL value (32-bit floating-point number). This block is particularly useful in scenarios where type conversion between these two numeric data types is required.
![F_LREAL_TO_REAL](F_LREAL_TO_REAL.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the execution of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The LREAL input value to be converted.

### **Data Outputs**
- **OUT**: The REAL output value containing the conversion result.

### **Adapters**
This function block has no adapters.

## Operation
When the event input `REQ` is triggered, the algorithm is executed, converting the LREAL value of `IN` to a REAL value and outputting the result to `OUT`. The event `CNF` is then triggered to signal the completion of the operation.

### **Adapters**

#
## Technical Features
- The function block performs a direct type conversion, taking into account potential accuracy losses due to the different bit widths of the data types.
- The conversion is performed using the built-in function `LREAL_TO_REAL`.

## State Overview

The function block is stateless and performs the conversion on every `REQ` event.

## Application Scenarios
- Type conversion in control applications where LREAL values from high-precision calculations need to be converted into REAL values for further processing.
- Compatibility with systems or function blocks that can only process REAL data types.

## ⚖️ Comparison with Similar Function Blocks
- Compared to generic conversion blocks, `F_LREAL_TO_REAL` specializes in converting between LREAL and REAL, thus offering a clearly defined and efficient solution for this specific use case.

## Conclusion
The `F_LREAL_TO_REAL` function block is a simple yet effective building block for converting between LREAL and REAL data types. Its clear interface and direct functionality make it a reliable component in control applications where such type conversions are required.
