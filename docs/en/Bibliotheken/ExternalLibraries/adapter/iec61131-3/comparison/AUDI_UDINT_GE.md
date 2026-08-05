# AUDI_UDINT_GE
![AUDI_UDINT_GE](./AUDI_UDINT_GE.svg)

* * * * * * * * * *
## Introduction
The function block **AUDI_UDINT_GE** performs a greater-than-or-equal-to (≥) comparison between two values of type UDINT. It encapsulates the comparison logic in an adapter-based interface that enables type-safe and event-driven communication with the environment.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-------|------------------|
| REQ | Event | Service Request |

### **Event Outputs**

No direct event outputs. The result is signaled as an event via the output adapter `OUT`.

### **Data Inputs**

| Name | Type | Comment |
|------|--------|------------------|
| IN2 | UDINT | Input value 2 |

### **Data Outputs**

No direct data outputs. The result value (BOOL) is provided via the output adapter `OUT`.

### **Adapters**

| Name | Type | Direction | Comment |
|------|---------------|----------------|----------------------------------|
| IN1 | AUDI (Socket) | Input | Input value 1 (via D1 and E1) |
| OUT | AX (Plug) | Output | Result: Value 1 ≥ Value 2 (D1), Event (E1) |

## Functionality

The function block operates in an event-driven manner. A comparison is triggered by:

- an event at input `REQ` or
- an event at adapter input `IN1.E1`.

Internally, the standard function block `F_GE` (IEC 61131-3) for the UDINT data type is used. The input data comes from:

- `IN1.D1` → first operand,
- `IN2` → second operand.

The comparison `IN1.D1 ≥ IN2` returns a BOOL result, which is output as the data value `OUT.D1` via the output adapter `OUT`. Simultaneously, an event is generated on `OUT.E1`, signaling the availability of the result.

## Technical Features
- **Adapter-Based Interface:** Instead of direct inputs/outputs, adapters (`AUDI`, `AX`) are used. This enables modular and type-safe cabling in larger networks.
- **Reuse of Standard Function Blocks:** The internal comparison is implemented using a certified IEC 61131-3 function block (`F_GE`), ensuring correctness and portability.
- **No Internal State:** The function is purely combinatorial; the result is recalculated immediately after each event.

## State Overview

The function block does not have an explicit state machine. It behaves like a pure function block without memory. Every input event triggers immediate evaluation and output.

## Application Scenarios
- **Threshold Monitoring:** Checks whether a measured value (via `IN1`) reaches or exceeds a set threshold (`IN2`).
- **Enable Logic:** Triggers an action when a counter variable (e.g., quantity) reaches at least a target value.
- **Sequence Controls:** Linking time or count values with comparison conditions in an adapter-based control architecture.

## Comparison with Similar Function Blocks
- **`AUDI_UDINT_GT`**: Performs a "greater than" comparison (>); if equal, it returns `FALSE`.
- **`AUDI_UDINT_EQ`**: Checks for equality (=).
- **`F_GE` (direct)**: Offers the same logic, but without an adapter interface. The `AUDI_UDINT_GE` facilitates integration into adapter-based component models.

## Conclusion

The `AUDI_UDINT_GE` function block is a specialized comparison block for UDINT values that combines the advantages of adapter technology with proven IEC 61131-3 logic. It is particularly suitable for modular, event-driven control applications where type-safe and flexible interfaces are required.
