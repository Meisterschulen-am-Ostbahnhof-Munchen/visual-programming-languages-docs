# F_BOOL_TO_LWORD

<img width="1242" height="182" alt="F_BOOL_TO_LWORD" src="https://github.com/user-attachments/assets/eed96580-b3cb-4354-91df-bc8b33c8a966" />

* * * * * * * * * *
## Introduction
The function block `F_BOOL_TO_LWORD` converts a Boolean value (`BOOL`) into a 64-bit unsigned integer (`LWORD`). This conversion is particularly useful in scenarios where Boolean values need to be embedded in larger data structures or processed with other long integer values.

![F_BOOL_TO_LWORD](F_BOOL_TO_LWORD.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Normal execution request. Triggers the conversion. Linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Execution Confirmation. Triggered after successful conversion. Linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The Boolean value (`BOOL`) to be converted to `LWORD`.

### **Data Outputs**

- **OUT**: The converted 64-bit unsigned integer value (`LWORD`).

### **Adapters**
This function block does not use adapters.


### **Adapters** ... ## Functionality

This function block converts `BOOL` to `LWORD` when the `REQ` event occurs. The Boolean value `IN` is converted to `LWORD`, while `FALSE` is converted to `0` and `TRUE` to `1`. The result is output at the data output `OUT`, and the `CNF` event is triggered to indicate successful execution.



``` ## Technical Features
- The conversion is performed using the function ``BOOL_TO_LWORD``, which converts the Boolean value into a 64-bit value.

- The function block is simple and deterministic because it does not store any internal states.

## State Overview
Since it is a simple function block without internal states, there are no state transitions or management.

## Application Scenarios

- Embedding Boolean values in larger data structures that use ``LWORD``.

- Use in systems that need to process Boolean values as long integers, e.g., when communicating with external systems or storing them in databases.


## ⚖️ Comparison with similar function blocks

- **F_BOOL_TO_<TYPE>**: Similar function blocks exist for other data types (e.g., `F_BOOL_TO_BYTE`, `F_BOOL_TO_WORD`). These convert Boolean values to other integer data types with different bit widths.

- **F_<TYPE>_TO_LWORD**: Other conversion blocks convert various data types (e.g., `INT`, `DINT`) to `LWORD`, but `F_BOOL_TO_LWORD` is specific to Boolean values.


## Conclusion

The `F_BOOL_TO_LWORD` function block offers a simple and efficient way to convert Boolean values into 64-bit integer values. Its deterministic operation and clear interface structure make it a useful component in control and automation systems, especially where Boolean values need to be integrated into larger data structures.