# ARR08B_TO_DWORDS

This function block converts an 8-byte array into two 32-bit data words (DWORDs). It is used to split a contiguous 8-byte data block into two 4-byte integer values.
![ARR08B_TO_DWORDS](./ARR08B_TO_DWORDS.svg)

* * * * * * * * * *
## Introduction

The **ARR08B_TO_DWORDS** is a pure conversion function block that creates two separate DWORD values from an incoming 8-byte array. The conversion is performed byte by byte, with the first four bytes assigned to the first output (OUT_00) and the last four bytes to the second output (OUT_01). The function block is triggered by an event (REQ) and outputs a confirmation event (CNF) after the conversion is complete.

## Interface Structure

### **Event Inputs**

| Event | Description | Data Carried |
|----------|---------------|-------------------|
| **REQ** | Starts the conversion of the input array. | IN (8-byte array) |

### **Event Outputs**

| Event | Description | Data Carried |
|----------|--------------|-------------------|
| **CNF** | Confirms the completed conversion. | OUT_00, OUT_01 |

### **Data Inputs**

| Name | Data Type | Array Dimension | Description |
|------|----------|-----------------|--------------|
| **IN** | BYTE | [0..7] | 8-byte input array that is split into two DWORDs. |

### **Data Outputs**

| Name | Data Type | Description |
|---------|----------|--------------|
| **OUT_00** | DWORD | First DWORD (bytes 0–3 of the array). |
| **OUT_01** | DWORD | Second DWORD (bytes 4–7 of the array). |

### **Adapters**

No adapters available.

## Functionality

This function block performs a direct byte-by-byte copy from the input array to the output variables:

1. Bytes **IN[0]** to **IN[3]** are assigned to the least significant to most significant bytes of **OUT_00**.
2. Bytes **IN[4]** to **IN[7]** are assigned to **OUT_01**.

The assignment is performed in the structured text body:

OUT_00.%B0 := IN[0];
OUT_00.%B1 := IN[1];
OUT_00.%B2 := IN[2];
OUT_00.%B3 := IN[3];
OUT_01.%B0 := IN[4];
OUT_01.%B1 := IN[5];
OUT_01.%B2 := IN[6];
OUT_01.%B3 := IN[7];
The function block operates without delay or state memory; the outputs are updated immediately upon arrival of the REQ event, and the CNF event is triggered instantly.

## Technical Features

- **Endianness**: The function block interprets the array in little-endian format – the first byte (index 0) is assigned to the least significant byte of the DWORD. This assumption is typical for many industrial protocols and systems.
- **No Array Length Check**: The array is assumed to be exactly 8 bytes. A different input size would lead to undefined behavior.
- **Functional Function Block**: The function block is purely functional and has no internal states.

## State Overview

The function block has no internal state machine. It operates event-driven and immediately returns the CNF signal after each activation. The outputs remain active until the next REQ activation.

## Application Scenarios

- **Data Packet Decomposition**: Separation of an 8-byte telegram into two 32-bit values, e.g., for communication with industrial field devices (CANopen, Modbus, etc.).
- **Sensor Value Processing**: Splitting an 8-byte raw data block from sensors that deliver two physical measured values (4 bytes each).
- **Conversion in the logiBUS Environment**: Within the `logiBUS::utils::conversion::arr::forwarding` package, this is a standard function block for forward conversion of array data.

## Comparison with Similar Function Blocks

| Function Block | Function | Difference |
|----------|----------|-------------|
| **BYTE_TO_DWORD** | Converts a single 4-byte array into a DWORD. | Requires separate calls for each 4-byte segment. |
| **ARR08B_TO_DWORDS** | Converts an 8-byte array into two DWORDs at once. | Integrated splitting in a single step reduces the number of calls and code. |

This function block thus offers a more compact solution than combining several basic conversion blocks.

## Conclusion

The **ARR08B_TO_DWORDS** is a simple yet useful function block for quickly and directly splitting an 8-byte array into two DWORDs. Thanks to its clear byte-to-byte mapping and event handling, it integrates well into dataflow-oriented control applications. Its use requires a little-endian format. Adjustments are necessary for other endianness requirements. Overall, the component is an efficient solution for preprocessing binary data.
