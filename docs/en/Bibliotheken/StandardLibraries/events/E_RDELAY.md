# E_RDELAY
![E_RDELAY Symbol](https://user-images.githubusercontent.com/113907528/204900519-829582bd-d9f3-4bee-934a-15dc393b4c34.png)

* * * * * * * * * *
## Introduction
The **E_RDELAY** (Reloadable Delay) is an extended delay function block according to IEC 61499, which, unlike the simple E_DELAY, enables a reloadable and abortable event delay. Developed under the EPL-2.0 license.
![E_RDELAY](E_RDELAY.svg)

## Interface Structure

### **Event Inputs**
- `START`: Starts/Resets the delay (with DT parameter)
- `STOP`: Cancels the active delay

### **Event Outputs**
- `EO`: Delayed output event

### **Data Inputs**
- `DT` (Delay Time): Delay duration (TIME data type)

## Operating Principle

1. **Delay Start**:

- On the `START` event, the timer starts with the configured `DT` time
- New `START` resets the timer during an active delay

2. **Delay Termination**:

- `STOP` immediately terminates the active delay
- No `EO` event is generated

3. **Delay Completion**:

- `DT` is triggered once after exactly `EO`
- Immediate triggering occurs if DT ≤ T#0s

## Service Sequences (according to the XML specification)

1. **event_delay**:

- Normal delay with START → EO

2. **delay_canceled**:

- START followed by STOP (no EO)

3. **no_multiple_delay**:

- Multiple START events trigger only one EO

## Technical Special Features

✔ **Reloadable Delay** (Reset Function)
✔ **Cancellable** during runtime
✔ **Deterministic Timing Behavior**
✔ **Real-Time Capable** Implementation

## Application Scenarios
- **Machine Safety**: Delayed Shutdown Sequences
- **Process Control**: Time-Controlled State Transitions
- **Alarm Systems**: Fault Message Delay
- **Robot Control**: Motion Sequence Timing

## ⚖️ Comparison with E_DELAY

| Feature | E_RDELAY | E_DELAY |

|---------------|----------|---------|

| Reset Function | ✔️ (via START) | ❌ |

| Multiple Triggers | Only 1 EO | Only 1 EO |

| Service Sequences | 3 defined | 1 defined |

## 🛠️ Related Exercises
* [Exercise_018a](../../../Uebungen/test_B/Uebungen_doc/Uebung_018a.md)]

## Conclusion

The E_RDELAY function block extends the classic delay function with essential, industry-ready features:

- Flexible reconfiguration during operation
- Safe termination of time sequences
- Standardized service interfaces

Thanks to its XML-based specification, the function block is particularly well-suited for use in distributed control systems. The implemented version offers reliable timing control for critical automation processes.
