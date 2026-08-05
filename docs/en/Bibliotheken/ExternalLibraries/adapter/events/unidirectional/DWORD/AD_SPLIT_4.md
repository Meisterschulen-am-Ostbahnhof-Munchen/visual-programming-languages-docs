# AD_SPLIT_4
![AD_SPLIT_4](./AD_SPLIT_4.svg)
* * * * * * * * * *
## Introduction
The function block **AD_SPLIT_4** is used to distribute an incoming unidirectional AD adapter (adapter definition) to four identical outputs. It is a generic function block specifically designed for splitting a single AD signal into up to four separate paths.
## Interface Structure
### **Event Inputs**
No event inputs available.

### **Event Outputs**
No event outputs available.

### **Data Inputs**
No data inputs available. Data transmission occurs exclusively via the incoming AD adapter.

### **Data Outputs**
No data outputs available. Output occurs exclusively via the four outgoing AD adapters.

#
## ### **Adapters**

This component uses only adapters of type `adapter::types::unidirectional::AD`:

* **Socket (Input)**

`IN` – A unidirectional analog-to-digital input that receives the signal to be split.

* **Plugs (Outputs)**

`OUT1`, `OUT2`, `OUT3`, `OUT4` – Four unidirectional analog-to-digital outputs that pass the signal received from the input onward identically.

## Functionality

The **AD_SPLIT_4** function block copies the AD data stream arriving at its socket `IN` (without event handling) and makes it available in parallel at all four plugs `OUT1` to `OUT4`. Distribution occurs without delay or buffering – any change at the input is immediately propagated to all outputs. The function block is designed generically, so the specific data type of the AD adapter is only determined at runtime (GenericClassName = `'GEN_AD_SPLIT'`).

## Technical Features
* **Generic Type**: The function block is implemented as a generic function block. The actual AD data type is determined by the attribute `eclipse4diac::core::GenericClassName` (`'GEN_AD_SPLIT'`).
* **Unidirectional Communication**: The adapter used, `adapter::types::unidirectional::AD`, only allows data transmission from the socket to the plugs – feedback is not supported.
* **No Event Control**: The module does not require events, as data transmission is purely data-driven (or by the underlying adapter logic).

## State Overview
Since the module has no event inputs/outputs, there is no state machine. The behavior is deterministic: The outputs always reflect the current state of the input.

## Application Scenarios
* **Signal Distribution**: When a single A/D signal (e.g., a measured value or a control signal) needs to be forwarded to multiple subsequent function blocks or hardware components.
* **Monitoring and Control**: Simultaneous monitoring of a signal in different logic units without requiring multiple copies of the signal source.
* **Redundancy Paths**: Splitting a signal for parallel, independent processing paths.

## Comparison with Similar Function Blocks
* **AD_SPLIT_2**, **AD_SPLIT_8**: Related function blocks with identical functionality, but for two or eight outputs, respectively. The choice depends on the number of distributions required.
* **AD_MERGE_4**: A counterpart that combines multiple AD inputs into a single output, as opposed to splitting them.
* **Pure Data Split Function Blocks (e.g., D_SPLIT_4)**: These split individual data values (e.g., INT, REAL), while AD_SPLIT_4 is specifically designed for the complex AD adapter type.

## Conclusion
The **AD_SPLIT_4** function block is a compact, generic tool for easily replicating a unidirectional AD signal. Its clean, event-free interface makes it particularly suitable for data flow-oriented applications in automation technology where a signal needs to be distributed to multiple receivers. Its generic design allows it to be flexibly adapted to various adapter data types.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
