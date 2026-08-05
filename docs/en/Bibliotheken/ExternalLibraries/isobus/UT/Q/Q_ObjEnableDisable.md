# Q_ObjEnableDisable

![Q_ObjEnableDisable](https://user-images.githubusercontent.com/116869307/214148082-167eae93-48d4-40cd-96e2-d0983e475187.png)

* * * * * * * * * *

## Introduction
The **Q_ObjEnableDisable** is a standards-compliant function block for enabling/disabling input objects in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.4) specification for VT input elements.


![Q_ObjEnableDisable](Q_ObjEnableDisable.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request (with object ID)
- `REQ`: Activation/Deactivation Request

### **Event Outputs**
- `INITO`: Initialization Confirmation
- `CNF`: Operation Confirmation

### **Data Inputs**
- `u16ObjId` (UINT): Object ID (16-bit)
- `qAbility` (BOOL): Activation Status (TRUE=activate, FALSE=deactivate)

### **Data Outputs**
- `STATUS` (STRING): Operational status message

- `qOldAbility` (BOOL): Previous activation status

- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` with target object ID

- `INITO` confirms operational readiness

2. **Status Change**:

- `REQ` with desired activation state

- Changes the object's interaction capability

- `CNF` returns operational status and previous state

3. **Special Cases**:

- VT_E_HANDLE_INVALID is returned for invalid object IDs

## Technical Features

✔ **ISO ISO 11783-6 compliant** (F.4)
✔ **Simple Binary Control** (Enabled/Disabled)
✔ **State Feedback** (Previous State)
✔ **Broad Object Support** (All Input Elements)

## Status Reference

| qAbility | Object State |

|----------|----------------------|

| FALSE (0)| Disabled (gray) |

| TRUE (1) | Enabled (normal) |

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Successful Execution |

| -6 | VT_E_OVERFLOW | Buffer Overflow |

| -8 | VT_E_NOACT | VT not ready |

-21 | VT_E_NO_INSTANCE | No VT client available |

-128 | VT_E_HANDLE_INVALID | Invalid object ID |

-129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |

-130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios

- **Form Control**: Conditional input approval
- **Security Features**: Block critical input

- **Workflow Management**: Step-by-step approval
- **Diagnostic Modes**: Input restrictions

## ⚖️ Comparison with similar building blocks

| Feature | Q_ObjEnableDisable | VtInputControl | VtObjectState |

|---------------|--------------------|----------------|---------------|

| ISO Standard | ✔ | ✖ | ✖ |

| Binary Control | ✔ | ✔ | ✖ |

| Feedback | ✔ | ✖ | ✔ |

| Object Type | Input Objects | All | All |

## Conclusion

The Q_ObjEnableDisable block provides essential input control:

- **Simple**: Clear activation logic
- **Reliable**: Integrated error detection
- **Flexible**: For all input element types

Essential for:

- Interactive forms
- Secure user interfaces
- State-driven applications