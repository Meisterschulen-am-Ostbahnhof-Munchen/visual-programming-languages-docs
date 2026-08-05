# AUDI_NE
![AUDI_NE](./AUDI_NE.svg)

* * * * * * * * * *
## Introduction
The function block **AUDI_NE** performs a not equal check. It compares two input values provided via adapters and outputs the comparison result as a Boolean value via an output adapter. This block is primarily used in automation systems that support adapter-based, event-driven communication.
## Interface Structure

### **Event Inputs**

The function block does not have separate event inputs on the interface itself. Events are transmitted via the adapter sockets **IN1** and **IN2**. Each of these sockets contains an event input (E1), the arrival of which triggers the internal comparison.

### **Event Outputs**

The output adapter **OUT** provides an event output (E1). This signals the completion of the comparison and indicates that the result at the data output is valid.

### **Data Inputs**
- **IN1.D1** – First value to be compared (data type depends on the adapter definition `adapter::types::unidirectional::AUDI`).
- **IN2.D1** – Second value to be compared (same data type as IN1).

### **Data Outputs**
- **OUT.D1** – Boolean result of the inequality check: `TRUE` if IN1 != IN2, otherwise `FALSE`.

### **Adapter**

| Adapter | Type | Direction | Description |
|---------|-----|----------|--------------|
| IN1 | `adapter::types::unidirectional::AUDI` | Socket | Captures the first input value |
| IN2 | `adapter::types::unidirectional::AUDI` | Socket | Receives the second input value |
| OUT | `adapter::types::unidirectional::AX` | Plug | Outputs the comparison result |

## Functionality

The **AUDI_NE** is a composite function block. Internally, it uses the standardized comparison block **F_NE (Not Equal)** from the IEC 61131 library.

- If an event occurs at **IN1.E1** or **IN2.E1**, the signal is forwarded to the internal block **F_NE.REQ**.
- Simultaneously, the current data values from **IN1.D1** and **IN2.D1** are transferred to **F_NE.IN1** and **F_NE.IN2**.

`` - **F_NE** performs the inequality comparison and outputs the result via **F_NE.OUT** and an acknowledgment event via **F_NE.CNF**.

- The acknowledgment event is passed to **OUT.E1**, and the result to **OUT.D1**.

The function block (FB) thus operates in an event-driven manner: Each event at either of the two inputs triggers a new comparison, and the output is updated immediately.

## Technical Features
- **Adapter-based interface**: Adapters are used instead of discrete inputs/outputs. This enables a type-safe and modular connection with other function blocks that use the same adapter protocol.
- **Two independent event sources**: Both IN1 and IN2 can provide an event. The internal behavior is designed so that a new comparison is started after each event – regardless of the source.
- **Reuse of Standardized Logic**: The actual comparison function is implemented by the embedded FB **F_NE**, ensuring high reliability and compliance with IEC 61131.

## State Overview

The FB has no explicit states (no ECC). It is a combinational block without memory. The output is determined solely by the current input values and the triggering event.

## Application Scenarios
- **Deviation Monitoring**: Checks whether two measured values (e.g., setpoint and actual values) differ. The result can be used for alarming or control.
- **Redundancy Check**: In safety-critical systems, the discrepancy between two redundant sensors can indicate a fault.
- **State Comparisons**: Compares binary states or count values to detect changes or inconsistencies.

## Comparison with Similar Function Blocks
- **AUDI_EQ (Equal)**: The counterpart for equality checking. Same interface, but inverted logic: Output `TRUE` on equality.
- **Direct Use of F_NE**: Without the adapter wrapper, F_NE could be used directly. However, **AUDI_NE** offers a standardized adapter interface that improves integration and type safety in frameworks like 4diac.

## Conclusion

The **AUDI_NE** is a practical function block for non-equal comparison in adapter-based IEC 61131 systems. By using adapters and embedding the proven **F_NE** function block, it combines type safety with established functionality. It is particularly suitable for event-driven automation solutions where modular and reusable components are required.

**AUDI_NE** ---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
