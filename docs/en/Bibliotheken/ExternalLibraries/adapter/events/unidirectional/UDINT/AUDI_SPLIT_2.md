# AUDI_SPLIT_2

![AUDI_SPLIT_2](./AUDI_SPLIT_2.svg)

* * * * * * * * * *
## Introduction

The function block **AUDI_SPLIT_2** is a generic block for signal distribution. It receives a signal via a single **AUDI** adapter (unidirectional) and forwards it to two identical **AUDI** output adapters. The function block is declared as a **generic FB**, meaning the specific signal type can be defined during project configuration using the attribute `GenericClassName`. It was developed by HR Agrartechnik GmbH (Version 1.0, 2025-01-24).
## Interface Structure

### **Event Inputs**

None.

#### **Event Outputs**

None.

#### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| **Socket** | `IN` | `adapter::types::unidirectional::AUDI` | Incoming unidirectional AUDIO adapter (signal source). |
| **Plug** | `OUT1` | `adapter::types::unidirectional::AUDI` | First output – forwards the input signal. |
| **Plug** | `OUT2` | `adapter::types::unidirectional::AUDI` | Second output – forwards the input signal. |

## Functionality

The module operates as a **passive splitter** without its own logic or states. The signal arriving via socket `IN` is passed through to both plugs `OUT1` and `OUT2`. The signal is forwarded unchanged and without buffering – any change at the input is immediately visible at both outputs.

Since this is a **unidirectional** adapter, data only flows from the socket to the plugs. No feedback from the outputs to the input is provided.

## Technical Features

- **Generic Module**: The attribute `eclipse4diac::core::GenericClassName` allows adaptation to different AUDI types (e.g., `AUDI_Int`, `AUDI_Bool`). The actual type is only determined during instantiation.
- **No internal ECC**: The function block (FB) does not have an execution state machine because it does not process events. Data transfer is purely structural.
- **Unidirectional interface**: Both sockets and plugs are of type `adapter::types::unidirectional::AUDI`, meaning that the data flow direction is fixed.
- **Copyright**: The function block is licensed under the Eclipse Public License 2.0.

## State overview

The FB does not have its own state diagrams because it does not contain any event-driven processes. Its function is limited to simple line branching.

## Application scenarios

- **Signal distribution**: A central sensor or controller (e.g., a PID controller) sends a value that is to be passed on in parallel to two downstream actuators or monitoring units.
- **Redundant Monitoring**: A measured value is simultaneously sent to two independent evaluation blocks to implement comparison or safety functions.
- **Generic Adapter Architecture**: Particularly useful in systems where the specific AUDI type is only determined at runtime (e.g., in a configurable device platform).

## Comparison with Similar Function Blocks

- **Non-generic Splitters** (e.g., `AUDI_SPLIT_2` with a fixed type): Do not allow type adaptation; the function block presented here is more flexible.
- **Other Splitters with More Outputs** (e.g., `AUDI_SPLIT_3`): Increase the number of branches but follow the same principle.
- **Event-based splitters** (e.g., `E_SPLIT`): These require event and data inputs/outputs and perform synchronized distribution—unlike the asynchronous data adapter split presented here.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The **AUDI_SPLIT_2** is a compact, generic adapter splitter for the 4diac IDE. It performs the simple task of splitting signals to two outputs without introducing additional latency or logic. Its generic design makes it suitable for a wide variety of AUDI data types and allows for flexible reuse in modular automation projects. Its simplicity and type safety make it a solid foundation for distributed control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
