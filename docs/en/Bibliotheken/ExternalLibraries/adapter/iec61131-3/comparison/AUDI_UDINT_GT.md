# AUDI_UDINT_GT
![AUDI_UDINT_GT](./AUDI_UDINT_GT.svg)
* * * * * * * * * *
## Introduction
The function block `AUDI_UDINT_GT` performs a comparison of two unsigned 32-bit integers (UDINT). It checks whether the value of an input (IN1) provided via an adapter socket is greater than a second value (IN2) passed directly as a data input. The result is output via an adapter plug. The block implements the **GREAT AS** comparison operator specified in IEC 61131-3.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |

|------|-------|----------------------------------------------|

| REQ | Event | Service Request to trigger the comparison. This event reads data input IN2. |

### **Event Outputs**

The FB does not have its own event outputs. However, the result of the comparison is signaled via the adapter plug `OUT` (see section Adapters).

### **Data Inputs**

| Name | Type | Description |

|------|-------|-----------------------|

| IN2 | UDINT | Second comparison value (right side of the operator >). |

### **Data Outputs**

The FB does not have its own data outputs. The result value is provided via the adapter plug `OUT` (see section Adapters).

### **Adapters**

| Type | Name | Kind | Description |

|------------|------|-------|------------------------------------------------------------------------------------------|

| Socket (IN1) | AUDI | Socket | Provides the first comparison value. This adapter provides an event input (E1) and a data input (D1). |

| Plug (OUT) | AX | Plug | Outputs the comparison result. This adapter has an event output (E1) and a data output (D1). The result is **TRUE** if IN1 > IN2, otherwise **FALSE**. |

## Functionality

1. The module waits for a **REQ event**.

2. Upon receipt of REQ, the current values of IN2 (direct data input) and IN1 (via the adapter socket) are read.

3. Internally, the predefined function block `F_GT` (IEC 61131-3 "Greater Than") is activated. This compares the two UDINT values.

4. The result of the comparison (Boolean value) is output via the adapter plug `OUT`. A corresponding event signals the availability of the result on the adapter output.

5. The function block then returns to the wait state and can be triggered again via REQ.

## Technical Features
- **Adapter-based interface:** The function block uses 4diac's proprietary adapter technology to flexibly encapsulate inputs and outputs. The adapters `AUDI` and `AX` correspond to the standard unidirectional types.
- **IEC 61131-3 Compliance:** The comparison is implemented using the standardized function block `F_GT`, ensuring reusability and interoperability.
- **Implicit Event Chaining:** By coupling the internal `F_GT` with the output adapter, the event-data relationship is automatically established – no manual linking of output events is required.
- **Type Safety:** Both comparison values must be of type `UDINT`. The function block does not perform any implicit type conversions.

## State Overview

The function block does not have an explicit state machine. It operates in an event-driven manner:

- **Idle:** Waiting for the **REQ** event.
- **Processing:** After REQ, the values are read, the internal `F_GT` is processed, and the result is output via the OUT adapter. The state is exited immediately after the output is complete.

The internal execution of `F_GT` is carried out in one step according to its specification.

## Application Scenarios
- **Threshold Monitoring:** Monitor whether a process value (via IN1) exceeds a limit value (via IN2).
- **Quality Control:** Check whether a count or a measured value exceeds a predefined target value.
- **Sequence Controls:** Activate subsequent logic steps when a specific numerical range is exceeded.
- **Safety Functions:** Trigger alarms when a measurable parameter (e.g., temperature, pressure) exceeds a maximum permissible value.

## Comparison with Similar Function Blocks

| Function Block | Comparison Operation | Data Type Support |

-------------------|--------------------------------|------------------------------------|

| `AUDI_UDINT_GT` | > (Greater than) | UDINT (32-bit, unsigned) |

| `AUDI_UDINT_GE` | >= (Greater than or equal to) | UDINT |

| `AUDI_UDINT_EQ` | = (Equal to) | UDINT |

| `AUDI_UDINT_LT` | < (Kleiner als)                | UDINT                              |
| `F_GT` (direkt)   | > (Greater than) | UDINT (and other supported types) |

The difference compared to directly using `F_GT` lies in the adapter-based encapsulation: `AUDI_UDINT_GT` expects the initial value via a socket adapter, enabling modular and reusable integration within project frameworks.

## Conclusion

The function block `AUDI_UDINT_GT` offers a standardized and type-safe way to implement a "greater than" comparison for unsigned 32-bit integers. Its adapter interface allows for seamless integration into IEC 61131-3 compliant automation projects and makes it particularly suitable for threshold comparisons and monitoring functions. Internal use of the standardized function block `F_GT` ensures deterministic and portable behavior.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
