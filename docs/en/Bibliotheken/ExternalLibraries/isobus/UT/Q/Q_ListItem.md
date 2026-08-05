# Q_ListItem
![Q_ListItem](https://user-images.githubusercontent.com/116869307/214147979-74d9863c-caa6-4953-8208-ae779dc6c71a.png)

* * * * * * * * * *
## Introduction
The **Q_ListItem** is a standards-compliant function module for managing list entries in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.42) specification for list input objects in VT systems.
![Q_ListItem](Q_ListItem.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization request (with list object ID)
- `REQ`: Change request (with index and new object ID)

### **Event Outputs**
- `INITO`: Initialization confirmation
- `CNF`: Change confirmation (with status and previous values)

### **Data Inputs**
- `u16ObjId` (UINT): List object ID (16-bit)
- `u8ListIndex` (USINT): List index (0-based)
- `u16NewObjId` (UINT): New object ID or 0xFFFF (empty entry)

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `u8OldListIndex` (USINT): Previous list index
- `u16OldObjId` (UINT): Previous object ID
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with list object ID
- `INITO` confirms operational readiness

2. **List Change**:

- `REQ` with index and new object ID
- Updates the list entry
- `CNF` returns result status and previous values

3. **Special Case**:

- `u16NewObjId = 0xFFFF` creates an empty entry

## Technical Features

✔ **ISO 11783-6 compliant** (F.42)
✔ **Dynamic List Management** (Real-time changes)
✔ **Traceability** (Previous state storage)
✔ **Flexible blanks** (0xFFFF special value)

## Index Reference

| Index | Description |
|-------|----------------------------|
| 0 | First list entry |
| ... | |
| 255 | Maximum index (uint8_t) |

## Return Codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Successful change |
| -6 | VT_E_OVERFLOW | Buffer overflow |
| -8 | VT_E_NOACT | VT not ready |
| -21 | VT_E_NO_INSTANCE | No VT client available |
| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |
| -130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios
- **Dynamic Menus**: Context-Aware Entries
- **Device Selection**: Plug-and-Play Device Lists
- **Parameter Settings**: Selection Options
- **Diagnostic Lists**: Fault Code Management

## ⚖️ Comparison with Similar Components

| Feature | Q_ListItem | VtListManager | VtDynamicMenu |
|---------------|-------------|---------------|---------------|
| ISO Standard | ✔ | ✖ | ✖ |
| Real-Time Change | ✔ | ✔ | ✖ |
| Empty Entries | ✔ | ✖ | ✔ |
| Index Return | ✔ | ✖ | ✖ |

## Conclusion

The Q_ListItem building block offers efficient list management:

- **Reactive**: Instant GUI updates
- **Robust**: Integrated error handling
- **Compatible**: Full ISO compliance

Essential for:

- Interactive selection menus
- Dynamic configurators
- Adaptive user interfaces
