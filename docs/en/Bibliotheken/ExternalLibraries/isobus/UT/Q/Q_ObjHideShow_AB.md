# Q_ObjHideShow_AB

![Q_ObjHideShow_AB](./Q_ObjHideShow_AB.svg)

* * * * * * * * * *
## Introduction

The function block **Q_ObjHideShow_AB** serves as a wrapper for the function block `Q_ObjHideShow` and enables hiding or showing an object via an **AB adapter** (unidirectional, BYTE). It encapsulates the direct control of the internal function block and provides an adapter-based interface that promotes loose coupling in the application.
## Interface Structure

### **Event Inputs**

| Event | with variables | Comment |
|---|---|---|
| `INIT` | `u16ObjId` | Service Initialization; Object ID is passed |

### **Event Outputs**

| Event | Comment |
|---|---|
| `INITO` | Initialization confirmed |

### **Data Inputs**

| Name | Type | Comment |
|---|---|---|
| `u16ObjId` | UINT | Object ID |

### **Data Outputs**

No explicit data outputs at the FB level. The output data is provided via the adapter `qOldVisible`.

### **Adapters**

| Direction | Name | Type | Comment |
|---|---|---|---|
| Socket (Input) | `qVisible` | `adapter::types::unidirectional::AB` | Target Visibility: 0 = hidden, 1 = displayed |
| Plug (Output) | `qOldVisible` | `adapter::types::unidirectional::AB` | Previous Visibility Value: 0 = hidden, 1 = displayed, 0xFF = undefined |

## Valid Object IDs

The validity rules of the internal base function block `Q_ObjHideShow` apply:

**`u16ObjId` — valid object types (Annex F.2):**
Container (3000–3999).

ID_NULL (65535) is not a valid command target but deactivates the FB when used with `INIT`.

## Functionality

1. **Initialization**

An event at input `INIT` initializes the internal function block `Q_ObjHideShow`. The passed `u16ObjId` identifies the object to be controlled. After successful startup, the event `INITO` is output.

2. **Visibility Control**

As soon as an event (E1) arrives at the socket adapter `qVisible`, the corresponding data value (D1) is read and forwarded to the internal function block (FB). The internal FB then sets the object's visibility accordingly (0 = hidden, 1 = displayed).

3. **Feedback**

After the action is executed, the internal FB sends the event `CNF` to the plug adapter `qOldVisible`. The previous visibility state is provided as a data value (D1) on `qOldVisible`. This allows the calling component to query the previous state.

## Technical Features

- **Wrapper Concept**: The function block (FB) encapsulates the direct use of `Q_ObjHideShow` and replaces the loose event/data connection with standardized AB adapters, enabling a modular and reusable interface.
- **AB Adapter (Unidirectional, BYTE)**: Communication takes place via a unidirectional adapter that transmits only one event and one associated byte at a time. This simplifies integration into adapter-based architectures.
- **State Maintenance**: The internal FB stores the last visibility state; with each new command, the previous state is reported back to the output adapter.
- **Undefined Value (0xFF)**: The output `qOldVisible` can return the value 0xFF if the previous state is unknown (e.g., after a restart without prior initialization).

## State Overview

The FB itself does not have its own state machine. Its behavior is entirely determined by the embedded function block `Q_ObjHideShow`. The following generally applies:

- **After INIT**: The function block is ready for operation and waits for events from the socket adapter `qVisible`.
- **On every incoming socket event**: Visibility is set, and the result is reported back via the plug adapter.

## Application Scenarios

- **Visualization Control**: Showing and hiding graphical objects (e.g., in HMI systems) based on binary or numerical control values.
- **State Feedback**: Monitoring of visibility changes; the previous visibility state can be used for logic decisions or logging.
- **Adapter-Based Automation**: Integration into a system that relies on adapter interfaces to achieve interchangeability and decoupling.

## Comparison with Similar Function Blocks

| Function Block | Properties |
|---|---|
| `Q_ObjHideShow` (direct) | Event/data interface without adapter; direct connection required |
| `Q_ObjHideShow_AB` (this function block) | Uses AB adapters for loose coupling; easier integration into adapter-based networks |
| Other AB-based wrappers | Similar concept for other commands (e.g., `Q_ObjMove_AB`), but specifically designed for visibility |

The main advantage of the wrapper lies in its adaptation to the AB adapter interface without changing the actual functionality.

## Conclusion

The function block `Q_ObjHideShow_AB` represents an adapter-based, reusable component for controlling the visibility of objects. By encapsulating the internal function block and using unidirectional AB adapters, a clean separation of control logic and execution is achieved. It is particularly suitable for modular automation solutions that rely on loose coupling and standardized interfaces.
