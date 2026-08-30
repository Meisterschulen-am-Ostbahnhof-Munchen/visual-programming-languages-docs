# AB_TO_AQ

![AB_TO_AQ](./AB_TO_AQ.svg)

* * * * * * * * * *

## Introduction

The function block **AB_TO_AQ** converts a unidirectional adapter of type **AB (BYTE)** to an adapter of type **AQ (Quarter Byte)**. It directly passes an event and a data value from the input interface to the output interface, implicitly reducing the data width from 8 bits to 2 bits.

## Interface Structure

### **Event Inputs**

- **IN.E1** (via adapter IN): Event input of the BYTE adapter.

### **Event Outputs**

- **OUT.E1** (via adapter OUT): Event output of the Quarter Byte adapter.

### **Data Inputs**

- **IN.D1** (via adapter IN): Data input of the BYTE adapter (1 byte).

### **Data Outputs**

- **OUT.D1** (via adapter OUT): Data output of the quarter-byte adapter (1 quarter byte).

### **Adapters**

| Adapter | Direction | Type | Description |
| --------- | ---------- | ----- | -------------- |
| **IN** | Socket | `adapter::types::unidirectional::AB` | BYTE input adapter (8 bits) |
| **OUT** | Plug | `adapter::types::unidirectional::AQ` | Quarter-byte output adapter (2 bits) |

## Functionality

This function block forwards an incoming event (E1) and the associated data (D1) directly from the IN adapter to the OUT adapter. No internal processing or state changes occur; the data is simply passed through. The conversion from an 8-bit to a 2-bit format is determined by the different adapter types – typically, the least significant bits (LSB) of the BYTE value are converted to the quarter byte, unless otherwise specified.

## Technical Features

- Pure pass-through block without its own state logic (no ECC).
- Event and data paths are directly connected: `IN.E1 → OUT.E1` and `IN.D1 → OUT.D1`.
- Data reduction from 8 bits to 2 bits is achieved solely through type conversion; explicit conversion (e.g., truncation or rounding) is not implemented in the function block itself.
- The block is designed as a unidirectional adapter converter and does not support bidirectional communication.

## State Overview

There is no state machine. The function block (FB) operates purely combinatorially: Every event at the input is immediately forwarded as an event at the output, accompanied by the current data value.

## Application Scenarios

- Connecting a byte-oriented interface to logic that processes only two-bit wide data (e.g., status bits or switching signals).
- Reducing the data width in an adapter cascade when the original byte information can be compressed to the lower two bits.
- Test and simulation environments where different adapter formats need to be interconnected.

## Comparison with Similar Function Blocks

- **AB_TO_AQ** is similar to other unidirectional adapter converters such as `AB_TO_AB` (identical types) or `AQ_TO_AB` (extension to one byte). The difference lies in the data width and the type of implicit conversion.

**AB_TO_AQ** Unlike converters with explicit algorithms (e.g., scaling or bit masking), this function block offers no configuration options – the conversion is fixed.

## Conclusion

The **AB_TO_AQ** function block is a simple yet useful adapter converter that establishes a direct electrical and logical connection between two different unidirectional adapter types. It is ideally suited for situations where byte information needs to be reduced to the two most important bits and passed on without generating additional processing overhead.
