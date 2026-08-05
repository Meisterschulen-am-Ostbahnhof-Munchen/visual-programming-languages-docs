# AR_TO_AUI
![AR_TO_AUI](./AR_TO_AUI.svg)
* * * * * * * * * *
## Introduction
The function block **AR_TO_AUI** is a composite function block (FB) that implements a uniform and bidirectional conversion from an AR adapter (REAL) to an AUI adapter (UINT). It encapsulates the type conversion and simplifies communication between components that use different data types via adapters.
## Interface Structure

### **Event Inputs**
- **AR_IN.E1** – Conversion trigger: This event is received by the connected AR adapter and starts the conversion of the REAL value.

### **Event Outputs**
- **AUI_OUT.E1** – Conversion completion: After successful conversion, this event is sent to the AUI adapter.

### **Data Inputs**
- **AR_IN.D1** – REAL input value: The floating-point value (REAL) to be converted, provided via the AR adapter.

### **Data Outputs**
- **AUI_OUT.D1** – UINT output value: The result of the conversion (UINT) is passed to the AUI adapter via this data output.

### **Adapters**
- **AR_IN** – Socket of type `AR` (unidirectional REAL adapter)
- **AUI_OUT** – Plug of type `AUI` (unidirectional UINT adapter)

The adapters each combine an event signal and a data signal, so the function block offers a clean, type-safe interface.

## Functionality

1. An incoming event on **AR_IN.E1** triggers the processing.

2. The current value of **AR_IN.D1** (REAL) is passed to the integrated conversion block **F_REAL_TO_UINT**.

3. The conversion transforms the REAL value into an unsigned integer value (UINT) – according to IEC 61131-3 rounding rules.

4. Upon completion, the result is output to **AUI_OUT.D1**, and the event **AUI_OUT.E1** is sent simultaneously.

The entire process occurs without intermediate storage or delay – each pulse triggers an immediate conversion.

## Technical Features
- **Stateless Design**: The block has no internal state memory; each conversion is independent of previous ones.
- **Uniform Adapter Interface**: By using unidirectional standard adapters (AR and AUI), the function block can be easily integrated into various architectures.
- **No Side Effects**: No global variables or system resources are affected.

## State Overview
The AR_TO_AUI is a pure function block without an internal state machine (ECC). Its execution is strictly event-driven and deterministic. Therefore, a separate state machine is not required.

## Application Scenarios
- **Connecting Analog Sensors**: When a sensor delivers its measured value as a REAL via an AR adapter, but the downstream control system expects UINT.
- **Data Bridge**: Mediation between different communication modules or libraries with different adapter types.
- **Protocol Conversion**: For example, in agricultural technology, where REAL values (e.g., speed) often need to be converted into integers (e.g., for counters).

## Comparison with Similar Function Blocks
- **AR_TO_ADI**: Converts REAL to INT (signed). AR_TO_AUI, on the other hand, generates unsigned values (UINT), which is advantageous for certain applications such as counter readings or HMI indices.
- **Direct Conversion with F_REAL_TO_UINT**: This single function block offers the same logic but requires manually connecting events and data. The Composite FB encapsulates this effort and reduces the potential for errors in complex networks.

## Conclusion
The **AR_TO_AUI** is a practical and reliable function block for easy adapter conversion from REAL to UINT. Its clear interface, purely functional behavior, and reusability make it a useful tool in the 4diac ecosystem. It is particularly suitable for applications requiring a clean separation of adapter types and easy integration into existing projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]