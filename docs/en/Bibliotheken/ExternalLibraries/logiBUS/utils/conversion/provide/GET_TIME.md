# GET_TIME
![GET_TIME](./GET_TIME.svg)

* * * * * * * * * *
## Introduction
The function block **GET_TIME** allows you to read a TIME value from an InOut variable and provide it as a buffered output value. It serves as a simple interface for incorporating an external time value into the block structure.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment | With Variables |
|------|-----|------------|---------------|
| REQ | Event | Normal Execution Request | IN |

### **Event Outputs**

| Name | Type | Comment | With Variables |
|------|-----|-----------|---------------|
| CNF | Event | Execution Confirmation | OUT, IN |

### **Data Inputs**
No dedicated data inputs available.

### **Data Outputs**

| Name | Type | Comment | Initial Value |
|------|-----|-----------|-------------|
| OUT | TIME | Buffered Output Value | T#0s |

### **Adapters**
No adapters available.

## Functionality
**GET_TIME** implements a simple, event-driven process. An event at the **REQ** input triggers the execution of the algorithm. The current value of the InOut variable **IN** is copied to the data output **OUT** and temporarily stored. An event is then generated at the output **CNF** to acknowledge the successful transfer. The InOut variable **IN** serves solely as a readable source and retains its value.

## Technical Features
- The variable **IN** is declared as **InOut**. It can be externally linked to another variable or output without the function block accessing it for writing. This allows for flexible integration with external timers or signals.
- The output **OUT** buffers the read value. After a **REQ** event, the current **IN** value is available at the output until the next request.
- The function block does not have its own timer or buffer for delays.

## State Overview

| State | Description | Action Performed |
|---------|--------------|-------------------|
| REQ | Waits for an event at the **REQ** input. Upon receipt, the algorithm is executed and a **CNF** event is sent. | `OUT := IN;` |

## Application Scenarios
- **Time Measurement**: Acquisition of a current system time (e.g., `TIME()` or a clock signal) into an output for further processing.
- **Signal Forwarding**: Buffered forwarding of an external TIME signal to decouple asynchronous changes in the source from the rest of the process.
- **Initialization**: Setting a start time value in a control logic.

## Comparison with Similar Function Blocks
Compared to a pure **MOVE** function block for TIME data, **GET_TIME** uses an **InOut** interface, which allows a direct connection to the source even without an additional data input. It is specifically designed for TIME values and does not offer a general data copy function. Other time function blocks such as **E_TIME** or **TIME_IN** often work with their own timer or event counter, while **GET_TIME** passively retrieves an external value.

## Conclusion

**GET_TIME** is a lean, clear function block for reading and buffering a TIME value. Its simple event handling and the use of an InOut variable make it particularly suitable for scenarios in which an external time value needs to be selectively incorporated into control logic.
