# Q_ObjSelectInput
![Q_ObjSelectInput](https://user-images.githubusercontent.com/116869307/214148166-50d7f308-5767-4b09-b5a9-cd6f4e61bd5b.png)
* * * * * * * * * *
## Introduction
The **Q_ObjSelectInput** is a standards-compliant function block for the programmatic selection of input fields in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.6) specification for VT input elements.
![Q_ObjSelectInput](Q_ObjSelectInput.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request (with object ID)
- `REQ`: Selection Request (with option parameter)

### **Event Outputs**
- `INITO`: Initialization Confirmation
- `CNF`: Selection Confirmation

### **Data Inputs**
- `u16ObjId` (UINT): Input Object ID (16-bit)
- `u8Option` (USINT): Selection Option (0x00 or 0xFF)

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `u8OldOption` (USINT): Previous selection option
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with target object ID
- `INITO` confirms operational readiness

2. **Field selection**:

- `REQ` with selection option
- Sets focus on the input field
- `CNF` returns operational status and previous option

3. **Options**:

- `0xFF`: Standard selection (VT version 3+)
- `0x00`: Extended selection (VT version 4+ only)

## Technical Special Features

✔ **ISO 11783-6 compliant** (F.6)
✔ **VT version dependent** (Option 0x00 only available from VT4 onwards)
✔ **Instant focus change**
✔ **Feedback of previous state**

## Option Reference

| u8Option | Description | VT Version |

|----------|----------------------------|------------|

| 0xFF | Standard selection | 3+ |

| 0x00 | Extended selection | 4+ |

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Successful execution |

| -6 | VT_E_OVERFLOW | Buffer Overflow |

-8 | VT_E_NOACT | VT Not Ready |

-21 | VT_E_NO_INSTANCE | No VT Client Available |

-129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT Instance |

-130 | VT_E_NOT_ALIVE | VT Not Active |

## Application Scenarios
- **Form Navigation**: Automatic Field Selection
- **Input Assistants**: Guided Operation
- **Error Management**: Direct Jump to Error Fields
- **Touch Optimization**: Programmatic Focus Control

## ⚖️ Comparison with Similar Function Blocks

| Feature | Q_ObjSelectInput | VtFocusControl | VtInputSelector |

|---------------|------------------|----------------|-----------------|
| ISO Standard | ✔ | ✖ | ✖ |

| VT Version 4+ | ✔ | ✖ | ✔ |

| Option Control | ✔ | ✖ | ✖ |

| Feedback | ✔ | ✖ | ✔ |

## Conclusion

The Q_ObjSelectInput block offers precise input field control:

- **Efficient**: Direct focus change
- **Flexible**: Version-specific options
- **Reliable**: ISO-compliant implementation

Essential for:

- Professional form applications
- Guided user processes
- Touchscreen-optimized interfaces