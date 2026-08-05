# F_WORD_TO_ULINT

<img width="1448" height="214" alt="F_WORD_TO_ULINT" src="https://github.com/user-attachments/assets/0513fcc7-9c3a-4a16-bc9f-152d703063ce" />

* * * * * * * * * *
## Introduction
The function block `F_WORD_TO_ULINT` is used to convert a `WORD` data type to a `ULINT` data type. This function block is particularly useful in scenarios where data formats need to be extended or converted.

![F_WORD_TO_ULINT](F_WORD_TO_ULINT.svg)

## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: Expects a `WORD` value to be converted.

### **Data Outputs**

- **OUT**: Outputs the converted `ULINT` value.

#### **Adapters**
No adapters are available.

## Functionality
This function block performs the conversion from `WORD` to `ULINT` as soon as the `REQ` event occurs. The conversion is performed using the built-in function `WORD_TO_ULINT`. After successful conversion, the `CNF` event is triggered.

## Technical Features
- This function block is part of the `iec61131::conversion` package.

- The conversion is performed without additional parameters or settings.

## State Overview
1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Performs the conversion.

3. **Done**: Sends the `CNF` event and outputs the result.

## Application Scenarios
- Data processing in control systems where different data types need to be made compatible.

- Data extension for further calculations or storage.


## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks might offer direct conversions between other data types, e.g., `F_WORD_TO_INT`.

- This function block specializes in converting to `ULINT`, which is particularly relevant for large, unsigned numbers.

## Conclusion
The `F_WORD_TO_ULINT` function block is a simple yet effective function block for converting `WORD` to `ULINT`. Its clear interface and simple functionality make it a reliable solution in many automation scenarios.