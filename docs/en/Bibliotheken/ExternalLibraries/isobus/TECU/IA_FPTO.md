# IA_FPTO

![IA_FPTO](./IA_FPTO.svg)

*[Image of the function block, if available]*

* * * * * * * * * *

## Introduction

The **IA_FPTO** function block serves as an ISOBUS adapter for the front power take-off (FPTO) according to ISO 11783-7 (PGN 65092). It encapsulates the internal logic of the **I_FPTO** block and provides the relevant signals via standardized adapter interfaces. This enables seamless integration into ISOBUS-based control systems.

## Interface Structure

### **Event Inputs**

| Event | Type | Description | With Variables |

|----------|-----|---------------|---------------|

| INIT | EInit | Service Initialization | QI |

### **Event Outputs**

| Event | Type | Description | With Variables |

|----------|-----|---------------|---------------|

| INITO | EInit | Initialization Confirmation | QO, STATUS |

### **Data Inputs**

| Variable | Type | Description |

|----------|-----|--------------|

| QI | BOOL | Qualifier for the INIT input |

### **Data Outputs**

| Variable | Type | Description |

|----------|-----|--------------|

| QO | BOOL | Qualifier for the INITO output |

STATUS | STRING | Status message after initialization |

## **Adapter**

| Adapter | Type | Description |

|---------|-----|---------------|

SPEED | adapter::types::unidirectional::AUI | Front PTO output speed (actual value) |

SPEED_SET | adapter::types::unidirectional::AUI | Front PTO setpoint speed |

TIMEOUT | adapter::types::unidirectional::AX | Communication timeout status |

All adapters are unidirectional: Values are sent by the function block (FB), but not received.

## Functionality

The FB is activated via the **INIT** event. If the input qualifier **QI** is set, the internal logic initializes the connection to the ISOBUS communication layer. After successful initialization, the **INITO** event is triggered, and the output variables **QO** and **STATUS** return the initialization status.

After initialization, the function block operates autonomously: It cyclically provides the current speed of the front PTO via the **SPEED** adapter and the corresponding setpoint via **SPEED_SET**. The **TIMEOUT** adapter indicates whether a communication timing error has occurred (e.g., if the control unit is not sending current data). These outputs are continuously updated as long as the initialization remains valid.

## Technical Features

- The function block is based on the internal function block **I_FPTO** from the library `isobus::tecu`. The adapter interfaces decouple the application from the specific signal encoding of the ISOBUS.

- The adapters **SPEED** and **SPEED_SET** use the unidirectional type **AUI** (address unknown, integer), which is suitable for analog values such as rotational speeds.

- The adapter **TIMEOUT** uses the type **AX** (address unknown, Boolean value) to represent the timeout state in binary.

- The function block (FB) does not contain its own behavior for events outside of initialization; data updates are implicitly handled via the network connections of the block **I_FPTO**.

## State Overview

The FB does not have an explicit state machine. Its behavior can be described as follows:

1. **Initialization Phase**: After the **INIT** event, the internal FB **I_FPTO** is initialized. During this phase, the adapter outputs are invalid or set to a defined initial value (0/FALSE).


The FB does not have an explicit state machine. 2. **Active Phase**: After confirmation of the initialization (**INITO**), the current values are stably available at the **SPEED**, **SPEED_SET**, and **TIMEOUT** adapters.

3. **Error State**: If a timeout occurs, the **TIMEOUT** adapter is set to TRUE. The speed values may remain at the last valid value until communication is restored.

Reinitialization (another INIT pulse) can reset and restart the FB.

## Application Scenarios

- **Front PTO Control in Agricultural Tractors**: The FB receives the target and actual speeds of the front PTO via ISOBUS and forwards them to higher-level controllers or displays.

- **Integration into ISOBUS-Compliant Implements**: Implements such as front mowers or front loaders can use the speed and timeout information to adjust their functions accordingly.

- **Remote Diagnostics and Monitoring**: The timeout signal enables monitoring of the communication link to the PTO control unit, which is important for fault detection and safety functions.

## Comparison with Similar Modules

In the ISOBUS environment, there are other adapters for different PTOs (e.g., **IA_RPTO** for the rear PTO) or for general control units. **IA_FPTO** is specifically tailored to the front PTO and contains only the signals relevant to this application (actual/target speed and timeout). Compared to a generic ISOBUS adapter, it therefore offers a higher level of abstraction and easier handling for the application developer.

## Conclusion

The **IA_FPTO** function block provides a streamlined and specific interface for ISOBUS-compliant use of the front PTO. The encapsulation of the internal communication logic and its provision via unidirectional adapters significantly simplifies integration into control applications. The module is particularly suitable for tractors and agricultural machinery where reliable speed monitoring and timeout detection are required.