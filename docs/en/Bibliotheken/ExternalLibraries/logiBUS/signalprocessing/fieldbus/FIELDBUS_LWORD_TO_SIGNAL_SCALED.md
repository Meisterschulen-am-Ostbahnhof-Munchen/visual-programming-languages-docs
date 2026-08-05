# FIELDBUS_LWORD_TO_SIGNAL_SCALED
![FIELDBUS_LWORD_TO_SIGNAL_SCALED](./FIELDBUS_LWORD_TO_SIGNAL_SCALED.svg)
* * * * * * * * * *
## Introduction
The function block **FIELDBUS_LWORD_TO_SIGNAL_SCALED** converts a raw fieldbus signal in **LWORD** format into a scaled **LREAL** output value. It mirrors the input signal to the output, provided the signal is valid, and applies linear scaling. This function block is designed for use in industrial automation, particularly in the context of fieldbus systems.
## Interface Structure
### **Event Inputs**

| Event | Type | Description | Accompanying Data |

|----------|-----|---------------|-------------------|

| INIT | EInit | Initialization Request: Set Scale Factor (SCALE) and Offset (OFFSET) | SCALE, OFFSET |

| REQ | Event | Normal Execution Request: Process Input Signal (IN) | IN |

### **Event Outputs**

| Event | Type | Description | Accompanying Data |

|----------|-----|--------------|-------------------|

| INITO | EInit | Initialization Acknowledge | – |

| CNF | Event | Execution Acknowledge | OUT, VALID |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|----------|--------|-----------------------|-----------------------------------------------|

| IN | LWORD | NOT_AVAILABLE_LWM | Fieldbus Raw Signal (LWORD) |

SCALE | LREAL | LREAL#1.0 | Scaling Factor (Multiplication) |

OFFSET | DINT | DINT#0 | Offset added after scaling |

### **Data Outputs**

| Name | Type | Initial Value | Description |

|--------|-------|-------------|--------------------------------------------------------------|

OUT | LREAL | LREAL#0.0 | Scaled Output Value (LREAL) |

VALID | BOOL | FALSE | Indicates whether the input signal is valid (TRUE = valid) |

### **Adapters**
No adapters available.

## Functionality

The module has two algorithms that are triggered by the **INIT** and **REQ** events.

- **INIT** (on event `INIT`): The algorithm is empty, but sets the output event `INITO`. This allows the scaling parameters (SCALE and OFFSET) to be initialized via the INIT call without immediate processing.
- **REQ** (on event `REQ`): Performs the actual signal processing:

1. The input signal `IN` (LWORD) is interpreted as an unsigned integer value (`LWORD_TO_ULINT`).

2. This value is compared to an internally defined valid threshold value, **VALID_SIGNAL_LW** (also an LWORD, imported constant). The comparison is performed at the ULINT level.

``` 3. **Validity**: If `IN` ≤ `VALID_SIGNAL_LW`, the signal is considered valid:

- `OUT` = `(ULINT_TO_LREAL(IN)) * SCALE + DINT_TO_LREAL(OFFSET)`
- `VALID` = `TRUE`

4. **Invalidity**: Otherwise, the signal is considered invalid:

- `OUT` = `0.0`
- `VALID` = `FALSE`

5. After the calculation, the output event `CNF` is sent.

The scaling is linear: `OUT = IN_als_LREAL * SCALE + OFFSET`. The default value of `SCALE` is 1.0, and that of `OFFSET` is 0, so identical transmission occurs without adjustment.

## Technical Features
- **Validity Check**: The function block uses two imported constants:
- `NOT_AVAILABLE_LWM`: Initial value for the input `IN` (indicates "not available").
- `VALID_SIGNAL_LW`: Threshold up to which a signal is considered valid (inclusive).

The comparison is performed by converting both LWORD values to ULINT, so that negative values (as bit patterns) are also correctly interpreted.

``` - **Type Conversion**: The raw value is converted from LWORD to LREAL via ULINT (64-bit). Potential precision losses should be noted for very large ULINT values.

- **Scaling Parameters**: `SCALE` (LREAL) and `OFFSET` (DINT) are set only during the INIT event and remain unchanged for all subsequent REQ calls.
- **Event Control**: The function block has a simple state machine with two states and requires explicit initialization before first processing.

## State Overview

| State | Triggered by | Output Algorithm | Event Output | Description |

|---------|----------------|--------------------|-----------------|--------------|

| INIT | Event INIT | INIT | INITO | Initialization: Adopt Scaling Parameters |

REQ | Event REQ | REQ | CNF | Signal Processing: Scaling and Validation Check |

The function block switches between these two states only through the corresponding events. There is no explicit transition to a wait state after initialization; the function block remains in the last state until a new event arrives.

## Application Scenarios
- **Analog Values from the Fieldbus**: A raw LWORD value from an analog input module (e.g., 0…10V, scaled as a raw value) is converted into a physical value (e.g., pressure, temperature) using SCALE and OFFSET.
- **Validation Filter**: Signals that are outside the permissible range (e.g., wire break or overflow) are detected by the validity check and marked as invalid, while the output is set to 0.
- **Parameter Initialization**: Scaling can be configured via the INIT event when the controller starts, without the actual processing having to run yet.

## Comparison with Similar Function Blocks
- **FIELDBUS_LREAL_TO_SIGNAL_SCALED**: An analog function block for LREAL inputs that offers similar validation and scaling.
- **FIELDBUS_SINT_TO_SIGNAL_SCALED**: For signed 8-bit values.
- **Simple Scalers without Validation**: Function blocks like `SCALE` or `MUL_ADD` only offer the mathematical operation, but no fieldbus-specific validation.

This function block combines validation (via the threshold `VALID_SIGNAL_LW`) with linear scaling and is therefore particularly suitable for fieldbus applications where the validity of the signal must be ensured before further processing.

## Conclusion

**FIELDBUS_LWORD_TO_SIGNAL_SCALED** is a compact yet powerful function block for processing fieldbus signals in LWORD format. It offers simple scaling, integrated validation, and a clean separation of initialization and execution. Through the use of standardized imports (`VALID_SIGNAL_LW`)It can be easily integrated into existing libraries and adapted to specific fieldbus protocols. The module is available under the Eclipse Public License 2.0 and is suitable for use in industrial control systems with IEC 61499-compliant runtime environments.