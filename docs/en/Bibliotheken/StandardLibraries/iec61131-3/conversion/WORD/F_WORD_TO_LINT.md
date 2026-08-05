# F_WORD_TO_LINT
<img width="1438" height="214" alt="F_WORD_TO_LINT" src="https://github.com/user-attachments/assets/626d094f-fb66-471e-9668-d8d5be75042c" />
* * * * * * * * * *
## Introduction
The function block `F_WORD_TO_LINT` converts a `WORD` data type to a `LINT` data type. It is part of the `iec61131::conversion` package and enables simple and efficient type conversion within IEC 61499-based control systems.
![F_WORD_TO_LINT](F_WORD_TO_LINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the execution of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals successful completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input of type `WORD` to be converted.

### **Data Outputs**
- **OUT**: The output of type `LINT`, containing the result of the conversion.

### **Adapters**
- No adapters are present.

## Functionality
This function block performs the conversion from `WORD` to `LINT` as soon as the event `REQ` is triggered. The conversion is performed using the function ``WORD_TO_LINT``, which converts the input value ``IN`` and outputs the result to ``OUT``. Upon successful conversion, the event ``CNF`` is triggered.

## Technical Features
- The function block is a simple algorithm without a state machine.
- The conversion occurs directly and without any additional delay.
- The block is optimized for use in real-time control systems.

## State Overview
Since it is a simple function block, there are no state transitions or complex state logic. Execution occurs immediately upon receiving the ``REQ`` event.

## Application Scenarios
- Type conversion in control applications where `WORD` data needs to be converted to `LINT`.
- Integration into larger control systems that process different data types.
- Use in data processing chains where bit width extension is required.

## ⚖️ Comparison with Similar Blocks
- Compared to generic conversion blocks, `F_WORD_TO_LINT` is specialized and therefore more efficient.
- Other blocks, such as `F_INT_TO_LINT` or `F_DWORD_TO_LINT`, offer similar functionality, but for different data types.

## Conclusion

The `F_WORD_TO_LINT` function block is a simple and efficient building block for type conversion from `WORD` to `LINT`. It is ideally suited for applications requiring fast and direct conversion and can be easily integrated into existing control systems.