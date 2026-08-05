# AUDI_FB_CTD
![AUDI_FB_CTD](./AUDI_FB_CTD.svg)
* * * * * * * * * *
## Introduction
The function block **AUDI_FB_CTD** implements a down counter based on the UDINT data type. It is specifically designed for use with adapter interfaces and uses the types `AX` and `AUDI` for event-driven communication. The actual counting logic is executed by an internal function block of type `iec61131::counters::FB_CTD_UDINT`.
This function block fires an event on the output channel `CD`, `LD`, or `PV` with every update—regardless of whether the input was triggered by `CD`, `LD`, or `PV`. For change-based triggering, the use of a downstream `AX_D_FF` filter is recommended.

## Interface Structure

### **Event Inputs**

This function block does not have direct event inputs. All events are supplied via the connected **sockets** (adapter inputs).

| Socket (Adapter) | Type | Description |

|------------------|-------|-------------------------------------------|

| `CD` | `AX` | Countdown Event |

`LD` | `AX` | Load Event |

`PV` | `AUDI` | Preset Value Event |

### **Event Outputs**

| Name | Type | Description |

|------|--------|----------------------------------------------------|

`CNF` | Event | Acknowledge event after each processing step |

### **Data Inputs**

Data is transmitted via sockets as part of the adapter protocol.

| Socket (Adapter) | Data Type | Meaning |

------------------|-----------|-----------------------------------------|

| `CD.D1` | BOOL | Countdown command (TRUE = count)|

| `LD.D1` | BOOL | Load preset value command |

| `PV.D1` | UDINT | Preset counter value |

### **Data Outputs**

The output data is displayed via the plugs.

| Plug (Adapter) | Data Type | Meaning |

-----------|-------------------------------------|

| `Q.D1` | BOOL | Counter value = 0 (TRUE when reached)|

| `CV.D1` | UDINT | Current Counter Value |

### **Adapter**

| Direction | Name | Type | Description |

|----------|------|-------|----------------------------------------|

| Socket | `CD` | `AX` | Event-Driven Count Pulse (Down) |

| Socket | `LD` | `AX` | Event-Driven Preset Loading |

| Socket | `PV` | `AUDI` | Event-Driven Preset Selection |

| Plug | `Q` | `AX` | Output signal: Counter reading = 0 |

| Plug | `CV` | `AUDI` | Output signal: Current counter value |

## Functionality

Internally, a standardized IEC 61131 down counter (`FB_CTD_UDINT`) is used. The adapter events `CD.E1`, `LD.E1`, and `PV.E1` are combined into a single `REQ` event of the internal module. This causes the internal counter to be recalculated with every external event.

- **CD (Count Down)**: If the data signal `CD.D1 = TRUE` is present, the current counter value is decremented by 1. With `FALSE`, the value remains unchanged.
- **LD (Load)**: If `LD.D1 = TRUE` is present, the counter is set to the value of `PV.D1`.
- **PV (Preset Value)**: This event updates the stored preset value; a subsequent `LD` event adopts this value.

After each calculation, the output data `CV` (current counter value) and `Q` (TRUE if `CV = 0`) are output via the corresponding plugs. Simultaneously, the acknowledgment event `CNF` is triggered.

## Technical Features
- **Event Behavior**: For every input event (`CD`, `LD`, or `PV`), the output channel `Q` is activated. This means that a `Q.E1` event is sent even if the counter value or the `Q` state has not changed. This can lead to an unnecessarily high number of events in the subsequent logic.
- **Filtering Recommendation**: If the output event should only be triggered when `Q` actually changes state, an **AX_D_FF** (flip-flop) should be used as a filter. This suppresses repetitions.
- **Adapter-Based Connection**: All inputs and outputs are made via standardized adapters (`AX`, `AUDI`). This simplifies modular wiring and reuse in different environments.

## State Overview

The component has no explicit states. The internal counter operates according to the rules of an IEC 61131 CTD component. The current counter value is determined by the data signals.

## Application Scenarios
- **Event-driven Down Count**: Used in automation systems where a counter value is decremented by external events (e.g., number of workpieces processed).
- **Modular Control Components**: Integration into adapter-based architectures where standardized interfaces facilitate data exchange between different functional blocks.
- **Timer Simulation**: Combined with a clock generator to count a defined number of cycles and trigger an action when zero is reached.

## Comparison with Similar Function Blocks
- **Standard CTD** (e.g., `FB_CTD_UDINT`): Has direct input/output variables, no adapters. The `AUDI_FB_CTD`, on the other hand, encapsulates the logic and provides the signals via adapters, enabling a clean separation of event and data channels.
- **Upward Counting Unit (CTU)**: Unlike the `AUDI_FB_CTD`, a CTU counts upwards. Both can be implemented using adapters, but are designed for different counting directions.
- **Always fire feature**: Many standard counters only output a signal when the initial state changes. The `AUDI_FB_CTD` does this with every processing step, which is a unique feature and can be an advantage or disadvantage depending on the application.

## Conclusion

The `AUDI_FB_CTD`This is a flexible, adapter-based down counter for UDINT values. Its strength lies in its modular connectivity via standardized interfaces. However, developers should be aware of its unique event behavior (output pulse with each update) and correct it with a filter if necessary. This function block is well-suited for event-driven counting tasks in heterogeneous control environments.