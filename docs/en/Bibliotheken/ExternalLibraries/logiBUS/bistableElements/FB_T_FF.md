# FB_T_FF

[[Image of the function block – shown in the 4diac IDE as a symbol with an event input REQ, output CNF, data inputs CLK (BOOL) and RST (BOOL), and data output Q (BOOL)]]

![FB_T_FF](./FB_T_FF.svg)

* * * * * * * * * *

## Introduction

The **FB_T_FF** (Toggle Flip-Flop) implements an edge-triggered, asynchronously resettable frequency divider or toggle switch. On each rising clock edge at the **CLK** input, the output **Q** is inverted (toggled). A high level at the **RST** input immediately resets **Q** to `FALSE`. This function block is particularly suitable for binary state transitions in control sequences.

## Interface Structure

### **Event Inputs**

| Event | Associated Data | Description |

|----------|-------------------|--------------------------------------------|

| `REQ` | `CLK`, `RST` | Normal execution job; triggers the algorithm |

### **Event Outputs**

| Event | Associated Data | Description |

|----------|-------------------|--------------------------------------------------|

| `CNF` | `Q` | Confirms execution, returns the current value of `Q` |

### **Data Inputs**

| Name | Type | Description |

|------|-------|---------------------------------|

| `CLK`| BOOL | Clock signal (edge detection) |

| `RST`| BOOL | Asynchronous reset (active high) |

### **Data Outputs**

| Name | Type | Description |

|------|-------|--------------------------------------------|

| `Q` | BOOL | Output – toggles on rising CLK edge, unless reset is active |

### **Adapters**

No adapters available.

## Functionality

This function block is called using the **REQ** event. On each call, the internal variable **EDGE** (Bool, initial `TRUE`) is updated as follows:

1. **Reset priority:** If `RST = TRUE` is active, `Q` is immediately set to `FALSE`.

2. **Edge detection:** If `RST` is not active and the condition `CLK AND NOT EDGE` is met, there is a **rising edge** of `CLK`. In this case, `Q` is inverted to `Q := NOT Q`.


2. **Edge detection:** If `RST` is not active and the condition `CLK AND NOT EDGE` is met, there is a **rising edge** of `CLK`. In this case, `Q` is inverted to `Q := NOT Q`. 3. **Storage:** After evaluation, `EDGE := CLK` is set so that the edge can be detected on the next call.

The algorithm is executed in the internal **REQ** state; after the algorithm, the **CNF** event is sent.

## Technical Features

- **Immediate Edge Detection:** A rising edge is detected by comparing the current `CLK` value with the previous one (stored in `EDGE`). This is a typical software implementation of an edge-triggered flip-flop.

- **Asynchronous Reset:** The reset takes effect immediately with each call, regardless of the clock edge.

- **Initial State:** `Q` is undefined after the function block starts; it is only set by the first REQ call or a reset. The internal **EDGE** is initially set to `TRUE`, ensuring that the first rising edge (from `FALSE` to `TRUE`) is correctly detected.

## State Overview

The function block is implemented as a **SimpleFB** with a single EC state:

| State | Incoming Events | Outgoing Action | Outgoing Event |

|---------|-----------------------|-------------------|----------------------|

| `REQ` | `REQ` | Execute algorithm `REQ` (Toggle/Reset logic) | `CNF` |


The state is immediately reactivated after processing; there are no wait or follow-up states.

## Application Scenarios

- **Frequency Divider:** Applying a square wave signal to `CLK`; half the frequency appears at `Q`.

- **Binary State Change:** Switching a light or valve on each clock pulse.

- **Reset-Proof Toggle:** By controlling `RST`, the output can be forced into a defined default state.

- **Pulse Counter:** Combining several FB_T_FFs in series results in a binary counter.

## Comparison with Similar Function Blocks

| Function Block | Property |

|----------------|-----------------------------------------------------------------------------|

| **SR Flip-Flop**| Set and reset via separate inputs; no toggle behavior. |

**D-Flip-Flop** | Takes the value of `D` on the clock edge; no toggle, no reset integrated. |

**FB_T_FF** | Inverts the output on each rising edge; asynchronous reset possible. |

The **FB_T_FF** is therefore ideal for simple switching tasks where no set/reset input is required.

## Conclusion

The **FB_T_FF** implements a robust, edge-triggered toggle flip-flop with asynchronous reset. Its compact implementation makes it suitable for time-critical control systems in automation technology where reliable state transitions are required. Edge detection is cleanly implemented in software and requires no additional hardware.


The **FB_T_FF** is therefore ideal for simple switching tasks where a set/reset input is not needed. ---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]