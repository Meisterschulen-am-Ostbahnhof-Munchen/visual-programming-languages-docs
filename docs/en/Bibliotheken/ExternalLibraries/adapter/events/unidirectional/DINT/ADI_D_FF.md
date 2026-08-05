# ADI_D_FF
![ADI_D_FF](./ADI_D_FF.svg)

* * * * * * * * * *
## Introduction
The function block `ADI_D_FF` implements a data latch (D flip-flop) based on adapters. It serves to store and output a Boolean value when an event occurs. The block encapsulates the industrial standard function block `E_D_FF_ANY` and communicates exclusively via the unidirectional adapters `ADI`.
## Interface Structure

### **Event Inputs**

The function block has no separate event inputs. Event control is handled exclusively via the adapter `I`.

## **Event Outputs**

The function block has no separate event outputs. Event output is exclusively via the `Q` adapter.

### **Data Inputs**

The FB has no separate data inputs. Data is acquired via the `I` adapter.

### **Data Outputs**

The FB has no separate data outputs. Data is output via the `Q` adapter.

### **Adapters**

| Type | Name | Direction | Description |

|-----|-------------|-----------|-------------|

| `adapter::types::unidirectional::ADI` | `I` | Input (Socket) | Outputs the clock signal (`E1`) and the data value to be latched (`D1`). |

| `adapter::types::unidirectional::ADI` | `Q` | Output (Plug) | Outputs the stored data value (`D1`) and an acknowledgment event (`E1`). |

## Functionality

The `ADI_D_FF` operates on the principle of an edge-triggered D flip-flop. Each event arriving at the adapter `I` (`E1`) is interpreted as a clock signal (CLK). At each clock cycle, the current data value `D1` is received from the input, stored internally, and output at the adapter `Q` both as a new data value (`D1`) and as an acknowledgment event (`E1`).

Internally, the standardized IEC 61499 function block `E_D_FF_ANY` is used, which provides precisely this functionality. The adapters serve as uniform, reusable interfaces for events and data.

## Technical Features
- All data and event exchange takes place via adapters of type `ADI` (unidirectional event and data transmission). This makes the function block easy to integrate into adapter-based architectures.
- No independent state machine is implemented; The entire logic is implemented by the internal function block `E_D_FF_ANY`.
- The implementation follows the IEC 61499-1 (Annex A) standard and uses the Eclipse 4diac IDE.

## State Overview

The function block does not have explicit states in the sense of a state machine. Its behavior corresponds to a simple flip-flop:

- At each clock cycle (event at `I.E1`), the current value is taken from `I.D1` and passed to `Q.D1`.
- The stored value remains constant until the next clock cycle.
- The output `Q.E1` signals the transfer of a new value.

## Application Scenarios
- **Synchronization:** Holding an asynchronously arriving Boolean signal at a defined clock time.
- **Latch:** Holding a data value for further processing in subsequent function block networks.
- **Buffering:** Decoupling event and data sources from further processing (e.g., in time-critical processes).

## Comparison with Similar Function Blocks

| Function Block | Function | Differences |

|----------|----------|--------------|

| `ADI_SR_FF` | Set-Reset Flip-Flop | Stores based on set/reset behavior, not clock-driven. |

| `ADI_T_FF` | T Flip-Flop | Toggles the state on every clock cycle. |

| `ADI_D_FF` | D flip-flop | Stores the incoming data value on the clock edge (as described here). |

## Conclusion

The `ADI_D_FF` is a compact, adapter-based D flip-flop component for the 4diac IDE. It offers a clean separation of clock and data and is ideally suited for use in event-driven automation solutions. The adapter encapsulation increases reusability and simplifies integration into existing projects.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
