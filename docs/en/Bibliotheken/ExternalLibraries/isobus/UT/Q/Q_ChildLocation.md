# Q_ChildLocation

![Q_ChildLocation](https://user-images.githubusercontent.com/116869307/214147140-820ec964-b57a-499c-9e0d-1811b56a585c.png)

* * * * * * * * * *

## Introduction
The **Q_ChildLocation** is a standards-compliant function block for changing the position of child objects in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.14) specification for agricultural tax systems.


![Q_ChildLocation](Q_ChildLocation.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request (with object and parent ID)
- `REQ`: Position Change Request (with relative coordinates)

### **Event Outputs**

- `INITO`: Initialization Acknowledgement
- `CNF`: Change Acknowledgement (with result data)

### **Data Inputs**

- `u16ObjId` (UINT): Child Object ID

- `u16ObjIdParent` (UINT): Parent Object ID

- `u8Xchange` (USINT): Relative X-Position Change (-128 to +127)

- `u8Ychange` (USINT): Relative Y-position change (-128 to +127)

### **Data Outputs**

- `STATUS` (STRING): Operational status message

- `u8OldXchange` (USINT): Previous X-change
- `u8OldYchange` (USINT): Previous Y-change
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with child and parent object IDs

- `INITO` confirms operational readiness

2. **Position Change**:

- `REQ` with relative coordinate changes

- Values are interpreted as signed 8-bit

- `CNF` returns the result and previous values

3. **Error Handling**:

- ISO-standardized error codes

- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.14)
✔ **Relative position change** (relative to the parent)
✔ **Signed 8-bit values** (-128 to +127)
✔ **Real-time processing**

## Position Change Range

| Parameter | Range | Description |

|-----------|------------|----------------------------|

| X Change| -128 - +127| Horizontal Displacement |

| Y-Change | -128 - +127 | Vertical Shift |

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Success |

| -6 | VT_E_OVERFLOW | Invalid Position Values |

| -128 | VT_E_HANDLE_INVALID | Invalid Object ID |

## Application Scenarios

- **Dynamic Layouts**: Object Positioning

- **Animated Elements**: Smooth Movements

- **Responsive Designs**: Adaptation to Different Screen Sizes

- **Grouped Objects**: Shared Movements

## ⚖️ Comparison with Similar Building Blocks

| Feature | Q_ChildLocation | VtAbsolutePosition | VtGroupMove |

|---------------|-----------------|--------------------|-------------|

| ISO Standard | ✔ | ✖ | ✖ |

| Movement | Relative | Absolute | Groups |

| Value Range | ±127 pixels | 0-65535 pixels | ±127 pixels |

## Conclusion

The Q_ChildLocation block provides the reference implementation for relative position changes:

- **Flexible**: Simple relative positioning
- **Precise**: Pixel-accurate control
- **Standard-compliant**: Full ISO 11783-6 compatibility

Ideal for use with:

- Dynamic surfaces
- Animated transitions
- Parent-child object relationships