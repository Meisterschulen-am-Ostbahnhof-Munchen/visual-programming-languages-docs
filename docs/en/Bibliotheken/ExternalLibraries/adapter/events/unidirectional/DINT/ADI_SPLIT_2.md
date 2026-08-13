# ADI_SPLIT_2

![ADI_SPLIT_2](./ADI_SPLIT_2.svg)

* * * * * * * * * *
## Introduction

The function block `ADI_SPLIT_2` is used to distribute an incoming ADI adapter (socket) to two identical ADI output adapters (plugs). It is designed as a generic building block and enables simple signal bundling in adapter-based architectures.
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
|-----|------|----------|--------------|
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

- **Event/Data Splitter:** Conventional splitter function blocks (e.g., `SPLIT` for `BOOL`) operate on individual data and event channels. `ADI_SPLIT_2`, on the other hand, copies an entire adapter, including all its data and events.
- **Mux/Demux Function Blocks:** Multiplexers and demultiplexers perform merging or distribution with selection; `ADI_SPLIT_2` distributes rigidly without selection.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

ADI_SPLIT_2` is a simple yet useful function block for distributing an ADI adapter to two identical outputs. It simplifies the design of adapter-based controllers and avoids redundant source blocks. Its generic nature and lack of internal logic make it a flexible component in IEC 61499 applications.
