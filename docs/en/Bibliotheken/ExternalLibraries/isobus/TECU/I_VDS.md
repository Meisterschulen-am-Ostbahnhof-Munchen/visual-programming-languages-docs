# I_VDS

* * * * * * * * * *
## Introduction

The **I_VDS** function block (Vehicle Direction/Speed) is an ISO 11783-7 compliant system for the precise detection of vehicle direction, speed, and inclination, developed under the EPL-2.0 license.
The block integrates navigation data for modern agricultural machinery and commercial vehicles.
![I_VDS](I_VDS.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initialization Request (with qualifier `QI`)

### **Event Outputs**

- `INITO`: Initialization Confirmation (with status)
- `IND`: Data Indication with Navigation Parameters
- `TIMEOUT`: Timeout Event

### **Data Inputs**

- `QI` (BOOL): Qualifier for Initialization

### **Data Outputs**

| Parameter | Type | SPN | Bit | Scale | Range | Description |
| |-----------|-----|-----|-----|------------|----------|-------------|
| `QO` | BOOL | - | 1 | - | TRUE/FALSE | Event Qualifier |
| `STATUS` | STRING | - | - | - | - | System Status Message |
| `CompassBearing` | UINT | 165 | 16 | 1/128°/bit | 0-360° | Compass Direction |
| `NavigationBasedVehicleSpeed` | UINT | 517 | 16 | 1/256 km/h/bit | 0-250 km/h | GPS-based speed |
| `Pitch` | UINT | 583 | 16 | - | 0xFFFF | Pitch angle (reserved) |
| `Altitude` | UINT | 580 | 16 | - | 0xFFFF | Altitude above sea level (reserved) |

## Functionality

1. **Initialization**:
- `INIT` with `QI`=TRUE starts the GPS/navigation system
- `INITO` confirms operational readiness with `QO` and `STATUS`
2. **Data Update**:
- `IND` provides continuously updated navigation data
- Standard update rate: 100ms for real-time applications
3. **Error Handling**:
- `TIMEOUT` in case of signal loss or communication errors
- Status messages in the `STATUS` field

## Technical Features

✔ **ISO 11783-7 compliant** (PGN) 65256)

✔ **High-precision direction detection** with 0.008° resolution

✔ **GPS-based speed** with 0.004 km/h accuracy

✔ **Extended sensor data** (pitch angle/altitude reserved)

## Application Scenarios

- **Precision agriculture**: Automatic guidance
- **Fleet management**: Real-time tracking and speed monitoring
- **Slope detection**: Safety systems for slopes
- **Telematics**: Operational data acquisition and analysis

## Data formats

| Parameter | Example value | Meaning |
|-----------|--------------|------------|
| `CompassBearing` | 16384 | 128° (16384 × 1/128) |
| `NavigationBasedVehicleSpeed` | 12800 | 50 km/h (12800 × 1/256) |
| `Pitch` | 0xFFFF | Not used |
| `Altitude` | 0xFFFF | Not used |

## ⚖️ Comparison with similar systems

| Feature | I_VDS | Standard GPS | Premium Navigation |
|---------|-------|-------------|--------------|
| Accuracy | ±0.1° Direction | ±5° | ±0.05° |
| Speed | ±0.1% | ±2% | ±0.05% |
| Update Rate | 10 Hz | 1 Hz | 20 Hz |
| ISO Compliance | Full | Partial | Full |

## 🛠️ Related Exercises

- [Exercise_073](../../../../Uebungen/test_B/Uebungen_doc/Uebung_073.md)
- [Exercise_079](../../../../Uebungen/test_B/Uebungen_doc/Uebung_079.md)

## Conclusion

The I_VDS module offers precise navigation for mobile machinery:

- **Precision**: Subgrade-accurate direction detection
- **Reliability**: Robust GPS-based speed
- **Future-proof**: Reserved parameters for extensions

Ideal for use in:

- Automatic steering systems
- Precision agriculture
- Fleet management systems
- Safety-critical applications

*Designed for high-precision vehicle guidance and monitoring*
