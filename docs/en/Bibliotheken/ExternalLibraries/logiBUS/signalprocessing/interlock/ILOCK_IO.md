# ILOCK_IO
![ILOCK_IO](./ILOCK_IO.svg)

* * * * * * * * * *
## Introduction
The function block **ILOCK_IO** implements a cascadable, momentary (non-resettable) interlock with a BOOL interface. It is used to ensure that, in a chain of multiple function blocks, only one block sets its output to TRUE at a time, as long as its input is active and no other block in the chain is already active. This function block is particularly suitable for controllers where competing requirements must be handled exclusively.
## Interface Structure

### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| REQ | Event | Execution Request (triggers the processing of the IN input) |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| CNF | Event | Execution Confirmation (signals that the output OUT has been updated) |

### **Data Inputs**

| Variable | Data Type | Comment |
|----------|----------|-----------|
| IN | BOOL | Input Value (Set Request) |

### **Data Outputs**

| Variable | Data Type | Comment |
|----------|----------|-----------|
| OUT | BOOL | Output Value (Enabled/Disabled) |

### **Adapters**

| Label | Type | Direction | Description |
|-------------|------------------------------|----------|-------------|
| ILOCK_IN | adapter::types::bidirectional::AX2 | Socket | Input adapter for receiving locking information from the chain (from the predecessor) |
| ILOCK_OUT | adapter::types::bidirectional::AX2 | Plug | Output adapter for sending locking information to the chain (to the successor) |

The adapters of type `AX2` are bidirectional and contain the data points `DI1` (Data Input 1) and `DO1` (Data Output 1). In the chain, `ILOCK_OUT.DO1` and `ILOCK_IN.DI1`, as well as `ILOCK_OUT.DI1` and `ILOCK_IN.DO1`, are connected in pairs to implement the interlock logic.

## Functionality

The function block operates as a **momentary latch with interlock**. The following algorithm is executed each time the event `REQ` is called:

1. The output `OUT` is set to TRUE if the input `IN` is TRUE **and** no other function block in the chain is active. The activity of other blocks is queried via the adapters:

- `ILOCK_IN.DO1`: Signal from the predecessor (whether it is active)
- `ILOCK_OUT.DI1`: Signal from the successor (whether it is active)
- Logic: `OUT := IN AND NOT (ILOCK_IN.DO1 OR ILOCK_OUT.DI1)`

2. Subsequently, the current state is propagated to its neighbors via the adapters:

- `ILOCK_IN.DI1 := OUT` – writes the state back to the predecessor
- `ILOCK_OUT.DO1 := OUT` – writes the state to the successor

The chain is structured so that only one block can be active at a time. If `IN` goes to FALSE, `OUT` immediately goes to FALSE, and the interlock is released.

## Technical Features
- **Cascading**: Any number of `ILOCK_IO` blocks can be connected in series using the bidirectional adapters. Each block checks whether its predecessor or successor is already active before it becomes active itself.
- **Instantaneous Behavior**: The output is only TRUE as long as the input is active. There is no memory function – the block is not a flip-flop.
- **Exclusive Release**: Even with multiple simultaneous set requests, only one block can be activated. The priority is determined by the order of the `REQ` events (the one processed first blocks the others).

## State Overview

The block has a single **algorithmic state** `REQ`. Each time `REQ` is called, the algorithm is executed, and the system immediately transitions back to the same state. There is no state storage – the logic is purely combinatorial with feedback via the adapters.

| State | Action | Output |
|---------|--------|---------|
| REQ | Execute algorithm `REQ` | `CNF` is sent after calculation |

## Application Scenarios
- **Traffic light control with multiple request buttons**: Each button is connected to a `ILOCK_IO`; only the first button pressed receives the enable signal.
- **Exclusive machine control**: Multiple control panels compete for control of a machine – only the active panel receives the authorization.
- **Safety Interlock**: In a conveyor system, several safety doors block each other; only one door can be open at a time.

## Comparison with Similar Components
- **SR Flip-Flop (`SR`)** – stores a state, `ILOCK_IO` does not store (instantaneously).
- **Monostable Flip-Flop (`RTRIG`, `FTRIG`)** – reacts only to edges, `ILOCK_IO` operates on a level-controlled basis.
- **Simple `AND` Gate Component** – only local logic, no networking with other components. `ILOCK_IO` offers this networking via adapters.

## Conclusion

The `ILOCK_IO` function block is a specialized block for implementing exclusive release chains. Its simple interface and cascadability make it ideal for modular controllers where multiple competing requirements need to be managed. The bidirectional adapters enable flexible and expandable wiring.
