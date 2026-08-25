# ASSEMBLE_AL_FROM_AB

![ASSEMBLE_AL_FROM_AB](./ASSEMBLE_AL_FROM_AB.svg)

* * * * * * * * * *
## Introduction

The function block `ASSEMBLE_AL_FROM_AB` combines eight individual byte pieces of information from adapters of type `AB` (unidirectional) into a single, contiguous 64-bit data word (LWORD). The result is output via an output adapter of type `AL`. This function block serves as a central repository for byte-oriented data and enables modular and clear data structuring.
## Interface Structure

### Event Inputs

None. Event control is handled exclusively via the connected adapters.

### Event Outputs

None. The output event is provided via the adapter `OUT`.

### Data Inputs

None. Data inputs are supplied via the byte adapters.

### Data Outputs

None. The composite LWORD is output via the adapter `OUT`.

### Adapters

**Sockets (Input Adapters)**

| Name | Data Type | Description |
|------|----------|--------------|
| `BYTE_00` | `adapter::types::unidirectional::AB` | Byte 0 (least significant byte) |
| `BYTE_01` | `adapter::types::unidirectional::AB` | Byte 1 |
| `BYTE_02` | `adapter::types::unidirectional::AB` | Byte 2 |
| BYTE_03` | `adapter::types::unidirectional::AB` | Byte 3 |
| BYTE_04` | `adapter::types::unidirectional::AB` | Byte 4 |
| BYTE_05` | `adapter::types::unidirectional::AB` | Byte 5 |
| BYTE_06` | `adapter::types::unidirectional::AB` | Byte 6 |
| BYTE_07` | `adapter::types::unidirectional::AD` | Byte 7 (most significant byte) |

Each byte adapter provides one event (`E1`) and one data byte (`D1`).

**Plugs (Output Adapters)**

| Name | Data Type | Description |
|------|----------|---------------|
| `OUT` | `adapter::types::unidirectional::AL` | Output: composite LWORD; event output via `E1`, data value via `D1` |

## Functionality

The function block is implemented as a composite FB and contains two internal function blocks: `ASSEMBLE_LWORD_FROM_BYTES` and `E_D_FF_ANY`.

1. **Data Collection**: As soon as one of the eight byte adapters (`BYTE_00` … `BYTE_07`) delivers an event at its output `E1`, this event is forwarded to the input `REQ` of `ASSEMBLE_LWORD_FROM_BYTES`. Simultaneously, the corresponding byte values from each adapter are routed to the appropriate data inputs of the assembler block (`BYTE_00` … `BYTE_07`).
2. **Conversion**: The internal component `ASSEMBLE_LWORD_FROM_BYTES` combines the eight bytes in the order `BYTE_00` to `BYTE_07` into a 64-bit word (LWORD). `BYTE_00` is the least significant byte, and `BYTE_07` is the most significant. After completion of the operation, an acknowledgment event (`CNF`) is issued, and the constructed LWORD is made available at its data output.
3. **Buffering and Output**: The event `CNF` triggers the edge-triggered flip-flop `E_D_FF_ANY`. This flip-flop takes the current LWORD value and stores it temporarily. On each rising edge at the clock input (`CLK`), the value at the data output `Q` is updated. The output `Q` is connected to the data output `D1` of the adapter plug `OUT`. The stored event `EO` of the flip-flop is provided as the output event `E1` of the adapter plug `OUT`.

Thus, with each update of one of the eight byte inputs, the entire LWORD is recalculated and output via the output adapter.

## Technical Features

- **Adapter-based interfaces**: The component uses adapters exclusively for input and output. This enables flexible and loose coupling with other components that use the same adapter type.
- **Composite Architecture**: The internal structure is built from proven standard components (`ASSEMBLE_LWORD_FROM_BYTES` and `E_D_FF_ANY`). This hides complexity and increases maintainability.
- **Flip-Flop Buffering**: The `E_D_FF_ANY` buffers the assembled value and only releases it after assembly is complete. This prevents inconsistent output during individual byte updates and ensures that a complete data value is always available.
- **Event Synchronization**: All byte adapter signals are routed to a common `REQ` input. This ensures that any change to any byte is processed immediately. However, the merging of all bytes always occurs based on the currently available values.

## State Overview

Since this is a composite function block (FB), it does not have its own state machine. The internal `E_D_FF_ANY` has an internal state: the stored LWORD value. This value only changes on rising edges at the clock input, i.e., after each successful assembly. The state is retained until another assembly is triggered.

## Application Scenarios

- **Data Aggregation in Sensor Networks**: Several byte-oriented sensors (e.g., temperature, pressure, humidity) are connected via separate adapters. The function block combines them into a 64-bit data telegram, which is forwarded to a central controller.
- **Protocol Conversion**: A byte stream received via multiple adapters (e.g., a serial interface with 8 payload bytes) is converted into a single LWORD, which is easier to handle for further processing.
- **Modular I/O Expansion**: In a modular automation solution, eight digital/analog byte inputs (e.g., via I/O modules) can be combined into a single 64-bit variable.

## Comparison with Similar Components

- **`ARRAY_TO_LWORD` Components**: These components typically use arrays as inputs and have a different interface (no adapters). The `ASSEMBLE_AL_FROM_AB` offers an adapter-based, event-driven alternative that fits better into modular, typed adapter structures.
- **Multiplexer (MUX)**: A multiplexer selects one of several inputs, while this component combines all inputs simultaneously into a larger data word.
- **Direct Bit Concatenation**: Without this component, byte concatenation would have to be performed manually using bitwise shifting and OR operations. The `ASSEMBLE_AL_FROM_AB` encapsulates this logic and reduces development and testing effort.

## Conclusion

The `ASSEMBLE_AL_FROM_AB`This is a specialized function block for the modular and event-driven aggregation of eight-byte data sets into a single LWORD. Its exclusive use of adapters makes it ideal for use in adapter-based architectures and promotes a clear separation of data sources and sinks. Integrated buffering via the flip-flop and triggering by each incoming event ensure that a consistent, complete data value is always output. This component significantly simplifies data aggregation and contributes to maintainable and reusable control logic.
