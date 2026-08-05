# Q_Attribute
![Q_Attribute](https://user-images.githubusercontent.com/69573151/212329228-8c605296-7915-4def-a497-2860e14ae509.png)

* * * * * * * * * *
## Introduction
The **Q_Attribute** is a standards-compliant function block for modifying VT object properties, developed under the EPL 2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.38) specification for agricultural tax systems.
![Q_Attribute](Q_Attribute.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request (with object ID and attribute ID)
- `REQ`: Attribute Change Request (with new value)

### **Event Outputs**
- `INITO`: Initialization Acknowledgement
- `CNF`: Change Acknowledgement (with result data)

### **Data Inputs**
- `u16ObjId` (UINT): Object Identifier
- `u8IdAttribute` (USINT): Attribute Identifier (AID)
- `u32ValueAttribute` (UDINT): New Attribute Value

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `u32OldValueAttribute` (UDINT): Previous attribute value
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with object and attribute ID
- `INITO` confirms operational readiness

2. **Attribute Change**:

- `REQ` triggers with new value
- `CNF` returns result and old value

3. **Error Handling**:

- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 Compliant** (F.38)
✔ **Deterministic** Execution
✔ **32-bit Value Support**
✔ **Real-time** Processing

## Return Codes (s16result)

| Code | Constant | Meaning |
|------|-----------|-----------|
| 0 | VT_E_NO_ERR | Success |
| -6 | VT_E_OVERFLOW | Buffer Overflow |
| -8 | VT_E_NOACT | Invalid State |
| -21 | VT_E_NO_INSTANCE | No VT Instance |

## Application Scenarios
- **Display Settings**: Visibility/Position of VT Objects
- **Machine Configuration**: Adjusting Operating Parameters
- **Diagnostic Systems**: Controlling Debug Information
- **Multi-Terminal Operation**: Consistent Object Attributes

## ⚖️ Comparison with Similar Blocks

| Feature | Q_Attribute | VtPropertySet | VtDynamicConfig |
|---------------|--------------|---------------|-----------------|
| ISO Standard | ✔ | ✖ | ✖ |
| Value Range | 32-bit | 16-bit | 32-bit |
| State Management | Full | Partial | Extended |

## Conclusion

The Q_Attribute block provides the reference implementation for ISOBUS attribute control:

- **Standard-compliant**: Full ISO 11783-6 compatibility
- **High-performance**: 32-bit value support
- **Reliable**: Proven technology in field devices

Essential for:

- VT object controllers
- Dynamic display configurations
- Machine parameter adapters
