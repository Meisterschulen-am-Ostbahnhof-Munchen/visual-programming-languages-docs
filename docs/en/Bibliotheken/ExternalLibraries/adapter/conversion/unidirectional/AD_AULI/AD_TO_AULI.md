# AD_TO_AULI

![AD_TO_AULI](./AD_TO_AULI.svg)

* * * * * * * * * *
## Introduction

The AD_TO_AULI function block is a composite FB for converting a DWORD adapter (AD) to a ULINT adapter (AULI). It uses the IEC 61131 conversion function F_DWORD_TO_ULINT and encapsulates the event and data connections for easy adapter-based conversion.
## Interface Structure

### **Event Inputs**

None
### **Event Outputs**

None
### **Data Inputs**

None
### **Data Outputs**

None
### **Adapter**

- **AD_IN** (Socket): Type AD (DWORD), unidirectional input adapter for the DWORD.
- **AULI_OUT** (Plug): Type AULI (ULINT), unidirectional output adapter for the converted ULINT.

## Functionality

The function block receives a DWORD via the AD_IN adapter. An event at the E1 input of AD_IN triggers the REQ event input of the internal converter F_DWORD_TO_ULINT. This converts the data value (AD_IN.D1) and signals completion via CNF. The CNF event then triggers the E1 event at the AULI_OUT adapter, and the converted value (ULINT) is output via AULI_OUT.D1.

## Technical Features

- **Bit-reinterpretation, value-preserving** (destination is same width or wider than the source bit-string).

- The function block is implemented as a composite and uses the `iec61131::conversion::F_DWORD_TO_ULINT` library.
- No direct event or data inputs/outputs are used; all communication takes place exclusively via adapters.
- The conversion is performed according to IEC 61499 event control: The output event is only sent after the conversion is complete.

## State Overview

The composite block itself does not have its own states. The integrated function block F_DWORD_TO_ULINT goes through the following states:

- **IDLE**: Waiting for a REQ event.
- **REQ**: Conversion is being performed.
- **CNF**: Conversion complete, output data is being updated.

## Application Scenarios

- Conversion of measured values or control data, which are available as DWORD (32-bit), into a ULINT (64-bit) adapter for subsequent processing.
- Use in modular automation systems based on adapter interfaces.
- Bridging between components with different adapter types.

## Comparison with Similar Function Blocks

- Direct type conversion function blocks like `F_DWORD_TO_ULINT` operate at the data level, while AD_TO_AULI encapsulates the adapter interfaces.
- Similar composite function blocks exist for other data type combinations (e.g., DWORD_TO_LWORD), specifically utilizing the unidirectional AD and AULI adapters.

## Conclusion

AD_TO_AULI offers a simple and reusable solution for adapter-based conversion from DWORD to ULINT. Encapsulating the conversion logic within a composite function block increases reusability and reduces network complexity.
