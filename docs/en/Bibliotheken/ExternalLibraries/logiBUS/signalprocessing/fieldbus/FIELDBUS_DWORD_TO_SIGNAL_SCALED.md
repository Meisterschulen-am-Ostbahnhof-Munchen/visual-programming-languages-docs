# FIELDBUS_DWORD_TO_SIGNAL_SCALED
![FIELDBUS_DWORD_TO_SIGNAL_SCALED](./FIELDBUS_DWORD_TO_SIGNAL_SCALED.svg)
* * * * * * * * * *
## Introduction
The function block **FIELDBUS_DWORD_TO_SIGNAL_SCALED** converts a fieldbus DWORD signal into a scaled LREAL value. It checks the validity of the input signal against a predefined range and, if the signal is valid, calculates the output value by multiplying it by a scaling factor and adding an offset. If the signal is invalid, the output is set to 0 and the validity flag is set to FALSE.
## Interface Structure
### **Event Inputs**

| Event | Type | Description |

|----------|-----|---------------|

| INIT | EInit | Initialization request; passes scaling parameters |

| REQ | Event | Normal execution request for processing the input |

### **Event Outputs**

| Event | Type | Description |

|----------|-----|--------------|

| INITO | EInit | Initialization Acknowledgement |

| CNF | Event | Execution Acknowledgement; returns scaled output and validity flag |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|--------|-------|-----------------------|--------------|

| IN | DWORD | NOT_AVAILABLE_DWM | Input value from the fieldbus |

| SCALE | LREAL | LREAL#1.0 | Scaling factor (multiplier) |

| OFFSET | DINT | DINT#0 | Offset added after scaling |

### **Data Outputs**

| Name | Type | Initial Value | Description |

|-------|-------|--------------|--------------|

| OUT | LREAL | LREAL#0.0 | Scaled output value |

| VALID | BOOL | FALSE | TRUE if the input signal is valid |

##**Adapters**
No adapters available.

## Functionality
The function block has two states: **INIT** and **REQ**.

- **INIT state**: Triggered by the INIT event. The associated algorithm is empty, meaning no further actions are performed. The INITO output confirms the completion of the initialization.
- **REQ state**: Triggered by the REQ event. The REQ algorithm performs the following steps:

1. Checks whether the input value IN, interpreted as a UDINT, is less than or equal to the constant `VALID_SIGNAL_DW`.

2. If this condition is met, the signal is considered valid:

- `OUT` is calculated as: `UDINT_TO_LREAL(DWORD_TO_UDINT(IN)) * SCALE + DINT_TO_LREAL(OFFSET)`
- `VALID` is set to `TRUE`.

3. Otherwise (signal invalid):

- `OUT` is set to `0.0`.
- `VALID` is set to `FALSE`.

4. The CNF event is then triggered, providing the results (OUT, VALID).

The constants `NOT_AVAILABLE_DWM` and `VALID_SIGNAL_DW` are taken from imported libraries and define which DWORD values are considered "not available" and "valid," respectively.

## Technical Features
- The function block uses a range check by comparing `DWORD_TO_UDINT(IN)` with `VALID_SIGNAL_DW`. This assumes that valid fieldbus signals lie within a specific range of numbers.
- The conversion is performed without floating-point errors because the DWORD is first converted to UDINT and then to LREAL.

``` - The scaling factor `SCALE` and the offset `OFFSET` can be set during initialization or runtime, but are only used in the REQ algorithm.

- The function block is implemented as a SimpleFB and is suitable for cyclic processing.

## State Overview

| State | Trigger | Action | Output |

|---------|----------|---------|---------|

| INIT | INIT Event | INIT Algorithm (empty) | INITO |

| REQ | REQ Event | REQ Algorithm (calculation and validation) | CNF |

The function block does not require state transitions between INIT and REQ – both states are triggered directly by their respective events.

## Application Scenarios
- **Agricultural Fieldbus Controllers**: Conversion of raw DWORD sensor values (e.g., rotational speeds, pressures) into physical units, taking sensor characteristics into account.
- **Scaling of Analog Values**: When a fieldbus device delivers a 32-bit raw value that must first be converted into a normalized value (e.g., 0-100%) using a factor and offset.
- **Signal Validation**: Only valid signals (within a defined range) are processed further; for invalid values, a defined zero value is output.

## Comparison with Similar Function Blocks
- **FIELDBUS_DWORD_TO_SIGNAL**: A similar function block without scaling capabilities, which outputs the raw value directly as LREAL.
- **FIELDBUS_DWORD_TO_SIGNAL_SCALED** additionally offers the parameters `SCALE` and `OFFSET` for flexible conversion.
- **Event-driven converters**: Other function blocks may use different validation logic (e.g., bitmasks) or support different fieldbus types.

This function block combines signal validation with a simple linear transformation, making it suitable for many applications.

## Conclusion
The `FIELDBUS_DWORD_TO_SIGNAL_SCALED` is a compact and reusable function block for processing fieldbus signals. It enables reliable validity checking and simultaneous scaling in a single step. Due to the clear separation of initialization and processing, it is suitable for both one-time and cyclic calls in automation systems, particularly in agricultural technology.