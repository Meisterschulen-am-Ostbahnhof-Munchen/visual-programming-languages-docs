# Q_Priority_AUS
![Q_Priority_AUS](./Q_Priority_AUS.svg)
* * * * * * * * * *
## Introduction
The Q_Priority_AUS function block is used to change the priority of an alarm mask according to ISO 11783-6 (Part 6, F.40). An initialization process identifies the alarm mask, after which a new priority can be set. Confirmation of the service and the old priority value are output.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |

|----------|-----|-------------|

| INIT | EInit | Service initialization; executed with the data input `u16ObjId`. |

### **Event Outputs**

| Event | Type | Description |

|----------|-----|-------------|

| INITO | EInit | Confirmation of successful initialization. |

| CNF | Event | Confirmation of the requested service; output with `STATUS` and `s16result`. |

### **Data Inputs**

| Name | Type | Description | Initial Value |

|------|-----|--------------|-------------|

| u16ObjId | UINT | Object ID of the alarm mask | ID_NULL |

### **Data Outputs**

| Name | Type | Description |

|------|-----|-------------|

| STATUS | STRING | Service status (e.g., error or success message) |

| s16result | INT | Return value as described (see Functionality) |

### **Adapter**

| Name | Type | Direction | Description |

|------|-----|----------|-------------|

| u8Priority | OFF (unidirectional) | Socket | New priority (sent via the adapter) |

| u8OldPriority | OFF (unidirectional) | Plug | Old priority (received via the adapter) |

## Functionality
After triggering `INIT` with the valid object ID of the alarm mask, the function block initializes the internal communication. As soon as an event arrives via the `u8Priority` adapter, the service for changing the priority is executed. The module sends the new priority to the virtual terminal and, upon completion, outputs confirmation via `CNF`, including the status and result value. Simultaneously, the previous priority (if available) is returned via the adapter `u8OldPriority`.

The module sends the new priority to the virtual terminal and, upon completion, outputs confirmation via `CNF`. **Return Values (s16result):**

- **VT_E_NO_ERR (0)** – Success
- **VT_E_OVERFLOW (-6)** – Buffer Overflow
- **VT_E_NOACT (-8)** – Command Not Possible in Current State
- **VT_E_NO_INSTANCE (-21)** – No VT Client Available
- **VT_E_ISO_INSTANCE_INVALID (-129)** – Connection Instance Invalid
- **VT_E_NOT_ALIVE (-130)** – Instance Valid, but VT Inactive

## Technical Features
- The function block is based on the ISO 11783-6 protocol and uses unidirectional adapters for data transmission.
- Initialization expects a valid object ID; an invalid value (ID_NULL) results in no service.
- The error codes are standardized and enable easy diagnostics at the VT level.

`` - The internal logic delegates the actual priority change to the embedded function block `Q_Priority`.

## State Overview
The function block does not have an explicitly displayed state machine. Sequence:

1. **INIT** → Initialization waits for a valid object ID.

2. After successful initialization → **INITO** is active.

3. The request (REQ) is initiated via the adapter `u8Priority`.

4. After processing → **CNF** with result.

## Application Scenarios
- Changing the priority of an alarm mask in a virtual terminal of agricultural machinery (e.g., an ISOBUS-compliant control unit).
- Integration into a controller that needs to dynamically set different alarm levels (e.g., from "low" to "high" in the event of a critical incident).

## Comparison with Similar Function Blocks
- **Q_Priority** (without OFF): Offers the same core functionality but requires separate data lines for priority and age value. This function block encapsulates input and output via adapters, thus facilitating modular use in hierarchical networks.
- **Q_AlarmMask_Select**: Selects an alarm mask but does not change the priority. Q_Priority_OFF adds this functionality.

## Conclusion
The Q_Priority_OFF function block implements a standardized, robust interface for changing the priority of alarm masks according to ISO 11783-6. Due to its adapter-based data transmission and the clear separation of initialization and service execution, it is particularly suitable for modular agricultural control systems.
