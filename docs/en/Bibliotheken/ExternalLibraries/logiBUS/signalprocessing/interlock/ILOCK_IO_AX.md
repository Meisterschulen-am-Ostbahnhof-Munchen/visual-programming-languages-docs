# ILOCK_IO_AX
![ILOCK_IO_AX](./ILOCK_IO_AX.svg)

* * * * * * * * * *
## Introduction
The function block **ILOCK_IO_AX** implements a chainable momentary latch with interlock functionality. It ensures that only one element in a chain is active at any given time – as soon as another function block in the chain becomes active, it is reset. The function block is specifically designed for use with AX/AX2 adapter interfaces.
## Interface Structure
The block does not have any traditional event or data inputs/outputs at the function block level. All communication takes place via **adapter interfaces**. The signals transmitted via the adapters are detailed below.

### **Event Inputs**

| Signal | Adapter | Description |

|--------|---------|--------------|

| `IN.E1` | IN (AX) | Trigger for processing the input signal. |

| `ILOCK_IN.EO1` | ILOCK_IN (AX2) | Event from the parent function block in the chain (e.g., when a different output becomes active there). |

| `ILOCK_OUT.EI1` | ILOCK_OUT (AX2) | Event from the child function block in the chain (e.g., when it becomes active). |

### **Event Outputs**

| Signal | Adapter | Description |

|--------|---------|--------------|

| `OUT.E1` | OUT (AX) | Confirmation that processing is complete. |

| `ILOCK_IN.EI1` | ILOCK_IN (AX2) | Event sent to the parent FB (sent with each processing cycle). |

| `ILOCK_OUT.EO1` | ILOCK_OUT (AX2) | Event sent to the child FB (sent with each processing cycle). |

### **Data Inputs**

| Signal | Adapter | Description |

|--------|---------|--------------|

| `IN.D1` | IN (AX) | Set input (BOOL) – if TRUE and no other FB in the chain is active, the output becomes active. |

| `ILOCK_IN.DO1` | ILOCK_IN (AX2) | State of the parent FB (TRUE means that the output is active there). |

| `ILOCK_OUT.DI1` | ILOCK_OUT (AX2) | State of the child function block (TRUE means that its output is active). |

### **Data Outputs**

| Signal | Adapter | Description |

|--------|---------|--------------|

| `OUT.D1` | OUT (AX) | Output signal (BOOL) – active when `IN.D1` is set and no other function block in the chain is active. |

| `ILOCK_IN.DI1` | ILOCK_IN (AX2) | Passes its own output signal to the parent function block. |

| `ILOCK_OUT.DO1` | ILOCK_OUT (AX2) | The output signal is passed on to the subordinate function block. |

### **Adapter**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| `IN` | Socket (Input) | `adapter::types::unidirectional::AX` | Input signal from the user (set input and event). |

| `OUT` | Plug (Output) | `adapter::types::unidirectional::AX` | Output signal to the user (output value and confirmation). |

| `ILOCK_IN` | Socket (Input) | `adapter::types::bidirectional::AX2` | Connection to the **parent** function block in the chain. |

| `ILOCK_OUT` | Plug (Output) | `adapter::types::bidirectional::AX2` | Connection to the **subordinate** FB in the chain. |

## Functionality
The FB operates as a **momentary switch with interlock** (also known as an "exclusive latch"). In state `REQ`, the following logic is executed:

- The output `OUT.D1` is only **TRUE** if the input `IN.D1` is active **and** no other FB in the chain is currently active (`ILOCK_IN.DO1` from the predecessor and `ILOCK_OUT.DI1` from the successor must be FALSE).
- The active state of the function block (`OUT.D1`) is passed on via the adapters `ILOCK_IN.DI1` (to the predecessor) and `ILOCK_OUT.DO1` (to the successor).
- Each triggering event input (whether from `IN.E1`, `ILOCK_IN.EO1`, or `ILOCK_OUT.EI1`) leads to a recalculation of the logic and the output of all events (`OUT.E1`, `ILOCK_IN.EI1`, `ILOCK_OUT.EO1`).

Due to the bidirectional state transmission via the ILOCK adapters, all function blocks in the chain are aware of each other, so only one can be active at a time.

## Technical Features
- **Chainable Interlock Structure**: Multiple ILOCK_IO_AX function blocks can be chained together by connecting `ILOCK_OUT` of one function block to `ILOCK_IN` of the next. The chain can be of any length.
- **No Own Events/Data at the Function Block Level**: All signal transmission takes place via the standardized AX/AX2 adapters. This allows for easy integration into existing adapter-based systems.
- **Only One Processing at a Time**: Since only one state (`REQ`) exists, the same logic is executed for each event. There are no internal state changes.

## State Overview
The function block has only one state:

+-------+
|  REQ  |  (Standardzustand)
+-------+
| ^
| | (Ereignisse: IN.E1, ILOCK_IN.EO1, ILOCK_OUT.EI1)
+-+
In state `REQ`, the algorithm `REQ` and the event outputs are executed. This state is never exited.

## Application Scenarios
- **Control of switching devices** (e.g., valves, motors) in a line where only one may be active at a time.
- **Non-priority selection** from multiple sources (e.g., a push-button panel with interlock).
- **Chained safety controllers** where activating a subsequent stage must deactivate the previous one (or vice versa).

## Comparison with Similar Function Blocks

| Function Block | Description | Difference to ILOCK_IO_AX |

|----------|---------------|----------------------------|

| **SR Flip-Flop** | Sets output on SET, resets on RESET. | No interlock – multiple function blocks (FBs) can be active simultaneously. |

**Simple Latch (e.g., LATCH_AX)** | Holds the value until triggered again. | No coupling with other FBs. |

**ILOCK_IO_AX** | Exclusive activation in a chain. | Enforces that only one FB is active – ideal for line control systems. |

## Conclusion
The **ILOCK_IO_AX** is a specialized function block for exclusive activation in chained configurations. By using AX/AX2 adapters and bidirectional status feedback, robust interlock logic is implemented without separate wiring. It is particularly suitable for modular control structures where multiple actuators may only be active sequentially or individually.
