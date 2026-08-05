# Q_GetAttribute
![Q_GetAttribute](https://user-images.githubusercontent.com/116869307/214147879-2749e8c2-364e-4335-9c0e-0445694831e4.png)
* * * * * * * * * *
## Introduction
The **Q_GetAttribute** is a standards-compliant function module for querying object attributes in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.58) specification for VT systems from version 4 onwards.
![Q_GetAttribute](Q_GetAttribute.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization request (with object ID)
- `REQ`: Attribute query request (with attribute ID)

### **Event Outputs**
- `INITO`: Initialization acknowledgment
- `CNF`: Query acknowledgment (with status and attribute value)

### **Data Inputs**
- `u16ObjId` (UINT): Object ID (16-bit)
- `u8AID` (USINT): Attribute ID (8-bit)

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `u8OldAID` (USINT): Current attribute value
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with object ID
- `INITO` confirms operational readiness

2. **Attribute Query**:

- `REQ` with desired attribute ID
- Reads current attribute value from VT
- `CNF` returns result status and current value

3. **Error Handling**:

- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.58)
✔ **Exclusive to VT Version 4+**
✔ **Universally applicable** (All object types)
✔ **Real-time capable** (Fast query cycles)

## Attribute Types

| Category | Example IDs | Description |

|----------------|--------------------------|----------------------------------|

| Basic Attributes | 0x01 - 0x0F | Visibility, Activity |

| Appearance | 0x10 - 0x2F | Colors, Borders, Alignment |

| Content | 0x30 - 0x4F | Text Values, Numeric Values |

| States | 0x50 - 0x6F | Alarm Status, Operating Modes |

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Query successful |

| -6 | VT_E_OVERFLOW | Buffer overflow |

| -8 | VT_E_NOACT | VT not ready |

| -21 | VT_E_NO_INSTANCE | No VT client available |

| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |

| -130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios
- **System Diagnostics**: Status Queries
- **User Interaction**: Input Value Validation
- **Automation**: Rule-Based Controls
- **Configuration**: Parameter Readout

## ⚖️ Comparison with Similar Function Blocks

| Feature | Q_GetAttribute | VtReadValue | VtObjectQuery |

|---------------|----------------|-------------|---------------|

| ISO Standard | ✔ | ✖ | ✖ |

| VT Version | 4+ | All | All |

| Attribute Width | Universal | Value-Only | Limited IDs |

## Conclusion

The Q_GetAttribute function block offers the standard implementation for attribute queries:

- **Efficient**: Minimal latency
- **Reliable**: Robust error detection
- **Flexible**: Supports all object types

Essential for:

- Diagnostic systems
- Automation solutions
- Interactive VT applications
- Configuration management