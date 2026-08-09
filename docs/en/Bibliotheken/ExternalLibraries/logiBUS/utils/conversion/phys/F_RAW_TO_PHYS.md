# F_RAW_TO_PHYS

![F_RAW_TO_PHYS](./F_RAW_TO_PHYS.svg)

* * * * * * * * * *
## Introduction

The function block **F_RAW_TO_PHYS** converts an ISOBUS raw value of type `UDINT` into a physical value of type `REAL`. The conversion is performed according to the standardized ISOBUS formula:
display = (raw + offset) * scale`

It is typically used in agricultural control systems to convert sensor data or actuator values between the CAN-based ISOBUS signal layer and the application.

## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|------|-------|---------------|
| REQ | Event | Starts the conversion of a raw value (using `u32Raw` and `stObj`). |

### **Event Outputs**

| Name | Type | Description |
|------|-------|--------------|
| CNF | Event | Confirms that the calculation is complete and the output value is valid. |

### **Data Inputs**

| Name | Type | Description |
|--------|-------|--------------|
| u32Raw | UDINT | The raw integer value (e.g., from an ISOBUS message object). |
| stObj | `NumericObjectPool_S` | Structure containing the offset (`i32Offset : DINT`) and the scaling factor (`r32Scale : REAL`). |

### **Data Outputs**

| Name | Type | Description |
|------|------|--------------|
| (no explicit name) | REAL | The calculated physical value, output as a floating-point number. |

### **Adapters**

None.

## Functionality

When an event occurs at the **REQ** input, the function block performs the following calculation:

1. The raw value `u32Raw` is converted from `UDINT` to `LINT` (64-bit to prevent overflows during addition).
2. The offset `stObj.i32Offset` is also extended to `LINT`.
3. Both values are added: `(u32Raw + stObj.i32Offset)`.
4. The intermediate result is converted to `REAL` and multiplied by the scaling factor `stObj.r32Scale`.

Result: `REAL := (LINT(UDINT(u32Raw)) + LINT(stObj.i32Offset)) * stObj.r32Scale`

**Example (from the source code documentation):**

- Raw value = 50000
- Scaling = 0.01
- Offset = -100000
- Calculation: `(50000 + (-100000)) * 0,01 = (-50000) * 0,01 = -500,0`

The result is available at the data output after the **CNF** event.

## Technical Features

- The function block uses **`LINT`** (64-bit integer) as an intermediate type to reliably prevent overflow when adding `UDINT` and `DINT` (e.g., large positive values with large negative values).
- Raw value = 50000
- Scaling = 0.01
- Offset = -100000
- Calculation = `(50000 + (-100000)) * 0,01 = (-50000) * 0,01 = -500,0`

The result is available at the data output after the **CNF** event.

- The function block uses **`LINT`** (64-bit integer) as an intermediate type to reliably prevent overflow when adding `UDINT` and `DINT` (e.g., large positive values with large negative values). - The output variable has no name of its own – in the 4diac IDE, it is automatically displayed as `OUT` or can be referenced via the interface.
- Offset and scaling are configured via an external structure (`NumericObjectPool_S`), which typically originates from a pool object that bundles all parameters of an ISOBUS object.

## State Overview

The function block has **no** internal states or memory. Each call processes the current input data and simultaneously generates the output value. It is therefore a pure **combinatorial logic function block**.

## Application Scenarios

- **ISOBUS control units** (tractors, implements) – conversion of raw CAN data into physical units (e.g., pressure, position, speed).
- **Agricultural Applications** – Conversion of sensor values from the ISOBUS protocol into displayable values.
- **Test and Simulation Environments** – Replication of the ISOBUS conversion for development and verification purposes.

## Comparison with Similar Function Blocks

- **F_RAW_TO_PHYS** is specifically designed for the ISOBUS formula `(raw + offset) * scale` and uses the data types common there (`UDINT`, `DINT`).
- General converter function blocks (e.g., `LREAL_TO_REAL`) do not offer offset scaling logic and therefore must be manually supplemented with this calculation.

Other ISOBUS-specific function blocks, such as `F_PHYS_TO_RAW`, reverse the operation (converting from physical value to raw value).

## Conclusion

The **F_RAW_TO_PHYS** function block is a useful and cleanly implemented component for ISOBUS data conversion. The use of 64-bit intermediate values prevents overflow, and encapsulating the parameters in a structure facilitates reuse in projects that utilize the `NumericObjectPool` concept. It is suitable for both production use and rapid prototyping in the field of agricultural control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
