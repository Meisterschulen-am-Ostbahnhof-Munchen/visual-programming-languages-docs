# UDINT_AUDI_AX_SEL_AUDI

![UDINT_AUDI_AX_SEL_AUDI](./UDINT_AUDI_AX_SEL_AUDI.svg)

* * * * * * * * * *
## Introduction

The function block `UDINT_AUDI_AX_SEL_AUDI` is used for binary selection (multiplexing) between two input values of the data type `UDINT`. The special feature of this block lies in its use of standardized adapter interfaces for signal transmission. It allows either a directly applied `UDINT` value or a value provided via an adapter to be selected based on a selection signal, and the result to be forwarded via an output adapter.

## Interface Structure

### **Event Inputs**

| Event | Description | Associated Data |

| :--- | :--- | :--- |

| **EI0** | Signals the update of the input value `IN0`, which is directly connected to the function block. | `IN0` |

### **Event Outputs**

*No direct event outputs are available. Event control is handled via the adapter interfaces.*

### **Data Inputs**

| Variable | Data Type | Description |

| :--- | :--- | :--- |

| **IN0** | UDINT | Selectable input value directly connected to the function block. |

### **Data Outputs**

*No direct data outputs are available. Data is transferred via the output adapter.*

### **Adapter**

| Adapter Name | Type | Direction | Description |

| :--- | :--- | :--- | :--- |

| **OUT** | `adapter::types::unidirectional::AUDI` | Plug | The selected output value (UDINT) including its associated event. |

| **IN1** | `adapter::types::unidirectional::AUDI` | Socket | The second selectable input value received via this adapter. |

| **G** | `adapter::types::unidirectional::AX` | Socket | The selector signal that determines which input is connected to the output. |


## Functionality

The module implements an internal logic network for data- and event-driven selection:

1. **Signal Buffering**:

The inputs `IN0`, `IN1` (via adapter), and the selection signal `G` (via adapter) are buffered internally by edge-triggered flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively). This ensures that value changes and events are processed synchronously.

2. **Data Transfer**:

The buffered input values are forwarded to the central selection module via assignment blocks (`F_MOVE`) for the data type `UDINT`.

3. **Selection Logic (`F_SEL`)**:

- If the selection signal `G` (via adapter `G.D1`) is **FALSE**, the value of **IN0** is passed through to the output.

- If the selection signal `G` is **TRUE**, the value of adapter **IN1** (via `IN1.D1`) is selected.

4. **Output**:

The result is passed to the output adapter `OUT` and triggers the corresponding output event (`OUT.E1`).


Adjustments to any of the inputs (`IN0`, `IN1`) or a change to the selector (`G`) immediately trigger a recalculation and update of the output.

## Technical Features

- **Adapter Integration**: The function block utilizes unidirectional adapter types (`AUDI` for UDINT signals, `AX` for selection signals) to simplify wiring in complex systems and support modular architectures.

- **Event Consistency**: The use of internal `E_D_FF_ANY` function blocks ensures that data values are always transmitted consistently with their associated events and that no incomplete data states arrive at the output.


## State Overview

Since this is a composite FB network, the block does not have its own classic state machine (ECC). The data and event flow is determined by the internal connections:

- Every event at `EI0`, `IN1.E1`, or `G.E1` triggers the internal processing chain.

- After successful selection, the event `OUT.E1` of the output plug is always triggered.

## Application Scenarios

- **Setpoint Switching**: Switching between a locally defined default value (`IN0`) and a value dynamically supplied by a higher-level system (`IN1`).

- **Operating Mode Switching**: Selection of various numerical parameters (e.g., speeds, counter limits) depending on a binary status signal.

- **Modular Plant Controls**: Coupling of distributed control components via standardized adapter interfaces to reduce signal connections in the system model.

## Comparison with Similar Function Blocks

Compared to the standard selection block `F_SEL` (according to IEC 61131-3), this function block offers direct integration of IEC 61499 adapters. While all events and data must be manually wired with the standard `F_SEL`, this block encapsulates event synchronization and adapter coupling, significantly reducing engineering effort in complex projects.

## Conclusion

The `UDINT_AUDI_AX_SEL_AUDI` is a specialized and reliable multiplexer for 32-bit unsigned integers (UDINT). It is ideally suited for modern, service-oriented and event-driven automation applications where clean encapsulation of signals via adapters is required.