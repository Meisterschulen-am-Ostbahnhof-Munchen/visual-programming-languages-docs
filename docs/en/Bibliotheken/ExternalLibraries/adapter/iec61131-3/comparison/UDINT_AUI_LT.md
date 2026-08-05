# UDINT_AUI_LT
![UDINT_AUI_LT](./UDINT_AUI_LT.svg)
* * * * * * * * * *
## Introduction
The function block **UDINT_AUI_LT** performs the "less than" comparison. It checks whether the value at input **IN1** is less than the value at adapter input **IN2**. The result (BOOL) is provided via the output adapter **OUT**. The use of IEC 61131-3 adapters enables flexible and modular integration with the environment.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| **REQ** | Event | Service Request – triggers the comparison (connected to IN1) |

### **Event Outputs**

*(No direct event outputs; the result event is provided via the OUT adapter)*

### **Data Inputs**

| Name | Data Type | Comment |

|------|----------|-----------|

| **IN1** | ANY_ELEMENTARY | First comparison value |

### **Data Outputs**

*(No direct data outputs; the result value is provided via the OUT adapter)*

### **Adapters**

| Direction | Name | Adapter Type | Comment |

|----------|------|------------|-----------|

| Input (Socket) | **IN2** | `adapter::types::unidirectional::AUI` | Second comparison value (triggered via the adapter's event E1) |

| Output (Plug) | **OUT** | `adapter::types::unidirectional::AX` | Result (TRUE if IN1 < IN2, otherwise FALSE) – provided via event E1 and data D1 |

## Functionality
The function block is built as an internal network from the base function block **F_LT** (type `iec61131::comparison::F_LT`).

- An event at **REQ** or at the adapter input **IN2.E1** triggers the internal F_LT via its event input **REQ**.
- The data values **IN1** and **IN2.D1** are forwarded to the corresponding data inputs of F_LT.
- F_LT performs the comparison `IN1 < IN2` and outputs the result (BOOL) to **OUT.D1**.

``` - After a successful comparison, the event **OUT.E1** is activated.

## Technical Features
- The function block uses the IEC 61131-3 adapters **AUI** (unidirectional input) and **AX** (unidirectional output). This allows the function block to be easily integrated into existing adapter network-based architectures.
- The data type **ANY_ELEMENTARY** allows the processing of all elementary types (BOOL, INT, REAL, …) – the actual type is determined at runtime.
- There is no separate state management; the logic is fully implemented by the internal **F_LT**.

## State Overview
The function block does not have its own state machine. Execution is purely event-driven:

- **Waiting for Event**: No comparison is active.
- **Comparison Active**: After the arrival of **REQ** or **IN2.E1**, the internal F_LT is executed.
- **Output**: After the comparison is complete, **OUT.E1** is triggered and the result is provided to **OUT.D1**.

## Application Scenarios
- **Limit Monitoring**: Checking whether a measured value (e.g., temperature, pressure) is below a setpoint.
- **Control Logic**: Conditions such as "If sensor value < threshold, then switch on actuator."
- **Modular Automation**: Integration into existing adapter structures without additional conversion blocks.

## Comparison with Similar Blocks

| Block | Comparison Type | Special Feature |

|----------|---------------|--------------|

| **F_LT** | less than | Direct inputs/outputs, no adapter |

| **UDINT_AUI_LT** | less than | Adapter for second input and output, modular coupling |

| **F_LE** | less or equal | Comparison ≤ |

This function block differs from **F_LT** in its exclusive use of IEC adapters, which simplifies integration into adapter-based components (e.g., services).

## Conclusion

**UDINT_AUI_LT** represents a compact and flexible solution for "less than" comparisons in IEC 61131-3 systems. The adapter interfaces enable a clean separation of event and data flows and allow for easy integration into complex automation networks. Support for basic data types makes the function block highly versatile.
