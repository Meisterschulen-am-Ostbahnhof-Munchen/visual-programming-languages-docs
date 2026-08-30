# ASR_SWITCH

![ASR_SWITCH](./ASR_SWITCH.svg)

* * * * * * * * * *
## Introduction

The **ASR_SWITCH** function block acts as a demultiplexer for **ASR events** (SET/RESET). It forwards events received via the adapter socket `EI` to either the adapter plug `EO0` or `EO1`, depending on the Boolean value of the input `G`. This allows switching between two different signal paths in an automation application.
## Interface Structure

### **Event Inputs**

| Event | Data Link | Description |
|----------|--------------|--------------|
| `EIG` | `G` | Sets the switching value `G` to the Boolean value present at input `G`. |

### **Event Outputs**

This function block does not have any independent event outputs. Output is exclusively via the **adapter plugs**.

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|--------------|
| `G` | `BOOL` | Switch position: `FALSE` → Events are forwarded to `EO0`, `TRUE` → to `EO1`. |

### **Data Outputs**

None.

### **Adapters**

| Adapter | Direction | Type | Description |
|---------|----------|---------------------------|--------------|
| `EI` | Socket | `adapter::types::unidirectional::ASR` | Receives incoming ASR events (SET/RESET). |
| `EO0` | Plug | `adapter::types::unidirectional::ASR` | Output for the case `G = FALSE`. |
| `EO1` | Plug | `adapter::types::unidirectional::ASR` | Output for the case `G = TRUE`. |

## Functionality

The **ASR_SWITCH** is activated by an incoming event from the adapter socket `EI` or by the event `EIG`. The processing takes place in **Event-driven Control (ECC)**:

1. **Switching G:**

When the event `EIG` occurs, the value of `G` is adopted. The function block remains in the start state `START` and waits for the next events.

2. **Forwarding `EI.SET`:**
- `EI.SET` and `G = FALSE`: Transition to the state `G0_SET`, where `EO0.SET` is output.
- `EI.SET` and `G = TRUE`: Transition to state `G1_SET`, where `EO1.SET` is output.
3. **Forwarding from `EI.RESET`:**
- `EI.RESET` and `G = FALSE`: Transition to state `G0_RESET`, where `EO0.RESET` is output.
- `EI.RESET` and `G = TRUE`: Transition to state `G1_RESET`, where `EO1.RESET` is output.
4. **Return:**

After the action is output, the ECC immediately (condition = `1`) returns to the start state `START` to process the next event.

## Technical Features

- The function block works exclusively with the **unidirectional adapter type `ASR`**, meaning it can transport both SET and RESET events via the same adapter.
- The switchover is **event-triggered** via `EIG` (non-cyclically).
- No data outputs are required – all signaling is handled via the adapter plugs.
- Due to the immediate reset to the start state, the module is ready to restart **deterministically and quickly**.

## State Overview

The following table summarizes the ECC states and the actions performed:

| State | Description | Action(s) |
|---------------|----------------------------------------------|-------------------|
| `START` | Waiting for events | – |
| `G0_SET` | `EI.SET` at `G = FALSE` | Output `EO0.SET` |
| `G1_SET` | `EI.SET` at `G = TRUE` | Output `EO1.SET` |
| `G0_RESET` | `EI.RESET` at `G = FALSE` | Output `EO0.RESET` |
| `G1_RESET` | `EI.RESET` at `G = TRUE` | Output `EO1.RESET` |

All states (except `START`) return to `START` with an unconditional transition (`1`).

## Application Scenarios

- **Control of two parallel process paths:** Depending on the position of a switch, SET/RESET signals are distributed to different parts of the system.
- **Operating mode switching:** For example, between automatic and manual operation – a logical variable `G` determines which events affect which logic.
- **Test environments:** A test frame can send the same events to different test objects by switching `G`.

## Comparison with Similar Function Blocks

- **`SELECT` Function Block:** A classic multiplexer/demultiplexer usually works with data, not events. The **ASR_SWITCH** specializes in ASR event forwarding.
- **`F_TRIG` / `R_TRIG` / `SR`:** These function blocks set or reset a memory function, but do not forward events. The **ASR_SWITCH** does not create states itself, but only channels existing events.
- **Adapter-Based Solutions:** In the 4diac IDE, the use of adapters is typical for modular communication – the **ASR_SWITCH** is a prime example of the flexible coupling of function blocks.

**
## Conclusion

The **ASR_SWITCH** is a simple yet effective function block for demultiplexing SET/RESET events. Its adapter interface allows for seamless integration into event-based automation solutions. Its clear state logic and minimal interface make it a reliable component for switching between two signal paths.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
