# Q_ESC

![Q_ESC](https://user-images.githubusercontent.com/116869307/214147236-7b0ba071-871f-4b5c-8d15-5089ae7f07fc.png)

* * * * * * * * * *

## Introduction
The **Q_ESC** is a standards-compliant function block for termination control in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.8) specification for agricultural tax systems.


![Q_ESC](Q_ESC.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request
- `REQ`: Abort Request

### **Event Outputs**
- `INITO`: Initialization Confirmation
- `CNF`: Abort Confirmation (with status)

### **Data Outputs**
- `STATUS` (STRING): Operational Status Message
- `s16result` (INT): ISO-compliant Result Code

## Functionality

1. **Initialization**:

- `INIT` without parameters

- `INITO` confirmed Operational Readiness

2. **Cancel Function**:

- `REQ` terminates the current user input

- No additional parameters required

- `CNF` returns the result status

3. **Error Handling**:

- ISO-standardized error codes

- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.8)

✔ **Universal cancel command**

✔ **No configuration required**
✔ **Immediate effect upon execution

## Typical Use Cases

| Scenario | Effect |

|------------------------|-----------------------------|

| Dialog cancel | Ends current input |

| Exit menu | Return to main screen |

| Alarm acknowledgement | Stops audible signals |

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Successfully aborted |

| -8 | VT_E_NOACT | No active input to abort |

| -21 | VT_E_NO_INSTANCE | No VT instance available |

| -130 | VT_E_NOT_ALIVE | VT not reachable |

## Application Scenarios

- **Emergency Abort**: Quickly terminate processes

- **Input Error**: Correction option for users

- **Menu Navigation**: Back functionality

- **System Reset**: Abort all active operations

## ⚖️ Comparison with similar modules

| Feature | Q_ESC | VtAbortCmd | VtCancelOp |

|---------------|-------------|--------------|-------------|

| ISO Standard | ✔ | ✖ | ✖ |

| Effect | Global | Local | Object-Specific |

| Parameters | None | Configurable | Configurable |

## Conclusion

The Q_ESC block provides the standardized abort function for ISOBUS systems:

- **Universal**: Suitable for all abort scenarios
- **Simple**: No configuration required
- **Reliable**: Immediate system response

Essential for:

- Safety-critical applications

- User-friendly interfaces
- Robust error handling