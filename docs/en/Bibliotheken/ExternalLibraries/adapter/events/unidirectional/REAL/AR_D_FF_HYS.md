# AR_D_FF_HYS
![AR_D_FF_HYS](./AR_D_FF_HYS.svg)

* * * * * * * * * *
## Introduction
The function block **AR_D_FF_HYS** implements a data latch (D) flip-flop with hysteresis. It serves for the stable acquisition and transmission of an analog (real) value, with a hysteresis band suppressing unwanted fluctuations at the output. The block is designed for use in industrial signal processing.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |
|----------|-----|--------------|
| INIT | EInit | Initializes the block and sets the hysteresis band. |

### **Event Outputs**

| Event | Type | Description |
|----------|-----|--------------|
| INITO | EInit | Confirms successful initialization. |

### **Data Inputs**

| Name | Type | Description |
|------|-----|--------------|
| HYSTERESIS | REAL | Hysteresis band size. |

### **Data Outputs**

*(No direct data outputs; the latent value is output via adapter Q)*

### **Adapter**

| Name | Type | Direction | Description |
|-------------|-----|-----------|--------------|
| I | adapter::types::unidirectional::AR | Socket (Input) | Receives the value to be latched (trigger event on E1, data on D1). |
| Q | adapter::types::unidirectional::AR | Plug (Output) | Outputs the latched value (event on E1, data on D1). |

## Functionality

The function block internally contains a sub-FB `E_D_FF_ANY_HYS` from the library `logiBUS::signalprocessing::hysteresis`.

- On each rising edge at the event input `I.E1`, the current data value from `I.D1` is taken.

`` - The received value is only passed on to `Q.D1` if it differs from the last issued value by more than the configured hysteresis (`HYSTERESIS`).

- The event `I.E1` is synchronously forwarded as `Q.E1` to inform the receiver of a new value.
- Initialization (`INIT`) sets the hysteresis band and immediately confirms it with `INITO`. Changing `HYSTERESIS` during operation is not supported; the hysteresis is only applied during the INIT event.
- Initialization (`INIT`) sets the hysteresis band and immediately confirms it with `INITO`. Modifying `HYSTERESIS` during operation is not supported; the hysteresis is only applied during the INIT event.
-
## Technical Features
- **Adapter-Based Interface**: Both the input and output use the generic adapter `adapter::types::unidirectional::AR`, allowing the block to be flexibly integrated into existing adapter chains.
- **Hysteresis Function**: Suppresses noise and oscillations at threshold values, ensuring a clean, stable output.
- **EPL 2.0**: The block is licensed under the Eclipse Public License 2.0 and can be freely used and modified.
- **Internal Implementation**: The actual hysteresis logic is executed by a specialized sub-block (`E_D_FF_ANY_HYS`), improving maintainability and reusability.

## State Overview

The block has an implicit memory state for the last output value. Since this is a D flip-flop with hysteresis, three logical ranges can be distinguished:

- **Input ≥ (Output + Hysteresis/2)** → Output is set to the new input.
- **Input ≤ (Output − Hysteresis/2)** → Output is set to the new input.
- **Value within the hysteresis range** → Output remains unchanged (history).

There are no explicit state machines; the component operates purely event-driven.

## Application Scenarios
- **Signal Smoothing**: Removal of high-frequency noise from analog measured values.
- **Threshold Switch**: Defined on and off points for binary decisions (e.g., temperature control).
- **Edge Detection with Hysteresis**: Reliable detection of rising or falling edges of an analog signal.
- **Level Adjustment**: Stable tracking of an output value to a fluctuating input.

## Comparison with Similar Function Blocks

| Function Block | Feature |
|----------|-------------|
| **AR_D_FF** (without hysteresis) | Instantly adopts any new value; sensitive to noise. |
| **AR_D_FF_HYS** (this function block) | Uses a hysteresis band to suppress flicker. |
| **Schmitt Trigger** | Implements similar hysteresis, but usually for binary (Boolean) signals. This function block operates with analog (REAL) values. |

## Conclusion

The **AR_D_FF_HYS** is a robust, adapter-based function block for the reliable transmission of analog values with adjustable hysteresis. It is particularly suitable for applications where interference occurs on the signal line or where defined switching behavior is required. Its simple initialization and clear interface structure facilitate integration into automation systems.
