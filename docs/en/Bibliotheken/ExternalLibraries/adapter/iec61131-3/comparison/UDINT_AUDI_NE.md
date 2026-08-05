# UDINT_AUDI_NE
![UDINT_AUDI_NE](./UDINT_AUDI_NE.svg)
*(No image available)*

* * * * * * * * * *
## Introduction
The function block **UDINT_AUDI_NE** compares two values for inequality ("not equal"). It is implemented as a composite block and uses adapters for the second input and output to enable flexible integration with other components. The block is designed for use in automation systems based on the 4diac IDE.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-------|------------------|

| REQ | Event | Service Request |

The event input **REQ** triggers the comparison process.

### **Event Outputs**

No explicit event outputs. The results are output via the **OUT** adapter (see section Adapters).

### **Data Inputs**

| Name | Type | Comment |

|------|-----------------|------------------|

| IN1 | ANY_ELEMENTARY | Input value 1 |

The **IN1** data input receives the first value to be compared. The second value is provided via the **IN2** socket.

### **Data Outputs**

No direct data outputs. The comparison result (Boolean value: TRUE for inequality, FALSE for equality) is output via the **OUT** adapter.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|------------------------------|------------------------------------|

| Plug | OUT | `adapter::types::unidirectional::AX` | Output: TRUE if IN1 != value of IN2 |

| Socket | IN2 | `adapter::types::unidirectional::AUDI` | Input for the second value |

- **OUT** (Plug) transmits the result as a Boolean value via the data field `D1` and is controlled by the event `E1`.
- **IN2** (Socket) provides the second comparison value via the data field `D1` and the event `E1` (e.g., to trigger the comparison).

## Functionality

This function block performs an inequality comparison between two values:

1. The **REQ** event input or the **IN2.E1** event starts the comparison.

2. Internally, the function block **F_NE** (type `iec61131::comparison::F_NE`) is used to check the two values **IN1** and **IN2.D1** for inequality.

3. The result (Boolean value) is output via **OUT.D1**.

4. The output adapter **OUT** signals via its event **E1** that the result is valid.

The control is event-driven: The comparison is triggered either by the external event **REQ** or by the event **IN2.E1** from the adapter (OR operation). This allows the function block to operate both cyclically and in a data-driven manner.

## Technical Features
- **Adapter-based Input/Output:** The second input and the output are implemented as adapters. This enables loose coupling and reusability in different contexts.
- **Support for any elementary data types:** The data input **IN1** is of type `ANY_ELEMENTARY`, so the function block can work with all IEC 61131-3 elementary data types (e.g., INT, REAL, BOOL). The adapter **IN2** should provide a compatible data type.
- **Reusability:** The function block is defined as a composite and internally uses the standardized comparison function block **F_NE**. Modifying the comparison logic is possible by replacing the internal function block.
- **Copyright:** The function block is subject to the Eclipse Public License 2.0.

## State Overview

The function block does not have an explicit state machine. It behaves like a functional unit:

- **Waiting:** The function block waits for an event at **REQ** or **IN2.E1**.

**Reusability:** - **Compare:** As soon as an event occurs, the comparison is performed.

- **Output:** The result is output via **OUT** and the event **OUT.E1** is triggered.

The block then returns to the wait state.

## Application Scenarios
- **Inequality Check in Control Logic:** Monitoring whether a process value deviates from a setpoint.
- **Signal Comparison in Communication Interfaces:** Comparing two measured values from different sources.
- **Enable Conditions:** Triggering an action if two input signals are not identical (e.g., in safety applications).
- **Adapter-Coupled Systems:** Integration into modular automation projects that rely on adapters for signal forwarding.

## Comparison with Similar Blocks

| Block | Function | Difference to UDINT_AUDI_NE |

--------------------|--------------------------------|-----------------------------------------------------------------|

F_EQ` | Equality Comparison | Checks for equality, not inequality |

| `F_LT`, `F_GT` | Less Than/Greater Than Comparison | Perform order comparisons, not inequality checks |

| `UDINT_AUDI_EQ` | Equality with Adapters | Same adapter interface, but compares for equality |

The **UDINT_AUDI_NE** is specifically designed for inequality comparison with adapter interfaces and complements the family of adapter-based comparison blocks.

## Conclusion

**UDINT_AUDI_NE** is a flexible and reusable function block for inequality comparison. By using adapters for the second input and output, it can be easily integrated into complex automation networks. Support for any elementary data type and event-driven execution make it a versatile tool for a wide range of applications. Its composite structure also allows for easy customization of the comparison logic as needed.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
