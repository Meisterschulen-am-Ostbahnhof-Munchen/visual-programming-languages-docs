# AD_DEMUX_4
No image available.
![AD_DEMUX_4](./AD_DEMUX_4.svg)

* * * * * * * * * *
## Introduction
The function block `AD_DEMUX_4` is a generic AD demultiplexer. It distributes an input received via a socket adapter to one of four output adapters. The selection of the active output is event-driven via an index.

## Interface Structure

### **Event Inputs**

| Name | Description |

|------|--------------|

| `REQ` | Sets the index `K` and triggers the switchover. |

### **Event Outputs**

| Name | Description |

|------|--------------|

| `CNF` | Confirms successful switching to the output determined by `K`. |

### **Data Inputs**

| Name | Type | Description |

|--------|--------|--------------|

| `K` | `UINT` | Index that determines the active output (value range depends on the specific parameterization – typically 0 to 3 or 1 to 4). |

### **Data Outputs**

No separate data outputs are available.

### **Adapters**

#### Socket (Input)

| Name | Type | Description |

|------|-----|--------------|

| `IN` | `adapter::types::unidirectional::AD` | Input adapter whose connection is redirected to the selected output. |

#### Plugs (Outputs)

| Name | Type | Description |

|-------|-----|--------------|

| `OUT1` | `adapter::types::unidirectional::AD` | First output. |

| `OUT2` | `adapter::types::unidirectional::AD` | Second output. |

| `OUT3` | `adapter::types::unidirectional::AD` | Third output. |

| `OUT4` | `adapter::types::unidirectional::AD` | Fourth output. |

## Functionality

As soon as an event arrives at input `REQ`, the current value of index `K` is evaluated. The function block connects the input adapter `IN` to the output adapter designated by `K` (`OUT1` … `OUT4`). After a successful switchover, the event `CNF` is output. The unselected outputs are inactive or disconnected at this time.

## Technical Features
- **Generic Function Block**: The function block is declared as generic (`GenericClassName = 'GEN_AD_DEMUX'`). This allows it to be parameterized with different adapter types.
- **Unidirectional**: Both the socket and the plugs are of type `unidirectional::AD`, meaning the data flow direction is fixed.
- **Event-Driven Switching**: Switching occurs exclusively upon the `REQ` event – no cyclic sampling is performed.

## State Overview

An explicit state machine is not defined in the function block's source code. Its behavior is limited to:

1. Waiting for a `REQ` event.

2. Evaluate the index `K`.

3. Connect `IN` to the corresponding `OUTX`.

4. Send `CNF`.

5. Return to standby mode.

## Application Scenarios
- Switching an analog measurement signal between different processing units.
- Controlling multiple actuators from a common signal source.
- Selecting one of several adapter-based communication paths (1-to-N switch).
- Flexible routing in modular automation systems based on IEC 61499.

## Comparison with similar components

The `AD_DEMUX_4` is the counterpart to the multiplexer component (e.g., `AD_SELECT`), which combines multiple inputs into a single output. While a multiplexer implements an **N-to-1** function, the demultiplexer provides a **1-to-N** function. Unlike classic demultiplexers for elementary data types, this component uses **adapter interfaces**, enabling it to route complex, composite signals or protocols in a structured manner.

## Conclusion

The `AD_DEMUX_4` is a versatile, generic adapter demultiplexer for the IEC 61499 environment. Due to its event-driven switching and the use of adapters, it is particularly suitable for flexible signal switches in modular automation and control systems.
