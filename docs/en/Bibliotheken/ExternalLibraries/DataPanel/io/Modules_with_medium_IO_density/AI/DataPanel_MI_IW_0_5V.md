# DataPanel_MI_IW_0_5V
![DataPanel_MI_IW_0_5V](./DataPanel_MI_IW_0_5V.svg)
* * * * * * * * * *
## Introduction
The function block **DataPanel_MI_IW_0_5V** is a service interface function block (SIFB) for acquiring analog input signals in the voltage range **0 ... 5 V**. It provides the interface to an analog input channel of the DataPanel-MI-IW series and enables initialization, cyclic querying, and asynchronous reception of measured values via a bus system. The block is implemented as an IEC 61499-compliant FB and uses system-specific data types from the package `DataPanel::io::MI::AI`.
## Interface Structure

### **Event Inputs**

| Event | Type | Description | With Variables |

|----------|-----|--------------|---------------|

| `INIT` | EInit | Initializes the service connection | `QI`, `PARAMS`, `u8SAMember`, `Input`, `AnalogInput_hysteresis` |

| `REQ` | Event | Requests a current measurement value | `QI` |

### **Event Outputs**

| Event | Type | Description | With Variables | ... |----------|-----|--------------|---------------|

| `INITO` | EInit | Initialization Confirmation | `QO`, `STATUS` |

| `CNF` | Event | Confirmation of a Completed Request | `QO`, `STATUS`, `IN` |

| `IND` | Event | Asynchronous Indication of a Measured Value from the Resource | `QO`, `STATUS`, `IN` |

### **Data Inputs**

| Variable | Type | Description | Initial Value |

|----------|-----|--------------|-------------|

| `QI` | BOOL | Qualifier for Event Inputs | – |

| `PARAMS` | STRING | Service Parameter (e.g., Communication Address) | – |

| `u8SAMember` | USINT | Node SA Address (224 … 239) | `MI::MI_00` |

| `Input` | DataPanel::io::MI::AI::DataPanel_MI_AI_S | Selection of the analog input channel (e.g., AnalogInput_1A … 8B) | `Invalid` |

| `AnalogInput_hysteresis` | WORD | Hysteresis value for signal evaluation | – |

### **Data Outputs**

| Variable | Type | Description |

|----------|-----|--------------|

| `QO` | BOOL | Output qualifier (indicates valid status) |

| `STATUS` | STRING | Service status message (e.g., error text) |

| `IN` | WORD | Measured analog value (raw value) from the resource |

### **Adapter**

No adapter interfaces are available.

## Functionality

The function block operates according to the **service interface principle**: It communicates with an underlying hardware resource (e.g., a bus system or I/O module) via events.

1. **Initialization (`INIT`)**

A `INIT` event (with `QI` set) initiates the connection. The parameters `PARAMS`, `u8SAMember`, `Input`, and `AnalogInput_hysteresis` define the target address and channel configuration. After successful initialization, `INITO` is triggered, and `QO` is set to `TRUE` and `STATUS` to the corresponding text.

2. **Measurement Request (`REQ`)**

Once the function block (FB) is initialized, a current measurement value can be requested via `REQ`. The function block (FB) sends the request to the resource and signals upon receiving the result with ``CNF``. The raw value is provided in the output variable ``IN`` (type ``WORD``).

3. **Asynchronous Indication (`IND`)**

The resource can independently report changes in measured values or alarms. These are reported via the ``IND`` event with the corresponding value in ``IN``.

In case of a negative value (`QI`) or an error, `QO` is set to `FALSE` and `STATUS` to an error description.

## Technical Features
- **System-Specific Types**

The function block uses the user-defined structures `DataPanel_MI_AI_S` (channel selection) and the constants `MI::MI_00` (address specification). These are defined in the package `DataPanel::io::MI::AI`.

- **Hysteresis**

A hysteresis value can be specified via the input `AnalogInput_hysteresis` as a `WORD` value to suppress the noise of the analog signal.

- **Channel Addressing**

The analog input channel is selected via the ``Input`` parameter. Valid values are, for example, ``AnalogInput_1A`` through ``AnalogInput_8B``; the initial value ``Invalid`` must be replaced with a valid channel before first use.

## State Overview

Since the XML definition does not contain an ECC (Execution Control Chart), the state logic is derived from the typical behavior of a SIFB (Single-Integrated Function Block). An abstract state machine can be described as follows:

| State | Description | Event | Action |

|---------|---------------|----------|---------|

| **IDLE** | Waiting for Initialization | `INIT` (QI=TRUE) | Starting connection |

**INIT** | Initialization in progress | – | Waiting for resource confirmation |

**READY** | Ready for requests | `INITO` | Set QO=TRUE |

**BUSY** | Measurement request in progress | `REQ` | Sending request to resource |

**DONE** | Response received | `CNF` | Loading `IN` and setting QO=TRUE |

**ERROR** | Error status | – | Set QO=FALSE, STATUS=Error text |

Asynchronous `IND` events can occur in the **READY** or **BUSY** states and result in the immediate availability of the value.

## Application Scenarios
- **Agricultural Sensors** (e.g., level sensors, pressure sensors, temperature sensors with 0-5V output)
- **Data Acquisition in Stationary Motors** or **Vehicle Control Units** of the DataPanel family
- **Multi-Channel Analog Value Acquisition** through parallel instances of the FB with different `Input` and `u8SAMember` values

## Comparison with Similar Function Blocks

| Feature | DataPanel_MI_IW_0_5V | Generic Analog Input (e.g., IEC 61499 standard) |

|---------|----------------------|------------------------------------------------------|

| Voltage Range | 0 – 5V | Usually configurable (0-10V, 4-20mA, etc.) |

| Channel Selection | Specific type `DataPanel_MI_AI_S` | Usually `INT` or `STRING` parameter |

| Hysteresis | Separate Variable (`WORD`) | Often not included |

| Bus connection | Proprietary (DataPanel-MI-IW) | Abstract communication interface |

The function block is highly tailored to the DataPanel hardware and therefore offers less flexibility than a generic analog input, but provides a direct, optimized connection.

## Conclusion

The **DataPanel_MI_IW_0_5V** is a specialized service interface function block for acquiring 0–5V analog signals in the DataPanel environment. It encapsulates the complex bus communication and offers a simple, event-driven interface to the application logic. Thanks to its integrated hysteresis and clear channel addressing, it is particularly suitable for robust measurement tasks in agricultural automation.