# F_RAW_TO_PHYS_LREAL

![F_RAW_TO_PHYS_LREAL](./F_RAW_TO_PHYS_LREAL.svg)

* * * * * * * * * *
## Introduction
The function block `F_RAW_TO_PHYS_LREAL` converts a raw ISOBUS integer value (UDINT) into a physical floating-point value (LREAL).

The conversion follows the standardized ISOBUS formula:

`display = (raw + offset) * scale`

The block is optimized for use in agricultural control systems (ISOBUS) and uses the provided parameters from a pool of numeric objects.

## Interface Structure
### **Event Inputs**

| Name | Type | With Variables |

|------|------|----------------|

| REQ | Event | u32Raw, stObj |

The function block is triggered by an event at input `REQ`.

### **Event Outputs**

| Name | Type | With Variables |

|------|------|----------------|

| CNF | Event | (none) |

After successful calculation, the result is acknowledged via event `CNF`.

### **Data Inputs**

| Name | Type | Description |

|------|-------------|--------------|

| u32Raw | UDINT | Raw value from the ISOBUS bus (0 … 4294967295) |

| stObj | NumericObjectPool_S | Structure with the conversion parameters: `i32Offset` (DINT) and `r32Scale` (REAL) |

### **Data Outputs**

| Name | Type | Description |

|-------|-------|--------------|

| (no name) | LREAL | Calculated physical value (IEEE double precision) |

The output signal has no explicit name but represents the directly calculated LREAL value.

### **Adapter**
None.

## Functionality
The function block is activated via the event `REQ`. The input data is read in, and the following calculation is performed:

1. The 32-bit raw value `u32Raw` (UDINT) is converted unsigned to a 64-bit integer (LINT).

2. The offset value `stObj.i32Offset` (DINT) is also converted to LINT and added to the raw value.

3. The sum (LINT) is converted to an LREAL.

4. The intermediate result is multiplied by the scaling factor `stObj.r32Scale` (REAL).

5. The final result is available as an LREAL at the output.

6. The event `CNF` is then triggered.

Type conversion ensures that large UDINT values (e.g., 4,000,000,000) can be processed without information loss.

## Technical Features

- **Enhanced Accuracy**: The intermediate step via LINT prevents overflows during addition with large raw values and negative offsets.

- **ISOBUS Compliance**: The formula `display = (raw + offset) · scale` complies with the ISOBUS standard ISO 11783.

- **Parameterization via Structure**: All conversion coefficients are provided via the structure `NumericObjectPool_S`, making the function block universally applicable to various sensors and devices.

- **Single-Cycle Processing**: The calculation is performed without state storage within a single cycle.

## State Overview
The function block does not have an internal state machine, as it is a pure transformation function. It follows this sequence:

1. Wait for `REQ` (idle state)

2. At `REQ` → calculation → output of the result → trigger `CNF` → return to idle state

## Application Scenarios

- **Agricultural Engineering**: Conversion of ISOBUS raw values (e.g., speeds, pressures, flow rates) into physical units such as °/s, bar, or l/min.

- **Vehicle Control**: Processing of CAN data from tractors, harvesters, or application systems.

- **Simulation**: Replication of ISOBUS sensor data in test environments where raw values from a database with different scales are processed.

## Comparison with Similar Function Blocks

| Function Block | Input Data Type | Output Data Type | Special Features |

|----------|------------------|------------------|--------------|

| `F_RAW_TO_PHYS_LREAL` | UDINT | LREAL | Double precision, LINT intermediate step |

| `F_RAW_TO_PHYS_REAL` | UDINT | REAL | Single precision, reduced computational load |

| `F_RAW_TO_PHYS_LINT` | UDINT | LINT | Output as integer, without scaling |

| `F_RAW_TO_PHYS_INT` | UINT | REAL | Only positive raw values, smaller range |

This function block offers the highest precision and is recommended for applications requiring large ranges or fine increments.


## Conclusion

`F_RAW_TO_PHYS_LREAL` is a reliable and accurate converter for ISOBUS raw data processing.

By using LINT as the buffer and LREAL as the output type, rounding errors are minimized and large value ranges are covered. The module is particularly suitable for safety-critical or precision agricultural applications and can be flexibly adapted to various measured variables via its configurable structure.