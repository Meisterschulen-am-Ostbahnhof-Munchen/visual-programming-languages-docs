# IA_MSS
![IA_MSS](./IA_MSS.svg)

* * * * * * * * * *
## Introduction
The **IA_MSS** function block represents an ISOBUS adapter for machine-selected speed (MSS). It encapsulates the communication with the underlying ISOBUS protocol (PGN 61474) and provides the determined values for speed, distance traveled, and timeout status via standardized adapter interfaces. The block is typically embedded in an ISOBUS-compatible control unit (TECU) and enables easy integration into IEC 61499-based automation systems.
## Interface Structure
### **Event Inputs**

| Event | Type | Description |
|----------|-----|---------------|
| INIT | EInit | Service Initialization; is triggered by the data input `QI`. |

### **Event Outputs**

| Event | Type | Description |
|----------|-----|--------------|
| INITO | EInit | Initialization confirmation; outputs the data `QO` and `STATUS`. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-----|---------------|
| QI | BOOL | Qualifier for the initialization input. |

### **Data Outputs**

| Variable | Type | Description |
|----------|-----|--------------|
| QO | BOOL | Qualifier for the initialization output. |
| STATUS | STRING | Initialization status message. |

### **Adapter**

| Adapter | Type | Description |
|---------|-----|--------------|
| SPEED | adapter::types::unidirectional::AUI | Output for the machine-selected speed (value of type `AUI`). |
| DISTANCE | adapter::types::unidirectional::AUDI | Output for the machine-selected distance (value of type `AUDI`). |
| TIMEOUT | adapter::types::unidirectional::AX | Output for the timeout status (value of type `AX`). |

## Functionality

The **IA_MSS** block is implemented as a pure adapter wrapper. Internally, it contains an instance of the function block `isobus::tecu::I_MSS` (*I_CORE*), which implements the actual ISOBUS logic. The external interfaces of the adapter are mapped to the internal component via event and data connections:

1. **Initialization** – An event on `INIT` (with `QI` set) activates `I_CORE.INIT`. After successful initialization, `INITO` is triggered, which forwards the qualifiers `QO` and `STATUS` to the adapter's outputs.

2. **Data Provision** – The internal module provides the selected speed (`SELECTEDMACHINESPEED`), the distance (`SELECTEDMACHINEDISTANCE`), and the timeout status (`Q_timeout`). These values are output via the adapters `SPEED`, `DISTANCE`, and `TIMEOUT` as soon as the corresponding events (`IND` and `TIMEOUT`, respectively) occur.

The adapter thus provides a clean separation between ISOBUS communication and the application level.

## Technical Features
- **Standard Compliance** – The module is based on the ISOBUS standard ISO 11783-7 (PGN 61474) for machine-selected speed.
- **Unidirectional Adapters** – The outputs `SPEED`, `DISTANCE`, and `TIMEOUT` are defined as unidirectional adapters (types `AUI`, `AUDI`, `AX`). They only transmit data from the module to the calling application; feedback is not provided.
- **Adapter Wrapper** – The internal logic is fully encapsulated in component `I_CORE`. `IA_MSS` is used exclusively for interface adaptation and event forwarding.
- **Error Handling** – The initialization status is signaled via `STATUS` (STRING) and `QO` (BOOL). Any timeout is reported via the `TIMEOUT` adapter.

## State Overview
Since the function block does not have its own execution state (ECC), the state results from the interaction of input and output events:

| State | Description |
|---------|--------------|
| **Not Initialized** | After system startup or after a failed initialization. `INIT` can be triggered. |
**Initialized** | After successful execution of `INIT` → `INITO` with `QO` set. The adapters deliver valid values. |
**Error/Timeout** | If the internal initialization fails or a timeout is detected, this is signaled via `STATUS` and the `TIMEOUT` adapter. |

## Application Scenarios
- **ISOBUS Control Units (TECU)** – Integration into agricultural machinery to read the speed provided by the tractor or implement.
- **Traction Control** – Use of the selected speed for site-specific applications (e.g., fertilization, crop protection).
- **Distance and Path Measurement** – Evaluation of the distance traveled for controlling working widths or for documentation purposes.
- **Communication Monitoring** – Detection of timeout situations in the ISOBUS network via the `TIMEOUT` adapter.

## Comparison with Similar Modules
- **I_MSS (Direct)** – The internal module `I_CORE` of type `isobus::tecu::I_MSS` offers the same functionality, but without adapter interfaces. `IA_MSS` facilitates integration into systems based on standardized adapters (AUI, AUDI, AX).
- **Other ISOBUS Adapters** – Numerous adapters exist for other PGNs (e.g., for GPS, working width, engine speed). `IA_MSS` is specifically designed for machine-selected speed.

## Conclusion

The **IA_MSS** block is a practical adapter wrapper for the ISOBUS "Machine Selected Speed" data set. It abstracts the communication with the ISOBUS protocol and provides the relevant parameters (speed, distance, timeout) via standardized unidirectional adapters. This enables simple and reusable integration into IEC 61499 applications for agricultural machinery. The block is standards-compliant, robust thanks to timeout monitoring, and particularly suitable for use in TECU-based controllers.
