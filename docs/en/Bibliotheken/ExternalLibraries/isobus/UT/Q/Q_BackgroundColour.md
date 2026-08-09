# Q_BackgroundColour

![Q_BackgroundColour](https://user-images.githubusercontent.com/113907471/204320542-f628c868-03d7-4d81-9ebb-5cf63d9ce541.png)
![Beispiel](https://user-images.githubusercontent.com/113907471/204320176-773a1f69-281c-4d83-873a-671f1680081a.png)

* * * * * * * * * *
## Introduction

The **Q_BackgroundColour** is a standards-compliant function block for controlling background colors in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.20) specification for agricultural tax systems.

![Q_BackgroundColour](Q_BackgroundColour.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request (with object ID)
- `REQ`: Color Change Request (with color code)

### **Event Outputs**

- `INITO`: Initialization Confirmation
- `CNF`: Change Confirmation (with result data)

### **Data Inputs**

- `u16ObjId` (UINT): Object Identifier
- `u8Colour` (USINT): New Color Value (ISO 11783-6 palette)

### **Data Outputs**

- `STATUS` (STRING): Operating status message
- `u8OldColour` (USINT): Previous color value
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:
- `INIT` with object ID
- `INITO` confirms operational readiness
2. **Color Change**:
- `REQ` triggers with new color code (0-255)
- `CNF` returns result and previous color value
3. **Error Handling**:
- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.20 + A.3 color palette)
✔ **8-bit color support** (256 values)
✔ **Real-time processing**
✔ **State preservation** (u8OldColour)

## Standard color palette (excerpt)

| Code | Color | RGB equivalent |
|------|-------------|----------------|
| 0 | Black | #000000 |
| 1 | Red | #FF0000 |
| 2 | Green | #00FF00 |
| 3 | Yellow | #FFFF00 |
| 4 | Blue | #0000FF |

## Return codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Success |
| -6 | VT_E_OVERFLOW | Buffer Overflow |
-8 | VT_E_NOACT | Invalid State |
-128 | VT_E_HANDLE_INVALID | Invalid Object ID |

## Application Scenarios

- **Machine Status**: Color-coded Alarm Indication
- **Night Mode**: Dark Color Palettes
- **Markings**: Highlighting Objects
- **Branding**: Manufacturer-Specific Colors

## ⚖️ Comparison with Similar Function Blocks

| Feature | Q_BackgroundColour | VtColourManager | VtDynamicStyle |
---------------|-------------------|-----------------|----------------|
| ISO Standard | ✔ | ✖ | ✖ |
| Color Palette | Standard | Extended | User Defined |
| Object Binding | Explicit | Implicit | Stylesheet |

## 🛠️ Related Exercises

* [Exercise_016](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_016.md)]
* [Exercise_016a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_016a.md)]

## Conclusion

The Q_BackgroundColour block provides the reference implementation for ISOBUS color control:

- **Standard-compliant**: Full ISO 11783-6 compatibility
- **Easy integration**: Clear color palette definition
- **Robust**: Proven field reliability

Essential for:

- Color status indicators
- User interface design
- Dynamic visualizations
