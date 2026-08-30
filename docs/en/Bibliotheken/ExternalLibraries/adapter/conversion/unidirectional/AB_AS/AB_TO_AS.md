# AB_TO_AS

![AB_TO_AS](./AB_TO_AS.svg)

* * * * * * * * * *

## Introduction

The **AB_TO_AS** is a composite function block (FB) that converts a unidirectional AB adapter (BYTE) into a unidirectional AS adapter (SINT). It serves as a conversion bridge between two different data types in an IEC 61499-based control application.

## Interface Structure

The FB does not have its own top-level event or data ports. All communication takes place via two adapter interfaces:

### **Event Inputs**

- **E1** (via **AB_IN**, socket, type `adapter::types::unidirectional::AB`)

This event is received by the connected source adapter and triggers the conversion of a BYTE value to a SINT value.

### **Event Outputs**

- **E1** (via **AS_OUT**, Plug, Type `adapter::types::unidirectional::AS`)

This event is sent to the target adapter after successful conversion to signal the new SINT value.

### **Data Inputs**

- **D1** (BYTE, via **AB_IN** adapter)

Contains the BYTE value to be converted. It is sampled at the input via the **E1** event.

### **Data Outputs**

- **D1** (SINT, via **AS_OUT** adapter)

Provides the converted SINT value. It becomes valid at the output after the conversion is complete with the **E1** event.

### **Adapters**

| Adapter | Direction | Type | Description |
| --------- | ---------- | ----- | -------------- |
| **AB_IN** | Socket (Input) | `adapter::types::unidirectional::AB` | Receives BYTE data and a trigger event from the source system. |
| **AS_OUT** | Plug (Output) | `adapter::types::unidirectional::AS` | Provides the converted SINT data with an acknowledgment event to the target system. |

## Functionality

The **AB_TO_AS** function block internally contains a single function module of type `iec61131::conversion::F_BYTE_TO_SINT`. This module performs the actual data type conversion from BYTE to SINT.

1. An incoming event **AB_IN.E1** triggers the **F_BYTE_TO_SINT** function block via its **REQ** input.
2. Simultaneously, the data value from **AB_IN.D1** (BYTE) is placed on the **IN** input of the converter.
3. After processing, the converter signals its **CNF** event, which is forwarded to the adapter output **AS_OUT.E1**.
4. The converted SINT value is transferred from the **OUT** output of the converter to **AS_OUT.D1**.

This implements an asynchronous, event-driven translation of a BYTE value into a SINT value.

## Technical Features

- **Bit-reinterpretation, value-preserving** (destination is same width or wider than the source bit-string).

- **Composite FB**: The logic is completely encapsulated within the internal FB network structure. This facilitates maintenance and reuse.
- **License**: This module is provided under the **Eclipse Public License 2.0** (SPDX license identifier: EPL-2.0).
- **Version**: 1.0, released 2026.
- **Dependencies**: The internal converter module `F_BYTE_TO_SINT` from the library `iec61131::conversion` is required.

## State Overview

The **AB_TO_AS** module does not have its own state machine. Processing is purely data-flow and event-driven via the embedded **F_BYTE_TO_SINT** module. Therefore, there are no explicit states, only the implicit processes: *Waiting for input event*, *Conversion active*, and *Output event sent*.

## Application Scenarios

- **System Integration**: Connecting two subsystems that use different adapter data types (BYTE vs. SINT).
- **Data Format Conversion**: When an existing control algorithm expects SINT values, but the source only provides BYTE adapters.
- **Protocol Adaptation**: In heterogeneous automation environments where function blocks from different manufacturers or libraries need to be combined.

## Comparison with Similar Function Blocks

- **F_BYTE_TO_SINT** (Direct Function Block): Offers the same conversion logic, but without adapter encapsulation. Requires manual wiring of event and data lines.
- **AB_TO_INT** or **AB_TO_USINT**: Similar adapter converters for other target data types. **AB_TO_AS** is specifically designed for SINT.
- **Custom Implementation**: The composite design allows for easy extension, e.g., by adding plausibility checks or scaling, without changing the basic functionality.

**Company Implementation**

## Conclusion

The **AB_TO_AS** is a specialized yet simple composite function block that offers a clean and reusable solution for adapter-based data type conversion from BYTE to SINT. By utilizing a standardized converter block and clear event control, it integrates seamlessly into IEC 61499 networks. Its licensing under EPL 2.0 promotes open use and further development.
