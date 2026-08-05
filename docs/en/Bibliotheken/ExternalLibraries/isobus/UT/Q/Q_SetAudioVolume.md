# Q_SetAudioVolume
![Q_SetAudioVolume](https://user-images.githubusercontent.com/116869307/214153008-918f1900-9a0a-4ee0-8fdb-ef02818a91cd.png)

* * * * * * * * * *
## Introduction
The **Q_SetAudioVolume** is a standards-compliant function block for volume control in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.12) specification for VT audio control.
![Q_SetAudioVolume](Q_SetAudioVolume.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request
- `REQ`: Volume Change Request

### **Event Outputs**
- `INITO`: Initialization Acknowledgement
- `CNF`: Change Acknowledgement

### **Data Inputs**
- `u8Volume` (USINT): Volume Value (0-100%)

### **Data Outputs**
- `STATUS` (STRING): Operating Status Message
- `u8OldVolume` (USINT): Previous Volume Setting
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` without parameters
- `INITO` confirms operational readiness

2. **Volume Control**:

- `REQ` with desired volume level
- Changes the global VT volume
- `CNF` returns operating status and previous value

3. **Value Range**:

- 0%: Muted
- 100%: Maximum volume

## Technical Features

✔ **ISO 11783-6 compliant** (F.12)
✔ **Global audio control**
✔ **Percentage control** (0-100%)
✔ **Traceability** (Previous Setting)

## Volume Reference

| Value | Meaning |

|------|------------------------|

| 0 | Mute |

| 50 | Medium Volume |

| 100 | Maximum Volume |

## Return Codes (s16result)

| Code | Constant | Meaning |

|------|-------------------------|------------------------------------|

| 0 | VT_E_NO_ERR | Successful Change |

| -6 | VT_E_OVERFLOW | Buffer Overflow |

| -8 | VT_E_NOACT | VT Not Ready |

| -21 | VT_E_NO_INSTANCE | No VT Client Available |

| -128 | VT_E_HANDLE_INVALID | Invalid Audio Configuration |

| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |

-130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios
- **Alarm Management**: Adjustable warning signals
- **Voice Output**: Volume adjustment
- **Ease of Use**: User-defined audio settings
- **Night Mode**: Automatic volume reduction

## ⚖️ Comparison with similar components

| Feature | Q_SetAudioVolume | VtAudioControl | VtSoundManager |

---------------|------------------|----------------|----------------|

| ISO Standard | ✔ | ✖ | ✖ |

| Value Range | 0-100% | 0-255 | 0-10 steps |

| Global Effect | ✔ | ✔ | ✖ |

Feedback | ✔ | ✖ | ✔ |

## Conclusion

The Q_SetAudioVolume module offers precise audio control:

- **Intuitive**: Percentage-based control
- **Reliable**: ISO-compliant implementation
- **Flexible**: For all audio outputs

Essential for:

- Professional alarm systems
- Voice-controlled applications
- User-friendly interfaces
