# F_UDINT_AS_WSTRING

<img width="1494" height="212" alt="F_UDINT_AS_WSTRING" src="https://github.com/user-attachments/assets/dd3fe324-73e2-4f6e-8ccc-6a9fe7bb8e35" />
* * * * * * * * * *
## Introduction

The function block `F_UDINT_AS_WSTRING` converts an unsigned 32-bit integer value (`UDINT`) into a Unicode string (`WSTRING`). This functionality is particularly useful when numeric values are needed as text for display or further processing.
![F_UDINT_AS_WSTRING](F_UDINT_AS_WSTRING.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The unsigned 32-bit integer value (`UDINT`) to be converted to a Unicode string.

### **Data Outputs**

- **OUT**: The resulting Unicode string (`WSTRING`) after conversion.

#### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion as soon as the event `REQ` is triggered. The algorithm converts the value of `IN` into a `WSTRING` representation and stores the result in `OUT`. The event `CNF` is then triggered to signal the completion of the operation.

## Technical Features

- The conversion is performed directly without additional parameters.
- The function block is optimized for use in IEC 61131-compliant environments.

## State Overview

1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Performs the conversion.
3. **Completed**: Signals completion with `CNF` and returns to the idle state.

## Application Scenarios

- Displaying numeric values in user interfaces.
- Logging numeric data to text files.
- Preparing data for communication via text-based protocols.

## ⚖️ Comparison with Similar Function Blocks

- Compared to `F_DINT_AS_WSTRING`, this function block processes unsigned values.
- Similar to `F_UDINT_AS_STRING`, but with Unicode support.

## Conclusion

The `F_UDINT_AS_WSTRING` function block provides a simple and efficient way to convert unsigned 32-bit integer values to Unicode strings. Its clear interface and straightforward functionality make it a valuable tool in many automation applications.
