# AE_AX_SWITCH

![AE_AX_SWITCH](./AE_AX_SWITCH.svg)

* * * * * * * * * *
## Introduction

The function block **AE_AX_SWITCH** implements event-driven switching (demultiplexing). An incoming event is forwarded to one of two event outputs – depending on the Boolean value of a separate data input.
## Interface Structure

### **Event Inputs**

The function block has no direct event inputs. Events are received via the **adapter `EI`** (type `adapter::types::unidirectional::AE`).

#### **Event Outputs**

The function block has no direct event outputs. Events are output via the **adapters `EO0` and `EO1`** (both type `adapter::types::unidirectional::AE`).

### **Data Inputs**

- **`G`** (adapter type `adapter::types::unidirectional::AX`) – Boolean value that controls the switching.
* `G=0` → Event is routed to `EO0`
* `G=1` → Event is routed to `EO1`

### **Data Outputs**

No direct data outputs. Output is exclusively via the event adapters.

### **Adapters**

| Name | Type | Direction | Description |
|------|-----|----------|--------------|
| `EI` | `AE` (Event Adapter) | Socket | Receives the event to be switched. |
| `G` | `AX` (Data Adapter) | Socket | Returns the switching state (boolean). |
| `EO0`| `AE` | Plug | Outputs the event if `G=0` was present. |
| `EO1`| `AE` | Plug | Outputs the event if `G=1` was present. |

## Functionality

The function block (FB) is always in state `START`. As soon as an event arrives at adapter `EI` (signal `EI.E1`), the current value of the Boolean adapter `G.D1` is evaluated:

- **`G.D1 = 0`** → The FB switches to state `G0` and sends an event via adapter `EO0.E1`. It then immediately returns to state `START`.

- **`G.D1 = 1`** → The function block (FB) switches to state `G1` and sends an event via adapter `EO1.E1`. It then immediately returns to state `START`.

An additional event at adapter `G` (signal `G.E1`) does not trigger any action – the FB remains in state `START`. This prevents unwanted switching operations when the data value changes.

## Technical Features

- **Adapter-based interface** – The FB uses loosely coupled adapters of types `AE` (event) and `AX` (data). This enables flexible integration with other function blocks in the 4diac framework.
- **Deterministic Switching** – The decision as to which output is activated is made in the same step as the event is received, thus eliminating any additional delay.
- **No Memory Behavior** – After outputting, the function block immediately returns to its initial state. The state `G` is not cached – it is read anew with each event.

## State Overview

| State | Description | Output Action |
|---------|---------------|--------------|
| `START` | Waiting for an event at `EI`. | – |
| `G0` | Event from `EI` processed at `G.D1=0`. | `EO0.E1` |
| `G1` | Event from `EI` processed at `G.D1=1`. | `EO1.E1` |

States `G0` and `G1` are exited immediately after output (automatic transition to `START`).

## Application Scenarios

- **Event Routing** – Forwarding an event to different downstream logic branches, depending on a condition.
- **State-Dependent Control** – In automation systems, a sensor event can be sent to different processing blocks depending on the operating mode.
- **Multiplexing Reversal** – As a demultiplexer for asynchronous event streams, e.g., in communication protocols.

## Comparison with Similar Function Blocks

- **E_SWITCH** – The standard function block `E_SWITCH` uses direct event inputs/outputs. `AE_AX_SWITCH` extends this concept with adapters, enabling looser coupling and reusability in different contexts.
- **E_DEMUX** – Other demultiplexer function blocks often use multiple inputs or states. `AE_AX_SWITCH` focuses on the simple, Boolean switching of a single event – without buffering or delay.

## Conclusion

The `AE_AX_SWITCH` is a compact, efficient demultiplexer for events based on a Boolean switching signal. Its adapter-based interface allows for flexible integration into IEC 61499 systems, while its deterministic behavior ensures reliable routing. It is particularly suitable for applications where an event needs to be sent to different processing paths depending on the state of a condition.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
