# GET_LWORD

![GET_LWORD](./GET_LWORD.svg)

* * * * * * * * * *

## Introduction

The **GET_LWORD** function block is used for the consistent retrieval of an LWORD value from an **InOut variable**. It buffers the current value of the source variable and makes it available at the output `OUT`. This is particularly useful when the content of a shared variable needs to be saved at a defined point in time without being affected by subsequent write operations from other function blocks.

## Interface Structure

### **Event Inputs**

| Event | Description |
|---|---|
| `REQ` | Starts the read operation. The current value of `IN` is transferred to `OUT`. |

### **Event Outputs**

| Event | Description |
|---|---|
| `CNF` | Confirms successful completion of the operation. Triggered after the copy operation. |

### **Data Inputs**

This function block does not have traditional data inputs but uses an **InOut parameter** that functions as a bidirectional interface.

### **Data Outputs**

| Variable | Type | Description |
|---|---|---|
| `OUT` | `LWORD` | Buffered output value. Contains the copy of the value of `IN` at the time of the last `REQ`. Initial value = `0`. |

### **Adapter**

None available.

## Functionality

The function block implements a simple sequence:

1. **Event `REQ`** triggers the execution of algorithm `REQ`.
2. **Algorithm `REQ`**: The instruction `OUT := IN;` copies the current value of the InOut variable `IN` to the output buffer `OUT`. The InOut interface ensures direct read access to the source variable.
3. After the assignment is complete, the output event **`CNF`** is sent. The event outputs `CNF` are linked to both `OUT` and `IN`, allowing subsequent function blocks to use both the new value and the reference to the InOut variable.

Buffering ensures that the value of `OUT` remains stable during a run cycle, even if the source `IN` is modified by other function blocks in the meantime.

## Technical Features

- **InOut Parameter**: The variable `IN` is declared as `InOutVar`. This allows the function block to directly access an external memory location without requiring an additional connection as a data input. The function block reads this value but does not modify it.
- **Simple State Logic**: The component has only a single state, `REQ`. Therefore, exactly one action is executed for each `REQ` event – execution is deterministic and instantaneous.
- **Variable Type**: `LWORD` (64-bit logarithmic or bifield value) is treated as a safe buffer.

## State Overview

| State | Description |
|---|---|
| `REQ` | Initial and only state. Upon receiving `REQ`, the algorithm is executed and `CNF` is sent. The state is retained, so the process is repeated upon receiving `REQ` again. |

## Application Scenarios

- **Consistent Sampling**: A `GET_LWORD` function block can be used to read the value of a cyclically updated sensor at a defined time and store it for further processing (e.g., a calculation chain).
- **Preventing Race Situations**: In systems with multiple parallel function blocks accessing the same memory location, buffering prevents a function block from receiving an inconsistent value in the interim.
- **Data Logging**: A snapshot can be created using `GET_LWORD` before a measurement is stored in a log memory.

## Comparison with Similar Components

- **`GET_INT`, `GET_DWORD`, `GET_BOOL`** etc.: These components follow the same principle but differ in data type. `GET_LWORD` is specifically designed for 64-bit values.
- **Simple Input Variable**: A pure data input would require the connecting component to buffer the value itself or constantly update the connection. The InOut mechanism provides a reference to the original, which is more direct and memory-efficient in some architectures.
- **`MUX` Components**: A multiplexer could also select a value but requires additional control lines. `GET_LWORD` is optimized for one-time, deterministic reading.

## Conclusion

The function block `GET_LWORD` is a simple yet effective building block for the safe and time-controlled querying of an InOut variable of type `LWORD`. Its minimal state machine and direct copy logic make it ideal for real-time applications requiring consistent data retrieval. By utilizing the InOut concept, efficient coupling to existing memory locations is achieved without increasing the complexity of the connection structure.
