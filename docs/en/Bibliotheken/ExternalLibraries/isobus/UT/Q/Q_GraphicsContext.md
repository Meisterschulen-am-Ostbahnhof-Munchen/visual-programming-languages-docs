# Q_GraphicsContext

![Q_GraphicsContext](https://user-images.githubusercontent.com/116869307/214147904-b9764918-1247-4264-908d-bd8fb290e0ef.png)

* * * * * * * * * *

## Introduction

The **Q_GraphicsContext** is a standards-compliant function block for controlling graphics context objects in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.56) specification for VT systems from version 4 onwards.
![Q_GraphicsContext](Q_GraphicsContext.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization request (with object ID)
- `REQ`: Configuration request (with sub-command and parameters)

### **Event Outputs**

- `INITO`: Initialization acknowledgment
- `CNF`: Configuration acknowledgment (with status and previous values)

### **Data Inputs**

- `u16ObjId` (UINT): Graphics context object ID (16-bit)
- `u8SubCommandID` (USINT): Subcommand ID (8-bit)
- `u8ParaList` (USINT[5]): Parameter list (5-byte array)
- `u16LenBytes` (UINT): Parameter length in bytes

### **Data Outputs**

- `STATUS` (STRING): Operating status message
- `u8OldSubCommandID` (USINT): Previous subcommand ID
- `u8OldParaList` (USINT[5]): Previous parameter list
- `u16OldLenBytes` (UINT): Previous parameter length
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with graphics context object ID
- `INITO` confirms operational readiness
1. **Configuration**:

- `REQ` with sub-command ID and parameter list
- Configures graphics context properties
- `CNF` returns result status and previous configuration
1. **Error Handling**:

- ISO-standardized error codes
- Buffer overflow check

## Technical Features

✔ **ISO 11783-6 compliant** (F.56)
✔ **Exclusive to VT Version 4+**
✔ **Flexible parameterization** (5-byte parameter array)
✔ **Traceability** (Previous configuration)

## Sub-Command Reference

The sub-command IDs correspond to Table F.1 of ISO 11783-6 (not to be confused with earlier/derived numbering):

| ID | Command                       | Parameter Description                    |
|-----|-------------------------------|------------------------------------------|
| 0   | Set Graphics Cursor           | Bytes 5-6 X, 7-8 Y (signed)              |
| 1   | Move Graphics Cursor          | Bytes 5-6 X offset, 7-8 Y offset (signed)|
| 2   | Set Foreground Colour         | Byte 5 colour index                      |
| 3   | Set Background Colour         | Byte 5 colour index                      |
| 4   | Set Line Attributes Object ID | Bytes 5-6 object ID (65535 = no line)    |
| 5   | Set Fill Attributes Object ID | Bytes 5-6 object ID (65535 = no fill)    |
| 6   | Set Font Attributes Object ID | Bytes 5-6 object ID (65535 = no font)    |

⚠ **Variable data length / Transport Protocol:** The F.56 command has a **variable data length**. Messages **larger than 8 bytes** are transmitted via the **Transport Protocol (TP)**; smaller commands are padded to 8 bytes with FF16. With this FB's 5-byte parameter list (`u8ParaList`, ArraySize 5) the message becomes 9 bytes (→ TP). Sub-commands requiring more than 5 parameter bytes (e.g. Draw Polygon with several points, Pan & Zoom Viewport) cannot be fully expressed through this FB.

## Return Codes (s16result)

| Code | Constant | Meaning |
| ------ | ------------------------- | ------------------------------------ |
| 0 | VT_E_NO_ERR | Successful Execution |
| -6 | VT_E_OVERFLOW | Parameter Buffer Too Small |
| -8 | VT_E_NOACT | VT not ready |
| -21 | VT_E_NO_INSTANCE | No VT client available |
| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |
| -130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios

- **Graphics Rendering**: Line and Fill Styles
- **User Interfaces**: Transparency Effects
- **Charts**: Clipping Ranges for Excerpts
- **Animations**: Transformation Matrices

## Safety Notes

⚠ **Consider Buffer Size**:
Parameter lists must not exceed `ISO_VTC_CMD_STR_MAX_LENGTH`
⚠ **Sub-Command Validation**:

Unknown command IDs can lead to unexpected behavior

## Conclusion

The Q_GraphicsContext block offers powerful graphics control:

- **Precise Control**: Over all graphics attributes
- **Traceable**: Previous State Backup
- **High Performance**: Optimized command load

Essential for:

- High-quality graphics rendering
- Dynamic visualizations
- Complex user interfaces
