# AX_RS_SYM
![AX_RS_SYM](./AX_RS_SYM.svg)
* * * * * * * * * *
## Introduction
The **AX_RS_SYM** is an event-driven, bistable function block (RS flip-flop) with symmetrical start-up behavior. It has two event inputs, `R` (Reset) and `S` (Set), each of which sets the state of the output `Q`. The output is provided as a unidirectional adapter, through which both a data value (D1) and an event (E1) can be transmitted.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|
| `R` | Event | Sets output `Q.D1` to `FALSE` and fires `Q.E1` |

| `S` | Event | Sets output `Q.D1` to `TRUE` and fires `Q.E1` |

### **Event Outputs**
The function block (FB) does not have its own event outputs. The event is output via the adapter `Q` using `Q.E1`.

### **Data Inputs**
None.

### ### **Data Outputs**
The FB has no separate data outputs. The current state is provided via the adapter `Q` as `Q.D1` (of type BOOL).

### **Adapters**

| Name | Type | Comment |

|------|-----|-----------|

| `Q` | `adapter::types::unidirectional::AX` | Provides the flip-flop value (D1) and an acknowledgment event (E1) |

## Functionality

The function block implements a classic RS flip-flop:

- Upon arrival of the event `S`, the output value `Q.D1` is set to `TRUE`, and then the event `Q.E1` is triggered.
- Upon arrival of the event `R`, the output value `Q.D1` is set to `FALSE`, and `Q.E1` is also triggered.

The special feature is the **symmetrical start-up behavior**: Immediately after initialization, the function block is in the state `START`. If the first event received is `S`, it transitions to state `SET`; if `R` is received, it transitions to state `RESET`. This ensures a defined state from the start – there is no undefined or random initial value.

## Technical Features
- **Symmetrical Start Behavior**: Both inputs, `R` and `S`, are treated equally. The function block has no preferred initial state; the first incoming pulse determines the state.
- **Adapter-Based Output**: The output is implemented as a unidirectional adapter. This allows for flexible reuse of the value and the event in more complex structures.
- **No undefined state**: The state machine with three states (START, SET, RESET) prevents the function block from remaining in an unknown or metastable state after startup.

## State Overview
The internal state machine consists of the following states and transitions:

| State | Meaning | Action on entry |

|---------|-----------|---------------------|

| START | Initial state after power-on | No action (waits for first event) |

| SET | Output `Q.D1` is `TRUE` | Executes algorithm `SET`: `Q.D1 := TRUE` and fires `Q.E1` |

| RESET | Output `Q.D1` is `FALSE` | Executes algorithm `RESET`: `Q.D1 := FALSE` and fires `Q.E1` |

`` **Transitions:**

- `START` → `SET` on condition `S`
- `START` → `RESET` on condition `R`
- `SET` → `RESET` on condition `R`
- `RESET` → `SET` on condition `S`

## Application Scenarios
- **Simple Switch/Button**: One button press sets a marker bit, a second button press It resets.
- **Interlocks** (e.g., in safety controllers): A set pulse activates an action, a reset pulse deactivates it.
- **State control in sequence sequences**: As a memory block for events that are evaluated later.
- **Start-up behavior**: Particularly suitable when the system should start in a defined state after power-up, but one not yet specified by pre-logic.

## Comparison with similar blocks
- **AX_RS**: A frequently used RS flip-flop with asynchronous set/reset. Unlike `AX_RS_SYM`, most implementations define a preferred state (e.g., the "R" signal resets the output at startup). `AX_RS_SYM` handles both events symmetrically, which makes the start-up behavior predictable.
- **AX_SR (Set-dominant)** or **AX_RS (Reset-dominant)**: These function blocks have a dominant input order when S and R arrive simultaneously. However, the symmetry here only applies to the startup behavior; during operation, the order is determined by the event processing of the runtime environment in the case of simultaneous events – the function block itself cannot handle simultaneity.
- **SR flip-flops in IEC 61131-3**: (e.g., `SR` or `RS`) usually operate with static signals. `AX_RS_SYM` is purely event-driven and therefore optimized for event-oriented controllers (e.g., 4diac IDE with FORTE).

``` ## Conclusion

The **AX_RS_SYM** is a simple yet flexible event-driven RS flip-flop. Its unique feature lies in its symmetrical startup behavior, which allows for a defined initial state without a fixed preset. The adapter interface facilitates integration into larger systems. This component is the ideal choice for applications where neither setting nor resetting is preferred after startup.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]