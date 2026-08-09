# F_UINT_TO_SINT

<img width="1441" height="216" alt="F_UINT_TO_SINT" src="https://github.com/user-attachments/assets/34da5b79-b1cc-4893-9138-b98b0cbfab10" />
* * * * * * * * * *
## Introduction

The function block `F_UINT_TO_SINT` converts an unsigned 16-bit integer value (UINT) to a signed 8-bit integer value (SINT). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_UINT_TO_SINT](F_UINT_TO_SINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When activated, the input value `IN` is read and processed.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output value `OUT` is then available.

### **Data Inputs**

- **IN** (UINT): The unsigned 16-bit integer value to be converted.

### **Data Outputs**

- **OUT** (SINT): The resulting signed 8-bit integer value after the conversion.

#### **Adapters**

- No adapters are available.

## Functionality

The function block performs the conversion by converting the `UINT` value at input `IN` to a `SINT` value and outputting it at output `OUT`. The conversion occurs when the ``REQ`` event is triggered, and the ``CNF`` event signals completion.

## Technical Features

- Data loss can occur during the conversion if the ``UINT`` value is outside the representable range of ``SINT`` (0 to 127).
- The function block is implemented as a simple function block (SimpleFB) and uses an ST algorithm for the conversion.

## State Overview

The function block has no internal states. The conversion occurs immediately upon the triggering of the ``REQ`` event.

## Application Scenarios

- Type conversion in control applications, where `UINT` values need to be converted to `SINT` values.
- Data processing in industrial automation systems, where different data types are processed.

## ⚖️ Comparison with Similar Function Blocks

- Compared to generic conversion function blocks, `F_UINT_TO_SINT` specializes in converting `UINT` to `SINT`.
- Other conversion function blocks might offer additional features such as range checks or error handling.

## Conclusion

The `F_UINT_TO_SINT` function block is an efficient tool for the specific conversion of `UINT` to `SINT`. Its simplicity and direct functionality make it ideal for applications requiring fast and straightforward type conversion.