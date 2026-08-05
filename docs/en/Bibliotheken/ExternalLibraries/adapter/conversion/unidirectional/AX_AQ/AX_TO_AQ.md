# AX_TO_AQ
![AX_TO_AQ](./AX_TO_AQ.svg)
* * * * * * * * * *
## Introduction
The **AX_TO_AQ** function block converts a Boolean signal (AX adapter) into a quarter-byte signal (AQ adapter). The conversion is based on event-driven COMMAND logic, where an incoming event triggers the conversion and the result is acknowledged via an output event. The function block encapsulates the conversion logic in an internal sub-function block, thus enabling a clean separation between adapter types.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|---------------|

| `IN.E1` | Starts the conversion of the incoming Boolean value. Interpreted as a command. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| `OUT.E1` | Confirms the completion of the conversion and signals the validity of the output quarter-byte value. |

### **Data Inputs**

| Data | Type | Description |

|-------|-----|---------------|

| `IN.D1` | BOOL (via AX adapter) | Boolean input value to be converted into a quarter byte. |

### **Data Outputs**

| Data | Type | Description |

|-------|-----|--------------|

| `OUT.D1` | Quarter Byte (via AQ adapter) | Output value – the converted quarter byte (4-bit representation). |

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| `IN` | Socket | `adapter::types::unidirectional::AX` | Receives the Boolean signal. The AX adapter provides a unidirectional Boolean channel. |

| `OUT` | Plug | `adapter::types::unidirectional::AQ` | Provides the converted quarter-byte signal. The AQ adapter is a unidirectional quarter-byte channel. |

## Functionality

1. An event at `IN.E1` triggers the internal processing.

2. The sub-function block `BOOL_TO_QUARTER` is activated via its event input `REQ` and converts the Boolean value at `I` into a quarter byte.

`` 3. After the conversion is complete, `BOOL_TO_QUARTER` reports this via its event `CNF`, which is then passed on to `OUT.E1`.

4. Simultaneously, the converted value is transferred via the data connection from the output `QB` of the sub-block to `OUT.D1`.

The entire process is event-driven and operates without internal state storage – each command generates a complete conversion.

## Technical Features
- **Internal Encapsulation**: The conversion logic is fully implemented by the embedded function block `logiBUS::utils::quarter::BOOL_TO_QUARTER`. This simplifies maintenance and replacement of the conversion implementation.
- **Unidirectionality**: Both the input and output adapters are unidirectional; Feedback or bidirectional use is not supported.
- **Event Synchronization**: The output event pulse `OUT.E1` guarantees that the data at output `OUT.D1` is valid before the calling block continues processing.
- **License and Origin**: The block is licensed under EPL-2.0 and is included in the package `adapter::conversion::unidirectional` (see CompilerInfo).

## State Overview
The function block does not have an explicit state machine. It operates as pure combinational logic with event-driven triggering:

- **Idle State**: No event is present at `IN.E1`. Outputs remain unchanged.
- **Active**: An event at `IN.E1` starts the conversion. Upon completion, `OUT.E1` is triggered, and the new value is output to `OUT.D1`. The function block then returns to its idle state.

## Application Scenarios
- **Bus Signal Translation**: In an industrial bus system, Boolean control signals (e.g., bit values from sensors) are converted into compact 4-bit data words to reduce bandwidth.
- **Bit-to-Quarter-Byte Converter in Automation Networks**: When a subsystem can only process quarter-byte values but receives Boolean inputs.
- **Adapter Bridge**: The function block acts as an intermediary between an AX-compatible transmitter and an AQ-compatible receiver in a unidirectional chain.

## Comparison with Similar Function Blocks

| Function Block | Task | Difference |

|----------|---------|-------------|

| `BOOL_TO_BYTE` | Converts BOOL to a byte (8-bit) | Works with 8-bit output instead of 4-bit. Requires other adapter types (e.g., `AB`). |

| `BOOL_TO_WORD` | Converts BOOL to a word (16-bit) | Provides a wider output, often for analog or digital word signals. |

| `AX_TO_AQ` | Converts BOOL (AX) to a quarter byte (AQ) | Specifically designed for the unidirectional AX↔AQ adapter combination, it generates only 4-bit values. |

## Conclusion

The **AX_TO_AQ** function block is a specialized and compact converter for converting Boolean adapter signals into the quarter-byte format. Its clear, event-driven structure and internal reuse of a standardized conversion block make it ideal for use in automation and bus systems where space-saving transmission of Boolean states is required. The simple interface and unidirectional nature facilitate integration into existing communication workflows.
