# AB_DEMUX_3

![AB_DEMUX_3](./AB_DEMUX_3.svg)

* * * * * * * * * *
## Introduction

The **AB_DEMUX_3** is a generic demultiplexer for the adapter type `unidirectional::AB`. It forwards a value present at socket **IN** to one of three adapter plugs, **OUT1**, **OUT2**, or **OUT3**, depending on the index **K**. The function block is controlled via the **REQ** event.
## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| **REQ** | Sets the index **K** and triggers demultiplexing. (Linked to **K**) |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| **CNF** | Confirms successful setting of index **K**. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|--------------|
| **K** | UINT | Index of the target output (1 = OUT1, 2 = OUT2, 3 = OUT3). |

### **Data Outputs**

No data outputs available – output is handled via the adapter plugs.

### **Adapters**

| Adapter | Direction | Type | Description |
|-----------|-----------------|-------------------------------|--------------|
| **IN** | Socket (Input) | `adapter::types::unidirectional::AB` | Input value that is demultiplexed. |
**OUT1** | Plug (Output) | `adapter::types::unidirectional::AB` | First output (index 1). |
**OUT2** | Plug (Output) | `adapter::types::unidirectional::AB` | Second output (index 2). |
**OUT3** | Plug (Output) | `adapter::types::unidirectional::AB` | Third output (index 3). |

## Functionality

The function block waits for the **REQ** event. As soon as this occurs, the value of **K** is evaluated:

- If **K = 1**, the value present at socket **IN** is transferred to plug **OUT1**.
- If **K = 2**, the transfer to **OUT2** takes place.

**OUT2** - When **K = 3**, the data is transferred to **OUT3**.

For all other values of **K**, the output state remains unchanged (no output). After the operation is complete, the **CNF** event is sent.

Data flow is bidirectional via the adapters, but only the direction from the socket to the plugs is controlled.

## Technical Features

- **Generic Block**: The function block is defined as a generic class (`GenericClassName = 'GEN_AB_DEMUX'`). The specific data type is configured during instantiation by the development system.
- **Adapter Type**: All adapters are of type `unidirectional::AB`, which requires a simple but fixed connection to this bidirectional interface type.
- **Index Range**: The input **K** is declared as `UINT`; only the values 1, 2, and 3 result in forwarding. Other values have no effect.
- **Event-driven**: Demultiplexing occurs only upon the **REQ** event – there is no automatic passthrough or cyclic behavior.

## State Overview

The function block (FB) does not have an explicit state machine (ECC). Its functionality is implemented purely event-driven: After a **REQ**, the assignment is performed synchronously and **CNF** is output. There are no internal states or delays.

## Application Scenarios

- **Data Path Switching**: An AB data value supplied by a higher-level controller should be forwarded to different consumers (e.g., actuators, subsystems) depending on an index.
- **Selective Activation**: In process automation, the same sensor value (adapter-based) can be switched to different evaluation blocks depending on the operating mode.
- **Test and Simulation Environments**: Targeted redirection of data streams for testing purposes.

## Comparison with Similar Function Blocks

- **AB_MUX**: The multiplexer combines multiple adapter inputs into a single output – the inverse function.
- **AB_DEMUX_N**: Variants with more or fewer outputs (e.g., `AB_DEMUX_2`, `AB_DEMUX_4`). This function block is specifically designed for three outputs.
- **Manual Switching**: Alternatively, switching could be implemented using conditional assignments in a script-based function block – however, **AB_DEMUX_3** offers a compact and standardized solution.

## Conclusion

**AB_DEMUX_3** is a simple yet effective function block for demultiplexing AB adapter data. It neatly encapsulates index selection in a reusable function block and is particularly suitable for systems requiring flexible, event-driven data forwarding. Furthermore, its generic nature allows for easy adaptation to different data types of the AB interface.
