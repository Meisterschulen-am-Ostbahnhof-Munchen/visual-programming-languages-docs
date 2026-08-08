# F_LINT_TO_WORD
<img width="1436" height="214" alt="F_LINT_TO_WORD" src="https://github.com/user-attachments/assets/4aa4298e-3732-42d1-a295-e26f81c02b3d" />
* * * * * * * * * *
The function block `F_LINT_TO_WORD` converts a LINT data type (64-bit integer) to a WORD data type (16-bit word count). This conversion is useful when data needs to be exchanged between systems with different word widths or when an explicit type conversion is required.
![F_LINT_TO_WORD](F_LINT_TO_WORD.svg)

- `REQ` (Normal Execution Request): Starts the execution of the conversion. Linked to the data input `IN`.

- `CNF` (Execution Confirmation): Signals successful completion of the conversion. Linked to the data output `OUT`.

- `IN` (LINT): The input value to be converted from LINT to WORD.

- `OUT` (WORD): The converted output value in WORD format.

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**
This function block does not use adapters.

## Functionality
The function block performs the conversion from LINT to WORD when the event `REQ` is triggered. The conversion is performed using the built-in function ``LINT_TO_WORD``, which takes the value of the input ``IN`` and converts it to the WORD data type. The result is output at ``OUT``, and the event ``CNF`` signals successful execution.

- The conversion truncates the higher-order bits of the LINT value because WORD can only store 16 bits.
- There is no overflow or underflow check during the conversion.


The function block is stateless and re-executes the conversion with each ``REQ`` event.

- Data communication between systems with different word lengths.


- Similar function blocks such as `F_DINT_TO_WORD` or `F_INT_TO_WORD` perform similar conversions, but with different output data types.
- `F_LINT_TO_WORD` is specific to converting 64-bit to 16-bit and does not offer additional functionality such as overflow checking.

The `F_LINT_TO_WORD` function block is a simple yet effective tool for converting LINT to WORD data. It is particularly useful in scenarios where data width reduction is required without the need for additional validation.
## Technical Features
## State Overview
## Application Scenarios
## ⚖️ Vergleich mit ähnlichen Bausteinen
## Conclusion