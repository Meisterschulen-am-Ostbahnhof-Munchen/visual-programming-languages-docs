# F_DWORD_TO_UINT

<img width="1242" height="181" alt="F_DWORD_TO_UINT" src="https://github.com/user-attachments/assets/8aa2ae37-3b94-46bf-9683-ee81e0a3e434" />

* * * * * * * * * *
## Introduction
The function block `F_DWORD_TO_UINT` converts a `DWORD` value to a `UINT` value. This function block is particularly useful in scenarios where type conversion between these two data types is required, for example, in communication between different systems or when processing data from different sources.

![F_DWORD_TO_UINT](F_DWORD_TO_UINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: This input triggers the execution of the function block. The associated data value `IN` is processed upon this event.


### **Event Outputs**

- **CNF**: This output is activated after successful conversion and confirms execution. The converted value `OUT` is output with this event.

### **Data Inputs**

- **IN** (`DWORD`): The input value to be converted from `DWORD` to `UINT`.

### **Data Outputs**

- **OUT** (`UINT`): The output value after conversion.

### **Adapters**
This function block does not use adapters.


### ## Functionality

The function block performs the conversion from `DWORD` to `UINT` as soon as the event `REQ` is received. The conversion is performed using the function `DWORD_TO_UINT`, which converts the input value `IN` and outputs the result to `OUT`. After successful conversion, the event `CNF` is triggered.

## Technical Features
- The function block is a simple algorithm (`SimpleFB`) and does not perform any complex state transitions.

- The conversion occurs directly and without delay.

## State Overview
Since it is a simple function block, there are no complex state transitions. The block responds exclusively to the ``REQ`` event, outputting the converted value, and to the ``CNF`` event.

## Application Scenarios

- Type conversion in communication interfaces where different systems use different data types.

- Data processing in control systems where conversion between ``DWORD`` and ``UINT`` is required.

## ⚖️ Comparison with Similar Blocks
- Compared to other conversion blocks such as ``F_WORD_TO_UINT`` or ``F_BYTE_TO_UINT``, this one is specifically optimized for converting ``DWORD`` to ``UINT``.


## ⚖️ Comparison with Similar Blocks

- Compared to other conversion blocks like ``F_WORD_TO_UINT`` or ``F_BYTE_TO_UINT``, this one is specifically optimized for converting ``DWORD`` to ``UINT``.

Similar function blocks might offer additional features such as range checks or error handling, which this function block does not.

## Conclusion
The `F_DWORD_TO_UINT` function block is a simple and efficient tool for converting `DWORD` values to `UINT` values. Its simplicity makes it particularly suitable for applications where fast and direct type conversion is required.