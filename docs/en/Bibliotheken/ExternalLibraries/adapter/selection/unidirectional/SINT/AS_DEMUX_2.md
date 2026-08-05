# AS_DEMUX_2
![AS_DEMUX_2](./AS_DEMUX_2.svg)

* * * * * * * * * *
## Introduction
The **AS_DEMUX_2** (Generic FB) is an application-neutral, event-driven demultiplexer for adapters of type `adapter::types::unidirectional::AS`. It distributes an incoming data value (via the **IN** socket) to one of two possible output adapters (**OUT1** or **OUT2**). The destination is selected via the data input **K**.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Variables |
|------|-----|------------|---------------|
| REQ | Event | Set Index K | K |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation of Set Index K |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | index |

### **Data Outputs**

None.

### **Adapters**
* **IN** (Socket): `adapter::types::unidirectional::AS` – Input value to be demultiplexed.
* **OUT1** (Plug): `adapter::types::unidirectional::AS` – First output channel.
* **OUT2** (Plug): `adapter::types::unidirectional::AS` – Second output channel.

## Functionality

The function block operates according to a simple 1-to-2 demultiplex principle. An external call to the **REQ** event triggers the evaluation of the **K** index. The value currently present at socket **IN** is forwarded to the corresponding adapter plug, depending on the value of **K**:

- If `K = 0` → Data is passed to **OUT1**.
- If `K = 1` → Data is passed to **OUT2**.
- For other values of **K** (other than 0 or 1), the behavior can be considered either undefined or an error case – in such cases, the function block does not output anything but still acknowledges **CNF**.

After successful forwarding, the **CNF** event is output.

## Technical Features
- **Generic Block**: The function block (FB) is declared as generic (`GenericClassName = 'GEN_AS_DEMUX'`) and can therefore be used in various type variations of the adapter `AS`.
- **Adapter-Based**: The interfaces are fully implemented via adapters, enabling high modularity and reusability in various control architectures.
- **No State Machines**: The FB does not have an explicit state machine; processing is purely event-driven and combinatorial.

## State Overview

Since the function block does not store an internal state (purely combinatorial behavior), only a single implicit state exists:

| State | Description |
|---------|--------------|
| *Idle* | Waiting for the **REQ** event. After **REQ**, the output is immediately selected, the data is forwarded, and **CNF** is sent. Return to *Idle*. |

## Application Scenarios
- **Data Distribution in Modular Automation Systems**: A sensor value (e.g., speed, pressure) should be selectively forwarded to various downstream processing units.
- **Channel Switching**: In a controller with multiple actuators, the demultiplexer can be used to switch a common data stream to the currently active channel.
- **Test and Debug Functions**: Temporary redirection of diagnostic data to a separate monitoring path.

## Comparison with Similar Function Blocks

| Function Block | Outputs | Special Features |
|----------|----------|--------------|
| **AS_DEMUX_2** | 2 | Basic two-channel demultiplexer, generic |
| **AS_DEMUX_4** (hypothetical) | 4 | Extended version with four outputs |
**AS_MUX_2** | – | Multiplexer: multiple inputs to one output |
**AS_SELECT** | – | Direct adapter switch without indexing (hardwired) |

The AS_DEMUX_2 is specifically optimized for the bidirectional (but here used unidirectionally) AS adapter interface and, unlike general data blocks, operates exclusively at the adapter level.

## Conclusion

The **AS_DEMUX_2** is a simple yet flexible demultiplexer for adapter-based applications. Thanks to its generic design and purely event-driven control, it is ideally suited for dynamic switching tasks in IEC 61499 systems where a data stream needs to be selectively routed to two paths. Its low complexity facilitates integration and makes it a reliable basic component in modular control architectures.
