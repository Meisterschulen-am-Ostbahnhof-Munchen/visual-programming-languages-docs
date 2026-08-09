# Q_Priority

![Q_Priority](https://user-images.githubusercontent.com/116869307/214148302-f10f051a-fad7-42af-a3e0-9f5e0eedbaf3.png)

* * * * * * * * * *
## Introduction

The **Q_Priority** is a standards-compliant function block for priority control of alarm masks in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.40) specification for VT alarm management.
![Q_Priority](Q_Priority.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request (with Alarm Mask ID)
- `REQ`: Priority Change Request

### **Event Outputs**

- `INITO`: Initialization Acknowledgement
- `CNF`: Change Acknowledgement

### **Data Inputs**

- `u16ObjId` (UINT): Alarm Mask Object ID (16-bit)
- `u8Priority` (USINT): New Priority (0-255)

### **Data Outputs**

- `STATUS` (STRING): Operational status message
- `u8OldPriority` (USINT): Previous priority
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:
- `INIT` with alarm mask ID
- `INITO` confirms operational readiness
2. **Priority change**:
- `REQ` with new priority value
- Updates the alarm display order
- `CNF` provides result status and previous value
3. **Priority logic**:
- Lower numbers = Higher priority
- Affects alarm display order

## Technical features

✔ **ISO 11783-6 compliant** (F.40)

✔ **Real-time Prioritization** (Immediate Effect)
✔ **Traceability** (Previous Priority)
✔ **Wide Value Range** (0-255)

## Priority Reference

| Priority | Typical Use |
|-----------|-----------------------------|
| 0-31 | Critical System Alarms |
| 32-63 | Important Process Alarms |
| 64-127 | Standard Warnings |
| 128-255 | Informational Messages |

## Return Codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Successful Change |
| -6 | VT_E_OVERFLOW | Buffer Overflow |
-8 | VT_E_NOACT | VT Not Ready |
-21 | VT_E_NO_INSTANCE | No VT Client Available |
-129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT Instance |
-130 | VT_E_NOT_ALIVE | VT Not Active |

## Application Scenarios

- **Alarm Management**: Dynamic Priority Adjustment
- **Process Control**: Importance Classification
- **Diagnostic Systems**: Escalation Management
- **Maintenance Modes**: Temporary Priority Changes

## ⚖️ Comparison with Similar Components

| Feature | Q_Priority | VtAlarmPriority | VtEventManager |
|---------------|------------|-----------------|----------------|
| ISO Standard | ✔ | ✖ | ✖ |
| Real-time effect | ✔ | ✔ | ✖ |
| Value range | 0-255 | 0-127 | 0-31 |
| Feedback | ✔ | ✖ | ✔ |

## Conclusion

The Q_Priority block offers essential alarm control:

- **Dynamic**: Immediate priority adjustment
- **Transparent**: Feedback of the previous state
- **Robust**: Full ISO compliance

Essential for:

- Professional alarm management systems
- Process-critical applications
- Flexible diagnostic solutions
