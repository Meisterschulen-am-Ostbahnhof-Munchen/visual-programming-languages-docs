# AX_T_FF_SR_SYM_STORE
![AX_T_FF_SR_SYM_STORE](./AX_T_FF_SR_SYM_STORE.svg)
* * * * * * * * * *
## Introduction
The function block `AX_T_FF_SR_SYM_STORE` implements an event-driven, bistable flip-flop with set (S), reset (R), and toggle (CLK) functions. Its special feature is its symmetrical startup behavior: The initial state at system startup can be defined and saved via a special adapter (`Q_INIT`).
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-------|---------------------------------------------|

| S | Event | Sets the output `Q` to TRUE |

| R | Event | Sets output `Q` to FALSE |

| CLK | Event | Toggles output `Q` (TRUE ↔ FALSE) |

### **Event Outputs**
No direct event outputs are available. Output data is provided exclusively via the adapter interfaces.

### **Data Inputs**
No direct data inputs. Initial value and state are read and output via adapters.

### **Data Outputs**
No direct data outputs. The current state is made available via the adapters.

### **Adapters**

| Name | Type | Comment |

|---------|----------------------------------|---------------------------------------------|

| Q | adapter::types::unidirectional::AX | Returns the current state of the flip-flop (single-wire Boolean value) |

| Q_INIT | adapter::types::bidirectional::AX2 | Bidirectional interface for the initial value of `Q` at INIT (includes three inputs/outputs: e.g., DI1/DO1, EI1/EO1) |

## Functionality
The function block operates as an SR flip-flop (set-reset) with an additional toggle function. The process is divided into initialization and operation:

1. **Initialization (START → Init)**

After system startup, the function block is in the START state. As soon as the event `EI1` arrives at the adapter `Q_INIT`, it switches to the Init state. There, the initial value provided via `Q_INIT.DI1` is read.

- If the initial value is FALSE, the system subsequently enters the RESET state.
- If the initial value is TRUE, the system enters the SET state.

In both cases, the corresponding outputs `Q.D1` and `Q_INIT.DO1` are set to their initial values.

2. **Operation (SET ↔ RESET)**

Starting from SET or RESET, each event at inputs S, R, or CLK toggles the state:

- **S** → switches to SET (sets Q = TRUE)
- **R** → switches to RESET (sets Q = FALSE)
- **CLK** → toggles the state (from SET to RESET or vice versa)

With each state change, the output data is updated via the adapters, and the events `Q.E1` and `Q_INIT.EO1` are output.

## Technical Features
- **Adapter-Based Input/Output**

Instead of classic data inputs/outputs, the module uses adapter interfaces. This enables flexible coupling with other modules or system components that also support the adapter protocol.

- **Symmetrical Startup Behavior**

The bidirectional adapter `Q_INIT` allows the initial state to be set externally and read after initialization. This ensures deterministic restart behavior – particularly important for safety-critical or stateful applications.

- **Toggle Function (CLK)**

In addition to the classic set and reset events, the clock input CLK allows for easy switching of the output without requiring a separate set/reset signal.

- **No Data Inputs/Outputs**

This functional reduction simplifies the interface and avoids confusion with the adapters.

## State Overview

| State | Description | Output on Event |

|---------|------------------------------------------|-----------------------------------------------|

| START | Initial Wait State | Waits for initialization event via Q_INIT.EI1 |

| Init | Initialization | Reads Q_INIT.DI1, sets Q and Q_INIT.DO1 accordingly |

| SET | Output Q = TRUE | Processes S, R, CLK (see Transitions) |

| RESET | Output Q = FALSE | Processes S, R, CLK (see Transitions) |

**State Transitions (Simplified)**

- START → Init (Event Q_INIT.EI1)
- Init → SET (if Q_INIT.DI1 = TRUE)
- Init → RESET (if Q_INIT.DI1 = FALSE)
- SET → RESET (on Event R or CLK)
- RESET → SET (on Event S or CLK)

## Application Scenarios
- **Machine State Storage**

In production plants, this function block can store the current operating mode (e.g., "On" or "Off") and restore it upon restart.

- **Initialization of Control Sequences**

Scenarios requiring a defined start value (e.g., valve position at the beginning of a batch) benefit from the symmetrical INIT behavior.

- **Event-Driven Toggle Functions**

For example, toggling an indicator light with each key press, without requiring separate on and off commands.

## Comparison with Similar Function Blocks
- **Standard E_SR (E_R-SET)**

Simple set-reset flip-flop without toggle functionality and without symmetric start initialization. The initial state is usually undefined or must be set externally.

- **E_RS**

Offers reset prioritization, but also no toggle or INIT functionality.

- **Toggle Function Blocks (e.g., E_Toggle)**

Pure toggle function blocks usually only have a clock input and no bidirectional adapter for initialization. The AX_T_FF_SR_SYM_STORE combines all three functions in one function block.

- **Adapter-Based Function Blocks**

A few function blocks in the 4diac library use adapters for state output. This design allows for a clean separation of event and data paths and facilitates reuse in complex systems.

## Conclusion

The `AX_T_FF_SR_SYM_STORE` is a powerful and flexible function block for stateful control tasks. Its combination of Set, Reset, and Toggle functions, coupled with symmetrical startup behavior via adapters, makes it ideal for applications requiring defined restart behavior. Through the use of adapters, it integrates seamlessly into modular and distributed automation systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
