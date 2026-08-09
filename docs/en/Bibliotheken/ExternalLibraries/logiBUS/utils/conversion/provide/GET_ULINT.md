# GET_ULINT

![GET_ULINT](./GET_ULINT.svg)

* * * * * * * * * *
## Introduction

The **GET_ULINT** function block reads the current value of a variable of type `ULINT` (unsigned 64-bit integer) provided as an InOut parameter and makes it available as a buffered value at a data output. Upon a request (REQ), the value from the source is read and output at `OUT`. The acknowledgment (CNF) is then sent. Thus, GET_ULINT is a simple read function block for InOut variables.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Data |
|-------|--------|-------------------------|-----------|
| `REQ` | Event | Normal Execution Request | `IN` |

### **Event Outputs**

| Name | Type | Comment | With Data |
|-------|--------|--------------------------|-----------------|
| `CNF` | Event | Execution Confirmation | `OUT`, `IN` |

### **Data Inputs**

| Name | Type | Comment |
|------|--------|-----------------|
| - | - | - |

### **Data Outputs**

| Name | Type | Comment | Initial Value |
|------|--------|--------------------------|-------------|
| `OUT`| ULINT | Buffered output value | 0 |

### **Adapters**

No adapters available.

### **Internal Input/Output Variables**

In addition to the inputs/outputs, the function block has an input/output variable:

| Name | Type | Comment | Initial Value |
| |------|--------|------------------------------|-------------|
| `IN` | ULINT | Source variable (InOut) | 0 |

## Functionality

This function block processes a single action:

1. An incoming event at input `REQ` triggers the execution of algorithm `REQ`.
2. In the algorithm, the current value of the InOut variable `IN` is copied directly to the output `OUT`:

OUT := IN;`

3. After the assignment is complete, the event `CNF` is output. The outputs `OUT` and `IN` are associated with the event `CNF`, allowing calling blocks to process the updated value.

By using an InOut variable, the block can access memory outside its own context without obtaining it via a conventional input. The value is read fresh with each request, making the block suitable as a read buffer.

## Technical Features

- **InOut Variable:** The function block uses a variable named `IN` with the property `InOut`. This allows linking to a parent variable (e.g., from a resource or global data space) without the function block having to obtain the variable via a normal data input. Access is reference-based.
- **ULINT Type:** Both `IN` and `OUT` are declared as unsigned 64-bit integers (ULINT) – suitable for large count values, timestamps, or other values in the range 0 … 2⁶⁴‑1.
- **Instant Read:** The algorithm is extremely short (one assignment), making the execution time negligible.

## State Overview

The function block is implemented as a SimpleFB with a single ECC state:

| State | Action | Output Event | Meaning |
|---------|--------|------------------|-----------|
| `REQ` | `REQ` (OUT := IN) | `CNF` | Upon a request, the value is read and acknowledged. |

There are no other states, no branches, and no internal memory variables (except for the output `OUT` itself, which buffers the last read value).

## Application Scenarios

- **Safe Read Operation:** A higher-level function block wants to retrieve the current value from a shared variable (e.g., a sensor value written by another control component) without permanently referencing the value.
- **Value Buffer for Asynchronous Processing:** In a time-controlled process, `GET_ULINT` can be called to take a snapshot of a global counter variable and buffer it.
- **Parameterization via InOut Interfaces:** If the function block is embedded in a higher-level component, the InOut variable can be directly connected to a data connection of the parent function block, so that read requests point to this variable.

## Comparison with Similar Function Blocks

- **GET_DINT / GET_LINT / GET_UINT:** Analogous function blocks for other integer types (DINT, LINT, UINT, etc.). The functionality is identical; the only difference is the data type.
- **READ_ULINT (hypothetical):** A function block that uses a separate data input for the source value instead of an InOut variable. This would have the advantage of loose coupling, but the disadvantage that the source value would have to be carried along as a data stream. The InOut approach of `GET_ULINT` allows a direct reference to a shared variable, which is preferred in some architectures.
- **SAMPLE_ULINT:** A function block that samples and buffers the current value of an input on each event – also similar, but with a normal data input instead of InOut.

## Conclusion

The `GET_ULINT` function block provides a simple and efficient way to read the current value of an InOut variable of type `ULINT` and output it as a buffered output. Using an InOut variable allows direct, reference-based access to external memory locations without additional data copying during the call. Thanks to its minimalist state machine, it is ideally suited for time-critical applications where a fast, unobtrusive value read is required.
