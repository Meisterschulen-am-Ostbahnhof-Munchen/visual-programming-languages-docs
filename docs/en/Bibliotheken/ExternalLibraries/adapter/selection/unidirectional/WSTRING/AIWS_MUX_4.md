# AIWS_MUX_4
![AIWS_MUX_4](./AIWS_MUX_4.svg)
* * * * * * * * * *
## Introduction
The function block **AIWS_MUX_4** is a multiplexer for four unidirectional AIWS adapters. It selects one of the four inputs (IN1 to IN4) based on an index value **K** and forwards its data to the output **OUT**. It is implemented as a generic function block (Generic FB) based on the IEC 61499 standard.
## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| **REQ** | Starts the switching process. The value of **K** is read, and the corresponding input is switched to the output. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| **CNF** | Acknowledgement: The switchover was completed. |

### **Data Inputs**

| Variable | Type | Description |

|----------|-------|--------------|

| **K** | UINT | Index of the input to be selected (value range 0 … 3). |

### **Data Outputs**
None.

### **Adapters**

| Name | Type | Direction | Description |

|------|-----------------------------------------------|-----------|--------------|

| IN1 | adapter::types::unidirectional::AIWS | Socket | First input (K = 0). |

IN2 | adapter::types::unidirectional::AIWS | Socket | Second input (K = 1). |

IN3 | adapter::types::unidirectional::AIWS | Socket | Third input (K = 2). |

IN4 | adapter::types::unidirectional::AIWS | Socket | Fourth input (K = 3). |

OUT | adapter::types::unidirectional::AIWS | Plug | Output (receives the data from the selected input). |

## Functionality

1. A **REQ** event is received.

2. The current value of **K** is evaluated.

3. Depending on the value (0, 1, 2, or 3), the respective socket (IN1 … IN4) is activated, and its data is forwarded to the **OUT** plug.

4. After successful activation, the **CNF** event is output.

The selection is made without additional intermediate storage; the data is copied **transparently** from the selected input to the output.

## Technical Features
- The function block is marked as **Generic FB** (attribute `GenericClassName` = `'GEN_AIWS_MUX'`), which allows for later type specialization or reuse.
- The connection to the inputs and output is exclusively via **unidirectional adapters** (type `AIWS`), which enables a clean separation of data and control flow.
- No data interfaces beyond index **K** are required – all information transfer takes place via the adapter interfaces.

## State Overview

The function block has **no explicit states**, as it is implemented as a pure function block without a state machine (ECC). The response to **REQ** is strictly deterministic: after event processing, **CNF** is sent immediately.

## Application Scenarios
- **Selection of a sensor signal** from multiple AIWS-compatible sources (e.g., temperature, pressure, or level sensors).
- **Switching between redundant measured values** in safety-critical control systems.
- **Multiplexing of measurement data** into a central data stream for further processing or visualization.

## Comparison with Similar Function Blocks

The **AIWS_MUX_4** is specifically designed for the unidirectional AIWS adapter type. A general multiplexer for other adapter types (e.g., for byte or Boolean data) differs in its interface definition, while the underlying logic (index-based selection) is identical. Due to its generic design, the function block can be easily adapted to other adapter types.

## Conclusion

The **AIWS_MUX_4** is a compact, generic multiplexer for four unidirectional AIWS adapters. It offers simple, event-driven switching with a clear interface concept and is particularly suitable for applications where multiple AIWS sources need to be selectively connected to a common output.