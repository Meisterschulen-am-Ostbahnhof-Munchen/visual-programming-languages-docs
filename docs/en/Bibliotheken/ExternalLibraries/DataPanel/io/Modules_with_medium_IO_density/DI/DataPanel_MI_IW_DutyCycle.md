# DataPanel_MI_IW_DutyCycle

No image available.
![DataPanel_MI_IW_DutyCycle](./DataPanel_MI_IW_DutyCycle.svg)

* * * * * * * * * *
## Introduction

The function block `DataPanel_MI_IW_DutyCycle` is a service interface function block (FB) for acquiring and processing frequency input signals (type 7A/8A) in the hardware system. It calculates the duty cycle from the incoming frequency signal and outputs it as a percentage. The block supports initial parameterization as well as event-driven outputs upon significant value changes or time-controlled queries.

## Interface Structure

### **Event Inputs**

| Event | Type | With Variables | Comment |
|----------|-----|----------------|-----------|
| `INIT` | EInit | QI, PARAMS, u8SAMember, Input, FreqDelta, TimeDelta | Service Initialization |
| `REQ` | Event | QI | Service Request |

### **Event Outputs**

| Event | Type | With Variables | Comment |
|----------|-----|---------------|------------|
| `INITO` | EInit | QO, STATUS | Initialization Acknowledgement |
| `CNF` | Event | QO, STATUS, IN | Requested Action Acknowledgement |
| `IND` | Event | QO, STATUS, IN | Resource indication (upon value change/timer) |

### **Data Inputs**

| Variable | Type | Comment |
|----------|-----|-----------|
| `QI` | BOOL | Event input qualifier |
| `PARAMS` | STRING | Service parameter (e.g., configuration string) |
| `u8SAMember` | USINT | Node address (SA 224..239, default: MI::MI_00) |
| `Input` | DataPanel_MI_DI_S | Input identification (must be 7A or 8A, initial value: Invalid) |
| `FreqDelta` | WORD | Required value change in %, to trigger an IND |
| `TimeDelta` | DWORD | Time interval in ms after which an IND is triggered |

### **Data Outputs**

| Variable | Type | Comment |
|----------|-----|-----------|
| `QO` | BOOL | Event output qualifier |
| `STATUS` | STRING | Service status (failure/success message) |
| `IN` | WORD | Measured duty cycle in percent (0..100) |

### **Adapter**

No adapters defined.

## Functionality

The function block initializes itself via the event `INIT`. The following parameters are passed: `QI` (activation), `PARAMS` (general configuration), the node address `u8SAMember`, the physical input (`Input`), the change delta `FreqDelta`, and the time interval `TimeDelta`. After successful initialization, `INITO` is output with valid `QO` and `STATUS`.

A `REQ` event triggers an immediate query of the current duty cycle. The result is output via `CNF`, with the current value displayed in `IN`.

The function block continuously monitors the input. If the measured duty cycle changes by more than the amount specified in `FreqDelta`, a `IND` event is sent with the new value. Additionally, after `TimeDelta` milliseconds (provided no change has occurred in the meantime), a `IND` event is also triggered to ensure regular updates.

## Technical Specifications

- The function block is designed for connection to 7A or 8A type frequency inputs. The input is identified via the structure `DataPanel_MI_DI_S` – set to `Invalid` by default until a valid initialization occurs.
- The node address (SA) is limited to the range 224–239. The default is `MI::MI_00`.
- The parameters `FreqDelta` and `TimeDelta` allow for flexible configuration of the notification behavior: either change-only triggering, time-only triggering, or a combination of both.
- The status `QO` indicates the validity of the output data; `STATUS` contains detailed error or success messages.
- - Compiler imports reference the packages `DataPanel::io::MI::const::MI` and `DataPanel::io::MI::DI::DataPanel_MI_DI::Invalid`, as well as `eclipse4diac::core::TypeHash`.

## State Overview

An explicit state machine is not defined in the XML. However, the following sequence can be derived from the behavior of the events:

1. **Initialization State** – After `INIT`, the module is configured and transitions to the operating state. Errors result in `INITO` with a negative `QO`.
2. **Operating State** – `REQ` is followed by `CNF` with the current duty cycle. When changes occur or the timer expires, `IND` is sent.
3. **Error State** – In case of invalid parameters or hardware errors, `STATUS` is set accordingly, and `QO` is changed to `FALSE`.

## Application Scenarios

- **Speed Measurement in Agricultural Machinery** – Monitoring of frequency signals (e.g., from speed sensors) and output of the duty cycle as an indicator of engine speed or conveying rate.
- **Pulse Width Modulation (PWM) Analysis** – Measurement of the duty cycle of a PWM signal for controlling actuators or for providing feedback on the fill level.
- **Vibration/Frequency Monitoring** – Acquisition of periodic signals with configurable sensitivity (FreqDelta) and update rate (TimeDelta).

## Comparison with Similar Components

- **`DataPanel_MI_DI`**: A digital input component without frequency or duty cycle calculation. Provides only binary states.
- **`DataPanel_MI_AI`**: Analog input component for voltage or current signals; not optimized for frequency signals.
- **`DataPanel_MI_IW_Frequency`**: Measures the absolute frequency, not the duty cycle. `DataPanel_MI_IW_DutyCycle` adds the percentage on/off time to this.

## Conclusion

The `DataPanel_MI_IW_DutyCycle` function block offers a robust and configurable interface for acquiring duty cycles from frequency inputs in the 7A/8A range. The parameters `FreqDelta` and `TimeDelta` allow the reporting behavior to be flexibly adapted to the application. It is particularly suitable for use in agricultural technology and industrial control systems where reliable duty cycle monitoring is required.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
- [🌐 The PWM Signal & Infographic on ms-muc-docs.de](https://www.ms-muc-docs.de/automatisierung/das-pwm-signal-die-kunst-spannung-zu-zerhacken/das-pwm-signal-die-kunst-spannung-zu-zerhacken-website/)

]
