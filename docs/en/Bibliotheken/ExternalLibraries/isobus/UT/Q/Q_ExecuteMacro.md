# Q_ExecuteMacro
![Q_ExecuteMacro](https://user-images.githubusercontent.com/116869307/214147465-1e5432e3-d3d3-4eee-a8a5-8aec4ee82198.png)

* * * * * * * * * *
## Introduction
The **Q_ExecuteMacro** is a standards-compliant function block for executing macros in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.48) specification for VT from version 4 onwards.
![Q_ExecuteMacro](Q_ExecuteMacro.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization request (with macro ID)
- `REQ`: Macro execution request

### **Event Outputs**
- `INITO`: Initialization acknowledgment
- `CNF`: Execution acknowledgment (with status)

### **Data Inputs**
- `u16ObjId` (UINT): Macro object ID (max. value 255)

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with macro object ID (8-bit compatible)
- `INITO` confirms operational readiness

2. **Macro Execution**:

- `REQ` without additional parameters
- Executes stored macro sequence
- `CNF` returns result status

3. **Error Handling**:

- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.48)
✔ **Compatible with VT version 4+**
✔ **8-bit Macro IDs** (0-255)
✔ **Atomised Execution** (Transaction-Safe)

## Macro Properties

| Feature | Description |
|---------------|----------------------------------|
| Location | Permanently stored in the VT |
| Size | Up to 255 commands |
| Content | VT command sequences |
| ID Range | 0x01 - 0xFF (8-bit) |

## Return Codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Successful execution |
| -6 | VT_E_OVERFLOW | Macro too complex |
| -8 | VT_E_NOACT | VT not ready |
-129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |

## Application Scenarios
- **Standard Flows**: Frequently Used Command Chains
- **System Startup**: Basic Initializations
- **Operating Sequences**: Automated Menu Navigation
- **Diagnostics**: Predefined Test Routines

## ⚖️ Comparison with Similar Components

| Feature | Q_ExecuteMacro | Q_ExecuteExtendedMacro | VtMacroRunner |
---------------|----------------|------------------------|---------------|
| ISO Standard | ✔ | ✔ | ✖ |
| VT Version | 4+ | 5+ | All |
| ID Type | 8-bit | 16-bit | 8-bit |

## Conclusion

The Q_ExecuteMacro block offers the standard implementation for basic macros:

- **Simple**: Compact 8-bit addressing
- **Compatible**: Works with VT Generation 4+
- **Reliable**: Proven technology in production devices

Ideal for:

- Standard automation
- Compatibility-critical systems
- Simple macro applications
