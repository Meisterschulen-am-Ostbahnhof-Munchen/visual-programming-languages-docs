# Q_EndPoint

![Q_EndPoint](https://user-images.githubusercontent.com/116869307/214147340-866900ae-dc9c-4cbd-a9e8-c8755d833674.png)

* * * * * * * * * *

## Introduction
The **Q_EndPoint** is a standards-compliant function block for controlling line endpoints in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.26) specification for agricultural tax systems.


![Q_EndPoint](Q_EndPoint.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request (with object ID)
- `REQ`: Endpoint Change Request (with position/direction)

### **Event Outputs**

- `INITO`: Initialization Confirmation
- `CNF`: Change Confirmation (with result data)

### **Data Inputs**

- `u16ObjId` (UINT): Line Object ID

- `u16Width` (UINT): New X End Position (0-65535 pixels)

- `u16Height` (UINT): New Y-End Position (0-65535 pixels)

- `u8LineDirection` (USINT): Line Direction (ISO 11783-6 B.27)

### **Data Outputs**

- `STATUS` (STRING): Operating Status Message

- `u16OldWidth` (UINT): Previous X-End Position
- `u16OldHeight` (UINT): Previous Y-End Position

- `u8OldLineDirection` (USINT): Previous Line Direction
- `s16result` (INT): ISO-compliant Result Code

## Functionality

1. **Initialization**:

- `INIT` with Line Object ID

- `INITO` confirms operational readiness

2. **Endpoint Change**:

- `REQ` with new position and direction parameters

- Changes the endpoint and orientation of the line

- `CNF` returns the result and the old values

3. **Error Handling**:

- ISO-standardized error codes

- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.26 + B.27)

✔ **16-bit position resolution** (0-65535 pixels)
✔ **Full line control** (position + direction)

✔ **Real-time processing**

## Line directions (B.27)

| Value | Direction | Description |

|------|-------------------|-------------------------| | 0 | Horizontal | From left to right |

| 1 | Vertical | From top to bottom |

| 2 | Diagonal right | Top left → Bottom right |

| 3 | Diagonal left | Top right → Bottom left |

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Success |

| -6 | VT_E_OVERFLOW | Invalid position values |

| -128 | VT_E_HANDLE_INVALID | Invalid line object ID |

| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid instance |

## Application Scenarios

- **Machine Visualization**: Dynamic Connecting Lines
- **Diagrams**: Customizable Data Displays
- **Technical Drawings**: Configurable Guidelines
- **UI Design**: Adaptive Dividing Lines

## ⚖️ Comparison with Similar Building Blocks

| Feature | Q_EndPoint | VtLineEditor | VtDynamicLine |

|----------------|---------------|---------------|---------------|

| ISO Standard | ✔ | ✖ | ✖ |

| Control | Endpoint | Full | Position Only |

| Directions | 4 Options | 8 Options | None |


## Conclusion

The Q_EndPoint block provides the reference implementation for line endpoint control:

- **Precise**: Pixel-accurate positioning
- **Flexible**: Combined position and direction control
- **Standard-compliant**: Full ISO 11783-6 compatibility

Ideal for use in:

- Dynamic technical drawings
- Adaptive diagram displays
- Configurable user interfaces