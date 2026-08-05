# Q_FontAttributes
![Q_FontAttributes](https://user-images.githubusercontent.com/116869307/214147610-3b768d9e-7d5f-4260-abb0-1393bea3f0ff.png)

* * * * * * * * * *
## Introduction
The **Q_FontAttributes** is a standards-compliant function module for modifying font attributes in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.28) specification for VT systems.
![Q_FontAttributes](Q_FontAttributes.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization request (with object ID)
- `REQ`: Attribute change request (with new font attributes)

### **Event Outputs**
- `INITO`: Initialization confirmation
- `CNF`: Change confirmation (with status and old attributes)

### **Data Inputs**
- `u16ObjId` (UINT): Object ID (16-bit)
- `u8FontColour` (USINT): New font color
- `u8FontSize` (USINT): New font size
- `u8FontType` (USINT): New font
- `u8FontStyle` (USINT): New font style

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `u8OldFontColour` (USINT): Old font color
- `u8OldFontSize` (USINT): Old font size
- `u8OldFontType` (USINT): Old font
- `u8OldFontStyle` (USINT): Old font style
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with object ID
- `INITO` confirms operational readiness

2. **Attribute Change**:

- `REQ` with new font attributes
- Changes the object's font properties
- `CNF` returns the result status and previous values

3. **Error Handling**:

- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.28)
✔ **Comprehensive font control** (color, size, type, style)
✔ **Feedback of previous values** for reversal options
✔ **Transaction-safe** (Atomic execution)

## Attribute Properties

| Feature | Description |

|---------------|----------------------------------|

| Color Palette | 8-bit Color Index (ISO 11783-6 A.3) |

Sizes | Standardized Font Sizes |

Fonts | Predefined Types |

Styles | Bold/Italic/Underline Bit Field |

## Return Codes (s16result)

| Code | Constant | Meaning |

------|-------------------------|------------------------------------|

0 | VT_E_NO_ERR | Successful Change |

-6 | VT_E_OVERFLOW | Buffer Overflow |

-8 | VT_E_NOACT | VT Not Ready |

-21 | VT_E_NO_INSTANCE | No VT Client Available |

-129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT Instance |

-130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios
- **Text Display**: Dynamic font adjustments
- **Warnings**: Color highlighting
- **User Interfaces**: Style changes
- **Accessibility**: Font enlargements

## ⚖️ Comparison with similar building blocks

| Feature | Q_FontAttributes | VtTextStyle | VtFontManager |

---------------|------------------|-------------|---------------|

| ISO Standard | ✔ | ✖ | ✖ |

| Color Control | ✔ | ✔ | ✖ |

| Size Control | ✔ | ✖ | ✔ |

| Style Control | ✔ | ✔ | ✔ |

## Conclusion

The Q_FontAttributes module provides the standard implementation for font attribute changes:

- **Versatile**: Complete control over font properties
- **Traceable**: Feedback of previous values
- **Robust**: ISO-compliant error handling

Essential for:

- Dynamic text rendering
- Accessible applications
- Design-flexible VT interfaces
