# IA_FHS
![IA_FHS](./IA_FHS.svg)
* * * * * * * * * *
## Introduction
The function block **IA_FHS** serves as an ISOBUS adapter for the Front Hitch Status (FHS) according to ISO 11783-7 (PGN 65094). It encapsulates the internal processing of the function block `I_FHS` and provides the acquired measurement and status values via standardized unidirectional adapter outputs. Initialization occurs via the event `INIT`; after successful completion, the data is provided via the adapter interfaces.
## Interface Structure

### **Event Inputs**

| Event | Type | with variables | Description |

|----------|--------|----------------|---------------------------------|

| `INIT` | EInit | `QI` | Service Initialization |

### **Event Outputs**

| Event | Type | with Variables | Description |

|----------|--------|--------------------|-----------------------------------|

| `INITO` | EInit | `QO`, `STATUS` | Initialization Acknowledgement |

### **Data Inputs**

| Variable | Type | Description |

|----------|--------|-------------------------------|

| `QI` | BOOL | Event Input Qualifier |

### **Data Outputs**

| Variable | Type | Description |

|----------|--------|----------------------------|

| `QO` | BOOL | Output Qualifier |

| `STATUS` | STRING | Status Message (e.g., "OK") |

### **Adapters**

| Adapter | Type | Description |

|-----------|-----------------------------|----------------------------------------------|

| `POSITION`| `adapter::types::unidirectional::AUS` | Front Hitch Position (analog, unsigned) |

| `FORCE` | `adapter::types::unidirectional::AUS` | Front Nominal Lower Link Force (analog) |

| `DRAFT` | `adapter::types::unidirectional::AUI` | Front Draft (analog, integer, unsigned) |

| `TIMEOUT` | `adapter::types::unidirectional::AX` | ISOBUS Reception Timeout Status |

## Functionality

The function block internally contains an instance `I_CORE` of type `isobus::tecu::I_FHS`. Upon arrival of the initialization event `INIT`, the kernel is activated with the qualifier `QI`. After successful initialization, it triggers the event `INITO`, sets `QO = TRUE`, and outputs the status as `STATUS`. Simultaneously, the kernel generates the event `IND`, which is forwarded via internal event connections to the adapters `POSITION`, `FORCE`, and `DRAFT`. The corresponding data values (`FRONT_HITCH_POSITION`, `FRONT_HITCH_NOMINAL_LOWER_LINK_FORCE`, `FRONT_HITCH_DRAFT`) are transmitted to the adapter outputs via the appropriate data connections. Any ISOBUS reception timeout is reported via the adapter event `TIMEOUT.E1` and the data value `Q_timeout`.

## Technical Features
- **Standard Compliance**: The module meets the requirements of ISO 11783-7 for **PGN 65094** (Front Hitch Status).
- **Adapter Interfaces**: All sensor values are output via unidirectional adapters, enabling flexible and decoupled further processing in the 4diac IDE.
- **Initialization Sequence**: Initialization must be explicitly triggered via the event `INIT`; the function block will only function correctly after successful completion.
- **Timeout Monitoring**: The adapter `TIMEOUT` signals whether ISOBUS data reception occurs within the expected time. This serves to detect errors in fieldbus communication.

## State Overview

The function block does not have its own visible state machine. Internal sequence control is handled by the core function block `I_FHS`. Broadly speaking, two phases can be distinguished:

- **Before Initialization**: The function block is inactive. The event outputs and adapters do not provide any data.
- **After Initialization (INIT successful)**:
- `INITO` is triggered, `QO = TRUE`.
- The adapters `POSITION`, `FORCE`, and `DRAFT` are supplied with current measured values cyclically or event-driven.
- The adapter `TIMEOUT` reports the current timeout status.

If an error occurs during operation (e.g., connection loss), this is signaled via the timeout adapter or the status output.

## Application Scenarios
- **Tractor Control**: Acquisition of the front linkage position and the load on the lower links for controlling implements (e.g., front loader, front linkage).
- **ISOBUS Diagnostics**: Monitoring of the ISOBUS data stream for timeouts and plausibility of the force and position values.
- **Data Recording**: Provides position, force, and tractive force data for telemetry or logging applications.

## Comparison with Similar Modules
- **IA_RHS** (Rear Hitch Status): Analog adapter for the rear hitch. The addressing and PGN number differ (e.g., PGN 65096). While `IA_FHS` provides front hitch data, `IA_RHS` focuses on the rear hitch.
- **Direct I_FHS Module**: Without an adapter wrapper, the user would have to integrate the core module `I_FHS` themselves and manually configure the necessary data and event connections. The adapter module simplifies handling through standardized, pre-configured interfaces.

## Conclusion

The **IA_FHS** function block offers a ready-to-use ISOBUS adapter for front hitch status. Thanks to the internal encapsulation of the `I_FHS` core and the output via unidirectional adapters, users can quickly and reliably integrate the values for position, force, and tensile force into their own control or monitoring applications. The integrated timeout monitoring increases the operational reliability of the ISOBUS communication.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
