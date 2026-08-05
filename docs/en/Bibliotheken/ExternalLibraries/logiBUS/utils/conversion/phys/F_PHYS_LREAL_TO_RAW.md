# F_PHYS_LREAL_TO_RAW
![F_PHYS_LREAL_TO_RAW](./F_PHYS_LREAL_TO_RAW.svg)
*Image not available*
* * * * * * * * * *
## Introduction
The function block F_PHYS_LREAL_TO_RAW converts a physical measured value in the LREAL data type into an ISOBUS-compliant raw value as a UDINT. Saturation limits are observed, and overflow and underflow states are signaled as Boolean outputs. The conversion follows the ISOBUS formula:

**Display value = (Raw value + Offset) · Scaling**
**Raw value = UDINT( UDINT( physical value / scaling ) – Offset )**

This function block is suitable for applications that need to integrate physical quantities into the ISOBUS protocol, particularly in agricultural and commercial vehicle technology.

## Interface Structure

### **Event Inputs**

| Event | Description | Accompanying Variables |

|----------|--------------|-----------------------|

| `REQ` | Starts the conversion | `lrPhys`, `stObj` |

### **Event Outputs**

| Event | Description | Accompanying Variables |

|----------|--------------|------------------------|

| `CNF` | Confirms the conversion is complete | `xOver`, `xUnder` |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|---------|----------------------------------------------------------|-------------|---------------------------------------------------|

| `lrPhys`| `LREAL` | – | Physical Input Value (e.g., Temperature, Pressure) |

| `stObj` | `logiBUS::utils::conversion::phys::NumericObjectPool_S` | `(u16ObjId := 65535, r32Scale := 1.0, i32Offset := 0, u8Decimals := 0)` | Data Structure with Scaling and Offset Parameters |

### **Data Outputs**

| Name | Type | Description |

|----------|--------|----------------------------------------------|

| *(no name)* | `UDINT` | Calculated ISOBUS raw value (0 … 4294967295) |

| `xOver` | `BOOL` | `TRUE`, if the input exceeds the upper limit (overflow) |

| `xUnder` | `BOOL` | `TRUE`, if the input falls below the lower limit (underflow) |

### **Adapters**

This function block does not use adapters.

## Functionality

The function block performs the following steps:

1. **Calculation of limits:**

- Lower limit: `i32Offset * r32Scale`
- Upper limit: `(i32Offset + 4294967295) * r32Scale`

2. **Comparison and saturation:**

- If `lrPhys > obere Grenze` is present → Raw value = **UDINT#4294967295**, `xOver = TRUE`.

If `lrPhys < untere Grenze` is present → Raw value = **0**, `xUnder = TRUE`.

- Otherwise → Raw value = `DINT_TO_UDINT( LREAL_TO_DINT( lrPhys / r32Scale ) - i32Offset )`, no overflow/underflow message.

3. **Output:** The calculated raw value is provided at the unnamed `UDINT` output, and the event `CNF` is triggered.

## Technical Features
- **ISOBUS Compliance:** The conversion follows the ISOBUS specification exactly (ISO 11783).
- **Saturation Behavior:** Critical ranges are represented by the overflow/underflow outputs `xOver` and `xUnder`, allowing subsequent functions (e.g., alarms) to react.
- **Scaling Unit:** The scaling factor `r32Scale` is of type `REAL` and is directly included in the calculation.
- **Integer Conversion:** The conversion from LREAL via DINT to UDINT is performed using the rounding standard in IEC 61499 (truncation of decimal places).
- **No State Machines:** The function block operates purely functionally without an internal state machine.

## State Overview

The function block does not have an explicit state machine. The calculation is triggered by the event `REQ`; after one cycle, the result is provided at the data output and the event `CNF` is sent. The execution time is deterministic and depends only on the runtime environment.

## Application Scenarios
- **Agricultural Control Units:** Conversion of sensor values (e.g., torque, pressure) into ISOBUS raw data for transmission to terminals or actuators.
- **Diagnostics and Monitoring:** Detection of measurement range exceedances via `xOver`/`xUnder` to trigger warnings.
- **Data Logging:** Preparation of physical measured values for archiving in ISOBUS format.

## Comparison with Similar Function Blocks

Typical alternatives are custom-written calculation functions or generic conversion blocks.

The F_PHYS_LREAL_TO_RAW offers the following advantages:

- **Predefined parameterization** via the structure `NumericObjectPool_S` (object ID, scaling, offset, decimal places).
- **Integrated saturation** and limit value monitoring.
- **Reusable** in all logiBUS projects.

Disadvantages compared to a custom solution include the reliance on the ISOBUS formula and the fixed data structure.

## Conclusion

The F_PHYS_LREAL_TO_RAW function block is a compact, standards-compliant solution for converting physical measured values into the ISOBUS raw data format. Its saturation logic and monitoring outputs make it robust and reliable for use in industrial and agricultural control systems. The use of predefined structural parameters simplifies integration and reduces the potential for errors during parameterization.