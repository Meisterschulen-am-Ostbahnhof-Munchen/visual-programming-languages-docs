# F_SEL_E_3
![F_SEL_E_3](https://github.com/user-attachments/assets/7dbef3ab-5e30-406e-8013-d5f2bfadb120)
* * * * * * * * * *
## Introduction
The function block `F_SEL_E_3` is an event-based selector that selects one of three input variables based on the triggering event and passes it to the output. It is part of the `eclipse4diac::utils::selection` package and complies with the IEC 61131-3 standard for standard selection functions.
![F_SEL_E_3](F_SEL_E_3.svg)

## Interface Structure

### **Event Inputs**
- `REQ0`: Selects the input variable `IN0`
- `REQ1`: Selects the input variable `IN1`
- `REQ2`: Selects the input variable `IN2`

### **Event Outputs**
- `CNF`: Confirms the execution of the selection and returns the selected value

### **Data Inputs**
- `IN0`: First selectable input variable (Type: ANY)
- `IN1`: Second selectable input variable (Type: ANY)
- `IN2`: Third selectable input variable (Type: ANY)

### **Data Outputs**
- `OUT`: Selected input variable (Type: ANY)

### **Adapters**
No adapters available.

## Functionality
The function block waits for an incoming event (`REQ0`, `REQ1`, or `REQ2`). Upon the occurrence of such an event, the corresponding input variable (`IN0`, `IN1`, or `IN2`) is selected and forwarded to the output `OUT`. Simultaneously, the acknowledgment event `CNF` is triggered.

When such an event occurs, the corresponding input variable (`IN0`, `IN1`, or `IN2`) is selected and forwarded to the output `OUT`. ## Technical Features
- Supports the ANY data type for maximum flexibility
- Event-based triggering for deterministic behavior
- Simple and direct selection without additional logic

## State Overview
1. Waiting state: No active event
2. Selection state: Event received, corresponding input selected
3. Acknowledgement state: Output updated and CNF event triggered

## Application Scenarios
- Selection between different sensor data streams
- Switching between operating modes
- Multiplexing of data sources in control systems
- Implementation of priority logic

## ⚖️ Comparison with Similar Function Blocks
- Unlike `F_SEL_E_2`, this function block offers three inputs instead of two
- Similar to `F_MUX`, but with event-based instead of data-driven selection
- More complex than simple gates, but more specialized for selection tasks

## 🛠️ Related Exercises
* [Exercise_015a](../../../../Uebungen/test_B/Uebungen_doc/Uebung_015a.md)
* [Exercise_016a](../../../../Uebungen/test_B/Uebungen_doc/Uebung_016a.md)

## Conclusion
The `F_SEL_E_3` is an efficient and flexible component for applications that require event-driven switching between three different data sources. Its simple interface and support for any data type make it a versatile tool in automation technology.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
