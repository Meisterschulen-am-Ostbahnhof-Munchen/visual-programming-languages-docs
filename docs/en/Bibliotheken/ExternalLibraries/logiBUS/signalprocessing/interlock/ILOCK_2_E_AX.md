# ILOCK_2_E_AX
![ILOCK_2_E_AX](./ILOCK_2_E_AX.svg)

* * * * * * * * * *
## Introduction
The function block **ILOCK_2_E_AX** provides two bistable outputs with mutual interlock and a toggle function. It is event-driven and outputs its states via two adapters (type `AX`). This block is suitable for applications requiring two mutually exclusive signals, such as controlling switches, valves, or motors.
## Interface Structure
### **Event Inputs**

| Name | Description |

|--------|-----------------------------------------------|

| `SET1` | Sets output `OUT1` to TRUE and `OUT2` to FALSE |

| `CLK1` | Toggles the state of `OUT1` if it is not already toggled |

| `SET2` | Sets output `OUT2` to TRUE and `OUT1` to FALSE |

| `CLK2` | Toggles the state of `OUT2` if it is not already toggled |

| `R` | Sets both outputs to FALSE (Reset) |

### **Event Outputs**

The function block has no dedicated event outputs. Output signals are transmitted exclusively via the **adapters** (see below).

### **Data Inputs**
None.

### **Data Outputs**
No direct data outputs. The current states of the flip-flops can be retrieved via the **adapters** (see below).

### **Adapters**

| Name | Type | Description |

|--------|------|--------------------------------------------------|

| `OUT1` | `AX` | Provides the state of the first flip-flop (data output `D1`) and acknowledges changes via event output `E1` |

| `OUT2` | `AX` | Provides the state of the second flip-flop (data output `D1`) and acknowledges changes via event output `E1` |

## Functionality
This function block operates in an event-driven manner. An incoming event triggers a state change, which is immediately output to the corresponding adapters.

- **SET1**: Sets `OUT1.D1 = TRUE` and `OUT2.D1 = FALSE`. The internal edge buffers (`EDGE1`, `EDGE2`) are reset.
- **SET2**: Sets `OUT1.D1 = FALSE` and `OUT2.D1 = TRUE`. The edge buffers are reset.
- **CLK1**: Toggles `OUT1.D1` (if not already toggled by a previous `CLK1` event) and sets `OUT2.D1 = FALSE`. The edge buffer `EDGE1` prevents repeated toggling on the same event.
- **CLK2**: Toggles `OUT2.D1` (edge buffer `EDGE2`) and sets `OUT1.D1 = FALSE`.
- **R**: Sets both outputs to FALSE and clears the internal edge buffers.

The interlock ensures that only one of the two outputs can be TRUE at any given time. When one output is toggled, the other is always set to FALSE.

## Technical Features
- The module uses **adapters** (type `AX`) as outputs. This allows for flexible connection to other modules that support the same adapter.
- An **internal edge detection** (variables `EDGE1`, `EDGE2`) prevents multiple toggling on a single event. The edge buffer is only reset after a reset or an explicit setting, allowing for further toggling.
- All algorithms are executed **atomically** in the ECC states; the module outputs an event via the adapters (`OUT1.E1` or `OUT2.E1`) after each action.
- The initial states of all outputs are **FALSE**.

## State Overview
The following states underlie the ECC (Executive Control Cycle):

- **STOP** – Wait state (initial)
- **SET1** – Sets channel 1
- **SET2** – Sets channel 2
- **TOGGLE1** – Toggles channel 1, disables channel 2
- **TOGGLE2** – Toggles channel 2, disables channel 1
- **RESET** – Resets both channels

The transitions between states are triggered by the received events (`SET1`, `SET2`, `CLK1`, `CLK2`, `R`) and automatically return to state `STOP` after the actions are executed (transition condition). `1`).

## Application Scenarios
- **Alternating operation** of two consumers, e.g., feed/return valves, where both must never be active simultaneously.
- **Clock-controlled switching** between two states (e.g., direction change of a conveyor belt) using the toggle inputs.
- **Central reset function** for a group of bistable actuators via the `R` input.

## Comparison with Similar Function Blocks
Compared to a simple set-reset flip-flop (e.g., `E_SR`), **ILOCK_2_E_AX** offers two outputs with integrated interlocking and a toggle function. While `E_SR` only switches a single output, this function block can control two coupled signals. The use of adapters instead of direct data ports allows for standardized and reusable coupling with other components.

## Conclusion
The **ILOCK_2_E_AX** function block is a compact, event-driven component for implementing interlocked, bistable outputs with an optional toggle function. Thanks to its adapter-based interface and the clear separation of setting, toggling, and resetting, it is particularly suitable for safety-critical or logically linked control tasks in automation technology.
