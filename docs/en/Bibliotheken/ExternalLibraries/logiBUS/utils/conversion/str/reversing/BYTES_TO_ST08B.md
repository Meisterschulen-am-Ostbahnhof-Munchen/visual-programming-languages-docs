# BYTES_TO_ST08B

<img width="1047" height="423" alt="image" src="https://github.com/user-attachments/assets/d2c1b827-1e6e-4e74-b89f-c8b60ae0824f" />
![BYTES_TO_ST08B](./BYTES_TO_ST08B.svg)

* * * * * * * * * *
## Introduction

This function block combines eight individual byte values into a single 8-byte structure of type `ST08B`. It enables the orderly conversion of discrete byte values into a structured data format.

## Interface Structure

### **Event Inputs**

* **REQ** (Type: `Event`)
* Connects the activation of the function block to the data inputs: `IN_00`, `IN_01`, `IN_02`, `IN_03`, `IN_04`, `IN_05`, `IN_06`, `IN_07`.
* Triggers the conversion of the input bytes to the `ST08B` structure.

### **Event Outputs**

* **CNF** (Type: `Event`)
* Triggered after successful conversion.
* Signals the availability of the converted value at data output `OUT`.

### **Data Inputs**

* **IN_00** (Type: `BYTE`)
* Comment: BYTE 00
* **IN_01** (Type: `BYTE`)
* Comment: BYTE 01
* **IN_02** (Type: `BYTE`)
* Comment: BYTE 02
* **IN_03** (Type: `BYTE`)
* Comment: BYTE 03
* **IN_04** (Type: `BYTE`)
* Comment: BYTE 04
* **IN_05** (Type: `BYTE`)
* Comment: BYTE 05
* **IN_06** (Type: `BYTE`)
* Comment: BYTE 06
* **IN_07** (Type: `BYTE`)
* Comment: BYTE 07

### **Data Outputs**

* **OUT** (Type: `logiBUS::utils::conversion::types::ST08B`)
* Comment: ST08B Output
* Outputs the 8-byte structure created from the eight input bytes.

### **Adapters**

This function block does not have any adapter interfaces.

## Functionality

Upon receiving a `REQ` event, the function block directly assigns the values of the eight data inputs `IN_00` to `IN_07` to the corresponding fields (`B_00` to `B_07`) of the output structure `OUT`. After this assignment is complete, a `CNF` event is triggered, signaling that the `OUT` structure has been updated with the new values and is ready for further processing.

## Technical Features

The function block uses the user-defined data type `logiBUS::utils::conversion::types::ST08B` as its output format. This type must be defined in the system for the function block to function correctly. The bytes are assigned positionally: `IN_00` becomes `OUT.B_00`, `IN_01` becomes `OUT.B_01`, and so on.

## State Overview

The `BYTES_TO_ST08B` function block is a purely combinational function block. It has no internal states that are stored for extended periods. Each execution triggered by a `REQ` event processes the current input values independently of previous executions and produces a corresponding output result.

## Application Scenarios

* **Data Packet Assembly:** Combining individual byte components into a predefined data packet, e.g., for communication via serial interfaces or networks.
* **Interfacing with Protocols:** Adapting data to communication protocols that expect specific 8-byte structures.
* **Data Type Conversion:** Converting raw byte data into a higher-level, structured data type for improved handling and readability within the application.
* **Hardware Interconnection:** When data from sensors or actuators is read byte by byte and needs to be aggregated into a fixed structure.

## ⚖️ Comparison with Similar Blocks

Compared to general type conversion or array manipulation blocks, `BYTES_TO_ST08B` offers a specialized solution for converting exactly eight bytes into a predefined `ST08B` structure. This eliminates the need for manual indexing or looping and simplifies handling for this specific use case. Other function blocks might be more flexible (e.g., able to process a variable number of bytes), but this block is optimized for its fixed size.

## Conclusion

The function block `BYTES_TO_ST08B` is a useful tool for converting eight individual byte inputs into a defined 8-byte structure `ST08B`. It contributes to the modularization and simplification of control programs, especially when it comes to preparing discrete byte data for structured communication tasks or internal data processing. Its direct and event-driven operation makes it reliable and easy to integrate.
