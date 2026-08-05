# GET_WSTRING
![GET_WSTRING](./GET_WSTRING.svg)

* * * * * * * * * *
## Introduction
The function block **GET_WSTRING** is used to read a WSTRING variable via an InOut parameter and provides the buffered value as a data output. It is typically used to transfer an external WSTRING value into the internal processing of an application module without modifying the original value.
## Interface Structure
### **Event Inputs**

| Event | Data Type | Description |
|----------|----------|--------------|
| REQ | Event | Normal execution request – triggers the reading of the InOut variable. |

### **Event Outputs**

| Event | Data Type | Description |
|----------|----------|--------------|
| CNF | Event | Confirmation of execution – sent after successful copying. |

### **Data Inputs**

| Variable | Data Type | Description |
|----------|----------|--------------|
| IN | WSTRING | InOut source variable whose value is read. (The variable is not modified.) |

### **Data Outputs**

| Variable | Data Type | Description |
|----------|-----------|--------------|
| OUT | WSTRING | Buffered output value – contains the content of IN read at the time of the REQ event. |

### **Adapter**
No adapters available.

## Functionality
The function block has a single real-time step (EC state) called `REQ`. As soon as a pulse arrives at the **REQ** event input, the defined algorithm is executed:

1. The current value of the InOut variable **IN** is read and directly assigned to the output variable **OUT** (`OUT := IN`).

2. The **CNF** event is then triggered to signal successful transfer to the calling network.

The InOut variable remains unchanged; only a read access takes place.

## Technical Features
- **Input/Output Usage**: The variable `IN` is formally declared as `InOut`. This allows the function block (FB) to access the memory address of the connected source without requiring a separate input variable. The variable can therefore be written to externally as well as read from within the FB.
- **Buffered Output**: The value of `OUT` remains stable until the FB is updated by another **REQ**. This ensures that downstream parts of the application always have access to a consistent value.
- **Type Consistency**: The FB works exclusively with the data type `WSTRING`. Separate function blocks (e.g., `GET_STRING`, `GET_DINT`) are required for other data types.

## State Overview
The FB has only one active state:

| State | Description |
|---------|--------------|
| REQ | Initial and operating state. The algorithm is executed and a CNF is sent on every **REQ** event. There are no further branches or wait states. |

## Application Scenarios
- **Data retrieval from an external WSTRING source** – e.g., reading a global configuration string or a WSTRING value provided by another function block.
- **Decoupling of read and write accesses** – The value from a shared variable can be safely buffered before being processed further in the internal logic.
- **Implementation of a "Get" function block** in an InOut-based architecture, as commonly used in **EC-61499** networking.

## Comparison with Similar Function Blocks

| Function Block | Data Type | Special Feature |
|----------|----------|--------------|
| GET_STRING | STRING | Analog function block for ASCII strings (not Unicode). |
| GET_DINT | DINT | For 32-bit integers. |
| FORCE | Any type | Forces a value regardless of the source, often with an additional reset mechanism. |

**GET_WSTRING** differs from these by its specific support for the wide character type (WSTRING), used for Unicode strings (UTF-16). It is a simple function block limited to reading and buffering, with no side effects.

## Conclusion

The **GET_WSTRING** function block is a lean, easy-to-understand function block that performs a fundamental task in IEC 61499 environments: the safe reading of a WSTRING InOut variable and the provision of a buffered output value. Its simple structure and the absence of state branches make it ideal for use in data-driven control tasks where values from an external source need to be retrieved once or cyclically.
