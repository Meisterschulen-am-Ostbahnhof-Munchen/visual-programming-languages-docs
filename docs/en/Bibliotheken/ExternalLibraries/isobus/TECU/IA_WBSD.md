# IA_WBSD
![IA_WBSD](./IA_WBSD.svg)
* * * * * * * * * *
## Introduction
The function block **IA_WBSD** (ISOBUS Adapter for Wheel Based Speed and Distance) serves as an interface wrapper for ISOBUS communication of wheel-based speed and distance values according to ISO 11783-7. It encapsulates the internal module `I_WBSD` and provides its functionality via standardized adapter connections.
## Interface Structure
### **Event Inputs**

| Event | Type | Comment |

|----------|-----|-----------|

| INIT | EInit | Service Initialization |

### **Event Outputs**

| Event | Type | Comment |

|----------|-----|-----------|

| INITO | EInit | Initialization Confirm |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| QI | BOOL | Event Input Qualifier (Initialization Confirmation) |

### **Data Outputs**

| Name | Type | Comment |

|--------|-------|-----------|

| QO | BOOL | Event Output Qualifier (Initialization Result) |

| STATUS | STRING | Status Message (e.g., Error or Success) |

### **Adapters**

| Adapter | Type | Comment |

|----------|-----|-----------|

SPEED | adapter::types::unidirectional::AUI | Wheel-based machine speed (unidirectional, analog value) |

DISTANCE | adapter::types::unidirectional::AUDI | Wheel-based machine distance (unidirectional) |

TIMEOUT | adapter::types::unidirectional::AX | Timeout status (unidirectional) |

## Functionality

The **IA_WBSD** function block is a pure adapter wrapper. It connects the external event and data interfaces as well as the three adapters directly to the internal function block `I_WBSD` (of type `isobus::tecu::I_WBSD`).

- The initialization of the ISOBUS service is triggered via the **INIT** input and the qualifier signal **QI**.
- After successful initialization, **INITO** is triggered and **QO** is set to `TRUE`. **STATUS** contains textual feedback.
- The **SPEED** and **DISTANCE** adapters provide the current measured values for wheel-based speed and distance, respectively.
- The **TIMEOUT** adapter signals whether a timeout has occurred in the ISOBUS communication.

The internal logic (calculation, timeout monitoring, ISOBUS frame handling) is handled entirely by the internal function block `I_WBSD`; **IA_WBSD** makes this available externally as an IEC 61499-compliant adapter interface.

## Technical Features
- **Standard:** ISO 11783-7 (ISOBUS) – PGN 65096
- **Development History:**
- Version 1.0: Initial implementation as an adapter wrapper for `I_WBSD`
- Version 1.1: Bug fixes – correct connection between internal pins and adapter plugs through additional conversion blocks
- **Compiler Package:** `isobus::tecu`
- **License:** Eclipse Public License 2.0
- **Author:** - (not named)

## State Overview
The block does not have its own explicit state machine. Its behavior is controlled by the internal function block `I_WBSD`:

- **Idle State:** No initialization pending.
- **Initialization Run:** After **INIT** with **QI = TRUE**, the internal process is started. If **QI = FALSE**, no action is taken.
- **Initialization Complete:** **INITO** is triggered, **QO** indicates success (`TRUE`) or failure (`FALSE`). Afterward, measured values and timeout status can be continuously received via the adapters.

## Application Scenarios
- **Agricultural Machine Control:** Integration of wheel-based speed and distance sensors into an ISOBUS control system (e.g., for tractors, harvesters).
- **Positioning without GPS:** Use of the wheel sensors for relative position determination in field work applications.
- **Monitoring of Driving Cycles:** Acquisition of speed and distance data for diagnostics or process control.

## Comparison with Similar Function Blocks
- **IA_WBSD vs. Direct I_WBSD:** The internal function block `I_WBSD` provides the pure ISOBUS implementation, while **IA_WBSD** encapsulates this in an IEC 61499 adapter interface. This facilitates reuse in various tools (e.g., 4diac IDE) and loose coupling with other function blocks.
- **IA_WBSD vs. Other ISOBUS Adapters:** Specific to the PGN 65096 (Wheel Based Speed and Distance). Adapters for other PGNs (e.g., for GPS position or motor speed) have a similar structure but differ in data types and internal interpretation.

**IA_WBSD vs. Other ISOBUS Adapters:**
## Conclusion

The **IA_WBSD** is a practical adapter wrapper for the ISOBUS module `I_WBSD`. It reduces the complexity of integrating wheel-based speed and distance data into IEC 61499 projects and provides the functionality via standardized unidirectional adapters. Thanks to its EPL 2.0 license, it can be freely used and adapted in your own projects. Version 1.1 ensures that all internal connections are correctly routed to the adapter plugs.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
