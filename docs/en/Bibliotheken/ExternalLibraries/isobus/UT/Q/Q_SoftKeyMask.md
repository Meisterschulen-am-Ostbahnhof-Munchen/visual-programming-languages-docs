# Q_SoftKeyMask
![Q_SoftKeyMask](https://user-images.githubusercontent.com/116869307/214153149-6b211119-6c29-4154-bfa3-d1dd61a435bb.png)

* * * * * * * * * *
## Introduction
The **Q_SoftKeyMask** is a standards-compliant function block for managing softkey masks in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.36) specification for VT systems.
![Q_SoftKeyMask](Q_SoftKeyMask.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request
- `REQ`: Screen Change Request

### **Event Outputs**
- `INITO`: Initialization Confirmation
- `CNF`: Change Confirmation

### **Data Inputs**
- `u8MaskType` (USINT): Screen Type (1=Data, 2=Alarm)
- `u16DataMaskId` (UINT): Object ID of the Active Screen
- `u16SoftKeyMaskId` (UINT): Object ID of the New Softkey Screen

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `u8OldMaskType` (USINT): Previous screen type
- `u16OldDataMaskId` (UINT): Previous data mask ID
- `u16OldSoftKeyMaskId` (UINT): Previous softkey screen ID
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` without parameters
- `INITO` confirms operational readiness

2. **Screen change**:

- `REQ` with screen type, data mask ID, and new softkey screen
- Linkes softkeys to the active screen
- `CNF` provides operating status and previous configuration

3. **Mask Types**:

- `1`: Data Mask Link
- `2`: Alarm Mask Link

## Technical Features

✔ **ISO 11783-6 compliant** (F.36)
✔ **Dual Mask Types** (Data/Alarms)
✔ **Dynamic Reassignment**
✔ **Traceability** (Previous Configuration)

## Mask Type Reference

| Value | Type | Description |

|------|-----------|----------------------------|

| 1 | Data | Normal Data Mask |

| 2 | Alarm | Alarm Mask Link |

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Successful switch |

| -6 | VT_E_OVERFLOW | Buffer overflow |

| -8 | VT_E_NOACT | VT not ready |

| -21 | VT_E_NO_INSTANCE | No VT client available |

| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |

| -130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios
- **Context-Sensitive Softkeys**: Function Switching
- **Alarm Management**: Special Alarm Softkeys
- **Mask Hierarchies**: Dynamic Key Assignments
- **User Guidance**: Adaptive User Interfaces

## ⚖️ Comparison with Similar Components

| Feature | Q_SoftKeyMask | VtKeyMapping | VtMaskLinker |

|---------------|---------------|---------------|--------------|

| ISO Standard | ✔ | ✖ | ✖ |

| Mask Types | 2 (Data/Alarm)| 1 (Universal)| 1 (Data) |

| Feedback | ✔ | ✖ | ✔ |

| Real-Time Switching | ✔ | ✔ | ✖ |

## Conclusion

The Q_SoftKeyMask module offers flexible softkey control:

- **Context-sensitive**: Different mask types
- **Dynamic**: Instant reassignment
- **Reliable**: ISO-compliant implementation

Essential for:

- Professional user interface concepts
- Complex mask hierarchies
- Adaptive VT applications
