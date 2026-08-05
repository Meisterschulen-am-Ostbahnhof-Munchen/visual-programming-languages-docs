# AD_MUX_4

![AD_MUX_4](./AD_MUX_4.svg)

* * * * * * * * * *

## Introduction

The **AD_MUX_4** is a generic, event-driven adapter multiplexer for unidirectional analog/data signals. Using the index *K*, a channel is selected from four input adapters (IN1 … IN4) and routed to the output adapter (OUT). This component is suitable for flexible signal routing tasks in automation and control systems.

## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| **REQ** | Request to evaluate the index *K* and establish the corresponding connection. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| **CNF** | Confirmation of successful switching operation. |

### **Data Inputs**

| Variable Name | Type | Description |

|---------------|------|--------------|

| **K** | UINT | Index for selecting the input channel (value range 0–3). |

### **Data Outputs**

The function block does not have direct data outputs; output is provided via the **OUT** adapter.

### **Adapter**

| Type | Name | Direction | Description |

|-----|------|-----------|--------------|

| `adapter::types::unidirectional::AD` | **OUT** | Plug | Output adapter that provides the value of the selected input. |

| `adapter::types::unidirectional::AD` | **IN1** | Socket | First input channel (index *K* = 0). |

| `adapter::types::unidirectional::AD` | **IN2** | Socket | Second input channel (index *K* = 1). |

| `adapter::types::unidirectional::AD` | **IN3** | Socket | Third input channel (index *K* = 2). |

| `adapter::types::unidirectional::AD` | **IN4** | Socket | Fourth input channel (index *K* = 3). |

## Functionality

1. In its idle state, the function block waits for an event at the **REQ** input.

2. Upon receiving the **REQ** event, the current value of the **K** data input is read.


``` 3. Depending on the value of *K* (0, 1, 2, or 3), the corresponding socket adapter (**IN1** to **IN4**) is connected to the plug adapter **OUT**.

4. Once the connection is established, an acknowledgment event is output at **CNF**.

5. The selected input value is then available at the **OUT** adapter.

Note: In case of an error (e.g., *K* > 3), the connection is not established; the behavior depends on the specific implementation – typically, the last valid value or a 0 is retained.

## Technical Features

- **Adapter-based interface**: The module utilizes the adapter concept of the 4diac IDE for unidirectional connections. This allows complex signal types to be exchanged between modules in a type-safe and flexible manner.

- **Generic Type**: The XML attributes declare the function block (FB) as a generic block (`GEN_AD_MUX`), enabling reuse with different adapter types or data structures.

- **No Internal State Machine**: The FB is purely event-driven and does not have an explicit ECC (Event Control Chart). Selection occurs immediately upon **REQ**; there are no waiting states.

- **Simple Index Scheme**: The index *K* is interpreted as a 16-bit integer (UINT), so values greater than 3 are technically possible, but only the first four channels are addressed.

## State Overview

Since the function block operates without an ECC, it can be considered a single state:

| State | Description |

|---------|--------------|

| **Idle** | Waiting for **REQ**. No active connection exists, or the connection from the last valid switching operation remains active. |

Upon arrival of **REQ**, the connection is updated, and the transition back to the idle state occurs immediately after output of **CNF**.

## Application Scenarios

- **Sensor Selection**: In a machine control system, four analog sensors (e.g., pressure sensors) are read via an analog-to-digital converter (ADC). Depending on the operating mode, the AD_MUX_4 can switch the appropriate sensor to the subsequent processing module.

- **Path Switching**: In a communication line with multiple data sources, the module can be used as a simple 4:1 adapter multiplexer.

- **Test and Diagnostic Functions**: For troubleshooting, various signal sources can be successively routed to a common analysis path.

## Comparison with Similar Modules

| Module | Channels | Interface | Special Features |

|----------|--------|---------------|----------------|

| **AD_MUX_4** (this FB) | 4 | Adapter (unidirectional) | Generic, no ECC, simple index event handling |

| **AD_MUX_2** | 2 | Adapter | Corresponding for two channels, identical functionality |

| **MUX** (Standard) | Variable | Data inputs (ANY) | Suitable for values of type ANY, not limited to adapters; usually works with Boolean selection |

| **SELECT** | 2 | Data and event interface | Often with two data inputs and a switching signal, more suitable for single values |

The AD_MUX_4 is characterized by its adapter-based, unidirectional signal routing, which allows for clean encapsulation in modular IEC 61499 applications.

## Conclusion

The **AD_MUX_4** is a compact and flexible adapter multiplexer that routes four input channels to a single output path via a numerical index. Its event-driven operation and adapter interfaces make it ideal for modular automation systems requiring dynamic signal selection. Its simple structure allows for easy integration into higher-level control logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]