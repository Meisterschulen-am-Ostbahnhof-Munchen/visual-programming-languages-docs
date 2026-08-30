# E_TimeOut

![E_TimeOut](https://user-images.githubusercontent.com/116869307/214142822-3b167702-112f-454a-a42f-62c5f7454561.png)

* * * * * * * * * *
## Introduction

The **E_TimeOut** is a standards-compliant function block (IEC 61499-1) for implementing timeout services. Version 1.0 offers simple yet effective timeout functionality through internal use of an E_DELAY block. The **E_TimeOut** is a composite function block. Within the network of a composite function block, each adapter added to its interface is represented by an adapter block, which looks like a function block. The interface elements of this adapter block are connected like a function block.
![E_TimeOut](E_TimeOut.svg)

## Interface Structure

### **Adapter Interface (Socket Perspective)**

The block uses a **socket** of type `ATimeOut`. Since this is a socket, the signal directions are inverted compared to the adapter definition (plug):

- **Inputs (received from the socket)**:
- `START`: Starts the internal timer.
- `STOP`: Stops the internal timer.
- `DT` (TIME): The delay time to be used.
- **Output (sent to the socket)**:
- `TimeOut`: Signaled to the connected plug after the specified time has elapsed.

### **Internal Components**

- `DLY` (E_DELAY): Core component for time control

## Functionality

1. **Timeout Initialization**:
- Upon a `START` event at the socket, the timer starts with the configured `DT` value.
- Any further `START` event while the timer is running is ignored.
2. **Timeout Termination**:
- A `STOP` event immediately terminates the active timer. No `TimeOut` event is generated.
3. **Timeout Trigger**:
- After `DT` expires, the `TimeOut` event is generated once.

## Technical Features

✔ **Adapter-based** interface (`ATimeOut`).

✔ **Simple, non-retriggerable timeout logic**.

✔ **Deterministic** timing behavior.

## Application Scenarios

- **Network Communication**: Monitoring for a response within a fixed timeframe. When the response arrives, the timer is canceled via `STOP`.
- **Device Control**: Simple watchdog functions that do not require resetting.
- **Process Monitoring**: Ensuring that a process step does not exceed a maximum duration.

## ⚖️ Comparison with E_RTimeOut

| Feature | E_TimeOut (this one) | E_RTimeOut |
|---------------|-----------|-----------|
| Internal Block | E_DELAY | E_RDELAY |
| `START` on running timer | Ignored | Restarts timer |
| Adapter Type | ATimeOut | ARTimeOut |

## 🛠️ Related exercises

- [Uebung_035](../../../Uebungen/test_B/Uebungen_doc/Uebung_035.md)
- [Uebung_035a](../../../Uebungen/test_B/Uebungen_doc/Uebung_035a.md)
- [Uebung_035a1_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a1_AX.md)
- [Uebung_035a2](../../../Uebungen/test_B/Uebungen_doc/Uebung_035a2.md)
- [Uebung_035a2_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
- [Uebung_035a3](../../../Uebungen/test_B/Uebungen_doc/Uebung_035a3.md)
- [Uebung_035a3_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a3_AX.md)
- [Uebung_035c](../../../Uebungen/test_B/Uebungen_doc/Uebung_035c.md)
- [Exercise_036](../../../Uebungen/test_B/Uebungen_doc/Uebung_036.md)
- [Exercise_037](../../../Uebungen/test_B/Uebungen_doc/Uebung_037.md)
- [Exercise_038](../../../Uebungen/test_B/Uebungen_doc/Uebung_038.md)
- [Exercise_038_AX](../../../Uebungen/test_AX/Uebungen_doc/Uebung_038_AX.md)
- [Exercise_039](../../../Uebungen/test_B/Uebungen_doc/Uebung_039.md)
- [Exercise_039a](../../../Uebungen/test_B/Uebungen_doc/Uebung_039a.md)

## Conclusion

The E_TimeOut block provides a robust basic implementation for non-retriggerable timeout requirements. It is ideal for cases where a timer is started and should either run to completion or be explicitly aborted. For scenarios that require "re-triggering" or resetting the timer (such as a watchdog that is periodically "kicked"), the `E_RTimeOut` block is the better choice.
