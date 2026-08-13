# ALI_SPLIT_2

![ALI_SPLIT_2](./ALI_SPLIT_2.svg)

* * * * * * * * * *
## Introduction

The **ALI_SPLIT_2** function block serves as a generic distributor for a unidirectional ALI (Application Layer Interface) adapter. It copies all incoming data and events from a single input socket to two output plugs. This allows a signal or data source to be passed on to two independent receivers.
## Interface Structure

### **Event Inputs**

No event inputs are available. Data is passed solely via the adapter interface.

### **Event Outputs**

No event outputs are available. Event control is handled via the adapter connections.

### **Data Inputs**

No dedicated data inputs. All data is provided via the incoming adapter **IN**.

### **Data Outputs**

No dedicated data outputs. The distributed data is provided via the two outgoing adapters **OUT1** and **OUT2**.

### **Adapters**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| **Socket** | `IN` | Input | Unidirectional ALI adapter that receives incoming data/events. |
| **Plug** | `OUT1` | Output | First unidirectional ALI adapter to which the data/events are forwarded. |
| **Plug** | `OUT2` | Output | Second unidirectional ALI adapter to which the data/events are forwarded. |

All adapters are of type `adapter::types::unidirectional::ALI`.

## Functionality

The module implements a 1:2 split at the adapter level. As soon as data or events are present at socket **IN**, they are passed on unchanged and simultaneously to both plugs **OUT1** and **OUT2**. No buffering or processing of the data takes place – the module operates purely as a signal distributor.

## Technical Features

- **Generic Module**: The attribute `eclipse4diac::core::GenericClassName` marks the module as a generic instance `GEN_ALI_SPLIT`. It can therefore be used with different ALI types or parameters, as long as the underlying adapter definition is compatible.
- **No State Management**: The module has no internal states or variables – its functionality is purely combinatorial.
- **Unidirectionality**: The adapters are defined as unidirectional, meaning data flows only from the input to the outputs; reverse communication is not supported.

## State Overview

Since the module has no event inputs/outputs or internal states, there is no state machine. Data transmission is continuous and instantaneous.

## Application Scenarios

- **Distributing a Sensor Signal**: An analog or digital ALI sensor is connected to two control units that need to access the measurement data independently.
- **Parallel Processing**: A data stream should be processed simultaneously by two different function blocks without requiring manual branching in the application.
- **Redundancy**: An application requires duplicate ALI communication to increase reliability.

## Comparison with Similar Function Blocks

| Function Block | Function | Difference |
|----------|----------|-------------|
| **ALI_SPLIT_2** | Distributes one ALI input to two ALI outputs. | – |
| **ALI_SPLIT_3** (hypothetical) | Distributes to three outputs. | Higher number of outputs. |
| **ALI_MERGE_2** | Combines two ALI inputs into one ALI output. | Opposite function (Join). |
| **ALI_FILTER** | Passes on only specific data/events. | Contains filter logic. |

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

**ALI_SPLIT_2** is a simple but essential function block for distributing unidirectional ALI interfaces. Its generic nature and lean implementation make it a universal tool in IEC 61499 component development when a signal or data stream needs to be passed to multiple subsequent blocks.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
