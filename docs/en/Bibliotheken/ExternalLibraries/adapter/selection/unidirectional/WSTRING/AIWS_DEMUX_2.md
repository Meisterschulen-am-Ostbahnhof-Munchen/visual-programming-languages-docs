# AIWS_DEMUX_2

![AIWS_DEMUX_2](./AIWS_DEMUX_2.svg)

* * * * * * * * * *
## Introduction

The **AIWS_DEMUX_2** is a generic demultiplexer function block for the AIWS protocol. It forwards an incoming AIWS data stream to one of two outputs, controlled by an index. The block is event-driven and operates unidirectionally.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Sets the index K and starts the forwarding |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirms index processing |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index that determines the destination output (e.g., 0 → OUT1, 1 → OUT2) |

### **Data Outputs**

None.

### **Adapters**

| Type | Name | Direction | Comment |
|-----|------|----------|-----------|
| AIWS (unidirectional) | IN | Socket (Input) | Input data stream to be demultiplexed |
| AIWS (unidirectional) | OUT1 | Plug (Output) | First destination output |
| AIWS (unidirectional) | OUT2 | Plug (Output) | Second destination output |

## Functionality

The function block waits for a **REQ** event. Upon arrival, the value of the data input **K** is evaluated:

- If `K = 0`, the current data of the **IN** adapter is passed to the **OUT1** adapter.
- If `K = 1`, the data is passed to **OUT2**.
- For other values of K (if any), the output remains unchanged (or an error state is assumed – depending on the implementation).

After successful forwarding, the **CNF** event is output. The function block operates strictly sequentially and does not block any further REQ events during processing.

## Technical Features

- **Generic Type**: The function block is declared as a generic function block (`GenericClassName = 'GEN_AIWS_DEMUX'`), so it can be parameterized for different numbers of outputs. The specific implementation `AIWS_DEMUX_2` has two outputs.
- **Adapter-based**: The interfaces are implemented via adapters of type `adapter::types::unidirectional::AIWS`, enabling a clean separation of control and data flow.
- **Event-driven processing**: The demultiplexing operation is triggered only by the REQ event; without an event, all outputs remain unchanged.
- **No data outputs**: Output is exclusively via the adapter plugs; there are no separate data variables.

## State overview

The function block has a simple state logic (not explicitly shown in the ECC, but implicit):

- **IDLE**: Waiting for a REQ event.
- **PROCESS**: Evaluating K and forwarding the data to the corresponding OUT adapter.
- **DONE**: Sends the CNF event and returns to the IDLE state.

Error states (e.g., invalid index) can optionally be represented by an error event in the implementation, but are not defined in this interface.

## Application Scenarios

- **Sensor Value Distribution**: An analog sensor (e.g., an AIWS-compliant temperature sensor) provides data that is forwarded to different actuators or controllers depending on the index.
- **Channel Selection**: Two different control paths can be operated in a controller, e.g., for heating and cooling.
- **Switching Between Operating Modes**: The index K can originate from a higher-level state machine and send the data to the currently active subprocess.

## Comparison with Similar Function Blocks

- **AIWS_DEMUX_N**: Generalized variant with N outputs – this function block is a specific implementation with two outputs.
- **Standard DEMUX (e.g., for ANY data types)**: Often uses data inputs and outputs instead of adapters; the adapter approach encapsulates the protocol and facilitates reuse.
- **AIWS Splitter**: Unlike a splitter (which sends data to all outputs simultaneously), the demultiplexer selectively chooses a path.

## Change Detection

The selected output plug is only written and its adapter event only sent if the incoming value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates on unrelated peers.


## Conclusion

The **AIWS_DEMUX_2** is a compact, event-driven demultiplexer for AIWS protocol data. It is ideally suited for applications where a data stream needs to be routed to one of two destinations on demand. Its generic architecture allows for easy expansion to more channels without requiring fundamental changes to the interface.
