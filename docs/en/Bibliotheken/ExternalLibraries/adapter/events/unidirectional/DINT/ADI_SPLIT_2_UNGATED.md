# ADI_SPLIT_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ADI_SPLIT_2`](ADI_SPLIT_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ADI_SPLIT_2_UNGATED](./ADI_SPLIT_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block `ADI_SPLIT_2_UNGATED` is used to distribute an incoming ADI adapter (socket) to two identical ADI output adapters (plugs). It is designed as a generic building block and enables simple signal bundling in adapter-based architectures.

## Interface Structure

### **Event Inputs**

None – this function block has no event inputs.

### **Event Outputs**

None – this function block has no event outputs.

### **Data Inputs**

None – this function block has no separate data inputs. All data is transported via the ADI adapter.

### **Data Outputs**

None – This function block has no separate data outputs. All data is output via the ADI adapters.

### **Adapters**

| Type | Name | Direction | Description |
| ----- | ------ | ---------- | -------------- |
| `adapter::types::unidirectional::ADI` | `IN` | Socket | Incoming ADI adapter that is distributed to the two outputs. |
| `adapter::types::unidirectional::ADI` | `OUT1` | Plug | First output adapter (duplicate of the input). |
| `adapter::types::unidirectional::ADI` | `OUT2` | Plug | Second output adapter (duplicate of the input). |

## Functionality

The function block forwards the ADI adapter received via socket `IN` to both plugs `OUT1` and `OUT2` without modification. This makes the data and events provided by the input adapter available at both outputs simultaneously. No processing, delay, or transformation of the data takes place.

## Technical Features

- **Generic Function Block:** The function block is declared as a generic type (`GEN_ADI_SPLIT`) and can be reused in different ADI environments.
- **No State Machine:** Due to its pure signal forwarding function, the function block does not have its own state machine (ECC).
- **Adapter-based:** All data exchange occurs exclusively via adapters, not via individual data or event ports.

## State Overview

This functional block does not have an internal state machine. The routing is static and without time dependencies.

## Application Scenarios

- **Signal Multiplication:** When an ADI adapter supplied by a sensor or controller needs to be distributed to multiple downstream functional units (e.g., for display, logging, or parallel processing).
- **Architecture Decoupling:** In systems where an output signal is required multiple times without the source component needing to know the number of destinations.
- **Prototypes and Test Setups:** Rapid expansion of an existing adapter circuit by adding a second branch.

## Comparison with Similar Function Blocks

- **Event/Data Splitter:** Conventional splitter function blocks (e.g., `SPLIT` for `BOOL`) operate on individual data and event channels. `ADI_SPLIT_2_UNGATED`, on the other hand, copies an entire adapter, including all its data and events.
- **Mux/Demux Function Blocks:** Multiplexers and demultiplexers perform merging or distribution with selection; `ADI_SPLIT_2_UNGATED` distributes rigidly without selection.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

ADI_SPLIT_2_UNGATED` is a simple yet useful function block for distributing an ADI adapter to two identical outputs. It simplifies the design of adapter-based controllers and avoids redundant source blocks. Its generic nature and lack of internal logic make it a flexible component in IEC 61499 applications.
