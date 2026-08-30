# F_NOW_MONOTONIC

![F_NOW_MONOTONIC](https://github.com/user-attachments/assets/ae1652e1-fcca-44f4-aa16-c1cfa5a794cd)

* * * * * * * * * *

## Introduction

F_NOW_MONOTONIC` is an IEC 61499-compliant function that returns a monotonic timestamp.
Unlike the system time (`NOW`), this time is independent of external changes (e.g., time zones or NTP updates) and is therefore ideally suited for time-critical control applications or performance measurements.

The function serves as a wrapper for the ST function `NOW_MONOTONIC()`.

---

## Interface Structure

### **Event Inputs**

- **REQ** (Trigger):

Starts the execution of the function. Upon receipt of this event, the current monotonic timestamp is calculated and output via `CNF`.

### **Event Outputs**

- **CNF** (Acknowledgement):

Signals the completion of the operation. The event is output along with the calculated time value (`TIME`).

### **Data Inputs**

- *None* – The function requires no additional input parameters.

### **Data Outputs**

- **TIME** (Output Variable):

Return value of type `TIME`, representing the current value of the monotonic clock.

*Example:* `T#123456ms` (depending on the hardware/OS reference point).

---

## Operation

1. **Initialization**:

The function is activated by the event `REQ`. Resources are not persistently stored, as this is a stateless computation.

1. **Macro Execution**:

- Calls the system-level function `NOW_MONOTONIC()`.
- Assigns the return value to the output variable `TIME`.
- Triggers the event `CNF`.
1. **Error Handling**:

- No specific error handling, as the function has no external dependencies.
- In case of hardware/OS errors, the return value is undefined.

--

## Technical Features

- **Monotonic Time**:

Guaranteed continuously increasing values, even with system time changes.

*Note:* The reference point is hardware-dependent (e.g., system startup).

- **License**: Eclipse Public License 2.0 (EPL-2.0).

---

## Return Codes

- **Success**: Valid `TIME` value (e.g., `T#42s`).
- **Error**: No explicit error codes, but undefined values in case of system errors.

--

## Application Scenarios

1. **Real-time Measurements**:
Runtime analysis of control cycles unaffected by system time changes.

2. **Synchronization**:
Timestamps for logging in distributed systems.

3. **Timeout Control**:

Reliable timers for critical processes.

--

## ⚖️ Comparison with Similar Function Blocks

| Function | `F_NOW_MONOTONIC` | `NOW()` | `NOW_SYSTEM()` |
| --------------------- | ----------------------- | ----------------------- | ----------------------- |
| **Time Source** | Monotonous (Hardware) | System Time | System Time (UTC) |
| **Influenceable** | No | Yes (NTP, Time Zone) | Yes (NTP) |
| **Use Case** | Real-time Measurements | General Timestamps | Global Timestamps |

---

## Conclusion

F_NOW_MONOTONIC` is a lean yet essential component for applications requiring a reliable and monotonous time source.

Its close connection to the hardware and its independence from system time changes make it particularly suitable for industrial real-time applications.

Integration with Eclipse 4diac ensures compatibility with modern automation solutions.

*Note:* For absolute time references, `NOW_SYSTEM()` should be used.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
