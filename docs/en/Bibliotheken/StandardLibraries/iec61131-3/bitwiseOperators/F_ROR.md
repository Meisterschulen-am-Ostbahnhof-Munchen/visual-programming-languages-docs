# F_ROR

<img width="1364" height="208" alt="F_ROR" src="https://github.com/user-attachments/assets/b26a1c34-8702-476a-9811-0f51ada0efd6" />

* * * * * * * * * *
## Introduction
The function block `F_ROR` (Rotate Right) performs a bitwise right rotation. It belongs to the category of standardized bit shift functions according to IEC 61131-3. The block rotates the input data a specified number of bits to the right and fills the freed bits with the bits rotated out.

![F_ROR](F_ROR.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Service request that triggers the operation. Linked to the data inputs `IN` and `N`.


### **Event Outputs**

- `CNF`: Confirmation of the operation performed. Linked to the data output `OUT`.

### **Data Inputs**

- `IN`: The input value to be rotated (Type: `ANY_BIT`).

- `N`: The number of bits by which the input value should be rotated right (Type: `ANY_INT`).

### **Data Outputs**

- `OUT`: The result of the right rotation (Type: `ANY_BIT`).

### **Adapters**
No adapters available.


### ## Functionality
The function block performs a bitwise right rotation of the input value `IN` by `N` bits. The bits rotated out are then reinserted on the left side. This differs from a simple right shift, where the freed bits are padded with zeros.

## Technical Features
- Supports all `ANY_BIT` data types for the input value `IN` and the output value `OUT`.

- The parameter `N` can accept any `ANY_INT` data type.

- The operation is independent of the word length of the input value.

## State Overview
The function block has no internal state. The operation is re-executed with each `REQ` event.

## Application Scenarios

- Cryptographic operations requiring bitwise rotations.

- Signal processing requiring bitwise manipulation of data.

- Low-level hardware controllers requiring bitwise operations.

## ⚖️ Comparison with Similar Components

- `F_SHR` (Shift Right): Performs a right shift, but pads the freed bits with zeros.

- `F_ROL` (Rotate Left): Performs a left rotation, similar to `F_ROR`, but in the opposite direction.


## Conclusion

The `F_ROR` function block is a useful tool for applications requiring bitwise rotations. Its simple interface and support for various data types make it versatile. Unlike simple shift operations, it preserves all bits of the input value, making it indispensable for certain applications.