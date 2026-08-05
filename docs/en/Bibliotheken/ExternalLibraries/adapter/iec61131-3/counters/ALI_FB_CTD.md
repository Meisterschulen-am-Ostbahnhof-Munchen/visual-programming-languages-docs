# ALI_FB_CTD
![ALI_FB_CTD](./ALI_FB_CTD.svg)
* * * * * * * * * *
## Introduction
The **ALI_FB_CTD** is a down counter for LINT values (64-bit integers) with adapter interfaces according to IEC 61499. It is specifically designed for use with the unidirectional adapters `AX` (event/boolean carrier) and `ALI` (LINT value carrier). The function block encapsulates the standard FB `FB_CTD_LINT` from the library `iec61131::counters` and extends it with an adapter-based connection that enables loose coupling between the function blocks.
The function block fires its event outputs with every update – regardless of whether the counter value actually changes. For change-triggered processing, it is recommended to use a `AX_D_FF` as a filter.

## Interface Structure

### **Event Inputs**

None – all event and data information is transmitted via adapter sockets (CD, LD, PV).

### **Event Outputs**
- **CNF** (Event): Acknowledgement of the executed operation (sent after every update).

### **Data Inputs**

There are no separate data inputs. The input data is provided via the following adapter sockets:

- **CD** (Socket, type `adapter::types::unidirectional::AX`): Down count pulse (activates the counting process).

### - **LD** (Socket, type `adapter::types::unidirectional::AX`): Load pulse (activates loading the preset value).
- **PV** (Socket, type `adapter::types::unidirectional::ALI`): Preset value (LINT); the value is adopted during loading (LD).

### **Data Outputs**
There are no separate data outputs. The output data is provided via the following adapter plugs:

- **Q** (Plug, type `adapter::types::unidirectional::AX`): Output signal (Bool) – indicates whether the counter reading has reached **zero**.
- **CV** (Plug, type `adapter::types::unidirectional::ALI`): Current counter value (LINT).

### **Adapters**

| Name | Direction | Type | Description |

|-------------|----------|-----|--------------|

| CD | Socket | AX | Down counter pulse (Event + Bool) |

| LD | Socket | AX | Charge pulse (Event + Bool) |

| PV | Socket | ALI | Preset value (LINT) |

| Q | Plug | AX | Output signal when counter value = 0 |

| CV | Plug | ALI | Current counter value (LINT) |

## Functionality

The ALI_FB_CTD implements a down counter with charge function. The internal logic is implemented by the function block `FB_CTD_LINT`:

1. **Load**

An event at socket **LD** (via `LD.E1`) transfers the data value from **PV** (via `PV.D1`) to the internal counter. The counter value is then set to the preset value.

2. **Count Down**

An event at socket **CD** (via `CD.E1`) decrements the current counter value by 1, provided it is greater than 0.

3. **Output Signaling**

The current counter value is always output via plug **CV** (as a LINT).

- The plug **Q** returns `true` when the counter reaches **zero** (Boolean value via the AX adapter).
- The **CNF** event is sent after **every** processing operation (CD, LD, and PV).

4. **Event Passing**

The incoming events from CD, LD, and PV are all combined at the **REQ** input of the internal function block. Its **CNF** output is then distributed to the output adapters (Q.E1, CV.E1) and to the external event output CNF.

## Technical Features
- **Always Triggering**: The function block sends the output events (Q.E1, CV.E1, CNF) with **every** update – even if the counter value does not change (e.g., after repeated CD resets to 0). For change-based triggering, a `AX_D_FF` (edge detector) must be interposed.
- **Adapter Coupling**: The use of unidirectional adapters (AX, ALI) enables flexible interconnection in IEC 61499 networks without rigid data and event connections.
- **LINT Values**: The counter operates with 64-bit integers, suitable for large counting ranges.
- **Internal Structure**: The function block delegates all counting logic to the proven standard FB `FB_CTD_LINT` from the `iec61131::counters` library.

## State Overview

The ALI_FB_CTD does **not have an explicit state machine** in the FB network. Its behavior is purely event-driven and combinatorial:

| Input event | Action |

|------------------|--------|

| LD activated | Counter reading = Preset value |

| CD activated | Decrement counter reading (if > 0) |

| PV activated | No counter change, but a CNF event is sent. The data value from PV is not directly adopted – an LD is required. |

The current counter reading and the Boolean output are updated after each step.

## Application Scenarios
- **Piece Counter in Manufacturing**: At the end of a production step, a pulse is sent to CD; the counter counts down from a predefined quantity (PV). At zero, Q is activated and signals, for example, "Batch complete".
- **Time Control with Pulse Counting**: A clock generator sends pulses to CD; after a predefined number (PV), an event is triggered.
- **Maintenance Interval**: The counter serves as a countdown in maintenance cycles; an alarm is triggered when it reaches 0.

## Comparison with Similar Function Blocks

| Function Block | Special Feature |

|----------|--------------|

| **ALI_FB_CTD** (this function block) | Uses AX and ALI adapters; always triggers; suitable for adapter-based architectures. |

| **FB_CTD_LINT** (Standard) | Pure data/event function block without adapters; event triggering directly via the interfaces. |

| **CTU** (Upward Counter) | Counts upwards instead of downwards; different application logic. |

| **Counter Function Blocks with Edge Suppression** | They have their own filter logic (e.g., AX_D_FF) and only trigger on actual value changes. |

The ALI_FB_CTD is particularly suitable for adapter-based environments where simple, reliable downcounting without additional filters is desired.

## Conclusion

The **ALI_FB_CTD** is a robust downcounter for LINT values, specifically designed for adapter technology in IEC 61499 systems. It offers a clear, adapter-based interface and is reliable and tested thanks to the internal use of `FB_CTD_LINT`. Its "always-trigger" behavior makes it suitable for applications where every state change at the input should be immediately forwarded. Where change-based triggering is required, a simple filter block can be added. Overall, it represents a valuable addition to adapter-oriented automation solutions.