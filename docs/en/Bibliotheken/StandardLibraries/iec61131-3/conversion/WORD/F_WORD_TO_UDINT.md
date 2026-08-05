# F_WORD_TO_UDINT

<img width="1455" height="214" alt="F_WORD_TO_UDINT" src="https://github.com/user-attachments/assets/0620ecfb-f811-4aea-b442-967e54ac35c8" />

* * * * * * * * * *
## Introduction
The function block `F_WORD_TO_UDINT` converts a `WORD` data type to a `UDINT` data type. This function block is particularly useful in scenarios where type conversion is required to prepare data for further processing.

![F_WORD_TO_UDINT](F_WORD_TO_UDINT.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the conversion. When this event is triggered, the input value `IN` is processed.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion and outputs the result via output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `WORD`, which is to be converted to `UDINT`.

### **Data Outputs**

- **OUT**: The result of the conversion as `UDINT`.

### **Adapters**
This function block has no adapters.


### ## Functionality
When the `REQ` event is triggered, the algorithm is started, which converts the `WORD` value at the `IN` input into a `UDINT` value. The result is provided at the `OUT` output, and the `CNF` event signals successful execution.

## Technical Features
- The function block uses the built-in function `WORD_TO_UDINT` for the conversion.

- The conversion is performed without additional parameters or complex logic, enabling fast and efficient processing.

## State Overview

1. **Idle State**: Waits for the `REQ` event.

2. **Processing State**: Performs the conversion.

3. **Completion State**: Sends the `CNF` event and outputs the result.

## Application Scenarios

- Type conversion in control applications.

- Preparing data for further calculations or storage.

- Integration into larger automation solutions where different data types need to be processed.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_INT_TO_REAL` or `F_BOOL_TO_BYTE` offer similar functionality for other data types.

- `F_WORD_TO_UDINT` specializes in converting `WORD` to `UDINT` and therefore offers an optimized solution for this specific use case.

## Conclusion
The `F_WORD_TO_UDINT` function block is a simple and efficient building block for converting `WORD` values to `UDINT` values. Its clear interface and simple functionality make it a reliable component in automation projects.