# OFF_SPLIT_5

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AUS_SPLIT_5`](AUS_SPLIT_5.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AUS_SPLIT_5_UNGATED](./AUS_SPLIT_5_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block `AUS_SPLIT_5_UNGATED` distributes an incoming OFF event (e.g., a signal or a message) to five identical outputs. It is a generic function block that serves as a placeholder for an application-specific type (`GEN_AUS_SPLIT`) in the 4diac IDE.

## Interface Structure

### **Event Inputs**

None (signal exchange occurs exclusively via adapters).

### **Event Outputs**


### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

| Direction | Name | Type |
| ---------- | ------ | ----- |
| Socket (Input) | `IN` | `adapter::types::unidirectional::AUS` |
| Plug (Output) | `OUT1` | `adapter::types::unidirectional::AUS` |
| Plug (Output) | `OUT2` | `adapter::types::unidirectional::AUS` |
| Plug (Output) | `OUT3` | `adapter::types::unidirectional::AUS` |
| Plug (Output) | `OUT4` | `adapter::types::unidirectional::AUS` |
| Plug (Output) | `OUT5` | `adapter::types::unidirectional::AUS` |

## Functionality

The function block receives a unidirectional OFF event (e.g., a pulse or a logic 1) via socket `IN` and forwards it without delay or processing to all five connected plugs (`OUT1` to `OUT5`). Each outgoing event is an exact copy of the incoming event.

## Technical Features

- **Generic Type**: The function block is defined as a generic placeholder by the attribute `GenericClassName = 'GEN_AUS_SPLIT'`. During instantiation, the actual adapter type (e.g., specific event signatures) can be replaced.
- **No States**: The component has no internal logic or state machine – routing is purely structural.
- **Unidirectional Communication**: All adapters are declared as `unidirectional::AUS`, meaning data flows only from the input to the outputs.

## State Overview

The component has no internal state. It operates deterministically and entirely in a passive mode.

## Application Scenarios

- **Signal Distribution**: A central event (e.g., "Start" or "Alarm") is intended to control multiple components in parallel.
- **Bus Topologies**: Replacement for multiple manual wiring of a signal in the IEC 61499 environment.
- **Prototyping**: Rapid distribution of an event source across five target components during the development phase.

## Comparison with Similar Function Blocks

- **OFF_SPLIT_2 / OFF_SPLIT_3** – Function blocks with the same functionality but a different number of outputs (2 or 3).
- **E_SPLIT** – A standard event split function block that uses event inputs and outputs instead of adapters. `AUS_SPLIT_5_UNGATED` is adapter-based and therefore more flexible in its reuse with different protocols.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

AUS_SPLIT_5_UNGATED` is a simple, generic distribution function block for unidirectional OFF signals. It simplifies modular control logic by implementing a 1:5 split without additional logic. Thanks to the adapter interface, it can be used in different contexts (e.g., event, data, or mixed streams).

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
