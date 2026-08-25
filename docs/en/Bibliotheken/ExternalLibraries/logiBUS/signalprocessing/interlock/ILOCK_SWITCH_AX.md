# ILOCK_SWITCH_AX

![ILOCK_SWITCH_AX](./ILOCK_SWITCH_AX.svg)
*(No image available)*

* * * * * * * * * *
## Introduction

The function block **ILOCK_SWITCH_AX** implements interlocking switch control for bidirectional axes. It prioritizes the last active input and ensures that both directions are never activated simultaneously. Communication occurs exclusively via adapter interfaces of type `adapter::types::unidirectional::AX`. This version is specifically designed for use in modular control systems with standardized adapters.

## Interface Structure

### **Event Inputs**

None (all events are transmitted via the adapter sockets).

#### **Event Outputs**

None (all events are transmitted via the adapter plugs).

### **Data Inputs**

None (all data is transmitted via the adapter sockets).

### **Data Outputs**

None (all data is transmitted via the adapter plugs).

### **Adapters**

| Name | Type | Direction | Comment |
|------|-----|----------|-----------|
| UP_IN | `adapter::types::unidirectional::AX` | Socket | Input for forward/upward direction |
| DOWN_IN | `adapter::types::unidirectional::AX` | Socket | Input for reverse/downward direction |
| UP_OUT | `adapter::types::unidirectional::AX` | Plug | Output for forward/upward direction |
| DOWN_OUT | `adapter::types::unidirectional::AX` | Plug | Output for reverse/downward direction |

Each adapter provides an event output `E1` and a data input/output `D1` (of type BOOL). The sockets receive requests, and the plugs pass on the switched states.

## Functionality

The logic is implemented using a finite state machine (ECC). The function block is initially in state `STOP`. A change to the states `UP` or `DOWN` occurs when the corresponding socket returns an event `E1` with the data value `D1` set (i.e., `UP_IN.E1[UP_IN.D1]` or `DOWN_IN.E1[DOWN_IN.D1]`).

- In the state `UP`, `UP_OUT.D1` is set to `TRUE` and `DOWN_OUT.D1` is set to `FALSE`.
- In the state `UP`, `UP_OUT.D1` is set to `TRUE` and `DOWN_OUT.D1` to `FALSE`.

- In state `DOWN`, `DOWN_OUT.D1` is set to `TRUE` and `UP_OUT.D1` to `FALSE`.

A change from the current state to the other is only possible when the other socket becomes active (prioritization of the last active input). The conditions are differentiated as follows:

- **UP → DOWN**: either directly via `DOWN_IN.E1[DOWN_IN.D1]` or when the current input is deactivated and the other is active (`UP_IN.E1[NOT UP_IN.D1 AND DOWN_IN.D1]`).
- **DOWN → UP**: analogously via `UP_IN.E1[UP_IN.D1]` or `DOWN_IN.E1[NOT DOWN_IN.D1 AND UP_IN.D1]`.

If the active input is lost without the other becoming active, an intermediate state (`UP_STOP` or `DOWN_STOP`) is reached. In this state, the outputs are set to `FALSE`, and then the state machine immediately transitions to the `STOP` state.

## Technical Features

- **Adapter-based interface**: The function block uses only adapters of type `unidirectional::AX`, which enables clean encapsulation of event and data communication and facilitates reuse in different contexts.
- **Prioritization of the last active input**: Unlike a simple state machine that only reacts to rising edges, this system considers the last valid signal sent.
- **Secure Interlock**: The ECC structure prevents both outputs from becoming `TRUE` simultaneously.
- **Explicit Stop Intermediate States**: The states `UP_STOP` and `DOWN_STOP` ensure a defined response to the disappearance of a control signal before returning to the idle state.

## State Overview

| State | UP_OUT.D1 | DOWN_OUT.D1 | Description |
|---------|-----------|-------------|--------------|
| `STOP` | FALSE | FALSE | Idle state, no direction active |
| `UP` | TRUE | FALSE | Forward/Upward Direction Active |
| DOWN` | FALSE | TRUE | Backward/Downward Direction Active |
| UP_STOP` | FALSE | FALSE | Intermediate State After Exiting UP |
| DOWN_STOP` | FALSE | FALSE | Intermediate State After Exiting DOWN |

## Application Scenarios

- **Control of lifting/lowering drives** (e.g., hoists, hydraulic cylinders) – prevents simultaneous lifting and lowering.
- **Interlocking of switches** in conveyor systems – prioritizes the most recent request.
- **Safety-oriented switching** in modular automation systems using an adapter-based data model (e.g., logiBUS).

## Comparison with similar function blocks

- **ILOCK_SWITCH** (without adapter): Offers similar interlock logic but uses direct event and data ports. The adapter version `ILOCK_SWITCH_AX` allows for easier coupling to standardized interfaces and is better suited for hierarchical architectures.
- **SR-Flipflop** (Set-Reset): Can also lock two states, but always prioritizes the set or reset input (depending on the implementation) and not the last active one.

## Conclusion

The function block `ILOCK_SWITCH_AX` offers robust, adapter-based interlocking for bidirectional controllers. Due to the state automation, only one direction is active at a time, with priority assigned to the last received command. The clean separation of event and data channels, as well as the defined stop states, make it a reliable component in safety-critical applications.
