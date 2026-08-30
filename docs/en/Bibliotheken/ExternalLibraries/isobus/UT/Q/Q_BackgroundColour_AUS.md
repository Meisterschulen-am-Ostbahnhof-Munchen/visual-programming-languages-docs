# Q_BackgroundColour_AUS

![Q_BackgroundColour_AUS](./Q_BackgroundColour_AUS.svg)

* * * * * * * * * *
## Introduction

The function block **Q_BackgroundColour_AUS** is used to change the background color of an object in the ISOBUS Virtual Terminal (VT). It encapsulates the corresponding command interface according to ISO 11783-6 (Part 6 – F.20).
The block is supplied with the new color via a socket and returns the previous color via a plug. The actual color change is performed by the internal block `Q_BackgroundColour`.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Variables |
|--------|-------|------------------------------------|---------------------|
| `INIT` | EInit | Service Initialization | `u16ObjId` |

### **Event Outputs**

| Name | Type | Comment | With Variables |
|---------|-------|----------------------------------------|-----------------------------|
| `INITO` | EInit | Initialization Acknowledgement | – |
| `CNF` | Event | Acknowledgement of Requested Service | `STATUS`, `s16result` |

### **Data Inputs**

| Name | Data Type | Initial Value | Comment |
|--------------|----------|-----------------|------------------------------------|
| `u16ObjId` | UINT | `ID_NULL` | Object ID of the object to be modified |

### **Data Outputs**

| Name | Data Type | Comment |
|-------------|----------|---------------------------------------------------------|
| `STATUS` | STRING | Service status (e.g., error message or "OK") |
| `s16result` | INT | Return value (see description – error codes) |

### **Adapter**

- **Socket** `u8Colour`

Type: `adapter::types::unidirectional::AUS`

Returns the new background color (according to ISO 11783-6, A.3 VT standard color palette).

The adapter provides both the event `E1` (to trigger the color change) and the data value `D1` (color value).

- **Plug** `u8OldColour`


Returns the previous background color after the change command has been executed.

The event `E1` signals that the value is valid; the data value `D1` contains the old color.

## Valid Object IDs

`u16ObjId` is valid for the same object types as the wrapped base block `Q_BackgroundColour` (Annex F.20, objects with background colour attribute): WorkingSet (0), Data Mask (1000–1999), Alarm Mask (2000–2999), Soft Key Mask (4000–4999), Key (5000–5999), Button (6000–6999), Input Boolean Field (7000–7999), Input String Field (8000–8999), Input Number Field (9000–9999), Output String Field (11000–11999), Output Number Field (12000–12999), Window Mask (34000–34999), Graphics Context (36000–36999), Auxiliary Function (29000–29999), Auxiliary Function Type2 (31000–31999), Auxiliary Input Type2 (32000–32999).

ID_NULL (65535) is not a command target but deactivates the FB when used with `INIT`.

## Functionality

1. **Initialization**

An event `INIT` starts the function block. The passed object ID (`u16ObjId`) is forwarded to the internal function block `Q_BackgroundColour` and initialized there. After successful initialization, `INITO` is output.

2. **Triggering a Color Change**

As soon as an event arrives at socket `u8Colour` (via the adapter path `E1`), the internal function block is triggered with `REQ`. The color value (`u8Colour.D1`) is passed to `Q_BackgroundColour.u8Colour`.

3. **Feedback**

After the command is completed, the internal module sends a `CNF` event.

- The outputs `STATUS` and `s16result` are set accordingly and are valid at the event output `CNF`.
- Simultaneously, the previous color value (data `D1`) and an acknowledgment event (`E1`) are output via the plug `u8OldColour`.
*
## Technical Features

- The module implements the "Change Background Colour" command according to ISO 11783-6, section F.20.
- The color values correspond to the VT standard color palette from Annex A.3 of the standard.

- Possible return values (`s16result`) are:

- `VT_E_NO_ERR (0)` – Success
- `VT_E_OVERFLOW (-6)` – Buffer overflow
- `VT_E_NOACT (-8)` – Command not possible in the current state
- `VT_E_NO_INSTANCE (-21)` – No VT client available
- `VT_E_ISO_INSTANCE_INVALID (-129)` – Invalid connection identifier
- `VT_E_HANDLE_INVALID (-128)` – Invalid handle
- `VT_E_NOT_ALIVE (-130)` – VT not reachable
- The function block uses a unidirectional adapter (`AUS`) that combines the event and data channels – this reduces the number of interfaces.

## State Overview

The function block (FB) does not have an explicit state machine at the top level, but the interaction with `INIT`, `REQ` (via adapter), and `CNF` results in the following implicit states:

1. **IDLE** – Waiting for `INIT` or for an event on socket `u8Colour`.
2. **INIT** – After `INIT`, the internal block is initialized.
3. **READY** – After `INITO`, the FB is ready to receive color changes.
4. **BUSY** – During the execution of the color change command (after `REQ`). 5. **DONE** – After `CNF`, the next command can be processed.

## Application Scenarios

- **ISOBUS Virtual Terminal**

Changing the background color of a graphical object (e.g., button, group, softkey) on the VT screen in an agricultural control system.

- **HMI Customization**

Responding to user input or system states to dynamically adjust the visual display (e.g., alarm colors, highlighting active elements).

- **Recovering the Previous Color**

The `u8OldColour` plugin allows you to save the previous color value or use it for later restoration.

*
## Comparison with Similar Function Blocks

- **`Q_BackgroundColour`** (without `_AUS`):

Offers the same core functionality, but usually with individual event/data ports instead of encapsulated adapters. The `_AUS` function block simplifies the connection to other function blocks that also use AUS adapters.

- **`Q_Colour`** or **`Q_ForegroundColour`**:

Modify different color properties (foreground, full color) and use similar return values and status mechanisms.

- **`Command_ChangeColour`** (more general):

Could modify multiple color parameters simultaneously, while `Q_BackgroundColour_AUS` specializes in background colors.

## Conclusion

The `Q_BackgroundColour_AUS` function block offers a standards-compliant, compact interface for changing background colors in an ISOBUS VT. The use of the unidirectional adapter simplifies integration with other components and improves clarity. The documented error codes and the clear separation of initialization and service execution make it a reliable building block for dynamic HMI adjustments in agricultural control systems.
