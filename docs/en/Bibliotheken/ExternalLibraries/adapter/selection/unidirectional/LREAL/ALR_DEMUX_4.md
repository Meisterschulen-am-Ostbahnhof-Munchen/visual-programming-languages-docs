# ALR_DEMUX_4
![ALR_DEMUX_4](./ALR_DEMUX_4.svg)
* * * * * * * * * *
## Introduction
The function block **ALR_DEMUX_4** acts as a demultiplexer for data stream-oriented ALR (Agricultural Logic Router) signals. It distributes an incoming ALR data stream to one of four identical outputs. The destination output is selected dynamically via the index K, which is evaluated upon an event at the REQ input. The output is acknowledged via the event output CNF. The block is designed generically and can be parameterized for various ALR types.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| **REQ** | Trigger for switching the data path. The corresponding data input K is evaluated. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| **CNF** | Confirmation that the data path has been set according to K. |

### **Data Inputs**

| Name | Type | Description |

|------|--------|--------------|

| **K** | UINT | Index of the desired output (value range 1-4). |

### **Data Outputs**

No direct data outputs are available. Data is transmitted exclusively via the adapter interfaces.

### **Adapters**

| Type | Name | Direction | Description |

|-----|------|----------|--------------|

Socket (Input) | **IN** | Unidirectional | ALR input to be distributed. |

Plug (Output) | **OUT1** | Unidirectional | First destination output (address 1). |

Plug (Output) | **OUT2** | Unidirectional | Second destination output (address 2). |

Plug (Output) | **OUT3** | Unidirectional | Third destination output (address 3). |

Plug (Output) | **OUT4** | Unidirectional | Fourth destination output (address 4). |

## Functionality

1. No data path is active in the idle state.

2. When a **REQ** event is received, the function block reads the current value of **K**.

3. Depending on **K** (1–4), the ALR data stream from socket **IN** is routed to the corresponding plug **OUTx**. All other outputs remain inactive.

4. After successful switching, the event **CNF** is sent.

5. If **K** is outside the valid range, no connection is established; however, **CNF** is still sent (the action has no effect).

## Technical Features
- **Generic Type**: The function block can be specialized for any ALR subtype via the attribute `GenericClassName`, e.g., for different data formats or protocols.
- **Unidirectional Adapters**: The ALR interfaces are unidirectional, meaning data flows only from the socket to the plugs.
- **No State Machine**: The function block operates in an event-driven manner without an internal state. Switching occurs purely combinatorially upon REQ.
- **License**: This function block is licensed under the EPL 2.0 (Eclipse Public License).

## State Overview
The function block does not have an explicit state machine. Its behavior can be described as an immediate reaction to the REQ event:

- **Before REQ**: No data path is active.
- **After REQ with a valid K**: The selected OUT path is active (until a new REQ arrives).

## Application Scenarios
- **Distribution of Control Commands** in Agricultural Engineering: A central ALR data stream is distributed to various actuators (e.g., valves, bars) depending on the machine's status.
- **Routing of Measured Values** in Fieldbus Systems: A sensor provides data that is alternately sent to multiple evaluation units via the demultiplexer.
- **Test and Simulation Environments**: Targeted injection of test data into one of several downstream blocks.

## Comparison with Similar Components
- **ALR_MUX_4**: This multiplexer collects data from four inputs and passes it to a single output – the inverse function of a demultiplexer.
- **ALR_DEMUX_2**: A demultiplexer with only two outputs, suitable for smaller configurations.
- **Generic DEMUX Components**: Other implementations often use direct data inputs/outputs, while ALR_DEMUX_4 is based on adapters, allowing for more flexible type adaptation.

## Conclusion

**ALR_DEMUX_4** is a compact, event-driven demultiplexer for ALR data streams. Its adapter-based interface and generic architecture make it versatile for use in automated agricultural systems. It allows for simple, index-driven signal distribution without additional logic and is particularly useful in scenarios with multiple identical actuators or sensors.