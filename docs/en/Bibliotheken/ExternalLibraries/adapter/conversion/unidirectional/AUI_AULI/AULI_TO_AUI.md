# AULI_TO_AUI
![AULI_TO_AUI](./AULI_TO_AUI.svg)
* * * * * * * * * *
## Introduction
The function block **AULI_TO_AUI** is a composite function block (FB) that converts an **AULI** adapter (based on the data type `ULINT`) into an **AUI** adapter (based on the data type `UINT`). It is used when a 64-bit unsigned integer interface (`ULINT`) needs to be mapped to a 16-bit unsigned integer interface (`UINT`), for example, when connecting different sensor or actuator components in automation technology.
```
## Interface Structure
### **Event Inputs**
An event of type `AULI_IN` is provided via the adapter socket. This is forwarded internally to the conversion module.

### **Event Outputs**
An event of type `AUI_OUT` is output via the adapter plug as soon as the conversion is complete.

### **Data Inputs**
A data value of type `D1` (corresponding to `ULINT`) is received via the adapter socket `AULI_IN`.

#
## ### **Data Outputs**
The adapter plug `AUI_OUT` outputs a data value of type `D1` (equivalent to `UINT`).

### **Adapter**

| Name | Direction | Type |

|----------|----------|----------------------------|

| AULI_IN | Socket | `adapter::types::unidirectional::AULI` |

| AUI_OUT | Plug | `adapter::types::unidirectional::AUI` |

## Functionality

The function block operates in an event-driven manner:

1. An event at input `AULI_IN.E1` triggers the internal function block `F_ULINT_TO_UINT` via its input `REQ`.

2. The data value `AULI_IN.D1` is directly passed to the conversion block as input `IN`.

3. The conversion block converts the `ULINT` value into a `UINT` value.

4. After the conversion is complete, the output `CNF` of the conversion block signals an event, which is then forwarded to the output `AUI_OUT.E1`.

5. Simultaneously, the converted value is transferred from the `OUT` output of the conversion module to the `AUI_OUT.D1` output.

The conversion is performed according to IEC 61131 standard `F_ULINT_TO_UINT`. Values greater than `65535` (maximum `UINT` value) may result in an overflow, which must be handled by the application.

## Technical Features
- **Adapter-Based Encapsulation**: The module allows for the seamless replacement of adapters in the 4diac IDE without changing the logic of the surrounding network.
- **Reuse of IEC standard conversion**: The actual type conversion is performed by the standardized IEC function block `F_ULINT_TO_UINT`, ensuring portability and correctness.
- **No state storage**: The function block is purely combinatorial – after each execution, the current result is available at the output.

## State overview
The function block does not have its own finite state machine. The internal conversion is event-driven and without internal states. The runtime is determined solely by the underlying `F_ULINT_TO_UINT` function block.

## Application scenarios
- **Sensor integration**: A 64-bit sensor (e.g., high-resolution displacement measurement) is connected to a controller that only accepts 16-bit inputs.
- **Communication Gateway**: Adapter interfaces between bus systems (e.g., CANopen with 64-bit data to PROFINET I device with 16-bit data).
- **Data Reduction**: Targeted reduction of the resolution for subsequent processing steps (e.g., display or simple threshold logic).

## Comparison with similar components

| Component | Input type | Output type | Special feature |

|---------------|-------------|-------------|-------------|

| `AULI_TO_AUI` | `ULINT` | `UINT` | Adapter Wrapper, Event-Driven |

| `F_ULINT_TO_UINT` | `ULINT` | `UINT` | Pure Function, No Adapter |

| `AUI_TO_AULI` | `UINT` | `ULINT` | Reverse Direction (Not Available) |

Unlike a bare IEC function, this block offers an adapter-compliant input and output interface, thus enabling easy integration into adapter-based architectures.

## Conclusion
The **AULI_TO_AUI** block is a practical solution for mapping 64-bit UINT data to 16-bit UINT data using a standardized adapter mechanism. It combines the robustness of IEC conversion functionality with the flexibility of 4diac adapters and is particularly well-suited for heterogeneous automation systems where different data types interact.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
