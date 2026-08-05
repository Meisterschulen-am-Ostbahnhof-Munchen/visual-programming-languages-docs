# IA_PosDeltaHighPrecRapidUpd
![IA_PosDeltaHighPrecRapidUpd](./IA_PosDeltaHighPrecRapidUpd.svg)
* * * * * * * * * *
## Introduction
The function block `IA_PosDeltaHighPrecRapidUpd` is an ISOBUS adapter module for high-precision, rapidly updated position deltas according to the NMEA 2000 standard (PGN 129027). It encapsulates the internal core module `I_PosDeltaHighPrecRapidUpd` and makes its output data available via adapter interfaces. This allows position changes (time, latitude, and longitude deltas) as well as a timeout status to be seamlessly integrated into automation systems.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |

|----------|-------|---------------------------------------------------------|

| `INIT` | EInit | Initialize the function block; used with `QI`. |

### **Event Outputs**

| Event | Type | Description |

|----------|-------|-------------------------------------------------|

| `INITO` | EInit | Initialization confirmation; returns `QO` and `STATUS`. |

### **Data Inputs**

| Name | Type | Description |

|------|--------|-----------------------------|

| `QI` | `BOOL` | Qualifier for INIT event. |

### **Data Outputs**

| Name | Type | Description |

|----------|----------|-----------------------------------|

| `QO` | `BOOL` | Output qualifier (Initialization successful?). |

| `STATUS` | `STRING` | Initialization status message. |

### **Adapters**

| Adapter name | Type (Adapter) | Description |

|--------------------|----------------------------------|-----------------------------------------|

| `TIME_DELTA` | `adapter::types::unidirectional::AUI` | Returns the time delta (unsigned integer). |

LAT_DELTA` | `adapter::types::unidirectional::AI` | Returns the latitude delta (signed integer). |

LON_DELTA` | `adapter::types::unidirectional::AI` | Returns the longitude delta (signed integer). |

TIMEOUT` | `adapter::types::unidirectional::AX` | Indicates whether a timeout occurred (Bool). |

## Functionality

This function block acts as a wrapper around the internal function block `I_PosDeltaHighPrecRapidUpd`. The kernel is initialized when a `INIT` event occurs with a set `QI`. After successful initialization, the kernel reports back with `INITO` and delivers `QO = TRUE` along with a corresponding status. As soon as new position data arrives, the kernel generates the event `IND` (internal, not directly visible), which forwards the data to the three delta adapters. Simultaneously, if a timeout occurs, the event `TIMEOUT` is triggered, and the corresponding adapter is updated.

... The internal data connections ensure that the values from `TimeDelta`, `LatitudeDelta`, `LongitudeDelta`, and `Q_timeout` are transferred to the corresponding adapter data port `D1`.

## Technical Features
- **Standard Compliance**: The module implements NMEA 2000 PGN 129027 – "Position Delta, High Precision Rapid Update".
- **Adapter-Based**: The output data is provided via flexible, unidirectional adapters, allowing direct connection to other modules in a 4diac system.
- **High Precision & Update Rate**: Optimized for applications requiring accurate and rapid position changes (e.g., in agriculture or vehicle navigation).
- **Initialization with Status**: The function block provides an explicit initialization confirmation (QO, STATUS) and can therefore be integrated into safety-critical processes.

## State Overview

The function block does not have an explicit finite state machine (ECC) in its XML definition. Its behavior is entirely controlled by the internal core function block `I_PosDeltaHighPrecRapidUpd`:

1. **Wait for Initialization**: After system startup, `QI = FALSE` is present; `INIT` is not triggered.

2. **Start Initialization**: Upon the `INIT` event with `QI = TRUE`, the core is activated.

3. **Initialization Confirmed**: The core reports `INITO` with `QO = TRUE` and a positive status; data provisioning then begins.

4. **Data Update**: With each new position delta, the adapters are automatically updated with the current values.

5. **Timeout**: If no more valid data is received, the core sets `Q_timeout = TRUE` and triggers the `TIMEOUT` event.

## Application Scenarios
- **Precision Agriculture**: Monitoring of position changes of a tractor or agricultural machine in real time (e.g., for steering systems or application maps).
- **Vehicle Navigation**: Processing of high-precision GNSS deltas in autonomous vehicles.
- **ISOBUS Integration**: Connection to existing ISOBUS control units based on PGN 129027.
- **Safety Monitoring**: Detection of data failures via the timeout adapter.

## Comparison with Similar Modules

Similar ISOBUS adapter modules (e.g., `IA_PosSpeed` or `IA_TimeDate`) also encapsulate specific PGNs and provide their data via adapters. The `IA_PosDeltaHighPrecRapidUpd` differs in that:

- Specialization in **position deltas** (not absolute positions)
- Support for **time, latitude, and longitude deltas** as well as a separate **timeout** signal
- Focus on high **precision** and fast **update rates**

Other modules often only provide a single measurement or lack timeout monitoring.

## Conclusion

The `IA_PosDeltaHighPrecRapidUpd` is a specialized ISOBUS adapter for high-precision position changes according to NMEA 2000 PGN 129027. It offers a standards-compliant, adapter-based interface that integrates seamlessly into 4diac systems. Thanks to its integrated timeout detection and explicit initialization confirmation, it is particularly suitable for safety-critical automation solutions in agriculture and automotive engineering.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
