# IA_COGSOGRapidUpdate
![IA_COGSOGRapidUpdate](./IA_COGSOGRapidUpdate.svg)
* * * * * * * * * *
## Introduction
The function block **IA_COGSOGRapidUpdate** serves as an ISOBUS adapter for the NMEA 2000 PGN 129026 messages "Course Over Ground (COG)" and "Speed Over Ground (SOG)" with support for rapid updates. It decouples the ISOBUS communication and provides the received navigation data and a timeout status via standardized adapter interfaces. The block was developed under the Eclipse Public License 2.0 and is optimized for use in agricultural control systems (TECU).
## Interface Structure
### **Event Inputs**

| Event | Type | Comment |

|----------|-----|-----------|

| INIT | EInit | Service initialization, triggered by input QI |

### **Event Outputs**

| Event | Type | Comment |

|----------|-----|-----------|

| INITO | EInit | Initialization acknowledgment, returns QO and STATUS |

### **Data Inputs**

| Variable | Type | Comment |

|----------|-----|-----------|

| QI | BOOL | Input qualifier for initialization |

### **Data Outputs**

| Variable | Type | Comment |

|----------|-----|-----------|

| QO | BOOL | Output qualifier (initialization status) |

| STATUS | STRING | Status message (e.g., error text or "OK") |

### **Adapter**

| Adapter Name | Type | Comment |

|--------------|-----|-----------|

| COG | adapter::types::unidirectional::AUI | Course Over Ground |

| SOG | adapter::types::unidirectional::AUI | Speed Over Ground |

| TIMEOUT | adapter::types::unidirectional::AX | Timeout status (active when no update occurs) |

| SID | adapter::types::unidirectional::AUS | Sequence ID (sequential number of the data record) |

| COG_REF | adapter::types::unidirectional::AB | Course reference (e.g., True/Magnetic) |

## Functionality

1. **Initialization**

An event at **INIT** activates the function block. The **QI** input controls the start. After successful initialization, **INITO** is triggered, and the **QO** (TRUE on success) and **STATUS** outputs are set.

2. **ISOBUS Message Processing**

The internal core (FB `I_CORE` of type `isobus::tecu::I_COGSOGRapidUpdate`) continuously receives NMEA 2000 PGN 129026 messages. As soon as new data is available, the following values are output via the corresponding adapters:

- **COG**: Course over ground (e.g., in 0.01° increments)
- **SOG**: Speed over ground (e.g., in 0.01 km/h)
- **SID**: Sequence ID for synchronization
- **COG_REF**: Reference (True or Magnetic)

3. **Timeout Monitoring**

If no valid message is received within a configured time period, the function block activates the **TIMEOUT** adapter. This event can be used by the application to trigger error conditions or plausibility checks.

4. **Output Cycles**

The **COG**, **SOG**, **SID**, and **COG_REF** adapters are triggered together with each valid data reception (event connection `IND`). The **TIMEOUT** adapter is triggered independently upon timeout.

## Technical Features
- **NMEA 2000 PGN 129026** – This module is specifically designed to interpret this PGN, enabling rapid updates of COG and SOG.
- **Adapters instead of direct inputs/outputs** – All navigation data is provided via unidirectional adapters (type `unidirectional::AUI`, `AX`, etc.), allowing for flexible further processing and encapsulation in higher-level networks.
- **License and Origin** – This module is available under the Eclipse Public License 2.0 and was developed by **HR Agrartechnik GmbH** (Version 1.0, April 19, 2026, Author: Franz Höpfinger).

**Adapters instead of direct inputs/outputs** – - **Integration in isobus::tecu** – The function block is part of the `isobus::tecu` library and is based on a low-level ISOBUS implementation.

## State Overview
The function block does not have explicitly modeled states; however, the following operating phases can be derived:

| State | Description |

|---------|--------------|

| **Inactive** | INIT not yet triggered or QI = FALSE |

| **Initializing** | After INIT, until INITO is reported with QO |

| **Active (Data Received)** | Regular reception of PGN 129026, adapter updates |

| **Timeout** | No valid message within the timeout threshold – TIMEOUT adapter active |

| **Error** | Initialization failed (STATUS = error text) |

## Application Scenarios
- **Agricultural Tractors** – Providing course and speed data for automatic steering systems or application maps.
- **ISOBUS-based ECUs** – Integration into a TECU network for evaluating GPS/GNSS data.
- **Fast Control Loops** – Utilizing the rapid update function for dynamic control variables (e.g., for site-specific treatment).
- **Fault Monitoring** – Using the TIMEOUT adapter to detect data failures and activate redundancy mechanisms.

## Comparison with Similar Modules
There are general ISOBUS adapters for COG/SOG (e.g., `I_COGSOG`), but these do not offer rapid update support. The **IA_COGSOGRapidUpdate** is specifically designed for PGN 129026 and additionally provides the sequence ID and timeout status. Similar modules like `I_COGSOGStd` may use a slower update rate or lack timeout detection. Using adapter interfaces (instead of a fixed data port) increases flexibility but requires corresponding adapter configuration in the parent project.

## Conclusion
The **IA_COGSOGRapidUpdate** is a specialized, license-free ISOBUS adapter for high-frequency navigation data. It encapsulates the complex NMEA 2000 communication and offers standardized adapter outputs for heading, speed, sequence ID, and timeout. Its clear initialization logic and error monitoring capabilities make it ideal for real-time applications in agricultural technology. The use of adapter technology enables clean modularization and reusability in a wide variety of control architectures.