# AX_ASR_RF_TRIG

![AX_ASR_RF_TRIG](./AX_ASR_RF_TRIG.svg)

* * * * * * * * * *

## Introduction

The function block **AX_ASR_RF_TRIG** is used for bidirectional edge detection (rising and falling) of a Boolean input signal. It is designed as an adapter-based envelope of the IEC 61499 standard function block `E_RF_TRIG`. The signal to be monitored is read via two unidirectional adapters, and the result is provided as a set/reset output.

## Interface Structure

The function block has **no direct** event or data inputs/outputs. All communication takes place via two adapters.


### Event Inputs

- **none**

### Event Outputs

- **none**

### Data Inputs

- **none**

### Data Outputs

- **none**

### Adapters

| Adapter | Type | Direction | Description |

|---------|-----|----------|--------------|

| **QI** | `adapter::types::unidirectional::AX` | Socket | Input adapter – provides the Boolean value to be monitored (via channel `D1`) as well as an event (`E1`) for processing. |

| **Q** | `adapter::types::unidirectional::ASR` | Plug | Output adapter – signals the detected edge state via the events `SET` (rising edge) and `RESET` (falling edge). |

## Functionality

1. An event received at socket **QI** (via `QI.E1`) simultaneously transmits the Boolean value `QI.D1` to the internal `E_RF_TRIG` module.

2. The integrated `E_RF_TRIG` detects a **rising edge** (transition from FALSE to TRUE) and a **falling edge** (transition from TRUE to FALSE).

3. On a rising edge, the internal function block (FB) generates the event `ER`, which is output via the **Q** plug as `Q.SET`.

4. On a falling edge, the internal FB generates the event `EF`, which is output as `Q.RESET`.

Thus, the input signal is converted into a set/reset signal without the user having to deal with the internal event processing.

## Technical Features

- **Pure Adapter Interface:** The FB has no direct inputs/outputs in the FB type interface, which enables loose coupling and reusability in different adapter networks.

- **Use of the standard function block `E_RF_TRIG`:** Edge detection is based on the proven IEC 61499 implementation, which reliably detects both rising and falling edges.

- **No state storage outside the internal function block:** All logic is implemented by the embedded `E_RF_TRIG`; the external function block serves solely as encapsulation and adapter adaptation.

## State Overview

The function block does **not have its own explicit state machine**. The internal `E_RF_TRIG` operates according to the following implicit state logic:

| last value | current value | triggered event |

|--------------|----------------|----------------------|

| FALSE | TRUE | rising edge (SET) |

| TRUE | FALSE | Falling Edge (RESET) |

| else | – | no event |

State storage occurs exclusively within the internal function block.

## Application Scenarios

- **Button Press Detection:** Monitoring of a button signal; `SET` when pressed, `RESET` when released.

- **Signal Edge Evaluation in Controllers:** Detection of limit exceedances or pulse beginnings/ends.

- **Adapter-Based Sensor Integration:** Integration of sensors with Boolean outputs into an adapter network, e.g., via the AX/ASR adapter family.

## Comparison with Similar Function Blocks

| Function Block | Edge Detection | Output Signal | Interface |

|----------|------------------|----------------|---------------|

| `E_RF_TRIG` | Ascending + Falling | Separate Event Outputs | Direct Events |

| `E_TRIG` | Ascending only | One Event | Direct Events |

| `E_F_TRIG` | Falling only | One Event | Direct Events |

| **AX_ASR_RF_TRIG** | Ascending + Falling | Set/Reset Events via Adapter | Pure Adapters |

Unlike pure event blocks, this function block offers an adapter interface, enabling simpler connections in hierarchical or typed adapter networks.



## Conclusion

The `AX_ASR_RF_TRIG` is a compact, adapter-based edge detector for Boolean signals. It simplifies the use of the standard `E_RF_TRIG` module in adapter-based architectures and directly converts the detected edges into a set/reset signal. Its loose coupling makes it particularly suitable for modular, reusable control applications.