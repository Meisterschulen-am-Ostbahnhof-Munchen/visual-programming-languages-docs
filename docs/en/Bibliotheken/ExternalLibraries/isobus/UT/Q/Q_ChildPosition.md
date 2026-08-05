# Q_ChildPosition
![Q_ChildPosition](https://user-images.githubusercontent.com/116869307/214147176-8b27f37a-4898-406a-98a0-e5f5701abc58.png)
* * * * * * * * * *
## Introduction
The **Q_ChildPosition** is a standards-compliant function block for the absolute position change of child objects in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.16) specification for agricultural tax systems.
![Q_ChildPosition](Q_ChildPosition.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization request (with object and parent ID)
- `REQ`: Position change request (with absolute coordinates)

### **Event Outputs**
- `INITO`: Initialization confirmation
- `CNF`: Change confirmation (with result data)

### **Data Inputs**
- `u16ObjId` (UINT): Child object ID
- `u16ObjIdParent` (UINT): Parent object ID
- `s16Xposition` (INT): Absolute X-position relative to the parent
- `s16Yposition` (INT): Absolute Y-position relative to the parent

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `s16OldXposition` (INT): Previous X-position
- `s16OldYposition` (INT): Previous Y-position
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with child and parent object IDs
- `INITO` confirms operational readiness

2. **Position Change**:

- `REQ` with absolute coordinates relative to the parent
- Value range: -32768 to +32767 pixels
- `CNF` returns the result and the previous position

3. **Error Handling**:

- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.16)
✔ **Absolute position change** (relative to the parent)
✔ **16-bit value range** (±32768 pixels)
✔ **Real-time processing**

## Position Range

| Parameter | Range | Description |

|-----------|----------------|----------------------------|

| X-Position| -32768 - +32767| Horizontal Position |

| Y-Position| -32768 - +32767| Vertical Position |

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Success |

| -6 | VT_E_OVERFLOW | Position outside the valid range |

| -128 | VT_E_HANDLE_INVALID | Invalid object ID |

## Application Scenarios
- **Precise Object Placement**: Exact positioning of UI elements
- **Dynamic Layouts**: Reorientation of controls
- **Complex Arrangements**: Multi-layered interfaces
- **Machine Visualization**: Technical drawings

## ⚖️ Comparison with Similar Function Blocks

| Feature | Q_ChildPosition | Q_ChildLocation | VtAbsoluteMove |

|---------------|-----------------|-----------------|----------------|

| ISO Standard | ✔ | ✔ | ✖ |

| Position Type | Absolute | Relative | Absolute |

| Value Range | ±32767 pixels | ±127 pixels | ±32767 pixels |

## Conclusion

The Q_ChildPosition block provides the reference implementation for absolute position changes:

- **Precise**: Pixel-accurate positioning
- **Flexible**: Large value range
- **Standard-compliant**: Full ISO 11783-6 compatibility

Ideal for use in:

- Complex user interfaces
- Technical drawings
- Precise layout requirements