# F_ULINT_TO_BCD_LWORD
<img width="1302" height="181" alt="F_ULINT_TO_BCD_LWORD" src="https://github.com/user-attachments/assets/e52c2e4c-a8aa-4dc5-bb01-ce013aadd734" />
* * * * * * * * * *
## Introduction
The function block `F_ULINT_TO_BCD_LWORD` converts a `ULINT` value (64-bit unsigned integer) to a `LWORD` value type in BCD (Binary Coded Decimal) format. This block is particularly useful in applications where numeric values need to be converted into a format compatible with BCD systems.
![F_ULINT_TO_BCD_LWORD](F_ULINT_TO_BCD_LWORD.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. The value to be converted is passed via the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The converted value is output via the data output `OUT`.

### **Data Inputs**
- **IN**: The input for the `ULINT` value to be converted.

### **Data Outputs**
- **OUT**: The output for the converted `LWORD` value type in BCD format.

### **Adapters**
This function block does not have any adapters.

## Functionality
The function block performs the conversion from `ULINT` to `LWORD` in BCD format as soon as the `REQ` event is triggered. The conversion is performed using the integrated function `ULINT_TO_BCD_LWORD`. Once the conversion is complete, the `CNF` event is triggered, and the converted value is available at the `OUT` output.

## Technical Features
- Supports the conversion of 64-bit unsigned integer (`ULINT`) to 64-bit BCD (`LWORD`).
- No additional parameters or settings are required.

## State Overview
1. **Idle**: Waits for the `REQ` event.

2. **Conversion**: Performs the conversion as soon as `REQ` is activated.

3. **Completion**: Sends the `CNF` event and outputs the converted value.

## Application Scenarios
- Industrial control systems that process BCD-encoded data.
- Communication with peripheral devices that expect BCD data.
- Data conversion in automation applications.

## ⚖️ Comparison with Similar Blocks
- Compared to generic conversion blocks, `F_ULINT_TO_BCD_LWORD` offers a specialized solution for conversion to the BCD format.
- Other blocks might offer additional conversion options, but they may be less efficient for this specific use case.

## Conclusion

The `F_ULINT_TO_BCD_LWORD` function block is an efficient and specialized solution for converting `ULINT` to `LWORD` in BCD format. Its ease of use and direct functionality make it ideal for applications requiring fast and reliable data conversion.