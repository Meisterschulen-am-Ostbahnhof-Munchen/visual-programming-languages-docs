# FIELDBUS_BYTE_TO_SIGNAL_SCALED
![FIELDBUS_BYTE_TO_SIGNAL_SCALED](./FIELDBUS_BYTE_TO_SIGNAL_SCALED.svg)
* * * * * * * * * *
## Introduction
The function block **FIELDBUS_BYTE_TO_SIGNAL_SCALED** converts an incoming byte value into a scaled real value. It checks whether the incoming signal is valid. If so, the input value is multiplied by a scaling factor and an offset is added. Otherwise, the output is set to zero and the validity signal is reset. This block is designed for use in fieldbus systems where sensor or actuator data is transmitted as bytes and needs to be linearized or normalized.
## Interface Structure

### **Event Inputs**

| Event | Type | Description | Data Carried |

|-------|-----|--------------|-------------------|
| `INIT` | EInit | Initialization request; sets scaling and offset | `SCALE`, `OFFSET` |

| `REQ` | Event | Normal processing request; evaluates input `IN` | `IN` |

### **Event Outputs**

| Event | Type | Description | Accompanying Data |

|-------|-----|--------------|-------------------|

| `INITO` | EInit | Initialization Acknowledgement | – |

| `CNF` | Event | Confirmation of processing; provides scaled value and validity | `OUT`, `VALID` |

### **Data Inputs**

| Name | Data Type | Initial Value | Description |

|---------|----------|-------------|--------------|

| `IN` | BYTE | `NOT_AVAILABLE_B` | Raw fieldbus value (byte) |

| `SCALE` | REAL | `1.0` | Scaling factor (multiplier) |

| `OFFSET` | DINT | `0` | Additive Offset (after scaling) |

### **Data Outputs**

| Name | Data Type | Initial Value | Description |

|---------|----------|-------------|--------------|

| `OUT` | REAL | `0.0` | Scaled Output Value |

| `VALID` | BOOL | `FALSE` | `TRUE`, if the incoming byte value was deemed valid |

### **Adapter**
None.

## Functionality

The function block is controlled by two events:

1. **Initialization (`INIT`)**

Upon arrival of `INIT`, the parameters `SCALE` and `OFFSET` are accepted. The associated algorithm (`INIT`) does not perform any further calculations. After successful initialization, the event `INITO` is sent.

2. **Processing (`REQ`)**

Upon arrival of `REQ`, the value of `IN` is compared to a fixed threshold value `VALID_SIGNAL_B`. This threshold is obtained from the imported package `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`.

- **Signal valid:** If `IN <= VALID_SIGNAL_B` is valid, the output value is calculated according to the formula

OUT := IN * SCALE + OFFSET`

and `VALID` is set to `TRUE`.

- **Signal invalid:** Otherwise, `OUT` is set to `0.0` and `VALID` is set to `FALSE`.

The event `CNF` is then sent with the current values of `OUT` and `VALID`.

The initial value of `IN` is `NOT_AVAILABLE_B` – another imported constant value that indicates an unavailable signal. Therefore, the first time `REQ` is called (without a previous valid input), it always produces an invalid output.

## Technical Features
- The constants `NOT_AVAILABLE_B` and `VALID_SIGNAL_B` are imported from a separate library package and are not defined locally. This ensures they are consistent across the entire project.
- Scaling is linear: multiplication by `SCALE` and addition by `OFFSET`. The offset is converted from type `DINT` to `REAL` before being converted to `REAL`.
- The input `IN` is first converted from `BYTE` to `USINT` (unsigned short integer) to obtain an integer range of 0…255.
- The block has an explicit initialization mode (`INIT`) that allows the scaling and offset to be reset at runtime.

```
## State Overview

The function block has two simple states, each activated by the corresponding event:

| State | Triggering Event | Executable Algorithm | Outgoing Events |

|---------|-------------------|--------------------------|-------------------|

| `INIT` | `INIT` | `INIT` (empty) | `INITO` |

| `REQ` | `REQ` | `REQ` (validation check + scaling) | `CNF` |

There are no automatic state transitions; Each state is addressed exclusively through its corresponding event.

## Application Scenarios
- **Exchange of analog sensor data via fieldbuses:**

An 8-bit sensor value (e.g., temperature 0…255) is to be converted into physical units (e.g., °C). The characteristic curve is adjusted via `SCALE` and `OFFSET`.

- **Error detection during data transmission:**

If the fieldbus defines certain byte values as invalid (e.g., `0xFF` for "sensor error"), the block detects these using the threshold `VALID_SIGNAL_B` and reports them via `VALID = FALSE`.

- **Initializing Configuration Parameters:**

Before the first processing, the desired scaling factor and offset can be set using `INIT`.

## Comparison with Similar Blocks
- **`FIELDBUS_BYTE_TO_SIGNAL`** (without scaling):

This block outputs the byte value directly as REAL, without multiplication or addition. It is suitable for signals that are already in the correct unit.

- **`FIELDBUS_BYTE_TO_SIGNAL_SCALED`** (existing block):

Additionally offers linear scaling and an offset. The user can flexibly adjust the conversion without changing the algorithm.

- **`FIELDBUS_WORD_TO_SIGNAL_SCALED`**:

Analog block for 16-bit values (WORD) with identical scaling logic, but a different input data type.

## Conclusion

The function block `FIELDBUS_BYTE_TO_SIGNAL_SCALED` is a practical tool for processing fieldbus signals in byte format. It combines simple validity checking with freely configurable linear scaling. Thanks to the use of imported constants, it can be integrated into standardized signal processing pipelines. The clear separation of initialization and operation, along with the two event interfaces, makes it a robust and easy-to-understand building block for industrial automation solutions.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
