# ATM_IN_S_TO_AULI

![ATM_IN_S_TO_AULI](ATM_IN_S_TO_AULI.svg)

* * * * * * * * * *

## Introduction

The function block **ATM_IN_S_TO_AULI** is a composite block that converts a `TIME` value (carried via the [ATM](../../../types/unidirectional/TIME/ATM.md) adapter) expressed in seconds into a `ULINT` value (64-bit unsigned integer), output via the [AULI](../../../types/unidirectional/ULINT/AULI.md) adapter. It belongs to the `ATM_IN_<UNIT>_TO_<TARGET>` block family, which provides the same conversion for all four time units (MS, NS, S, US) and all five target integer/floating-point types.

## Interface Structure

### **Event Inputs**

- No directly visible event inputs. Event control is handled indirectly via the **IN** adapter (event E1).

### **Event Outputs**

- No directly visible event outputs. Event signaling is handled indirectly via the **OUT** adapter (event E1).

### **Data Inputs**

- No directly visible data inputs. The input value is provided via the **IN** adapter (data point D1 of type `TIME`).

### **Data Outputs**

- No directly visible data outputs. The output value is provided via the **OUT** adapter (data point D1 of type `ULINT`).

### **Adapters**

| Adapter | Role | Type | Description |
| --------- | ------- | ----- | -------------- |
| IN | Socket | adapter::types::unidirectional::ATM | Unidirectional `TIME` adapter as input interface. |
| OUT | Plug | adapter::types::unidirectional::AULI | Unidirectional `ULINT` adapter as output interface, value of `IN` expressed in seconds. |

## Functionality

The function block internally contains a single function block, `F_TIME_IN_S_TO_ULINT`, from the IEC 61131-3 standard library. Sequence control is purely event-driven:

1. An event at the input adapter **IN.E1** triggers the input **REQ** of the internal conversion block.
2. The data value **IN.D1** (`TIME`) is passed to the input **IN** of `F_TIME_IN_S_TO_ULINT`.
3. `F_TIME_IN_S_TO_ULINT` converts the time value into a seconds figure of type `ULINT` and signals this via its output **CNF**.
4. This event is forwarded to the output adapter **OUT.E1**.
5. Simultaneously, the converted value (output **OUT** of `F_TIME_IN_S_TO_ULINT`) is passed to the data point **OUT.D1**.

The entire process is synchronous and without intermediate storage – each successful conversion immediately triggers an output event.

## Technical Features

- **Unit conversion per IEC 61131-3**: The internal block `F_TIME_IN_S_TO_ULINT` interprets the `TIME` value (internally held in nanoseconds) as a figure in seconds and returns the result as `ULINT` (64-bit unsigned integer).
- **Unidirectional adapters**: Both the input and output adapters are unidirectional. Reverse communication is not supported.
- **Composite structure without its own logic**: The block consists solely of a data and an event connection to the internal conversion block; there is no ECC of its own.
- **Empty TypeHash**: As with all generated conversion composites in this package, `eclipse4diac::core::TypeHash` is empty (`''`).

## State Overview

The function block does not have its own state machine. The process can be described as a simple step:

| Step | Action |
| --------- | -------- |
| 1 | Wait for event at **IN.E1** |
| 2 | Convert the data value from `TIME` (seconds) to `ULINT` via `F_TIME_IN_S_TO_ULINT` |
| 3 | Output the converted value to **OUT.D1** and event to **OUT.E1** |
| 4 | Return to step 1 |

## Application Scenarios

- **Displaying/processing durations**: A duration carried via an `ATM` adapter (e.g., a cycle time or delay) needs to be forwarded as a figure in seconds to an adapter socket of type `AULI`, for example for display on a panel or further use in a calculation.
- **Interface adaptation**: In networks that consistently rely on adapter connections instead of classic data wiring, the block enables seamless conversion of a time adapter into a numeric adapter.

## Comparison with similar function blocks

- **Same unit, other target types**: [ATM_IN_S_TO_ADI](ATM_IN_S_TO_ADI.md), [ATM_IN_S_TO_ALI](ATM_IN_S_TO_ALI.md), [ATM_IN_S_TO_ALR](ATM_IN_S_TO_ALR.md), [ATM_IN_S_TO_AUDI](ATM_IN_S_TO_AUDI.md)
- **Same target type, other units**: [ATM_IN_MS_TO_AULI](ATM_IN_MS_TO_AULI.md), [ATM_IN_NS_TO_AULI](ATM_IN_NS_TO_AULI.md), [ATM_IN_US_TO_AULI](ATM_IN_US_TO_AULI.md)
- **[ATM_TIME_TO_TM](ATM_TIME_TO_TM.md) / [ATM_TM_TO_TIME](ATM_TM_TO_TIME.md)**: pure adapter-to-variable passthrough without unit conversion, unlike the numeric conversion performed by `ATM_IN_S_TO_AULI`.

## Conclusion

`ATM_IN_S_TO_AULI` provides a standards-compliant, fully adapter-based conversion of a `TIME` value in seconds into a `ULINT` value, fitting seamlessly into networks that consistently rely on adapter connections instead of classic data wiring.
