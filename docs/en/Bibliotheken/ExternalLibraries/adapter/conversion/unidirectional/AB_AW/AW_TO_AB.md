# AW_TO_AB

![AW_TO_AB](./AW_TO_AB.svg)

* * * * * * * * * *
## Introduction
The function block `AW_TO_AB` is a composite block that converts a unidirectional WORD adapter (`AW`) into a unidirectional BYTE adapter (`AB`). It serves as an interface converter between components based on different data types. The conversion is performed by the integrated standard function block `F_WORD_TO_BYTE`.

## Interface Structure
### **Event Inputs**
The block does not have its own event inputs. Instead, the trigger signal is provided via the adapter input `AW_IN` (event `E1`).

### **Event Outputs**
The function block does not have its own event outputs. The result is signaled via the adapter output `AB_OUT` (event `E1`).

### **Data Inputs**
The function block does not have its own data inputs. The WORD value to be converted is provided via the adapter input `AW_IN` (data `D1`).

### **Data Outputs**
The function block does not have its own data outputs. The converted BYTE result is output via the adapter output `AB_OUT` (data `D1`).

### **Adapter**

| Name | Direction | Type | Description |

|------|----------|-----|-------------|

| `AW_IN` | Socket (Input) | `adapter::types::unidirectional::AW` | WORD adapter with one event `E1` and one data value `D1` (WORD) |

| `AB_OUT` | Plug (Output) | `adapter::types::unidirectional::AB` | BYTE adapter with one event `E1` and one data value `D1` (BYTE) |

## Functionality
This function block performs a simple data conversion from WORD (16 bits) to BYTE (8 bits). The process is as follows:

1. An event at the adapter input `AW_IN.E1` triggers the internal function block `F_WORD_TO_BYTE`.

2. The data value `AW_IN.D1` (WORD) is passed as an input to `F_WORD_TO_BYTE.IN`.

3. After the conversion, the result is forwarded via `F_WORD_TO_BYTE.OUT` to the adapter output `AB_OUT.D1`.

4. The output `AB_OUT.E1` is activated to signal completion.

The conversion according to IEC 61131-3 returns the least significant byte (low byte) of the WORD value by default.

## Technical Features

- **Unidirectional Adapter**: The module operates in only one data flow direction – from the socket to the plug.

- **Integrated Conversion**: The actual conversion is performed by the established module `F_WORD_TO_BYTE`, so no custom logic needs to be implemented.

- **Data Loss**: Since a WORD (16 bits) is mapped to a BYTE (8 bits), the upper 8 bits are lost. This must be taken into account in the application.

- **Package Structure**: The function block is located in package `adapter::conversion::unidirectional` and uses the import `iec61131::conversion::F_WORD_TO_BYTE`.

## State Overview
The composite function block does not have its own state machine. Its operation is purely event-driven:

- **Idle**: Waiting for an event at socket `AW_IN`.

- **Conversion Active**: After receiving an event, the internal function block `F_WORD_TO_BYTE` is executed (combinatorial logic without wait cycles).

- **Output**: Once the conversion is complete, the event is output to plug `AB_OUT`, along with the new data value.

## Application Scenarios

- **Protocol Adaptation**: When a sensor provides a WORD value, but the actuator only supports BYTE-capable adapters.

- **Interface Reduction**: In hierarchical control systems where byte sizes are used for performance or memory reasons.

- **Adapter Bridge**: As an intermediary in a 4diac IDE application to connect components with incompatible adapter types.

## Comparison with Similar Blocks

- **`F_WORD_TO_BYTE`**: A pure data conversion block without adapter integration. `AW_TO_AB` encapsulates this block and provides a standardized adapter interface.

- **`AW_TO_AW` (identical type)**: Not useful; this block is specifically designed for type conversion.

- **Manual Conversion**: Without this component, the developer would have to manually insert `F_WORD_TO_BYTE` into the network and wire the adapter connections themselves – this composite component simplifies this process.

## Conclusion
`AW_TO_AB` is a simple yet useful composite component for converting a WORD adapter to a BYTE adapter. It reduces the wiring effort in 4diac applications and ensures consistent conversion by reusing the standard component `F_WORD_TO_BYTE`. Users should be aware of the potential data loss due to the reduced bit width.


---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]