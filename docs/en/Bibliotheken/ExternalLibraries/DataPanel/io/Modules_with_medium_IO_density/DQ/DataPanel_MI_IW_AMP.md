# DataPanel_MI_IW_AMP

![DataPanel_MI_IW_AMP](./DataPanel_MI_IW_AMP.svg)

* * * * * * * * * *
## Introduction

The DataPanel_MI_IW_AMP function block is an input interface function block (Service Interface Function Block) for acquiring the current feedback (amperage) of a single channel. It serves to integrate current measurements into the 4diac IDE and enables communication with a higher-level controller or a data panel. The block initializes the hardware-level communication and returns the current measurement value as a WORD upon each request.
## Interface Structure

### **Event Inputs**

- `INIT (EInit)` – Service initialization. Triggered to configure the function block and establish the connection to the hardware. This event transfers the parameters QI, PARAMS, u8SAMember, Input, and AnalogInput_hysteresis.

- `REQ (Event)` – Service request. Triggers a new measurement query. The function block responds with the CNF event and provides the current amperage value on the IN output.

### **Event Outputs**

- `INITO (EInit)` – Initialization confirmation. Sent after successful initialization. Outputs the QO and STATUS status.
- `CNF (Event)` – Service request confirmation. Sent in response to REQ and contains the current measurement value IN as well as the status information QO and STATUS.
- `IND (Event)` – Resource indication. Triggered by asynchronous events from the hardware (e.g., spontaneous value changes). Also provides the current measurement value IN.

### **Data Inputs**

- `QI (BOOL)` – Input Qualifier. Controls whether the FB is active (TRUE) or not (FALSE).
- `PARAMS (STRING)` – Service Parameter. Contains configuration data for initialization, e.g., bus interface or addressing.
- `u8SAMember (USINT)` – Node SA (Source Address) in the range 224..239. Defines the unique address of the connected device. Initial value: `MI::MI_00`.
- `Input (DataPanel_MI_DO_S)` – Identifies the digital output whose current is to be measured (e.g., DigitalOutput_1A..8B). Initial value: `Invalid`.
- `AnalogInput_hysteresis (WORD)` – Hysteresis for the analog input. Can be used to prevent edge detection during small fluctuations.

### **Data Outputs**

- `QO (BOOL)` – Output qualifier. Indicates whether the function block is operating correctly (TRUE) or if an error has occurred (FALSE).
- `STATUS (STRING)` – Service status. Contains error messages or information about the operating status.
- `IN (WORD)` – Measured current value in units of mA or 0.1A (depending on the configuration). Provides the current amperage value of the selected channel.

### **Adapters**

No adapters defined.

## Functionality

The function block acts as a service interface between the application and the hardware level. When `INIT` is triggered, the configuration parameters (address, channel assignment, hysteresis) are passed to the hardware. After successful initialization, `INITO` is sent. A `REQ` event triggers an immediate query of the current measurement value, which is provided on the output `IN` and acknowledged with `CNF`. Additionally, the hardware can generate a `IND` event upon changes to asynchronously inform the application.

`IND`` The values of `QI` and `QO` control the activity state: The function block (FB) can only deliver data if `QI`=TRUE and `QO`=TRUE. In case of an error, `QO` is set to FALSE and an error message is stored in `STATUS`.

## Technical Features

- The FB is designed as a generic service interface block and requires a hardware-dependent implementation of the service functions.
- Addressing via `u8SAMember` follows a predefined set of constants (e.g., `MI::MI_00` … `MI::MI_15`), which allows for easy configuration of multiple channels.
- The output type `DataPanel_MI_DO_S` is used to select a specific digital output; the function block will only operate correctly if this value is valid (not `Invalid`).
- Hysteresis (`AnalogInput_hysteresis`) can be used to suppress measurement noise and avoid unnecessary events.
- The amperage output is a WORD, depending on the configuration, in mA (e.g., 0–65535 mA) or in 0.1 A increments.

## State Overview

The function block typically goes through the following states:

1. **IDLE** – Idle state after startup, waiting for INIT.
2. **INIT** – Initialization is performed; after success, transition to OPERATIONAL, then INITO.
3. **OPERATIONAL** – Ready for operation; REQ events are processed, measured values are delivered via CNF; asynchronous IND is possible.
4. **ERROR** – Error state (e.g., communication error, invalid parameters); QO = FALSE, STATUS contains error text; reset only by re-INIT.

A detailed state machine is embedded in the service implementation.

## Application Scenarios

- **Current monitoring of individual outputs** in a machine controller, e.g., for detecting load changes or defects.
- **Integration of analog input modules** of a data panel to measure the current consumption per channel.
- **Parameterization via INIT** enables flexible use in various hardware configurations.

## Comparison with Similar Function Blocks

Compared to a purely digital input function block, this block offers analog measured value feedback (amperage), which provides more information about the load state. Similar modules for voltage or temperature measurement use a comparable interface scheme (INIT/REQ/IND) with other physical units. The advantage of `DataPanel_MI_IW_AMP` lies in its specific optimization for current measurement and its integration into the DataPanel family.

## Conclusion

The `DataPanel_MI_IW_AMP` function block provides a standardized and flexible interface for acquiring current values in automation systems. Its clearly defined events and parameters allow for easy integration into 4diac projects and offer both synchronous and asynchronous notifications of measured value changes. Detailed configuration via address, channel, and hysteresis enables adaptable use in diverse hardware environments.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
