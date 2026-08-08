# FB_CTU_UDINT
<img width="1411" height="277" alt="FB_CTU_UDINT" src="https://github.com/user-attachments/assets/f36dc7f5-bd23-4af7-8a8a-fc038435ca79" />
* * * * * * * * * *
The function block `FB_CTU_UDINT` is an up counter for the data type `UDINT` (unsigned double integer). It increments with each event `REQ` as long as the input `CU` is active, and can be reset via the input `R`. The counter compares the current counter value with a predefined setpoint (`PV`) and outputs a signal via the output `Q` when this setpoint is reached or exceeded.
![FB_CTU_UDINT](FB_CTU_UDINT.svg)


- **REQ**: Starts the execution of the function block. It is linked to the data inputs `CU` and `R`.

- **CNF**: Confirms the execution of the function block. It is linked to the data outputs `Q` and `CV`.

- **CU** (`BOOL`): Increment signal. The counter value is incremented on `TRUE`.

- **PV** (`UDINT`): Preset value against which the current counter reading is compared.

- **Q** (`BOOL`): Signal generated when the counter reading (`CV`) reaches or exceeds the preset value (`PV`).
- **CV** (`UDINT`): Current counter reading.

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
## Functionality
The function block performs the following steps on each `REQ` event:

1. If `R` is active (`TRUE`), the counter value (`CV`) is reset to `0`.

2. If `CU` is active (`TRUE`) and the counter value (`CV`) is less than the maximum value (`4294967295`), the counter value is incremented by `1`.

3. The output `Q` is set to `TRUE` when the counter reading (`CV`) reaches or exceeds the target value (`PV`).

- The counter reading (`CV`) is of type `UDINT` and can take values between `0` and `4294967295`.
- The function block is deterministic and performs the counting operation on every `REQ` event.

The function block has no internal states other than the current counter reading (`CV`). The logic is re-evaluated with each `REQ` event.

- Counting events in control applications (e.g., production counters).
- Monitoring processes where a specific number of steps must be completed.
- As part of a larger control logic that reacts to counter readings.

- Compared to other counters (e.g., `FB_CTU_INT`), this function block uses the `UDINT` data type, which allows for a larger range of values.
- Similar function blocks might offer additional features such as counting down or combined counting up/down.

The `FB_CTU_UDINT` is a simple and efficient up counter for applications that require a large range of values. Its clear interface and deterministic functionality make it a reliable component in control applications.
## Technical Features
## State Overview
## Application Scenarios
## ⚖️ Vergleich mit ähnlichen Bausteinen
## Conclusion