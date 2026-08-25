# DataPanel_MI_IW_0_10V

![DataPanel_MI_IW_0_10V](./DataPanel_MI_IW_0_10V.svg)

* * * * * * * * * *
## Introduction

The **DataPanel_MI_IW_0_10V** function block is a service-oriented interface module (SIFB) for acquiring an analog 0-10V input signal. It is designed as part of the **HR Agrartechnik DataPanel MI** system and enables parameterizable initialization as well as cyclical or event-driven retrieval of measured values.
## Interface Structure

### **Event Inputs**

| Event | Type | Data Carried | Description |
|----------|-----|-------------------|---------------|
| `INIT` | `EInit` | `QI`, `PARAMS`, `u8SAMember`, `Input`, `AnalogInput_hysteresis` | Service Initialization: Hardware Connection Configuration |
| `REQ` | `Event` | `QI` | Service Request: Triggering a Measurement Data Query |

### **Event Outputs**

| Event | Type | Accompanying Data | Description |
|----------|-----|-------------------|--------------|
| `INITO` | `EInit` | `QO`, `STATUS` | Initialization Confirmation |
| `CNF` | `Event` | `QO`, `STATUS`, `IN` | Measurement Query Confirmation |
| `IND` | `Event` | `QO`, `STATUS`, `IN` | Asynchronous display (e.g., spontaneous measurement update from the resource) |

### **Data Inputs**

| Name | Type | Initial Value | Description |
|------|-----|--------------|--------------|
| `QI` | `BOOL` | – | Input Qualifier (controls execution) |
| `PARAMS` | `STRING` | – | Service Parameter (e.g., communication configuration) |
| `u8SAMember` | `USINT` | `MI::MI_00` | Node SA Address (valid range 224…239) |
| `Input` | `DataPanel::io::MI::AI::DataPanel_MI_AI_S` | `Invalid` | Analog Input Selection (e.g., `AnalogInput_1A` … `AnalogInput_8B`) |
| `AnalogInput_hysteresis` | `WORD` | – | Hysteresis Value for Signal Smoothing |

### **Data Outputs**

| Name | Type | Description |
|------|-----|--------------|
| `QO` | `BOOL` | Output Qualifier (indicates valid processing) |
| STATUS` | `STRING` | Service Status (Error/Success Message) |
| IN` | `WORD` | Digitized Analog Value (0…10V, raw WORD value) |

### **Adapter**

No adapters available.

## Functionality

1. **Initialization (`INIT`)**

The function block is configured with the parameters `PARAMS`, the node address `u8SAMember`, the selected input `Input`, and the hysteresis `AnalogInput_hysteresis`. Upon successful initialization, the output `INITO` is sent with `QO = TRUE` and a positive `STATUS`.

2. **Measurement Query (`REQ`)**

A new measurement is requested by creating an event at `REQ`. The result is available at output `IN` as soon as event `CNF` is triggered. Qualifiers `QO` and `STATUS` indicate the validity of the value.

3. **Asynchronous Display (`IND`)**

The function block can also receive an event `IND` from the hardware without an explicit request (e.g., during a spontaneous value change or a periodic update). In this case, `IN`, `QO`, and `STATUS` are also updated.

The digitized analog value is provided as a 16-bit word (`WORD`) on output `IN`. The scaling (e.g., 0V → 0, 10V → 65535) depends on the connected hardware and must be interpreted in the application.

## Technical Features

- **HR Agricultural Technology Specific**: This function block is designed for the DataPanel MI family and uses predefined constants from the packages `DataPanel::io::MI::const::MI` and `DataPanel::io::MI::AI::DataPanel_MI_AI`.
- **Hysteresis**: The parameter `AnalogInput_hysteresis` allows you to configure noise reduction or debouncing of the signal.
- **Addressing**: The bus node is selected via `u8SAMember` (USINT, range 224–239); the default is `MI::MI_00`.
- **Compiler Integration**: The block is integrated into the 4diac IDE ecosystem as a SIFB and has a unique type hash (`eclipse4diac::core::TypeHash`).

## State Overview

Since this is a service-oriented block, the internal state machine is controlled by the following events:

- **IDLE** – After successful initialization (or after a reset), the block waits for `REQ` or an external `IND`.
- **BUSY** – After a `REQ`, the hardware query is performed; no further `REQ` is possible during this time. Upon completion, `CNF` is sent, and the state returns to IDLE.
- **ERROR** – If an error occurs during initialization or measurement, `STATUS` is set accordingly, and `QO = FALSE` is signaled.

A detailed state machine (ECC) is not present in the XML model; however, the described behavior is typical for service-oriented SIFBs.

## Application Scenarios

- **Agricultural Technology**: Acquisition of sensor signals (e.g., pressure, temperature, fill level) via 0-10V interfaces on HR data panels.
- **Industrial Control**: Integration of analog measured values into a PLC environment via 4diac applications.
- **Configurable Measuring Points**: Multiple channels of an MI module can be queried using different `Input` values.

## Comparison with Similar Function Blocks

| Function Block | Voltage Range | Platform | Features |
|----------|------------------|-----------|----------------|
| `DataPanel_MI_IW_0_10V` | 0-10V | HR DataPanel MI | Hysteresis, SA Addressing |
| `DataPanel_MI_IW_4_20mA` | 4-20mA | HR DataPanel MI | Analog Current Inputs |
| `GenericAnalogInput` | Variable | Standard IEC 61131 | General Input, No Hysteresis |

This function block is specifically optimized for DataPanel-MI hardware and offers tight coupling to device-specific parameters.

## Conclusion

The **DataPanel_MI_IW_0_10V** function block provides a robust and flexibly configurable interface for acquiring analog 0-10V signals in the HR Agrartechnik DataPanel system. Its channel configuration, addressing, and hysteresis capabilities make it suitable for precise measurement tasks in agricultural automation.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
