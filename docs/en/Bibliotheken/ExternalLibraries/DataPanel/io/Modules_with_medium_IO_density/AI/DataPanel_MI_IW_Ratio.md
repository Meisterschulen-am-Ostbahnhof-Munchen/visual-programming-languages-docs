# DataPanel_MI_IW_Ratio

![DataPanel_MI_IW_Ratio](./DataPanel_MI_IW_Ratio.svg)

* * * * * * * * * *
## Introduction

The function block **DataPanel_MI_IW_Ratio** is a service interface function block (SIFB) for acquiring analog input data with ratiometric conversion. It provides the interface to a sensor connected to a node (SA 224..239) whose measured value is output as a 16-bit word (WORD). This block is part of the library `DataPanel::io::MI::AI` and is typically used in automation technology, particularly in agricultural engineering.
## Interface Structure

### **Event Inputs**

| Event | Type | With Variables | Comment |
|----------|-----|---------------|-----------|
| INIT | EInit | QI, PARAMS, u8SAMember, Input, AnalogInput_hysteresis | Service Initialization |
| REQ | Event | QI | Service Request |

### **Event Outputs**

| Event | Type | With Variables | Comment |
|----------|-----|---------------|------------|
| INITO | EInit | QO, STATUS | Initialization Confirmation |
| CNF | Event | QO, STATUS, IN | Confirmation of Requested Service |
| IND | Event | QO, STATUS, IN | Indication from Resource |

### **Data Inputs**

| Variable | Type | Initial Value | Comment |
|----------|-----|-------------|-----------|
| QI | BOOL | – | Event Input Qualifier |
| PARAMS | STRING | – | Service Parameters |
| u8SAMember | USINT | MI::MI_00 | Node SA 224..239 |
| Input | DataPanel::io::MI::AI::DataPanel_MI_AI_S | Invalid | Identify the Input AnalogInput_1A..8B |
| AnalogInput_hysteresis | WORD | – | (no value specified) |

### **Data Outputs**

| Variable | Type | Comment |
| |----------|-----|-----------|
| QO | BOOL | Event Output Qualifier |
| STATUS | STRING | Service Status |
| IN | WORD | Input data from resource |

### **Adapter**

No adapters available.

## Functionality

The function block operates as a state-controlled service interface block:

1. **Initialization (INIT)**:

The function block is configured via the INIT event. The inputs `PARAMS`, `u8SAMember`, `Input`, and `AnalogInput_hysteresis` define the bus/node address, the analog channel, and the hysteresis. The `QI` input must be set to TRUE to start initialization. After successful configuration, the INITO event is output with `QO = TRUE` and `STATUS = "OK"` (or similar).

2. **Measurement Request (REQ)**:

The REQ event requests a new measurement from the sensor. The function block evaluates the hardware and returns the result via the CNF event at output `IN`. Here too, `QO` indicates the validity of the value.

3. **Indication (IND)**:

If the hardware supports asynchronous events (e.g., cyclic updates), the IND event is used to report the current measurement value without prompting.

The measurement value is output as a 16-bit word (WORD) in ratiometric format. This means that the digital value is directly proportional to the ratio of the measured voltage to the reference voltage.

## Technical Features

- **Ratiometric Measurement**: The function block is specifically designed for ratiometric sensors where the output is proportional to the supply voltage. This minimizes measurement errors caused by voltage fluctuations.
- **Configuration via constants**: The initial value of `u8SAMember` (`MI::MI_00`) and the data type `DataPanel_MI_AI_S` are derived from imported libraries (`DataPanel::io::MI::const::MI` and `DataPanel::io::MI::AI::DataPanel_MI_AI`). The valid address range for the node is between 224 and 239 (Node SA 224..239).
- **Hysteresis**: Threshold hysteresis behavior can be implemented using `AnalogInput_hysteresis`; the exact effect depends on the underlying driver.
- **TypeHash attribute**: The attribute `eclipse4diac::core::TypeHash` is used for unique type identification in the runtime system.

## State Overview

Since the function block is implemented as a service interface function block, it has an internal state machine. The typical states are:

- **IDLE**: Waiting for an INIT event.
- **INIT**: Initialization is being executed (parameterization, hardware access).
- **READY**: Initialization is complete, waiting for REQ or IND.
- **REQ**: Processing a measurement request.
- **IND**: Asynchronous indication is being processed.

In case of an error, `QO = FALSE` is set and `STATUS` contains a corresponding error message.

## Application Scenarios

- **Agricultural Machinery**: Acquisition of sensor values (e.g., fill levels, pressure, position) via the ratiometric input of a data panel.
- **Industrial Automation**: Connection of analog sensors with voltage output (0…5V, 0…10V) that operate ratiometrically.
- **Early Prototypes**: The module can be directly integrated into a controller from the 4diac IDE and tested with any parameters.

## Comparison with Similar Modules

| Module | Feature |
|----------|---------|
| `DataPanel_MI_AI` | Standard analog input without explicit ratiometric design. |
| `DataPanel_MI_IW_Voltage` | Voltage measurement with absolute values (e.g., mV). |
| **DataPanel_MI_IW_Ratio** | Specifically optimized for ratiometric sensors. |

The module described here differs primarily in its use of the ratiometric measurement principle, which is employed in many modern sensors (e.g., Hall effect sensors, potentiometers).

## Conclusion

The `DataPanel_MI_IW_Ratio` is a specialized service interface function block for the reliable acquisition of ratiometric analog signals. With its clearly defined interface (INIT/REQ/IND) and configurable parameters, it is ideally suited for use in agricultural and automation applications. Integration into the 4diac IDE is achieved via the `DataPanel::io::MI::AI` library.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
