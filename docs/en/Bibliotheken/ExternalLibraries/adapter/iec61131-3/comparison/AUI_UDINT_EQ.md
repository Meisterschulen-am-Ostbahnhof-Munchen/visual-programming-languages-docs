# AUI_UDINT_EQ
![AUI_UDINT_EQ](./AUI_UDINT_EQ.svg)
* * * * * * * * * *
## Introduction
The function block **AUI_UDINT_EQ** performs an equality comparison between two values. The first operand is provided via an adapter input (IN1) of type `AUI`, the second via the data input `IN2` as `UDINT`. The comparison result is output as a Boolean value via an adapter output (OUT) of type `AX`. The block is designed for use in IEC 61499 systems and is based on the standard comparison block `F_EQ`.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Service Request – triggers the comparison. |

| (via adapter IN1.E1) | Event | Event from the adapter input – also triggers the comparison. |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| OUT.E1 | Event | Acknowledgement event at the adapter output, signals completion of the comparison. |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|------------|

| IN2 | UDINT | Second operand (unsigned double integer). |

| (via adapter IN1.D1) | (implicit) | First operand, type-dependent (via AUI adapter). |

### **Data Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| OUT.D1 | BOOL | Comparison result: TRUE if the values are equal, otherwise FALSE. |

### **Adapters**

| Type | Direction | Name | Comment |

|-----|----------|------|-----------|

| `adapter::types::unidirectional::AUI` | Socket (Input) | IN1 | Provides the first operand as a value (D1) and an event (E1). |

| `adapter::types::unidirectional::AX` | Plug (Output) | OUT | Outputs the comparison result as a Boolean value (D1) and a confirmation event (E1). |

## Functionality
The function block is activated either by an event at input `REQ` or by an event from adapter `IN1.E1`. Both events trigger the execution of the internal function block `F_EQ`, which checks the values of `IN1.D1` (first operand) and `IN2` (second operand) for equality. The result is output as a Boolean value via `OUT.D1`. Simultaneously, an event is sent to `OUT.E1` to signal the completion of the comparison.

## Technical Features
- **Dual Trigger Option:** The function block can be activated via the separate event input `REQ` as well as via the event `IN1.E1` received by the adapter. This allows for flexible integration: either cyclically timed or directly by the incoming AUI message.
- **Internal Use of the Standard Block `F_EQ`:** The actual comparison logic is implemented by the IEC 61131 block `F_EQ`. This ensures standards compliance and reusability.
- **Adapter-Based Input/Output:** The adapters `AUI` and `AX` enable a standardized, modular connection in 4diac architectures.

**Internal Use of the Standard Block `F_EQ`:** ## State Overview
The FB does not have its own ECC, but delegates execution to the internal `F_EQ`. Its behavior is purely event-driven:

- Upon the arrival of an event (REQ or IN1.E1), a comparison is performed once.
- After completion, the result is output via OUT.
- There are no internal states or sequential processes.

## Application Scenarios
- **Monitoring a Process Value:** Compare a measured value (e.g., rotational speed, temperature) supplied via an AUI adapter with a fixed threshold (as a UDINT) and report equality.
- **Trigger-Controlled Check:** In cyclic control tasks, the comparison can be timed via the REQ event, independent of incoming AUI messages.
- **Integration with adapter-based components:** The function block can be easily integrated into existing 4diac networks that use AUI and AX adapters.

## Comparison with similar function blocks
- **CMP_EQ (Standard Comparison):** Simple equality comparison of two data values without an adapter. In contrast, `AUI_UDINT_EQ` offers an adapter-based interface that allows loose coupling with other IEC 61499 components.
- **AUI_UDINT_GT, AUI_UDINT_LT:** Analogous function blocks for greater-than/less-than comparisons with an identical adapter structure. `AUI_UDINT_EQ` focuses specifically on equality checking.
- **Direct use of `F_EQ`:** This function block encapsulates `F_EQ` and extends it with adapter-specific event control.

## Conclusion

The `AUI_UDINT_EQ` is a compact and flexible function block for equality comparisons in IEC 61499 environments. The combination of adapter-based access to the first operand and a direct data input for the second operand, along with dual triggering capabilities, makes it highly versatile. The use of the standard function block `F_EQ` ensures robust and standards-compliant functionality.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
