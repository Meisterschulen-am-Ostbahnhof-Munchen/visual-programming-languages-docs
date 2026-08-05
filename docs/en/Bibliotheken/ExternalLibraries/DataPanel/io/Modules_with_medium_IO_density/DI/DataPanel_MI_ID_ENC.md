# DataPanel_MI_ID_ENC
![DataPanel_MI_ID_ENC](./DataPanel_MI_ID_ENC.svg)
* * * * * * * * * *
## Introduction
The **DataPanel_MI_ID_ENC** function block is an input service interface function block for acquiring encoder pulse data. It is designed to process a 7A+8A encoder pair and outputs the current counter reading and status information. Initialization is performed via parameters such as the node address (SA member), the input configuration, and thresholds for pulse- and time-based event triggering.
## Interface Structure
### **Event Inputs**

| Event | Description | Accompanying Data |

|----------|---------------|-------------------|

| INIT | Service Initialization | QI, PARAMS, u8SAMember, Input, ImpulseDelta, TimeDelta |

| REQ | Service Request | QI |

### **Event Outputs**

| Event | Description | Accompanying Data |

|----------|--------------|-------------------|

| INITO | Initialization Acknowledgement | QO, STATUS |

| CNF | Requested Action Acknowledgement | QO, STATUS, IN |

| IND | Asynchronous Event Display (Pulse or Timeout) | QO, STATUS, IN |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|------|-----|--------------|--------------|

| QI | BOOL | – | Event Input Qualifier |

PARAMS | STRING | – | Service Parameter |

u8SAMember | USINT | MI::MI_00 | Node Address (range 224..239) |

Input | DataPanel::io::MI::DI::DataPanel_MI_DI_S | Invalid | Input Identifier (usually 7A for a 7A+8A pair) |

PulseDelta | DWORD | – | Number of pulses after which an IND is triggered |

TimeDelta | DWORD | – | Time in milliseconds after which an IND is triggered |

### **Data Outputs**

| Name | Type | Description |

|------|-----|---------------|

QO | BOOL | Event Output Qualifier |

| STATUS | STRING | Service Status |

| IN | DWORD | Current Encoder Counter Value |

### **Adapter**
None.

## Functionality

1. **Initialization (INIT → INITO)**

The function block is configured with the parameters `PARAMS`, the node address `u8SAMember`, the input specification `Input`, and the threshold values `ImpulseDelta` and `TimeDelta`. After successful initialization, the event `INITO` is acknowledged with `QO` and `STATUS`.

2. **Request (REQ → CNF)**

The function block `REQ` triggers a targeted query of the current counter reading. The block responds with `CNF` and provides the current encoder value via `IN`, along with status information.

3. **Asynchronous Events (IND)**

Regardless of an explicit request, `IND` is triggered as soon as either the number of encoder pulses specified in `ImpulseDelta` has been exceeded or the time interval defined in `TimeDelta` has expired. This enables event-driven processing without continuous polling.

The output `IN` contains the current 32-bit counter value of the encoder for each event (CNF and IND).

## Technical Features
- **User-Defined Types**: The input `Input` is based on the data type `DataPanel_MI_DI_S`, which expects a specific input configuration (e.g., 7A). The constant value `Invalid` serves as a placeholder for undefined inputs.
- **Configurable Event Triggering**: By combining `ImpulseDelta` and `TimeDelta`, the system can trigger an IND either after a specific number of pulses, after a time interval, or after the first event occurring (AND operation).
- **Node Addressing**: The physical node in the bus system is selected via `u8SAMember` (value range 224–239). The initial value `MI::MI_00` refers to a constant in the module `MI`.

## State Overview

| State | Description |

|---------|--------------|

| IDLE | Waiting for INIT or REQ |

| INIT | Initialization in progress, parameters are being applied |

| ACTIVE | Initialization complete, ready for REQ and IND |

| ERROR | Error state (e.g., failed initialization) |

The actual state machine is not explicitly represented in the code shown; the states depicted are derived from the typical behavior of service interface function blocks.

## Application Scenarios
- **Agricultural Machinery Control**: Acquisition of rotational speeds on drive shafts via incremental encoders (7A+8A pair) for monitoring and controlling work processes.
- **Position Acquisition**: Use as a pulse counter for position measurement, e.g., for drive systems or actuators.
- **Event-Driven Data Acquisition**: Configurable IND thresholds prevent peak loads in data traffic and optimize logging tasks.

## Comparison with Similar Components
Compared to simple encoder counters, the DataPanel_MI_ID_ENC offers:

- **Flexible Trigger Criteria**: Instead of relying solely on polling, pulse or time thresholds can be set.
- **Structured Initialization**: The use of a user-defined type (`DataPanel_MI_DI_S`) enables clear mapping to specific hardware inputs.
- **Event-based output**: The separation of `CNF` (synchronous with the request) and `IND` (asynchronous) allows for decoupled processing at higher control levels.

## Conclusion
The **DataPanel_MI_ID_ENC** function block is a powerful service interface module for encoder data acquisition in industrial control systems. Its configurable thresholds and support for both synchronous and asynchronous events make it particularly suitable for real-time applications in agricultural engineering. The clear interface definition and the use of specific data types enable easy integration into existing automation environments.