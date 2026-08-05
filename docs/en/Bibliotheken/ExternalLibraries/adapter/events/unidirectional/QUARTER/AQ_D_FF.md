# AQ_D_FF

![AQ_D_FF](./AQ_D_FF.svg)

* * * * * * * * * *
## Introduction
The function block `AQ_D_FF` implements a data storage element (D-latch) based on the adapter concept of IEC 61499. It receives an incoming data value upon an event and makes it available at the output until the next event. The block fully encapsulates the latch functionality in an adapter interface, thus enabling modular integration into system-wide data and event paths.

## Interface Structure
### **Event Inputs**
No direct event inputs are available. Event control is handled exclusively via the adapter `I`.

## **Event Outputs**
No direct event outputs are available. Event output is handled exclusively via the adapter `Q`.


### **Data Inputs**
No direct data inputs are available. The data value to be latched is provided via the adapter `I`.

### **Data Outputs**
No direct data outputs are available. The latched data value is output via the adapter `Q`.

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| `I` | Socket (Input) | `adapter::types::unidirectional::AQ` | Provides the data value to be latched and the triggering event. |

| `Q` | Plug (Output) | `adapter::types::unidirectional::AQ` | Outputs the latched data value and an acknowledgment event. |

The adapter type used, `adapter::types::unidirectional::AQ`, provides a unidirectional connection: One event channel and one data channel are transmitted from the socket to the plug.

## Functionality
The `AQ_D_FF` operates on the principle of an edge-triggered D-latch. Internally, the function block `iec61499::events::E_D_FF_ANY` is used:

- As soon as an event arrives at the `I` adapter, the currently available data value, `D1` (from the `I` adapter), is retrieved.

- The received value is output as `D1` at adapter `Q`, and simultaneously, event `E1` is triggered at the output adapter.

- The output value remains constant between two events. With each new event at the input, the output is updated to the then-current input value.

## Technical Features

- **Pure Adapter Interface**: The module has no direct event or data inputs/outputs. All communication takes place via adapters `I` and `Q`.

- **Unidirectional Data Transmission**: The adapters are of type `adapter::types::unidirectional::AQ`, meaning that data and events flow only from input to output. Feedback or bidirectional communication is not supported.

- **Internal Implementation**: The latch function is implemented using the universal function block `E_D_FF_ANY` from the IEC 61499 event library, ensuring robust and standards-compliant processing.

- **No Initialization**: The initial state of the latched value is undefined until the first event arrives at the input.

## State Overview
The `AQ_D_FF` does not have an explicit state machine. However, its behavior can be described by two logical states:

| State | Description |

|---------|--------------|

| **Waiting for Event** | The output `Q` holds the last latched value. No event is pending at `I`. |

| **Accept/Output** | When an event arrives at `I`, the new value is transferred from `I`, output to `Q`, and an event is generated on `E1` by `Q`. The function block then returns to its wait state. |

## Application Scenarios

- **Cache Storage of Sensor Values**: A measured value is captured upon a trigger event (e.g., clock cycle or query) and is then available for further processing.

- **Synchronization of Asynchronous Data Streams**: If data arrives asynchronously, `AQ_D_FF` can hold the last valid value until a subsequent process retrieves it.

- **Event-driven data forwarding**: The function block can be used as a simple "data holder" in an adapter-based communication path to forward data only upon specific events.

## Comparison with similar function blocks

| Function block | Properties |

|----------|---------------|

| `E_D_FF` (direct I/Os) | Same latch functionality, but with separate event and data inputs/outputs. No adapters. |

| `E_SR_FF` | Set/reset flip-flop with two separate input events. Binary states, not data values. |

| `AQ_D_FF` | Enables embedding the latch function into existing adapter interfaces without additional wiring at the function block level. |

## Conclusion
The function block `AQ_D_FF` offers a compact, adapter-based implementation of a D-latch. It integrates seamlessly into system-wide adapter paths, thus reducing wiring effort at the function block level. Its operation is simple and reliable, especially for applications where a data value needs to be transferred upon an event and held until the next event.