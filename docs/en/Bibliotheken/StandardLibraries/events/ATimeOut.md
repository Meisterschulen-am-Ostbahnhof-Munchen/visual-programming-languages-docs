# ATimeOut
![ATimeOut](https://user-images.githubusercontent.com/116869307/214142228-09857ba5-6164-4597-bb66-8a99e74f4d14.png)

* * * * * * * * * *
## Introduction
The **ATimeOut** adapter is a standardized interface (AdapterType) according to IEC 61499 for implementing timeout services. It defines the communication between a service user (PLUG) and a time service provider (SOCKET). Unlike `ARTimeOut`, this adapter is designed for simple, non-retriggerable timeouts.
![ATimeOut](ATimeOut.svg)

## Structure of the ATimeOut Adapter
The ATimeOut adapter defines a clear separation of responsibilities between the control logic (Plug) and the timer (Socket).

### Interface

The interface is defined from the perspective of the **plug**:

- **Input Events (received from the socket)**:
- **Timeout**: Signals that the specified time has elapsed.
- **Output Events (sent to the socket)**:
- **START**: Initiates the timeout process. This event is associated with the variable **DT**.
- **STOP**: Terminates an ongoing timeout process.
- **Output Variables (sent to the socket)**:
- **DT (Duration Time)**: Defines the duration of the timeout (data type: TIME).

## Behavior and Service Sequences

The adapter supports two basic processes:

1. **Timeout Expiration**:

- The plug sends `START` with a value for `DT`.
- The socket processes the time and sends back `TimeOut` after the time expires.

2. **Premature Termination**:

- The plug sends `START`.
- Before the time expires, the plug sends `STOP`. The socket terminates the timer; no `TimeOut` event occurs.

## Technical Features
- **Non-retriggerable**: A repeated `START` during an ongoing timeout is ignored in the standard implementation (`E_TimeOut`).
- **Adapter Concept**: Enables clean encapsulation of the timing logic and simplifies the component network by reducing the number of connection lines.

## Application Examples
- **Monitoring Response Times**: Waiting for an acknowledgment (e.g., from a communication partner) within a fixed time window.
- **Process Monitoring**: Ensuring that a mechanical process is completed within the expected time.

## ⚖️ Comparison with ARTimeOut

| Feature | ATimeOut (this) | ARTimeOut |

|----------------|-------------------|-----------|

| Type | Adapter | Adapter |

| Retriggerable | No | Yes |

| Event START | Start Timer | Start/Reset Timer |

## Conclusion
The ATimeOut adapter provides a robust and simple interface for time-critical monitoring tasks in distributed control systems. It forms the basis for the function block `E_TimeOut`.
