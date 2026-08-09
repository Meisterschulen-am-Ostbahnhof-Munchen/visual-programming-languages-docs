# DataPanel_MI_IW_4_20mA

![DataPanel_MI_IW_4_20mA](./DataPanel_MI_IW_4_20mA.svg)

* * * * * * * * * *
## Introduction

The function block **DataPanel_MI_IW_4_20mA** is a service interface function block (SIFB) for acquiring analog input data in the 4-20mA range. It serves as an interface between the automation system and a hardware-level analog input module. The block handles the initialization of communication (e.g., bus connection), the cyclic request for measured values, and the provision of the measured raw data via output events.

* * * * * * * * * *
## Interface Structure

### **Event Inputs**

| Event | Type | Description | Associated Variables |
|----------|-------|------------------------------------------------|---------------------------------------------|
| `INIT` | EInit | Service Block Initialization | QI, PARAMS, u8SAMember, Input, AnalogInput_hysteresis |
| `REQ` | Event | Request for a Measured Value Update | QI |

### **Event Outputs**

| Event | Type | Description | Carried Variables |
|----------|-------|----------------------------------------------------|---------------------------|
| `INITO` | EInit | Confirmation of Successful Initialization | QO, STATUS |
| `CNF` | Event | Confirmation of a Requested Measurement | QO, STATUS, IN |
| `IND` | Event | Asynchronous Display of an Incoming Measured Value | QO, STATUS, IN |

### **Data Inputs**

| Variable | Type | Description | Initial Value |
|------------------------|---------------|-----------------------------------------------------------|-----------------------------------|
| `QI` | BOOL | Qualifier for the Event Input | – |
| `PARAMS` | STRING | Parameter for Service Initialization | – |
| `u8SAMember` | USINT | Node Address (224…239) of the Slave Device | `MI::MI_00` (224) |
| `Input` | *DataPanel::io::MI::AI::DataPanel_MI_AI_S* | Analog input channel identification (e.g., AnalogInput_1A..8B) | `Invalid` |
| `AnalogInput_hysteresis` | WORD | Hysteresis value for signal smoothing | – |

### **Data Outputs**

| Variable | Type | Description |
|----------|--------|-------------------------------------------------|
| `QO` | BOOL | Qualifier for event output |
| `STATUS` | STRING | Status message (e.g., error, initialization) |
| `IN` | WORD | Raw value read from analog input |

### **Adapter**

*No adapters defined.*

* * * * * * * * * *
## Functionality

This function block implements asynchronous communication with a slave device (e.g., an analog input module with a 4-20mA interface) via a proprietary bus.

1. **Initialization** (`INIT`):

The parameters `PARAMS` (e.g., baud rate, protocol settings), the node address (`u8SAMember`), and the specific analog input channel (`Input`) are set. Hysteresis (`AnalogInput_hysteresis`) can be specified to stabilize the raw value. After a successful connection, `INITO` is sent along with `QO = TRUE`.

2. **Measurement Request** (`REQ`):

This function block requests the current measured value of the configured channel. The response is delivered asynchronously via output `CNF` (upon successful request) or, if necessary, via `IND` (in case of spontaneous value changes or cyclical messages from the slave). The read value appears in the output variable `IN` as a 16-bit raw value.

3. **Asynchronous Indication** (`IND`):

If the slave device sends data independently (e.g., upon exceeding a threshold), `IND` is triggered. This allows even unsolicited measurement values to be acquired.

The outputs `QO` and `STATUS` provide information about the success of the operations (e.g., initialization error, communication error).

* * * * * * * * * *
## Technical Specifications

- **Target Platform**: The module is designed for the "DataPanel" system of HR Agrartechnik GmbH (version 1.0, year 2026).
- **Node Address Range**: The slave addresses `u8SAMember` are limited to the range 224–239; The initial value `MI::MI_00` corresponds to the smallest address (224).
- **Input Channel Identification**: The data type `DataPanel_MI_AI_S` defines possible channels (`AnalogInput_1A … 8B`). The initial value `Invalid` indicates that no channel is selected before the first initialization.
- **Hysteresis**: The `AnalogInput_hysteresis` value is passed as a 16-bit word and acts as a digital filter to prevent noise or oscillation.
- **Type Hash**: An attribute `eclipse4diac::core::TypeHash` is included but initialized with an empty string – it can be set later at runtime.
* * * * * * * * * *
## State Overview

Since this is a service interface function block (FB), its behavior is determined by the event logic and the underlying communication protocol. An internal state machine is not represented in the XML definition; however, the following phases typically exist:

- **OFF / UNINITIALIZED**: Before the first `INIT` event. No communication is active.
- **INIT** Phase: After receiving `INIT`, until `INITO` is sent. Slave configuration.
- **IDLE** (ready): After successful initialization. The FB can accept `REQ` events.
- **BUSY** (Request in progress): From `REQ` until the response arrives (followed by `CNF`).
- **INDICATION** state: `IND` is triggered when data arrives asynchronously, after which the function block returns to the IDLE state.

Error states (e.g., communication failure) are reported via `STATUS`.

* * * * * * * * * *
## Application Scenarios

- **4-20 mA Sensor Connection**: A pressure sensor, level sensor, or temperature sensor with a 4-20 mA output is connected to the DataPanel system. The function block reads the measured value cyclically or on demand.
- **Multi-channel acquisition**: Via different instances of the building block (with different `Input`With parameters, multiple analog channels can be operated in parallel.
- **Data Logger System**: Combined with a function block for data recording, the `IND` output can be used to log status changes or alarms.
- **Agricultural Control**: In agricultural technology (HR Agrartechnik GmbH), this allows for the recording of fluid levels, flow rates, or axle loads, for example.
* * * * * * * * * *
## Comparison with Similar Function Blocks

*

Compared to a general analog input function block (e.g., a function block for standardized fieldbuses like PROFIBUS or IO-Link), this block is distinguished by the following features:

- **Specific Hardware Assignment**: It is directly tailored to the "DataPanel::io::MI::AI" protocol.
- **Node Addressing**: The limitation to nodes 224–239 and the predefined constants from `MI::MI_xx` simplify configuration in fixed networks.
- **Event Model**: `IND` alongside `CNF` allows for both synchronous and asynchronous data acquisition – more flexible than a pure polling model.
- **Event Model**: `IND` alongside `CNF` enables both synchronous and asynchronous data acquisition – more flexible than a pure polling model.
- **Node Addressing**: - **Hysteresis Parameter**: Provides simple debouncing at the function block level, a feature not found in many generic function blocks.
* * * * * * * * * *
## Conclusion

The **DataPanel_MI_IW_4_20mA** function block offers a robust and compact solution for acquiring 4-20mA signals in a proprietary DataPanel system. The clear separation of initialization, request, and spontaneous indication, along with the integrated hysteresis, makes it suitable for practical use in agricultural technology. Its configurable node address and channel allow for flexible deployment and integration into existing automation networks.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
