# SPLIT_AB_INTO_AQ

![SPLIT_AB_INTO_AQ](./SPLIT_AB_INTO_AQ.svg)

* * * * * * * * * *

## Introduction

The function block `SPLIT_AB_INTO_AQ` is used to split a data byte received via a `AB` adapter (byte) into four individual 2-bit quartets and output each of these via a `AQ` adapter (quarter). It encapsulates the decomposition of a byte into manageable partial values and makes them available for further processing via standardized unidirectional adapter interfaces.

## Interface Structure

### **Event Inputs**

| Name | Description |
|---------|--------------|
| `IN.E1` | An event at the socket triggers the decomposition and output of the quartets. |

### **Event Outputs**

No direct event outputs; output is provided via the events of the connected adapters (`QUARTER_BYTE_xx.E1`).

### **Data Inputs**

| Name | Description |
|---------|--------------|
| `IN.D1` | The incoming data byte (type: BYTE) that is split into four quartets. |

### **Data Outputs**

No direct data outputs; the quartets are provided via the data interfaces of the output adapters (`QUARTER_BYTE_xx.D1`).

### **Adapters**

| Name | Type | Direction | Description |
| -------------------- | ----- | ---------- | -------------- |
| `IN` | `adapter::types::unidirectional::AB` | Socket (Input) | Receives the byte to be parsed, including the event. |
| `QUARTER_BYTE_00` | `adapter::types::unidirectional::AQ` | Plug (Output) | Outputs the quartet 0 (least significant 2 bits). |
| `QUARTER_BYTE_01` | `adapter::types::unidirectional::AQ` | Plug (Output) | Outputs the quartet 1. |
| `QUARTER_BYTE_02` | `adapter::types::unidirectional::AQ` | Plug (Output) | Outputs quartet 2. |
| `QUARTER_BYTE_03` | `adapter::types::unidirectional::AQ` | Plug (Output) | Outputs quartet 3 (most significant 2 bits). |

## Functionality

1. An event at socket `IN.E1` activates processing.
2. The byte present at the socket (`IN.D1`) is forwarded to the internal component `SPLIT_BYTE_INTO_QUARTERS`. This component splits the byte into four 2-bit parts (quartets).
3. The four quartets are fed in parallel to the data inputs of `E_D_FF_ANY` flip-flops.

4. Simultaneously, the splitter's acknowledgment event (`CNF`) is distributed to the clock inputs (`CLK`) of all four flip-flops.

5. On the rising edge of this event, the flip-flops take over the quartets and pass them on to their respective outputs (`Q`).
6. The flip-flop outputs are directly connected to the data inputs of the output adapters `QUARTER_BYTE_00` … `QUARTER_BYTE_03`. Simultaneously, the flip-flop output event (`EO`) is sent to the event input (`E1`) of the respective adapter, so that the data is output on the adapter interface.

Thus, with each activation of the socket, an entire byte is split into four quartets and transmitted synchronously to all four output adapters.

## Technical Features

- **Internal Flip-Flops:** The use of `E_D_FF_ANY` ensures that the splitting occurs only once per event and that the values are buffered until a new event arrives.
- **Adapter Coupling:** Instead of direct inputs/outputs, only unidirectional adapters are used, enabling loose coupling and reusability in complex adapter networks.
- **Synchronization:** The flip-flops are clocked via the shared `CNF` event, ensuring all quartets are present simultaneously.
- **No State Machine:** The function block operates purely event-driven without its own sequential state – the logic is entirely implemented through the interconnected internal components.

## State Overview

Since `SPLIT_AB_INTO_AQ` is a composite function block without its own state machine, its behavior is determined by the internal components. Essentially, there are two phases:

1. **Idle:** No event is present at the socket; the output adapters hold the last received values.
2. **Processing:** An event at the socket triggers the decomposition and updating of all outputs. Upon completion, the function block returns to its idle state.

## Application Scenarios

- **Control of Four Actuators:** A byte (e.g., from a master control bus) is split into four 2-bit values to provide separate control signals for independent actuators.
- **Data Reduction:** Splitting a byte into four individual signals for transmission to parallel, simpler processing units.
- **Adapter-Based Architectures:** Used in systems that consistently operate with unidirectional adapters to increase modularity.

## Comparison with Similar Components

- **`SPLIT_BYTE_INTO_QUARTERS`:** Performs the simple splitting of a byte into four quartets, but via direct data and event inputs/outputs. `SPLIT_AB_INTO_AQ` encapsulates this logic in an adapter interface and adds flip-flops for stable output.
- **`SPLIT_WORD_INTO_BYTES`:** Splits a 16-bit word into two bytes – analogous principle, but for different data widths and adapter types.
- **Simple Multiplexers/Demultiplexers:** While these signals switch, `SPLIT_AB_INTO_AQ` focuses on the fixed, parallel division of a composite data type.

## Conclusion

SPLIT_AB_INTO_AQ` is a specialized composite function block for splitting a byte adapter input into four separate quarter adapter outputs. It simplifies the design of adapter networks by hiding the complex bit manipulation and ensuring reliable, event-driven output of the quartets. The use of flip-flops ensures stable data storage between events. This component is particularly suitable for modular automation solutions that work with unidirectional adapters.
