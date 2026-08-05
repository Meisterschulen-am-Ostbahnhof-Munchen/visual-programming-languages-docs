# GET_UINT
![GET_UINT](./GET_UINT.svg)

* * * * * * * * * *
## Introduction
The **GET_UINT** function block reads the current value of a source `UINT` passed as an InOut variable and provides it as a buffered output value. It serves to capture a consistent snapshot of an external or internal UINT value at a defined point in time and make it available for further processing in the workflow.
## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| **REQ** | Normal execution command; triggers reading the InOut variable and updating the output. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| **CNF** | Confirms the successful execution of REQ and signals that the outputs are valid. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|--------------|
| **IN** | UINT | Source variable provided as an InOut parameter. The value is read during REQ and passed unchanged to the output. Default value: `0`. |

**Note:** `IN` is declared as an InOut variable, but is only used for reading within the function block.

### **Data Outputs**

| Variable | Type | Description |
|----------|-------|--------------|
| **OUT** | UINT | Buffered output value containing the value read from `IN` during the last REQ execution. Default value: `0`. |

### **Adapter**

None.

## Functionality

The function block has a single execution state (`REQ`). When the event input `REQ` is activated, it performs the following action:

1. **Read** the current value of the InOut variable `IN`.

### **Adapter**

None.

## Functionality

The function block has a single execution state (`REQ`). 2. **Copy** this value to the output variable `OUT`.

3. **Trigger** the event output `CNF` to signal completion.

Processing is strictly sequential and instantaneous.

## Technical Features
- **InOut variable as source:** Although `IN` is declared as an InOut variable, it is used for reading only. The function block does not write back, so the source remains unchanged.
- **Buffering:** The output `OUT` holds the value until the next output, `REQ`, is executed. This achieves decoupling between the source and the subsequent logic.
- **Simple state model:** The function block consists of only one state, so no complex sequence controls are required.

## State Overview

| State | Description |
|---------|--------------|
| **REQ** | Waits for the arrival of event `REQ` and then performs the assignment `OUT := IN`. Subsequently, `CNF` is sent. |

There is no explicit start or end state; after execution, the function block remains in state `REQ`, ready for the next task.

## Application Scenarios
- **Safe Value Transfer:** A UINT value from a global variable or another function block should be frozen at a defined point in time to maintain consistency throughout a process.

**Safe Value Transfer:** - **Sampling of Measured Values:** In a cyclic control system, the current value of a counter or sensor is read and temporarily stored.

- **Data Transfer Between Tasks:** This function block can serve as a simple buffer layer between asynchronous communication paths.

## Comparison with Similar Function Blocks

Unlike a pure input function block, which uses a fixed data port, **GET_UINT** allows the use of an **InOut variable** as a source. This allows the variable to be both written to and read from external sources without requiring a separate connection to an input. Pure read function blocks (e.g., UINT input) do not offer this flexibility but have a clearer interface. Compared to a memory function block (e.g., `R_TRIG` or `SR`), **GET_UINT** does not store states, but only the last read value.

#
## Conclusion

**GET_UINT** is a simple yet useful function block that buffers a UINT value from an InOut variable. Its minimalist design—one event, one action—makes it ideal for situations requiring clean, time-defined value transfer. It is particularly well-suited for applications that need a consistent data set within a flow without affecting the source.
