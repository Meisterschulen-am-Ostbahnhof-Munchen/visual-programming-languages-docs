# DataPanel_MI_IW_0_32V
![DataPanel_MI_IW_0_32V](./DataPanel_MI_IW_0_32V.svg)
* * * * * * * * * *
## Introduction
The function block **DataPanel_MI_IW_0_32V** is a Service Interface Function Block (SIFB) according to IEC 61499. It is used to read an analog voltage signal in the range of 0–32V via a DataPanel MI module. The block handles the initialization of the communication channel, the configuration of an analog input (e.g., AnalogInput_1A to 8B), and the cyclical querying or reception of measured values. The output is as a **WORD** value; the status is signaled via **STATUS** and the **CNF** or **IND** event.
## Interface Structure

### **Event Inputs**

| Event | Comment | With |

|-------|-----------|------------|

**INIT** | Service Initialization | QI, PARAMS, u8SAMember, Input, AnalogInput_hysteresis |

**REQ** | Service Request (Measurement Retrieval) | QI |

### **Event Outputs**

| Event | Comment | With |

|-------|-----------|------------|

**INITO** | Initialization Acknowledgement | QO, STATUS |

**CNF** | Service Request Acknowledgement | QO, STATUS, IN |

**IND** | Indication of a New Measured Value from the Resource | QO, STATUS, IN |

### **Data Inputs**

| Name | Type | Initial Value | Comment |

|------|-----|-------------|-----------|

| **QI** | BOOL | – | Event input qualifier |

| **PARAMS** | STRING | – | Service parameters (e.g., addresses, baud rate) |

| **u8SAMember** | USINT | `MI::MI_00` | Node SA address (224..239) |

| **Input** | DataPanel::io::MI::AI::DataPanel_MI_AI_S | `Invalid` | Analog input selection (AnalogInput_1A … 8B) |

| **AnalogInput_hysteresis** | WORD | – | Analog value hysteresis (configuration) |

### **Data Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| **QO** | BOOL | Event Output Qualifier |

| **STATUS** | STRING | Service Status (e.g., error/success messages) |

| **IN** | WORD | Measured Analog Value (0..32V scaled as WORD) |

### **Adapters**

No adapters available.

## Functionality

The function block is started by the **INIT** event. The passed parameters (node address, analog input selection, and hysteresis) are then passed to the hardware. After successful initialization, **INITO** is triggered with `QO = TRUE`.

A **REQ** event triggers the query of the current analog value. The measured value is provided as a **WORD** via the **IN** output and acknowledged via the **CNF** event. The resource can also spontaneously send a new value, which is then signaled via the **IND** event – also with the current **IN** and **STATUS** values.

**STATUS** returns a valid value for `"OK"`; in case of errors (e.g., communication error, invalid channel), an error message is issued and `QO` is set to `FALSE`.

## Technical Specifications
- **Voltage Range:** 0V to 32V, represented as a WORD – scaling is hardware-dependent.
- **Hysteresis Configuration:** The parameter `AnalogInput_hysteresis` allows setting a threshold to suppress noise or small voltage fluctuations.
- **Initialization:** The input `u8SAMember` must contain a valid node address (224–239); `Input` selects the specific analog channel. The default settings are `MI::MI_00` (address of the first MI module) and `Invalid`, meaning a valid channel must be set before the first INIT.
- **Service Interface Block:** The FB communicates directly with the hardware and is not modeled by an ECC state machine – event control is event-driven, following the SIFB pattern.

## State Overview

Since this is a Service Interface FB, the internal logic is handled by the hardware. From the perspective of the IEC 61499 model, the following typical phases emerge:

- **IDLE:** After system startup, before an INIT has been triggered.
- **INITIATE:** During INIT processing (hardware parameterization).
- **OPERATIONAL:** After successful INIT – REQ and IND events are processed.
- **ERROR:** In case of faulty initialization or loss of communication – STATUS contains an error message.

## Application Scenarios
- **Voltage Monitoring:** Acquisition of sensor signals (e.g., pressure sensors, level sensors) with an output signal of 0…10V or 0…32V.
- **Analog Value Acquisition in Agricultural Technology:** Integration into a DataPanel control system for recording analog values from various machine components.
- **Hysteresis-controlled threshold evaluation:** Direct use of the input value in downstream logic that reacts to thresholds being exceeded or fallen below.

## Comparison with similar components

Unlike generic analog input components (e.g., `AI_BASIC`), the **DataPanel_MI_IW_0_32V** is specifically optimized for DataPanel MI hardware. Typical differences:

- **Parameterization:** Specific node address (`u8SAMember`) and channel selection (`Input`) instead of generic configuration strings.
- **Hysteresis:** Explicit input for hysteresis – with standard components, this is often controlled via the communication driver parameterization.
- **Voltage Range:** Fixed at 0–32V; other modules may offer adjustable measurement range.

## Conclusion

The **DataPanel_MI_IW_0_32V** is a practical, custom-designed module for the DataPanel platform, enabling the acquisition of analog signals in the 0–32V range. Its clear interface (initialization, retrieval, spontaneous indication) and integrated hysteresis make it ideal for use in agricultural control systems and other industrial applications with DataPanel components. Easy operation via the INIT and REQ events, along with standardized status feedback, allows for rapid integration into IEC 61499 projects.