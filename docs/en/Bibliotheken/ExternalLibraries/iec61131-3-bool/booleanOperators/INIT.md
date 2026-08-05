# INIT
![INIT](./INIT.svg)
* * * * * * * * * *
## Introduction
The **INIT** function block serves as a direct event pass-through. It is designed as the counterpart to a `E_TRIG` function block and is typically used in the initialization phase of a system. The function block has two event inputs and two corresponding event outputs; no data is processed.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|-------|--------|------------------------------|

| INIT | EInit | Initialization Request |

| REQ | Event | Service Request |

### **Event Outputs**

| Name | Type | Comment |

|-------|--------|-------------------------------|

| INITO | EInit | Initialization Acknowledgement |

| CNF | Event | Request Acknowledgement |

### **Data Inputs**
None.

### **Data Outputs**
None.

### **Adapters**
None.

## Functionality
The function block operates in an event-driven manner and does not perform any logic or state changes of its own. Every incoming event is forwarded to the corresponding output without delay or processing:

- An event at input `INIT` immediately generates an event at output `INITO`.
- An event at input `REQ` immediately generates an event at output `CNF`.

This behavior is achieved through a simple connection of the event paths within the internal function block network. No value changes or state storage occur.

## Technical Features
- **Direct Pass-Through**: The function block is extremely lightweight and requires no internal variables or time delays.
- **Event Types**: The input and output events `INIT`/`INITO` are typed as `EInit`, while `REQ`/`CNF` are declared as the default `Event`. This allows for a clear semantic separation between initialization and operational events.
- **License**: The function block is licensed under the Eclipse Public License 2.0 (EPL-2.0).

## State Overview

The function block has **no internal states**. It is a pure pass-through block that reacts to incoming events at any time without changing state. Therefore, a state machine is not required.

## Application Scenarios
- **Placeholder in Design Phases**: If a `E_TRIG` block is later to be replaced by more complex logic, `INIT` can temporarily serve as a simple pass-through block.
- **Initialization Cascades**: In architectures that perform multiple initialization steps, `INIT` blocks can be used to pass events to subsequent blocks without processing them.
- **Prototyping and Testing**: For bridging unused initialization logic or for debugging event flows.

## Comparison with Similar Function Blocks
- **E_TRIG (Input Trigger)**: `E_TRIG` generates an output event only on a rising or falling edge of a connected Boolean input. `INIT`, on the other hand, reacts directly to an event and does not require a data value.
- **E_PERMIT (Enable)**: `E_PERMIT` allows events to pass only if a Boolean enable input is set. `INIT` has no such condition.
- **E_DELAY (Delay)**: `E_DELAY` delays events for a specific period of time. `INIT` operates without delay.

## Conclusion

The `INIT` function block is a minimalist yet useful building block for direct event forwarding. Due to its simplicity, it is particularly suitable for design phases, initialization processes, and as a temporary placeholder. It fulfills the basic requirement of passing on initialization and service events unchanged and can be replaced by more functionally richer building blocks if needed.