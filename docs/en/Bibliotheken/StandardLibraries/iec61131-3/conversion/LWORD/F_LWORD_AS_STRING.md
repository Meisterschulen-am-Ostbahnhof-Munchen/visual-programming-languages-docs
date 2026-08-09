# F_LWORD_AS_STRING

<img width="1478" height="214" alt="F_LWORD_AS_STRING" src="https://github.com/user-attachments/assets/29fc831d-b4b3-4e7c-8264-93a698db1ab6" />
* * * * * * * * * *
## Introduction

The function block `F_LWORD_AS_STRING` converts a `LWORD` data type to a `STRING` data type. This block is particularly useful when large binary data (64-bit) needs to be converted into a readable string.
![F_LWORD_AS_STRING](F_LWORD_AS_STRING.svg)
## Interface Structure

### **Event Inputs**

- `REQ`: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**

- `CNF`: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- `IN` (LWORD): The input value to be converted.

### **Data Outputs**

- `OUT` (STRING): The result of the conversion.

### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion as soon as the `REQ` event is triggered. The `LWORD` value at input `IN` is converted to `STRING` and output `OUT`. Successful conversion is signaled by the `CNF` event.

## Technical Features

- The function block uses the standard algorithm `LWORD_AS_STRING` for conversion.
- The block is part of the `iec61131::conversion` package.

## State Overview

1. **Idle State**: The function block waits for the `REQ` event.
2. **Conversion State**: Upon receiving `REQ`, the conversion is performed.
3. **Completion State**: After successful conversion, the `CNF` event is triggered.

## Application Scenarios

- Conversion of large binary data into readable strings.
- Use in systems that need to work with binary and textual data.

## ⚖️ Comparison with Similar Function Blocks

- Unlike other conversion blocks that may process different data types, this one is specifically optimized for converting `LWORD` to `STRING`.

## Conclusion

The `F_LWORD_AS_STRING` function block provides a simple and efficient way to convert large binary data into strings. Its clear interface structure and simple functionality make it a valuable component in automation technology.