# AUS_MUX_4
![AUS_MUX_4](./AUS_MUX_4.svg)

* * * * * * * * * *
## Introduction
The AUS_MUX_4 is a generic function block (FB) according to IEC 61499, which serves as a multiplexer for four AUS adapter signals. An integer index K switches one of the four inputs (IN1..IN4) to the output (OUT). The block is suitable for modular control applications where signal selection is event-driven.
## Interface Structure

### **Event Inputs**

| Event | Description | With |

|----------|--------------|-----|

| **REQ** | Triggers the switching; evaluates the index K. | K |

### **Event Outputs**

| Event | Description |
|----------|--------------|

| **CNF** | Confirms successful switching. |

### **Data Inputs**

| Variable | Type | Description |

|----------|-----|--------------|

| **K** | UINT | Index for selecting the input (value range 0..3). |

### **Data Outputs**

The module does not have separate data outputs; the output data is provided via the adapter plug **OUT**.

### **Adapter**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| Socket (Input) | **IN1** | adapter::types::unidirectional::OFF | First input, active when K = 0 |

Socket (Input) | **IN2** | adapter::types::unidirectional::OFF | Second input, active when K = 1 |

Socket (Input) | **IN3** | adapter::types::unidirectional::OFF | Third input, active when K = 2 |

Socket (Input) | **IN4** | adapter::types::unidirectional::OFF | Fourth input, active when K = 3 |

Plug (Output) | **OUT** | adapter::types::unidirectional::OFF | Output reflecting the currently selected input |

## Functionality

As soon as an event arrives at the **REQ** input, the function block reads the current value of **K**. Depending on **K** (0, 1, 2, or 3), the corresponding adapter input (IN1..IN4) is switched to the adapter output **OUT**. After the switchover is complete, the **CNF** event is sent. The function block operates in an event-driven manner without internal delay; the switching occurs directly upon the REQ event.

## Technical Features
- **Generic Function Block:** The function block has the attribute `GenericClassName` with the value `'GEN_AUS_MUX'`, which allows for subsequent type parameterization or specialization.
- **Adapter-Based:** All inputs and outputs use the specific adapter type `AUS` (unidirectional). This promotes reusability and a clear interface definition.
- **Standard-Compliant:** Implemented according to IEC 61499-2.
- **Version 1.0,** released on May 28, 2026.

## State Overview

This function block is implemented as a simple event-driven function block (FB) without an explicit state machine (implicit Basic FB). Its behavior can be abstracted as follows:

- **IDLE:** Waits for a REQ event.
- **PROCESSING:** Upon receiving the REQ, the index is evaluated, the connection is established, and the CNF event is immediately sent. The FB then returns to the IDLE state.

There are no further states or delays.

## Application Scenarios
- **Sensor Selection:** Selects one of four analog or digital sensors in a machine controller.
- **Mode Switching:** Switches between different operating modes (e.g., automatic, manual, maintenance) in agricultural technology.
- **Adapter-Based Multiplexing:** Use in modular control systems where AUS adapters are used as a uniform signal format.

## Comparison with Similar Components
- Compared to a general **MUX component** (e.g., for simple Boolean or numeric types), the AUS_MUX_4 works exclusively with the **AUS** adapter type. This limits the signal types but offers a type-safe and modular interface.
- An **AUS_DEMUX** would distribute one input to multiple outputs; the AUS_MUX_4 performs the reverse selection.
- Other multiplexers with more channels (e.g., AUS_MUX_8) would be suitable for larger selections, while this one is specialized for four channels.

## Conclusion

The AUS_MUX_4 is a specialized yet flexible multiplexer for selecting one of four AUS signals. Thanks to its adapter interface and generic approach, it integrates well into modular automation solutions. It is particularly suitable for applications that require event-driven signal selection with clearly defined interfaces.
