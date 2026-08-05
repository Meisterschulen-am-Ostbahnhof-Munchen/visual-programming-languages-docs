# F_PHYS_TO_RAW
![F_PHYS_TO_RAW](./F_PHYS_TO_RAW.svg)

* * * * * * * * * *
## Introduction
The function block **F_PHYS_TO_RAW** converts a physical REAL value into an ISOBUS raw value (UDINT). Saturation limits are taken into account, and overflow and underflow alarms are issued. The conversion is based on the ISOBUS formula: `Anzeige = (Rohwert + Offset) * Skalierung`. The inverse calculation is: `Rohwert = UDINT(DINT(physikalischer Wert / Skalierung) - Offset)`.
## Interface Structure
### **Event Inputs**

| Event | Description |
|----------|--------------|
| REQ | Request to convert the physical value. Executed with the parameters `rPhys` and `stObj`. |

### **Event Outputs**

| Event | Description |
|----------|---------------|
| CNF | Confirmation that the conversion is complete. Returns the calculated raw value as well as the alarm flags `xOver` and `xUnder`. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-----|---------------|
| rPhys | REAL | The physical value to be converted. |
| stObj | NumericObjectPool_S | Structure with the parameters `i32Offset` (DINT) and `r32Scale` (REAL) for the ISOBUS formula. |

### **Data Outputs**

| Variable | Type | Description |
|----------|-----|--------------|
| * | UDINT | The calculated ISOBUS raw value (function return value). Saturated to the range 0 to 4294967295. |
| xOver | BOOL | TRUE if the physical value exceeds the upper limit. |
| xUnder | BOOL | TRUE if the physical value falls below the lower limit. |

### **Adapter**
None.

## Functionality
The function block first calculates the lower and upper limits:

- Lower limit: `lrLower = Offset * Skalierung`
- Upper limit: `lrUpper = (Offset + 4294967295) * Skalierung`

The physical value is then compared to these limits:

1. **Overflow (xOver = TRUE):** If `rPhys > lrUpper`, the raw value is set to the maximum UDINT value (4294967295).

2. **Underflow (xUnder = TRUE):** If `rPhys < lrLower`, the raw value is set to 0.

3. **Normal range:** Within the valid range, the raw value is calculated using the formula `UDINT(DINT(rPhys / Skalierung) - Offset)`.

This calculation is performed within the structured text code for each REQ event.

## Technical Features
- The return type is UDINT, and saturation is applied to the full value range from 0 to 4294967295.
- The offset and scaling data are read from an external structure (`NumericObjectPool_S`), typically provided by the ISOBUS object pool.
- The function block does not use internal states; the calculation is purely combinatorial and is performed completely anew with each REQ.
- The conversion from REAL to DINT is performed using `REAL_TO_DINT`, which can lead to rounding errors with large values.

## State Overview

The function block does not have an explicit state machine. It operates statelessly based on the current inputs. The output is recalculated with each REQ event.

## Application Scenarios
- **ISOBUS Control Units:** Conversion of sensor readings (e.g., temperature, pressure) into ISOBUS-compliant raw data values for display on a terminal.
- **Agricultural Machinery Control:** Conversion of physical quantities that are represented with a specific scale and offset in the ISOBUS diagnostic protocol.
- **Test and Simulation Environments:** Generation of ISOBUS raw values from simulated physical values.

## Comparison with Similar Function Blocks
Function blocks like `F_RAW_TO_PHYS` perform the inverse conversion (raw value → physical value). While this function block converts the physical quantity into the raw value, `F_PHYS_TO_RAW` additionally provides saturation and alarm signaling for overflow and underflow. Unlike general arithmetic function blocks, it is specifically designed for the ISOBUS convention with offset and scaling.

## Conclusion

The `F_PHYS_TO_RAW` function block is a specialized module for ISOBUS conversion with integrated range monitoring. It offers a simple and robust interface for integrating physical measured values into the ISOBUS protocol and ensures that the raw value always remains within the valid range. The alarm outputs enable immediate fault detection in the event of limit violations.
