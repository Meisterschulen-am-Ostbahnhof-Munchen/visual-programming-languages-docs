# logiBUS_IDA

![logiBUS_IDA](./logiBUS_IDA.svg)

* * * * * * * * * *
## Introduction

The **logiBUS_IDA** is a composite function block (CFB) for digital double-word input processing. It encapsulates an internal **logiBUS_ID** block and provides a uniform interface for initialization, parameterization, and event-driven data querying. The block is designed for use in logiBUS-based automation systems and supports the selection of an input channel as well as the configuration of the repeat event.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |
|----------|-------|---------------|
| INIT | EInit | Service initialization; expects valid parameters (QI, PARAMS, Input, InputEvent) |
| REQ | Event | Service request; triggers a new data query at the internal function block |

### **Event Outputs**

| Event | Type | Description |
|----------|-------|--------------|
| INITO | EInit | Initialization confirmation; returns the status (QO, STATUS) |

### **Data Inputs**

| Variable | Type | Description |
|----------------|-----------------------------|--------------|
| QI | BOOL | Qualifier for the event input; controls the execution |
| PARAMS | STRING | Service parameter (e.g., configuration string) |
| Input | logiBUS_DI_S | Selection of the digital input channel (I1…I8); Default value: *Invalid* |
| InputEvent | logiBUS_DI_Events_S | Selection of the event type (currently only *REPEAT* supported); Default value: *Invalid* |

### **Data Outputs**

| Variable | Type | Description |
|---------------|--------|--------------|
| QO | BOOL | Qualifier of the output event |
| STATUS | STRING | Service status (e.g., error messages or operating state) |

### **Adapters**

| Adapter | Type | Description |
|---------|------------------------------|--------------|
| IN | adapter::types::unidirectional::AD | Unidirectional input adapter for receiving digital double-word data from the resource |

## Functionality

The **logiBUS_IDA** is implemented as a composite block that encapsulates a single **logiBUS_ID** function block.

Initialization occurs via the **INIT** event. The parameters *QI*, *PARAMS*, *Input*, and *InputEvent* are passed to the inner block. The inner block then configures the selected digital input channel and prepares for data acquisition. After successful initialization, **INITO** is output with the values *QO* and *STATUS*.

A cyclic or one-time read operation is triggered via the **REQ** event. The internal block reads the current value of the configured input (8-bit/double word) via the **IN** adapter and makes the result available internally for further processing. The actual data values are not directly used as output variables of the **logiBUS_IDA**; They are available exclusively via the **IN** adapter at the output of the internal function block (see FBNetwork connections: DI.IN → IN.D1).

## Technical Features

- **Composite Architecture**: Encapsulates complex logic in a reusable function block.
- **Event-driven Processing**: Separation of initialization (INIT) and operational request (REQ).
- **Adapter-Based Input/Output**: Digital double-word information is transmitted via a unidirectional adapter, which keeps the coupling to the resource flexible.
- **Configurable Parameters**: The input channel (I1…I8) and the event behavior (e.g., REPEAT) can be set at runtime.
- **Standard-Compliant IEC 61499-2**: The function block is modeled according to the standard and uses type safety through predefined structures (logiBUS_DI_S and logiBUS_DI_Events_S).

## State Overview

The function block goes through the following main states:

1. **Initialization (INIT)**
- Entry: Event **INIT** is activated.
- Action: Internal function block is parameterized and started.
- Output: **INITO** with QO/STATUS.
2. **Operation (REQ)**
- Entry: Event **REQ** is activated.
- Action: Data query at the internal function block; value is provided via adapter **IN**.
- Cyclic repetition is possible if *InputEvent* is set to *REPEAT*.

Error states (e.g., invalid parameters or connection problems) are signaled via **STATUS**.

## Application Scenarios

- **Digital Multiple Input in Agricultural Technology**: Acquisition of up to 8 digital sensors (e.g., limit switches, proximity switches) and summarization as a double word.
- **Fieldbus Connection**: Use in logiBUS networks for decentralized I/O acquisition.
- **Configurable Monitoring**: Configuration of the sampling behavior (event type) according to the controller's requirements.
- **Extended Diagnostics**: The STATUS output allows feedback of errors or operating states to the higher-level controller.

## Comparison with Similar Function Blocks

Compared to a simple **logiBUS_DI**, the **logiBUS_IDA** offers an extended interface with explicit initialization (INIT) and event-driven requests (REQ). While a pure **logiBUS_ID** function block directly delivers the raw data via adapters, the **IDA** integrates the configuration of the channel and event behavior in a compact block. Similar composite function blocks from other fieldbus systems (e.g., CANopen, PROFIBUS) often implement comparable functionalities close to the processor, while the **logiBUS_IDA** is specifically tailored to the logiBUS protocol environment.

## Conclusion

The **logiBUS_IDA** is a flexible composite function block for digital double-word input processing in IEC 61499 environments. It simplifies commissioning through its clear interface with initialization and request events and enables channel- and event-configured data acquisition. Thanks to adapter-based data transfer, it can be seamlessly integrated into existing logiBUS resources. The block is particularly suitable for applications requiring reliable initialization and repeated, parameterizable queries of digital inputs.
