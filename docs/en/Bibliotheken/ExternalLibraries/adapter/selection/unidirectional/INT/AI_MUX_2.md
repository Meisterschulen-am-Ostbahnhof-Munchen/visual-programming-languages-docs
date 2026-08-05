# AI_MUX_2
![AI_MUX_2](./AI_MUX_2.svg)

* * * * * * * * * *
## Introduction
The function block **AI_MUX_2** is a generic analog input multiplexer. It selects one of two analog signal inputs (IN1 and IN2) based on an index **K** and makes the selected signal available at its output **OUT**. The block is event-controlled and operates according to the 61499-2 standard.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Data |

|------|-------|-----------------------------------|-----------|

| REQ | Event | Request to select index K | K |

### **Event Outputs**

| Name | Type | Comment |

|------|-------|---------------------------------------------|

| CNF | Event | Confirmation of executed index selection |

### **Data Inputs**

| Name | Type | Comment |

|------|------|-------------------|

| K | UINT | Index (0 or 1) |

### **Data Outputs**

No data outputs available.

### **Adapters**

| Type | Direction | Name | Comment | Adapter Type |

|-------|----------|------|----------------------------------------------------|-----------------------------------------------------|

| Plug | Output | OUT | Output signal, dependent on K: IN1 when K=0, IN2 when K=1 | adapter::types::unidirectional::AI |

| Socket| Input | IN1 | First analog input (K=0) | adapter::types::unidirectional::AI |

Socket | Input | IN2 | Second analog input (K=1) | adapter::types::unidirectional::AI |

The adapters used are unidirectional (transmitter/receiver) and specific for analog input signals (type `adapter::types::unidirectional::AI`).

## Functionality

1. The module waits for a **REQ** event.

2. When the event occurs, the value of the data input **K** is read.

3. If **K = 0**, the adapter socket **IN1** is connected to the adapter plug **OUT**.

If **K = 1**, **IN2** is connected to **OUT**.

For other values of **K**, the behavior is not specified (typically only the values 0 and 1 are supported).

4. After successful switching, the **CNF** event is output.

The switching logic is synchronous with the REQ event. There is no delay or buffering.

## Technical Features
- **Generic Function Block**: The function block is declared as a generic type (`GEN_AI_MUX`) and can be adapted to different environments using type parameters.
- **Adapter-Based Interface**: The analog signals are not transmitted via direct input/output variables, but via adapters. This allows for flexible coupling with other function blocks that use the same adapter type.
- **No State Machine**: The function block has no ECC (Execution Control Chart) and no internal states. Processing is purely event-driven and occurs in a single step.
- **Unidirectional Adapters**: The adapters are defined as unidirectional, meaning the data flow is fixed from the sockets (IN1, IN2) to the plug (OUT).

## State Overview

The function block (FB) has **no explicit states**. Its operation is combinatorial with event-driven triggering:

- **Start State**: Waiting for REQ.
- **After REQ**: Immediate selection according to K and output of CNF.

There are no internal variables that store a state.

## Application Scenarios
- **Sensor Switching**: Selection between two analog sensors (e.g., temperature, pressure) in a controller, depending on the operating mode.
- **Test/Measurement System**: Switching between a measurement signal and a reference signal for calibration.
- **Redundancy**: Switching to a second analog signal if the first one fails (controlled via an external index).

## Comparison with Similar Function Blocks

| Function Block | Features |
|----------|----------|

**AI_MUX_2** | Multiplexer for two analog inputs, adapter-based, generic. |

**DEMUX_AI** | Distributes one analog signal to multiple outputs (demultiplexer). |

**SEL** (Standard IEC 61499) | Selection between multiple data inputs via an index, usually for basic data types and without an adapter. |

The **AI_MUX_2** is specifically designed for analog (AI) signals via adapters and is therefore easier to integrate into complex automation systems that rely on adapter communication than a standardized SEL module.

## Conclusion

The **AI_MUX_2** is a simple yet effective function block for event-driven switching between two analog signals. It utilizes the adapter concept of the 61499-2 standard to ensure a clean separation of data and event flows. Its generic design allows for easy adaptation to customer-specific requirements. The FB is particularly suitable for modular control architectures where analog signal path switching is required.
