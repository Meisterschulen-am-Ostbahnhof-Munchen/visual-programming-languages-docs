# AQ_MUX_2
![AQ_MUX_2](./AQ_MUX_2.svg)

* * * * * * * * * *
## Introduction
The **AQ_MUX_2** is a generic 2-channel multiplexer for analog outputs, implemented as an IEC 61499 function block. Based on an index `K`, it selects one of the two analog input adapters (`IN1`, `IN2`) and forwards its signal to the output adapter (`OUT`). This function block is suitable for applications requiring switching between two signal sources, such as controlling an actuator with different setpoints.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| **REQ** | This event triggers the switching of the multiplexer. The current value of `K` determines which input is passed through to the output. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| **CNF** | Confirms the successful execution of the selection requested by `REQ`. |

### **Data Inputs**

| Name | Type | Description |

|------|-------|--------------|

| **K** | UINT | Index for selecting the input. Valid values: `0` → IN1, `1` → IN2. Values outside this range are undefined. |

### **Data Outputs**

This function block does not have its own data outputs; the output data is provided via the adapter `OUT`.

### **Adapters**

| Role | Name | Type (Adapter) | Description |

|-------|------|----------------|--------------|

| Plug | **OUT** | `adapter::types::unidirectional::AQ` | Selected analog output value. |

| Socket | **IN1** | `adapter::types::unidirectional::AQ` | First input (index 0). |

| Socket | **IN2** | `adapter::types::unidirectional::AQ` | Second input (Index 1). |

All adapters are of the same type: a unidirectional analog output adapter.

## Operation
The **AQ_MUX_2** operates in an event-driven manner:

1. A **REQ** event signals a new request.

2. The current value of `K` is evaluated:

- At `K = 0`, the value of adapter **IN1** is passed to **OUT**.
- At `K = 1`, the value of adapter **IN2** is passed to **OUT**.

3. After a successful switchover, a **CNF** event is output.

The selection is made immediately upon arrival of the `REQ` event. There is no intermediate storage; the output data corresponds to the current state of the selected input adapter.

## Technical Features
- **Adapter-based interface**: Both inputs and outputs use uniform adapters of type `adapter::types::unidirectional::AQ`, enabling modular and reusable cabling in the application.
- **Generic structure**: The function block is declared as a generic FB (`GEN_AQ_MUX`) and can be instantiated specifically for each target platform.
- **License**: Available under the Eclipse Public License 2.0 (EPL-2.0).
- **Developed by**: HR Agrartechnik GmbH (Version 1.0, 2026-05-28).

## State Overview
The function block (FB) does not have an explicitly modeled state machine (ECC). Its internal behavior can be described as a simple, event-driven process:

IDLE → [REQ empfangen] → Auswahl durchführen → [CNF senden] → IDLE
After processing, the function block immediately returns to standby mode and awaits the next `REQ` event.

## Application Scenarios
- **Switching between two setpoints**: In a machine control system, a choice can be made between two predefined analog control variables (e.g., speed, position).
- **Redundancy switching**: If a sensor or signal transmitter fails, the system automatically or manually switches to a backup input.
- **Operating mode selection**: Depending on the operating mode (e.g., automatic/manual operation), a different analog value is forwarded to the actuator.

## Comparison with similar function blocks
Various multiplexer function blocks exist in the IEC 61499 standard (e.g., `SEL`, `MUX`). The **AQ_MUX_2** differs in the following ways:

- **Adapter Interface**: Instead of individual data inputs/outputs, it uses adapters, which allows for the encapsulation of more complex data types.
- **Specialization for Analog Outputs**: The adapter type `AQ` is optimized for analog output signals (e.g., 0-10V, 4-20mA).
- **Simplicity**: Only two channels (compared to `MUX` with multiple inputs), which improves clarity.

## Conclusion
The **AQ_MUX_2** is a practical, generic multiplexer module for analog output values. Its adapter-based interface facilitates integration into existing 4diac applications and makes it particularly suitable for modular control solutions. Thanks to its transparent switching logic and clear event handling, it is reliable and easy to understand.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
