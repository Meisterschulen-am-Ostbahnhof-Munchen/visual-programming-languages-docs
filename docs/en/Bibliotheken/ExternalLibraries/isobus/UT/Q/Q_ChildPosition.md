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

## Valid Object IDs

`u16ObjId` (the child object to move) and `u16ObjIdParent` (the parent object) are subject to **different** validity rules. ISO 11783-6 Annex F only defines which object types are valid as the child — which object types may act as parent is defined separately in Annex B, under each object type's "Allowed commands" list.

**`u16ObjId` — valid child object types (Annex F.16):**
Container (3000–3999), Key (5000–5999), Button (6000–6999), Input Boolean Field (7000–7999), Input String Field (8000–8999), Input Number Field (9000–9999), Input List Field (10000–10999), Output String Field (11000–11999), Output Number Field (12000–12999), Output Line (13000–13999), Output Rectangle (14000–14999), Output Ellipse (15000–15999), Output Polygon (16000–16999), Meter (17000–17999), Linear Bar Graph (18000–18999), Arched Bar Graph (19000–19999), Picture Graphic (20000–20499), Object Pointer (27000–27999), Output List Object (37000–37999), External Object Pointer (43000–43999), Animation Object (44000–44999), Scaled Graphic Object (48000–48999), Auxiliary Function/Type2 (29000–29999 / 31000–31999), Auxiliary Input/Type2 (30000–30999 / 32000–32999), Auxiliary Control Designator (33000–33999).

**`u16ObjIdParent` — valid parent object types (Annex B, "Allowed commands"):**
WorkingSet (B.1), Data Mask (B.2), Alarm Mask (B.3), **Container (B.4)**, Key (B.6), Window Mask, Button, Auxiliary Function (Type 1/2), Auxiliary Input (Type 1/2).

**Not valid as parent:** Soft Key Mask (B.5 does not list the command as allowed) and Animation Object (its children are indexed frames, not X/Y-positioned).

ID_NULL (65535) is not a valid command target but deactivates the FB when used with `INIT`.

## Functionality

1. **Initialization**:

- `INIT` with child and parent object IDs
- `INITO` confirms operational readiness
1. **Position Change**:

- `REQ` with absolute coordinates relative to the parent
- Value range: -32768 to +32767 pixels
- `CNF` returns the result and the previous position
1. **Error Handling**:

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
| ------ | ------------------------- | ------------------------------------ |
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
| --------------- | ----------------- | ----------------- | ---------------- |
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
