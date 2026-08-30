# F_DINT_TO_WORD

<img width="1438" height="211" alt="F_DINT_TO_WORD" src="https://github.com/user-attachments/assets/0eae21ae-dfc1-44bc-a956-609f3c8000a1" />
* * * * * * * * * *
The function block `F_DINT_TO_WORD` converts a 32-bit integer value (DINT) into a 16-bit word value (WORD). This conversion is particularly useful when data needs to be exchanged between systems with different word widths.
![F_DINT_TO_WORD](F_DINT_TO_WORD.svg)

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is read and converted.
- **CNF**: Signals the successful completion of the conversion. The converted value is available at data output `OUT`.
- **IN**: The 32-bit integer value (DINT) to be converted.
- **OUT**: The converted 16-bit word value (WORD).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

#### **Adapters**

This function block has no adapters.

When the event input `REQ` is triggered, the algorithm is executed, converting the value of `IN` from DINT to WORD and outputting the result to `OUT`. The event `CNF` is then triggered to signal the completion of the operation.

- The conversion truncates the upper 16 bits of the DINT value, as a WORD can only store 16 bits. It is therefore important to ensure that the original DINT value is within the representable range of a WORD (0 to 65535) to avoid data loss.
- The function block is deterministic and has no internal states.

Since this is a simple function block without internal states, there are no state transitions. The block performs the conversion on each `REQ` event and signals completion with `CNF`.

- Communication between systems that use different word widths.
- Adapting data for peripheral devices that can only process WORD data.
- Use in control systems where memory optimization is required.
- Compared to generic conversion blocks like `F_ANY_TO_ANY`, `F_DINT_TO_WORD` is specialized and therefore more efficient when precisely this type of conversion is required.
- Similar blocks like `F_INT_TO_WORD` work with smaller integer types, while `F_DINT_TO_WORD` handles the larger DINT type.

The `F_DINT_TO_WORD` function block is a specialized and efficient tool for converting 32-bit integers to 16-bit words. Its simplicity and determinism make it a reliable component in control applications, especially for data adaptation between different systems.

## Functionality

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion
