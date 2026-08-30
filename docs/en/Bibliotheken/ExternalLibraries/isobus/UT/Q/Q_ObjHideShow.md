# Q_ObjHideShow

![Q_ObjHideShow](https://user-images.githubusercontent.com/116869307/214148121-b8115f93-fc92-499d-ae8f-b207656d64c0.png)

* * * * * * * * * *

## Introduction

The **Q_ObjHideShow** is a standards-compliant function block for controlling the visibility of container objects in Virtual Terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.2) specification for VT containers.
![Q_ObjHideShow](Q_ObjHideShow.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request (with Container Object ID)
- `REQ`: Visibility Change Request

### **Event Outputs**

- `INITO`: Initialization Acknowledgement
- `CNF`: Change Acknowledgement

### **Data Inputs**

- `u16ObjId` (UINT): Container Object ID (16-bit)
- `qVisible` (BOOL): Visibility Status (TRUE=show, FALSE=hide)

### **Data Outputs**

- `STATUS` (STRING): Operational status message
- `qOldVisible` (BOOL): Previous visibility status
- `s16result` (INT): ISO-compliant result code

## Valid Object IDs

**`u16ObjId` — valid object types (Annex F.2):**
Container (3000–3999).

ID_NULL (65535) is not a valid command target but deactivates the FB when used with `INIT`. Any ID outside this range is invalid for commanding.

## Functionality

1. **Initialization**:

- `INIT` with container object ID
- `INITO` confirms operational readiness
1. **Visibility Change**:

- `REQ` with desired visibility status
- Changes the display of the container and all contained objects
- `CNF` returns operational status and previous state
1. **Special Cases**:

- VT_E_HANDLE_INVALID is returned for invalid object IDs

## Technical Features

✔ **ISO 11783-6 compliant** (F.2)
✔ **Cascading effect** (Affects contained objects)
✔ **Instant GUI update**
✔ **State retention** (Remembers previous state)

## State reference

| qVisible | Container state |
|----------|----------------------|
| FALSE (0)| Invisible |
| TRUE (1) | Visible |

## Return codes (s16result)

| Code | Constant | Meaning |
| ------ | ------------------------- | ------------------------------------ |
| 0 | VT_E_NO_ERR | Successful execution |
| -6 | VT_E_OVERFLOW | Buffer overflow |
| -8 | VT_E_NOACT | VT not ready | | -21 | VT_E_NO_INSTANCE | No VT client available |
| -128 | VT_E_HANDLE_INVALID | Invalid container ID |
| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |
| -130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios

- **Dynamic Interfaces**: Context-sensitive displays
- **Screen Manager**: View switching
- **Alarm Management**: Fault message containers
- **User Guidance**: Step-by-step instructions

## ⚖️ Comparison with similar components

| Feature | Q_ObjHideShow | VtContainerControl | VtVisibilityManager |
| --------------- | --------------- | -------------------- | --------------------- |
| ISO Standard | ✔ | ✖ | ✖ |
| Container Focus | ✔ | ✔ | ✖ |
| Cascading | ✔ | ✖ | ✔ |
| Feedback | ✔ | ✖ | ✔ |

## 🛠️ Related Exercises

- [Exercise_014](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_014.md)

## Conclusion

The Q_ObjHideShow block offers centralized visibility control:

- **Efficient**: Instant GUI update
- **Comprehensive**: Affects all container elements
- **Reliable**: ISO-compliant implementation

Essential for:

- Adaptive user interfaces
- Complex form hierarchies
- State-driven visualizations
