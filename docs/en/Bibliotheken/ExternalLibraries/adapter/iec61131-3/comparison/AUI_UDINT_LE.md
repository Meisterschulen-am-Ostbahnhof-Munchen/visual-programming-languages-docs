# AUI_UDINT_LE
![AUI_UDINT_LE](./AUI_UDINT_LE.svg)
* * * * * * * * * *
## Introduction
The function block `AUI_UDINT_LE` performs a less-than-equal-to comparison between two UDINT values. The first value is provided via a unidirectional adapter interface (AUI), and the second value is directly inputted as a data input. The result of the comparison is output via a unidirectional output adapter (AX).
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| `REQ` | Event | Service Request; triggers the comparison. The data value `IN2` is read at this time. |

### **Event Outputs**

This function block does not have direct event outputs. Result notification is provided via the event output of the output adapter `OUT.E1`.

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| `IN2` | UDINT | Second input value for comparison. |

### **Data Outputs**

This function block does not have direct data outputs. The comparison result is provided via the data output `OUT.D1` of the output adapter.

### **Adapters**

| Name | Type | Direction | Comment |

|------|-----|----------|-----------|

| `IN1` | AUI (adapter::types::unidirectional::AUI) | Socket | Input adapter for the first comparison value (UDINT). |

| `OUT` | AX (adapter::types::unidirectional::AX) | Plug | Output adapter for the comparison result (BOOL). |

## Functionality
This function block implements the function `IN1 ≤ IN2`. Internal processing:

- The event input `REQ` or the incoming event `IN1.E1` (via the socket adapter) triggers the internal function block `F_LE` (IEC 61131-3 comparison `LE`).

`` - The data values `IN1` (via adapter) and `IN2` (directly) are fed to the internal function block.

- The result (BOOL) is output via the output adapter `OUT` as soon as the internal function block has completed its calculation (`F_LE.CNF` → `OUT.E1`).

## Technical Features
- **Adapter-based communication**: The first value (IN1) is not provided as a classic data input, but via a unidirectional adapter interface (AUI). This enables loose coupling in distributed systems.
- **Result output via adapter**: The comparison result is also output via an adapter (AX), which allows for flexible further processing.
- **Standard Comparison Function**: The underlying algorithm is based on the established IEC 61131-3 function block `F_LE` for `Less_or_Equal`.

## State Overview
The function block itself does not have its own state machines. The internal logic is determined by the state of the embedded function block `F_LE`, which performs a calculation after each event and outputs the result without delay.

## Application Scenarios
- **Limit Monitoring**: Checking whether a value received via an interface (e.g., a sensor value) does not exceed a defined threshold.
- **Control Logic**: Used in complex sequence control systems where conditions like `Wert1 ≤ Wert2` are part of a decision chain.
- **Distributed Systems**: Use the adapters to compare values from different components of a controller without requiring direct data lines.

## Comparison with Similar Function Blocks
- **`AUI_UDINT_GT`** (greater than): Performs the comparison with `IN1 > IN2`.
- **`AUI_UDINT_EQ`** (equal): Checks for equality.
- **`AUI_UDINT_NE`** (not equal): Checks for inequality.

These function blocks have an identical interface structure and differ only in their comparison function. The function block `LE` is specifically designed for the "less than or equal to" condition.

## Conclusion
The `AUI_UDINT_LE` function block is a specialized comparison function block for the UDINT data type with adapter connectivity. It is particularly suitable for modular and distributed control systems where values are exchanged via standardized interfaces. Adherence to IEC 61131-3 ensures interoperability and maintainability.
