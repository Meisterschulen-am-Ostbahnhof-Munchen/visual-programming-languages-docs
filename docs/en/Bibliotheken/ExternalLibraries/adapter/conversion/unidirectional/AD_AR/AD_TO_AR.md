# AD_TO_AR

![AD_TO_AR](./AD_TO_AR.svg)

* * * * * * * * * *

## Introduction

The **AD_TO_AR** function block is a composite function block for converting a DWORD value from a unidirectional AD adapter (socket) into a REAL value, which is output via an AR adapter (plug). It encapsulates the conversion logic, thus enabling simple adapter-based data transfer between different data types.

## Interface Structure

The function block has no direct (individual) event or data inputs/outputs. All communication takes place via two adapter interfaces:

### **Event Inputs**

- *No direct event inputs* – event control is handled via the incoming adapter.

### **Event Outputs**

- *No direct event outputs* – event output is handled via the outgoing adapter.

### **Data Inputs**

- *No direct data inputs* – data is received via the incoming adapter.

### **Data Outputs**

- *No direct data outputs* – data is output via the outgoing adapter.

### **Adapters**

| Name | Type | Direction | Description |
| -------- | -------------------------------------------- | ---------- | ---------------------------------------------------------------------------- |
| AD_IN | `adapter::types::unidirectional::AD` | Socket | Receives an event (E1) and a DWORD value (D1) for conversion. |
| AR_OUT | `adapter::types::unidirectional::AR` | Plug | Sends an event (E1) with the converted REAL value (D1). |

## Functionality

The function block operates as an event-driven pipeline:

1. An incoming event at socket **AD_IN.E1** triggers the conversion.
2. The data value **AD_IN.D1** (DWORD) is passed to the internal function block `F_DWORD_TO_REAL`.
3. After successful conversion, the internal function block signals an output event (**CNF**).
4. This event is forwarded to plug **AR_OUT.E1**, and simultaneously, the converted REAL value is output via **AR_OUT.D1**.

The value conversion is performed according to the IEC 61131 standard function `DWORD_TO_REAL`.

## Technical Features

- **Composite Function Block**: The conversion logic is implemented entirely within an internal network consisting of a single function block.
- **Type Conversion via Adapter**: This function block enables the connection of components that communicate exclusively via adapter interfaces, eliminating the need for additional manual conversions.
- **Standard Compliance**: Utilizes the IEC 61131 library function `F_DWORD_TO_REAL`, making it portable and well-tested.
- **Unidirectional Adapters**: Both input and output adapters are unidirectional, meaning data flows in only one direction.

## State Overview

The function block does not have its own state machine. Processing is strictly causal: An event at the input immediately triggers the conversion and output. There are no delays or intermediate states.

## Application Scenarios

- **Adapter Bridge**: Connects a component that provides DWORD via adapter (e.g., from a binary sensor value) to a component that expects REAL via adapter (e.g., a floating-point controller).
- **Value Conversion in Adapter Networks**: When adapters of different data types interact in a 4diac IDE application, this function block can serve as a simple converter.
- **Data Preparation**: Before further processing in analysis or visualization blocks that require real values.

## Comparison with Similar Function Blocks

Similar conversion function blocks exist for other data types, e.g.:

- `WORD_TO_REAL` or `INT_TO_REAL` – directly as individual function blocks,
- `AD_TO_AR` – as a composite with an adapter interface.

The advantage of `AD_TO_AR` lies in its seamless integration into adapter-based architectures, whereas pure IEC 61131 function blocks often require manual connections.

## Conclusion

The **AD_TO_AR** block offers a compact and standards-compliant solution for converting DWORD values to REAL values via adapter interfaces. Its encapsulation as a composite increases reusability and simplifies the design of adapter-based automation solutions.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
