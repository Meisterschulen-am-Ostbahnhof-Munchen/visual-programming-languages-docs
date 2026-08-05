# BasicOne_AX
![BasicOne_AX](./BasicOne_AX.svg)

* * * * * * * * * *
## Introduction
The function block `BasicOne_AX` is a basic IEC 61499 block of type *Basic Function Block*, serving as a template for simple control tasks. It implements an initializable switching of a Boolean signal using unidirectional adapter interfaces of type `AX`. The block is suitable for scenarios in which an input signal needs to be copied to an output and the initialization state needs to be monitored.
## Interface Structure

### **Event Inputs**

| Event | Type | With Variables | Comment |
|----------|-----|----------------|------------|
| `INIT` | `EInit` | `QI` | Initialization Request |

### **Event Outputs**

| Event | Type | With Variables | Comment |
|----------|-----|---------------|-----------|
| `INITO` | `EInit` | `QO` | Initialization Confirmation |

### **Data Inputs**

| Variable | Type | Comment |
|----------|-----|-----------|
| `QI` | `BOOL` | Input Qualifier (Turns initialization on/off) |

### **Data Outputs**

| Variable | Type | Comment |
|----------|-----|-----------|
| `QO` | `BOOL` | Output Qualifier (Reflects the initialization state) |

#### **Adapter**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| Plug (Output) | `DO1` | `adapter::types::unidirectional::AX` | Unidirectional adapter for data transmission (AX interface) |
Socket (input) | `DI1` | `adapter::types::unidirectional::AX` | Unidirectional adapter for receiving data (AX interface) |

## Functionality

The function block iterates through a finite state machine (ECC) with the states `START`, `Init`, `Initialized`, `NormalOp`, and `DeInit`.

- **START** → **Init**: Upon the occurrence of the event `INIT`, the process is executed with `QI = TRUE`. The algorithm `initialize` sets `QO` to the value of `QI` (i.e., `TRUE`). The output `INITO` signals successful initialization.
- **Init** → **Initialized**: After initialization, the automaton immediately transitions to the state `Initialized` (transition with condition `1`). The module remains in this state until either an event arrives at socket `DI1.E1` or a subsequent event, `INIT`, triggers deinitialization with `QI = FALSE`.
- **Initialized** → **NormalOp**: Upon arrival of the adapter event `DI1.E1`, the module transitions to state `NormalOp`. The algorithm `normalOperation` then performs the actual switching: If `QI = TRUE` is present, the value of the adapter input `DI1.D1` is copied to the adapter output `DO1.D1`. Additionally, `QO` is set to the current value of `QI` (remaining `TRUE` until `QI` is set to `FALSE`).
- **NormalOp** → **Initialized**: After execution, the function block immediately returns to the state `Initialized` (transition `1`), ready for the next `DI1.E1` event.
- **Initialized** → **DeInit**: When the event `INIT` with `QI = FALSE` is received, deinitialization occurs. The algorithm `deInitialize` sets `QO` to `FALSE` and the adapter output `DO1.D1` to `FALSE`. Then, `INITO` is output.
- **DeInit** → **START**: After deinitialization, the automaton returns to its initial state and awaits re-initialization.

In summary, the function block operates as a *triggered passthrough*: The adapter input is copied to the adapter output with each event at the socket, but only if the function block was previously initialized correctly (`QI=TRUE` for `INIT`).

## Technical Features
- **Adapter-Based Interface**: Input/output data is not exchanged via direct variables, but rather via the unidirectional adapters `DI1` and `DO1` (type `AX`). This enables flexible coupling with other function blocks of the same adapter type.
- **Initialization Logic**: The function block distinguishes between an initialized (`QI=TRUE`) and a deinitialized (`QI=FALSE`) state. Incoming adapter events are only processed after successful initialization.
- **Package Name**: The function block is organized in the package `logiBUS::utils::sequence::one`, indicating its use in a logiBUS environment.
- **Automatic State Transitions**: The transitions of `Init→Initialized`, `NormalOp→Initialized`, and `DeInit→START` occur without any further condition (transition `1`), meaning the execution of the algorithms is complete.

## State Overview

The ECC (Execution Control Chart) of the module comprises five states:

| State | Description |
|---------|--------------|
| `START` | Waiting for the first `INIT` event with `QI=TRUE`. |
| `Init` | Executes initialization algorithm, sets `QO=QI`, and sends `INITO`. |
| `Initialized` | Idle state after successful initialization; waits for `DI1.E1` or another `INIT` (with `QI=FALSE`). |
| `NormalOp` | Performs passthrough (copies `DI1.D1` to `DO1.D1` if `QI=TRUE` is present). |
| `DeInit` | Performs deinitialization (sets `QO` and `DO1.D1` to `FALSE`), sends `INITO`. |

## Application Scenarios
- **Signal Passthrough with Fuse**: A Boolean signal (e.g., enabling a process) should only be passed from a source to a sink if the function block has been initialized beforehand. Sending `INIT` followed by `QI=FALSE` again interrupts the passthrough.
- **Initialization Sequence in Manufacturing Plants**: Before production starts, the function block is initialized (e.g., checking safety conditions). Only then may actuators be controlled via `DO1`.
- **Data Transfer in Modular Systems**: The unidirectional adapter `AX` allows loose coupling between modules – the component serves as a simple "pass-through" in a data chain.

## Comparison with Similar Components
- **BasicOne (without adapter)**: A typical `BasicOne` component uses direct input/output variables. `BasicOne_AX` extends this with an adapter-based interface, improving reusability and structuring in larger systems.
- **Standard `E_SR` (Set/Reset)**: A set/reset flip-flop stores a state, while `BasicOne_AX`It has no memory function – the output follows the input only during active initialization and upon each event.
- **Move Function Block**: A `MOVE` block continuously copies values. In contrast, `BasicOne_AX` only copies upon an event (triggered) and only after successful initialization.

## Conclusion

The `BasicOne_AX` is a minimalist yet robust IEC 61499 block for initialization-controlled signal switching with an adapter interface. Its clear state logic and the separation of initialization and operation make it particularly suitable for safety-critical or sequential applications where a defined start state is required before data transmission. The use of unidirectional adapters increases modularity and facilitates integration into complex automation systems.
