# AUDI_UDINT_LE
![AUDI_UDINT_LE](./AUDI_UDINT_LE.svg)

* * * * * * * * * *
## Introduction
The function block `AUDI_UDINT_LE` performs a less-than-equal-to comparison. It compares two values of type `UDINT` – a value provided via an adapter input and a direct data input – and outputs the result via an adapter output. The block is event-driven and is classified as a standard comparison function according to IEC 61131-3.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| `REQ` | Event | Service Request – triggers the comparison operation |

- The event input `REQ` is linked to the data input `IN2` (`With Var="IN2"`), meaning the value of `IN2` is required for processing.

### **Event Outputs**

The function block does not have its own event output on the top-level interface. Instead, the result is signaled via the adapter output `OUT`. The internal event output `CNF` of the embedded comparison block is directly routed to the event input of the output adapter.

### **Data Inputs**

| Name | Type | Comment |
|------|-----|------------|
| `IN2` | UDINT | Input value 2 – the right operand of the comparison |

### **Data Outputs**

This function block has no direct data outputs. The comparison result (Boolean value) is provided via the adapter `OUT`.

### **Adapters**

| Type | Name | Role | Comment |
|-----|------|-------|-----------|
| `adapter::types::unidirectional::AUDI` | `IN1` | Socket (Input adapter) | Input value 1 – provides the left operand of the comparison |
| `adapter::types::unidirectional::AX` | `OUT` | Plug (Output adapter) | Comparison result: `IN1 <= IN2` (true/false) |

- The adapter `IN1` provides not only the data value but also an event (`E1`) that is connected to the internal comparison block.
- The adapter `OUT` receives an event (`E1`) and the data value (`D1`) containing the result.

## Functionality

1. When a signal is applied to the event input `REQ`, the embedded function block `F_LE` (less or equal) is started.

2. The data value of the adapter input `IN1.D1` and the direct data input `IN2` are passed to `F_LE.IN1` and `F_LE.IN2`, respectively.

3. The internal function block performs the comparison `IN1 ≤ IN2` and outputs the result (typically `TRUE` or `FALSE`) to its output `OUT`.

4. After processing is complete, `F_LE` sends an event via its output `CNF`. This event is forwarded to the output adapter `OUT.E1`, so that the downstream function block is informed of the completion and the result.

- Event control can be achieved via the external event input `REQ` or via the event `IN1.E1` coming from the adapter `IN1` (both are connected to `F_LE.REQ`). This allows for flexible control.

## Technical Features
- **Adapter-based interface:** The function block uses standardized unidirectional adapters (`AUDI` and `AX`), which allow loose coupling between the connected function blocks. The data type `UDINT` is transmitted transparently via the adapter interface.
- **Reuse of Standard Function Blocks:** The actual comparison logic is implemented using the internal `F_LE` function block from the IEC 61131-3 library. This increases maintainability and consistency.
- **Event Linking:** The output adapter is supplied with both the result data value and an acknowledgment event, so the receiving function block knows the time of data transfer.
- **No State of Its Own:** The function block is stateless; processing is performed anew with each event.

## State Overview

The function block does not have an explicit state machine. Its behavior is purely combinatorial: The comparison is executed once with each event input. There is no internal memory or timing dependencies.

## Application Scenarios
- **Limit Monitoring:** Checks whether an actual value supplied via a sensor adapter (e.g., `AUDI`) is less than or equal to a setpoint (`IN2`). The result can, for example, represent an alarm limit or a release condition.
- **Control Logic:** Used in conjunction with other function blocks when a condition "Value1 ≤ Value2" is required as part of an interlock or sequence control.
- **Data Filter:** Selects values that must not exceed an upper limit.

## Comparison with Similar Function Blocks
- **Direct Comparison Function Block `F_LE`:** Unlike the simple `F_LE` function block, `AUDI_UDINT_LE` offers an adapter interface that enables modular integration into adapter-based networks and ensures type compatibility through specific adapter types.
- **Other Comparison Function Blocks (e.g., `LT`, `EQ`, `GT`):** These differ only in the comparison operation. The architecture with adapters and event handling is identical.
- **Adapter blocks without internal comparison:** `AUDI_UDINT_LE` combines data provision via adapters with a fixed comparison function, resulting in a compact, reusable block.

## Conclusion

AUDI_UDINT_LE` is a clear and efficient function block for comparing "less than or equal to" two `UDINT` values. By using standardized adapters and a proven core block, it is robust, expandable, and easily integrated into industrial control environments. Its simple interface and stateless behavior make it particularly suitable for safety-related and modular automation solutions.
