# AIS_DEMUX_5
![AIS_DEMUX_5](./AIS_DEMUX_5.svg)

* * * * * * * * * *
## Introduction
The function block **AIS_DEMUX_5** is a generic AIS demultiplexer (Generic FB) according to IEC 61499. It serves to forward an AIS signal arriving via the adapter input **IN** to one of five adapter outputs (**OUT1** … **OUT5**) according to the set index **K**. The selection and forwarding are triggered by an event **REQ** and acknowledged with **CNF** after successful transmission.
## Interface Structure

### **Event Inputs**

| Event | With Variables | Description |
|----------|----------------|---------------------------------------------------|
| **REQ** | K | Sets the index **K** and starts the demultiplexing action |

### **Event Outputs**

| Event | Description |
|----------|------------------------------------------------|
| **CNF** | Confirmation that the demultiplexing operation is complete |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|-----------------------------------------|
| **K** | UINT | Index of the desired output (1 … 5) |

### **Data Outputs**
No data outputs are available. Output is exclusively via the adapter interfaces.

### **Adapters**

| Direction | Adapter | Type | Description |
|----------|-------------|--------------------------------------|-------------------------------------------------------|
| Socket | **IN** | adapter::types::unidirectional::AIS | Input AIS signal, which is distributed to the outputs |
| Plug | **OUT1** | adapter::types::unidirectional::AIS | First AIS output |
| Plug | **OUT2** | adapter::types::unidirectional::AIS | Second AIS output |
| Plug | **OUT3** | adapter::types::unidirectional::AIS | Third AIS output |
| Plug | **OUT4** | adapter::types::unidirectional::AIS | Fourth AIS output |
| Plug | **OUT5** | adapter::types::unidirectional::AIS | Fifth AIS output |

## Functionality

1. The user sets the desired output index **K** (1 … 5).

2. A rising event at **REQ** triggers the demultiplexing action:

- The current value from the adapter input **IN** is read.
- This value is then written to the adapter output **OUTx** (x = K).

3. After successful writing, the event **CNF** is output.

4. If the index is outside the permissible range (e.g., 0 or >5), no action is performed, and **CNF** is still sent (or depending on the behavior – typically, no assignment occurs).

The internal processing is event-driven and follows the principle of classic demultiplexers: An input is switched to one of several outputs.

## Technical Features
- **Generic Function Block (FB):** The function block is designed as a generic template `GEN_AIS_DEMUX`. The present instance, `AIS_DEMUX_5`, is a special implementation with exactly five outputs. By modifying the generic type, demultiplexers with any number of outputs can be created.
- **Adapter-based I/O:** Instead of conventional data inputs/outputs, the block uses directed adapters of type `AIS`. This enables clean, component-oriented interconnection of complex signal types in the IEC 61499 environment.
- **Error Handling:** If the index **K** is invalid, the incoming value is not passed to any output; however, the acknowledgment signal **CNF** is still output to avoid blocking the calling block.

## State Overview

The internal state machine is kept simple:

[IDLE] → REQ (mit gültigem K) → [WRITE] → CNF → [IDLE]
↑
Bei ungültigem K: sofort CNF, kein Schreiben

- **IDLE:** Waiting for a REQ event.
- **WRITE:** Value transfer from **IN** to the selected **OUTx**.
- Upon completion (or in case of an error), **CNF** is sent and the machine returns to the IDLE state.

## Application Scenarios
- **Sensor Selection:** A single AIS sensor (e.g., an analog level sensor) can be switched to different actuators (valves, pumps) depending on the requirements.
- **Test and Diagnostic Systems:** Switching a test signal sequentially to several devices under test.
- **Routing Tasks:** Dynamic distribution of a data stream to different consumers in an automation system.

## Comparison with Similar Function Blocks

| Function Block | Description |
|--------------------|--------------|
**AIS_DEMUX_5** | Demultiplexer for 5-output AIS adapters |
**AIS_SELECT** | Multiplexer (selection of one of several inputs) |
**GEN_DEMUX** (generic) | General demultiplexer for simple data types (e.g., INT, REAL) – without an adapter |

Unlike a simple data demultiplexer, `AIS_DEMUX_5` operates at a more abstract adapter level and encapsulates all signal transmission (including consistency checks) within the adapter protocol.

## Conclusion

**AIS_DEMUX_5** is a compact, generic function block from the IEC 61499 library that provides clean, adapter-based demultiplexing functionality for AIS signals. Thanks to its generic template, it can be flexibly adapted to the number of outputs required. The simple event-driven interface makes it easy to integrate into higher-level control logic, while the use of adapters ensures high reusability and encapsulation.
