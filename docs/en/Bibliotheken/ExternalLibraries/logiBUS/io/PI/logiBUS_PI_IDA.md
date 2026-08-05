# logiBUS_PI_IDA
![logiBUS_PI_IDA](./logiBUS_PI_IDA.svg)

* * * * * * * * * *
## Introduction
The **logiBUS_PI_IDA** is a composite function block (FB) for processing double-word input data (DWORD). It serves as an interface between a logiBUS fieldbus and the control logic. The FB enables parameterizable monitoring of pulse and time changes at a digital input. By configuring pulse delta, time delta, and a rate limit, the signaling behavior can be precisely tailored to the application. The block initializes the internal sub-block `logiBUS_PI_ID` and provides its results via a unidirectional adapter.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| INIT | EInit | Service Initialization – Parameterization and Start |
REQ | Event | Service Request – Triggers processing |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
INIT | EInit | Initialization Confirm – Confirms successful initialization |

### **Data Inputs**

| Name | Type | Initial Value | Comment |
|------|-----|-------------|-----------|
QI | BOOL | – | Event Input Qualifier (Enable/Disable) |
PARAMS | STRING | – | Service Parameters (e.g., bus address, channel configuration) |
Input | logiBUS::io::PI::logiBUS_PI_S | `Invalid` | Identifies the physical input (Input_I1..I8) |
| PulseDelta | DWORD | – | Number of pulses after which an indication (IND) is triggered |
| TimeDelta | DWORD | `250` | Time in ms after which a periodic indication (IND) is triggered |
| TimeRateLimit | DWORD | `100` | Minimum interval in ms between two indications (rate limiting) |

### **Data Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| QO | BOOL | Event Output Qualifier – Status of the last processing |
| STATUS | STRING | Service Status – Error or Diagnostic Message |

### **Adapter**

| Name | Type | Comment |
|------|-----|-----------|
| IN | adapter::types::unidirectional::AD | Output data of the function block – delivers the processed events and values to the application |

The adapter `IN` is connected to the events `IND` (indication) and `CNF` (confirmation), as well as the data value `D1` of the internal function block `logiBUS_PI_ID`.

## Functionality

The function block (FB) operates as a composite, delegating all initialization and processing logic to the internal FB `logiBUS_PI_ID`.

1. **Initialization (INIT):**

Upon arrival of `INIT`, the parameters `QI`, `PARAMS`, `Input`, `ImpulseDelta`, `TimeDelta`, and `TimeRateLimit` are forwarded to the internal FB. This FB configures the hardware input and starts monitoring. After successful initialization, `INITO` is output.

2. **Processing (REQ):**

An event `REQ` triggers a query of the input value. The internal function block checks whether the configured thresholds (pulse counter, time limit) have been reached or exceeded. If so, the events `IND` and/or `CNF` are sent to the downstream logic via the adapter `IN`.

3. **Reporting Behavior:**

- **Pulse-Dependent:** If `ImpulseDelta > 0` occurs, an internal pulse counter is incremented after each change in the input signal. When the counter reaches the value of `ImpulseDelta`, an indication (`IND`) is triggered and the counter is reset.

`` - **Time-dependent:** Additionally or alternatively, a periodic indication is generated after `TimeDelta` milliseconds.

- **Lock logic:** If `ImpulseDelta = 0` is set, `TimeDelta` must not be 0 (error prevention). If `TimeDelta = 0xFFFFFFFF` is set, cyclic processing is deactivated – only pure value changes are reported.
- **Rate limit:** `TimeRateLimit` prevents excessively frequent indications; it ensures that at least the specified time in milliseconds elapses between two consecutive `IND` events.

## Technical Features
- The function block (FB) internally uses the module `logiBUS_PI_ID`, which encapsulates the actual hardware connection and counting logic.
- If `ImpulseDelta = 0` is present, `TimeDelta > 0` must be set; otherwise, the behavior is undefined (see license information).
- A `TimeDelta` from `0xFFFFFFFF` disables the time-based indication – only pulse-driven or pure value changes are transmitted.
- The adapter `IN` provides the output data as a unidirectional data stream, which is further processed in the higher-level application.

If `ImpulseDelta = 0` is present, `TimeDelta > 0` must be set; otherwise, the behavior is undefined (see license information).

- A `TimeDelta` from `0xFFFFFFFF` disables the time-based indication – only pulse-driven or pure value changes are transmitted.
- The adapter `IN` provides the output data as a unidirectional data stream, which is further processed in the higher-level application. - The initial values (`Input`: `Invalid`, `TimeDelta`: `250`, `TimeRateLimit`: `100`) are sensibly preset to enable fast operation without additional configuration.

## State Overview

Since the FB is a composite and the state logic is completely encapsulated in the internal FB `logiBUS_PI_ID`, a general state description is given here:

- **IDLE** – After a reset or failed initialization. No processing.
- **INIT** – Initialization is in progress (waiting for hardware feedback).
- **RUN** – Normal operation: Monitoring of pulses and time, triggering of indications.
- **ERROR** – Error state (e.g., invalid parameters, hardware error). Signaled via `STATUS`.

Transitions are triggered by `INIT`, `REQ`, and internal errors. The internal function block (FB) likely uses an Execution Control Chart (ECC) to implement these states.

## Application Scenarios
- **Monitoring of Digital Inputs:** Connection of pushbuttons, switches, or limit switches, where both rapid pulse changes and regular status messages are required.
- **Pulse Counting:** E.g., detection of flow sensors or rotary encoders; the FB reports a measured value after each defined number of pulses.
- **Time-Controlled Queries:** In applications where the input value must be queried regularly (every ms), e.g., B. for long-term monitoring or safety testing.
- **Rate Limiting:** Prevents overloading of the bus communication during high-frequency signal changes.

## Comparison with Similar Function Blocks

| Function Block | Difference |
|----------|-------------|
| `logiBUS_PI` | Simpler input function block without pulse and time-delta filters; only raw value changes. |
| `logiBUS_PI_ID` | Predecessor without composite structure and without adapter interface; direct event outputs. |
| `logiBUS_PI_IDA` (this function block) | Additionally offers an **adapter** for flexible further processing and combines pulse, time, and rate logic in a composite. |

The `logiBUS_PI_IDA`This represents an extended and more modular variant, particularly suitable for complex automation projects with standardized interfaces.

## Conclusion

The **logiBUS_PI_IDA** is a powerful composite function block for the configurable acquisition of digital input signals via the logiBUS. By combining pulse and time delta measurements with rate limiting, it can be flexibly adapted to a wide variety of requirements. The encapsulation of the logic within the internal block and the adapter interface facilitate reuse and integration into higher-level control programs. The function block is ideal for applications requiring precise and configurable signal evaluation with minimal resource consumption.
