# GET_DATE
![GET_DATE](./GET_DATE.svg)
* * * * * * * * * *
## Introduction
The **GET_DATE** function block reads a DATE value from an InOut variable and provides it as a buffered output. When requested by an event, the current value of the source is copied into an internal buffer and then output to the output as well as to the InOut variable itself.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment | With Variables |

|------|-----|-----------|----------------|

| REQ | Event | Normal Execution Request | IN |

### **Event Outputs**

| Name | Type | Comment | With Variables |

|------|-----|-----------|----------------|

| CNF | Event | Execution Confirmation | OUT, IN |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| IN | DATE | Source Variable (InOut) |

### **Data Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| OUT | DATE | Buffered Output Value |

| IN | DATE | Source Variable (InOut) – also output with CNF |

### **Adapters**
No adapters available.

## Functionality
The function block has a simple execution state **REQ**:

1. An incoming event at the **REQ** input triggers processing.

2. The internal algorithm copies the current value of the InOut variable **IN** to the output signal **OUT**.

3. Subsequently, the **CNF** event is sent. This passes both the value of **OUT** and the (unchanged) value of **IN** to the output.

The functionality corresponds to a simple value transfer without further processing or state storage across multiple calls.

## Technical Features
- The use of an **InOut** variable allows direct access to an external variable without declaring a separate data input.
- Buffering occurs only during the execution of the algorithm; the current value of **IN** is read again with each new **REQ**.
- The function block is implemented as a **SimpleFB** and has no internal state transitions – processing is purely combinatorial in a single step.

``` ## State Overview
The function block consists of exactly one state:

- **REQ**: Upon entering this state, the algorithm that converts **OUT** to **IN** is executed, and the **CNF** event is sent.

There are no other states or conditional transitions.

## Application Scenarios
- **Reading a Global Date**: When a system time or date needs to be read from a central variable and used locally.
- **Buffering for Subsequent Processing**: To hold a DATE value at a specific point in time and pass it to other function blocks.
- **Cascading InOut Accesses**: In combination with other function blocks that access the same InOut variable to ensure consistent data.

## Comparison with Similar Function Blocks
- **GET_BOOL**, **GET_INT**, **GET_STRING**, etc.: These function blocks operate on the same principle but with different data types. They all use an InOut variable as a source and a buffered output.
- **SET_DATE**: The counterpart – it writes a value to an InOut variable instead of reading it.
- All these function blocks have a simple structure and are suitable for standardized access to shared data.

## Conclusion

**GET_DATE** is a minimalist yet useful function block for reading a DATE value via an InOut variable. Its simple state logic and direct value copying make it reliable and easy to understand. It is particularly suitable for modular automation solutions where data needs to be exchanged between function blocks using a shared variable.