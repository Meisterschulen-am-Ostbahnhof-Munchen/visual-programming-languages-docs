# ARTimeOut
![ARTimeOut](https://user-images.githubusercontent.com/116869307/214142115-28b88284-c3b6-4c78-9145-6de372738f36.png)
* * * * * * * * * *
## Introduction
IEC 61499 is an international standard for modeling distributed industrial control systems. Within this standard, adapter types are an important component for defining reusable interfaces between function blocks. The **ARTimeOut** adapter (Adapter for Resettable Timeout) is an example of such an adapter, providing an interface for a resettable timeout service.
![ARTimeOut](ARTimeOut.svg)

## Structure of the ARTimeOut Adapter

The ARTimeOut adapter is specified as **AdapterType** in IEC 61499 and defines an interface for communication between a socket and a plug.

### Interface

The ARTimeOut adapter interface consists of:

- **Input Events**:
- **TimeOut**: This event is triggered by the SOCKET to indicate that the timeout has expired.
- **Output Events**:
- **START**: This event is triggered by the PLUG to start or reset the timeout. It is linked to the output variable **DT**, which defines the timeout duration.
- **STOP**: This event is triggered by the PLUG to stop the timeout.
- **Output Variable**:
- **DT (Duration Time)**: A time variable (TIME) that specifies the duration of the timeout.

### Service Behavior

The ARTimeOut adapter offers two service sequences:

1. **Timeout**:

- The PLUG sends a **START** event with a duration of **DT** to start the timeout.
- When the timeout expires, the SOCKET sends a **TimeOut** event back to the PLUG.

2. **NormalOperation**:

- The PLUG sends a **START** event with a duration of **DT** to start the timeout.
- The PLUG can send a **STOP** event to end the timeout prematurely.

## ARTimeOut Adapter Behavior

The ARTimeOut adapter enables the control of a timeout mechanism with the following functions:

1. **Start/Reset Timeout**:

- The **START** event starts or resets the timeout with the specified duration **DT**.

2. **Stop Timeout**:

- The **STOP** event terminates the timeout prematurely.

3. **Timeout Expiration**:

- When the timeout expires, the **TimeOut** event is triggered to notify the PLUG.

## Application Examples

The ARTimeOut adapter can be used in various industrial control applications, particularly in scenarios requiring a reliable and resettable timeout mechanism. Examples include:

- **Network Communication**: Monitoring response timeouts in distributed systems.
- **Machine Control**: Timeouts for command execution to detect hung processes.
- **Safety Systems**: Monitoring sensors to detect malfunctions when no updates are received.

## Conclusion

The ARTimeOut adapter is a useful tool within IEC 61499 to provide a standardized interface for resettable timeout services. Its clear separation between SOCKET and PLUG, along with defined service sequences, makes it ideal for integration into distributed control systems. The ability to start, stop, and notify when the timeout expires makes it a flexible solution for a wide range of industrial applications.