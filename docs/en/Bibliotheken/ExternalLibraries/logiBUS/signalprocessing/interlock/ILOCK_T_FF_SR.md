# ILOCK_T_FF_SR

![ILOCK_T_FF_SR](./ILOCK_T_FF_SR.svg)

* * * * * * * * * *
## Introduction

The function block `ILOCK_T_FF_SR` is a composite function block (FB) that implements a latchable toggle flip-flop with set and reset functionality. It has an adapter interface (AE2) that enables bidirectional communication with other instances and serves for interlock chaining. The flip-flop toggles its output `Q` on every rising edge of the clock input `CLK`, provided no reset or set event is present. Latching is achieved via the adapters, which can be set by external function blocks.

## Interface Structure

### **Event Inputs**

| Name | Type | Description |

|------|-----|-------------|

| `S` | Event | Sets output `Q` to TRUE |

| `R` | Event | Sets output `Q` to FALSE |

| `CLK` | Event | Clock event – triggers a toggle on output `Q` |

### **Event Outputs**

| Name | Type | Description |

|------|-----|--------------|

| `EO` | Event | Triggered after every change of the internal state (Set, Reset, or Toggle) |

### **Data Inputs**

None.

### **Data Outputs**

| Name | Type | Description |

|------|-----|-------------|

| `Q` | BOOL | Current state of the flip-flop (TRUE = set, FALSE = reset) |

### **Adapter**

| Name | Type | Direction | Description |

|------|-----|----------|-------------|

| `ILOCK_IN` | AE2 (bidirectional) | Socket (input) | Allows the reception of latching signals from upstream devices |

| `ILOCK_OUT` | AE2 (bidirectional) | Plug (output) | Sends interlock signals to downstream components |

The adapters `ILOCK_IN` and `ILOCK_OUT` are of type `AE2` (general, bidirectional adapter). They are used to cascade multiple instances of the component, allowing a set state in one component to reset other components (interlock).

## Functionality

The component is based on an internal network consisting of three primitive functional blocks: a `E_SR` (set/reset flip-flop), a `E_SWITCH` (event-driven toggle switch), and a `E_MERGE_2` (event merger).

- **Set (`S`):** An event at `S` is routed via `E_MERGE_2` directly to the Set input of `E_SR`. The output `Q` is set to TRUE. Simultaneously, the events are passed on to the connected function blocks via the adapters.

- **Reset (`R`):** An event at `R` goes directly to the Reset input of `E_SR`. The output `Q` is set to FALSE. Reset signals received from the adapters (via `ILOCK_IN.EO1` and `ILOCK_OUT.EI1`) also trigger a reset.

- **Toggle (`CLK`):** An event at `CLK` is routed to `E_SWITCH`. Its control input, `G`, is connected to the current output, `Q`.

- If `Q = FALSE` is active, the clock event is forwarded via the output `EO0` to `E_MERGE_2.EI2` and from there to the set input of `E_SR`. Thus, `Q` is set to TRUE.

- If `Q = TRUE` is set to TRUE, the clock event is routed directly to the reset input of `E_SR` via the output `EO1`. `Q` is set to FALSE.

This results in the toggle behavior: Each clock pulse reverses the current state of `Q`.


- **Interlock:** The adapters `ILOCK_IN` and `ILOCK_OUT` are interconnected such that an incoming event from `ILOCK_IN` (e.g., from a previous block) triggers the reset input and is simultaneously passed on to the next block via `ILOCK_OUT`. This allows for the creation of a chain of flip-flops, where only one may be active at any given time.

After each state change, the event output `EO` is triggered.

## Technical Features

- **Composite FB:** The block is implemented as a network of IEC 61499 elementary modules. This ensures transparent and traceable behavior.

- **Bidirectional Adapters:** Using the adapter type `AE2` allows for flexible coupling as both a socket (input) and a plug (output).

- **Conflict Handling:** If a set and a reset event occur simultaneously (e.g., `S` and `R`), the reset event takes precedence because the reset input of `E_SR` has multiple sources and is treated with priority. The exact priority is determined by the E_SR implementation (default: reset takes precedence over set).

- **No Data Inputs:** The function block operates purely event-driven; its state is only changed by events.


**No Data Inputs:** ## State Overview

The internal flip-flop `E_SR` has two states:

- **State FALSE** (Q = FALSE): The output is reset. A clock event causes it to be set.

- **State TRUE** (Q = TRUE): The output is set. A clock event causes it to be reset.

A set event (`S`) always results in the state TRUE, regardless of the current state.

A reset event (`R`) always results in the state FALSE, regardless of the current state.

| Current State | Event | New State | Output Actions |

|-------------------|----------|---------------|------------------|

| FALSE | `S` | TRUE | `EO` is triggered |

| FALSE | `R` | FALSE | `EO` is triggered |

| FALSE | `CLK` | TRUE | `EO` is triggered |

| TRUE | `S` | TRUE | `EO` is triggered |

| TRUE | `R` | FALSE | `EO` is triggered |

| TRUE | `CLK` | FALSE | `EO` is triggered |

The adapter events act like an external reset and set the state to FALSE.

## Application Scenarios

- **Interlock Control in Safety Circuits:** Several machines or drives should interlock with each other. Only one may be active at any given time. By chaining multiple `ILOCK_T_FF_SR` devices, it can be ensured that only one flip-flop is set at any given time.

- **State Machines with Changing Modes:** This component is suitable as a toggle flip-flop that can be overridden by external set/reset signals, e.g., for manual intervention.

- **Cascaded Circuits with Feedback:** The adapter interface allows for easy integration into existing AE2-based communication structures.

## Comparison with Similar Components

- **Standard T-FF (IEC 61499)`E_T_FF`):** Offers only toggle functionality without separate set/reset inputs. The `ILOCK_T_FF_SR` extends this to include set and reset control.

- **Standard SR flip-flop (e.g., `E_SR`):** Has only set and reset, no toggle. This component combines toggle with SR.

- **Interlock component:** Many manufacturer-specific blocks implement interlock via buses; this component uses standardized adapters (AE2) and is therefore more portable.

## Conclusion

The `ILOCK_T_FF_SR` is a versatile function block that combines a toggle flip-flop with set/reset and an interlock interface. The clear separation between logic and adapter connections allows for the construction of safe, cascadable circuits. By using IEC 61499 standard components, the behavior remains traceable and expandable.