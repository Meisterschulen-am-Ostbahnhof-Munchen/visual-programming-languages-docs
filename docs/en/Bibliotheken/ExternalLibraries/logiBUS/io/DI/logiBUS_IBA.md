# logiBUS_IBA

![logiBUS_IBA](./logiBUS_IBA.svg)

* * * * * * * * * *
## Introduction

The **logiBUS_IBA** function block is a composite block for processing byte input data via the logiBUS protocol. It encapsulates the initialization, configuration, and event control of a logiBUS input block and provides the data via an adapter. The block is designed for use in agricultural control systems.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |
|----------|-----|---------------|
| INIT | EInit | Service initialization; takes over the configuration parameters (QI, PARAMS, Input, InputEvent) |
| REQ | Event | Service request to execute a function (dependent on QI) |

### **Event Outputs**

| Event | Type | Description |
|----------|-----|--------------|
| INITO | EInit | Initialization confirmation; signals successful or failed initialization (QO, STATUS) |

### **Data Inputs**

| Variable | Type | Description |
|----------|-----|--------------|
| QI | BOOL | Qualifier for event inputs; controls the activation of event processing |
| PARAMS | STRING | Service parameter (e.g., configuration data for the logiBUS driver) |
| Input | logiBUS::io::DI::logiBUS_DI_S | Selection of the physical input (e.g., Input_I1..I8); Default value: `logiBUS_DI::Invalid` |
| InputEvent | logiBUS::io::DI::logiBUS_DI_Events_S | Selection of the event type (currently only `REPEAT` is supported); Default value: `logiBUS_DI_Events::Invalid` |

### **Data Outputs**

| Variable | Type | Description |
|----------|-----|--------------|
| QO | BOOL | Qualifier for event outputs; indicates the success of the operation |
| STATUS | STRING | Status message (e.g., error or success message) |

### **Adapters**

| Adapter | Type | Description |
|---------|-----|--------------|
| IN | adapter::types::unidirectional::AB | Unidirectional adapter for providing input data to the higher-level resource |

## Functionality

The **logiBUS_IBA** function block works internally with an instance of the **logiBUS_IB** function block (from the `logiBUS::io::DI` library). The event and data paths are linked as follows:

- During the **INIT** event, the inputs `QI`, `PARAMS`, `Input`, and `InputEvent` are forwarded to the corresponding initialization of the internal function block. After initialization is complete, the output event **INITO** is set, and the outputs `QO` and `STATUS` are updated.
- The **REQ** event triggers the internal function block for processing a service request. The processing depends on the current state and the input parameters.
- Data read from the logiBUS input is transferred to the output adapter **IN** via the adapter connection (`IN.E1` and `IN.D1`). The adapter then provides the data to a higher-level function block or resource.
- Error and status signals are reported back via `QO` and `STATUS`.

## Technical Features

- **Composite FB:** This function block encapsulates the complex initialization and data provision of a logiBUS input in a single interface.
- **Adapter-Based Data Output:** Input data is not output via separate data outputs, but rather via a **unidirectional adapter** (type `AB`). This allows for flexible coupling with other function blocks.
- **Configurable Inputs:** The physical input (I1..I8) and the event behavior (e.g., repetition) can be selected using the parameters `Input` and `InputEvent`.
- **License and Origin:** This function block is provided under the **Eclipse Public License 2.0** and is optimized for use in agricultural technology.

## State Overview

This function block does not have an explicitly displayed state machine, as it is a composite function block. The internal behavior is determined by the included function block **logiBUS_IB**, which typically implements the following states:

- **IDLE** – Waiting for INIT or REQ
- **INIT** – Initialization with parameters
- **RUN** – Ready for operation, data processing active
- **ERROR** – Error state (status message via STATUS)

## Application Scenarios

- **Agricultural Control Systems:** Acquisition of digital input signals (e.g., sensors, switches) via logiBUS and forwarding to a controller.
- **Input Modules in Fieldbus Systems:** The function block serves as a standardized interface for logiBUS inputs in IEC 61499-2 applications.
- **Prototypes and Test Setups:** Thanks to its configurability, the function block can be quickly adapted to various input configurations.

## Comparison with Similar Function Blocks

- **logiBUS_IB:** The internal function block is a pure Basic Function Block; **logiBUS_IBA** adds an adapter output and simplified event control.
- **SYNC/D_SYNC:** These function blocks from the Sync library offer similar input configuration but without specific logiBUS protocol support.
- **Generic Input Adapter:** Compared to generic adapters, **logiBUS_IBA** offers a predefined logiBUS configuration, reducing development effort.

## Conclusion

The **logiBUS_IBA** is a practical composite function block for integrating logiBUS inputs into IEC 61499-based automation systems. By combining initialization, parameter configuration, and adapter-based data output, it creates a clean and reusable interface. It is particularly suitable for agricultural applications that rely on the logiBUS protocol.
