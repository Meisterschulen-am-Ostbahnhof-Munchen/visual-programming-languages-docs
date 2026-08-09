# Q_ChangeObjectLabel

![Q_ChangeObjectLabel](https://user-images.githubusercontent.com/116869307/214146892-63ae12b3-94e1-400d-bbdc-57754ce825f2.png)

* * * * * * * * * *
## Introduction

The **Q_ChangeObjectLabel** is a standards-compliant function block for changing object labels in Virtual Terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.50) specification for agricultural tax systems.
![Q_ChangeObjectLabel](Q_ChangeObjectLabel.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request (with object ID)
- `REQ`: Label Change Request (with text/graphic parameters)

### **Event Outputs**

- `INITO`: Initialization Acknowledgement
- `CNF`: Change Acknowledgement (with result data)

### **Data Inputs**

- `u16ObjId` (UINT): Target Object Identifier
- `u16ObIdStringVar` (UINT): Text Variable Object ID (max. 32 characters)
- `u8FontType` (USINT): Font (for text labeling)
- `u16ObIdGrafic` (UINT): Graphic object ID (for symbol labeling)

### **Data Outputs**

- `STATUS` (STRING): Operating status message
- `u16OldObIdStringVar` (UINT): Previous text variable ID
- `u8OldFontType` (USINT): Previous font
- `u16OldObIdGrafic` (UINT): Previous graphic object ID
- `s16result` (INT): ISO-compliant result code

## Valid Object IDs

The F.50 command addresses, in bytes 2,3, the **Object ID of the object to label** — per Annex F.51 (error bit 0) and B.21 this object must be **listed in the Object Label Reference List** (i.e. any pool object whose ID is an entry of the reference list).

**Implementation note (VTClientHelper):** `iso_is_object_label_refer_list_id` accepts only the **ObjectLabelReferList** range (the Object Label Reference List object's own ID) — a known deviation from the Annex F.50 semantics:
- **ObjectLabelReferList**: 40000 – 40999

ID_NULL (65535) is not a valid command target but deactivates the FB when sent via `INIT`.

## Functionality

1. **Initialization**:
- `INIT` with target object ID
- `INITO` confirms operational readiness
2. **Label Change**:
- `REQ` with new label parameters
- Supports text (with font) or graphic symbols
- `CNF` returns the result and the old values
3. **Error Handling**:
- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.50)
✔ **Flexible Labeling**: Text or graphics
✔ **Font Control** (8-bit)
✔ **32-character limit** for text labels

## Standard Parameters

| Parameter | NULL value | Description |
|--------------------|-----------|----------------------------|
| u16ObIdStringVar | 0xFFFF | No text |
| u16ObIdGrafic | 0xFFFF | No graphic |

## Return Codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Success |
| -6 | VT_E_OVERFLOW | Buffer overflow (text too long) |
| -128 | VT_E_HANDLE_INVALID | Invalid object ID |

## Application Scenarios

- **Machine Control**: Dynamic button labels
- **Language Switching**: Multilingual interfaces
- **Status Indicators**: Icon change on alarms
- **Personalization**: User-defined labels

## ⚖️ Comparison with similar building blocks

| Feature | Q_ChangeObjectLabel | VtDynamicLabel | VtTextManager |
---------------|---------------------|----------------|---------------|
| ISO Standard | ✔ | ✖ | ✖ |
| Labeling | Text + Graphics | Text Only | Text Only |
| Font | Controllable | Fixed | Partial |

## Conclusion

The Q_ChangeObjectLabel block provides the reference implementation for ISOBUS labeling:

- **Versatile**: Combination of text and graphics
- **Standard-compliant**: Full ISO 11783-6 compatibility
- **Proven in practice**: Used in modern agricultural machinery

Essential for:

- Adaptive user interfaces
- Multilingual systems
- Icon-driven operating concepts
