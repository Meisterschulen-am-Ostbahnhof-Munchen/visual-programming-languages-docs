# FIELDBUS_WORD_TO_SIGNAL_SCALED
![FIELDBUS_WORD_TO_SIGNAL_SCALED](./FIELDBUS_WORD_TO_SIGNAL_SCALED.svg)
* * * * * * * * * *
## Introduction
The function block **FIELDBUS_WORD_TO_SIGNAL_SCALED** is used to convert a digital fieldbus raw value (16-bit WORD) into a scaled physical signal value (REAL). A valid output is only provided if the incoming value is recognized as a valid signal. The block checks the validity against a predefined constant (`VALID_SIGNAL_W`) and can reliably suppress unsafe or "unavailable" values.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|-------------|

| `INIT` | Initialization request; sets the scaling factors (`SCALE`, `OFFSET`). |

| `REQ` | Normal processing request; evaluates the current input `IN`. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| `INITO` | Initialization confirmation. |

| `CNF` | Processing confirmation; signals that outputs `OUT` and `VALID` have been updated. |

### **Data Inputs**

| Name | Data Type | Default Value | Description |

|---------|----------|-----------------|-------------|

| `IN` | WORD | `NOT_AVAILABLE_WM` | Raw value from the fieldbus (e.g., 0…65535). The constant `NOT_AVAILABLE_WM` indicates an invalid starting value. |

| `SCALE` | REAL | `1.0` | Scaling factor (multiplied by the read value). |

| `OFFSET` | DINT | `0` | Integer offset added after scaling (converted to REAL). |

### **Data Outputs**

| Name | Data Type | Default Value | Description |

|---------|----------|-------------|-------------|

| `OUT` | REAL | `0.0` | Scaled signal value. Valid only if `VALID = TRUE`. |

| `VALID` | BOOL | `FALSE` | Validation flag – `TRUE`, if the incoming raw value is recognized as a valid signal. |

### **Adapter**
No adapters available.

## Functionality
The module operates in a state-controlled manner:

1. **INIT State**:

After the `INIT` event occurs, the initialization algorithm (empty) is executed and the `INITO` event is output. The scaling factors are then applied to the inputs `SCALE` and `OFFSET` (the values are already present at the inputs).

2. **REQ State** (Main Logic):

For each `REQ` event, the following algorithm is executed:

- The incoming `IN` (WORD) is first converted to `UINT`.
- If this value is **less than or equal to** the threshold defined in the global constant `VALID_SIGNAL_W` (also as WORD/UINT), the signal is considered **valid**.
- If valid:

`OUT = UINT_TO_REAL(IN) * SCALE + DINT_TO_REAL(OFFSET)`

`VALID = TRUE`

- If invalid:

`OUT = 0.0`

`VALID = FALSE`

- Subsequently, the `CNF` event is triggered, which accompanies the updated outputs `OUT` and `VALID`.

The comparison value `VALID_SIGNAL_W` and the default input value `NOT_AVAILABLE_WM` are imported as constants in the namespace `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`.

## Technical Features
- **Use of External Constants**: The validity threshold (`VALID_SIGNAL_W`) and the "Not Available" marker (`NOT_AVAILABLE_WM`) are retrieved from a global library. This enables consistent signal definition across multiple FB instances.
- **Scaling with REAL and DINT**: The offset is defined as `DINT`, but is converted to a floating-point number by `DINT_TO_REAL`. This can lead to minor rounding errors with large values, but is usually negligible in practice.
- **Validation Logic**: Unlike simple "word-to-real" converters, the value is only output if it lies within the defined valid range. This prevents misinterpretations of errors or invalid telegrams.
- **Initial Behavior**: The inputs `IN` have a default value of `NOT_AVAILABLE_WM`, so the function block immediately reports "invalid" after a reset or in case of no communication until a valid value is received.

## State Overview

| State | Content | Action | Output Event |

|---------|--------|--------|-----------------|

| `INIT` | Initialization (empty algorithm) | – | `INITO` |

| `REQ` | Signal Processing | Calculation of `OUT` and `VALID` | `CNF` |

The function block (FB) has no further states; after each event, it returns to the corresponding start state. There is no explicit error handling or timeouts.

## Application Scenarios
- **Agricultural Technology / Agricultural Control Systems**: A fieldbus device (e.g., ISOBUS) provides raw values for sensors (speed, temperature, pressure). The FB scales these to physical units and detects invalid measurement ranges.
- **Industrial Automation**: With Profibus/IO-Link connectivity, word codes can be converted into process-relevant quantities – e.g., 0…1000 → 0.0…10.0 V.
- **Diagnostic and Safety Functions**: Validation checks allow for easy detection of signal losses or range exceedances and the initiation of an error response.

## Comparison with Similar Function Blocks

| Function Block | Differences |

|----------|-------------|

| **FIELDBUS_WORD_TO_SIGNAL** (without scaling) | Maps the raw value 1:1, without multiplication/addition. |

| **WORD_TO_REAL** (standard IEC function block) | Pure type conversion without validation or scaling. |

| **SCALING_FB** | Usually with separate validation and scaling branches; this function block combines both in one step. |

The strength of `FIELDBUS_WORD_TO_SIGNAL_SCALED` lies in the **combination of validation, scaling, and offset** in a single, manageable function block.

## Conclusion
This function block offers a compact and robust solution for processing fieldbus raw data. It integrates the typical task chain "Check → Scale → Offset" and, thanks to its fixed validity threshold, ensures a clear separation between normal measured values and error signals. The use of external constants allows for flexible adaptation without complicating the internal logic. Ideal for safety-critical or diagnostic applications in automation technology.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]