# IA_VDS

![IA_VDS](./IA_VDS.svg)

* * * * * * * * * *

## Introduction

The **IA_VDS** function block is an ISOBUS adapter for vehicle direction and speed according to ISO 11783-7 (PGN 65256). It encapsulates access to the corresponding CAN bus data and provides it as modern 4diac adapter interfaces. The block is initialized via an INIT event and subsequently provides continuous navigation speed, compass direction, altitude, and a timeout status.

## Interface Structure

### **Event Inputs**

| Event | Type | Description |
|----------|-------|--------------|
| INIT | EInit | Initializes the block. Expects the qualifier QI. |

### **Event Outputs**

| Event | Type | Description |
|----------|-------|--------------|
| INITO | EInit | Confirms successful initialization. Returns QO and STATUS. |

### **Data Inputs**

| Name | Type | Description |
|------|--------|--------------|
| QI | BOOL | Event Input Qualifier (TRUE = Initialization active). |

### **Data Outputs**

| Name | Type | Description |
| -------- | -------- | -------------- |
| QO | BOOL | Event Output Qualifier (TRUE = Initialization OK). |
| STATUS | STRING | Message text (e.g., error description or "Ready"). |

### **Adapter**

| Adapter | Type | Description |
| -------------- | ------ | -------------- |
| NAV_SPEED | AUI | Navigation-based vehicle speed (unidirectional, receiver). |
| BEARING | AUI | Compass direction (unidirectional, receiver). |
| ALTITUDE | AUI | Altitude above sea level (unidirectional, receiver). |
| TIMEOUT | AX | Timeout status (unidirectional, receiver). |

All adapters are implemented as plugs (outgoing) – the IA_VDS sends the data to the connected sinks.

## Functionality

The module internally contains another function block, **I_VDS** (from the library `isobus::tecu`), which handles the actual ISOBUS communication. Upon arrival of the INIT event, the initialization of I_VDS is triggered. After successful initialization, I_VDS reports this via its INITO event, which is forwarded to the INITO output of IA_VDS. Simultaneously, I_VDS begins cyclically updating the values for NavigationBasedVehicleSpeed, CompassBearing, and Altitude. These values are output via the corresponding adapters (NAV_SPEED, BEARING, ALTITUDE) as soon as the IND event from I_VDS arrives. If a timeout occurs (e.g., a CAN bus error), this is reported via the TIMEOUT adapter.

## Technical Features

- The module is based on the **Eclipse Public License 2.0 (EPL-2.0)** and is designed as an ISOBUS adapter for PGN 65256.
- Data is distributed asynchronously to the adapter outputs via dedicated events (IND), enabling decoupled processing in the 4diac environment.
- The internal block I_VDS is implemented in the `isobus::tecu` library and optimized for direct bus access.
- The timeout status is provided by a dedicated adapter (type AX) to clearly separate error handling from the normal data stream.

## State Overview

The IA_VDS does not have an explicit state machine; its behavior is determined by the internal I_VDS:

1. **Initial** – No INIT signal has been received yet.
2. **Initialization in progress** – After INIT, as long as I_VDS is not yet ready.
3. **Active** – After successful initialization (INITO = TRUE). Values are updated regularly.
4. **Error** – In case of timeout or invalid bus data (STATUS contains an error message, QO = FALSE).

## Application Scenarios

- **Agricultural Machinery Control** – Integration of driving speed, direction, and height into control logic (e.g., for site-specific applications).
- **ISOBUS Network Connection** – As an adapter in 4diac applications that use ISOBUS data from a tractor or harvester.
- **Telemetry Systems** – Forwarding of VDS data to higher-level systems (cloud, display).

## Comparison with Similar Modules

- **I_TC** (ISOBUS Tractor Control) – Provides general tractor data (speed, PTO speed, linkage) via similar adapters, but not specifically the VDS-PGN.
- **I_GNSS** (ISOBUS GNSS Adapter) – Provides GPS-based position data, but without a focus on direction/speed via CAN.
- **IA_VDS** is specialized for pure vehicle direction/speed information (PGN 65256) and has a particularly streamlined interface.

## Conclusion

The **IA_VDS** is a practical module for easily integrating ISO-11783-7-specific vehicle data (direction/speed) into a 4diac application. The adapter-based output keeps the architecture modular and extensible. The division into data and timeout adapters facilitates robust error handling. Ideal for all applications requiring precise, bus-based vehicle dynamics.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
