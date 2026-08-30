# AX_TO_AS

![AX_TO_AS](./AX_TO_AS.svg)

* * * * * * * * * *
## Introduction

The function block `AX_TO_AS` is a composite function block that converts a BOOL adapter (type AX) into a SINT adapter (type AS). It encapsulates the conversion of a binary signal into a signed 8-bit value and provides this via a standardized adapter interface.
## Interface Structure

### **Event Inputs**

No separate event inputs; event control is handled via the AX_IN adapter (see Adapters).

### **Event Outputs**

No separate event outputs; event output is handled via the AS_OUT adapter (see Adapters).

### **Data Inputs**

No separate data inputs; Data is transferred via the AX_IN adapter (see Adapters).

### **Data Outputs**

No separate data outputs; data is output via the AS_OUT adapter (see Adapters).

### **Adapters**

- **AX_IN** (Socket):

Type `adapter::types::unidirectional::AX` (BOOL).

Provides the binary input signal via the event port `E1` and the data port `D1`.

- **AS_OUT** (Plug):

Type `adapter::types::unidirectional::AS` (SINT).

Outputs the converted SINT signal via the event port `E1` and the data port `D1`.

## Functionality

The function block (FB) has an internal network consisting of an instance of the standard function block `F_BOOL_TO_SINT`.

1. An incoming event at the AX_IN adapter (`E1`) triggers the conversion.
2. The data value of `AX_IN.D1` (BOOL) is passed to the input `IN` of the conversion function block.
3. The conversion function block converts the BOOL value into a SINT value (`TRUE` → 1, `FALSE` → 0).
4. The result is provided at output `OUT` and forwarded to the AS_OUT adapter (`D1`).
5. An acknowledgment event is output via `AS_OUT.E1`.

## Technical Features

- **Bit-reinterpretation, value-preserving** (destination is same width or wider than the source bit-string).

- **Composite Structure**: The function block (FB) is implemented as a composition, making the internal logic transparent and reusable.
- **Standard Conversion**: Uses the standardized FB `iec61131::conversion::F_BOOL_TO_SINT` from the IEC 61131 library.
- **Adapter Interface**: Input and output are exclusively via unidirectional adapters (sockets/plugs), enabling modular connections in adapter-based architectures.

## State Overview

The FB does not have any explicitly modeled states. The behavior is purely event-driven: Every event at the input adapter triggers a conversion, after which an output event is sent.

## Application Scenarios

- **Binary Sensor Connection**: A binary sensor (e.g., limit switch) is read via an AX adapter and passed to a controller as a SINT value.
- **Protocol Adaptation**: In systems requiring SINT-based adapters, existing BOOL adapters can be connected without additional coding.
- **Test Environments**: Easy switching between BOOL and SINT signals to verify adapter communication paths.

## Comparison with Similar Components

- **Direct Conversions (`F_BOOL_TO_SINT`)**: These operate at the data level without adapters. The `AX_TO_AS` encapsulates the conversion in an adapter-based interface and is therefore easier to integrate into adapter networks.
- **Other adapter converters (e.g., `AS_TO_AX`)**: These represent the reverse direction; `AX_TO_AS` complements them as a counterpart.

## Conclusion

The `AX_TO_AS` is a simple yet useful composite function block for converting BOOL adapter signals to SINT adapter signals. By using a standardized conversion block and adapter technology, it can be flexibly integrated into existing 4diac projects and contributes to the clean separation of signal types.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
