# Q_LockUnlockMask
![Q_LockUnlockMask](https://user-images.githubusercontent.com/116869307/214148004-903a6233-7e3e-43eb-a611-03d82d451bf4.png)

* * * * * * * * * *
## Introduction
The **Q_LockUnlockMask** is a standards-compliant function block for controlling the locking state of masks in virtual terminals, developed under the EPL-2.0 license. Version 1.0 implements the ISO 11783-6 (Part 6 - F.46) specification for VT systems from version 4 onwards.
![Q_LockUnlockMask](Q_LockUnlockMask.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request
- `REQ`: Lock/Unlock Request

### **Event Outputs**
- `INITO`: Initialization Acknowledgement
- `CNF`: Operation Acknowledgement

### **Data Inputs**
- `u8LockCmd` (USINT): Lock Command (0=Unlock, 1=Lock)
- `u16MaskId` (UINT): Mask Object ID
- `u16LockTimeoutMs` (UINT): Timeout in ms (0 = no timeout)

### **Data Outputs**
- `STATUS` (STRING): Operational status message
- `u8OldLockCmd` (USINT): Previous lock state
- `u16OldMaskId` (UINT): Previous mask ID
- `u16OldLockTimeoutMs` (UINT): Previous timeout
- `s16result` (INT): ISO-compliant result code

## Functionality

1. **Initialization**:

- `INIT` without parameters
- `INITO` confirms operational readiness

2. **Mask Locking**:

- `REQ` with lock command, mask ID, and timeout
- Controls the screen refresh of the mask
- `CNF` provides operating status and previous values

3. **Timeout Behavior**:

- Automatic unlocking after expiration

## Technical Features

✔ **ISO 11783-6 compliant** (F.46)
✔ **Exclusive to VT Version 4+**
✔ **Time-controlled locking** (millisecond accuracy)
✔ **Bidirectional control** (lock/unlock)

## Command Reference

| u8LockCmd | Function |
|-----------|------------------------------|
| 0 | Unlock mask |
| 1 | Lock mask |

## Return Codes (s16result)

| Code | Constant | Meaning |
|------|-------------------------|------------------------------------|
| 0 | VT_E_NO_ERR | Successful execution |
| -6 | VT_E_OVERFLOW | Buffer overflow |
| -8 | VT_E_NOACT | VT not ready |
| -21 | VT_E_NO_INSTANCE | No VT client available |
| -129 | VT_E_ISO_INSTANCE_INVALID | Invalid VT instance |
| -130 | VT_E_NOT_ALIVE | VT not active |

## Application Scenarios
- **Critical Operations**: Locking During Data Transfer
- **User Interaction**: Temporary Disabling
- **Energy Efficiency**: Reducing Display Updates
- **Diagnostic Logs**: Targeted Recording

## ⚖️ Comparison with Similar Components

| Feature | Q_LockUnlockMask | VtMaskControl | VtScreenLock |
---------------|------------------|----------------|--------------|
| ISO Standard | ✔ | ✖ | ✖ |
| Timeout | ✔ | ✖ | ✔ |
| Mask-Specific | ✔ | ✔ | ✖ |
| Bidirectional | ✔ | ✖ | ✔ |

## Conclusion

The Q_LockUnlockMask module offers precise control over mask updates:

- **High Performance**: Minimal system load
- **Reliable**: Time-controlled automation
- **Secure**: Exclusive access protection

Essential for:

- Process-critical applications
- Resource-optimized systems
- High-availability VT solutions
