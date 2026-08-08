# F_LWORD_TO_LINT
<img width="1450" height="211" alt="F_LWORD_TO_LINT" src="https://github.com/user-attachments/assets/af814d4f-020f-4276-840f-113fb63e2f16" />
* * * * * * * * * *
The function block `F_LWORD_TO_LINT` converts a `LWORD` value (64-bit unsigned) to a `LINT` value (64-bit signed). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_LWORD_TO_LINT](F_LWORD_TO_LINT.svg)

- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

- **IN**: Input for the `LWORD` value to be converted.

- **OUT**: Output for the converted `LINT` value.

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**
- No adapters are present.

## Functionality
The function block performs the conversion from `LWORD` to `LINT` as soon as the event `REQ` is triggered. The conversion is performed using the function `LWORD_TO_LINT(IN)`. Upon successful conversion, the event `CNF` is triggered.

- The function block is a simple FB (SimpleFB) and uses an ST algorithm for the conversion.
- The conversion is performed directly without additional state management.

Since it is a simple function block, there are no complex state transitions. The block responds to `REQ` by executing the algorithm and signals completion with `CNF`.

- Type conversion in control applications where `LWORD` data needs to be converted to `LINT`.


- Similar blocks could be `F_DWORD_TO_DINT` or `F_WORD_TO_INT`, but these are designed for smaller data types.
- Unlike generic conversion blocks, this one is specifically optimized for converting `LWORD` to `LINT`.

The `F_LWORD_TO_LINT` function block offers an efficient and direct method for converting `LWORD` to `LINT`. Its simplicity and specialization make it a reliable component in control applications.
## Technical Features
## State Overview
## Application Scenarios
## ⚖️ Vergleich mit ähnlichen Bausteinen
## Conclusion