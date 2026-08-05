# GET_STRING
![GET_STRING](./GET_STRING.svg)

* * * * * * * * * *
## Introduction
The function block `GET_STRING` is used to read a string value from an InOut variable and provide it as a buffered output. It is typically used to capture the current value of an external variable at a specific time and make it available for further processing.
## Interface Structure
### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| REQ | Event | Normal execution request. Triggers the reading of the InOut variable. |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| CNF | Event | Confirmation of execution. Sent after the value has been read and passed to the output. |

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| IN | STRING | InOut variable that serves as the source. Its current value is read and buffered on REQ. |

### **Data Outputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| OUT | STRING | Buffered output value. Contains the string read from IN at the time of the last REQ. |

### **Adapter**
None.

## Functionality
The function block has a state `REQ`. An incoming event at `REQ` executes the algorithm, which copies the value of the InOut variable `IN` directly to the output `OUT`. Then, the event `CNF` is sent. The InOut variable `IN` is not modified, but only read. The buffered value remains until another `REQ` reads a new value.

## Technical Features
- The variable `IN` is declared as **InOut**, meaning it is passed by reference. This allows direct access to the memory of the passed string variable without first copying the value locally.
- The function block is specialized for the data type `STRING`. Corresponding variants (e.g., `GET_ANY`) are required for other data types.
- No initial values are set. The output `OUT` is undefined after the first cycle until `REQ` has been received.

## State Overview

The function block has a single state:

| State Name | Description |
| State Name | Description | |--------------|--------------|
| REQ | Waits for an event at `REQ`. Executes the algorithm (copies `IN` → `OUT`) and sends `CNF`. |

There are no start or end states; the block returns to state `REQ` after each iteration.

## Application Scenarios
- **Caching**: A string value from an external source (e.g., a data block) is sampled and cached for subsequent processing without affecting the source.
- **Logging**: Snapshot of a changing string at specific event times.
- **Synchronization**: Provides a consistent value for multiple downstream blocks when the source is to be read from several locations simultaneously.

## Comparison with similar blocks
- **MOVE / ASSIGN**: Simple assignment blocks for arbitrary types, often without explicit event handling. `GET_STRING`, on the other hand, is specifically designed for `STRING` and uses an InOut interface.
- **GET_ANY**: A generic block for arbitrary data types. `GET_STRING` is type-safe and avoids parameterization overhead for reading strings.
- **READ_REF**: Also a block for passing by reference, but often implemented as a function block without event handling. `GET_STRING` integrates event handling and is therefore suitable for sequential control systems.

## Conclusion

GET_STRING` is a simple yet specialized function block for buffering a string value from an InOut variable. Its event-driven approach allows for precise use in time-critical processes. Using an InOut interface saves memory and processing time, as no value copy is required on the caller side. For most applications that need to sample strings, this function block offers a clean and resource-efficient solution.
