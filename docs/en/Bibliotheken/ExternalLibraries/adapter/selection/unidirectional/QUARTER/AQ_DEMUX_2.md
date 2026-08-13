# AQ_DEMUX_2

![AQ_DEMUX_2](./AQ_DEMUX_2.svg)

* * * * * * * * * *
## Introduction

The **AQ_DEMUX_2** is a generic function block that acts as a demultiplexer for analog values (AQ – Analog Quantity). It distributes an incoming AQ value to one of two possible output adapters, controlled by an index. The block is designed as a generic FB (Generic FB) and allows for flexible reuse in various application contexts.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Trigger to set the index K and forward the value. Connected to the data input K. |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation that index K has been set and the value has been passed on. |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index for selecting the output (1 → OUT1, 2 → OUT2). |

### **Data Outputs**

This function block does not have direct data outputs. Output is provided via the adapter interfaces.

### **Adapters**

| Type | Direction | Name | Comment |
|-----|----------|------|-----------|
| adapter::types::unidirectional::AQ | Input (Socket) | IN | Input value to be demultiplexed. |
| adapter::types::unidirectional::AQ | Output (Plug) | OUT1 | First output channel (Index 1). |
| adapter::types::unidirectional::AQ | Output (Plug) | OUT2 | Second output channel (Index 2). |

## Functionality

When a **REQ** event arrives, the value of the data input **K** is evaluated:

- If **K** = 1**, the current value of the adapter socket **IN** is forwarded to the adapter plug **OUT1**.
- If **K** = 2**, the value is forwarded to **OUT2**.
- For other values of **K**, the block remains inactive or the value is ignored (depending on the implementation). The **CNF** event is then issued to signal successful completion.
- The forwarding is event-driven and without internal caching – the value is copied directly from the input adapter to the selected output adapter.

## Technical Features

- **Generic Function Block**: The function block is defined as a Generic FB (`GEN_AQ_DEMUX`), allowing it to be instantiated for different analog data types, as long as the adapter interface supports the `unidirectional::AQ` protocol.
- **Adapter-Based Communication**: Adapters are used instead of traditional data ports. This enables loose coupling and the exchange of complex data structures between function blocks.
- **Simple Index Control**: The index **K** is of type `UINT` and determines which output is activated. The limitation to two outputs is hard-coded (the "_2" in the name).
- **No Data Linking on the CNF Event**: The acknowledgment event (CNF) has no associated data – it serves only for synchronization.

## State Overview

The function block does not have an explicit state machine. The internal logic can be described as a simple sequence:

1. **Wait for REQ** (Idle state)
2. **Evaluate K** and **Forward the IN value** to the corresponding plug
3. **Send CNF** and return to the idle state

A repeated REQ event performs a new forwarding each time, regardless of the previous index.

## Application Scenarios

- **Distributing an analog setpoint** to various actuators (e.g., valves, drives) in a production plant.
- **Controlling two parallel process branches** with a common measured value, which is passed on to different control loops depending on the index.
- **Switching between two operating modes** in an adaptive controller where one analog input is switched to two different outputs.

## Comparison with Similar Function Blocks

- **AQ_MUX**: The multiplexer counterpart – it selects one of several analog inputs and passes it on to a single output.
- **DATA_DEMUX**: A general-purpose data demultiplexer, which, however, often works with primitive data types (e.g., INT, REAL) and does not use adapters.
- **AQ_DEMUX_N**: An extended version with more than two outputs. The AQ_DEMUX_2 represents the simplest implementation.

Compared to a pure data demultiplexer, the AQ_DEMUX_2 offers advantages through its adapter interface, which enables standardized transmission of analog values with optional additional information (e.g., unit, status).

## Change Detection

The selected output plug is only written and its adapter event only sent if the incoming value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates on unrelated peers.


## Conclusion

The **AQ_DEMUX_2** is a specialized yet flexible function block for distributing analog values to two outputs. Its generic nature and adapter-based communication make it a valuable element in automation technology, especially in scenarios with event-driven channel selection. The simple interface and clear separation of event and data logic facilitate integration into complex control projects.
