# ALI_DEMUX_2

![ALI_DEMUX_2](./ALI_DEMUX_2.svg)

* * * * * * * * * *

## Introduction

The function block **ALI_DEMUX_2** is a generic demultiplexer for the ALI adapter type. It routes the value present at an input adapter to either one of two output adapters. The active output is selected via an index, which is set by an event input.

## Interface Structure

### **Event Inputs**

| Event | Comment |

|----------|-----------|

| `REQ` | Sets the index `K` and routes the input value to the corresponding output. |

### **Event Outputs**

| Event | Comment |

|----------|-----------|

| `CNF` | Confirms successful forwarding (without additional data). |

### **Data Inputs**

| Variable | Type | Comment |

|----------|-------|-----------|

| `K` | UINT | Index of the selected output (1 or 2). |

### **Data Outputs**

No separate data outputs – output is handled via the adapters.

### **Adapters**

| Type | Direction | Label | Comment |

|--------------|-----------|-------------|---------------------------------------|

| ALI | Input | `IN` | The input value to be demultiplexed. |

| ALI | Output | `OUT1` | First output channel (index 1). |

| ALI | Output | `OUT2` | Second output channel (index 2). |

## Functionality

An event at input `REQ` triggers the processing. The value of parameter `K` determines which of the two output adapters (`OUT1` or `OUT2`) receives the value from `IN`. After forwarding, an event is sent at output `CNF`.



``` The mapping is as follows:

- If `K = 1`, the value is passed to `OUT1`.

- If `K = 2`, the value is passed to `OUT2`.

- For other values of `K`, the behavior is undefined (no output).

The function block operates purely on a signal-based basis – no permanent connection is established, but only a one-time forwarding occurs per REQ event.

## Technical Features

- **Generic Adapter Type** – The function block uses the standardized unidirectional ALI adapter, which is available in many IEC 61499 libraries.

- **Indexing via UINT** – The index `K` is defined as an unsigned 16-bit value, theoretically allowing for expansion to more than two outputs (though limited to two here).

- **Event-driven processing** – Forwarding occurs only upon an explicit `REQ` event, not cyclically.

- **No data validation** – It is not checked whether `K` is within the allowed range; the application must ensure this.

## State overview

The ALI_DEMUX_2 does not have explicit states in the sense of a state machine. After receiving `REQ`, the operation is executed immediately and the `CNF` event is sent. The module is always ready for the next task.

## Application Scenarios

- **Signal Distribution** – An ALI signal acquired by a sensor unit can be sent to one of two downstream processing components.

- **Switching Between Operating Modes** – Depending on the operating mode (indices 1 or 2), the data stream is routed to different actuator or control modules.

- **Test or Simulation Environments** – A generated test signal can be dynamically switched between different test paths.

## Comparison with Similar Modules

Unlike a conventional data demultiplexer (e.g., `DEMUX`), which transmits values via data ports, the ALI_DEMUX_2 operates using **adapters**. Adapters encapsulate complex interfaces, allowing multiple data points and events to be transmitted simultaneously via a single port. This simplifies interconnection in larger architectures, but requires that all components involved use the same adapter type (in this case, ALI).

A pure data demux would have separate data outputs; here, the outputs are implemented as adapters, making the structure more modular, but also more specific.

## Conclusion

The ALI_DEMUX_2 is a compact and useful component for signal routing in ALI-based systems. Thanks to event-driven selection and the use of adapters, it integrates seamlessly into modern IEC 61499 applications. Its simplicity and clear functionality make it a solid foundation for any switching logic.