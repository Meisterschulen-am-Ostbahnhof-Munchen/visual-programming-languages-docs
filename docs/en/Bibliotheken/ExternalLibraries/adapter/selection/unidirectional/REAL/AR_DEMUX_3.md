# AR_DEMUX_3
![AR_DEMUX_3](./AR_DEMUX_3.svg)

* * * * * * * * * *
## Introduction
The function block **AR_DEMUX_3** is a generic demultiplexer for unidirectional adapters of type `adapter::types::unidirectional::AR`. It distributes an incoming adapter data stream (via socket `IN`) to one of three output adapters (`OUT1`, `OUT2`, `OUT3`), depending on an index value `K`. The block is triggered by an event `REQ` and confirms the operation with `CNF`. This enables flexible and dynamic signal routing in adapter-based IEC 61499 applications.
## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| `REQ` | Starts the demultiplex operation. The data value `K` is evaluated to establish the connection between `IN` and one of the three outputs. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| `CNF` | Confirms successful execution of the demultiplexing operation after processing `REQ`. |

### **Data Inputs**

| Name | Type | Description |

|------|-----|---------------|

| `K` | `UINT` | Index (1–3) that determines which output (`OUT1` to `OUT3`) is connected to the input adapter `IN`. Values outside the valid range result in no connection. |

### **Data Outputs**
None.

### **Adapters**

| Name | Type | Direction | Description |

|------|------|----------|--------------|

| `IN` | `adapter::types::unidirectional::AR` | Socket | Input adapter that provides the data to be distributed. |

| `OUT1` | `adapter::types::unidirectional::AR` | Plug | First output adapter (Index 1). |

| `OUT2` | `adapter::types::unidirectional::AR` | Plug | Second output adapter (Index 2). |

| `OUT3` | `adapter::types::unidirectional::AR` | Plug | Third output adapter (Index 3). |

## Functionality

The function block behaves like a 1-to-N demultiplexer at the adapter level. Upon receiving a `REQ` event, the current value of index `K` is read. Depending on `K`, the logical connection between socket `IN` and the corresponding plug (`OUT1`, `OUT2`, or `OUT3`) is activated. The output event `CNF` is then sent to acknowledge the successful switchover. The unselected outputs remain inactive.

## Technical Features

- **Generic Function Block**: The function block is declared as a generic type (`GEN_AR_DEMUX`) and can be reused for different output numbers (here, 3).
- **Adapter-Based Communication**: Data exchange occurs exclusively via unidirectional adapters of type `AR`. This enables loose coupling and easy reuse of the interfaces.
- **No Data Outputs**: All data transfer occurs via the adapters, not via separate variables.
- **Value Range of K**: The index `K` of type `UINT` should be restricted to the values 1 to 3 to ensure a defined assignment.

## State Overview
Since this is a service-oriented generic function block (FB), no explicit state engine is included in the XML definition. However, its functionality can be reduced to two logical states:

1. **IDLE**: Waiting for a `REQ` event. All output adapters are disconnected from `IN`.

2. **ACTIVE**: Upon receipt of `REQ`, the index `K` is evaluated and the connection is established. After sending `CNF`, the FB immediately returns to the IDLE state.

## Application Scenarios
- **Data Distribution in Control Systems**: Selection of a target device or control unit from several identically structured adapters.
- **Switching Signal Sources**: In control systems, the demux can be used to alternately route a measured value to different displays or processing blocks.
- **Prototype and Test Environments**: Rapid configuration of data paths without changing the network topology.

## Comparison with Similar Components
Compared to classic IEC 61439 demultiplexers (e.g., `DEMUX_BOOL`, `DEMUX_INT`), the `AR_DEMUX_3` operates at the adapter level. While conventional demultiplexers distribute individual data values to multiple output variables, this component transmits complete adapter interfaces. This reduces wiring and increases abstraction. Similar components, such as the `MUX_3` (multiplexer), operate in reverse, combining multiple adapter inputs into a single output.

## Conclusion

The `AR_DEMUX_3` is a specialized yet flexible component for the dynamic distribution of adapter connections in IEC 61499 systems. Its generic nature and simple index control make it ideal for modular automation solutions where a data path needs to be routed to different receivers. The use of unidirectional AR adapters ensures a clear separation of control and data flow.
