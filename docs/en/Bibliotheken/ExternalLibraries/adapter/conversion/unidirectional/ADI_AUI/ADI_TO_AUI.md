# ADI_TO_AUI

![ADI_TO_AUI](./ADI_TO_AUI.svg)

* * * * * * * * * *
## Introduction

The **ADI_TO_AUI** function block is a composite function block that implements interface conversion between the ADI adapter (DINT, 32-bit integer) and the AUI adapter (UINT, 16-bit integer). It enables the unidirectional transfer of a value from a DINT adapter to a UINT adapter using a standardized IEC 61131 conversion block.
## Interface Structure

### **Event Inputs**

None – event control is handled exclusively via the adapters.

#### **Event Outputs**

None.

### **Data Inputs**

None – all data is provided via the socket adapter.

### **Data Outputs**

None – all data is output via the plug adapter.

### **Adapters**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| Socket | `ADI_IN` | Input | ADI adapter (DINT) – provides the value to be converted and an event |
| Plug | `AUI_OUT` | Output | AUI adapter (UINT) – provides the converted value and the associated event |

## Functionality

The function block does not have its own input/output events or top-level data points. All control and data transmission is handled via the two adapters:

1. **Event Forwarding**:

The event `E1` received at socket `ADI_IN` is forwarded directly to the internal block `F_DINT_TO_UINT` (type: `iec61131::conversion`) to trigger a conversion.

2. **Data Path**:

The DINT value provided via `ADI_IN.D1` is passed to input `IN` of `F_DINT_TO_UINT`. After successful conversion, the result (UINT) is available at output `OUT` and is assigned to the data output `D1` of the plug adapter `AUI_OUT`.

3. **Feedback**:

The internal function block signals the end of the conversion with the event `CNF`. This event is transferred to the output event `E1` of the plug adapter `AUI_OUT` – synchronously with the provided data value.

Thus, the function block implements a **unidirectional, event-driven** transfer of a DINT value to a UINT value via the adapter interfaces.

## Technical Features

- **Composite Function Block**: The function block fully encapsulates the conversion logic and offers a clean, reusable interface.
- **Core Function Block Used**: `iec61131::conversion::F_DINT_TO_UINT` – a standardized IEC 61131 function for converting DINT to UINT (value range adjustment: DINT to UINT is considered without a sign; negative values are converted accordingly).
- **Adapter Types**: The adapters `ADI` and `AUI` are defined as unidirectional adapters (`adapter::types::unidirectional`). They each provide an event pair (`E1`/`E1`) and a data point (`D1` in the corresponding data type).
- **Package Structure**: The function block is organized in the package `adapter::conversion::unidirectional`.
- **License**: The function block is subject to the Eclipse Public License 2.0 (EPL-2.0). Copyright belongs to HR Agrartechnik GmbH.

## State Overview

As a composite function block, **ADI_TO_AUI** does not have its own internal state machine. The state is determined exclusively by the embedded function block `F_DINT_TO_UINT`, which performs the conversion after receiving the `REQ` event and completes with `CNF`. The function block is therefore **stateless** in the sense of a pure function block (no stored states outside the core function block).

## Application Scenarios

- **Interface adaptation** between system components that use different data types for analog or digital values (e.g., sensors with DINT output and actuators with UINT input).
- **Data consolidation** in heterogeneous IEC 61499 networks where adapters of different data types interact.
- **Prototypes and Migration**: Easy integration of function blocks that originally work with DINT into an environment that expects UINT – without manual conversion at each connection step.

## Comparison with Similar Function Blocks

Directly comparable adapter conversion blocks exist for other data types (e.g., `BOOL_TO_UINT`, `INT_TO_DINT`). The difference with **ADI_TO_AUI** lies in the specific combination of adapter interfaces (ADI ↔ AUI). Unlike simple conversion function blocks (`F_DINT_TO_UINT`), this composite function block encapsulates both the adapter connection and the event and data synchronization in a reusable module.

An alternative design could use a generic conversion block with configurable adapter types; however, the dedicated solution offers clearer documentation and easier handling within the 4diac IDE.

## Conclusion

The **ADI_TO_AUI** function block provides a clean, maintainable, and standardized way to convert DINT data via an ADI adapter to a UINT signal via an AUI adapter. By using an IEC 61131 core block, the conversion is standards-compliant and reliable. The composite approach increases reusability and simplifies engineering in distributed automation systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
