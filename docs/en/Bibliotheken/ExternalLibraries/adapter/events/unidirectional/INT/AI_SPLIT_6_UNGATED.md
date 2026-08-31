# AI_SPLIT_6_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AI_SPLIT_6`](AI_SPLIT_6.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

## Introduction

![AI_SPLIT_6_UNGATED](./AI_SPLIT_6_UNGATED.svg)
The function block **AI_SPLIT_6_UNGATED** serves as a generic splitter that distributes an analog input value (AI) to six identical outputs. It implements a 1:6 distribution of an AI adapter without modifying any data or events. The block is defined as a generic FB (GenericClassName: `GEN_AI_SPLIT`) and operates purely on an adapter basis.

## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No data inputs available.

### **Data Outputs**

No data outputs available.

### **Adapter**

| Direction | Name | Type | Description |
| ---------- | ------ | ----- | -------------- |
| Input (Socket) | IN | `adapter::types::unidirectional::AI` | Single Analog Input Adapter (Source) |
| Output (Plug) | OUT1 | `adapter::types::unidirectional::AI` | First Output (1:1 pass-through from IN) |
| Output (Plug) | OUT2 | `adapter::types::unidirectional::AI` | Second Output |
| Output (Plug) | OUT3 | `adapter::types::unidirectional::AI` | Third Output |
| Output (Plug) | OUT4 | `adapter::types::unidirectional::AI` | Fourth Output |
| Output (Plug) | OUT5 | `adapter::types::unidirectional::AI` | Fifth Output |
| Output (Plug) | OUT6 | `adapter::types::unidirectional::AI` | Sixth Output |

## Functionality

This function block has no internal logic or state machines. It functions as a passive splitter: The AI adapter connected to socket **IN** is duplicated unchanged to all six plug outputs **OUT1** to **OUT6**. Changes to the AI value (e.g., measured value or status) at the source are immediately and simultaneously visible at all outputs.

## Technical Features

- **Generic Function Block**: The function block is marked as `eclipse4diac::core::GenericClassName`. This allows it to be parameterized or instantiated depending on the runtime environment without changing its basic splitter function.
- **Pure Adapter Coupling**: Neither events nor data port variables are used; only unidirectional adapters of type `adapter::types::unidirectional::AI` are employed. This reduces overhead and enables direct interconnection with other AI adapter blocks.
- **No States**: Since no ECC (Execution Control Chart) is present, the function block requires no algorithms or state transitions. The routing is purely structural.

## State Overview

The function block does not have a state machine (ECC) and does not perform any active operations. There are no distinguishable operating states.

## Application Scenarios

- **Distribution of an Analog Sensor Signal**: A single analog input (e.g., a 4-20 mA transmitter) is to be passed on in parallel to multiple control functions or display units.
- **Redundancy / Plausibility Check**: The same measured value is routed to several parallel evaluation blocks, which perform tasks such as averaging or error detection.
- **Simulation and Testing**: A simulated AI adapter is distributed across multiple test blocks to verify system behavior under load.

## Comparison with Similar Blocks

- **AI_SPLIT_2 / AI_SPLIT_4**: These blocks split one AI input into two or four outputs, respectively. **AI_SPLIT_6_UNGATED** represents the variant with six outputs. All splitters function identically and differ only in the number of output adapters.
- **AI_DUPLICATE (hypothetical)**: A block that duplicates the value for copying purposes, but usually uses data ports. AI_SPLIT_6_UNGATED, on the other hand, uses adapters exclusively, allowing direct coupling without additional event control.

- **[`AI_SPLIT_6`](AI_SPLIT_6.md)**: The gated variant – updates the output only on an actual value change.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The **AI_SPLIT_6_UNGATED** is a minimal yet useful component for distributing analog adapter signals in the 4diac IDE. Its generic definition and pure adapter interface make it particularly suitable for architectures requiring loose coupling and easy extensibility. The distribution across six outputs enables flexible multiple use of a single analog input value.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
