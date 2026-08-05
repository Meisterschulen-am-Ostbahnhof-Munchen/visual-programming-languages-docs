# AX_TO_ALR

![AX_TO_ALR](./AX_TO_ALR.svg)

* * * * * * * * * *

## Introduction

The function block **AX_TO_ALR** is used to convert a BOOL adapter signal (AX) into an LREAL adapter signal (ALR). Internally, it uses the IEC 61131 standard function `F_SEL` (Selection) to generate a discrete LREAL value from a Boolean input. The block is implemented as a composite function block and is suitable for the simple, adapter-based conversion of digital states into numerical values.

## Interface Structure

### **Event Inputs**

| Name | Data Type | Description |

|-------------|----------|--------------|

| `AX_IN.E1` | EVENT | Event from the connected AX adapter; triggers processing. |

### **Event Outputs**

| Label | Data Type | Description |

|-------------|-----------|--------------|

| `ALR_OUT.E1` | EVENT | Confirmation event after the converted value has been output to the ALR adapter. |

### **Data Inputs**

| Label | Data Type | Description |

|-------------|----------|--------------|

| `AX_IN.D1` | BOOL | Boolean value to be converted to an LREAL value. |

### **Data Outputs**

| Label | Data Type | Description |

|-------------|-----------|--------------|

| `ALR_OUT.D1` | LREAL | Conversion result: 0.0 for `FALSE`, 1.0 for `TRUE`. |

### **Adapters**

| Direction | Label | Type | Description |

|----------|-------------|-----|--------------|

| Socket (Input) | `AX_IN` | `adapter::types::unidirectional::AX` | Receives a BOOL signal via the unidirectional AX adapter. |

| Plug (Output) | `ALR_OUT` | `adapter::types::unidirectional::ALR` | Provides the converted LREAL signal via the unidirectional ALR adapter. |

## Functionality

The function block operates according to the following scheme:

1. An incoming event at `AX_IN.E1` triggers the internal processing.

2. The Boolean value of ``AX_IN.D1`` is passed to the gate input (G) of the embedded function ``F_SEL``.

3. Depending on the Boolean value, ``F_SEL`` selects one of two constant values:

- ``FALSE`` (G = 0) → Output of **0.0** (LREAL#0.0)

- ``TRUE`` (G = 1) → Output of **1.0** (LREAL#1.0)

4. The result is passed to ``ALR_OUT.D1``, and the acknowledgment event ``ALR_OUT.E1`` is simultaneously output.



``ALR_OUT.D1`` is passed to the gate input (G) of the embedded function ``ALR_OUT.E1``. The conversion is event-driven: Each incoming event causes exactly one conversion of the current BOOL value.

## Technical Features

- **Adapter Interface**: The function block uses only unidirectional adapters (socket/plug), allowing it to integrate seamlessly into adapter-based architectures.

- **Internal Use of F_SEL**: The IEC 61131 standard function guarantees deterministic and portable behavior.

- **Fixed Thresholds**: The output values are fixed at `0.0` and `1.0`. Adjusting these thresholds requires modifying the internal network.

- **Packaging**: The function block is packaged in `adapter::conversion::unidirectional`.

- **License**: The function block is available under the Eclipse Public License 2.0.


## State Overview

Since this is a composite function block (FB) without its own execution state, the state logic is derived from the event and data processing of the included `F_SEL` block. Two stable states exist:

- **Waiting for Event**: No event at `AX_IN.E1` – no output.

- **Processing Active**: An event is being processed: the Boolean value is read, converted into an LREAL value, and made available at the output; subsequently, the acknowledgment event is sent.

## Application Scenarios

- **Digital-to-Analog Conversion**: A digital sensor (e.g., switch, limit switch) provides a Boolean value that is to be further processed in the controller as an LREAL signal (0.0/1.0).

- **Adapter Integration**: Integration into existing systems that already use unidirectional AX and ALR adapters – e.g., in agricultural technology or industrial automation.

- **State Scaling**: Simplified conversion of on/off signals into numerical values for calculations or visualizations.

## Comparison with Similar Function Blocks

| Function Block | Input Type | Output Type | Special Feature |

|----------|-------------|-------------|--------------|

| `AX_TO_ALR` | BOOL (Adapter) | LREAL (Adapter) | Adapter-based, fixed values 0.0 / 1.0 |

| `BOOL_TO_REAL` | BOOL (direct) | REAL (direct) | Conventional IEC function block, values freely configurable |

| `SEL` / `F_SEL` | BOOL + 2x ANY | ANY | General selection without adapter, values configurable |

Compared to direct function blocks, `AX_TO_ALR` offers the advantage of clean adapter encapsulation and easy reuse in adapter-oriented projects.

## Conclusion

The function block `AX_TO_ALR` provides a compact and reliable solution for converting a Boolean adapter signal into an LREAL adapter value. By using the IEC standard function `F_SEL`, its behavior is deterministic and portable. It is particularly suitable for applications that require a clean separation of digital and analog signal paths via adapters.