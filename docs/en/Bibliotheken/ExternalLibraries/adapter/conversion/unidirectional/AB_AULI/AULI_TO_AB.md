# AULI_TO_AB

![AULI_TO_AB](./AULI_TO_AB.svg)

* * * * * * * * * *

## Introduction

The function block `AULI_TO_AB` is a composite function block that converts an AULI adapter (ULINT data type) into an AB adapter (BYTE data type). It enables the seamless connection of components using different adapter interfaces by converting the incoming data and providing it as a compatible output.

## Interface Structure

The function block has no direct event or data inputs/outputs. All input and output is handled via adapters.

### **Event Inputs**

None (events are received via the AULI adapter).

### **Event Outputs**

None (events are sent via the AB adapter).

### **Data Inputs**

None (data is received via the AULI adapter).

### **Data Outputs**

None (data is sent via the AB adapter).

### **Adapters**

| Name | Type | Direction | Comment |
| ------ | ----- | ---------- | ----------- |
| `AULI_IN` | `adapter::types::unidirectional::AULI` | Socket (Input Adapter) | ULINT adapter that provides the values to be converted and the trigger event |
| `AB_OUT` | `adapter::types::unidirectional::AB` | Plug (Output Adapter) | BYTE adapter that provides the converted values and the confirmation event |

## Functionality

The component internally uses the IEC 61131 component `F_ULINT_TO_BYTE` for ULINT to BYTE conversion. The process is as follows:

1. **Input**: An event (E1) is received at socket `AULI_IN`, triggering the conversion. Simultaneously, the data value (D1) is present as a ULINT.
2. **Processing**: The event and data are forwarded to the internal component `F_ULINT_TO_BYTE` (event `REQ`, data `IN`). This component performs the type conversion.
3. **Output**: After successful conversion, the internal block signals an event (`CNF`) and delivers the result (`OUT`) as a BYTE. Both are transferred to the plug `AB_OUT` (event E1, data D1).

The entire process occurs synchronously within one execution cycle of the composite block.

## Technical Features

- **Composite Block**: The logic is implemented entirely through the internal network of predefined blocks – there is no separate ECC (Execution Control Chart).
- **License and Copyright**: The block is licensed under the Eclipse Public License 2.0 (EPL-2.0) and is subject to third-party copyright.
- **Dependencies**: It requires the IEC 61131 function block `F_ULINT_TO_BYTE` from the library `iec61131::conversion`.
- **Package Structure**: The function block belongs to the package `adapter::conversion::unidirectional`.

## State Overview

Since the function block does not have its own ECC, there are no explicit states. The internal flow is strictly defined by the event chain `AULI_IN.E1 → Convert.REQ → Convert.CNF → AB_OUT.E1`.

## Application Scenarios

- Integration of a ULINT-providing sensor (e.g., a high-resolution distance sensor) into a control system based on BYTE adapter interfaces.
- Retrofitting existing systems where components with different adapter types (ULINT vs. BYTE) need to be integrated.
- Prototype development where ULINT values are temporarily processed via a BYTE channel (e.g., simulation or testing).

## Comparison with similar function blocks

Analog conversion function blocks exist for other data types (e.g., `AULI_TO_xx` or `xx_TO_AB`). The `AULI_TO_AB` is specifically optimized for converting ULINT to BYTE and utilizes the corresponding adapter types. Unlike generic function blocks, it avoids the manual wiring of individual events and data and offers an encapsulated, adapter-based interface.

## Conclusion

The `AULI_TO_AB` is a compact, reliable composite function block for converting between two common adapter types in the 4diac IDE. It reduces wiring effort and simplifies the integration of heterogeneous components. By using the standardized IEC 61131 conversion block, the conversion remains type-safe and efficient.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
