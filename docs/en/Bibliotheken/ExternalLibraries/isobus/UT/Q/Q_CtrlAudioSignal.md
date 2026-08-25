# Q_CtrlAudioSignal

![Q_CtrlAudioSignal](https://user-images.githubusercontent.com/116869307/214147202-f060b872-d3d6-4c56-92c9-84961ce5127b.png)

* * * * * * * * * *
## Introduction

The **Q_CtrlAudioSignal** is a standards-compliant function block for controlling audio devices in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.10) specification for agricultural tax systems.

The F.10 command addresses the VT's **audio device** directly — it does **not reference any object**, so this block has no Object ID input. **Activations = 0** terminates any audio in process from the originating Working Set (frequency and duration values are ignored); 1–255 sets the number of audio activations.
![Q_CtrlAudioSignal](Q_CtrlAudioSignal.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request
- `REQ`: Audio Control Request (with signal parameters)

### **Event Outputs**

- `INITO`: Initialization Acknowledgement
- `CNF`: Control Acknowledgement (with result data)

### **Data Inputs**

- `u8NumOfRepit` (USINT): Repetitions (1-255)
- `u16Frequency` (UINT): Frequency in Hz
- `u16OnTimeMs` (UINT): On-time in ms
- `u16OffTimeMs` (UINT): Off-time in ms

### **Data Outputs**

- `STATUS` (STRING): Operating status message
- `u8OldNumOfRepit` (USINT): Previous repetitions
- `u16OldFrequency` (UINT): Previous frequency
- `u16OldOnTimeMs` (UINT): Previous on-time
- `u16OldOffTimeMs` (UINT): Previous off-time
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:
- `INIT` without parameters
- `INITO` confirmed Operational Readiness
2. **Audio Control**:
- Trigger `REQ` with signal parameters
- Generates tone with a configurable pattern
- `CNF` returns result and previous values
3. **Error Handling**:
- ISO-standardized error codes
- Detailed status messages

## Technical Features

✔ **ISO 11783-6 compliant** (F.10)
✔ **Flexible Signal Control**: Frequency, Duration, Repetitions
✔ **16-bit Time Resolution** (0-65535 ms)
✔ **255 Repetitions** maximum

## Standard Parameter Ranges

| Parameter | Range | Typical Value |
-----------------|------------|----------------|
| Frequency | 0-65535 Hz | 2000 Hz |
| Duty Cycle | 0-65535 ms | 200 ms |
| Shutdown time | 0-65535 ms | 100 ms |
| Repetitions | 1-255 | 3 |

## Return codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Success |
| -6 | VT_E_OVERFLOW | Invalid parameter values |
| -8 | VT_E_NOACT | VT in incorrect state |
| -128 | VT_E_HANDLE_INVALID | Invalid audio configuration |

## Application Scenarios

- **Warning Signals**: Audible alarm messages
- **Confirmation Tones**: Operator feedback
- **Voice Announcements**: Pre-recorded messages
- **Machine Status**: Audible status indicators

## ⚖️ Comparison with similar modules

| Feature | Q_CtrlAudioSignal | VtSoundManager | VtAudioAlert |
|---------------|-------------------|----------------|--------------|
| ISO Standard | ✔ | ✖ | ✖ |
| Parameterization| Full | Partial | Simple |
| Frequency Control | Yes | No | No |

## 🛠️ Related Exercises

* [Exercise_017](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_017.md)
* [Exercise_018](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_018.md)
* [Exercise_018a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_018a.md)

## Conclusion

The Q_CtrlAudioSignal block provides the reference implementation for VT audio control:

- **Flexible**: Fully configurable audio signals
- **Standards compliant**: Full ISO 11783-6 compatibility
- **Robust**: Proven technology in field devices

Essential for:

- Safety-critical warning signals
- User-friendly acoustic feedback
- Machines with complex audio status messages
