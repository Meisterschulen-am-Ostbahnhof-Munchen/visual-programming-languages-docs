# Q_ExecuteExtendedMacro
![Q_ExecuteExtendedMacro](https://user-images.githubusercontent.com/116869307/214147426-6df72399-0812-4695-ac3f-cda61c5e74c4.png)

* * * * * * * * * *
## Introduction
The **Q_ExecuteExtendedMacro** is a standards-compliant function block for executing extended macros in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.62) specification for VT from version 5 onwards.
![Q_ExecuteExtendedMacro](Q_ExecuteExtendedMacro.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization request (with macro ID)
- `REQ`: Macro execution request

### **Event Outputs**
- `INITO`: Initialization acknowledgment
- `CNF`: Execution acknowledgment (with status)

### **Data Inputs**
- `u16ObjId` (UINT): Macro object ID (16-bit)

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with macro object ID
- `INITO` confirms operational readiness

2. **Macro Execution**:

- `REQ` without additional parameters
- Executes saved macro sequence
- `CNF` returns result status

3. **Error Handling**:

- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.62)
✔ **Exclusive to VT Version 5+**
✔ **16-bit Macro IDs** (Extended Address Space)
✔ **Atomised Execution** (Transaction-Safe)

## Macro Properties

| Feature | Description |

|---------------|----------------------------------|

| Location | Permanently stored in the VT |

| Size | Up to 255 commands |

| Content | VT command sequences |

| ID Range | 0x0001 - 0xFEFF (reserved) |

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Successful execution |

| -6 | VT_E_OVERFLOW | Macro too complex |

| -8 | VT_E_NOACT | VT not ready |

| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |

## Application Scenarios
- **Automated Processes**: Complex Command Chains
- **System Initialization**: Startup Procedures
- **Diagnostic Routines**: Automated Tests
- **User Actions**: Macro Recordings

## ⚖️ Comparison with Similar Components

| Feature | Q_ExecuteExtendedMacro | VtMacroPlayer | VtCommandSequence |

|---------------|------------------------|---------------|-------------------|

| ISO Standard | ✔ | ✖ | ✖ |

| VT Version | 5+ | All | All |

| ID Type | 16-bit | 8-bit | 16-bit |

## Conclusion

The Q_ExecuteExtendedMacro block provides the standard implementation for extended macros:

- **Powerful**: Complex automations possible
- **Future-proof**: Optimized for VT Generation 5
- **Reliable**: Atomic execution guaranteed

Essential for:

- Highly automated agricultural systems
- Complex operating processes
- Systems with extended functionality
