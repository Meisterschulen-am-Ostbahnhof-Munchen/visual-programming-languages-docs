# NmSetName
<img width="1021" height="248" alt="image" src="https://github.com/user-attachments/assets/313bb66b-066d-4f13-adfb-b0d058074d2d" />
![NmSetName](./NmSetName.svg)
* * * * * * * * * *
## Introduction
The function block `NmSetName` converts a structured name field definition into a compact, 8-byte ISO NAME according to the ISO 11783-5 specification (section 5.1.2). This block is an essential component for device identification and addressing in ISOBUS networks (agricultural and forestry machinery). It performs the bit-accurate mapping of the individual fields of a `NAMEFIELD_T` structure to the corresponding byte array of a `CF_NAME_T`.
## Interface Structure

### **Event Inputs**
* **REQ**: This event triggers the conversion. Upon arrival, the incoming data is processed at input `psNameField`.

### **Event Outputs**
* **CNF**: This event signals the completion of processing. It is generated after the successful conversion of the input data.

### **Data Inputs**
* **psNameField** (`isobus::pgn::NAMEFIELD_T`): The input structure containing all individual components of an ISOBUS name (such as manufacturer code, device class, function instance, etc.) in a format easily manageable for the programmer.

### **Data Outputs**
* **(Unnamed)** (`isobus::pgn::CF_NAME_T`): This output provides the resulting 8-byte ISO NAME array (`data[0]` to `data[7]`), which can be used directly in ISOBUS messages.

### **Adapters**
This function block does not use any adapters.

## Functionality
The block operates as a pure data transformer. When triggered by the `REQ` event, it reads the values from the input structure `psNameField` and distributes them bitwise across the eight bytes of the output array according to the ISO standard. The logic consists of a sequential sequence of bitwise operations (AND, OR, SHL) and type conversions. Each line in the ST code sets specific bits in a particular byte of the `CF_NAME_T` output, while the remaining bits remain unchanged (masked by the `AND` operations). After all bytes are set, the `CNF` event is output.

## Technical Features
* **Bitwise Processing:** The core functionality is based on precise bitwise operations to pack the complex structure of the ISO NAME into a compact byte array.
* **Type Safety:** Explicit type conversions (e.g., `DWORD_TO_BYTE`, `WORD_TO_BYTE`) are used to ensure correct data handling.
* **Standard Compliance:** The implementation strictly adheres to the bit mapping as defined in ISO 11783-5.
* **Stateless:** The block has no internal state between calls. The output depends solely on the current input data.

## State Overview

The function block is stateless. Its behavior can be described as a simple, deterministic function:

1. **Waiting:** The block waits for the `REQ` event.

2. **Processing:** At `REQ`, the input data is processed and the output array is calculated.

3. **Confirming:** Immediately after the calculation, the `CNF` event is output.

The block then returns directly to the wait state (1).

## Application Scenarios
* **Initializing an ISOBUS Node:** When an electronic control unit (ECU) starts up in an ISOBUS network, its unique NAME must be constructed from configurable parameters (e.g., from an NVRAM) and entered into the communication stack.
* **Dynamic Device Configuration:** In systems where device properties (e.g., function instance) can change at runtime, this block is used to generate the new, valid NAME.
* **Test and Simulation Tools:** For generating correct ISO NAMEs for simulating various virtual devices in an ISOBUS network.

## ⚖️ Comparison with Similar Blocks
* **Counterpart `NmGetName`:** While `NmSetName` packs a structured description into a byte array, a hypothetical `NmGetName` block would perform the reverse operation: It extracts the individual fields from a given ISO NAME byte array and presents them in a `NAMEFIELD_T` structure. `NmSetName` is thus the "encoder," and its counterpart would be the "decoder."
* **Generic Byte Packers:** Unlike generic function blocks that serialize arbitrary data structures, `NmSetName` is specifically optimized for the ISO 11783 NAME structure, thus guaranteeing compliance with the standard without additional configuration.

## 🛠️ Related Exercises
* [Exercise_121](../../../../Uebungen/test_B/Uebungen_doc/Uebung_121.md)]

## Conclusion
The `NmSetName` function block is a specialized, indispensable component for ISOBUS communication. It abstracts the complex, bit-accurate composition of the ISO NAME according to the standard and provides the user with a simple, structured interface. Its deterministic and stateless operation makes it robust and easy to integrate into control sequences for device initialization and configuration.