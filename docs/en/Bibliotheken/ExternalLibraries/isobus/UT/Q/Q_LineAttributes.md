# Q_LineAttributes

![Q_LineAttributes](https://user-images.githubusercontent.com/116869307/214147948-3b9f6d08-00a5-43c0-895b-f2a997773b97.png)

* * * * * * * * * *
## Introduction

The **Q_LineAttributes** is a standards-compliant function module for modifying line attributes in Virtual Terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.30) specification for VT systems.
![Q_LineAttributes](Q_LineAttributes.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization request (with object ID)
- `REQ`: Attribute change request (with new line attributes)

### **Event Outputs**

- `INITO`: Initialization confirmation
- `CNF`: Change confirmation (with status and old attributes)

### **Data Inputs**

- `u16ObjId` (UINT): Object ID (16-bit)
- `u8LineColour` (USINT): New line color
- `u8LineWidth` (USINT): New line width
- `u16LineArt` (UINT): New line style

### **Data Outputs**

- `STATUS` (STRING): Operational status message
- `u8OldLineColour` (USINT): Old line color
- `u8OldLineWidth` (USINT): Old line width
- `u16OldLineArt` (UINT): Old line style
- `s16result` (INT): ISO-compliant result code

## Valid Object IDs

`u16ObjId` addresses the target object of the **F.30** command (Change Line Attributes). Valid is a **Line Attributes object**:

**LineAttributesObject:** 24000–24999

ID_NULL (65535) is not a valid command target but deactivates the FB when used with `INIT`.

## Functionality

1. **Initialization**:
- `INIT` with object ID
- `INITO` confirms operational readiness
2. **Attribute Change**:
- `REQ` with new line attributes
- Changes Object Line Properties
- `CNF` provides result status and previous values
3. **Error Handling**:
- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.30)

✔ **Comprehensive line control** (color, width, style)

✔ **Feedback of previous values** for reversal options
✔ **Transaction-safe** (Atomic execution)

## Attribute Reference

| Attribute | Value range | Description |
|--------------|-----------------------|----------------------------------|
| Color | 0-255 (8-bit) | Color index according to ISO 11783-6 A.3 |
| Width | 1-255 pixels | Line thickness in pixels |
| Style | 16-bit Bitmask | Line type according to B.14.3 |

## Return Codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Successful change |
| -6 | VT_E_OVERFLOW | Buffer overflow |
| -8 | VT_E_NOACT | VT not ready |
| -21 | VT_E_NO_INSTANCE | No VT client available |
| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |
| -130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios

- **Graphic Design**: Dynamic Line Adjustments
- **Diagrams**: Highlighting Important Elements
- **User Guidance**: Visual Markers
- **Machine Visualization**: Status Indicators

## ⚖️ Comparison with Similar Building Blocks

| Feature | Q_LineAttributes | VtLineStyle | VtGraphicAttributes |
|---------------|------------------|-------------|---------------------|
| ISO Standard | ✔ | ✖ | ✖ |
| Color Control | ✔ | ✔ | ✔ |
| Width Control | ✔ | ✔ | ✖ |
| Style Control | ✔ | ✔ | ✔ |

## Conclusion

The Q_LineAttributes block offers precise control over line attributes:

- **Flexible**: Complete design freedom
- **Reliable**: ISO-compliant implementation
- **Traceable**: Previous state storage

Essential for:

- Technical drawings
- Process visualizations
- Interactive graphics applications
