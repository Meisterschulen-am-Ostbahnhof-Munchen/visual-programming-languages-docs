# ST08X_TO_BOOLS
<img width="1020" height="423" alt="image" src="https://github.com/user-attachments/assets/4fc3f598-930f-475b-b552-aefad4b5bb28" />
![ST08X_TO_BOOLS](./ST08X_TO_BOOLS.svg)
* * * * * * * * * *
## Introduction
This function block extracts eight individual BOOL values from a single input structure of type `ST08X`. It allows for the easy decomposition of a bundled 8-BOOL structure into its individual components.
## Interface Structure
### **Event Inputs**
* **REQ**: An event at this input requests conversion. It signals the function block to process the data from input `IN`.

### **Event Outputs**
* **CNF**: This event is output once the conversion is complete and all output BOOL values (`OUT_00` to `OUT_07`) have been updated.

### **Data Inputs**
* **IN** (Type: `logiBUS::utils::conversion::types::ST08X`): The input structure containing the eight BOOL values to be extracted.

### **Data Outputs**
* **OUT_00** (Type: `BOOL`): The first extracted BOOL value (bit 00).
* **OUT_01** (Type: `BOOL`): The second extracted BOOL value (bit 01).
* **OUT_02** (Type: `BOOL`): The third extracted BOOL value (Bit 02).
* **OUT_03** (Type: `BOOL`): The fourth extracted BOOL value (Bit 03).
* **OUT_04** (Type: `BOOL`): The fifth extracted BOOL value (Bit 04).
* **OUT_05** (Type: `BOOL`): The sixth extracted BOOL value (Bit 05).
* **OUT_06** (Type: `BOOL`): The seventh extracted BOOL value (Bit 06).
* **OUT_07** (Type: `BOOL`): The eighth extracted BOOL value (Bit 7).

### **Adapter**
No adapters available.

## Functionality
As soon as an event is received at input `REQ`, the function block directly assigns the individual BOOL components of the input structure `IN` to the corresponding output variables. Specifically, `IN.X_00` is assigned to output `OUT_00`, `IN.X_01` to output `OUT_01`, and so on, up to `IN.X_07` to `OUT_07`. After successful assignment, a confirmation event `CNF` is output to indicate that the results are available.

## Technical Features
* **Direct Mapping:** The function block implements a simple and direct 1:1 mapping from the fields of the `ST08X` structure to the individual BOOL outputs.
* **Type Safety:** The use of the specific type `ST08X` ensures a clear and type-safe interface.
* **Efficiency:** The conversion is highly efficient because no complex logic or calculations are required.

## State Overview

This function block is stateless. It does not store any internal data between calls, and its output depends solely on the current input values. Each execution is independent of previous executions.

*
## Application Scenarios
* **Decomposition of Combined Signals:** Ideal for splitting a logically grouped 8-bit structure into its individual, independent BOOL signals.
* **Interface Adaptation:** Enables connection to other function blocks or systems that expect individual BOOL inputs instead of a structure.
* **Visualization and Diagnostics:** Simplifies the separate display or monitoring of each individual bit of a `ST08X` structure.

## ⚖️ Comparison with Similar Blocks

This function block is specifically designed for the `ST08X` structure. While generic bit extraction functions (e.g., from a BYTE or WORD) might produce similar results, `ST08X_TO_BOOLS` provides a clearly defined, typed interface for the specific `ST08X` structure. This improves readability and avoids potential errors during manual bit indexing. It is simpler and more specific than function blocks that support complex bit field operations or variable bit counts.

## Conclusion
The function block `ST08X_TO_BOOLS` is a useful tool for decomposing `ST08X` structures into individual BOOL signals. It impresses with its simplicity, efficiency, and clear, type-safe interface, which simplifies the development and maintenance of 4diac applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
