# AL_SPLIT_7
![AL_SPLIT_7](./AL_SPLIT_7.svg)
*(Image of function block not available)*

* * * * * * * * * *
## Introduction
The function block **AL_SPLIT_7** serves as a generic distributor (splitter) for a unidirectional adapter of type `AL`. It accepts a single adapter at its socket `IN` and forwards the incoming data and events unchanged to seven identical adapter outputs (`OUT1` … `OUT7`). The block is implemented as a generic type (`GEN_AL_SPLIT`), thus enabling flexible use in control and automation applications.

## Interface Structure

### **Event Inputs**

This function block has no explicit event inputs. All event control is handled via the connected adapter `IN`.

### **Event Outputs**

There are no direct event outputs. Events are passed on via the seven adapter outputs (`OUT1` … `OUT7`).

### **Data Inputs**

This function block has no independent data inputs. Data is transferred exclusively via the adapter `IN`.

### **Data Outputs**

Accordingly, there are no direct data outputs. The data is replicated via the seven adapter outputs.

### **Adapters**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| Socket | `IN` | `adapter::types::unidirectional::AL` | Adapter input that provides the AL connection to be distributed. |
| Plug | `OUT1` … `OUT7` | `adapter::types::unidirectional::AL` | Seven adapter outputs that provide an identical copy of the input adapter. |

## Functionality

The **AL_SPLIT_7** is a pure distribution module. When an adapter of type `AL` is connected to socket `IN`, all data and events received via this adapter are forwarded unchanged to each of the seven plugs (`OUT1` … `OUT7`). No logical or temporal processing takes place – the distribution is one-to-seven without delay or buffering. Due to its generic implementation, the function block can be used with different AL adapter instances that have the same data type and event schema.

## Technical Features
- **Generic Implementation:** The function block is declared as a generic type (`GEN_AL_SPLIT`). This allows it to be used in different projects without modifying the source code, as long as the underlying adapter type `AL` corresponds to the expected interface.
- **Unidirectionality:** The module operates exclusively unidirectionally – data and events flow from the socket to the plugs. Feedback or bidirectional communication is not supported.
- **No State Logic:** The module does not have its own state machine; it is transparent.

## State Overview

The module has no internal states. It is always ready to distribute incoming adapter connections. An active state results solely from the presence of a valid adapter at the `IN` socket.

## Application Scenarios
- **Control Distribution:** A higher-level control adapter (e.g., for controlling an axis or sensor) should send identical signals to multiple parallel components.
- **Test Environments:** In simulation or test setups, one adapter can supply several similar subsystems.
- **Signal Bundling:** This function block can be used as a distributor in a hierarchy of adapters when a signal needs to be split across multiple downstream function blocks.

## Comparison with Similar Function Blocks

Compared to an **AL_SPLIT_2** or **AL_SPLIT_4**, **AL_SPLIT_7** offers a higher number of outputs (seven instead of two or four). While smaller splitters are sufficient for low-demand applications, this function block enables direct distribution to seven receivers without the need to cascade multiple splitters. Its function is the exact opposite of an **AL_MERGE** (which combines multiple inputs).

## Conclusion

The **AL_SPLIT_7** is a simple yet useful generic function block for replicating unidirectional AL adapter connections. Thanks to its generic nature and clear interface, it can be flexibly integrated into automation and control systems where a signal needs to be distributed across multiple paths. Its inherent transparency ensures lossless transmission without additional latency.
