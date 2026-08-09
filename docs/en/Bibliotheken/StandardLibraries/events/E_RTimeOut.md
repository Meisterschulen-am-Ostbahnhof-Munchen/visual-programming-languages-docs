# E_RTimeOut (Resettable Timeout Service)

![IEC 61499 Timeout Symbol](https://user-images.githubusercontent.com/113907528/204902807-7fadcd7d-d6e1-47c0-812e-f5c2d80f79e0.png)

* * * * * * * * * *
## Introduction

The **E_RTimeOut** is a special function block according to IEC 61499-2. It implements a resettable timeout service by internally using an E_RDELAY block.
![E_RTimeOut](E_RTimeOut.svg)

## Structure and Interfaces

### **Adapter Interface (Socket Perspective)**

The block uses a **socket** of type `ARTimeOut`. Since it is a socket, the signal directions are inverted compared to the adapter definition (plug):

- **Inputs (received from the socket)**:
- `START`: Starts or resets the internal timer.
- `STOP`: Stops the internal timer.
- `DT` (TIME): The delay time to use.
- **Output (sent to the socket)**:
- `TimeOut`: Signaled to the connected plug after the time has elapsed.

### **Internal Components**

- `DLY` (E_RDELAY): Core component for time control

## Functionality

1. **Timeout Initialization**:
- The timer starts when the `START` event occurs on the socket.
- Uses the configured `DT` value.
2. **Timeout Reset**:
- A new `START` event resets the running timer.
- Uses the new `DT` value.
3. **Timeout Termination**:
- The `STOP` event terminates the active timer.
4. **Timeout Triggering**:
- After the `DT` event expires, `TimeOut` event generated
- Signaled via the adapter socket

## Technical Features

✔ **Resettable Timeout Function**

✔ **Adapter-Based Interface** (ARTimeOut)

✔ **Internal E_RDELAY Implementation**

✔ **IEC 61499-2 Compliant**

## Application Scenarios

- **Network Communication**: Response Timeout Monitoring
- **Machine Safety**: Monitoring of Motion Periods
- **Process Control**: Time-Limited Operation Control
- **Device Control**: Watchdog Functionality

## ⚖️ Comparison with Similar Components

| Feature | E_RTimeOut | E_DELAY | E_TABLE |
|--------------|------------|---------|---------|
Reset Function | ✔️ | ❌ | ❌ |
Interface | Adapter | Direct | Direct |
Standard | 61499-2 | 61499-1 | 61499-1 |

## 🛠️ Related Exercises

* [Exercise_035b](../../../Uebungen/test_B/Uebungen_doc/Uebung_035b.md)]
* [Exercise_170](../../../Uebungen/test_B/Uebungen_doc/Uebung_170.md)]

## Conclusion

The E_RTimeOut block offers an elegant solution for timeout requirements in distributed control systems:

- Reusable adapter interface
- Flexible timeout configuration
- Reliable reset functionality

By internally utilizing the E_RDELAY block, it combines precise timing control with a robust architecture. Its standardized implementation according to IEC 61499-2 makes it particularly suitable for interoperable automation solutions.
