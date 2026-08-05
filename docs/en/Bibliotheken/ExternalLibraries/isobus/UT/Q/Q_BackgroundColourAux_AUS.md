# Q_BackgroundColourAux_AUS

![Q_BackgroundColourAux_AUS](./Q_BackgroundColourAux_AUS.svg)

* * * * * * * * * *
## Introduction

This function block implements the command to change the background color of an object according to ISO 11783-6, Part F.20.

It enables interaction with the Virtual Terminal (VT) and handles the transmission of the new color as well as the feedback of the result.

## Interface Structure

### **Event Inputs**

| Event | Type | With Parameter | Description |

|----------|-------|----------------|--------------|

| INIT | EInit | u16ObjId | Service Initialization |

### **Event Outputs**

| Event | Type | With Parameter | Description |

|----------|--------|----------------|--------------|

| INITO | EInit | – | Initialization confirmed |

| CNF | Event | STATUS, s16result | Confirmation of requested service |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|-----------|-------|-------------|--------------|

| u16ObjId | UINT | ID_NULL | Object ID of the affected object |

### **Data Outputs**

| Name | Type | Description |

|-----------|--------|--------------|

| STATUS | STRING | Service status (e.g., error message) |

| s16result | INT | Return value (see below) |

### **Adapter**

| Direction | Name | Type | Description |

|----------|-------------|------|--------------|

| Socket | u8Colour | OFF | New background color (according to ISO 11783-6 A.3) |

| Plug | u8OldColour | OFF | Old background color (returned by the VT) |

## Functionality

The module first expects initialization with the object ID (`INIT` with `u16ObjId`).

As soon as a new color value is present at the socket adapter `u8Colour` (triggered by the adapter's event `E1`), an internal event `REQ` is sent to the encapsulated function block `Q_BackgroundColourAux`.

This executes the VT command and returns the status (`STATUS`) and the result (`s16result`) via the output `CNF`.

The previous color is output via the plug adapter `u8OldColour`.

All the logic is encapsulated in a subordinate function block of the same family, so this block serves only as an outer shell for the adapter coupling.



This function block executes the VT command and returns the status (`STATUS`) and the result (`s16result`) via the output `CNF`. ## Technical Features

- The initial value for `u16ObjId` is `ID_NULL`, meaning the function block must be initialized with a valid object ID before use.

- Color values are transmitted as 8-bit values via the AUS adapter. The valid colors are defined in the VT standard color palette (ISO 11783-6 Annex A.3).


- The initial value for `u16ObjId` is `ID_NULL`, meaning the function block must be initialized with a valid object ID before use.

- The color values are transmitted as 8-bit values via the AUS adapter. The valid colors are defined in the VT standard color palette (ISO 11783-6 Annex A.3). - Possible return values (`s16result`):

- `VT_E_NO_ERR` (0): Success

- `VT_E_OVERFLOW` (-6): Buffer overflow

- `VT_E_NOACT` (-8): Command not possible in the current state

- `VT_E_NO_INSTANCE` (-21): No VT client available

- `VT_E_ISO_INSTANCE_INVALID` (-129): Invalid connection identifier

- `VT_E_NOT_ALIVE` (-130): VT instance valid, but VT not reachable

## State Overview

The FB does not have explicit state machines in the XML. Event control is handled solely via event connections:

1. **INIT** → Initialization of the service.

2. **External event via socket adapter** → Start of the color change request.

3. **CNF** → Completion of the operation with status and return value.

## Application Scenarios

- Dynamic adjustment of the background color of an ISOBUS VT object (e.g., button, text field) depending on operating states or user input.

- Implementation of color changes in agricultural control and visualization systems.

## Comparison with Similar Function Blocks

Analogous function blocks exist for other visual properties (e.g., `Q_TextColourAux_AUS`, `Q_VisibilityAux_AUS`).

All of them share the schema-based adapter pattern, which implements the signaling of value changes via OFF adapters.

This function block specializes in background color and uses the same error and return values.

## Conclusion

The `Q_BackgroundColourAux_AUS` function block compactly encapsulates an ISOBUS-VT service for background color change and offers easy integration into higher-level controllers via its adapter interfaces.

It is reliable, standards-compliant, and allows for robust error handling through status feedback.