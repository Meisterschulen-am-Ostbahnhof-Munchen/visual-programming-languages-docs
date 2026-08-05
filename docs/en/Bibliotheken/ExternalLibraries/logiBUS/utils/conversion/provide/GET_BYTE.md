# GET_BYTE
![GET_BYTE](./GET_BYTE.svg)

* * * * * * * * * *
## Introduction
The **GET_BYTE** function block is used to read a variable `BYTE`, which is provided via an **InOut** parameter. The read value is buffered at the output `OUT` and is available after execution. This function block is typically used to retrieve a current `BYTE` value from an external source (e.g., a shared data area) without modifying the source itself.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Variables |

|------|-------|-------------------------------|---------------|

| REQ | Event | Normal execution trigger | IN |

### **Event Outputs**

| Name | Type | Comment | With variables |

|------|-------|------------------------------|---------------------|

| CNF | Event | Execution confirmation | OUT, IN |

### **Data Inputs**

This function block does not have traditional data inputs, but instead uses an **InOut parameter** that can be used as both an input and an output:

| Name | Type | Initial value | Comment |

|------|--------|--------------|------------------------------------|

| IN | BYTE | 0 | Source variable (read via InOut) |

### **Data Outputs**

| Name | Type | Initial value | Comment |

|------|--------|--------------|-----------------------------------------|

| OUT | BYTE | 0 | Buffered output value |

### **Adapters**

No adapters available.

## Functionality

The function block is activated by an event at input `REQ`. The current value of the variable at the **InOut** parameter `IN` is then read and copied to output `OUT`. Finally, event `CNF` is triggered, confirming successful execution. The algorithm is very simple:

OUT := IN;
Since `IN` is declared as an InOut parameter, the calling application must provide a BYTE variable that can be both read and (in the case of other function blocks) written. However, `GET_BYTE` only performs a read operation.

## Technical Features
- **InOut Parameter**: The function block accesses an external variable directly without connecting it via a separate data input. This enables efficient, direct data binding and saves network resources.
- **Buffered Output**: The read value is buffered in `OUT` and remains until the next execution – even if the source variable changes in the meantime.
- **No State Machine**: The function block consists of a single state, which makes the implementation lean and deterministic.

## State Overview

The function block has exactly one internal state:

| State | Description | Output Event |

|---------|----------------------------------------------------------|------------------|

| REQ | No waiting; immediate execution of the read operation | CNF |

There are no wait states or branches.

## Application Scenarios
- **Reading Configuration Values**: A `BYTE` value from a central data block (e.g., a global configuration) is transferred to a local buffer.
- **Synchronization Between Function Blocks**: Another function block writes a `BYTE` value to a shared InOut variable, and `GET_BYTE` reads this value as needed.
- **Safe Data Transfer**: The buffered output prevents subsequent logic from reacting to a changing source value – it always works with the value valid at the time of the request.

## Comparison with Similar Function Blocks

| Function Block | Description | Difference to GET_BYTE |

|------------|--------------------------------------------------------|--------------------------------------------------------------|

| GET_VALUE | Reads a value from an InOut parameter (type-independent) | GET_BYTE is specific to the data type `BYTE` and is therefore more type-safe. |

| MOVE | Copies a value from an input to an output | MOVE requires separate inputs and does not provide a buffer – GET_BYTE uses InOut. |

| READ_BYTE | Reads a byte via a hardware address | GET_BYTE operates at the variable level, not at hardware addresses. |

## Conclusion

**GET_BYTE** is a simple yet useful building block for reading a `BYTE` value from an external source via an InOut parameter and buffering it. Thanks to its streamlined design (one state, minimal interface), it is particularly suitable for resource-critical applications and for integration into existing communication or storage concepts where direct access to a shared variable is desired.
