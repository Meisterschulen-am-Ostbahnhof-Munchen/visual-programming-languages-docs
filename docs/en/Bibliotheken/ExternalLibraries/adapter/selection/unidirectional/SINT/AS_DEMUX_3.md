# AS_DEMUX_3

![AS_DEMUX_3](./AS_DEMUX_3.svg)

* * * * * * * * * *
## Introduction
The function block **AS_DEMUX_3** is a generic demultiplexer for the AS (adapter socket/plug) data type. It forwards an AS value received via the **IN** socket to one of three possible adapter outputs (**OUT1**, **OUT2**, **OUT3**). The target output is selected via the **K** index at the **REQ** event input.

## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Set Index K – triggers the forwarding |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation of Set Index K – confirms execution |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Index (0-based? or 1-based? typically 0-based) for selecting the target output |

### **Data Outputs**

No direct data outputs – data is passed through the adapters.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| Plug | OUT1 | adapter::types::unidirectional::AS | First Output |

| Plug | OUT2 | adapter::types::unidirectional::AS | Second Output |

| Plug | OUT3 | adapter::types::unidirectional::AS | Third Output |

| Socket | IN | adapter::types::unidirectional::AS | Input value to be demultiplexed |

## Functionality
The function block waits for an event at **REQ**. Upon its arrival, the current value of the input **IN** (AS adapter) is copied to the output (OUT1, OUT2, or OUT3) determined by **K**. After successful transfer, an event is sent at the output **CNF**.

- If **K** is outside the valid range (0–2), the function remains undefined – typically, no output is written or no action is taken.

- The adapters are unidirectional, meaning data flows only from the socket **IN** to the selected plug.


``` ## Technical Features

- The function block (FB) is implemented as a **generic block** (GenericClassName `'GEN_AS_DEMUX'`), meaning it can be parameterized at runtime for any AS adapter type.

- The number of outputs is fixed at three; for other numbers, a corresponding FB (e.g., AS_DEMUX_2, AS_DEMUX_4) would need to be created.

- The adapter definition is provided via the library `adapter::types::unidirectional::AS`.

## State Overview

The function block essentially has one implicit state:

- **IDLE** – Waits for REQ.

Upon receiving REQ, it briefly enters a processing state, copies the input value, sends CNF, and then immediately returns to IDLE. A precise state machine is not defined in the XML, as it could be an ECC-controlled FB; however, the function logic is deterministic and simple.


## Application Scenarios

- **Signal Distribution** in automation technology: A sensor value (e.g., AS data) is to be forwarded to different actuators or controllers depending on the selection.

- **Routing** of adapter-based messages in modular systems, e.g., in agricultural machinery (as indicated by the copyright notice).

- **Testing and Simulation**: Switching between different data sources or sinks.

## Comparison with Similar Components

- **AS_MUX_3** (Multiplexer): Performs the reverse operation – selects one of three inputs and passes it to an output.

- **AS_DEMUX_2 / AS_DEMUX_4**: Same functionality, but with two or four outputs, respectively.

- **S_DEMUX** (Standard Demultiplexer): Works with elementary data types (e.g., BOOL, INT); The present function block (FB) is specifically designed for AS adapters and is therefore easier to integrate into adapter-based architectures.

## Conclusion
The **AS_DEMUX_3** is a simple yet essential building block for dynamically forwarding AS data to one of three outputs. Its generic nature makes it flexible, especially in modular automation solutions that rely on adapter communication. Its clear interface (REQ/CNF + Index K) allows for efficient integration into control logic.