# AuxiliaryState
![AuxiliaryState](./AuxiliaryState.svg)
* * * * * * * * * *
## Introduction
AuxiliaryState is a collection of global constants for auxiliary inputs in ISOBUS systems. These constants define various states of auxiliary inputs, typically used for control functions in agricultural and mobile machinery.
## Interface Structure
AuxiliaryState consists of global constants and is not a function block in the traditional sense. Therefore, this component does not have any event or data interfaces.

### **Event Inputs**
- Not available (Global Constants)

### **Event Outputs**
- Not available (Global Constants)

### **Data Inputs**
- Not available (Global Constants)

### **Data Outputs**
- Not available (Global Constants)

### **Adapters**
- Not available

## Functionality
AuxiliaryState defines a set of predefined constants for the data type `AuxiliaryState_S`. Each constant represents a specific state of an auxiliary input with a corresponding numeric value and optional additional parameters.

## Technical Features
- All constants are of type `isobus::UT::io::Auxiliary::IN::AuxiliaryState_S`
- The value ranges from 0 to 255
- Some constants also contain the flag `bCyclic := FALSE`
- The structure follows ISOBUS standards for agricultural control systems

## State Overview
The defined constants include the following states:

| Constant | Value | Description |

|-----------|------|--------------|

| `AuxDisabled` | 0 | Off - reverse, down, left, or not pressed |

| `AuxDisabled_START` | 0 | Off - reverse, down, left, or not pressed (with bCyclic=FALSE) |

| `AuxEnabled` | 1 | On - forward, up, right, or pressed |

AuxEnabled_START` | 1 | On - forward, up, right, or pressed (with bCyclic=FALSE) |

AuxHeld` | 2 | Held (forward, up, or right) |

AuxHeld_START` | 2 | Held (forward, up, or right) (with bCyclic=FALSE) |

AuxEnabledBackwards` | 4 | Currently on - backward, down, or left |

AuxHeldBackwards` | 8 | Held (backward, down, or left) |

AuxHeldBackwards_START` | 8 | Held (backward, down, or left) (with bCyclic=FALSE) |
| `AuxDefault` | 9 | Default value |

| `Invalid` | 255 | Invalid value |

## Application Scenarios
- Control of hydraulic functions in tractors
- Operation of implements via ISOBUS interfaces
- Status monitoring of auxiliary functions in mobile machinery
- Implementation of standardized input states in agricultural control systems

## ⚖️ Comparison with similar blocks

Unlike function blocks with active logic, AuxiliaryState consists of passive constant definitions that can be used as reference values in other function blocks. They offer a standardized way to define auxiliary states in ISOBUS environments.

## Conclusion
AuxiliaryState provides a comprehensive collection of standardized constants for handling auxiliary inputs in ISOBUS systems. The clear definition of the different states enables a consistent implementation of control logic across different systems and facilitates the maintainability and readability of the code.
