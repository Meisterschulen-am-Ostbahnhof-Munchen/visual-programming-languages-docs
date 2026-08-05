# AUI_UDINT_GT
![AUI_UDINT_GT](./AUI_UDINT_GT.svg)

* * * * * * * * * *
## Introduction
The function block `AUI_UDINT_GT` performs a comparison of two unsigned 32-bit integers (UDINT) to determine if they are "greater than". This function block belongs to the IEC 61131-3 family of comparison functions and is specifically designed for use with adapter interfaces (unidirectional). The processing is triggered by an incoming event.
## Interface Structure
### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| `REQ` | Event | Service Request – triggers the comparison operation. Expects a valid value at `IN2`. |

### **Event Outputs**
No direct event outputs. The result is output via the `OUT` adapter.

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| `IN2` | UDINT | Second input value for comparison (value 2). |

### **Data Outputs**
No direct data outputs. The comparison result is output via the `OUT` adapter.

### **Adapters**

| Name | Type | Direction | Comment |
|------|-----|----------|-----------|
| `IN1` | `adapter::types::unidirectional::AUI` | Socket | Receiving adapter – provides the first input value (value 1) and a trigger event. |
| `OUT` | `adapter::types::unidirectional::AX` | Plug | Outputting adapter – outputs the comparison result (Boolean value) and an acknowledgment event. |

## Functionality
This function block compares the two input values `IN1` and `IN2` according to the **greater than** relationship.

- The value `IN1` is obtained via the adapter `IN1` (socket).
- The value `IN2` is directly assigned to the data input `IN2`.
- An event at `REQ` or an event arriving via the adapter triggers the processing.
- Internally, the actual comparison is performed by the function block `F_GT`.
- The result (`TRUE` if `IN1 > IN2`, otherwise `FALSE`) is output via the adapter `OUT` (plug), accompanied by an event at its E1 input.

## Technical Features
- **Adapter-Based Communication:** The module encapsulates input and output in unidirectional adapters. This allows it to be easily integrated into complex component networks without direct data or event connections at any level.
- **Internal Sub-Module:** The processing logic is not implemented by the module itself, but rather by the standardized `F_GT` module from the IEC 61131-3 library.
- **Typing:** All data is of type `UDINT` – unsigned 32-bit integers according to IEC 61131-3.
- **Parallel Triggering:** Both the `REQ` event and the event from the `IN1` adapter can initiate the operation. This enables flexible control patterns.

## State Overview
The function block does not have its own explicit state machine. Its behavior is purely event-driven:

- **Initial:** Wait for an event at `REQ` or via `IN1.E1`.
- **Processing:** After an event and valid data are received, the comparison is performed.
- **Output:** Immediately after completion, the result is output via `OUT` along with an event.

Input and output data are not cached; the function block operates in pure combinational mode.

## Application Scenarios
- **Limit Monitoring:** Check whether a measured value (e.g., speed, fill level) exceeds a predefined threshold.
- **State Control:** Trigger an action when a counter variable is greater than a limit.
- **Sequential Flow Control:** Determining the parent index or priority in a flow chain.
- **Adapter-Based Components:** Integrating this function block into a component library that communicates via standardized adapters (e.g., using the 4diac IDE approach).

## Comparison with Similar Function Blocks

| Function Block | Function | Adapter Type |
|----------|----------|------------|
| `AUI_UDINT_GT` | `IN1 > IN2` | AUI (Socket), AX (Plug) |
| `AUI_UDINT_LT` | `IN1 < IN2` | Analog |
| `AUI_UDINT_EQ` | `IN1 = IN2` | analog |
| `AUI_UDINT_GE` | `IN1 >= IN2` | analog |
| `AUI_UDINT_LE` | `IN1 <= IN2` | analog |
| `AUI_UDINT_NE` | `IN1 != IN2` | analog |

This block series represents the complete set of six comparison operators and differs only in the selected comparison function. The interface is identical, allowing for interchangeability without changing the connections.

## Conclusion
AUI_UDINT_GT` is a specialized yet flexible comparison block for industrial applications. The use of adapters simplifies integration into modular automation systems and makes the interface reusable. Thanks to its IEC 61131-3 compliance and simple internal structure, it is particularly well-suited for clear, maintainable control logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
