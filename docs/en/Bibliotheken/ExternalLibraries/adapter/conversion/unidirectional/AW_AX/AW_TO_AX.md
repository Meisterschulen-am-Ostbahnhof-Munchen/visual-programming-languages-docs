# AW_TO_AX

![AW_TO_AX](./AW_TO_AX.svg)

* * * * * * * * * *
## Introduction

The composite function block **AW_TO_AX** converts an **AW adapter** (WORD) into an **AX adapter** (BOOL). It checks whether the 16-bit value received via the AW adapter is non-zero and outputs the result as a Boolean signal via the AX adapter.
## Interface Structure

This function block does not have traditional event or data inputs/outputs, but only adapter interfaces.

### **Event Inputs**

No separate event inputs. Events are received via the socket adapter.

### **Event Outputs**

No separate event outputs. Events are sent via the plug adapter.

### **Data Inputs**

No separate data inputs. Data is received via the socket adapter.

### **Data Outputs**

No separate data outputs. Data is sent via the plug adapter.

### **Adapters**

| Name | Type | Direction | Comment |
|--------|----------------------------------------|----------|--------------------------|
| AW_IN | adapter::types::unidirectional::AW | Socket | WORD adapter input |
| AX_OUT | adapter::types::unidirectional::AX | Plug | BOOL adapter output |

The socket **AW_IN** provides the event and data interface of a **WORD**-based adapter.

The plug **AX_OUT** provides the event and data interface of a **BOOL**-based adapter.

## Functionality

When an event arrives at **AW_IN.E1**, the value of **AW_IN.D1** is compared to the constant value **WORD#0**. Internally, the function block **F_NE** (non-equal comparison from IEC 61131) is used for this comparison.

- If **AW_IN.D1 ≠ 0**, an event is sent to **AX_OUT.E1** and the data value **AX_OUT.D1** is set to **TRUE**.
- Otherwise, no event is generated at the output and the data value remains **FALSE** (i.e., it is not changed).

This behavior is event-driven and follows the IEC 61499 execution semantics: An event at the input triggers the comparison, the result of which is passed on to the output.

- If **AW_IN.D1 ≠ 0**, an event is sent to **AX_OUT.E1** and the data value **AX_OUT.D1** is set to **TRUE**.
-
## Technical Features

- The function block is implemented as a **composite function block**, meaning its functionality is represented by an internal network consisting of a single **F_NE** function block.
- It uses a **unidirectional adapter** (AW and AX) according to the adapter definition of the 4diac IDE.
- The comparison logic is taken from the IEC 61131 library (`iec61131::comparison::F_NE`).
- It is a pure signal conversion without any state management.

## State Overview

The function block has **no internal state machine** (no ECC). The sequence control is derived directly from the internal network: An event at the input adapter triggers the comparison block, which in turn passes the result to the output adapter.

## Application Scenarios

- **Signal Conditioning:** Conversion of a digital WORD value (e.g., from a sensor module) into a Boolean signal that indicates whether the value is non-zero.
- **Adapter Integration:** Use in systems that require adapter-based communication between different data types (e.g., linking a WORD-based bus component with BOOL-based control logic).
- **Threshold Check:** By changing the comparison value (in the internal block **F_NE**), the function block could also be adapted to other threshold values (e.g., "Value > 100").

## Comparison with Similar Blocks

- **WORD_TO_BOOL:** Simple, direct conversion of a WORD data type to BOOL (e.g., bit 0). In contrast, **AW_TO_AX** uses adapters and performs a comparison with zero – it reacts to the entire word.
- **Unequal Comparator (F_NE):** The **AW_TO_AX** encapsulates the **F_NE** block and adds the adapter interfaces, enabling its use in adapter-based architectures.

## Conclusion

The **AW_TO_AX** is a compact yet useful composite block for converting Word adapters to Bool adapters. Its simple comparison principle makes it ideal for integration into event-driven automation systems based on adapter interfaces. The clear separation of input and output adapters facilitates modular design and reusability.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
