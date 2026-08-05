# Q_FillAttributes
![Q_FillAttributes](https://user-images.githubusercontent.com/116869307/214147532-6ef11045-1dcb-4c4d-bdf3-84d87ed73257.png)

* * * * * * * * * *
## Introduction
The **Q_FillAttributes** is a standards-compliant function module for modifying fill attributes in Virtual Terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.32) specification for VT systems.
![Q_FillAttributes](Q_FillAttributes.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization request (with object ID)
- `REQ`: Attribute change request (with new fill attributes)

### **Event Outputs**
- `INITO`: Initialization confirmation
- `CNF`: Change confirmation (with status and old attributes)

### **Data Inputs**
- `u16ObjId` (UINT): Object ID (16-bit)
- `u8FillType` (USINT): New fill type
- `u8FillColour` (USINT): New fill color
- `u16FillPatternId` (UINT): New fill pattern

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `u8OldFillType` (USINT): Old fill type
- `u8OldFillColour` (USINT): Old fill color
- `u16OldFillPatternId` (UINT): Old fill pattern
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with object ID
- `INITO` confirms operational readiness

2. **Attribute Change**:

- `REQ` with new fill attributes
- Changes Object Fill Properties
- `CNF` provides result status and previous values

3. **Error Handling**:

- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.32)

✔ **Comprehensive attribute control** (type, color, pattern)

✔ **Feedback of previous values** for reversal options
✔ **Transaction-safe** (Atomic execution)

## Attribute Properties

| Feature | Description |

|---------------|----------------------------------|

| Fill types | According to ISO 11783-6 B.14.4 |

| Color palette | 8-bit color index |

| Patterns | 16-bit pattern references |

| Object range | All fillable VT objects |

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
- **Design Adjustments**: Dynamic Interface Design
- **Status Visualization**: Color Highlighting
- **Pattern Change**: Context-Sensitive Displays
- **Theme Change**: Dark/Light Mode Switching

## ⚖️ Comparison with Similar Building Blocks

| Feature | Q_FillAttributes | VtSetColor | VtPatternManager |

---------------|------------------|------------|------------------|

| ISO Standard | ✔ | ✖ | ✖ |

| Color Control | ✔ | ✔ | ✖ |

| Pattern Control | ✔ | ✖ | ✔ |

| Type Control | ✔ | ✖ | ✖ |

## Conclusion

The Q_FillAttributes module provides the standard implementation for fill attribute changes:

- **Versatile**: Complete control over fill properties
- **Traceable**: Feedback of previous values
- **Robust**: ISO-compliant error handling

Essential for:

- Dynamic user interfaces
- State-dependent visualizations
- Design-flexible VT applications
