# NOOP
![NOOP](./NOOP.svg)

* * * * * * * * * *
## Introduction
The NOOP function block ("No Operation") serves as a simple pass-through block. It copies the BOOL value present at data input `IN` to data output `OUT` as soon as an event occurs at input `REQ`. The output `CNF` is then triggered. The function block does not perform any logical or arithmetic operation; it simply passes the signal on unchanged.
## Interface Structure
### **Event Inputs**

| Event | Type | Comment |
|----------|-----|-----------|
| `REQ` | Event | Normal Execution Pulse |

### **Event Outputs**

| Event | Type | Comment |
|----------|-----|-----------|
| `CNF` | Event | Execution Acknowledgement |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `IN` | BOOL | Input Signal |

### **Data Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| `OUT`| BOOL | Output signal (identical to `IN`) |

### **Adapter**
None.

## Functionality
Internally, the function block consists of an instance of `F_MOVE` (from the library `iec61131::selection::F_MOVE`), configured with the data type `BOOL`.

- Upon an event on `REQ`, the value of `IN` is passed to `F_MOVE.IN`, triggering execution.
- After successful processing, `F_MOVE.OUT` outputs the value, which is then set to `OUT`. Simultaneously, `F_MOVE.CNF` is triggered, which activates the event output `CNF`.

Thus, the behavior corresponds exactly to a passthrough: `OUT := IN`.

## Technical Features
- The function block uses a pre-built MOVE block internally, so no custom state logic is required.
- The data paths are explicitly designed for `BOOL`. Extending it to other data types would be possible by modifying the `F_MOVE` attribute, but this is not included in the current design.
- No side effects such as delays or state changes beyond pure signal transmission are implemented.
...```
## State Overview
Since the function block does not have its own state machine, the process can be viewed as a simple two-step operation:

1. **Wait** – for an event `REQ`.

2. **Forward** – immediate transfer of `IN` to `OUT` and output of `CNF`.

There are no internal memory states or branches.

## Application Scenarios
- **Debugging and Testing**: Used as a placeholder to test signal paths in a complex network without affecting functionality.
- **Signal Forwarding**: When an event signal needs to be passed through unchanged, e.g., for synchronizing multiple branches.
- **Placeholder for Future Extensions**: In an early development phase, NOOP can be placed at locations that will later require specific processing.
- **Cascading of Events**: Event coupling allows multiple receivers to be served sequentially.

## Comparison with Similar Function Blocks
- **MOVE**: A MOVE function block (like the one used internally) also performs a value assignment. NOOP differs only in name and its explicit documentation as "no operation." Both are functionally almost identical, with the difference that MOVE is often typed for arbitrary data types, while NOOP is statically set to BOOL.
- **BISTABLE (RS / SR)**: These function blocks change their state based on inputs. NOOP does not store a state but only outputs the current input value.
- **CONSTANT**: A constant function block always returns a fixed value. NOOP, on the other hand, reacts to changing inputs and events.

## Conclusion
The NOOP function block is a simple yet useful function block that requires no internal logic. It copies the incoming BOOL value to the output upon each event and confirms execution. Due to its pass-through characteristics, it is ideally suited for testing purposes, as a placeholder or for event-driven signal transmission in IEC 61499 networks.
