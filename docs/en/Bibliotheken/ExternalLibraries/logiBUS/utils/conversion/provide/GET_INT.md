# GET_INT

![GET_INT](./GET_INT.svg)

* * * * * * * * * *
## Introduction

The **GET_INT** function block is used to read the current value of an INT variable (defined as an InOut parameter) and provide it as a buffered value at the output. Buffering occurs with each execution cycle, ensuring the output value remains stable until the next request.
## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| **REQ** | Normal execution request; triggers the reading of the InOut variable **IN**. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| **CNF** | Execution confirmation; indicates that the value of **IN** is buffered and available at output **OUT**. |

### **Data Inputs**

– *No standalone data inputs available.*

The input value is provided via the InOut parameter **IN** (see next section).

### **Data Outputs**

| Output | Type | Description |
|---------|-----|--------------|
| **OUT** | INT | Buffered output value containing the last read value from **IN**. Initial value: 0. |

### **Adapters**

– *No adapters available.*

### **InOut Variables (Implicit)**

| Variable | Type | Description |
|----------|-----|---------------|
| **IN** | INT | Source of the value to be read. Can be used as both input and output (read-only here). Initial value: 0. |

## Functionality

The FB operates as a simple read buffer:

1. Upon arrival of the **REQ** event, the **ST** algorithm `REQ` is executed:

``structured text
OUT := IN;

2. The current value of the InOut variable **IN** is copied to the output **OUT**.
3. The **CNF** event is then issued to signal the completion of the operation.

Since **IN** is declared as an InOut parameter, the function block directly accesses the memory location of the parent application. The value is not modified, but simply read and temporarily stored.

## Technical Features

- **InOut Parameter**: Using an InOut variable allows direct access to the data source without separate data inputs and outputs. This reduces the number of connections and saves resources.
- **Buffering**: The output **OUT** retains its value until the next **REQ** call. This ensures that the output value is independent of any changes to the source between two read cycles.
- **Initial Values**: Both **IN** and **OUT** start with 0, so defined values are available even without prior execution.

# Technical Features** ## State Overview

The function block (FB) has a single state: **REQ**

- **REQ**: When activated, the algorithm `REQ` is executed, followed by the **CNF** event. The state persists (no transition to another state).

| State | Entry Condition | Action | Output Event |
|---------|-------------------|--------|------------------|
| REQ | Event **REQ** received | `OUT := IN;` | CNF |

## Application Scenarios

- **Data Buffering**: An INT value used by multiple function blocks should be stably available without each block having to directly access the source.
- **Synchronization**: In time-critical control systems, the current value of a variable can be "frozen" at a specific point in time and processed later.
- **Replacement of a MOVE function block**: If direct memory access via InOut is preferred for performance reasons, **GET_INT** replaces the classic MOVE function block with separate input and output.

## Comparison with similar function blocks

| Function block | Input type | Buffering | Special feature |
|----------|------------------|-----------|--------------|
| **GET_INT** | InOut (INT) | Yes (one-time read on REQ) | Accesses the original variable, no additional variable required |
| **MOVE** (e.g., IEC 61131-3) | Input (INT) | Yes (on every execution) | Copies the value from an explicit input to an output |
| **F_TRIG / R_TRIG** | Input (BOOL) | No (edge detection only) | Works with Boolean values |

The main difference lies in the elimination of a separate data input through the use of an InOut parameter.

## Conclusion

**GET_INT** is a simple yet effective function block for buffered readout of an INT variable. By using an InOut parameter, it reduces connection overhead and is particularly suitable for applications requiring a stable instantaneous value. Its clear, low-state structure makes it reliable and easy to understand.
