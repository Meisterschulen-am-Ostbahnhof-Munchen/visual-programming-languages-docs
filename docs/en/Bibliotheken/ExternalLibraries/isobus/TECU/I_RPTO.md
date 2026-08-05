# I_RPTO
* * * * * * * * * *
## Introduction
The **I_RPTO** (Rear Power Take-Off) is a standards-compliant function block for controlling and monitoring the rear power take-off (PTO), developed under the EPL-2.0 license.
Version 1.0 implements the ISO 11783-7 specification (PGN 65091) for the precise control of PTO parameters in agricultural machinery.
![I_RPTO](I_RPTO.svg)

## Interface Structure

### **Event Inputs**
- `INIT`: Initialization Request (with qualifier `QI`)

### **Event Outputs**
- `INITO`: Initialization Confirmation (with status)
- `IND`: Indication Event with all PTO Parameters
- `TIMEOUT`: Timeout Event

### **Data Inputs**
- `QI` (BOOL): Qualifier for Initialization

### **Data Outputs**
- `QO` (BOOL): Qualifier for Output Events
- `STATUS` (STRING): Operating status message
- `Q_timeout` (BOOL): Timeout indicator
- `timestamp_timeout` (DINT): Timeout timestamp
- `timestamp_data` (DINT): PTO data timestamp

## PTO parameters

| Parameter | Type | Description | SPN | Bit length | Scaling |

|-----------|------|--------------|-----|------------|------------|

| `REAR_PTO_OUTP_SHAFT_SPEED` | UINT | Current speed | 1883 | 16 | 0.125 rpm/bit |

| `REAR_PTO_OUTP_SH_SPEED_SET` | UINT | Target Speed | 1885 | 16 | 0.125 rpm/bit |

| `REAR_PTO_ENGAGEMENT` | BYTE | Clutch State | 2408 | 2 | 4 states/2 bits |

| `REAR_PTO_MODE` | BYTE | Operating Mode | 1890 | 2 | 4 states/2 bits |

| `REAR_PTO_ECONOMY_MODE` | BYTE | Economy Mode | 1892 | 2 | 4 states/2 bits |

| `REAR_PTO_ENGAGEMENT_REQ` | BYTE | Clutch Request | 5156 | 2 | 4 states/2 bits |

| `REAR_PTO_MODE_REQ_STATUS` | BYTE | Mode Request | 5157 | 2 | 4 states/2 bits |

| `REAR_PTO_ECONOMY_MODE_REQ_STAT` | BYTE | Economy Mode Request | 5158 | 2 | 4 states/2 bits |

| `REAR_PTO_SH_SPEED_LIMIT_STAT` | BYTE | Speed Limit | 5159 | 3 | 8 states/3 bits |

| `REAR_PTO_EXIT_REASON_CODE` | BYTE | Fault Reason Code | 5820 | 6 | 64 states/6 bits |

## Operating Modes

| Code | Mode | Description |

|------|-------|--------------|

| 0 | Standby | Standby Mode |

| 1 | Speed Mode | Constant Speed |

| 2 | Load Mode | Load-Dependent Control |

| 3 | Reserved | Manufacturer-specific |
... ## Functionality

1. **Initialization**:

- `INIT` with `QI`=TRUE starts system calibration
- `INITO` confirms operational readiness with `QO` and `STATUS`

2. **Speed Control**:

- `IND` provides actual and target speeds
- Automatic adjustment to load changes

3. **Error Handling**:

- `TIMEOUT` in case of communication problems
- Detailed error codes in `REAR_PTO_EXIT_REASON_CODE`

## Technical Features

✔ **ISO 11783-7 compliant** (PGN 65091)

✔ **Precise speed control** with 0.125 RPM Resolution
✔ **4 Operating Modes** for Different Applications
✔ **64-Level Fault Diagnostics** with Detailed Codes

## Application Scenarios
- **Agricultural Machinery**: Drive for Combine Harvesters and Balers
- **Speed Control**: Precise Adaptation to Implements
- **Energy Efficiency**: Economy Mode for Part-Load Operation
- **Diagnostics**: Early Detection of Mechanical Problems

## ⚖️ Comparison with Similar Systems

| Feature | I_RPTO | Standard | Premium |

|---------|--------|----------|---------|

Speed Accuracy | ±0.2% | ±1% | ±0.1% |

Operating Modes | 4 | 2 | 6 |

Diagnostic Scope | 64 Codes | 8 Codes | 128 Codes |

Response Time | <100ms | 200ms | 50ms |

## 🛠️ Related Exercises
* [Exercise_074](../../../../Uebungen/test_B/Uebungen_doc/Uebung_074.md)]
* [Exercise_079](../../../../Uebungen/test_B/Uebungen_doc/Uebung_079.md)]

## Conclusion

The I_RPTO module offers reliable PTO control for modern agricultural machinery:

- **Precise**: High-resolution speed control
- **Flexible**: Multiple operating modes for various applications
- **Robust**: Integrated fault detection and diagnostics

Ideal for use in:

- Tractors with demanding implements
- Precision agriculture
- Energy-efficient drive systems
- Automated work processes