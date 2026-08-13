# AUDI_DEMUX_5

![AUDI_DEMUX_5](./AUDI_DEMUX_5.svg)

* * * * * * * * * *
## Introduction

The function block `AUDI_DEMUX_5` is a generic demultiplexer for the unidirectional `AUDI` adapter. It forwards an adapter value present at its input adapter `IN` to one of five output adapters (`OUT1` to `OUT5`). The target adapter is selected via the data input `K`.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Set Index K (triggers processing) |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation of Set Index K |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index (1..5) for selecting the output adapter |

### **Data Outputs**

No data outputs available.

### **Adapters**

**Plugs (Output Adapters)**

| Name | Type | Comment |
|------|-----|-----------|
| OUT1 | Adapter `AUDI` (unidirectional) | First Output |
| OUT2 | Adapter `AUDI` (unidirectional) | Second Output |
| OUT3 | Adapter `AUDI` (unidirectional) | Third Output |
| OUT4 | Adapter `AUDI` (unidirectional) | Fourth Output |
| OUT5 | Adapter `AUDI` (unidirectional) | Fifth Output |

**Socket (Input Adapter)**

| Name | Type | Comment |
|------|-----|-----------|
| IN | Adapter `AUDI` (unidirectional) | Input Value to Demultiplex |

## Functionality

This module operates as a 1-to-5 demultiplexer. As soon as a signal arrives at the event input `REQ`, the current value of the input `K` is evaluated (an integer value between 1 and 5 is expected). The adapter value present at the adapter socket `IN` is then passed through to the output adapter (`OUT1` to `OUT5`) determined by `K`. After successful switching, the event output `CNF` is sent to confirm processing.

## Technical Features

- The function block is implemented as a **generic FB**, identified by the attribute `GenericClassName` with the value `'GEN_AUDI_DEMUX'`. This allows for easy adaptation to a different number of outputs.
- No time delays or state machines are defined in the FB; switching is event-driven and instantaneous.
- All adapters used are of type `adapter::types::unidirectional::AUDI`, which is designed for directed data transmission.

## State Overview

The function block does not have an explicit state machine. Its behavior can be reduced to a simple sequence:

1. Wait for event `REQ`.
2. Read `K`.
3. Switch `IN` to the corresponding output adapter. 4. Sending `CNF`.

## Application Scenarios

- **Audio/Signal Distribution:** An incoming audio stream (via the `AUDI` adapter) is routed to one of five different processing paths or output devices, depending on the selected index.
- **Routing Systems:** In modular automation solutions, this component can be used to dynamically switch data flows.
- **Test Environments:** Switching between different test sources to a common destination, or vice versa.

## Comparison with Similar Components

The `AUDI_DEMUX_5` is similar to other demultiplexers such as the `AUDI_DEMUX_2` or `MUX_4`, but differs in the number of outputs and the specific use of the `AUDI` adapter type. Unlike multiplexers (which combine multiple inputs into one output), this component acts as a distributor from one input to multiple outputs. Generic versions can be created by simply changing the number of adapter ports.
...``AUDI_DEMUX_5`` is similar to other demultiplexers such as the `AUDI_DEMUX_2` or `MUX_4`, but differs in the number of outputs and the specific use of the `AUDI` adapter type.
## Change Detection

The selected output plug is only written and its adapter event only sent if the incoming value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates on unrelated peers.


## Conclusion

The `AUDI_DEMUX_5` is a compact, generic solution for the targeted forwarding of `AUDI` adapter data. Thanks to its clear interface and event-driven processing, it can be easily integrated into higher-level control logic and is particularly suitable for applications that require dynamic switching of signal paths.
