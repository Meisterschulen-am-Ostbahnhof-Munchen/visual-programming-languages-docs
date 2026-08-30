# ARR08B_TO_BYTES

<img width="1089" height="362" alt="image" src="https://github.com/user-attachments/assets/35768584-80d4-464c-b258-e26d1456fd4f" />
![ARR08B_TO_BYTES](./ARR08B_TO_BYTES.svg)

* * * * * * * * * *
The function block `ARR08B_TO_BYTES` is used to decompose an 8-element byte array (`ARR08B`) into eight individual byte outputs. It is a utility block for data conversion and forwarding within control applications, especially when structured data from an array needs to be split into discrete signals.

- **REQ**: This incoming event triggers the processing of the function block. Upon its arrival, the data at input `IN` is read and distributed to the individual outputs.
- **CNF**: This outgoing event signals the completion of processing. It is generated simultaneously with the output of the new values at data outputs `OUT_00` to `OUT_07`.
- **IN** (`ARRAY[0..7] OF BYTE`): The input for the 8-byte array to be split. The array has a fixed index range from 0 to 7.
- **OUT_00** (`BYTE`): Contains the value of the array element with index 0 (`IN[0]`).
- **OUT_02** (`BYTE`): Contains the value of the array element with index 2 (`IN[2]`).
- **OUT_03** (`BYTE`): Contains the value of the array element with index 3 (`IN[3]`).
- **OUT_04** (`BYTE`): Contains the value of the array element with index 4 (IN[4]) ... * **OUT_05** (`BYTE`): Contains the value of the array element with index 5 (`IN[5]`).
- **OUT_06** (`BYTE`): Contains the value of the array element with index 6 (`IN[6]`).
- **OUT_07** (`BYTE`): Contains the value of the array element with index 7 (`IN[7]`).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

This function block has no adapter interfaces.

The operation is deterministic and simple: Upon each occurrence of the `REQ` event, the function block reads the entire input array `IN`. Each element of the array is then assigned to a specific byte output. The assignment is made directly according to the array index. After all assignments have been completed, the ``CNF`` event is triggered to report the successful completion of the operation to subsequent blocks.

The included ST (Structured Text) code shows the direct implementation:

OUT_00 := IN[0];
OUT_01 := IN[1];
...
OUT_07 := IN[7];

- **Fixed Size:** The block is specifically designed for arrays with exactly 8 elements (`ARR08B`). Separate blocks are required for arrays of other lengths.
- **Synchronous Processing:** Processing occurs in a single cycle without delay. The latency between `REQ` and `CNF` is minimal.
- **No Internal State:** The block has no internal memory. The output is a direct function of the current input at any given time.

The function block has no internal states in the sense of a state machine. Its behavior is purely combinatorial and is entirely controlled by the interface events:

1. **Idle State:** Waiting for the `REQ` event.
2. **Execution State:** At `REQ`, the data is transferred and the `CNF` event is immediately generated. The block then returns to its idle state.

- **Data Distribution:** Splitting a received data packet (e.g., from a communication interface) into its individual byte components for further processing in the application.
- **Interface Adapter:** Connecting function blocks that work with array structures to blocks that expect individual byte inputs.
- **Data Logging and Visualization:** Separating array data to selectively display or store individual bytes in HMIs or logging systems.
-

- **`SEL_n` / `MUX` blocks:** These blocks select an element from an array based on an index. `ARR08B_TO_BYTES`, on the other hand, extracts **all** elements simultaneously and in parallel.
- **`BYTES_TO_ARR08B`:** This is the inverse block, which combines eight individual byte inputs into an 8-byte array.
- **Generic Array Splitting Blocks:** More generic blocks might exist that take the array length as a parameter. `ARR08B_TO_BYTES`, due to its fixed size, is simpler, faster, and requires no configuration.
-

The `ARR08B_TO_BYTES` function block is a specialized, efficient, and reliable building block for the fundamental operation of array decomposition. Its strength lies in its simplicity and unambiguity for the specific use case of an 8-byte array. For control applications where this data structure is common, it offers an optimized and maintainable solution compared to manual indexing in more complex blocks.

## Functionality

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion
