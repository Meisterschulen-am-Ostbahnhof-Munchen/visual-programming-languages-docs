# UDINT_AUI_NE
![UDINT_AUI_NE](./UDINT_AUI_NE.svg)

* * * * * * * * * *
## Introduction
The function block **UDINT_AUI_NE** compares two values for inequality ("not equal"). It is classified as a standardized comparison function according to IEC 61131-3 and uses adapter interfaces for the second input and the result. The block is asynchronously event-driven: An event at the **REQ** input triggers the comparison, and the result is output via the output adapter.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-------|-------------------|
| REQ | Event | Service Request |

- **REQ**: Starts the comparison. The input **IN1** is compared with the value of **IN2**. The function block expects the corresponding data value to be present at **IN1** and the second value to be present via adapter **IN2** before the event is triggered.

### **Event Outputs**

The function block does not have any independent event outputs. The result is signaled via adapter **OUT** (see section **Adapters**).

### **Data Inputs**

| Name | Type | Comment |
|------|------------------|--------------------------|
| IN1 | ANY_ELEMENTARY | Input value 1 |

- **IN1**: First value to be compared. The data type is generic (`ANY_ELEMENTARY`), so elementary types such as BOOL, INT, REAL, UDINT, etc., can be used.

### **Data Outputs**

The function block does not have any independent data outputs. The comparison result is output via the **OUT** adapter.

### **Adapter**

| Direction | Name | Adapter Interface Type | Comment |
|----------|------|------------------------------------------------|-------------------------------|
| Socket | IN2 | `adapter::types::unidirectional::AUI` | Input Value 2 |
| Plug | OUT | `adapter::types::unidirectional::AX` | value 1 != value2 = true |

- **IN2** (Socket): Receives the second comparison value via a unidirectional adapter of type `AUI`. The connected adapter must provide an elementary value.
- **OUT** (Plug): Outputs the Boolean result of the comparison. The adapter type `AX` signals `true` if `IN1 != Wert von IN2` is present, and `false` otherwise.

## Functionality

The function block operates internally with the predefined function block **F_NE** (from the library `iec61131::comparison`). The process is as follows:

1. An event at input **REQ** activates the comparison. Simultaneously, the value must be present at **IN1**.

2. The second value is provided via socket **IN2**. The internal function block **F_NE** receives an event from **IN2.E1** as well as from **REQ** (both event sources are connected to **F_NE.REQ**).

3. **F_NE** compares the two data values (**IN1** and **IN2.D1**) and outputs the result to its output **OUT** (boolean).

4. The output event **F_NE.CNF** is forwarded to the plug **OUT.E1**. The output data (**OUT.D1**) contains the comparison result.

Thus, after each **REQ** event (or an event from **IN2**), the result at the adapter **OUT** is updated.

## Technical Features
- **Generic Data Types:** The input **IN1** is declared as `ANY_ELEMENTARY`, making the function block compatible with all elementary data types. The second input is provided via the adapter **IN2** – this must also correspond to the same elementary data type.
- **Adapter Interfaces:** The function block uses adapters only for the second input and the output. This enables a modular, type-safe connection in the 4diac IDE.
- **Asynchronous Event Control:** The comparison is triggered by events. The result is output via the adapter in an event-driven manner – there is no continuous data output.
- **Internal Standard Implementation:** The function block uses the IEC 61131-3 compliant comparison function block **F_NE**, which ensures correctness and compliance with the standard.

## State Overview

The function block does not have an explicit state machine. Its behavior can be described as follows:

- **Idle State:** No event is present at **REQ** or **IN2**.
- **Comparison Active:** As soon as an event is received at **REQ**, the internal function block **F_NE** starts the comparison. The result is output at the output adapter **OUT** after a short processing time.
- **Result Ready:** The output **OUT** returns `true` or `false` and is acknowledged by the event **OUT.E1**.

The function block is ready for the next comparison as soon as the result has been output.

## Application Scenarios
- **Inequality Check in Control Sequences:** Monitors whether two measured values (e.g., temperature, pressure) differ from each other.
- **State Comparison:** Checks whether a setpoint deviates from an actual value in order to trigger switching or alarm functions.
- **Data Validation:** Compares input data from different sources for inconsistencies.

## Comparison with Similar Function Blocks
- **F_E (Equal) / UDINT_AUI_EQ:** Performs an equality comparison. The difference lies in the inverted result.
- **F_LT, F_GT:** Perform less-than and greater-than comparisons, respectively, but yield different logical results.
- **Custom Implementation without Adapters:** Comparison blocks without adapters use direct data inputs; the **UDINT_AUI_NE** is specifically designed for use in adapter-based architectures.

## Conclusion

The **UDINT_AUI_NE** function block is a standards-compliant, event-driven inequality comparison for elementary data types. Its unique feature lies in the use of adapter interfaces for the second input and the result, enabling flexible and type-safe integration into modular 4diac networks. It is ideally suited for applications that require a response to the inequality of two values.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
