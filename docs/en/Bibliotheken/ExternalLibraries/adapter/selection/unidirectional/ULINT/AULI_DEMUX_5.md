# AULI_DEMUX_5
![AULI_DEMUX_5](./AULI_DEMUX_5.svg)

* * * * * * * * * *
## Introduction
The **AULI_DEMUX_5** is a unidirectional demultiplexer function block for the AULI adapter type. It routes an incoming AULI signal to one of five outputs. The target output is selected via the index input `K`. The function block is implemented as a generic function block (according to the Eclipse 4diac Generic FB concept) and is identified as `GEN_AULI_DEMUX` by the attribute `GenericClassName`.
## Interface Structure
### **Event Inputs**

| Name | Comment | With Variables |
|------|-----------|---------------|
| REQ | Set Index K | K |

### **Event Outputs**

| Name | Comment |
|------|-----------|
| CNF | Confirmation of Index Setting |

### **Data Inputs**

| Name | Type | Comment |
|------|------|-----------|
| K | UINT | Index for Selecting the Output (valid: 1…5) |

### **Data Outputs**
None (data is passed via the AULI adapters).

### **Adapters**
- **Socket (Input):** `IN` – Type `adapter::types::unidirectional::AULI`
Receives the signal to be distributed.

- **Plugs (Outputs):** `OUT1`…`OUT5` – each type `adapter::types::unidirectional::AULI`
The five possible destination adapters for the input signal.

## Functionality
The module operates in an event-driven manner:

1. A rising edge at the event input **REQ** triggers processing.

2. The value of the data input **K** is read. This must be in the range 1 to 5 (behavior for values outside this range is undefined).

3. The AULI signal present at the **IN** adapter is routed to the adapters **OUT1**…**OUT5** specified by `K`.

4. After successful switching, the **CNF** event is output.

Data is passed passively via the adapter interface; the function block itself does not hold any data variables.

## Technical Features
- **Generic Implementation:** The function block is declared as a generic type (`GenericClassName = 'GEN_AULI_DEMUX'`), which simplifies the creation of derived variants with a different number of outputs.
- **Unidirectional Adapters:** All AULI adapters are unidirectional (type `unidirectional`), so data flows only from the socket to the plugs.
- **No State Machine:** The demultiplexer's logic is purely combinatorial (event-driven) and does not require discrete states. An Execution Control Chart (ECC) is not necessary.
- **Typed Indices:** `K` is declared as `UINT`; it is assumed that the user only passes valid values (1-5). Range checking by the function block itself is not explicitly implemented.

## State Overview
Since the function block does not have a state machine, its behavior can be described by two implicit phases:

| State | Description |
|---------|--------------|
| IDLE | Waiting for a REQ event; no connection is active. |
| ACTIVE | Upon receiving a REQ, the corresponding connection is established and a CNF is triggered; Then immediately back to IDLE. |

The function block (FB) is not stateful; after each request (REQ), the switchover is executed immediately and without delay.

## Application Scenarios
- **Signal Distribution in Automation:** An AULI signal from a sensor should be passed on to different actuators depending on the parameter (e.g., operating mode).
- **Testing and Simulation:** Switching between different data sources (e.g., live data vs. recorded data) within a 4diac system.
- **Flexible Routing Logic:** Combination with other function blocks to implement a dynamic multiplexer/demultiplexer setup.

## Comparison with Similar Function Blocks
- **AULI_MUX_5 (Multiplexer):** The reverse function block – multiple inputs to one output. The demux function here offers the opposite functionality.
- **Standard Data Demultiplexers (e.g., for ANY):** Instead of AULI adapters, these often work with scalar data types (such as INT, BOOL) and have separate data outputs. The AULI_DEMUX_5 is specifically designed for the AULI interface.
- **Adapter Multiplexers from Other Libraries:** Depending on the environment, similar function blocks may exist, but these often use bidirectional adapters. The function block presented here is explicitly unidirectional and expects the AULI definition.

## Conclusion
The **AULI_DEMUX_5** is a compact, event-driven demultiplexer for unidirectional AULI adapters. It enables flexible signal routing to five target adapters and is particularly suitable for modular automation solutions where adapters serve as a standardized interface. Thanks to its generic basis, the function block can be easily adapted to different channel counts.

**AULI_DEMUX_5** ---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
