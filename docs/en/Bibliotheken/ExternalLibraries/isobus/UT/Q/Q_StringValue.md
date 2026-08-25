# Q_StringValue

![Q_StringValue](https://user-images.githubusercontent.com/69573151/212334298-f7c6215c-a80c-491c-ad3e-6ba0e539f0d0.png)

* * * * * * * * * *
## Introduction

The **Q_StringValue** is a standards-compliant function block for dynamic text updates in Virtual Terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.24) specification for VT text objects.
![Q_StringValue](Q_StringValue.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request (with object ID)
- `REQ`: Text Change Request

### **Event Outputs**

- `INITO`: Initialization Confirmation
- `CNF`: Change Confirmation

### **Data Inputs**

- `u16ObjId` (UINT): Text Object ID (16-bit)
- `pau8String` (STRING): New Text Value (null-terminated)

### **Data Outputs**

- `STATUS` (STRING): Operational Status Message
- `pau8OldString` (STRING): Previous text value
- `s16result` (INT): ISO-compliant result code

## Valid Object IDs

**`u16ObjId` — valid object types (Annex F.24, objects with string value attribute):**
Input String Field (8000–8999), Output String Field (11000–11999), String Variable (22000–22999), Input Attributes (26000–26999).

**Data length / Transport Protocol:** The F.24 command has a **variable data length** (command frame: Object ID, string byte count, string value). Strings that fit into a single CAN message are sent directly; longer strings are transmitted using the ISO 11783 **transport protocol**. Per Annex F.24 the transferred string may be shorter than the target object's length attribute (the VT pads it with space characters), but the number of transferred bytes shall not exceed the target object's length attribute.

ID_NULL (65535) is not a command target but deactivates the FB when used with `INIT`. Any ID outside these ranges is invalid for commanding.

## Functionality

1. **Initialization**:
- `INIT` with target object ID
- `INITO` confirms operational readiness
2. **Text Update**:
- `REQ` with new text string
- Immediately updates the VT text object
- `CNF` returns operational status and previous text
3. **String Requirements**:
- Maximum `ISO_VTC_CMD_STR_MAX_LENGTH` including null termination
- Must be null-terminated

## Technical Features

✔ **ISO 11783-6 compliant** (F.24)

✔ **Real-time text update** (FIFO-based)

✔ **Null termination required**

✔ **Traceability** (Previous text value)

## String format

| Parameters | Requirements |
|--------------------|----------------------------------|
| Maximum length | ISO_VTC_CMD_STR_MAX_LENGTH |
| Termination | '\0' at the end is mandatory |
| Character set | ISO-8859-1 (Latin-1) recommended |

## Return codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Update successful |
| -6 | VT_E_OVERFLOW | String too long or buffer full |
| -8 | VT_E_NOACT | VT not ready |
| -21 | VT_E_NO_INSTANCE | No VT client available |
| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |
| -130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios

- **Dynamic Displays**: Measured values, status messages
- **Language Switching**: Multilingual texts
- **Process Visualization**: Real-time data
- **User Communication**: Dialogs and prompts

## ⚖️ Comparison with similar building blocks

| Feature | Q_StringValue | VtTextUpdate | VtStringManager |
|--------------|---------------|--------------|------------------|
| ISO Standard | ✔ | ✖ | ✖ |
| FIFO Update | ✔ | ✖ | ✔ |
| Length Check | ✔ | ✔ | ✖ |
| Feedback | ✔ | ✖ | ✔ |

## 🛠️ Related Exercises

* [Exercise_012c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012c.md)

## Conclusion

The Q_StringValue block offers efficient text management:

- **High-performance**: Direct FIFO update
- **Secure**: Integrated length check
- **Flexible**: For all text object types

Essential for:

- Dynamic process visualization
- Multilingual applications
- Real-time data display
