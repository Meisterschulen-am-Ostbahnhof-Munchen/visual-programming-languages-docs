# IA_VP1

![IA_VP1](./IA_VP1.svg)

* * * * * * * * * *

## Introduction

The function block **IA_VP1** is an ISOBUS adapter for Vehicle Position 1 (VP1) according to ISO 11783-7 (PGN 65267). It encapsulates the communication for the vehicle position and provides the received data via unidirectional adapter interfaces for further processing in the 4diac IDE.

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

| Variable | Type | Comment |
|----------|-----|-----------|
| QI | BOOL | Event Input Qualifier |

### **Data Outputs**

| Variable | Type | Comment |
| ---------- | ----- | ----------- |
| QO | BOOL | Event Output Qualifier |
| STATUS | STRING | Status Information |

### **Adapters**

| Adapter | Type | Comment |
| --------- | ----- | ----------- |
| LAT | adapter::types::unidirectional::AR | Latitude |
| LON | adapter::types::unidirectional::AR | Longitude |
| TIMEOUT | adapter::types::unidirectional::AX | Timeout Status |

## Functionality

The function block internally contains an instance of the function block `I_VP1` from the library `isobus::tecu`. Upon arrival of the INIT event, initialization is triggered – the qualifier `QI` determines whether initialization is active. After successful initialization, the INITO event is triggered, accompanied by the output data `QO` and `STATUS`.

The actual position data (latitude and longitude) and the timeout status are output via the unidirectional adapters. Each adapter is triggered by an event (e.g., `IND` from the core module) and provides the corresponding data value (`D1`) at the adapter interface.

## Technical Features

- **Unidirectional Adapters:** The LAT and LON interfaces use the type `AR`, which provides only one output data value. The TIMEOUT adapter uses the type `AX` for a Boolean timeout status.
- **ISOBUS Compliance:** The module implements the Vehicle Position 1 (VP1) message format according to ISO 11783-7.
- **Latitude/Longitude Provisioning:** The values are passed directly from the internal core block and are available as floating-point numbers in the adapter.
- **Timeout Monitoring:** The TIME
OUT adapter signals whether the position data has arrived within the expected time.

## State Overview

The block does not have an explicitly displayed state machine. Its behavior is event-driven:

- **Inactive:** No initialization occurs before the INIT event.
- **Initialization:** As soon as INIT arrives with `QI=TRUE`, the initialization sequence is started.
- **Active:** After successful INITO, the position and timeout data are available at the adapters. The data is updated with each new internal event (triggered by the core).
- **Error Case:** The status string and `QO` provide information about errors or timeouts.

## Application Scenarios

- **Agricultural Vehicles:** Reading the current GPS position (latitude/longitude) via the ISOBUS on-board computer.
- **Precision Agriculture:** Using the position data to control section control, variable application rates, or guidance systems.
- **Documentation and Telemetry:** Recording vehicle movements and position data for fleet management.

## Comparison with Similar Modules

- **IA_VP0, IA_GP, IA_PD:** Other ISOBUS position and data adapters (e.g., for speed, machine position). In contrast, IA_VP1 focuses solely on the vehicle position (latitude, longitude) and the timeout status. The data is provided here as unidirectional adapters and not as simple data outputs.
- **I_VP1 (Core Block):** The internal core block offers the same functionality, but without the adapter encapsulation. IA_VP1 makes the interfaces more accessible for the modular 4diac environment.

## Conclusion

The **IA_VP1** function block is a practical and standards-compliant block for integrating vehicle position data from ISOBUS into the 4diac world. The use of unidirectional adapters enables clean separation and easy integration into larger automation networks. Thanks to its standards compliance and simple initialization, it is ideally suited for agricultural control systems and IoT applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
