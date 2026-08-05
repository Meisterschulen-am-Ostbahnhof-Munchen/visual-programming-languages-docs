# UDINT_AUDI_AX_SEL_AUDI
![UDINT_AUDI_AX_SEL_AUDI](./UDINT_AUDI_AX_SEL_AUDI.svg)

* * * * * * * * * *
## Introduction
The function block `UDINT_AUDI_AX_SEL_AUDI` implements a binary selection between two input values. The selected value is provided as an output via an adapter. The selection is controlled by a separate selector parameter. The block is used for the flexible switching of signal sources in automation applications and complies with the IEC 61499 standard.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| EI0 | Event | Set IN0 – triggers the processing of data input IN0 |

### **Event Outputs**

The function block does not have direct event outputs on the interface. The output event is provided via the adapter `OUT` (E1). Event triggering occurs after successful selection.

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| IN0 | UDINT | Selectable input variable (first source) |

### **Data Outputs**

The function block has no direct data outputs on the interface. The selected data value is output via the adapter `OUT` (D1).

### **Adapters**

| Name | Direction | Type | Comment |
|------|----------|-----|-----------|
| OUT | Plug (Output) | `adapter::types::unidirectional::AUDI` | Selected output (Event E1, Data D1) |
| IN1 | Socket (Input) | `adapter::types::unidirectional::AUDI` | Selectable input variable (second source) |
| G | Socket (Input) | `adapter::types::unidirectional::AX` | Selector (controls the selection) |

## Functionality

The function block performs a binary selection between two values:

- **IN0** (direct UDINT data input)
- **IN1** (value from the adapter, e.g., an analog or digital signal value)

The selection is controlled by the value of **Selector G** (of type AX, typically Boolean).

An event at **EI0** starts processing with the value of **IN0**.

Events at the adapters **IN1.E1** or **G.E1** also trigger a selection (all events are routed to the internal function block `F_SEL`).

The internal `F_SEL` corresponds to the IEC 61131-3 SELECT operator:

- If G = FALSE → Output = IN0
- If G = TRUE → Output = IN1

After the selection, an event is output at the output adapter **OUT.E1**, and the selected data value is made available at **OUT.D1**.

## Technical Features
- **Adapter-based interfaces**: Inputs and outputs are implemented as IEC 61499 adapters, enabling modular and reusable encapsulation.
- **Internal IEC 61131-3 Block**: The actual selection logic is implemented by the predefined block `F_SEL`, which guarantees deterministic and standards-compliant selection.
- **Event Synchronization**: All incoming events (EI0, IN1.E1, G.E1) are processed identically, allowing the block to respond to various trigger sources.
- **Type Safety**: Adapter and data types are strictly defined (UDINT for data, AX for selector signal), minimizing design-time errors.

## State Overview

The block does not have an explicit state machine. It operates purely event-driven: With each valid event, the selection is immediately recalculated and the output event is triggered. There are no internal memory states outside of transient processing.

## Application Scenarios
- **Setpoint Switching**: Selection between a fixed value (IN0) and a variable setpoint from a higher-level system (IN1).
- **Signal Path Switching**: In process automation, switching between a local sensor (IN0) and an external measured value (IN1) is possible.
- **Operating Mode Selection**: Control of the output variable depending on an operating mode switch (G).
- **Redundancy Switching**: If a signal (IN1) fails, the system automatically uses the substitute value (IN0) (by controlling G accordingly).

## Comparison with Similar Function Blocks

| Function Block | Feature |
|----------|---------|
| **SEL (IEC 61131-3)** | Pure function block or ST implementation without adapters; direct data and event ports. |
| **UDINT_AUDI_AX_SEL_AUDI** | Extended version with adapter interfaces that facilitate loose coupling and reusability in complex networks. |
**MUX (Multiplexer)** | Multi-channel selection (often >2 inputs) – this block is limited to two sources. |

## Conclusion

The FB `UDINT_AUDI_AX_SEL_AUDI` offers reliable and standards-compliant binary selection for automation applications. Thanks to the use of IEC 61499 adapters and the integration of the standardized `F_SEL` block, it is flexible, easy to understand, and seamlessly integrates into existing 4diac projects. Its clear interface structure and event-driven processing make it a fundamental tool for signal switching in distributed systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
