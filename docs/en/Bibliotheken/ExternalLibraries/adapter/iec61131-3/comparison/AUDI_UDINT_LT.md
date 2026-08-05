# AUDI_UDINT_LT
![AUDI_UDINT_LT](./AUDI_UDINT_LT.svg)

* * * * * * * * * *
## Introduction
The function block **AUDI_UDINT_LT** performs a "less than" comparison for two values of type **UDINT** (Unsigned Double Integer). It complies with the IEC 61131-3 classification "standard comparison function". The block encapsulates an internal comparison block (F_LT) and provides a standardized, event-driven interface via adapters.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Service Request – triggers the comparison |

## **Event Outputs**
The block does not have direct event outputs. The result event is provided via the adapter plug **OUT** (event **E1**).

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| IN2 | UDINT | Input value 2 (second comparison value) |

### **Data Outputs**
The function block does not have direct data outputs. The comparison result is provided via the adapter plug **OUT** (data **D1**, type BOOL).

### **Adapter**

| Role | Name | Type | Comment |
|-------|------|-----|-----------|
| Socket | IN1 | adapter::types::unidirectional::AUDI | Input value 1 – provides event (E1) and data (D1) |
| Plug | OUT | adapter::types::unidirectional::AX | Comparison result (D1 = TRUE if IN1 < IN2) and confirmation event (E1) |

*Note:* The adapters of type **AUDI** and **AX** are unidirectional and each contains one event element (E1) and one data element (D1).

## Functionality
1. A **REQ** event starts the processing.

2. The function block reads **IN1** (via the socket adapter) and **IN2** (direct data input).

3. Internally, the function block `F_LT` ("less than" from the IEC 61131-3 comparison library) is executed:

- **F_LT.IN1** receives the value of **IN1.D1**
- **F_LT.IN2** receives the value of **IN2**
- The result (BOOL) is output to **F_LT.OUT**.

4. After the comparison is complete, **F_LT** sends an event to **OUT.E1**, and the result is output to **OUT.D1**.

This allows the calling context to asynchronously receive the comparison value and the acknowledgment event via the **OUT** adapter.

## Technical Features
- **Adapter-based interface:** Coupling is achieved via sockets and plugs, enabling loose coupling and reuse in service-oriented architectures.
- **Encapsulation of a Standard Comparison Block:** The function block internally uses the established `F_LT` block, so no custom comparison logic needs to be implemented.
- **No State Information:** The block is stateless – every call to **REQ** results in an immediate calculation.

## State Overview
The block does not have its own state machine; all logic is event-driven and stateless.

## Application Scenarios
- **Limit Monitoring:** Check whether a measured value (IN1) is below a threshold value (IN2).
- **Control Conditions:** Generate a signal when a counter variable is less than a predefined value.
- **Adapter-Based Data Flows:** Integration into complex networks where data and events are exchanged via standardized adapters.

## Comparison with Similar Function Blocks
- **AUDI_UDINT_GT** (greater than) and **AUDI_UDINT_EQ** (equal to) offer analogous comparisons for UDINT.
- Unlike direct IEC operators (e.g., `IN1 < IN2` in ST), this function block enables event-driven and component-oriented integration into 4diac networks.
- Other comparison blocks without adapters (e.g., `F_LT`) can be used directly but do not offer a standardized adapter interface.

## Conclusion
The **AUDI_UDINT_LT** is a specialized comparison block for the UDINT data type, characterized by its adapter-based event and data transmission. It is particularly suitable for modular control applications that require loose coupling and reusability.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
