# AL_DEMUX_4

![AL_DEMUX_4](./AL_DEMUX_4.svg)

* * * * * * * * * *
## Introduction

The function block **AL_DEMUX_4** implements a generic demultiplexer for the adapter type `AL` (analog/logic). It distributes an incoming adapter signal to one of four outputs, with the selection controlled by the index value `K`. The block is suitable for applications where a single signal needs to be routed to different outputs.
## Interface Structure

### **Event Inputs**

| Event | Comment |
|----------|-----------|
| REQ | Sets the index K and forwards the input signal to the corresponding output. |

### **Event Outputs**

| Event | Comment |
|----------|-----------|
| CNF | Confirms successful signal forwarding. |

### **Data Inputs**

| Variable | Type | Comment |
|----------|------|-----------|
| K | UINT | Index of the target output (value range 1 to 4). |

### **Data Outputs**

This function block does not have any standalone data outputs. Output is exclusively via adapters.

### **Adapters**

**Input Adapter (Socket):**

| Adapter | Type | Comment |
|---------|--------------------------------------------------------|--------------------------------|
| IN | `adapter::types::unidirectional::AL` | Input signal to be demultiplexed. |

**Output Adapters (Plugs):**

| Adapter | Type | Comment |
|---------|--------------------------------------------------------|-------------------------------|
| OUT1 | `adapter::types::unidirectional::AL` | First output (Index 1). |
| OUT2 | `adapter::types::unidirectional::AL` | Second output (Index 2). |
| OUT3 | `adapter::types::unidirectional::AL` | Third output (Index 3). |
| OUT4 | `adapter::types::unidirectional::AL` | Fourth output (Index 4). |

## Functionality

The module operates on the principle of a 1-to-4 demultiplexer. On a rising edge at the event input `REQ`, the current index `K` is evaluated. The signal present at adapter `IN` is then forwarded to the output adapter determined by `K`. All other outputs remain inactive (not connected). After successful transmission, the event `CNF` is output.

The index `K` is interpreted as an integer value in the range 1 to 4. Values outside this range do not result in any signal transfer and do not trigger the event `CNF` (or the behavior is implementation-dependent).

## Technical Features

- **Generic Adapter Type:** The function block is defined for the unidirectional adapter `AL`. The generic property (`GenericClassName`) allows the type to be extended to other unidirectional adapters.
- **Fixed Number of Outputs:** The architecture provides exactly four output adapters. Scaling to other channel numbers requires adjusting the function block type.
- **No Internal State Machine:** The logic is event-driven and does not have an explicit ECC state machine, enabling a lean and deterministic implementation.

## State Overview

The function block has no modeled states, as it operates purely event-driven. The processes can be described as follows:

1. **Waiting for REQ** – The function block is ready to receive a new index.
2. **Signal Forwarding** – At `REQ`, the value of `K` is evaluated, and the signal from `IN` is copied to the corresponding output (OUT1..OUT4).
3. **Acknowledgement** – `CNF` is then sent.

## Application Scenarios

- **Sensor-Actuator Matrix:** A single analog or logic sensor provides data that is forwarded to various actuators (e.g., valves or displays) depending on the operating mode.
- **Test and Verification Benches:** Rapid switching of a measured variable between multiple measuring devices.
- **Signal Distribution in Automation:** Control of multi-way valves or multiplex connections in the process industry.

## Comparison with Similar Components

- **`D_DEMUX` (Data Demultiplexer):** Works with data types (e.g., INT, REAL) and not with adapters. `AL_DEMUX_4`, on the other hand, encapsulates the signal in an adapter, which offers greater flexibility in type adaptation.
- **`AL_MUX_4`:** The multiplexer counterpart (`AL_MUX_4`) combines multiple inputs into one output. `AL_DEMUX_4` implements the reverse.
- **Generic MUX/DEMUX:** The IEC 61449-2 standard usually offers MUX components for scalar data, but without adapter support. `AL_DEMUX_4` fills this gap for unidirectional adapters.

## Conclusion

The **AL_DEMUX_4** is a compact and effective function block for signal distribution based on adapters. Its clear event control and limitation to four outputs make it particularly suitable for manageable automation tasks where a single analog or logic signal needs to be selectively routed to different locations. Its generic design allows for use with various adapter types and increases reusability.
