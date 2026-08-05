# ALR_MUX_4
![ALR_MUX_4](./ALR_MUX_4.svg)

* * * * * * * * * *
## Introduction
The function block `ALR_MUX_4` implements a 4-channel multiplexer for data of type `ALR`. It selects one of four adapter inputs (`IN1` … `IN4`) and forwards its signal to the adapter output `OUT`. The selection is made using the integer index `K` (0-based). The block is implemented as a generic FB (`GEN_ALR_MUX`) and connected to the environment via adapter interfaces.

## Interface Structure

### **Event Inputs**

| Name | Type | Description |

|------|-----|--------------|

| `REQ` | Event | Sets the index `K` and triggers the forwarding of the corresponding input. |

### **Event Outputs**

| Name | Type | Description |

|------|-----|--------------|

| `CNF` | Event | Confirmation that the selection according to `K` has been made. |

### **Data Inputs**

| Name | Data Type | Description |

|------|----------|--------------|

| `K` | UINT | Index of the input to be multiplexed (0 … 3). |

### **Data Outputs**

This function block does not have its own data outputs – the output data is provided via the adapter plug `OUT`.

### **Adapter**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| Plug (Output) | `OUT` | `adapter::types::unidirectional::ALR` | Adapter that provides the data for the selected input. |

| Socket (Input) | `IN1` | `adapter::types::unidirectional::ALR` | First Data Adapter (Index 0). |

Socket (Input) | `IN2` | `adapter::types::unidirectional::ALR` | Second Data Adapter (Index 1). |

Socket (Input) | `IN3` | `adapter::types::unidirectional::ALR` | Third Data Adapter (Index 2). |

Socket (Input) | `IN4` | `adapter::types::unidirectional::ALR` | Fourth Data Adapter (Index 3). |

Socket (Input) | `IN4` | `adapter::types::unidirectional::ALR` | Fourth Data Adapter (Index 3). |

## Functionality

As soon as a signal is present at the event input `REQ`, the module reads the current value of `K`. This integer value (0 … 3) determines which of the four adapter inputs (`IN1` for K=0, `IN2` for K=1, `IN3` for K=2, `IN4` for K=3) is connected to the output `OUT`. Immediately after the connection is established, the event output `CNF` is set to signal the successful completion of the operation.

Data transmission occurs entirely via the adapter interfaces. The function block itself does not have direct data fields for the values to be multiplexed.

## Technical Features
- **Adapter-Based Input/Output:** The function block works exclusively with adapters of type `ALR`. This enables loose coupling between the communication partners and easy reuse of the multiplexer function.
- **Generic Implementation:** By assigning the generic class `GEN_ALR_MUX`, the function block can be adapted for different adapter types or channel numbers, provided the interfaces are compatible.
- **No State Machine:** The logic is purely combinatorial (event-triggered) and does not require an internal state.

## State Overview

The function block does not have an explicit state machine (ECC). Processing is event-driven: A pulse at `REQ` directly leads to the selection and output of `CNF`.

## Application Scenarios
- **Switching of sensor data** in an agricultural control system, where different ALR data sources (e.g., fill level, temperature) are forwarded to a central evaluation unit depending on the operating mode.
- **Test and simulation environments** where different ALR signals need to be selectively switched to a common bus.
- **Redundant systems** where, in the event of a source failure, the system automatically switches to a backup (by changing the index `K`).

## Comparison with similar components
- Simple **2-channel multiplexers** have only two inputs and require, for example, a Boolean selector.
- Unlike **switchable interconnects** (e.g., `MUX` with `ANY` types), `ALR_MUX_4` operates exclusively with a fixed adapter protocol and is therefore optimized for standardized ALR data.
- Compared to a **16-channel multiplexer**, this component offers a smaller selection limited to four channels, reducing complexity and improving maintainability.

## Conclusion

The `ALR_MUX_4` is a compact, event-driven multiplexer for four ALR adapter inputs. Its adapter-based interface and configurable index selection make it a flexible tool for signal channel switching in industrial control systems. The simple handling (one event, one index) allows for quick integration into existing automation solutions.
