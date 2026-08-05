# ATM_D_FF
![ATM_D_FF](./ATM_D_FF.svg)
* * * * * * * * * *
## Introduction
The function block `ATM_D_FF` implements a data latch (D flip-flop) for storing a single data value. Communication occurs exclusively via adapters of type `adapter::types::unidirectional::ATM`, so events and data are transmitted as a bundled interface. The function block is implemented according to IEC 61499-1 Annex A and is licensed under the Eclipse Public License 2.0.
## Interface Structure
### **Event Inputs**
The function block does not have direct event inputs. An event is received at the adapter interface *E1* via the socket adapter **I** (type: `adapter::types::unidirectional::ATM`).

### **Event Outputs**
The FB has no direct event outputs. An event is output via the plug adapter **Q** (type: `adapter::types::unidirectional::ATM`) at the adapter interface *E1*.

### **Data Inputs**
The FB has no direct data inputs. A data value is provided via the socket adapter **I** at the adapter interface *D1*.

### **Data Outputs**
The FB has no direct data outputs. A data value is output via the plug adapter **Q** at the adapter interface *D1*.

### **Adapters**

| Adapter | Type | Direction | Comment |

|---------|-----|----------|-----------|

| I | `adapter::types::unidirectional::ATM` | Socket (incoming) | Latch value |

| Q | `adapter::types::unidirectional::ATM` | Plug (outgoing) | Stored value |

## Functionality
The function block internally uses the standard block `iec61499::events::E_D_FF_ANY`. Upon an event at the input adapter **I.E1** (clock), the current data value is taken from **I.D1** and temporarily stored. Immediately afterward, an event is triggered at the output adapter **Q.E1**, and the stored value is output to **Q.D1**. This behavior corresponds to an edge-triggered D flip-flop.

## Technical Features
- No direct event or data ports – all communication takes place via adapters, which enables flexible coupling in IEC 61499 systems.
- The function block is fully implemented by the internal `E_D_FF_ANY`; the state logic is handled by this block.
- Licensed under the Eclipse Public License 2.0; source code and metadata are stored in the function block type.

## State Overview
The `ATM_D_FF` does not have its own state engine. Its behavior is purely data flow-driven:

- **Waiting for Event** – the last stored value is retained.
- **On Event at I.E1** – the value from I.D1 is taken and immediately output to Q.

Internally, edge-triggered takeover is implemented by `E_D_FF_ANY` (rising edge of the event).

## Application Scenarios
- **Cache** for data that should be updated synchronously with an event.
- **State indicator** in automation processes (e.g., marker for "Value valid").
- **Data transfer** between asynchronous process steps when a simple latch is sufficient.
- **Adapter-based communication** in distributed systems where flat interfaces are preferred.

## Comparison with similar components
- **SR flip-flop** (`ATM_SR_FF`): Sets/resets state via two events, no clock-driven data input.
- **T flip-flop** (`ATM_T_FF`): Toggles the state on each event.
- **Direct `E_D_FF_ANY`**: Offers the same logic, but with explicit input/output ports instead of adapters. The `ATM_D_FF` encapsulates this logic and standardizes the interface to the unidirectional ATM adapter, facilitating reuse in adapter-based frameworks.

## Conclusion

ATM_D_FF` is a compact, reliable functional block for implementing a D flip-flop in IEC 61499 environments. The use of adapters ensures a clean separation of event and data paths, which is particularly advantageous in modular, reusable automation solutions. The component is easy to integrate and fulfills the basic requirement for an edge-triggered data storage device.
