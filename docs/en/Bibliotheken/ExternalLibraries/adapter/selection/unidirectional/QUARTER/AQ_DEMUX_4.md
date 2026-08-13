# AQ_DEMUX_4

![AQ_DEMUX_4](./AQ_DEMUX_4.svg)

* * * * * * * * * *
## Introduction

The **AQ_DEMUX_4** is a generic demultiplexer for the adapter type `AQ` (Analog Quantity). It distributes an incoming analog value to one of four output adapters, selected by an index `K`. The device is activated by an event via the input `REQ` and confirms the switchover via the output `CNF`.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Sets the index K and passes the value on |

**With Variable:** K

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation of successful demultiplexing |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index of the destination output (1…4) |

### **Data Outputs**

No directly declared data outputs – output is handled via the plugins.

### **Adapters**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| **Plug** | OUT1 | `adapter::types::unidirectional::AQ` | Destination Output 1 |
| **Plug** | OUT2 | `adapter::types::unidirectional::AQ` | Destination Output 2 |
| **Plug** | OUT3 | `adapter::types::unidirectional::AQ` | Destination Output 3 |
| **Plug** | OUT4 | `adapter::types::unidirectional::AQ` | Destination Output 4 |
| **Socket** | IN | `adapter::types::unidirectional::AQ` | Input value to be demultiplexed |

## Functionality

The demultiplexer operates in an event-driven manner:

1. A value present at the adapter socket `IN` is forwarded by the module to the plug (OUT1…OUT4) specified by `K`.
2. The forwarding occurs upon arrival of the event `REQ`.
3. After successful transmission, the acknowledgment event `CNF` is sent.
4. The index `K` must be in the range 1 to 4; other values result in undefined behavior (in the standard implementation, the module typically switches to the first output or none at all).

Since this is a **generic FB** (recognizable by the attribute `GenericClassName`), the specific data type of the adapter `AQ` can be adapted to the actual use case by the development environment during instantiation (e.g., analog value, temperature, pressure, etc.).

## Technical Features

- **Generic Type:** The FB is declared as generic (`GEN_AQ_DEMUX`). During instantiation, the adapter type `AQ` can be replaced by any compatible unidirectional adapter, provided the interface (data direction) matches.
- **No State Storage:** The function block has no explicit states or time delays – switching is strictly event-driven and instantaneous.
- **Output Selection:** The output is selected using the integer index `K` (UINT). The number of outputs is fixed at four (OUT1…OUT4).
- **Adapter Interface:** Both inputs and outputs use unidirectional adapters of type `AQ`. This allows for loose coupling to other function blocks and easy reuse in different contexts.

## State Overview

The function block does **not** define its own state machines (Execution Control Chart). The internal logic is purely event-driven and has no memory. Upon receiving the `REQ` event, the forwarding and the `CNF` event are triggered immediately. No error or overflow handling is provided.

## Application Scenarios

- **Signal Distribution:** An analog value (e.g., pressure, temperature) provided by a sensor can be selectively passed on to various evaluation units or actuators.
- **Channel Switching:** In a measurement chain, multiple measuring points can be connected sequentially to a common evaluation unit.
- **Configurable Multiplexers:** Together with an index encoder (e.g., counter or PLC selection), the demultiplexer can be dynamically switched during operation.
- **Generic Replacement:** Since the adapter type `AQ` is generic, the function block is suitable for any analog or scalar signals in automation technology (e.g., current, voltage, level).

## Comparison with Similar Function Blocks

- **AQ_MUX_4** (Multiplexer): Performs the opposite function – multiple inputs are switched to one output. Both function blocks complement each other.
- **E_DEMUX** (Event Demultiplexer): Distributes event signals instead of data values. The `AQ_DEMUX_4`, on the other hand, distributes continuous data across adapters and operates at the data level, not the event level.
- **Demultiplexer with a fixed number of outputs:** Other function blocks often offer 2, 8, or 16 outputs. This function block offers exactly four, which is a good compromise for many applications.
- **Generic Implementation:** Many demultiplexers in libraries are type-specific (e.g., for INT or REAL). The generic nature of this function block increases its reusability.

## Change Detection

The selected output plug is only written and its adapter event only sent if the incoming value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates on unrelated peers.


## Conclusion

The `AQ_DEMUX_4` is a compact, generic demultiplexer for unidirectional analog adapters. It enables the flexible distribution of an input value to four outputs under the control of an index. Thanks to its generic type definition, it can be used in various signal environments without changing the application core. Its simple event-driven interface makes it a fundamental building block for channel switching in distributed automation and control systems.
