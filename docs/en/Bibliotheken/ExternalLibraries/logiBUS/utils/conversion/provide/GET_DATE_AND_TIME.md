# GET_DATE_AND_TIME
![GET_DATE_AND_TIME](./GET_DATE_AND_TIME.svg)

* * * * * * * * * *
## Introduction
The **GET_DATE_AND_TIME** function block is used to read a value of type `DATE_AND_TIME` from a variable declared as InOut and provide it as a buffered output. On each request, the current value of the source (InOut variable) is copied to the output.
## Interface Structure

### **Event Inputs**

| Event | With | Description |

|----------|-----|--------------|

| REQ | IN | Normal execution request; triggers the reading of the source data. |

### **Event Outputs**

| Event | With | Description |

|----------|------------------|--------------|

| CNF | OUT, IN | Confirmation of execution; signals that the output has been updated. |

### **Data Inputs**

| Name | Type | Description |

|------|---------------|--------------|

| IN | DATE_AND_TIME | InOut variable as the data source. It is read but not modified. |

### **Data Outputs**

| Name | Type | Description |

|------|---------------|--------------|

| OUT | DATE_AND_TIME | Buffered output value that is taken from the InOut source on every REQ. |

### **Adapter**

None.

## Functionality

The component has a simple internal state **REQ**. When this state occurs (triggered by the event `REQ`), the following algorithm is executed:

OUT := IN;

The event `CNF` is then sent. The value of the InOut variable `IN` is not modified; it is simply read and copied to the output `OUT`. Thus, the function block acts as a **buffer** for any `DATE_AND_TIME` value.

## Technical Features
- The use of an **InOut variable** (`IN`) allows direct access to an external variable without having to declare it as a separate input or output. The function block accesses it in read mode.
- The output `OUT` stores the value present at the time of `REQ`. If the source changes between two `REQ` calls, the new value is only applied with the next `REQ` call (buffered provisioning).
- This is a **simple function block** (SimpleFB) without complex state management – only a single execution state.

## State Overview

| State | Action | Output Event |

|---------|--------|-----------------|

| REQ | `OUT := IN;` | CNF |

There is no initial state or other states; the function block waits for the `REQ` event and immediately executes the algorithm.

## Application Scenarios
- **Timestamp Acquisition**: Retrieving the current time from a system clock, provided as an InOut variable, at a defined control point.
- **Buffering of Date/Time Values**: Temporarily storing a current date/time value for later processing steps.
- **Synchronization**: Transferring a common time value from a central source to various function blocks.

## Comparison with Similar Function Blocks
- **GET_DATE_AND_TIME**, unlike function blocks such as `E_GET_TIME` (real-time clock query) or `TIME_GET` (current system time): This function block does not use a built-in clock but reads from any InOut variable. This makes it more flexible, e.g., for accessing application-specific time values.

**GET_DATE_AND_TIME** Compared to a simple assignment block (e.g., `MOVE` with `DATE_AND_TIME`), it offers an event-driven, explicit request and explicit acknowledgment (`REQ`/`CNF`), which is advantageous for time-critical control applications.

## Conclusion

**GET_DATE_AND_TIME** is a lean, clearly structured function block that allows reading and buffering a `DATE_AND_TIME` value from an InOut variable. Its ease of use and explicit event control make it a useful tool for reliably acquiring time data in automation applications.
