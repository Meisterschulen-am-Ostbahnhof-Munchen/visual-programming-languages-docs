# F_ROL
<img width="1340" height="208" alt="F_ROL" src="https://github.com/user-attachments/assets/24e2181b-8b77-46bf-bf08-bc549c06ab07" />
* * * * * * * * * *
## Introduction
The function block `F_ROL` (Rotate Left) performs a bitwise left rotation. It rotates the input value a specified number of bits to the left. The bits rotated out on the left side are inserted again on the right side. This is a cyclic operation in which no bits are lost.
![F_ROL](F_ROL.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Service request that triggers the execution of the left rotation. It is linked to the data inputs `IN` and `N`.

### **Event Outputs**
- **CNF**: Confirmation of the completed service. Linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input value to be rotated. The data type is `ANY_BIT` (any bit type).
- **N**: The number of bits by which the input value should be rotated. The data type is `ANY_INT` (any integer type).

### **Data Outputs**
- **OUT**: The result of the left rotation. The data type is `ANY_BIT` (the same as the input value).

### **Adapters**
- No adapters available.

### ## Functionality
The function block `F_ROL` performs a bitwise left rotation of the input value `IN` by `N` bits. Bits that fall outside the range on the left side are reinserted on the right side. This is a true rotation; no bits are padded with zeros.

## Technical Features
- Supports any bit type (`ANY_BIT`) for the input value `IN` and the output value `OUT`.
- The number of rotations `N` can be any integer value (`ANY_INT`).
- The operation is cyclical, meaning that if `N` is greater than the bit length of `IN`, the rotation is performed modulo the bit length.
- Unlike a shift, no bits are lost during rotation.

## State Overview

1. **Initial State**: Waits for the event `REQ`.

2. **Execution State**: Upon receiving `REQ`, the left rotation is performed and the result is output via `OUT`. The event `CNF` is triggered.

3. **Return to Initial State**: After `CNF` is triggered, the block returns to its initial state.

## Application Scenarios
- Bitwise manipulation of data in control applications.
- Cryptographic operations requiring bitwise rotations.
- Signal processing where data bits need to be shifted cyclically.
- Checksum calculations and data encoding.

## ⚖️ Comparison with Similar Components
- **F_SHL (Shift Left)**: Shifts bits to the left and pads the resulting free positions on the right with zeros. This is not a cyclic operation.
- **F_ROR (Rotate Right)**: Performs a right rotation, rotating bits from right to left.
- **F_ROL vs. F_SHL**: While F_SHL performs a shift with zero padding, F_ROL performs a cyclic rotation without zero padding.

## Conclusion

The function block `F_ROL` is an efficient tool for bitwise left rotations in control applications. Its flexibility in supporting various bit and integer types makes it versatile. The cyclic nature of the rotation ensures that no data bits are lost, making it particularly suitable for applications with strict data integrity requirements. The clear distinction between rotation (cyclic) and shift (with zero padding) is crucial for correct application.

--

**Changes at a Glance:**

- Correction of the description: With ROL, the rotated-out bits are reinserted on the right, not padded with zeros.
- Clarification that this is a true cyclic rotation.
- Improved distinction between rotation (ROL/ROR) and shift (SHL/SHR).
- Consistent wording throughout the document.