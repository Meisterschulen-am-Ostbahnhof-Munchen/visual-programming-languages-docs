# AULI_TO_ADI

![AULI_TO_ADI](./AULI_TO_ADI.svg)

* * * * * * * * * *
## Introduction

The **AULI_TO_ADI** function block is a composite module for converting an **AULI** adapter (unsigned 64-bit value) into an **ADI** adapter (signed 32-bit value). It enables simple conversion between two unidirectional adapter interfaces and internally utilizes an IEC 61131 type conversion function.
## Interface Structure

The module has no event or data inputs/outputs of its own. All communication takes place exclusively via the two adapters.

### **Event Inputs**

None (exclusively via adapters).

### **Event Outputs**

None (exclusively via adapters).

### **Data Inputs**

None (exclusively via adapter).

### **Data Outputs**

None (exclusively via adapter).

### **Adapters**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AULI` | `AULI_IN` | Socket / Input | Receives a ULINT value via event and data channels (E1, D1) |
| `adapter::types::unidirectional::ADI` | `ADI_OUT` | Plug / Output | Provides the converted DINT value via event and data channels (E1, D1) |

## Functionality

The module operates as a pure cascade:

1. An event at socket `AULI_IN.E1` triggers the data transfer from `AULI_IN.D1` (ULINT).
2. This event is transferred to the input `REQ` of the internal conversion module `F_ULINT_TO_DINT` (IEC 61131 type conversion).
3. The converter transforms the ULINT value into a DINT value and places it at its output `OUT`.
4. After the conversion is complete, the converter signals the event with `CNF`, which triggers the plug `ADI_OUT.E1` and simultaneously makes the converted value available on `ADI_OUT.D1`.
5. The connected receiver thus receives a DINT value that corresponds to the original ULINT value – insofar as it can be represented (DINT value range: -2³¹ … 2³¹‒1).

## Technical Features

- **Adapter-based**: The function block does not implement direct input/output variables, but uses only adapter sockets and plugs for loose coupling.
- **Type conversion**: The conversion is performed using the IEC 61131 standard function block `F_ULINT_TO_DINT`. ULINT values outside the DINT range can lead to overflows or unexpected results.
- **Compact Structure**: Since there is no state logic or branching, the function block operates deterministically and without delay beyond the pure conversion time.
- **Package**: The function block is packaged in `adapter::conversion::unidirectional`.

## State Overview

The function block has no internal state machine. It behaves like a pure functional mapping: An input event is immediately followed by an output event with the converted value.

## Application Scenarios

- **Interface Adaptation**: When a sensor or controller provides a ULINT adapter, but the downstream system expects a DINT adapter.
- **Data Reduction**: Reducing the bit width from 64 to 32 bits in cases where a 32-bit resolution is sufficient.
- **Adapter Cascades**: Used as a link in a seamless conversion chain between different data adapter types.

## Comparison with Similar Function Blocks

- **AULI_TO_UDI**: Converts ULINT to UDINT (unsigned 32-bit) – the value range remains positive, and overflows only occur with values > 2³²‒1.
- **DIRECT_CONVERT**: A generic function block with direct data input and output that does not use adapters – AULI_TO_ADI, on the other hand, offers loose coupling and standardized adapter interfaces.
- **Manual Conversion**: Without this function block, the conversion would have to be implemented in the application function block itself – AULI_TO_ADI encapsulates this task and promotes reusability.

## Conclusion

**AULI_TO_ADI** is a specialized, adapter-based conversion module that efficiently and in a standardized manner handles the conversion of ULINT to DINT data via unidirectional adapters. By utilizing an IEC 61131-compliant conversion function block, the conversion is reliable, and the simple adapter interface allows for flexible integration into existing systems. This module is particularly well-suited for loosely coupled architectures where data formats need to be adapted without burdening the application logic with type conversion.
