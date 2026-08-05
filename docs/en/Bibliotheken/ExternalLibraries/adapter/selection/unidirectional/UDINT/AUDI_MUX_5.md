# AUDI_MUX_5
![AUDI_MUX_5](./AUDI_MUX_5.svg)
* * * * * * * * * *
## Introduction
The function block **AUDI_MUX_5** is a generic multiplexer that allows one of five identical inputs (IN1 to IN5) to be switched to an output (OUT) depending on an index value (K). The block was designed for use with the adapter type `adapter::types::unidirectional::AUDI` and is part of the HR Agrartechnik GmbH library. The selection of the active input is triggered by the REQ event.
## Interface Structure

### **Event Inputs**
- **REQ** – Sets the index K and triggers the switching of the corresponding input to the output.

### **Event Outputs**
- **CNF** – Confirms the successful processing of the REQ event.

### **Data Inputs**
- **K** (Data type: UINT) – Index that determines which of the five inputs (IN1…IN5) is set to OUT. Valid values: 0–4.

### **Data Outputs**
None.

### **Adapters**
- **OUT** (Plug, Type: `adapter::types::unidirectional::AUDI`) – Output adapter that provides the currently selected input value.
- **IN1** (Socket, Type: `adapter::types::unidirectional::AUDI`) – First input (Index K=0).
- **IN2** (Socket, Type: `adapter::types::unidirectional::AUDI`) – Second input (Index K=1).
- **IN3** (Socket, Type: `adapter::types::unidirectional::AUDI`) – Third input (Index K=2).
- **IN4** (Socket, Type: `adapter::types::unidirectional::AUDI`) – Fourth input (Index K=3).
- **IN5** (Socket, Type: `adapter::types::unidirectional::AUDI`) – Fifth input (Index K=4).

## Functionality
The module operates as a **1-out-of-5 multiplexer**. As soon as a signal is present at the event input REQ, the current value of the data input K is read. The adapter output **OUT** is then connected to the content of the adapter corresponding to index K:

- K = 0 → IN1
- K = 1 → IN2
- K = 2 → IN3
- K = 3 → IN4
- K = 4 → IN5

After successful switching, the **CNF** event is output. The module is designed generically and can therefore work with any AUDI adapter type, as long as the interfaces are unidirectional.

## Technical Features
- **Generic Type** – The function block is declared as `generic FB` and can be instantiated using a specific class name (`GEN_AUDI_MUX`).
- **Adapter-Based** – Both inputs and outputs are implemented via adapters, enabling a modular and type-safe connection.
- **Index Coverage** – The index K is defined as `UINT`; the calling logic is expected to only pass values in the range 0–4. An invalid index (≥5) leads to undefined behavior.

## State Overview

The function block does not have explicit states in the sense of a state machine. It remains in an idle state until a REQ event arrives. After processing, CNF is immediately sent, and the function block returns to the wait state.

## Application Scenarios
- **Signal Switching** – Selection of one of five analog or digital measured values (e.g., temperature sensors, pressure sensors) for further processing.
- **Mode Switching** – Switching between different operating modes of a machine connected via adapters.
- **Test and Diagnostic Functions** – Targeted input of test signals to a common output.

## Comparison with Similar Function Blocks
Standard MUX function blocks (e.g., `MUX` or `SEL`) offer similar functionality, often using simple data types (BOOL, INT, REAL). The **AUDI_MUX_5** stands out due to its use of adapters that bundle complex, structured data or entire signal paths into a single connection point. This makes it particularly suitable for use in object-oriented or adapter-based architectures.

## Conclusion

The **AUDI_MUX_5** is a compact, generic multiplexer for five adapter inputs. It enables clean, type-tested switching of signals in automation technology and, due to its generic nature, can be flexibly integrated into various control environments. Its ease of use and clear interface make it a useful tool for signal selection in 4diac projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]