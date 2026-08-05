# AIWS_D_FF
![AIWS_D_FF](./AIWS_D_FF.svg)
* * * * * * * * * *
## Introduction
The AIWS_D_FF function block implements a data latch (D) flip-flop that stores an incoming data value and passes it to the output upon an event. Communication occurs exclusively via adapters, allowing the block to be seamlessly integrated into modular systems.
## Interface Structure

### **Event Inputs**

| Name | Data Type | Description |

|------|----------|--------------|

| I.E1 | Event (via adapter) | Event that triggers the transfer of the data value |

### **Event Outputs**

| Name | Data Type | Description |

|------|----------|--------------|

| Q.E1 | Event (via adapter) | Event that displays the stored data value |

### **Data Inputs**

| Name | Data Type | Description |

|------|----------|--------------|

| I.D1 | ANY (via adapter) | Data value that is received upon arrival of I.E1 |

### **Data Outputs**

| Name | Data Type | Description |

|------|----------|--------------|

| Q.D1 | ANY (via adapter) | Stored data value that is output with Q.E1 |

### **Adapter**

| Name | Type | Direction | Description |

|------|-----|----------|--------------|

| **I** | `adapter::types::unidirectional::AIWS` | Socket (Input) | Provides the value to be latched and the triggering event |

| **Q** | `adapter::types::unidirectional::AIWS` | Plug (Output) | Outputs the stored value with an event |

## Functionality

The AIWS_D_FF encapsulates an internal `E_D_FF_ANY` module. The incoming adapter `I` provides an event via `I.E1`, which takes the value present at data port `I.D1`. The stored value is then output via `Q.D1`, accompanied by an event on `Q.E1`. Thus, the function block behaves like a classic clocked D flip-flop, but with a fully adapter-based interface.

## Technical Features
- **Adapter-Based Interface:** All inputs and outputs are implemented via unidirectional adapters, enabling easy encapsulation and reuse in different contexts.
- **Internal Standard Function Block:** The implementation uses the IEC 61499 standard function block `E_D_FF_ANY`, which provides generic and proven latch functionality.
- **Unidirectional Data Flow:** The adapter type `AIWS` allows data flow in only one direction, improving clarity and preventing errors in networking.

## State Overview

The AIWS_D_FF has no explicit internal states at the top level. The integrated `E_D_FF_ANY` goes through two phases:

1. **Waiting:** It waits for an event at the clock input.

2. **Accept & Output:** Upon a clock event, the data value is accepted and an output event is generated.

This sequence repeats with each incoming event.

## Application Scenarios
- **Data Synchronization:** Buffering a sensor signal that is only to be passed on upon a specific trigger event.
- **Control Logic:** Storing a control signal as a function of a clock signal, e.g., for time-synchronized actuator control.
- **Modular Systems:** Integration into adapter-based architectures where functional blocks are connected via standardized interfaces.

## Comparison with Similar Components
- **Simple D flip-flop (e.g., `E_D_FF`):** Has separate event and data ports, while the AIWS_D_FF encapsulates the same logic via adapters.
- **SR flip-flop:** Stores two states (Set/Reset), whereas the AIWS_D_FF only stores a single data value and does not offer a reset function.
- **Register components:** Can store multiple bits in parallel, while the AIWS_D_FF is designed for a single data value (ANY).

## Conclusion

The AIWS_D_FF is a compact and modular functional block for implementing a D flip-flop in IEC 61499 systems. The exclusive use of adapters ensures high flexibility and reusability. It is particularly suitable for applications that require decoupled, event-driven data transfer.