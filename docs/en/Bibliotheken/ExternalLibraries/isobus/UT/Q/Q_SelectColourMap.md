# Q_SelectColourMap
![Q_SelectColourMap](https://user-images.githubusercontent.com/116869307/214152861-d7ab7c89-b643-4672-9689-addd4eddc23a.png)

* * * * * * * * * *
## Introduction
The **Q_SelectColourMap** is a standards-compliant function block for managing color palettes in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.60) specification for VT systems from version 4 onwards.
![Q_SelectColourMap](Q_SelectColourMap.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request
- `REQ`: Color Palette Change Request

### **Event Outputs**
- `INITO`: Initialization Acknowledgement
- `CNF`: Change Acknowledgement

### **Data Inputs**
- `u16ObjIdColourMap` (UINT): Color Palette Object ID or 0xFFFF for the default palette

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `u16OldObjIdColourMap` (UINT): Previous color palette ID
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` without parameters
- `INITO` confirms operational readiness

2. **Pallet Change**:

- `REQ` with target color palette ID
- Global color management change
- `CNF` provides operational status and previous palette

3. **Special Values**:

- `0xFFFF`: Sets the default ISO color table

## Technical Features

✔ **ISO 11783-6 compliant** (F.60)
✔ **Global effect**: Affects all workspaces
✔ **Long execution time**: For complex palettes
✔ **Traceability**: Previous palette can be saved

## Color Palette Reference

| Value | Meaning |

|------------|-------------------------------|

| 0x0001-FFFE| User-defined palettes |

| 0xFFFF | ISO Standard Palette (A.3) |

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Successful switch |

| -6 | VT_E_OVERFLOW | Buffer Overflow |

-8 | VT_E_NOACT | VT Not Ready |

-21 | VT_E_NO_INSTANCE | No VT Client Available |

-129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT Instance |

-130 | VT_E_NOT_ALIVE | VT Not Active |

## Application Scenarios
- **Design Change**: Dynamic Color Schemes
- **Night Mode**: Eye-Friendly Palettes
- **Brand Specifics**: Corporate Design
- **Accessibility**: High-Contrast Modes

## ⚖️ Comparison with Similar Components

| Feature | Q_SelectColourMap | VtColorManager | VtPaletteControl |

---------------|-------------------|----------------|------------------|

| ISO Standard | ✔ | ✖ | ✖ |

Global Effect | ✔ | ✖ | ✔ |

Standard Palette | ✔ | ✖ | ✖ |

Feedback | ✔ | ✖ | ✔ |

## Conclusion

The Q_SelectColourMap module offers professional color management:

- **Comprehensive**: Global color control
- **Flexible**: User and standard palettes
- **Reliable**: ISO-compliant implementation

Essential for:

- Design-oriented applications
- Adaptive visualization systems
- Brand-specific interfaces
