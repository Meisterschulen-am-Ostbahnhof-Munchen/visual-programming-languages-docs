# AIS_DEMUX_3
![AIS_DEMUX_3](./AIS_DEMUX_3.svg)

* * * * * * * * * *
## Introduction
The function block **AIS_DEMUX_3** is a generic demultiplexer for AIS adapter data. It forwards the AIS value present at socket `IN` to one of three output adapters, `OUT1`, `OUT2`, or `OUT3`, depending on an index `OUT1`, `OUT2`, or `OUT3`. This function block is suitable for distributing AIS signals in control systems.
## Interface Structure
### **Event Inputs**

| Event | Data Type | Description |

|----------|----------|--------------|

| REQ | Event | Starts the forwarding process. The current value of socket `IN` is sent to the output adapter specified by `K`. Input `K` is read simultaneously with this event. |

### **Event Outputs**

| Event | Data Type | Description |

|----------|----------|--------------|

| CNF | Event | Confirms the successful execution of the demultiplex operation. |

### **Data Inputs**

| Variable | Data Type | Description |

|----------|----------|--------------|

| K | UINT | Index of the desired output (1, 2, or 3). Values outside this range are ignored or result in no output (depending on the implementation). |

### **Data Outputs**

No data outputs are available. Output is exclusively via the adapter outputs.

### **Adapters**

| Type | Direction | Identifier | Description |

|-----|----------|-------------|--------------|

| Socket (Input) | input | IN | Receives the AIS value to be demultiplexed. Type: `adapter::types::unidirectional::AIS`. |

| Plug (Output) | output | OUT1 | First possible output for the demultiplexed AIS value. |

| Plug (Output) | output | OUT2 | Second possible output. |

| Plug (Output) | output | OUT3 | Third possible output. |

## Functionality
When an event occurs at input `REQ`, the AIS value present at socket `IN` is read. This value is then passed to the output specified by data input `K` (OUT1 for K=1, OUT2 for K=2, OUT3 for K=3) via the respective plug. After successful transmission, event `CNF` is triggered.

## Technical Features
- The function block is implemented as a **generic function block** (identified by the attribute `GenericClassName`).
- It uses only **unidirectional AIS adapters**, meaning data flows only from the input to the outputs.
- The number of outputs is fixed at three.
- The logic is event-driven: Forwarding only occurs upon an explicit `REQ` event.

## State Overview
Since the function block does not have its own sequence control (ECC), it is permanently in a single **waiting state**. Upon the arrival of a `REQ` event, the demultiplex function is executed, and the `CNF` event is immediately generated – the function block then returns to the waiting state.

## Application Scenarios
- **Control of A-IS sensor data**: A sensor provides data via socket `IN`, and various devices (e.g., actuators or displays) receive the data via the corresponding outputs.
- **Switching between multiple A-IS data sources** (in combination with a multiplexer).
- **Prototyping**: Outputs can be flexibly assigned in the early development phase.

## Comparison with similar components
- **AIS_DEMUX_2**: Has only two outputs; accordingly, the value range of `K` is limited to 1..2.
- **Generic demultiplexers (e.g., for other data types)**: These usually work with simple data variables (e.g., `ANY`) and not with adapters. This component is specifically designed for AIS adapters.
- **AIS_MUX_3**: The multiplexer, as the counterpart, combines several AIS inputs into a single output.

## Conclusion

**AIS_DEMUX_3** is a simple yet functional demultiplexer for AIS data in IEC 61499-based systems. It allows for the targeted routing of an adapter signal to one of three outputs. Thanks to the adapters used, it can be easily integrated into existing AIS communication structures. The event-driven execution ensures deterministic behavior.
