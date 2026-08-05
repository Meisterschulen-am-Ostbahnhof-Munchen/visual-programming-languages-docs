# AUS_DEMUX_3
![AUS_DEMUX_3](./AUS_DEMUX_3.svg)
* * * * * * * * * *
## Introduction
The function block **AUS_DEMUX_3** implements a generic demultiplexer for OFF signals. It distributes an input value (of adapter type `AUS`) received via a socket to one of three outputs provided via plugs. The active output is selected using the index `K`. The adapters used are unidirectional and allow loose coupling between the components.
## Interface Structure

### **Event Inputs**

| Name | Type | With Variables | Comment |

|------|-------|----------------|-------------------------|

| REQ | Event | K | Sets Index K |

### **Event Outputs**

| Name | Type | Comment |

|------|-------|-----------------------------------|

| CNF | Event | Acknowledge after setting K |

### **Data Inputs**

| Name | Type | Comment |

|------|------|----------------|

| K | UINT | Selection Index (1..3) |

### **Data Outputs**

No dedicated data outputs; output is handled via the adapters.

### **Adapters**

| Name | Type | Direction | Comment |

|------|-----------------------------------------|----------|----------------------------------------|

| IN | `adapter::types::unidirectional::AUS` | Socket | Input value that is demultiplexed |

OUT1 | `adapter::types::unidirectional::AUS` | Plug | First output channel |

OUT2 | `adapter::types::unidirectional::AUS` | Plug | Second output channel |

OUT3 | `adapter::types::unidirectional::AUS` | Plug | Third output channel |

## Functionality

The function block operates in an event-driven manner. An event at input `REQ` takes the current value from `K` and forwards the output value present at socket `IN` to the corresponding plug (`OUT1`, `OUT2`, or `OUT3`). After successful forwarding, the event `CNF` is output. The value of `K` determines the destination channel:

- `K = 1` → Forwarding to `OUT1`
- `K = 2` → Forwarding to `OUT2`
- `K = 3` → Forwarding to `OUT3`

If `K` is outside the valid range, the output remains unchanged (no action).

## Technical Features
- **Generic Function Block** – The function block is implemented as a generic type (`GEN_AUS_DEMUX`) and can be parameterized for different channel numbers during instantiation.
- **Adapter-Based Interface** – The use of adapters according to IEC 61499 enables flexible and standardized signal coupling.
- **Unidirectional Data Transmission** – The OFF adapters only operate in one direction; this corresponds to typical applications such as controlling actuators.

## State Overview

The function block does not have an explicit state machine (ECC). Its functionality is purely event-driven: Each `REQ` event leads directly to selection and forwarding. This allows the function block to be used concurrently without internal states.

## Application Scenarios
- **Signal Distribution** – A central sensor or control value is to be forwarded to one of several actuators, depending on the selection.
- **Multipoint Control** – In agricultural machinery (e.g., HR agricultural technology), this is used to control various segment valves or actuators from a single signal.
- **Test Environments** – Targeted switching of a test signal to different devices under test.

## Comparison with similar modules

| Module | Description | Differences |

------------------|-----------------------------------------------------------|--------------------------------------------------------|

| **OFF_MUX** | Multiplexer: selects one of several inputs | Reverse data direction, multiple inputs, one output |

| **OFF_DEMUX_2** | Demultiplexer with two outputs | Reduced number of channels, same logic |

| **OFF_SWITCH** | Simple switch (on/off) | No channel selection, only forwarding/switching |

The **AUS_DEMUX_3** offers three dedicated outputs and is suitable for applications requiring a fixed number of channels.

## Conclusion

The **AUS_DEMUX_3** is a compact, event-driven demultiplexer for unidirectional OFF signals. Its adapter technology and generic design allow for flexible integration into automation systems compliant with IEC 61499. It is a particularly useful tool for targeted signal distribution in agricultural technology and distributed control systems.
