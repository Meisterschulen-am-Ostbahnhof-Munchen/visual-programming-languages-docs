# Q_SelectActiveWorkingSet

![Q_SelectActiveWorkingSet](https://user-images.githubusercontent.com/116869307/214148333-97dd868b-07dc-4e3c-9dcf-aa68d76603f2.png)

* * * * * * * * * *
## Introduction

The **Q_SelectActiveWorkingSet** is a standards-compliant function block for controlling active workspaces in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.64) specification for VT systems from version 6 onwards.
![Q_SelectActiveWorkingSet](Q_SelectActiveWorkingSet.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request
- `REQ`: Workspace Change Request

### **Event Outputs**

- `INITO`: Initialization Acknowledgement
- `CNF`: Change Acknowledgement

### **Data Inputs**

- `pau8Name` (USINT[8]): ISO NAME of the new active workspace

### **Data Outputs**

- `STATUS` (STRING): Operational status message
- `pau8OldName` (USINT[8]): ISO NAME of the previous workspace
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:
- `INIT` without parameters
- `INITO` confirms operational readiness
2. **Workspace change**:
- `REQ` with 8-byte ISO NAME of the target workspace
- Performs context change
- `CNF` returns operational status and previous workspace
3. **ISO NAME format**:
- 8-byte array according to ISO 11783-5 specification

## Technical features

✔ **ISO 11783-6 Compliant** (F.64)
✔ **Exclusive to VT Version 6+**
✔ **Full Context Switch** (All associated resources)
✔ **Traceability** (Previous workspace)

## ISO NAME Structure

| Byte | Content |
|------|-------------------------|
| 0-1 | Vendor ID |
| 2-3 | Device ID |
| 4-5 | Device Instance |
| 6-7 | Workspace ID |

## Return Codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Successful Switch |
| -6 | VT_E_OVERFLOW | Buffer Overflow |
| -8 | VT_E_NOACT | VT not ready |
-21 | VT_E_NO_INSTANCE | No VT client available |
-129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |
-130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios

- **Multi-Client Systems**: Device switching
- **User Profiles**: Individual work environments
- **Process Phases**: Operating mode switching
- **Diagnostic Management**: Service/Normal mode

## ⚖️ Comparison with similar building blocks

| Feature | Q_SelectActiveWorkingSet | VtContextSwitch | VtWorkspaceManager |
---------------|--------------------------|-----------------|--------------------|
ISO Standard | ✔ | ✖ | ✖ |
VT Version | 6+ | All | All |
ISO NAME | ✔ | ✖ | ✖ |
Feedback | ✔ | ✖ | ✔ |

## Conclusion

The Q_SelectActiveWorkingSet building block offers centralized workspace control:

- **Secure**: ISO-compliant identification
- **Efficient**: Complete context switching
- **Transparent**: Previous state traceable

Essential for:

- Complex multi-client systems
- Flexible user environments
- Process-oriented VT applications
