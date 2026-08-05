# Q_ObjEnableDisable_AX
![Q_ObjEnableDisable_AX](./Q_ObjEnableDisable_AX.svg)
* * * * * * * * * *
## Introduction
The function block **Q_ObjEnableDisable_AX** is a composite function block that serves as an adapter wrapper for the internal function block `Q_ObjEnableDisable`. It enables the control of an enable/disable command (BOOL) via a unidirectional AX adapter (socket) and returns the previous state via an AB adapter (plug). This function block is typically used in ISOBUS-based control systems.
## Interface Structure
### **Event Inputs**

| Event | Type | Comment |

|----------|-----|-----------|

| `INIT` | EInit | Initialization of the function block; the object ID (u16ObjId) is passed. |

### **Event Outputs**

| Event | Type | Comment |

|----------|-----|-----------|

| `INITO` | EInit | Confirmation of successful initialization. |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| `u16ObjId` | UINT | Object ID set during the INIT event. |

### **Data Outputs**

No direct data outputs; the previous state is output via the adapter plug `qOldAbility`.

### **Adapter**

| Name | Type | Direction | Comment |

|------|-----|----------|-----------|

| `qAbility` | `adapter::types::unidirectional::AX` | Socket | Receives the Enable/Disable command (0 = disable, 1 = enable, 0xFF = undefined). |

| `qOldAbility` | `adapter::types::unidirectional::AB` | Plug | Returns the object's previous state (same encoding). |

## Functionality

1. **Initialization**

An INIT event at input `INIT` sets the desired object ID (`u16ObjId`) and initializes the internal block `Q_ObjEnableDisable`. After successful initialization, the event `INITO` is output.

2. **Signal Processing**

- A new command is received via the socket adapter `qAbility`:
- The adapter's event `E1` triggers the REQ input of the internal block.
- The data `D1` (0/1/0xFF) is forwarded to the input `qAbility` of the internal block.
- The internal block processes the command, activates or deactivates the object with the given ID, and outputs the previous state.
- The acknowledgment `CNF` of the internal block is transferred to the event `E1` of the plug adapter `qOldAbility`.
- The previous state is provided via the data output `D1` of the plug adapter.

3. **Output of Previous State**

The adapter plug `qOldAbility` provides the state before the last change as a BOOL value (0/1/0xFF). The event connection ensures that the output event occurs at the correct time.

## Technical Features
- This function block encapsulates the logic of the more complex `Q_ObjEnableDisable` and offers a simplified interface via two standardized adapters (AX/AB).
- Adapter socket `qAbility` expects unidirectional communication (value transfer only), while adapter plug `qOldAbility` returns the result.
- The object ID is set only during INIT; changing the ID during operation is not supported.

## State Overview
The FB `Q_ObjEnableDisable_AX` itself does not have its own state machine. The internal state logic is implemented by the included function block `Q_ObjEnableDisable`. Its typical states are:

- **IDLE** – Waiting for a command (REQ).
- **Processing** – Processing the command (e.g., sending a CAN message).
- **Done** – Command completed, output of the previous state, and return to IDLE.

## Application Scenarios
- **ISOBUS Control**: Enabling/disabling an agricultural device (e.g., valve, lighting) based on a Boolean signal from an AX adapter.
- **Universal Adapter**: Integrating enable/disable functions into systems that use standardized unidirectional adapters.
- **State Feedback**: Capturing the previous state for diagnostic or monitoring purposes.

## Comparison with Similar Function Blocks

| Function Block | Interface | Special Feature |

|----------|----------------|--------------|

| **Q_ObjEnableDisable** | Direct event/data inputs | Requires separate Boolean inputs and events. |

| **Q_ObjEnableDisable_AX** | AX/AB Adapter | Easy integration into adapter-based architectures; reduces wiring effort.

The AX wrapper does not add new functionality but optimizes the connection to existing adapter communication.

## Conclusion
The **Q_ObjEnableDisable_AX** function block is a practical adapter wrapper that simplifies the control of an ISOBUS object using enable/disable commands via a unidirectional AX adapter. It encapsulates the internal logic, enables clean interface separation, and returns the previous state via an AB adapter. This function block is particularly suitable for modular control architectures based on standardized adapter types.