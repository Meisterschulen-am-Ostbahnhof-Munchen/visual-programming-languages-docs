# F_REAL_TO_LREAL

<img width="1451" height="213" alt="F_REAL_TO_LREAL" src="https://github.com/user-attachments/assets/d9c98d4f-9da0-484e-ac3d-998cf8b14b3a" />

* * * * * * * * * *
## Introduction
The function block `F_REAL_TO_LREAL` is used to convert a REAL value to an LREAL value. This block is part of the `iec61131::conversion` package and enables simple type conversion between the two numeric data types.

![F_REAL_TO_LREAL](F_REAL_TO_LREAL.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. Triggers the conversion. Linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Execution confirmation. Triggered after successful conversion. Linked to the data output `OUT`.

### **Data Inputs**

- **IN**: Input value of type `REAL` to be converted.

### **Data Outputs**

- **OUT**: Output value of type `LREAL` containing the result of the conversion.

### **Adapters**
This function block does not use any adapters.

## Functionality
Upon receiving the event `REQ`, the function block converts the REAL value `IN` to an LREAL value and assigns the result to the output `OUT`. The event `CNF` is then triggered to confirm successful execution.

## Technical Features
- The function block is a simple building block without internal states or complex logic.

- Conversion is performed directly by assignment, as `LREAL` offers higher accuracy than `REAL` and can therefore represent all values without loss.

## State Overview
Since it is a simple function block, there are no state transitions or management. Execution occurs atomically upon receiving the `REQ` event.

## Application Scenarios

- Type conversion in control applications where higher accuracy is required.

- Integration into existing systems that use different data types.

- Use in mathematical calculations that require higher precision.


## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks like `F_INT_TO_REAL` or `F_DINT_TO_LINT` also perform type conversions, but between different data types.

- Unlike complex conversion blocks, `F_REAL_TO_LREAL` offers a simple and direct conversion without additional parameters or logic.

## Conclusion
The `F_REAL_TO_LREAL` function block is a useful tool for the simple and efficient conversion of REAL to LREAL values. Its simplicity and direct functionality make it ideal for applications that require fast type conversion without added complexity.