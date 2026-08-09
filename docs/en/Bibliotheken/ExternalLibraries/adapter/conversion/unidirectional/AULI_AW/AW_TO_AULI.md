# AW_TO_AULI

![AW_TO_AULI](./AW_TO_AULI.svg)

* * * * * * * * * *
## Introduction

The composite function block `AW_TO_AULI` converts a unidirectional adapter of type `AW` (WORD data format) into an adapter of type `AULI` (ULINT data format). The conversion is performed internally using the standard function block `F_WORD_TO_ULINT` from the IEC 61131 library.
## Interface Structure

### **Event Inputs**

- **AW_IN.E1** – Event input via socket `AW_IN`. Triggers the conversion.

### **Event Outputs**

- **AULI_OUT.E1** – Event output via plug `AULI_OUT`. Signals the completion of the conversion.

### **Data Inputs**

- **AW_IN.D1** – Data input of type WORD (via socket `AW_IN`).

### **Data Outputs**

- **AULI_OUT.D1** – Data output of type ULINT (via plug `AULI_OUT`).

### **Adapter**

- **Socket:** `AW_IN` (Type: `adapter::types::unidirectional::AW`)
- **Plug:** `AULI_OUT` (Type: `adapter::types::unidirectional::AULI`)

## Functionality

As soon as an event arrives at event input `AW_IN.E1`, the internal function block `F_WORD_TO_ULINT` is called. This block reads the current value of the data input `AW_IN.D1` (WORD) and converts it into a ULINT value. After successful conversion, an event is output at event output `AULI_OUT.E1`, and the converted value is made available at data output `AULI_OUT.D1`.

## Technical Features

- The function block (FB) is implemented as a composite and fully encapsulates the conversion logic.
- The conversion function used, `F_WORD_TO_ULINT`, complies with the IEC 61131-3 standard.
- The interfaces are based on unidirectional adapters – event and data flow is one-way only.
- The FB does not have a state machine; its functionality is purely event-driven.

## State Overview

The FB does not contain any explicit states. Processing is linear: Event → Conversion → Output.

## Application Scenarios

- Integration of sensors or actuators that deliver WORD data into systems that expect ULINT values.
- Adapter-based protocol conversion in automation technology (e.g., agricultural engineering).
- Reusable encapsulation of the standard conversion function for modular control projects.

## Comparison with Similar Function Blocks

- **Direct use of `F_WORD_TO_ULINT`:** Requires manual wiring of event and data lines. The composite function block `AW_TO_AULI` simplifies integration into adapter-oriented architectures.
- **Other conversion adapters** (e.g., `AW_TO_ADINT` for DINT or `AW_TO_ABOOL` for BOOL): Offer analogous conversions for other target data types.

## Conclusion

AW_TO_AULI` is a practical and easy-to-use component for converting WORD to ULINT data. The use of standardized adapter interfaces and the IEC conversion function ensures compatibility and reliability. The function block is particularly suitable for modular, adapter-based automation solutions.
