# ALI_TO_AB
![ALI_TO_AB](./ALI_TO_AB.svg)
* * * * * * * * * *
## Introduction
The **ALI_TO_AB** function block is a composite function block (FB) according to IEC 61499-2, used to convert a LINT value (64-bit integer) into a BYTE value (8-bit). The conversion is performed via two unidirectional adapter interfaces: The ALI_receiver (socket) receives a LINT value, and the AB_sender (plug) transmits the converted BYTE value. Internally, the conversion block `F_LINT_TO_BYTE` from the IEC 61131 library is used.

```
## Interface Structure

### **Event Inputs**

The FB has no direct event inputs. Events are received exclusively via the **ALI_IN** adapter (socket).

| Event | Description |

|----------|--------------|

| *E1 (via ALI_IN)* | Signal to trigger the conversion. |

### **Event Outputs**

The FB has no direct event outputs. Events are sent exclusively via the **AB_OUT** adapter (plug).

| Event | Description |

|----------|--------------|

| *E1 (via AB_OUT)* | Acknowledgement after successful conversion. |

### **Data Inputs**

The FB has no direct data inputs. Data is provided exclusively via the **ALI_IN** adapter (socket).

| Data | Type | Description |

|-------|-----|--------------|

| *D1 (via ALI_IN)* | LINT | 64-bit integer to be converted. |

### **Data Outputs**

The FB has no direct data outputs. Data is output exclusively via the **AB_OUT** adapter (plug).

| Data | Type | Description |

|-------|-----|---------------|

| *D1 (via AB_OUT)* | BYTE | 8-bit converted value. |

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| **ALI_IN** | Socket (Input) | `adapter::types::unidirectional::ALI` | Receives the LINT value and an associated event. |

| **AB_OUT** | Plug (Output) | `adapter::types::unidirectional::AB` | Outputs the converted BYTE value and an acknowledgment event. |

## Functionality

1. The function block waits for an event at the **ALI_IN** adapter (E1).

2. As soon as the event arrives, the data value D1 (LINT) is passed to the internal conversion block `F_LINT_TO_BYTE` and converted into a BYTE value.

``` 3. After the conversion is complete, the BYTE value is output via the **AB_OUT** adapter (D1) and the acknowledgment event (E1) is sent.

The conversion from LINT (64 bits) to BYTE (8 bits) is performed by truncating the 8 least significant bits. Higher-order bits are lost in the process.

## Technical Features
- **Type Conversion with Loss of Value:** Since LINT is 64 bits wide, but BYTE is only 8 bits, only the lower 8 bits of the LINT value are retained. A value range of 0 to 255 is correctly represented; larger numbers are reduced modulo 256.
- **Pure Adapter Interface:** The component has no direct inputs/outputs, but communicates exclusively via two unidirectional adapters. This enables loose coupling in adapter-based architectures.
- **Standard Compliance:** The function block (FB) is based on the IEC 61131 block `F_LINT_TO_BYTE` and can therefore be used in environments that support this library.

## State Overview

As a composite block, **ALI_TO_AB** does not have its own internal state machine. The states of the included `F_LINT_TO_BYTE` (e.g., IDLE, BUSY) are not visible to the user. The FB therefore behaves like a combinational or event-driven function without an explicit state mask.

## Application Scenarios
- **Adapter-Based Data Conversion:** In systems connected via adapters with ALI and AB interfaces, ALI_TO_AB can be used as a bridge between a LINT-supplying module and a BYTE-receiving module.
- **Data Width Reduction:** This function block is suitable when a 64-bit value (e.g., a counter reading) needs to be mapped to an 8-bit signal (e.g., a simple status byte).
- **Protocol Conversion:** In heterogeneous control systems using different adapter types, ALI_TO_AB enables simple type conversion.

## Comparison with Similar Function Blocks
- **ALI_TO_Ax (LINT to ANY):** A more general converter that converts LINT to any other data type. ALI_TO_AB is specialized for BYTE and is therefore simpler and more direct.
- **F_LINT_TO_BYTE:** The underlying IEC 61131 function block. ALI_TO_AB encapsulates this in an adapter-based interface, allowing its use in environments that only support adapter communication.
- **Direct Adapter Connection:** Without conversion, an ALI adapter could not be directly connected to an AB adapter. ALI_TO_AB closes this gap.

## Conclusion

**ALI_TO_AB** is a simple yet useful conversion block for adapter-based communication. It enables the conversion of a LINT value to a BYTE value using a standardized IEC 61131 block. Its complete encapsulation within two unidirectional adapters allows for seamless integration into adapter networks without requiring the user to implement the internal type conversion. The loss of value due to the reduced data width should be considered when using this feature.
