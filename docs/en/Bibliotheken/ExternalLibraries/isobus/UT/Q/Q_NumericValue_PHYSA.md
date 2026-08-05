# Q_NumericValue_PHYSA
![Q_NumericValue_PHYSA](./Q_NumericValue_PHYSA.svg)
* * * * * * * * * *
## Introduction
The function block `Q_NumericValue_PHYSA` serves as a wrapper for the function block `Q_NumericValue_PHYS`. It allows setting a numeric value, which is received as a physical value (`REAL`) via an AR adapter (socket `rPhys`). The function block is designed according to the ISO 11783-6 standard and is suitable for ISOBUS applications that require a physical value input.
## Interface Structure
### **Event Inputs**

| Name | Type | Description |

|------|-----|--------------|

| `INIT` | `EInit` | Service initialization; executed with data input `stObj` |

### **Event Outputs**

| Name | Type | Description |

|------|-----|--------------|

| `INITO` | `EInit` | Confirmation of successful initialization |

| `CNF` | `Event` | Confirmation of value change performed; Output together with `STATUS` and `s16result` |

### **Data Inputs**

| Name | Type | Description |

|------|-----|---------------|

| `stObj` | `logiBUS::utils::conversion::phys::NumericObjectPool_S` | Object pool properties: `u16ObjId` (Object ID), `r32Scale` (Scaling), `i32Offset` (Offset), `u8Decimals` (Decimal places). Default value: `(u16ObjId := ID_NULL, r32Scale := 1.0, i32Offset := 0, u8Decimals := 0)` |

### **Data Outputs**

| Name | Type | Description |
|------|-----|--------------|

| `STATUS` | `STRING` | Service status message |

| `s16result` | `INT` | Return value (see documentation for `Q_NumericValue`) |

### **Adapter**

| Type | Name | Direction | Description |

|-----|------|----------|--------------|

| `adapter::types::unidirectional::AR` | `rPhys` | Socket (Input) | Receives the physical value `REAL` for processing |

| `adapter::types::unidirectional::AX` | `xOver` | Plug (Output) | Signals that the physical value exceeds the upper ISOBUS limit |

| `adapter::types::unidirectional::AX` | `xUnder` | Plug (Output) | Signals that the physical value falls below the lower ISOBUS limit |

## Functionality

1. After the **INIT** event, the function block is initialized with the object pool properties defined in `stObj`.

``` 2. As soon as a new physical value arrives via the **rPhys** adapter (socket event `E1`), it is internally forwarded to the bound **Q_NumericValue_PHYS** block.

3. The `Q_NumericValue_PHYS` processes the value (taking scaling, offset, and decimal places into account) and triggers the **CNF** event.

4. The **CNF** event simultaneously outputs the status (`STATUS`), the return value (`s16result`), and the threshold indicators `xOver` and `xUnder`.

5. The outputs `xOver` and `xUnder` are provided as AX adapters to inform higher-level logic whether the entered value is outside the permissible ISOBUS range.

## Technical Features
- The function block (FB) is a **pure adapter wrapper component**. The actual logic resides in the internally used `Q_NumericValue_PHYS`.
- The parameters for scaling and offset are configured via the **structure `NumericObjectPool_S`** – this allows for flexible adaptation to different physical units.
- Communication is **event-driven** via the adapters `AR` (value input) and `AX` (limit signal output). This enables modular integration into existing ISOBUS communication sequences.

## State Overview

The function block itself does not have an explicit state machine. The initialized state is established by the first `INIT` event. Subsequent value changes via `rPhys.E1` lead directly to processing and output. Error states are communicated via the output `STATUS`.

## Application Scenarios
- **ISOBUS APP Control:** Setting a numeric value (e.g., setpoint for machine parameters) from a physical sensor value connected via an adapter.
- **Real to ISOBUS Format Conversion:** The function block handles the conversion of physical values to the internal integer format using scaling and offset.
- **Limit Monitoring:** The outputs `xOver` and `xUnder` allow the higher-level controller to react to exceedances or falls below limits.

## Comparison with Similar Function Blocks

| Function Block | Description | Difference |

|----------|--------------|-------------|

| `Q_NumericValue_PHYS` | Direct function block for physical values | `Q_NumericValue_PHYSA` wraps this function block and adds explicit adapter outputs (`xOver`, `xUnder`) for limit signals |

| `Q_NumericValue` | Basic Function Block for Numeric Values (No Physical Conversion) | `Q_NumericValue_PHYSA` is specifically designed for real-world physical values and includes scaling/offset functionality.

## Conclusion
The `Q_NumericValue_PHYSA` simplifies the integration of physical values into ISOBUS systems by encapsulating adapter communication and directly signaling limit values. Reusing the proven `Q_NumericValue_PHYS` ensures robust and standards-compliant logic.
