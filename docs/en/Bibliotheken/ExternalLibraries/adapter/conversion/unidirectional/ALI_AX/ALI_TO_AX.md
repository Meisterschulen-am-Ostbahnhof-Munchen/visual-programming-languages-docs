# ALI_TO_AX

![ALI_TO_AX](./ALI_TO_AX.svg)

* * * * * * * * * *

## Introduction

The function block **ALI_TO_AX** is a composite function block that converts an adapter of type **ALI** (containing a LINT value) into an adapter of type **AX** (containing a BOOL value).
The conversion follows the rule: A LINT value other than 0 is interpreted as a BOOL value **TRUE**, and a value equal to 0 as **FALSE**.

The function block serves as a bidirectional bridge between adapters based on different data types.

## Interface Structure

### **Event Inputs**

- **ALI_IN.E1** – Input event from the ALI adapter. Triggers processing.

### **Event Outputs**

- **AX_OUT.E1** – Output event to the AX adapter. Sent after successful processing.

### **Data Inputs**

(No direct data inputs. Data is provided via the ALI adapter.)

- **ALI_IN.D1** – LINT input value via the adapter.

### **Data Outputs**

(No direct data outputs. Data is output via the AX adapter.)

- **AX_OUT.D1** – BOOL output value via the adapter.

### **Adapters**

| Adapter | Direction | Type | Description |
| --------- | ---------- | ----- | -------------- |
| **ALI_IN** | Socket (Input) | `adapter::types::unidirectional::ALI` | Input adapter with a LINT value. |
| **AX_OUT** | Plug (Output) | `adapter::types::unidirectional::AX` | Output adapter with a BOOL value. |

## Functionality

The function block internally uses the comparison function block **F_NE** ("Not Equal") from the IEC 61131 library. The process is as follows:

1. A LINT value is received via socket `ALI_IN`.
2. The event `ALI_IN.E1` triggers the function block `F_NE` via its `REQ` input.

3. In `F_NE`, the input value (`IN1`) is compared with the constant value `LINT#0` (`IN2`).

4. The result `OUT` is a BOOL:

- **TRUE** if `IN1 ≠ 0`
- **FALSE** if `IN1 = 0`
1. After the comparison is complete, `F_NE` sends a `CNF` event, which triggers the output adapter `AX_OUT` via its `E1`.
2. Simultaneously, the BOOL value is output as `AX_OUT.D1`.

Thus, any LINT value (including negative numbers) is converted into a binary signal.

## Technical Features

- **Stores the integer's bit pattern**, as expected for a bit-string destination (truncates if the destination is narrower than the source).

- **Pure Logic Conversion**: No scaling or thresholding takes place. Any non-zero value is interpreted as `TRUE`.
- **Composite Function Block Use**: The function block encapsulates the adapter conversion in a reusable unit and allows for easy integration into larger networks.
- **Event-Driven**: Processing only occurs upon an incoming event (`ALI_IN.E1`). The output is only updated after successful processing.
- **License**: The function block is licensed under the **Eclipse Public License 2.0** (EPL-2.0).

## State Overview

Since this is a composite function block without its own state machine, the state logic results from the internal chaining:

1. **Waiting for event**: The function block is inactive until `ALI_IN.E1` arrives.
2. **Comparison in progress**: After receiving the event, the `F_NE` function block is executed.
3. **Output result**: After the comparison is complete, the result is set to `AX_OUT.D1`, and `AX_OUT.E1` is triggered.

There are no loops, time delays, or error states – the function is deterministic and error-free.

## Application Scenarios

- **Signal Conversion in Control Systems**: When a LINT-based protocol (e.g., counter readings, encoders) needs to be converted into simple binary information (e.g., "active," "presence").
- **Adapter Bridges**: Used in systems that employ heterogeneous adapter types to enable communication between components with different data types.
- **Test Environments**: Fast conversion of numerical values into Boolean signals for debugging or simulation.

## Comparison with Similar Function Blocks

- **Direct Compare Function Block**: Instead of `F_NE`, a `F_EQ` (equal) followed by negation could also be used – functionally identical.
- **Threshold Function Blocks (e.g., Greater_than)**: Would require an explicit threshold; `ALI_TO_AX` makes a hard zero decision.
- **Type conversions (e.g., LINT_TO_BOOL)**: Some libraries offer primitive converters – however, these usually do not operate at the adapter level. `ALI_TO_AX` is specifically designed for adapter interfaces.

## Conclusion

The **ALI_TO_AX** function block provides a simple and reliable method for translating a LINT adapter value to a BOOL adapter value.

Thanks to its clear logic structure and event-driven architecture, it is suitable for both production use and rapid prototyping.

The use of the composite concept promotes modularity and reusability in IEC 61499-based control applications.
