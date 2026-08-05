# F_SINT_AS_WSTRING

<img width="1477" height="213" alt="F_SINT_AS_WSTRING" src="https://github.com/user-attachments/assets/ee583877-c052-4a47-bc14-58fe834f43b7" />

* * * * * * * * * *
## Introduction
The function block `F_SINT_AS_WSTRING` is used to convert a SINT value (8-bit signed integer) into a WSTRING (wide string). This block is particularly useful when numeric values need to be converted into a text format suitable for display or further processing.

![F_SINT_AS_WSTRING](F_SINT_AS_WSTRING.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The SINT value (8-bit signed integer) to be converted to a WSTRING.

### **Data Outputs**

- **OUT**: The resulting WSTRING after the SINT value conversion.

#### **Adapters**

- No adapters are available.

## Functionality
This function block performs the conversion of the SINT value (`IN`) to a WSTRING (`OUT`) as soon as the event `REQ` is triggered. The conversion is performed using the integrated function `SINT_AS_WSTRING`. After successful conversion, the event `CNF` is triggered.

## Technical Features
- The function block has a simple structure and contains only one conversion algorithm.

- The conversion is performed directly without additional parameters or complex logic.

## State Overview
1. **Idle State**: Waits for the `REQ` event.

2. **Conversion State**: Performs the conversion and outputs the result via `OUT`.

3. **Confirmation State**: Triggers the `CNF` event and returns to the idle state.

## Application Scenarios

- Displaying numeric values in user interfaces.

- Logging numeric data in text format.

- Further processing of numeric values in text-based systems.

## ⚖️ Comparison with similar function blocks

- **F_INT_AS_WSTRING**: Converts an INT value (16-bit) to a WSTRING.

- **F_DINT_AS_WSTRING**: Converts a DINT value (32-bit) to a WSTRING.

- **F_LINT_AS_WSTRING**: Converts a LINT value (64-bit) to a WSTRING.

## Conclusion
The `F_SINT_AS_WSTRING` function block offers a simple and efficient way to convert SINT values to WSTRINGs. Its clear interface and simple operation make it a useful component in various applications, especially where numeric values need to be represented or processed in text format.