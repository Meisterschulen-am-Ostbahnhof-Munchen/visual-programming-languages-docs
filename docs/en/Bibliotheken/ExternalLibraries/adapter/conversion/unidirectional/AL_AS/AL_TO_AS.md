# AL_TO_AS

![AL_TO_AS](./AL_TO_AS.svg)

* * * * * * * * * *

## Introduction

The **AL_TO_AS** function block is a composite function block that converts a unidirectional AL adapter (LWORD data) into a unidirectional AS adapter (SINT data). It enables the seamless integration of components that work with different data types by converting the signals and passing them on via the respective adapter interfaces.

## Interface Structure

### **Event Inputs**

- None

### **Event Outputs**

- None

### **Data Inputs**

- None

### **Data Outputs**

- None

### **Adapter**

| Type | Name | Direction | Description |
| ----- | ------ | ---------- | -------------- |
| Socket | AL_IN | Input | Unidirectional AL adapter that provides LWORD data. |
| Plug | AS_OUT | Output | Unidirectional AS adapter that outputs the converted SINT data. |

## Functionality

The function block receives events and LWORD data via the `AL_IN` socket. Internally, a function block of type `F_LWORD_TO_SINT` (from the IEC 61131 library) is used to convert the input data (LWORD) to the output data type SINT. The event control works as follows:

- An incoming event at socket `AL_IN.E1` triggers the input `REQ` of the internal conversion module.
- After successful conversion, the output `CNF` of the converter signals an event, which is then passed to plug `AS_OUT.E1`.
- Simultaneously, the converted data value is transferred from the output `OUT` of the converter to the data output `AS_OUT.D1`.

The entire process is event-driven: Only an event at `AL_IN` triggers the conversion and an event at `AS_OUT`.

## Technical Features

- **Bit-reinterpretation**, value-preserving only if the source value fits the narrower destination width (otherwise the upper bits are silently dropped).

- The function block (FB) is implemented as a composite and uses the predefined conversion function `F_LWORD_TO_SINT`, ensuring high reusability and standards compliance.
- Conversion is **unidirectional**, only from LWORD to SINT; a reverse direction is not supported.
- Event forwarding is direct: An event at the input results in exactly one event at the output.
- The data width is reduced from 64 bits (LWORD) to 8 bits (SINT), therefore only values in the range [-128, 127] can be represented. If this range is exceeded, the internal converter behaves according to the IEC 61131 definition (e.g., overflow indication or modulo behavior).

## State Overview

The FB does not have its own state machine. Its behavior is purely combinatorial with event-driven triggering. There is no internal state; The conversion always occurs based on the current input data at an event.

## Application Scenarios

- **System Integration**: If a software system or device uses LWORD interfaces (AL adapter), but another part of the system only supports AS adapters (SINT), this function block can serve as a bridge.
- **Data Reduction**: Targeted conversion of 64-bit data to an 8-bit value, e.g., for transfer to simple actuators or displays that only process SINT.
- **Protocol Adaptation**: In heterogeneous automation networks where different adapter types are used (unidirectionally), this function block simplifies the conversion at a single logical level.

## Comparison with Similar Function Blocks

| Function Block | Input Type | Output Type | Special Feature |
| ---------- | ------------- | ------------- | -------------- |
| **AL_TO_AS** | LWORD (Adapter) | SINT (Adapter) | Composite; uses `F_LWORD_TO_SINT` |
| `F_LWORD_TO_SINT` | LWORD (Data) | SINT (Data) | Data converter only, no adapter integration |
| `F_LWORD_TO_DINT` | LWORD | DINT | Conversion to 32-bit integer |
| `F_SINT_TO_LWORD` | SINT | LWORD | Reverse direction (if available) |

The **AL_TO_AS** stands out due to its adapter-to-adapter interface, which enables a direct connection between two different adapter types without the need for additional manual wiring of individual events and data.

## Conclusion

The **AL_TO_AS** function block is a practical, standards-compliant converter module for unidirectional adapters. It encapsulates the necessary type conversion from LWORD to SINT and simplifies integration into existing 4diac projects. Thanks to its composite structure and the use of an established conversion function, it is reliable, easy to understand, and extensible. It is particularly suitable for scenarios where data widths need to be reduced or interfaces adapted.

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
