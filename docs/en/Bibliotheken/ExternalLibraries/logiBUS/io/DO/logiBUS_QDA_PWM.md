# logiBUS_QDA_PWM

![logiBUS_QDA_PWM](./logiBUS_QDA_PWM.svg)

* * * * * * * * * *
## Introduction

The **logiBUS_QDA_PWM** function block is a composite block for controlling a PWM (Double Word) output via a logiBUS system. It encapsulates the initialization and triggering of an internal PWM output block and provides an adapter interface for receiving commands (events and data) from external sources. The block was developed for use in agricultural technology and is licensed under EPL 2.0.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment |
|----------|-----|-----------|
| INIT | EInit | Service Initialization |
| *no further event input* | | *All triggers are handled via the adapter* |

### **Event Outputs**

| Event | Type | Comment |
|----------|-----|-----------|
| INITO | EInit | Initialization Acknowledgement |
| CNF | Event | Acknowledgement of a requested service |

### **Data Inputs**

| Variable | Type | Comment |
|----------|-----|-----------|
| QI | BOOL | Input Qualifier (Enable Initialization) |
| PARAMS | STRING | Service Parameter (e.g., Addressing, Configuration) |
| Output | logiBUS::io::DQ::logiBUS_DO_S | Output Identification (e.g., Output_Q1..Q8); Initial Value: *Invalid* |

### **Data Outputs**

| Variable | Type | Comment |
|----------|-----|-----------|
| QO | BOOL | Output Qualifier (Initialization Status) |
| STATUS | STRING | Service Status (Failure/Success Message) |

### **Adapters**

| Type | Name | Direction | Comment |
|-----|------|----------|-----------|
| adapter::types::unidirectional::AD | OUT | Socket | Receives trigger event (E1) and output data (D1) from the resource |

## Functionality

The function block is implemented as a composite and contains an internal instance of the function block `logiBUS::io::DQ::logiBUS_QD_PWM` (referred to here as *QX*). The logic can be described as follows:

1. **Initialization:**

An INIT event at the input triggers the initialization of the internal function block. The data inputs *QI*, *PARAMS*, and *Output* are then forwarded to the internal function block. After successful initialization, the event *INITO* is output, along with the output data *QO* and *STATUS*.

2. **Triggering via Adapter:**

The adapter *OUT* receives an external event *E1* and a data value *D1*. The event is forwarded to the internal function block as a *REQ* (Request), and the data *D1* as an *OUT* value. The internal function block processes this request and acknowledges it with the event *CNF*, which is then output to the external system via the *CNF* output. The associated output data *QO* and *STATUS* are updated.

This function block allows for a clean separation of initialization and cyclic output: Configuration is performed once via INIT, while the actual PWM output is triggered by the adapter.

## Technical Features

- **Composite Function Block:** The function block encapsulates all the logic of a PWM output function block and provides a standardized adapter interface for data exchange with the resource.
- **Double-Word Output:** The name indicates a 32-bit data width, which is transmitted via the adapter data element *D1*.
- **Initialization Parameters:** Flexible configuration data, necessary for addressing or parameterizing the logiBUS module, can be passed via *PARAMS* (STRING).

**Initialization Parameters:** Flexible configuration data, necessary for addressing or parameterizing the logiBUS module, can be passed via *PARAMS* (STRING). - **Error Handling:** The *STATUS* output provides a textual description of the service status (e.g., error messages for invalid configurations).

## State Overview

Since this is a composite function block without its own state machine, the state is defined by the internal function block *logiBUS_QD_PWM*. Typical states are:

- **IDLE:** Waiting for initialization or a trigger.
- **INITIALIZING:** During initialization (INIT received, INITO not yet sent).
- **OPERATIONAL:** Ready for cyclic triggers (via adapter).
- **ERROR:** Error state, indicated by *QO = FALSE* or *STATUS* with an error message.

The internal function block switches between these states depending on the events and data.

**IDLE:** Waiting for initialization or a trigger.

**INITIALIZING:** During initialization (INIT received, INITO not yet sent).

**OPERATIONAL:** Ready for cyclic triggers (via adapter).

**ERROR:** Error state, indicated by *QO = FALSE* or *STATUS* with an error message.

**The internal function block switches between these states depending on the events and data.**
## Application Scenarios

- **Agricultural Machinery:** Control of PWM-driven actuators (e.g., hydraulic valves, engine speed) via a logiBUS network.
- **Automation Systems:** Output of analog or pulse-width modulated signals with 32-bit resolution, controlled by a higher-level controller.
- **Remote Maintenance and Configuration:** The adapter allows new PWM values to be sent from a higher-level resource (e.g., HMI or PLC) without repeating the initialization process.

## Comparison with Similar Function Blocks

| Function Block | Type | Special Feature |
|----------|-----|---------------|
| logiBUS_QD_PWM | Composite/Basic | Directly controllable via INIT, REQ, CNF; without an adapter interface. |
| **logiBUS_QDA_PWM** | Composite | Like logiBUS_QD_PWM, but with an adapter for external triggering and data supply. |
| logiBUS_DO (simple) | Basic | Simple digital output, no PWM function. |

The function block described here offers greater flexibility, as the actual output via the adapter can occur asynchronously from initialization. A disadvantage is the dependence on the correct provision of the adapter signals.

## Conclusion

The **logiBUS_QDA_PWM** function block is a practical encapsulation of a PWM output for logiBUS. By combining INIT-based configuration and adapter-based triggering, it is particularly suitable for applications requiring one-time parameterization followed by cyclic or event-driven output. The use of standardized types and the clear separation of interfaces facilitate integration into IEC 61499-based control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 The PWM signal & infographic on ms-muc-docs.de](https://www.ms-muc-docs.de/automatisierung/das-pwm-signal-die-kunst-spannung-zu-zerhacken/das-pwm-signal-die-kunst-spannung-zu-zerhacken-website/)
