# GET_LTIME

![GET_LTIME](./GET_LTIME.svg)

* * * * * * * * * *
## Introduction
The function block **GET_LTIME** is used to read the current value of an LTIME variable and provide it as a buffered output value. It accesses the source via an InOut interface and makes the read value available at the output as soon as an event occurs. This enables controlled, one-time reading of a time variable.

## Interface Structure
### **Event Inputs**

| Event | Data Type | Comment |

|----------|----------|-----------|

| REQ | Event | Normal execution command. Associated with the input value IN. |

### **Event Outputs**

| Event | Data Type | Comment |

|----------|----------|-----------|

| CNF | Event | Execution confirmation. Connected to the outputs OUT and IN. |

### **Data Inputs**
This function block does not have traditional data inputs. Access to the source value is exclusively via the InOut variable.

### **Data Outputs**

| Name | Data Type | Comment |

|------|----------|-----------|

| OUT | LTIME | Buffered output value (initial value LT#0s). |

### **Adapter**
None.

## Functionality
This function block implements simple, event-driven copy logic:

1. An incoming **REQ** event triggers the execution of the internal algorithm.

2. The algorithm assigns the current value of the InOut variable **IN** to the output **OUT** (`OUT := IN;`).

3. After successful assignment, the output event **CNF** is sent to signal completion to the calling instance.

Thus, the value of the external LTIME variable is only read when the REQ event arrives and is buffered in the output until the next read.

## Technical Features

- **InOut Variable**: The source is accessed via an InOut interface, which represents a direct reference to an external variable. Changes to the external variable between two REQ calls are only applied during the next read operation.

- **Buffering**: The read value remains in the output OUT until another REQ event arrives. This protects against asynchronous changes to the source during processing.

- **Reading Back the Input**: The **CNF** event is connected not only to OUT but also to IN. This can be used in certain runtime environments to control the forwarding of the InOut value, but it has no additional functional significance in the standard behavior.

## State Overview
The function block is implemented as a SimpleFB and has exactly one internal state:

| State | Action | Output Event |

|---------|--------|------------------|

| REQ | Algorithm REQ (OUT := IN) | CNF |

After receiving **REQ**, the state is traversed once and the output is generated. There are no further states or branches.

## Application Scenarios

- **Timestamp Capture**: Freezing a current system time value (LTIME) once at a specific event, e.g., an alarm signal.

- **Synchronization of Time Measurements**: Reading a shared timer in an industrial controller to pass consistent time data to various downstream function blocks.

- **Buffering of Time Values** in data-driven architectures where an LTIME variable is used multiple times but must be read at precisely the same time.

## Comparison with Similar Function Blocks

- **GET_VALUE (for other data types)**: Functions analogously, but for scalar data types such as INT, REAL, etc. GET_LTIME is specialized for the LTIME data type.

- **Latch Function Blocks**: While latch blocks store and hold a value upon an event, GET_LTIME additionally generates an acknowledgment event and reads from an InOut variable instead of a normal data input.

- **MOVE Block**: A MOVE block also copies a value from an input to an output, but without event control and without InOut support. GET_LTIME offers an event-driven, buffered version.

## Conclusion
The **GET_LTIME** function block is a simple yet effective component for the controlled reading of an LTIME variable via an InOut interface. Its event-driven operation and buffering of the output value make it particularly suitable for time-critical applications where a consistent time value is required at a defined point in time. The clear interface and simple state logic facilitate integration into larger control applications.