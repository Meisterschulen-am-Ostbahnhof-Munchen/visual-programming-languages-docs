# ASSEMBLE_DWORD_FROM_BOOLS

![ASSEMBLE_DWORD_FROM_BOOLS](https://github.com/user-attachments/assets/2c59a6bc-c069-4740-8371-474846a393ee)

* * * * * * * * * *
## Introduction
The function block `ASSEMBLE_DWORD_FROM_BOOLS` combines 32 individual BOOL values into a single DWORD value. This is particularly useful when multiple binary states need to be processed or transmitted in a compact form.

## Interface Structure

### **Event Inputs**

- `REQ`: Trigger event that starts processing the input data. It is linked to all 32 bit inputs.

### **Event Outputs**

- `CNF`: Confirmation event that is output after successful combination of the BOOL values into a DWORD.


### **Data Inputs**

32 BOOL inputs (`BIT_00` to `BIT_31`), each representing one bit in the resulting DWORD:

- `BIT_00`: Bit 0 (least significant bit)
- `BIT_01`: Bit 1
- ...
- `BIT_31`: Bit 31 (most significant bit)

### **Data Outputs**
- `OUT`: DWORD composed of the 32 input BOOLs.

### **Adapters**
No adapters included.


## Functionality

When the `REQ` event is triggered, the function block combines the 32 BOOL inputs into a DWORD. Each BOOL input corresponds to one bit in the DWORD:

- `BIT_00` becomes bit 0 (LSB)

- `BIT_31` becomes bit 31 (MSB)

After successful combination, the `CNF` event is output.

## Technical Features

- The function block is implemented in ST (Structured Text).

- Bit mapping is performed directly by assigning the BOOL values to the corresponding bit positions of the DWORD.

- No buffering or state storage: Processing occurs anew with each `REQ` event.


## State Overview
The function block has no internal state. Processing is purely event-driven:

1. Receive `REQ` → Start processing.

2. Read BOOL values and combine them into a DWORD.

3. Output `CNF`.

## Application Scenarios

- Compression of multiple binary signals for transmission via communication protocols.

- Storage of multiple switching states in a single register.

- Efficient processing of bitmasks in control algorithms.

## ⚖️ Comparison with Similar Function Blocks

- Compared to manual bit operations in ST or other FB types, this function block offers a predefined, error-free solution for combining BOOLs into a DWORD.

- Similar function blocks might process fewer bits or offer additional functions such as bit shifts.


## Conclusion

The `ASSEMBLE_DWORD_FROM_BOOLS` function block is an efficient and reliable solution for combining 32 binary inputs into a single DWORD. Its simple and clear interface makes it ideal for applications requiring compact representations of multiple binary states.