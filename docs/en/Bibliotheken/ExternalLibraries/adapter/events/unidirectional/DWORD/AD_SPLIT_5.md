# AD_SPLIT_5

![AD_SPLIT_5](./AD_SPLIT_5.svg)

* * * * * * * * * *
The function block `AD_SPLIT_5` is a generic function block that splits an incoming unidirectional adapter (type `adapter::types::unidirectional::AD`) into five identical output adapters. It serves to forward an adapter signal in parallel to multiple subsequent function blocks without requiring the input to be connected multiple times.

None available.

None available. All communication takes place via the adapter socket.

None available. Outputs are exclusively via the adapter plugs.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AD` | `IN` | Socket (Input) | Incoming adapter signal, which is distributed to all outputs. |
| `adapter::types::unidirectional::AD` | `OUT1` | Plug (Output) | First outgoing adapter, identical to the input signal. |
| `adapter::types::unidirectional::AD` | `OUT2` | Plug (Output) | Second outgoing adapter. |
| `adapter::types::unidirectional::AD` | `OUT3` | Plug (Output) | Third outgoing adapter. |
| `adapter::types::unidirectional::AD` | `OUT4` | Plug (Output) | Fourth outgoing adapter. |
| `adapter::types::unidirectional::AD` | `OUT5` | Plug (Output) | Fifth outgoing adapter. |

## Functionality

This component does not have event or data ports in the conventional sense. Instead, an incoming adapter `IN` is passed through to all five outgoing adapters `OUT1` to `OUT5`. This means that changes or events transmitted via the input adapter are passed to all five outputs simultaneously. This multiplication occurs without any logical processing or delay.

- **Generic Type**: The function block is implemented as a generic component (attribute `eclipse4diac::core::GenericClassName = 'GEN_AD_SPLIT'`). This allows it to be used in various contexts with the adapter type `adapter::types::unidirectional::AD`.
- **No State Machine**: The block does not have an ECC (Execution Control Chart) and operates purely in a data flow-driven manner. It does not perform any data storage operations.
- **Unidirectional Adapters**: All adapters are unidirectional, meaning data flows in only one direction – from the socket to the plugs.

The function block has no internal states or steps. It is a pure splitter without its own behavior. Therefore, a state overview is not available.

- **Signal Distribution**: When an adapter signal is needed multiple times, e.g., to feed several parallel calculations or outputs.
- **Modular Chaining**: In complex automation systems where a sensor value (as an adapter) needs to be passed on to different subsystems.
- **Prototyping**: Rapid setup of test environments where a signal needs to reach multiple locations simultaneously.
- **AD_SPLIT_2, AD_SPLIT_3, AD_SPLIT_4**: The same functionality with two, three, or four outputs, respectively. `AD_SPLIT_5` is the five-output version.
- **Manual Wiring**: Without this block, the output of the source block would have to be connected multiple times, which is not directly possible in the 4diac IDE (a port can only have one connection). The splitter solves this problem.
- **Event-Based Splitters**: There are also splitters for events (e.g., `E_SPLIT`), but these are based on event and data ports. In contrast, `AD_SPLIT_5` operates exclusively at the adapter level.

The function block `AD_SPLIT_5` is a simple yet useful tool for multiplying adapter signals in the 4diac development environment. Its generic design and the absence of a state machine provide an efficient way to distribute an adapter signal across five parallel paths without requiring any code changes. It is ideal for modular and scalable automation applications.

---

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de
