# AX_TO_ALI

![AX_TO_ALI](./AX_TO_ALI.svg)

* * * * * * * * * *
## Introduction
The **AX_TO_ALI** is a composite function block (FB) that converts a unidirectional AX adapter (BOOL) into a unidirectional ALI adapter (LINT). It was developed to convert BOOL values received via an AX socket into LINT values and output them via an ALI plug. The block internally uses the IEC 61131 conversion function `F_BOOL_TO_LINT`.

## Interface Structure
The AX_TO_ALI has no direct event or data inputs/outputs. All communication takes place exclusively via adapters.

## **Event Inputs**
No separate event inputs. Events are received indirectly via the AX adapter socket.

### **Event Outputs**
No separate event outputs. Events are output indirectly via the ALI adapter plug.

### **Data Inputs**
No separate data inputs. Data is received indirectly via the AX adapter socket.

### **Data Outputs**
No separate data outputs. Data is output indirectly via the ALI adapter plug.

### **Adapter**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| `AX_IN` | Socket | `adapter::types::unidirectional::AX` | BOOL adapter input: Receives a BOOL signal via the unidirectional AX adapter. |

| `ALI_OUT` | Plug | `adapter::types::unidirectional::ALI` | LINT adapter output: Outputs the converted LINT value via the unidirectional ALI adapter. |

## Functionality
The module operates in an event-driven manner and performs the following steps upon each event received via the AX adapter socket:

1. **Event reception**: An event `E1` from the AX adapter is transmitted to the internal conversion module `F_BOOL_TO_LINT` (event `REQ`).

2. **Data Transfer**: The current BOOL value `D1` of the AX adapter is passed to the input `IN` of the conversion function.

3. **Conversion**: The internal function block converts the BOOL value into a LINT value (`FALSE` → `0`, `TRUE` → `1`).

4. **Data Output**: The converted LINT result is output via data output `OUT` to the data input `D1` of the ALI adapter.

5. **Event Output**: After successful conversion, an acknowledgment event `CNF` is sent to the ALI adapter output `E1`.

This enables synchronous, event-driven conversion from BOOL to LINT.

## Technical Specifications
- **License**: This function block is released under the **Eclipse Public License 2.0 (EPL-2.0)**.

Copyright © 2026 HR Agrartechnik GmbH.

- **Author & Version**: Developed by Franz Höpfinger, Version 1.0, February 17, 2026.

- **Adapter Package**: Uses adapters from the `adapter::types::unidirectional` package, which are designed for one-way data and event transmission.

- **Internal Implementation**: The conversion is performed using the IEC 61131 function block `F_BOOL_TO_LINT` from the library `iec61131::conversion`. This function block operates deterministically and does not require intermediate storage.

- **Hash Attribute**: The function block contains an empty type hash attribute (`eclipse4diac::core::TypeHash`).

## State Overview
The AX_TO_ALI function block does not have its own state machine. It forwards events and data directly to the internal conversion function block and outputs the result without delay. Since the internal function block `F_BOOL_TO_LINT` is pure function logic without state management, the entire composite function block behaves stateless. After each event at the AX adapter, the corresponding output is immediately generated at the ALI adapter.


## Application Scenarios

- **Type Conversion in Adapter Chains**: When a BOOL value arrives in an IEC 61499 application via a unidirectional AX adapter, but subsequent function blocks expect a LINT value (e.g., for counter functions or analog value processing).

- **Interface Adaptation**: Connecting binary sensors (BOOL) to control logic that works with integer LINT values.

- **Event-Driven Data Conversion**: Simple and fast conversion without intermediate storage, ideal for time-critical paths.

## Comparison with Similar Function Blocks
The library `iec61131::conversion` contains numerous function blocks for type conversion, e.g.,... Examples include `F_BOOL_TO_DINT`, `F_BOOL_TO_INT`, and `F_BOOL_TO_USINT`. The AX_TO_ALI differs in that it is already fully embedded in an adapter package and enables conversion between the unidirectional AX and ALI adapters. This eliminates the need for developers to manually wire sockets/plugs with a separate conversion block and provides a clean, reusable encapsulation.

## Conclusion
The AX_TO_ALI is a compact, license-compliant composite function block for reliably converting a BOOL value to a LINT value via unidirectional adapters. Its simple event handling and use of an established IEC function block make it a robust solution for typical conversion tasks in IEC 61499 systems. The clean separation of input and output via adapters facilitates integration into modular control architectures.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]