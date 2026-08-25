# Q_NumericValueAux

* * * * * * * * * *
## Introduction

The **Q_NumericValueAux** is a standards-compliant function block for numeric value changes in Virtual Terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.22) specification for numeric VT objects.
![Q_NumericValueAux](Q_NumericValueAux.svg)
## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request (with object ID)
- `REQ`: Value Change Request

### **Event Outputs**

- `INITO`: Initialization Acknowledgement
- `CNF`: Change Acknowledgement

### **Data Inputs**

- `u16ObjId` (UINT): Object ID (16-bit)
- `u32NewValue` (UDINT): New Numeric Value (32-bit unsigned)

### **Data Outputs**

- `STATUS` (STRING): Operational Status Message
- `u32OldValue` (UDINT): Previous numeric value
- `s16result` (INT): ISO-compliant result code

## Valid Object IDs

**`u16ObjId` — valid object types (Annex F.22, objects with numeric value attribute):**
Input Boolean Field (7000–7999), Input Number Field (9000–9999), Input List Field (10000–10999), Output Number Field (12000–12999), Meter (17000–17999), Linear Bar Graph (18000–18999), Arched Bar Graph (19000–19999), Number Variable (21000–21999), Object Pointer (27000–27999), Output List Object (37000–37999), External Object Pointer (43000–43999), Animation Object (44000–44999), Scaled Graphic Object (48000–48999).

ID_NULL (65535) is not a command target but deactivates the FB when used with `INIT`. Any ID outside these ranges is invalid for commanding.

## Functionality

1. **Initialization**:
- `INIT` with target object ID
- `INITO` confirms operational readiness
2. **Value Update**:
- `REQ` with new 32-bit value
- Updates the numeric VT object
- `CNF` returns operational status and previous value
3. **Value Range**:
- 0 to 4,294,967,295 (32-bit unsigned)

## Technical Features

✔ **ISO 11783-6 compliant** (F.22)

✔ **32-bit value range** (UDINT)

✔ **Instant update**

✔ **Traceability** (Previous value)

## Value range

| Parameter | Type | Value range |
|-------------|-----------|------------------------|
| u32NewValue | UDINT | 0 to 4,294,967,295 |

## Return codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Successful change |
| -6 | VT_E_OVERFLOW | Buffer overflow |
| -8 | VT_E_NOACT | VT not ready |
| -21 | VT_E_NO_INSTANCE | No VT client available |
| -128 | VT_E_HANDLE_INVALID | Invalid object ID |
| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |
| -130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios

- **Measurement Displays**: Real-time data visualization
- **Meter Readings**: Odometer, production counter
- **Process Control**: Setpoint specifications
- **Diagnostic Systems**: Fault code display

## ⚖️ Comparison with similar modules

| Feature | Q_NumericValueAux | VtNumericUpdate | VtValueManager |
|---------------|--------------------|-----------------|----------------|
| ISO Standard | ✔ | ✖ | ✖ |
| Value Range | 32-bit | 16-bit | 32-bit |
| Feedback | ✔ | ✖ | ✔ |
| Object Type | Numeric Objects | All | All |

## Conclusion

The Q_NumericValueAux block offers precise numerical control:

- **High-resolution**: 32-bit value range
- **Reliable**: Integrated error detection
- **Flexible**: For all numeric objects

Essential for:

- Precise measurement display
- High-resolution control
- Professional process visualization