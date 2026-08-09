# AW_TO_AUDI

![AW_TO_AUDI](./AW_TO_AUDI.svg)

* * * * * * * * * *
## Introduction

The function block `AW_TO_AUDI` is a composite block that converts a data value received via a WORD adapter (`AW`) into a UDINT value and outputs it via a UDINT adapter (`AUDI`). The conversion is performed using the internally used block `F_WORD_TO_UDINT` from the IEC 61131 library. The function block encapsulates the adapter interfaces and enables a clean separation between different data formats within a system.
## Interface Structure

### **Event Inputs**

- **AW_IN.E1** (via socket `AW_IN`): Trigger for conversion. An incoming event starts the conversion of the current WORD value.
- **Custom Event Inputs**: None – the function block receives events exclusively via the adapter `AW_IN`.

### **Event Outputs**

- **AUDI_OUT.E1** (via plug `AUDI_OUT`): Acknowledgement after successful conversion. The outgoing event signals that a new UDINT value is available at the data output.
- **Custom Event Outputs**: None – the function block forwards events exclusively via the adapter `AUDI_OUT`.

### **Data Inputs**

- **AW_IN.D1** (via socket `AW_IN`): The WORD value to be converted (16-bit).
- **Custom Data Inputs**: None.

### **Data Outputs**

- **AUDI_OUT.D1** (via plug `AUDI_OUT`): The converted UDINT value (32-bit, unsigned).
- **Custom Data Outputs**: None.

### **Adapters**

- **Socket `AW_IN`**: Expects an instance of adapter type `adapter::types::unidirectional::AW`. This adapter provides the event and data interface for the WORD input.
- **Plug `AUDI_OUT`**: Provides an instance of the adapter type `adapter::types::unidirectional::AUDI`. This adapter provides the event- and data-side interface for the UDINT output.

## Functionality

1. The function block waits for an event at **AW_IN.E1**.
2. Upon receiving the event, the current value of **AW_IN.D1** (WORD) is passed to the embedded function block `F_WORD_TO_UDINT`.
3. `F_WORD_TO_UDINT` performs the conversion and places the result (UDINT) at its output `OUT`.

`` 4. Once the conversion is complete, an event is sent via `Convert.CNF` to **AUDI_OUT.E1**, and the converted value is output via **AUDI_OUT.D1**.

Data flow and event control are synchronous: Each incoming event generates exactly one outgoing event with the updated data value.

## Technical Features

- **Composite Function Block**: The function block consists entirely of an internal network and has no state logic of its own.
- **Adapter Encapsulation**: All communication takes place via the standardized unidirectional adapters `AW` and `AUDI`. This allows the function block to be integrated into any system that supports these adapter interfaces.
- **Reuse**: The internally used conversion function `F_WORD_TO_UDINT` is part of the IEC 61131 library and ensures standards-compliant type conversion.
- **No Side Effects**: The function block (FB) does not perform any state changes or have any side effects outside of the actual conversion.

## State Overview

The FB `AW_TO_AUDI` does not have its own state machine. Sequence control is implemented by the internal block `F_WORD_TO_UDINT`, which exhibits simple REQ/CNF behavior:

- **Wait** (before REQ): No event at `AW_IN.E1` → no action.
- **Processing** (after REQ, before CNF): The conversion is running; the output is not updated.
- **Finished** (according to CNF): A new value is received at `AUDI_OUT.D1`, and an event is sent to `AUDI_OUT.E1`.

The overall function block reflects this behavior externally.

## Application Scenarios

- **Integration of Subsystems with Different Data Types**: A sensor delivers its values as WORD (e.g., a 16-bit counter) via an AW adapter, while a control unit expects UDINT values (32-bit) via an AUDI adapter.
- **Interface Adaptation in Modular Automation Systems**: Use in a component that communicates via an adapter but requires the actual data conversion from WORD to UDINT.
- **Creation of Conversion Cascades**: Together with other modules that use, for example, DINT or REAL adapters, any data format adaptations can be created.

## Comparison with Similar Modules

| Module | Input Adapter | Output Adapter | Conversion | Note |
|----------|-----------------|-----------------|---------------|-----------|
| `AW_TO_AUDI` | `AW` (WORD) | `AUDI` (UDINT) | WORD → UDINT | Composite, encapsulated `F_WORD_TO_UDINT` |
| Direct use of `F_WORD_TO_UDINT` | No adapters | No adapter | WORD → UDINT | Standard Function Block without Adapter Interfaces |
| `AW_TO_ADINT` (hypothetical) | `AW` (WORD) | `ADINT` (DINT) | WORD → DINT | Signed Analog Conversion |

The `AW_TO_AUDI` differs from directly using the conversion function by integrating adapters, making it immediately usable for adapter-based systems.

## Conclusion

The `AW_TO_AUDI` function block offers a simple and clean way to convert between two unidirectional adapters of types WORD and UDINT. By encapsulating the IEC conversion function and clearly defining the interfaces, it increases reusability and facilitates integration into existing adapter architectures. It is ideal for applications where different data widths or formats need to be exchanged via standardized adapters.
