# Q_ObjEnableDisable_AB

![Q_ObjEnableDisable_AB](./Q_ObjEnableDisable_AB.svg)

* * * * * * * * * *

## Introduction

The function block `Q_ObjEnableDisable_AB` serves as a wrapper that enables the control of a binary object (switching on/off) via a unidirectional **AB adapter (BYTE)**. It encapsulates the logic of the block `isobus::UT::Q::Q_ObjEnableDisable` and provides its functionality via the standardized adapter interfaces `qAbility` (socket) and `qOldAbility` (plug). The function block is suitable for connecting to adapter-based systems, e.g., for the remote control of actuators.

## Interface Structure

### **Event Inputs**

| Event | Type | Description |
|----------|-------|-------------|
| `INIT` | EInit | Service initialization: starts the internal function block and passes the object ID. |

### **Event Outputs**

| Event | Type | Description |
|----------|-------|-------------|
| `INITO` | EInit | Confirmation of successful initialization. |

### **Data Inputs**

| Name | Type | Description |
|------------|------|-------------------------------|
| `u16ObjId` | UINT | Unique identifier of the object to be controlled. |

### **Data Outputs**

No dedicated data outputs – output data is provided via the adapter plug.

### **Adapter**

| Adapter Type | Direction | Description |
| -------------------------------------- | ------------- | ------------- |
| **Socket** `qAbility` | Input | Unidirectional AB adapter: receives the command (BYTE). `0` = disable, `1` = enable, `0xFF` = undefined. |
| **Plug** `qOldAbility` | Output | Unidirectional AB adapter: returns the previous state of the object (same encoding). |

## Valid Object IDs

The validity rules of the internal base function block `Q_ObjEnableDisable` apply:

**`u16ObjId` — valid object types (Annex F.4):**
Button (6000–6999), Input Boolean Field (7000–7999), Input String Field (8000–8999), Input Number Field (9000–9999), Input List Field (10000–10999), Animation Object (44000–44999).

ID_NULL (65535) is not a valid command target but deactivates the FB when used with `INIT`.

## Functionality

The FB acts as a bridge between an AB adapter (BYTE) and the internal function block `Q_ObjEnableDisable`. The processes are as follows:

1. **Initialization**

An INIT event with a valid object ID (`u16ObjId`) is forwarded to the internal FB. The internal FB is initialized and reports this via `INITO`.

1. **Control**

A BYTE value is received via socket `qAbility`. The event `qAbility.E1` triggers the internal FB (event `REQ`). The data value from `qAbility.D1` is passed to the internal function block (FB).

The internal FB processes the command and sets the object's state accordingly. The previous state is passed via the internal connection to the plug `qOldAbility`. The event `CNF` of the internal FB is output as `qOldAbility.E1`.

1. **Feedback**

The plug `qOldAbility` provides the object's previous state (BYTE) and the associated event, allowing a downstream function block to react to state changes.

## Technical Features

- **Adapter-Based Encapsulation**

The FB uses the standardized unidirectional AB adapter, which allows for easy integration into existing adapter networks.

- **Typical BYTE Encoding**

0` → disable, `1` → enable, `0xFF` → undefined (error or no change). This convention is used for both input and output.

- **Initialization with Object ID Only**

The INIT event must be triggered with a valid `u16ObjId`. The function block itself does not store any persistent configuration.

- **Event-Driven Processing**

Control is exclusively via the events of the adapter socket. No state change occurs without an event on `qAbility.E1`.

## State Overview

The function block does not have its own explicit state machine – the state logic resides entirely within the internal function block `Q_ObjEnableDisable`. Nevertheless, the following operating states can be derived:

| State | Description |
| ----------------- | ------------- |
| **Idle** | After successful initialization (INITO sent), the function block (FB) waits for an event at socket `qAbility`. |
| **Processing** | An incoming event at `qAbility.E1` is processed; the internal FB executes the switchover. |
| **Completed** | Processing complete – the new (or old) state is available at the plug, and event `qOldAbility.E1` is output. |

Error states (e.g., invalid object ID, faulty INIT sequence) are handled by the internal FB and can be signaled via return values or special BYTE codes (`0xFF`).

## Application Scenarios

- **Remote Control of a Binary Output**

A higher-level control block sends the command "On" or "Off" via an AB adapter. The FB executes the command and reports back the previous state.

- **State Query Without Change**

By sending the code `0xFF`, the current state can be queried without making any changes.

- **Integration into Adapter-Based Service Interfaces**

The FB serves as a converter between an AB adapter (e.g., from an HMI or remote control) and a functional block that requires a native ISOBUS interface.

## Comparison with Similar Blocks

| Block | Difference |
| ---------- | ------------ |
| `Q_ObjEnableDisable` (direct) | Requires native event and data interfaces without adapters. `Q_ObjEnableDisable_AB` adds adapter compatibility. |
| `Q_ObjEnableDisable_BB` (hypothetical) | Would use a bidirectional BB adapter. This FB uses the simpler unidirectional AB adapter. |
| Generic "CommandOnOff" | Is typically not targeted to a specific object (ID) and does not provide status feedback via adapters. |

## Conclusion

The FB `Q_ObjEnableDisable_AB` is a useful wrapper that makes the functionality of an ISOBUS object switch accessible via the standardized AB adapter. It facilitates integration into modular adapter networks and reduces wiring effort. The simple interface with only one event input for control and feedback via the plug makes it particularly suitable for reusable components in automation technology.
