# Q_BackgroundColourAux

* * * * * * * * * *

## Introduction

The **Q_BackgroundColourAux** is a standards-compliant function block for controlling secondary background colors in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.20) specification for auxiliary colors in agricultural tax systems.
![Q_BackgroundColourAux](Q_BackgroundColourAux.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request (with object ID)
- `REQ`: Color Change Request (with color code)

### **Event Outputs**

- `INITO`: Initialization Confirmation
- `CNF`: Change Confirmation (with result data)

### **Data Inputs**

- `u16ObjId` (UINT): Object Identifier
- `u8Colour` (USINT): New Auxiliary Color Value (ISO 11783-6 palette)

### **Data Outputs**

- `STATUS` (STRING): Operational status message
- `u8OldColour` (USINT): Previous auxiliary color value
- `s16result` (INT): ISO-compliant result code

## Valid Object IDs

**`u16ObjId` — valid object types (Annex F.20, objects with background colour attribute):**
WorkingSet (0), Data Mask (1000–1999), Alarm Mask (2000–2999), Soft Key Mask (4000–4999), Key (5000–5999), Button (6000–6999), Input Boolean Field (7000–7999), Input String Field (8000–8999), Input Number Field (9000–9999), Output String Field (11000–11999), Output Number Field (12000–12999), Window Mask (34000–34999), Graphics Context (36000–36999), Auxiliary Function (29000–29999), Auxiliary Function Type2 (31000–31999), Auxiliary Input Type2 (32000–32999).

ID_NULL (65535) is not a command target but deactivates the FB when used with `INIT`. Any ID outside these ranges is invalid for commanding.

## Functionality

1. **Initialization**:

- `INIT` with object ID for auxiliary element
- `INITO` confirms operational readiness
1. **Color Change**:

- `REQ` triggers with new auxiliary color code (0-255)
- `CNF` returns result and previous color value
1. **Error Handling**:

- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.20 (for auxiliary colors)

✔ **8-bit color support** (256 values)

✔ **Compatible with Q_BackgroundColour**

✔ **State preservation** (u8OldColour)

## Standard auxiliary colors (excerpt)

| Code | Scope | Typical color |
| ------ | ------------------------ | ----------------- |
| 16 | Status bar | Blue |
| 32 | Secondary areas | Gray |
| 48 | Guidelines | Light blue |

## Return codes (s16result)

| Code | Constant | Meaning |
| ------ | ------------------------- | ------------------------------------ |
| 0 | VT_E_NO_ERR | Success |
| -128 | VT_E_HANDLE_INVALID | Invalid object ID |
| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid instance |

## Application Scenarios

- **Status Indicators**: Secondary colors for bars
- **Groupings**: Color separation of areas
- **Editor Modes**: Guidelines in configurators
- **Diagnostics**: Additional information

## ⚖️ Comparison with similar building blocks

| Feature | Q_BackgroundColourAux | Q_BackgroundColour | VtAuxColour |
| --------------- | ----------------------- | -------------------- | ------------- |
| ISO Standard | ✔ | ✔ | ✖ |
| Color range | Auxiliary elements | Primary elements | All |
| Usage | Secondary | Primary | Universal |

## Conclusion

The Q_BackgroundColourAux module extends ISOBUS color control for auxiliary elements:

- **Specialized**: Optimized for secondary display elements
- **Consistent**: Same API as Q_BackgroundColour
- **Proven in practice**: Used in modern tractor displays

Ideal for:

- Complex display layouts
- Multi-layered visualizations
- Systems with advanced color management
