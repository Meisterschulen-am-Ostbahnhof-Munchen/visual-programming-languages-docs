# F_WSTRING_AS_LREAL

<img width="1491" height="214" alt="F_WSTRING_AS_LREAL" src="https://github.com/user-attachments/assets/b9ea26e0-7746-451f-944c-2f89290dd9c1" />

* * * * * * * * * *
## Introduction
The function block `F_WSTRING_AS_LREAL` is used to convert a WSTRING value into an LREAL value. This block is particularly useful when strings need to be converted into numerical values, for example, for mathematical calculations or data processing.

![F_WSTRING_AS_LREAL](F_WSTRING_AS_LREAL.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. When this input is activated, the conversion of the WSTRING value at input `IN` into an LREAL value begins.

### **Event Outputs**

- **CNF**: Signals the successful completion of the conversion. The converted LREAL value is available at output `OUT`.

### **Data Inputs**

- **IN** (WSTRING): The input for the string to be converted to an LREAL value.

### **Data Outputs**

- **OUT** (LREAL): The output for the converted LREAL value.

#### **Adapters**
This function block has no adapters.

## Functionality
When the `REQ` event is triggered, the function block converts the WSTRING value at input `IN` into an LREAL value. The conversion is performed using the function `WSTRING_AS_LREAL`. After successful conversion, the `CNF` event is triggered, and the converted value is provided at output `OUT`.

## Technical Features
- The conversion is performed directly without additional parameters.

- The function block is optimized for use in real-time systems.

## State Overview
1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Performs the conversion.

3. **Complete**: Signals completion with the `CNF` event.

## Application Scenarios

- Conversion of user input into numeric values.

- Processing of text data from external sources for calculations.

- Integration into systems that need to process both strings and numeric values.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks, `F_WSTRING_AS_LREAL` is specifically designed for converting WSTRING to LREAL.

- Other blocks might offer additional parameters or error handling, but this block is optimized for simplicity and efficiency.

## Conclusion
The `F_WSTRING_AS_LREAL` function block provides a simple and efficient way to convert WSTRING values to LREAL values. Its clear interface structure and direct functionality make it a valuable component in many applications.