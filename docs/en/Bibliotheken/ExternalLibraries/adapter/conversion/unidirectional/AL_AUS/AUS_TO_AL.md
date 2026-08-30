# OFF_TO_AL

![AUS_TO_AL](./AUS_TO_AL.svg)

* * * * * * * * * *

## Introduction

The **OFF_TO_AL** function block is a composite function block (FB) that converts a unidirectional **OFF** adapter (USINT data type) into a unidirectional **AL** adapter (LWORD data type). It serves as a bridge between different data formats in a 4diac IDE environment, with the conversion being performed internally by the IEC 61131 FB `F_USINT_TO_LWORD`. The function block facilitates the integration of components based on different adapter types.

## Interface Structure

Because it is a composite FB, all I/O signals are provided via the two adapters. The FB itself does not have any independent event or data inputs/outputs.

### **Event Inputs**

- No standalone event inputs.

### **Event Outputs**

- No standalone event outputs.

### **Data Inputs**

- No standalone data inputs.

### **Data Outputs**

- No standalone data outputs.

### **Adapter**

| Name | Type | Direction | Description |
| ------------- | ----- | ----------- | -------------- |
| **OFF_IN** | `adapter::types::unidirectional::AUS` | Socket (Input) | Receives the USINT value and the associated event. The adapter provides an internal event input `E1` and a data input `D1` (USINT). |
| **AL_OUT** | `adapter::types::unidirectional::AL` | Plug (Output) | Outputs the converted LWORD value. The adapter also provides an internal event output `E1` and a data output `D1` (LWORD). |

## Functionality

1. The **AUS_IN** socket receives an event at its internal input `E1` and the corresponding USINT value at `D1`.

**AL_OUT** | `adapter::types::unidirectional::AL` | Plug (Output) | Outputs the converted LWORD value. 2. This event is internally forwarded to the **REQ** input of the conversion function block `F_USINT_TO_LWORD`; the USINT value is placed at its **IN** input.

1. The function block `F_USINT_TO_LWORD` performs the conversion from USINT (8-bit unsigned) to LWORD (64-bit unsigned).
2. After the conversion is complete, an event is generated at the **CNF** output of `F_USINT_TO_LWORD`, which is sent to the internal event input of the **AL_OUT** adapter (`E1`). Simultaneously, the converted LWORD value is placed at the data output `D1` of the adapter.

The conversion is then performed by the function block `F_USINT_TO_LWORD`. 5. The parent function block can then retrieve the LWORD value via the **AL_OUT** plug and use the event.

The entire sequence is strictly causal: The conversion is only triggered when an event arrives at **AUS_IN**.

## Technical Features

- **Composite FB**: The function block encapsulates the conversion logic in a reusable adapter pair.
- **Library Used**: The actual type conversion is performed by `iec61131::conversion::F_USINT_TO_LWORD` from the IEC 61131 standard library.
- **No State**: The function block is purely combinatorial with event-driven execution; it does not store any internal states.
- **Adapter Unidirectionality**: Both AUS and AL are defined as unidirectional adapters, meaning data flows in only one direction (input → output).

## State Overview

This function block does not have its own state diagram. Its behavior is determined exclusively by the event/data flows of the embedded function block `F_USINT_TO_LWORD`:

- **Idle**: Waiting for an event at **OFF_IN**.
- **Conversion Active**: As soon as an event arrives, the conversion is performed. Upon completion, the output event is generated, and the function block returns to the idle state.

## Application Scenarios

- **Data Format Adaptation**: A sensor or controller delivers data as a USINT value (e.g., counter readings), but the downstream component expects LWORD (e.g., for large data ranges or timestamps).
- **Adapter Bridges**: If components with different adapter types need to be connected in a 4diac application, this function block enables clean, type-safe conversion.
- **Legacy System Support**: Legacy systems that output USINT data can be integrated into modern LWORD interfaces using this function block.

## Comparison with Similar Function Blocks

- **F_USINT_TO_LWORD**: A pure function block (Basic FB) without adapter encapsulation. It can be used directly in a network but requires manual cabling of events and data.
- **AUS_TO_AL**: Offers a higher level of abstraction through the use of adapters. This improves the reusability and interchangeability of components because the adapter interfaces are standardized.
- **Other Type Converters** (e.g., `INT_TO_DWORD`): Similar logic, but for different data types; this function block fills the specific gap between USINT and LWORD.

## Conclusion

The **AUS_TO_AL** function block is a practical composite function block for converting USINT to LWORD data, packaged in an adapter-based interface. It utilizes the proven IEC 61131 conversion and allows for seamless integration into modular 4diac applications. Thanks to the adapter encapsulation, the interface remains clearly defined, and the block can be easily integrated into existing communication structures.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
