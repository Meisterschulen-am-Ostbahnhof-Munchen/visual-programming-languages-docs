# IA_RHS

![IA_RHS](./IA_RHS.svg)

* * * * * * * * * *

## Introduction

The function block **IA_RHS** (ISOBUS Adapter for Rear Hitch Status) serves as an interface between the ISOBUS system (according to ISO 11783-7, PGN 65093) and an application network. It encapsulates the communication with the internal module I_RHS and provides the measured rear hitch data (position, force, tractive force) as well as the timeout status via standardized, unidirectional adapters. This module is primarily used in tractor and agricultural machinery control systems.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Data |
|------|-------|-------------------------|-----------|
| INIT | EInit | Service Initialization | QI |

### **Event Outputs**

| Name | Type | Comment | With Data |
|-------|-------|--------------------------|----------------|
| INITO | EInit | Initialization Confirm | QO, STATUS |

### **Data Inputs**

| Name | Type | Comment |
|------|------|-------------------------|
| QI | BOOL | Event Input Qualifier |

### **Data Outputs**

| Name | Type | Comment |
| -------- | -------- | -------------------------- |
| QO | BOOL | Event Output Qualifier |
| STATUS | STRING | Status Message |

### **Adapters**

| Name | Type | Comment |
| --------- | ---------- | ------------------------------------------- |
| POSITION | OFF | Rear Hitch Position |
| FORCE | OFF | Rear Nominal Lower Link Force |
| DRAFT | AUI | Rear Draft |
| TIMEOUT | AX | Timeout Status |

## Functionality

The function block is activated by the **INIT** event. The qualifier signal **QI** is then forwarded to the internal function block **I_RHS**. After successful initialization (or an error), the function block reports back via the **INITO** event and outputs the **QO** and **STATUS** signals. Simultaneously, the data supplied by I_RHS (position, lower link force, draft force) is applied to the corresponding adapters **POSITION**, **FORCE**, and **DRAFT**. The timeout status of I_RHS is output via the **TIMEOUT** adapter. The adapters each use a unidirectional data format (e.g., OFF for analog, unscaled values). Output to the adapters occurs via a separate event (through internal connections of I_CORE.IND). This allows a receiving module to react to the arrival of new data.

## Technical Features

- The module is based on the ISOBUS standard ISO 11783-7 and uses PGN 65093.
- The internal calculations and ISOBUS communication are performed entirely by the **I_RHS** module. IA_RHS serves solely as an adapter wrapper for providing data to the 4diac network.
- All four adapters are unidirectional (output), meaning data is only sent but not received by the connected module.
- Data output to the adapters occurs simultaneously with the **IND** event (internal), which originates from I_RHS.
- Timeout information is provided separately from the main data path.

## State Overview

This function block does not have explicitly modeled states. Its behavior is determined by the internal function block I_RHS:

- **Initialization (INIT)**: The qualifier QI controls activation.
- **Operation**: After successful initialization, I_RHS cyclically or event-driven delivers new data to the adapters.
- **Error/Timeout**: A timeout is signaled via the TIMEOUT adapter, and the status is output as text via the **STATUS** output.

## Application Scenarios

- **Tractor Control with ISOBUS Connection**: Reading the rear linkage data (hitch status) from an ISOBUS-compatible terminal or control unit and forwarding it to a higher-level controller.
- **Agricultural Implements**: Connecting implements that require the rear linkage position or force (e.g., plow depth control).
- **Diagnostics and Monitoring**: Recording timeout status and system status for maintenance and fault analysis.

## Comparison with Similar Modules

Unlike a general ISOBUS receiver (e.g., a raw PGN parser), **IA_RHS** abstracts the ISOBUS-specific message processing and provides the data in standardized adapter formats. Compared to a direct I_RHS module, IA_RHS offers the advantage that data output is via separate adapters, enabling loose coupling in the network and easier reuse. Modules such as **IA_RHC** (Rear Hitch Control) or **IA_PTO** follow a similar adapter concept but are designed for other ISOBUS functions.

## Conclusion

The IA_RHS module is a practical, standards-compliant encapsulation of the rear hitch status according to ISO 11783-7. It simplifies the integration of ISOBUS data into a 4diac-based control system by hiding the complex bus interface behind easy-to-use adapters. The division into multiple data adapters and the provision of a timeout status make it flexibly applicable to various agricultural technology applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
