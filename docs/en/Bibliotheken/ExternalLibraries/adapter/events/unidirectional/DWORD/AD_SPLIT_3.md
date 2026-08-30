# AD_SPLIT_3

![AD_SPLIT_3](./AD_SPLIT_3.svg)

* * * * * * * * * *

## Introduction

The function block `AD_SPLIT_3` serves as a generic splitter for a unidirectional adapter (AD). It receives an incoming AD and forwards it to three separate outputs. This allows multiple uses of the same data or signal path.

## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapter**

| Type | Direction | Name | Description |
| ------ | ---------- | -------------- | -------------- |
| Socket (Input) | Input | IN | Unidirectional adapter input, which is distributed to the three outputs. |
| Plug (Output) | Output | OUT1 | First output with duplicated adapter signal. |
| Plug (Output) | Output | OUT2 | Second output with duplicated adapter signal. |
| Plug (Output) | Output | OUT3 | Third output with duplicated adapter signal. |

All adapters are of type `adapter::types::unidirectional::AD`.

## Functionality

The module functions as a pure splitter: The adapter (data or event stream) connected to socket `IN` is identically duplicated to the three plugs `OUT1`, `OUT2`, and `OUT3`. Changes or events at the input affect all three outputs instantly. No transformation, buffering, or logic is performed – signal distribution is transparent.

## Technical Features

- **Generic Type**: The function block is designed as a generic adapter splitter (`GenericClassName = 'GEN_AD_SPLIT'`) and can be used with any unidirectional adapter of type `adapter::types::unidirectional::AD`.
- **Pure Adapter Interface**: The function block has neither event nor data inputs/outputs in the traditional sense, but communicates exclusively via adapter plugs and sockets.
- **Unidirectional**: Communication occurs only in one direction (from the socket to the plugs), therefore no feedback or handshake mechanism is required.
- **No Runtime Dependence**: Distribution occurs instantaneously and without delay.

## State Overview

The `AD_SPLIT_3` does not have its own state diagram (ECC). The outputs follow the input without any internal logic or memory behavior. Therefore, there is only a single, passive state in which the current input is constantly passed on to the outputs.

## Application Scenarios

1. **Signal Fan-Out**: A sensor signal or a command (e.g., control word or status) is to be sent to multiple parallel consumers.
2. **Logging**: A data stream is processed once and then forwarded a second time for recording or monitoring.
3. **Redundancy**: A critical adapter path is distributed across multiple independent systems.
4. **Test Environments**: In simulation or test setups, a signal can be mirrored to multiple test points.

## Comparison with Similar Function Blocks

- **AD_SPLIT_2**: Distributes the input to only two outputs. `AD_SPLIT_3` extends this to three outputs.
- **AD_MERGE**: Combines multiple adapter inputs into one output – functionally the opposite.
- **Specific Data Splitters**: Function blocks like `SPLIT_INT` or `SPLIT_BOOL` operate at the data level, not the adapter level. `AD_SPLIT_3` is designed for complete adapter structures (data plus events).

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The `AD_SPLIT_3` is a simple yet useful generic function block for multiplying unidirectional adapters. Due to its pure adapter interface and lack of logic, it is particularly suitable for modular architectures where a signal needs to be distributed to multiple receivers without introducing additional complexity.
