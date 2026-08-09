# AULI_TO_AUDI

![AULI_TO_AUDI](./AULI_TO_AUDI.svg)

* * * * * * * * * *
## Introduction

The function block **AULI_TO_AUDI** is a composite block that converts an AULI adapter (ULINT data) to an AUDI adapter (UDINT data). It serves as a unidirectional bridge between two different adapter types and enables the seamless integration of components based on different integer widths.
## Interface Structure

### **Event Inputs**

The function block does not have separate event inputs. The required event is received via the socket adapter:

- **E1** (in socket `AULI_IN`): Starts the conversion of a ULINT value.

### **Event Outputs**

There are no direct event outputs. The event is output via the plug adapter:

- **E1** (in plug `AUDI_OUT`): Signals the completion of the conversion and the provision of the UDINT value.

### **Data Inputs**

Data is provided exclusively via the socket adapter:

- **D1** (in socket `AULI_IN`): UDINT input value (64-bit unsigned integer).

### **Data Outputs**

Data is output via the plug adapter:

- **D1** (in plug `AUDI_OUT`): UDINT output value (32-bit unsigned integer).

### **Adapter**

- **Socket AULI_IN**

Type: `adapter::types::unidirectional::AULI`

Receives the ULINT value to be converted and the associated event.

- **Plug AUDI_OUT**

Type: `adapter::types::unidirectional::AUDI`

Provides the converted ULINT value and the completion event.

## Functionality

The function block contains an internal network with a single conversion block, `F_ULINT_TO_UDINT` (from the IEC 61131 library).

1. An incoming event **E1** from socket `AULI_IN` triggers the conversion block via its `REQ` event.

`` 2. Simultaneously, the ULINT value from `AULI_IN.D1` is forwarded to the input `IN` of the converter.

3. The converter transforms the 64-bit value into a 32-bit value and outputs the result to its output `OUT`.
4. After successful conversion, the converter sends an acknowledgment event (`CNF`), which is forwarded as **E1** to the plug `AUDI_OUT`.
5. The converted ULINT value is output to `AUDI_OUT.D1`.

## Technical Features

- **Composite FB**: The function block itself does not have its own logic but uses a standardized IEC 61131 converter.
- **Adapter Conversion**: Enables the connection of components based on different adapter definitions without requiring manual conversion by the user.
- **Unidirectional Data Flow**: Conversion is only performed in one direction (ULINT → UDINT); reverse conversion is not supported.
- **No Data Range Check**: Since UDINT only comprises 32 bits, higher-order bits are lost for ULINT values > 2³²‒1.

## State Overview

The Composite FB does not have its own state machine. Its behavior is entirely determined by the internal conversion block `F_ULINT_TO_UDINT`, which typically implements a simple wait/process state. After starting (`REQ`), it performs the conversion and acknowledges it with `CNF`.

## Application Scenarios

- **Adapter Bridges**: When a system provides an AULI adapter (e.g., for large counters or timestamps), but a downstream component expects an AUDI adapter (e.g., for smaller control values).
- **Protocol or Interface Adaptation**: In heterogeneous automation networks where different integer sizes are used.
- **Data Reduction**: When only the lower 32 bits of a 64-bit size are relevant (e.g., for certain sensor values).

## Comparison with Similar Function Blocks

- **Direct Type Conversions** (e.g., `F_ULINT_TO_UDINT`): These operate at the data level without adapters. AULI_TO_AUDI encapsulates the conversion in an adapter-based interface, which facilitates the exchange between different adapter types.
- **Bidirectional Converters**: Function blocks for the reverse conversion (UDINT → ULINT) also exist. This function block (FB) is specialized for one direction.
- **Composite Adapter**: Other composite FBs can contain multiple conversions or additional logic (e.g., range checking) – here, the focus is on simplicity and reusability.

## Conclusion

The AULI_TO_AUDI is a compact, specialized composite block that cleanly encapsulates the conversion of an AULI (ULINT) to an AUDI adapter (UDINT). Thanks to the integration of the standardized converter, it is reliable and easy to integrate into existing 4diac projects. It is ideally suited for scenarios where different adapter definitions meet and contributes to the modularity and reusability of function blocks.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
