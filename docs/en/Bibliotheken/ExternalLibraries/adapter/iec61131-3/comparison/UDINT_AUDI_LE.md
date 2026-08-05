# UDINT_AUDI_LE
![UDINT_AUDI_LE](./UDINT_AUDI_LE.svg)

* * * * * * * * * *
## Introduction
The function block **UDINT_AUDI_LE** compares two values and checks whether the first value (IN1) is less than or equal to the second value (IN2). The second value is provided via an adapter socket (type `AUDI`), while the result (true/false) is output via an adapter plug (type `AX`). This function block is specifically designed for processing unsigned double integers (UDINT) – or, more generally, elementary data types – and is suitable for use in IEC 61131-3 environments.

* * * * * * * * * *
## Interface Structure

### **Event Inputs**

| Event | Description |
| `REQ` | Service Request: Triggers the comparison as soon as the event occurs. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| `OUT.E1` | Acknowledgement: Sent as soon as the comparison is complete and the result is available at data output `OUT.D1`. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------------------|---------------|
| `IN1` | `ANY_ELEMENTARY` | First comparison value (e.g., UDINT by default). |

### **Data Outputs**

This function block does not have direct data outputs. The comparison result is output via the adapter plug `OUT` (see below).

### **Adapters**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| Socket (Input) | `IN2` | `adapter::types::unidirectional::AUDI` | Provides the second comparison value (e.g., via a sensor or another function block). |
| Plug (Output) | `OUT` | `adapter::types::unidirectional::AX` | Outputs the Boolean result `True` if `IN1 <= IN2` is true. |

* * * * * * * * * *
## Functionality

The function block operates in an event-driven manner. A comparison is triggered by:

- the external event `REQ` or
- an incoming event from the adapter socket `IN2` (via its event output).

Both events are routed to the internal function block `F_LE` (less or equal). The data values are then passed to this block:

- `IN1` is assigned to the first input of `F_LE`.

`` - The value from adapter `IN2` (via its data output `IN2.D1`) is assigned to the second input of `F_LE`.

The internal block `F_LE` performs the comparison and passes the result (`TRUE` or `FALSE`) via its output `OUT` to the adapter plug `OUT`. Upon completion, the event `OUT.E1` is triggered.

The internal block `F_LE` performs the comparison and passes the result (`TRUE` or `FALSE`) to the adapter plug `OUT` via its output `OUT`. The use of adapters enables modular connectivity: The socket `IN2` expects a data source (e.g., an analog input), and the plug `OUT` delivers the result to subsequent logic or actuators.

* * * * * * * * * *
## Technical Features
- **Data Type:** The input `IN1` is declared as `ANY_ELEMENTARY`, so the function block is, in principle, suitable for all elementary data types (e.g., INT, UDINT, REAL) – however, the naming convention focuses on UDINT.
- **Adapters:** Communication with external systems is handled via standardized unidirectional adapters (`AUDI` and `AX`). This enables loose coupling and reusability across different networks.
- **Internal Implementation:** The comparison is implemented using the embedded basic function block `F_LE`, which represents a typical IEC 61131-3 function.
- **Parallel Triggering:** Both the external event `REQ` and the event from the socket `IN2` can initiate the comparison; processing is deterministic.
- **Copyright:** This function block is licensed under the Eclipse Public License 2.0 and was originally developed at TU Wien.
* * * * * * * * * *
## State Overview

This function block does not have an explicit state machine. It behaves like a simple function: Each incoming event (from `REQ` or the socket) triggers a comparison, and the confirmation event is then output to the plug. The internal state is retained between events (e.g., saving the last values is not supported).

* * * * * * * * * *
## Application Scenarios
- **Limit Monitoring:** Comparison of a measured value (e.g., speed, pressure) with a threshold value defined via an adapter.
- **Range Check:** Combination with other comparison blocks (e.g., `UDINT_AUDI_GE`) to check a range of values.
- **Control Logic:** Triggering an action if a value does not exceed a maximum value.
- **Data Exchange in Modular Systems:** Use of the adapter interface for easy connection to sensors, actuators, or other control modules.
* * * * * * * * * *
## Comparison with Similar Components

| Component | Comparison Operation | Adapter Types |
|------------------|-------------------------------|----------------------------|
| `UDINT_AUDI_LE` | Less than or equal to (≤) | Socket: AUDI – Plug: AX |
| `UDINT_AUDI_LT` | Less than (<)                   | identisch                  |
| `UDINT_AUDI_EQ`  | Gleich (=)                    | identisch                  |
| `UDINT_AUDI_GT`  | Größer (>) | Equal |
| `UDINT_AUDI_GE` | Greater than or equal to (≥) | Equal |

The components differ only in their comparison operation, making them structurally interchangeable. The adapter interface remains the same, allowing for easy parameterization of the comparison type.

* * * * * * * * * *
## Conclusion

The function block `UDINT_AUDI_LE` implements an IEC 61131-3 compliant less-than-or-equal-to comparison function with a variable data source via adapters. Thanks to the use of unidirectional adapters and an internal base block, it is flexible, expandable, and ideally suited for industrial use in modular control systems. Furthermore, support for `ANY_ELEMENTARY` allows its use with various data types without requiring interface modifications.
