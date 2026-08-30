# OFF_TO_AB

![AUS_TO_AB](./AUS_TO_AB.svg)

* * * * * * * * * *

## Introduction

The **OFF_TO_AB** is a composite function block for converting a unidirectional **OFF adapter** (USINT data type) to an **AB adapter** (BYTE data type). It serves as a bridge between different adapter interfaces in automation systems and enables the seamless integration of components based on different data types. Internally, the block uses the standard conversion block *F_USINT_TO_BYTE* from the IEC 61131 library.

## Interface Structure

### **Event Inputs**

The block does not have its own event input ports. Events are received via the **OFF_IN** adapter (socket):

- **OFF_IN.E1** – Trigger for data conversion and forwarding to the output.

### **Event Outputs**

Events are output via the **AB_OUT** adapter (plug):

- **AB_OUT.E1** – Confirmation that the converted value is present at the output.

### **Data Inputs**

Data is provided via the **AUS_IN** adapter:

- **AUS_IN.D1** (USINT) – The 8-bit unsigned integer value to be converted.

### **Data Outputs**

Data is passed through the **AB_OUT** adapter:

- **AB_OUT.D1** (BYTE) – The converted byte value.

### **Adapters**

| Name | Type | Direction | Description |
| ----------- | ---------------------------------------- | ---------- | -------------- |
| **AUS_IN** | `adapter::types::unidirectional::AUS` | Socket | Input adapter for USINT data and events. |
| **AB_OUT** | `adapter::types::unidirectional::AB` | Plug | Output adapter for BYTE data and events. |

## Functionality

The **AUS_TO_AB** is implemented as a pure composite function block without its own logic. It connects the AUS_IN and AB_OUT adapters via the internal function block **F_USINT_TO_BYTE**:

1. An incoming event on **AUS_IN.E1** triggers the conversion function block **Convert** (`F_USINT_TO_BYTE`) via its **REQ** input.
2. Simultaneously, the data value from **AUS_IN.D1** is passed to the **Convert.IN** input.
3. After the conversion (USINT → BYTE) is complete, **Convert** acknowledges with an event on **CNF**.
4. This event is forwarded directly to **AB_OUT.E1**.
5. The converted byte value from **Convert.OUT** is passed to **AB_OUT.D1**.

This ensures synchronized, event-driven data transfer.

## Technical Features

- **Composite FB**: Does not contain its own state machine; all logic is implemented by the internal FB `F_USINT_TO_BYTE`.
- **Unidirectional Adapters**: Both the incoming and outgoing adapters are unidirectional – data flows occur exclusively in one direction.
- **Standard Compliance**: The block is based on IEC 61499-2 and uses the IEC 61131 conversion function `F_USINT_TO_BYTE`. This makes it immediately usable in compatible runtime environments (e.g., 4diac-FORTE).
- **License**: Released under the Eclipse Public License 2.0 (EPL-2.0). Copyright © 2026 HR Agrartechnik GmbH.

## State Overview

Since this is a composite function block without its own ECC (Execution Control Chart), there is no explicit state machine. Its behavior is purely event-driven and determined by the internal interconnection of the individual function blocks. After startup, the system is always ready – an incoming event is processed immediately.

## Application Scenarios

- **System integration** in agricultural technology or other automation environments where an **OFF adapter** (USINT) needs to be connected to an **AB adapter** (BYTE).
- **Retrofitting older components** that provide a BYTE output with modern USINT-based sensors or actuators.
- **Prototyping and test setups** where rapid switching between different adapter types is required.
- **Data processing** in communication nodes that standardize different adapter protocols.

## Comparison with Similar Function Blocks

- **F_USINT_TO_BYTE** – a direct function block for pure data type conversion, but without adapter integration. **AUS_TO_AB** adds the adapter and event logic.
- **BYTE_TO_USINT** – inverse conversion (BYTE → USINT) if the reverse adapter direction is required (not included with this function block).
- **Generic Adapter Converters** – more complex blocks that convert multiple data types simultaneously. **AUS_TO_AB** is optimized for the specific use case and is therefore more compact.

## Conclusion

The **AUS_TO_AB** is a useful and lightweight function block for converting an **AUS adapter (USINT)** to an **AB adapter (BYTE)**. Its composite structure minimizes implementation effort, while the use of a standardized conversion block ensures reliability. This module is particularly suitable for the rapid integration of heterogeneous adapter interfaces into IEC 61499-based control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
