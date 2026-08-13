# AI_MUX_3

![AI_MUX_3](./AI_MUX_3.svg)

* * * * * * * * * *
## Introduction

The function block **AI_MUX_3** is a generic analog multiplexer with three adapter inputs (IN1, IN2, IN3). Depending on the index K, one of these inputs is routed to the adapter output OUT. The block operates in an event-driven manner: A REQ event triggers the selection and is confirmed with CNF.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Set Index K |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation of Set Index K |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index |

### **Data Outputs**

No dedicated data outputs – output data is provided via the OUT adapter.

### **Adapters**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| Plug (Output) | OUT | adapter::types::unidirectional::AI | IN1 for K=0, IN2 for K=1, IN3 for K=2 |
| Socket (Input) | IN1 | adapter::types::unidirectional::AI | Input value 1 |
| Socket (Input) | IN2 | adapter::types::unidirectional::AI | Input value 2 |
| Socket (Input) | IN3 | adapter::types::unidirectional::AI | Input value 3 |

## Functionality

The function block waits for a REQ event. As soon as it arrives, the current value of index K is evaluated:

- **K = 0** → Adapter IN1 is connected to output OUT.
- **K = 1** → Adapter IN2 is connected to output OUT.
- **K = 2** → Adapter IN3 is connected to output OUT.
- **K > 2** → No connection is made; output OUT remains unchanged (undefined behavior).

The connection is made via the unidirectional adapter definitions. The data flows are exchanged depending on the implementation of the underlying adapter types. After successful processing, the CNF event is triggered.

## Technical Features

- **Adapter-Based Interface**: The function block utilizes the 4diac adapter concept for flexible coupling of analog signal sources and sinks.
- **Generic Implementation**: Thanks to the attribute `GenericClassName = 'GEN_AI_MUX'`, the block can be used in various contexts with different adapter implementations (e.g., different value ranges or units).
- **Unidirectional Data Types**: Both inputs and output use unidirectional adapters (`unidirectional::AI`), enabling simple forwarding of measured values without feedback.

## State Overview

The function block does not have an explicit state machine. The logic is limited to event-driven switching, which occurs in a single-step cycle.

## Application Scenarios

- **Measurement Acquisition**: Selection between three different analog sensors (e.g., temperature, pressure, level) via a control command.
- **Signal Switching**: In a controller, the index K can be dynamically set by a higher-level logic to switch between different signal sources.
- **Redundancy**: Switching to a backup sensor in case of primary sensor failure.

## Comparison with Similar Function Blocks

- **Standard Multiplexer with Data Inputs**: Unlike function block types that use direct `ANY` data inputs, `AI_MUX_3` operates purely on an adapter basis. This allows for better modularity, as the attached adapters themselves can contain complex data structures or processing logic.
- **Multi-Channel Multiplexer**: A function block with more than three channels (e.g., AI_MUX_4) would function analogously, but the adapter definition allows for expansion through multiple instances or a custom function block with more sockets.

## Change Detection

The selected output plug (`OUT`) is only written and its adapter event only sent if the incoming value differs from the value currently held on `OUT`. If the value is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The **AI_MUX_3** is a compact, generic analog multiplexer for the 4diac IDE. Thanks to its adapters and event-driven control, it is particularly well-suited for flexible, modular automation solutions where multiple analog signal sources need to be selected and routed to a single output.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
