# AE_SPLIT_2

![AE_SPLIT_2](./AE_SPLIT_2.svg)

* * * * * * * * * *

## Introduction

The function block **AE_SPLIT_2** serves as a generic distributor for an incoming adapter event (AE). It receives a unidirectional event via socket `IN` and forwards it without delay or modification to the two output plugs `OUT1` and `OUT2`. The block is implemented as a generic FB (GenericClassName: `'GEN_AE_SPLIT'`), so it can theoretically be used for various adapter types – provided they conform to the unidirectional AE protocol.

## Interface Structure

### **Event Inputs**

None. The FB does not have any traditional event inputs. Event forwarding occurs exclusively via the adapter socket.

### **Event Outputs**

None. Event forwarding occurs via the adapter plugs.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapter**

| Role | Name | Type | Description |
| ------- | ------ | ----- | -------------- |
| Socket (Input) | `IN` | `adapter::types::unidirectional::AE` | Receives a unidirectional event, which is distributed to both outputs. |
| Plug (Output 1) | `OUT1` | `adapter::types::unidirectional::AE` | First output for the duplicated event. |
| Plug (Output 2) | `OUT2` | `adapter::types::unidirectional::AE` | Second output for the duplicated event. |

## Functionality

As soon as an event arrives at the adapter socket `IN`, it is forwarded **immediately and in parallel** to both output plugs `OUT1` and `OUT2`. The function block performs no logic, filtering, or delay – it functions purely as a splitter at the adapter level. The distribution is event-based: Every single incoming event appears at both outputs.

## Technical Features

- **Generic Type**: The function block is declared as a generic function block (`GenericClassName = 'GEN_AE_SPLIT'`). This allows adaptation to other user-defined adapter types, as long as they use the unidirectional event interface. In the current configuration, the specific type `adapter::types::unidirectional::AE` is defined.
- **No States / Algorithms**: Since no logic or memory behavior is implemented, the function block (FB) has no Execution Control Chart (ECC) and no internal states.
- **Latency**: Forwarding occurs instantaneously within one execution cycle.

## State Overview

The FB has **no state machine**. Its behavior is purely combinatorial: Every incoming adapter event is immediately duplicated and output to both outputs.

## Application Scenarios

- **Event Distribution**: A sensor or controller delivers an event (e.g., "Start" or "Alarm") that must be processed by two independent subsystems.
- **Parallel Circuit**: Splitting a signal to simultaneously control two actuators or for parallel data acquisition.
- **Prototyping**: Temporary branching of an event stream during the development and testing phase.

## Comparison with Similar Components

- **AE_SPLIT_1**: A splitter with only one output (i.e., pure pass-through) – usually unnecessary.
- **E_SPLIT_2**: Classic event splitter for standard event inputs/outputs. Unlike `AE_SPLIT_2`, this one operates at the event level without adapter coupling.
- **AE_ROUTER**: An adapter-based distributor that can selectively route events to specific outputs (e.g., based on data values). `AE_SPLIT_2` is simpler and always distributes to all outputs.

## Conclusion

The **AE_SPLIT_2** is a minimal yet useful function block for easily distributing adapter events. Its generic nature makes it versatile, while the lack of logic ensures low latency and high reliability. It is ideal for all scenarios where an event needs to be forwarded to multiple receivers.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Total resistance in series & parallel circuits on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/gesamtwiderstand-reihen-parallelschaltung/)
