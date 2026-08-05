# FIELDBUS_UDINT_TO_SIGNAL_SCALED
![FIELDBUS_UDINT_TO_SIGNAL_SCALED](./FIELDBUS_UDINT_TO_SIGNAL_SCALED.svg)
* * * * * * * * * *
## Introduction
The function block `FIELDBUS_UDINT_TO_SIGNAL_SCALED` processes a UDINT value received via the fieldbus. It mirrors the input `IN` to the output `OUT`, but only if the incoming signal is recognized as valid. Additionally, the value is scaled by a factor and an offset is applied. This function block is typically used in the signal processing chain of fieldbus protocols to convert raw integer values into physical quantities (e.g., as LREAL).
## Interface Structure

### **Event Inputs**

| Event | Type | With Parameters | Description |

|----------|-------|----------------|-----------------------------------------|

| `INIT` | EInit | `SCALE`, `OFFSET` | Initialization – sets scaling factor and offset. |

| `REQ` | Event | `IN` | Normal execution event – processes the current input value. |

### **Event Outputs**

| Event | Type | With Parameters | Description |

|----------|-------|----------------|-----------------------------------------|

| `INITO` | EInit | – | Confirmation of successful initialization. |
| `CNF` | Event | `OUT`, `VALID` | Processing confirmation – provides the scaled value and the validity signal. |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|----------|--------|------------------------------------------|---------------------------------------|

| `IN` | UDINT | `DWORD_TO_UDINT(NOT_AVAILABLE_DWM)` | Raw value from the fieldbus. |

| `SCALE` | LREAL | `LREAL#1.0` | Multiplicative scaling factor. |

| `OFFSET` | DINT | `DINT#0` | Additive Offset (after scaling). |

### **Data Outputs**

| Name | Type | Initial Value | Description |

|---------|--------|--------------|----------------------------------------------|

| `OUT` | LREAL | `LREAL#0.0` | Scaled output value. |

| `VALID` | BOOL | `FALSE` | `TRUE`, if the input value was recognized as valid. |

### **Adapter**

No adapters available.

## Functionality

The function block has two states: `INIT` and `REQ`.

- **INIT State**: Upon a `INIT` event, the empty algorithm is executed (no action is taken), and subsequently, `INITO` is output. The parameters `SCALE` and `OFFSET` are passed to the function block but are only used during the next `REQ` processing.
- **REQ State**: On a `REQ` event, the following logic is executed:

1. The incoming value `IN` is compared to a predefined threshold `VALID_SIGNAL_DW` (from the import `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL::VALID_SIGNAL_DW`).

2. If `IN <= DWORD_TO_UDINT(VALID_SIGNAL_DW)` is true, the input is considered valid. Then `OUT` is calculated as:

`OUT := UDINT_TO_LREAL(IN) * SCALE + DINT_TO_LREAL(OFFSET)`

and `VALID` is set to `TRUE`.

3. Otherwise, `OUT` is set to `0.0` and `VALID` to `FALSE`. This indicates that the transmitted fieldbus value is invalid (e.g., error value or communication failure).

The initial value of `IN` is preset to `DWORD_TO_UDINT(NOT_AVAILABLE_DWM)`, a constant from the same import that represents a special "not available" value.

## Technical Features
- The validity check is based on two imported constants:
- `VALID_SIGNAL_DW`: Upper limit for valid values.
- `NOT_AVAILABLE_DWM`: Default value for unavailable signals (used as the initial value for `IN`).
- Scaling is performed in LREAL (double precision), allowing for precise processing of very large or small input values.
- The offset is defined as `DINT`, but is converted to `LREAL` before addition. The entire computational range is covered by the LREAL representation.

## State Overview

The function block uses a simple state diagram with two states:

- **INIT**: Executed after the `INIT` event. The algorithm `INIT` is empty, and the output `INITO` is triggered.
- **REQ**: This event is executed after the `REQ` event. Here, the algorithm `REQ` is executed, which performs scaling and validation, and then outputs `CNF`.

There are no other states or loops.

## Application Scenarios
- **Scaling of Sensor Values**: A fieldbus device provides a raw UDINT value (e.g., 0 … 65535). `SCALE` converts a physical quantity (e.g., pressure in bar), and the offset accounts for zero-point shifts.
- **Validation Check**: Typical fieldbus protocols define certain bit patterns as "invalid." This function block automatically filters out these values and sets `VALID = FALSE`.
- **Initialization**: At system startup, the scaling factor can be set via `INIT`, while the `REQ` cycle regularly processes the current process values.

## Comparison with Similar Function Blocks

Similar function blocks are often generic `SCALE` functions that do not include a validation check. This function block adds explicit validation of the fieldbus signal. Other implementations might make the validity range configurable as a parameter or via separate thresholds. This function block uses fixed constants defined in the import library, which simplifies configuration but is less flexible.

## Conclusion

The `FIELDBUS_UDINT_TO_SIGNAL_SCALED` function block provides a robust and simple way to scale raw data from a fieldbus while simultaneously evaluating signal quality. The combination of scaling factor and offset, along with integrated validation, makes it particularly suitable for industrial automation applications where both the conversion and plausibility check of measured values are required.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]