# AS_D_FF
![AS_D_FF](./AS_D_FF.svg)
* * * * * * * * * *
## Introduction
The function block **AS_D_FF** implements a simple data latch (D flip-flop) based on adapters. It stores an incoming data value with each incoming event and outputs the stored value as a signal. The block encapsulates the logic of the 4diac standard block `E_D_FF_ANY` and provides its interfaces exclusively via unidirectional adapters of type `adapter::types::unidirectional::AS`. This enables modular and standardized integration into more complex systems.
## Interface Structure

### **Event Inputs**

No direct event inputs. The block receives events exclusively via the adapter **I** (socket). The event is provided at the adapter input `I.E1`.

### **Event Outputs**

No direct event outputs. The function block sends events exclusively via the **Q** (Plug) adapter. The output event appears at the adapter output `Q.E1`.

### **Data Inputs**

No direct data inputs. The data value to be stored is provided via the **I** (Socket) adapter as `I.D1`.

### **Data Outputs**

No direct data outputs. The stored data value is output via the **Q** (Plug) adapter as `Q.D1`.

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| **I** | Socket (Input) | `adapter::types::unidirectional::AS` | Provides the input event (`E1`) and the data value to be latched (`D1`). |

| **Q** | Plug (Output) | `adapter::types::unidirectional::AS` | Outputs an output event (`E1`) and the stored data value (`D1`). |

## Functionality

The **AS_D_FF** function block operates as an asynchronous data latch.

Upon each positive event on `I.E1`, the current value of `I.D1` is transferred to the block's internal memory. Immediately afterwards, an event is triggered on `Q.E1`, and the stored value is available on `Q.D1`.

``` This logic is implemented by the internally used component `E_D_FF_ANY`:

- `I.E1` → `E_D_FF_ANY.CLK`
- `I.D1` → `E_D_FF_ANY.D`
- `E_D_FF_ANY.EO` → `Q.E1`
- `E_D_FF_ANY.Q` → `Q.D1`

The component thus behaves like a classic D flip-flop, but with a standardized adapter interface instead of direct inputs/outputs.

... ## Technical Features

- **Adapter-based encapsulation**: All data exchange occurs exclusively via unidirectional adapters of type `adapter::types::unidirectional::AS`. This facilitates reuse in different contexts and ensures a clear separation between event and data flows.
- **Internal use of `E_D_FF_ANY`**: The component utilizes the standard function block `iec61499::events::E_D_FF_ANY`, which offers a proven and efficient implementation of a D flip-flop.
- **No direct I/O pins**: The component itself does not define any event or data inputs/outputs; all communication is handled via the adapters.
- **Unidirectional adapters**: Both adapters (I and Q) are defined as unidirectional, meaning that event and data flow occurs only in one direction (from the socket to the plug).

## State Overview

The component does not have an explicit state machine. Its behavior is determined by the internal D flip-flop, which has two logical states:

- **State 0**: The stored data value is 0 (or `FALSE`).
- **State 1**: The stored data value is 1 (or `TRUE`).

The state is switched to `I.E1` by an event (if the data value has changed) and remains in this state until the next event.

## Application Scenarios
- **Signal Buffering**: Temporarily storing a digital signal that is to be retrieved at specific times (e.g., sample-and-hold).
- **Synchronization**: Adapting asynchronous data streams to a clock-driven sequence by holding a value at an event.
- **Modular Interconnection**: Used in systems based on adapter communication to maintain a uniform interface (e.g., in a chain of processing blocks).
- **Simple State Storage**: Implements simple memory functions in automation applications without relying on complex memory modules.

## Comparison with Similar Modules

| Module | Property | Difference from AS_D_FF |

|----------|-------------|-------------------------|

| **SR_FF** | Set-Reset Flip-Flop | Has separate set and reset inputs, no clock signal. |

| **E_D_FF_ANY** | Pure D flip-flop with direct I/O | Does not offer an adapter interface; requires direct connections. |

| **AS_FF_RS** (hypothetical) | RS flip-flop with adapters | Uses two adapters for set and reset, no clock signal. |

The **AS_D_FF** combines the clear logic of a D flip-flop with the flexibility of an adapter-based interface. It is particularly suitable for systems that prefer standardized, unidirectional communication.

## Conclusion

The **AS_D_FF** function block represents a practical encapsulation of a D flip-flop that communicates exclusively via adapters. Its internal behavior corresponds to a reliable data latch that responds to every incoming event. The use of adapters increases modularity and reusability, while the implementation is based on the proven `E_D_FF_ANY`. The block is ideal for all applications that require simple, event-driven data storage with a standardized interface.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]