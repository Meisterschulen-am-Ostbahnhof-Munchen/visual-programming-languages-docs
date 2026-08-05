# AUS_MUX_2

![AUS_MUX_2](./AUS_MUX_2.svg)

* * * * * * * * * *
## Introduction

The function block **AUS_MUX_2** implements a generic multiplexer for the AUS adapter type (unidirectional). It selects between two input adapters (`IN1` and `IN2`) and forwards their signal to the output adapter (`OUT`). The selection is made using the index `K`. The block is triggered by the event `REQ` and acknowledged with `CNF`.

## Interface Structure

### **Event Inputs**

| Event | With Variables | Comment |

|----------|---------------|---------------------------------|

| REQ | K | Sets the index K and triggers the multiplexer action |

### **Event Outputs**

| Event | Comment |

|----------|----------------------------------------|

| CNF | Confirmation of successful switching |

### **Data Inputs**

| Variable | Type | Comment |

|----------|------|-------------------------|

| K | UINT | Index for selecting the input (0 → IN1, 1 → IN2) |

### **Data Outputs**

No separate data outputs are defined; data is transferred via the adapter `OUT`.


### **Adapter**

| Type | Name | Direction | Adapter Type | Comment |

|---------|------|------------|---------------------------------------|----------------------------------------|

| Plug | OUT | Output | adapter::types::unidirectional::OFF | Output that provides the selected input |

| Socket | IN1 | Input | adapter::types::unidirectional::OFF | First input (K = 0) |

| Socket | IN2 | Input | adapter::types::unidirectional::OFF | Second input (K = 1) |


## Functionality

When a **REQ** event occurs, the value of the index `K` is evaluated:

- If `K = 0`, the signal from `IN1` is switched to the adapter `OUT`.

- If `K = 1`, the signal from `IN2` is switched to `OUT`.

- For other values of `K` (e.g., >1), the behavior is not specified; therefore, the function block should only be used with `K = 0` or `1`.


After a successful switchover, a **CNF** event is output.

## Technical Features

- **Generic Type**: The function block is declared as a generic function block (attribute `GenericClassName = 'GEN_AUS_MUX'`). It can be automatically instantiated by the 4diac IDE.

- **Adapter-Based**: The inputs and outputs are implemented as unidirectional OFF adapters, allowing complex data structures or bus signals to be transmitted in bundles.

- **Packet Structure**: The function block is located in the namespace `adapter::selection::unidirectional`, indicating its systematic classification within a library of selection functions.

- **Event-Driven**: The switchover occurs only upon explicit request (REQ), not cyclically.

## State Overview

An explicit state machine is not defined in the XML. The module operates functionally:

1. **Waiting** – for a `REQ` event

1. **Processing** – evaluation of `K` and forwarding of the corresponding input to `OUT`

1. **Acknowledge** – sending `CNF`

1. Return to wait state

## Application Scenarios

- **Switching between two sensors**: In an agricultural machine, switching between two OFF-compatible sensor values (e.g., GPS vs. odometry) is possible.

- **Operating mode selection**: In a controller, selection is made between two different configuration data streams – for example, normal operation and maintenance mode.

- **Redundancy switching**: Switching to a second OFF data channel if the primary one fails.


## Comparison with Similar Function Blocks

- **Event Multiplexer (e.g., MUX_2)** – Selects between two event paths; the focus here is on the adapter signal.

- **Data Multiplexer (e.g., SEL, MUX_INT)** – Works with simple data types (INT, BOOL) and has separate output variables. In contrast, `AUS_MUX_2` uses complete adapter interfaces, enabling the encapsulated transfer of complex information.

## Conclusion

The `AUS_MUX_2` is a compact, adapter-based function block for selecting one of two OFF signals. Its generic design and clear event control make it particularly suitable for modular automation solutions in the IEC 61499 environment, where standardized adapters are used for data exchange.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]