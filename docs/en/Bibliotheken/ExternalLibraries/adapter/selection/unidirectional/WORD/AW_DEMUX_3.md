# AW_DEMUX_3
![AW_DEMUX_3](./AW_DEMUX_3.svg)

* * * * * * * * * *
## Introduction
The function block **AW_DEMUX_3** is a generic demultiplexer for the unidirectional adapter type `AW`. It distributes an incoming data value, provided via the socket adapter `IN`, to one of three output adapters (`OUT1`, `OUT2`, `OUT3`), depending on an integer index `K`. The function block is controlled by the event `REQ` and acknowledges the distribution with `CNF`.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `REQ` | Event | Set Index K; triggers the distribution. |

The event input `REQ` triggers the demultiplex operation. The current value of the data input `K` determines which output adapter the incoming value is forwarded to.

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| `CNF` | Event | Confirmation of Set Index K. |

After successful distribution, the event `CNF` is triggered. It indicates that the data value is available at the selected output.

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `K` | UINT | index (1-based, expected range 1…3) |

The input `K` determines which of the three outputs (`OUT1`, `OUT2`, `OUT3`) is used. Values outside the range 1–3 are ignored or do not result in any forwarding (depending on the specific implementation).

### **Data Outputs**

This function block does not have explicit data outputs. All output data is provided via the adapter interfaces.

### **Adapter**

| Type | Name | Direction | Comment |
|-----|------|----------|-----------|
| `adapter::types::unidirectional::AW` | `IN` | Socket | Input value to be demultiplexed |
| `adapter::types::unidirectional::AW` | `OUT1` | Plug | 1st Output |
| `adapter::types::unidirectional::AW` | `OUT2` | Plug | 2nd Output |
| `adapter::types::unidirectional::AW` | `OUT3` | Plug | 3rd Output |

All adapters are of the same unidirectional type `AW`. Socket `IN` receives the data value to be distributed. The three plugs `OUT1`…`OUT3` represent the respective outputs.

## Functionality

1. The function block waits for an event at input `REQ`.

2. Upon arrival of `REQ`, the current value of data input `K` is read.

3. Depending on `K` (values 1, 2, or 3), the data value received via socket `IN` is passed through to the corresponding plug (`OUT1`, `OUT2`, or `OUT3`). All other outputs remain unchanged or are put into a defined idle state (depending on the adapter definition).

4. After successful forwarding, the event `CNF` is output to confirm successful completion.

Since the adapter type `AW` is unidirectional, data transmission only occurs from the socket to the plugs; feedback from the consumers is not provided.

## Technical Features
- **Generic Block**: The function block is declared as a generic block (`GenericClassName = 'GEN_AW_DEMUX'`). This allows for later instantiation or adaptation to different output numbers, even though the current version has a fixed three outputs.
- **Unidirectional Communication**: The adapter used, `adapter::types::unidirectional::AW`, only allows data flow from the sender (socket) to the receiver (plug). No feedback or acknowledgment from connected consumers is included.
- **No internal state machine**: The functionality is purely event-driven and does not use an explicit state machine (ECC). The function block reacts immediately to each `REQ` event with the distribution.
- **Index check**: The input `K` is of type `UINT`. Only the values 1, 2, or 3 are expected. Deviating values should be excluded by the calling application.

## State overview

The function block **AW_DEMUX_3** does not have a modeled internal state machine. Its behavior is deterministic and purely transaction-based:

- In its idle state, it waits for `REQ`.
- At `REQ`, the distribution is executed, and `CNF` is immediately output.
- It then returns to its idle state.

There are no hold, error, or special states.

## Application Scenarios
- **Signal Distribution in Automation**: An analog or digital measured value (e.g., temperature, pressure) from a sensor unit is to be forwarded to different actuators or control blocks depending on the operating mode.
- **Channel Switching**: In a communication chain, an incoming data signal is switched to one of three downstream processing paths by an index.
- **Test and Simulation Environments**: The function block can be used to distribute a generic data stream to various test modules.

## Comparison with Similar Function Blocks

| Function Block | Description | Difference to AW_DEMUX_3 |
|----------|--------------|---------------------------|
**AW_MUX_3** | Multiplexer – combines three inputs into one output | Reverse data direction: DEMUX distributes, MUX combines |
**AW_DEMUX_2** | Demultiplexer with two outputs | Fewer outputs |
**E_DEMUX** (Event Demux) | Distributes events instead of data values | AW_DEMUX_3 distributes data via adapters, not events |
**GEN_DEMUX** (Generic, non-adapter-specific) | General demultiplexer with an adapter-generic interface | AW_DEMUX_3 is specifically designed for the `AW` type |
**AW_DEMUX_3** (Generic, non-adapter-specific) | General demultiplexer with an adapter-generic interface | AW_DEMUX_3 is specifically designed for the `AW` type |
**AW_DEMUX_2** | Demultiplexer with two outputs | Fewer outputs |
**AW_DEMUX_2** (Event Demux) | Distributes events instead of data values | AW_DEMUX_3 distributes data via adapters, not events |
**AW_DEMUX_3** (Generic, non-adapter-specific) | General demultiplexer with an adapter-generic interface | AW_DEMUX_3 is specifically designed for the `AW` type |

**AW_DEMUX_3** (Generic, non-adapter-specific) | The biggest difference compared to pure data or event demultiplexers is the use of the `AW` adapter type, which encapsulates standardized, unidirectional data transmission within the 4diac IDE.

## Conclusion

The **AW_DEMUX_3** is a compact, generic demultiplexer for the `AW` adapter type. Event-driven, it distributes input data to three outputs based on an index. Its simple, transaction-oriented operation without state machines makes it a reliable component for targeted signal routing in industrial control and automation solutions. Its generic nature also allows for flexible reuse in different projects.

**AW_DEMUX_3** ---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
