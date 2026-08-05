# FIELDBUS_USINT_TO_SIGNAL_SCALED
![FIELDBUS_USINT_TO_SIGNAL_SCALED](./FIELDBUS_USINT_TO_SIGNAL_SCALED.svg)
* * * * * * * * * *
## Introduction
The function block **FIELDBUS_USINT_TO_SIGNAL_SCALED** converts an incoming USINT signal into a scaled REAL value, taking a validity check into account. It is typically used in fieldbus signal processing to apply a scaling factor and an offset to raw fieldbus values (e.g., sensor data) and simultaneously evaluate the validity of the input signal. The block is structured according to the IEC 61499-1 standard.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |

| :--- | :--- | :--- |

| `INIT` | EInit | Initialization Request; linked to the parameters `SCALE` and `OFFSET`. |

| `REQ` | Event | Normal execution request; linked to the data input `IN`. |

### **Event Outputs**

| Event | Type | Description |

| :--- | :--- | :--- |

| `INITO` | EInit | Initialization confirmation. |

| `CNF` | Event | Execution confirmation; linked to the outputs `OUT` and `VALID`. |

### **Data Inputs**

| Name | Data Type | Initial Value | Description |

| :--- | :--- | :--- | :--- |

| `IN` | USINT | `BYTE_TO_USINT(NOT_AVAILABLE_B)` | Input signal as an unsigned 8-bit value. The initial value corresponds to the "not available" signal. |

| `SCALE` | REAL | `REAL#1.0` | Scaling factor (multiplication). |

| `OFFSET` | DINT | `DINT#0` | Offset added after scaling. |

### **Data Outputs**

| Name | Data Type | Initial Value | Description |

| :--- | :--- | :--- | :--- |

| `OUT` | REAL | `REAL#0.0` | Scaled output value. |

| `VALID` | BOOL | `FALSE` | Validation flag: `TRUE`, if the input signal is valid. |

### **Adapter**

None available.

## Functionality

The function block operates with two states: `INIT` and `REQ`.

- On a `INIT` event, the parameters `SCALE` and `OFFSET` are taken (the algorithm is empty, but the values are read in by the `With` binding). Then, `INITO` is output.
- On a `REQ` event, the algorithm `REQ` is executed:

If the input value `IN` is less than or equal to the predefined threshold `BYTE_TO_USINT(VALID_SIGNAL_B)`, the signal is considered valid. In this case, the value is scaled as follows:

OUT := USINT_TO_REAL(IN) * SCALE + DINT_TO_REAL(OFFSET)
and `VALID` is set to `TRUE`.

If `IN` exceeds the threshold (i.e., the signal is invalid), `OUT` is set to `0.0` and `VALID` to `FALSE`.

This behavior mirrors the input 1:1 to the output, provided the signal is valid – with additional scaling and offset.

## Technical Details
- The constants `NOT_AVAILABLE_B` and `VALID_SIGNAL_B` come from the external package `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`. They define the boundaries between valid and invalid USINT values. `BYTE_TO_USINT(NOT_AVAILABLE_B)` is the initial state of the input and indicates an "unavailable" signal.
- The `INIT` algorithm contains no ST code – initialization is limited to providing the parameters via event binding. The function block expects a `INIT` call before the first `REQ` to set the scaling and offset.
- Scaling is always performed as REAL arithmetic; therefore, the offset is converted from DINT to REAL.

## State Overview

The function block has two elementary states as simple FBs:

| State | Action | Output Event |

| :--- | :--- | :--- |

| `INIT` | Execute algorithm `INIT` (empty) | `INITO` |

| `REQ` | Execute algorithm `REQ` | `CNF` |

There are no further wait states – each incoming event immediately triggers the processing of the corresponding algorithm and the output of the associated result.

## Application Scenarios
- **Fieldbus Sensor Evaluation**: A sensor delivers a raw USINT value (e.g., 0…200). The physical quantity (e.g., pressure in bar) is calculated from this using `SCALE` and `OFFSET`. The limit value `VALID_SIGNAL_B` separates valid measured values from error or initialization values.
- **Process Variable Update**: In PLC or control applications, the function block is triggered cyclically with `REQ` to process the latest fieldbus data and incorporate it into the control context.

## Comparison with Similar Function Blocks
- **`FIELDBUS_USINT_TO_SIGNAL`**: A simpler function block without scaling or offset; it outputs the USINT value directly as REAL or as another data type.
- **`FIELDBUS_WORD_TO_SIGNAL_SCALED`**: Analog function block for WORD inputs – offers higher resolution but requires a different data type.

**`FIELDBUS_USINT_TO_SIGNAL_SCALED`** is characterized by the combination of validity checking (based on the constant `VALID_SIGNAL_B`) and simple linear scaling (multiplication + addition).

## Conclusion

The function block `FIELDBUS_USINT_TO_SIGNAL_SCALED` is a compact yet powerful component for processing 8-bit fieldbus signals. It combines validity detection, scaling, and offset in a single logical unit and is particularly suitable for applications where raw values need to be converted into physical quantities and their plausibility checked simultaneously. Its simple state machine and clearly defined interfaces make it robust and easy to use.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]