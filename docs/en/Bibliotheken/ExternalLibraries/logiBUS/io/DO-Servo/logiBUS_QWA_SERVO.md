# logiBUS_QWA_SERVO

![logiBUS_QWA_SERVO](./logiBUS_QWA_SERVO.svg)

* * * * * * * * * *
## Introduction

The **logiBUS_QWA_SERVO** is a composite function block (CFB) for outputting servo control words via a logiBUS. It encapsulates the initialization, parameterization, and output based on an internal function block (`logiBUS_QW_SERVO`) and provides a standardized interface. Developed under the Eclipse Public License 2.0 (Copyright 2026 HR Agrartechnik GmbH).
*Comment from the XML: “Composite FB for servo word output data”.*

## Interface Structure

### **Event Inputs**

| Event | Type | With Variables | Description |
|----------|-------|------------------------|-------------------------|
| `INIT` | EInit | `QI`, `PARAMS`, `Output` | Service Initialization |

### **Event Outputs**

| Event | Type | With Variables | Description |
|----------|-------|----------------|---------------------------------------|
| `INITO` | EInit | `QO`, `STATUS` | Initialization Confirmation |
| `CNF` | Event | `QO`, `STATUS` | Confirmation of a Requested Action|

### **Data Inputs**

| Name | Type | Initial Value | Description |
|----------|--------------|-------------|---------------------------------------------------|
| `QI` | `BOOL` | – | Event Input Qualifier |
| `PARAMS` | `STRING` | – | Service Parameter (e.g., Bus Configuration) |
| `Output` | `logiBUS::io::DQ::logiBUS_DO_S` | `Invalid` | Identifies the output (`Output_Q1` … `Output_Q8`)|

### **Data Outputs**

| Name | Type | Description |
|----------|----------|---------------------------------|
| `QO` | `BOOL` | Event Output Qualifier |
| `STATUS` | `STRING` | Status Message (Error, OK, etc.)|

### **Adapters**

| Adapter | Type | Direction | Description |
|---------|---------------------------------------|----------|---------------------------------------|
| `OUT` | `adapter::types::unidirectional::AW` | Socket | Output data for the resource (word output)|

## Functionality

The function block operates as a composite:

1. **Initialization** (`INIT`):
- Qualifier `QI`, parameter string `PARAMS`, and the desired output (`Output`) are passed.
- The internal function block `logiBUS_QW_SERVO` is initialized; after successful initialization, `INITO` is sent.
2. **Execution** (via adapter `OUT`):
- The event `OUT.E1` is received by the adapter and forwarded to the internal function block (FB) as `REQ`.
- Simultaneously, the data is transferred to the internal FB (`QX.OUT`) via `OUT.D1`.
3. **Feedback**:
- The internal FB signals completion via `CNF`, which is forwarded to the external output `CNF`.
- Status and qualifier are output via `QO` and `STATUS`.

The actual control of the servo hardware is handled via the adapter `OUT`, which is connected to the resource.

## Technical Features

- **Composite Design**: Encapsulates the complex initialization and execution control of the servo word output.
- **Adapter Interface**: The unidirectional adapter `AW` enables flexible connection to various physical output channels.
- **Output Selection**: The input `Output` allows selection between eight different outputs (`Q1`…`Q8`); the initial value `Invalid` prevents unintended actions before configuration.
- **Error Handling**: Status information is provided via `STATUS`; event sequences guarantee correct flow control.
- **License**: Eclipse Public License 2.0 (EPL-2.0) – free use and further development under the license terms.

## State Overview

The function block (FB) does not have an explicitly modeled state machine; however, the following implicit state logic results from the event sequences:

| State | Trigger | Response |
|---------------|-------------------------|----------------------------------------------|
| **Idle** | – | Waiting for `INIT` |
| **Initialize**| Received `INIT` | Internal FB is started |
| **Ready** | `INITO` sent | Ready for requests via the adapter |
| **Busy** | `OUT.E1` received | Action is being executed (`REQ` is running) |
| **Done** | `CNF` sent | Action completed, returning to **Ready** |
| **Error** | Error during initialization or action | `STATUS` contains error description; reinitialization may be necessary |

## Application Scenarios

- **Agricultural Machinery**: Control of servo drives (e.g., for flaps, valves, actuators) via a logiBUS fieldbus.

**Done** | `CNF` | Action completed, returning to **Ready** |
**Error** | Error during initialization or action | `STATUS` contains error description; reinitialization may be necessary |

- **Agricultural Machinery**: Control of servo drives (e.g., for flaps, valves, actuators) via a logiBUS fieldbus.

** - **Modular Output Block**: Used in distributed control systems where multiple servo outputs need to be parameterized depending on the machine configuration.

- **Parameterizable Configuration**: Bus address, protocol settings, and timing behavior can be defined via `PARAMS`.

## Comparison with Similar Blocks

- **logiBUS_QW_SERVO** (internal FB): Implements direct word output and bus communication, while `logiBUS_QWA_SERVO` offers a higher level of abstraction with consolidated inputs/outputs.
- **logiBUS_DO_S Family**: Other blocks in this family address individual discrete outputs (e.g., logiBUS_DO) – the FB described here is specifically designed for servo word data and multiple simultaneous outputs.
- **Generic Word Output Function Blocks**: Compared to standardized `W`-type function blocks, this block offers an interface adapted to servo applications (e.g., `logiBUS_DO_S`-type).

## Conclusion

The `logiBUS_QWA_SERVO` is a well-structured composite function block that simplifies the control of servo word outputs on a logiBUS. By separating initialization, execution, and error feedback, and using an adapter for the hardware interface, it is ideally suited for modular automation solutions in agricultural technology and similar industries. Licensing under EPL-2.0 allows for unrestricted use and customization.
