# ST08B_TO_BYTES

<img width="1031" height="423" alt="image" src="https://github.com/user-attachments/assets/d97ce166-0caf-452f-8aa8-52ba1b60245d" />

![ST08B_TO_BYTES](./ST08B_TO_BYTES.svg)

* * * * * * * * * *
## Introduction
This function block extracts the individual 8 bytes of a specific 8-byte structure (`ST08B`) and provides them as separate byte outputs. It enables detailed segmentation and further processing of structured 8-byte data.

## Interface Structure
### **Event Inputs**
* **REQ**: Triggers the function and initiates the extraction of the bytes from the data input `IN`.

#### **Event Outputs**
* **CNF**: Sent after successful execution and updating of all output bytes. This event is associated with all `OUT_xx` data outputs.

### **Data Inputs**

* **IN** (`logiBUS::utils::conversion::types::ST08B`): The input containing the 8-byte structure from which the bytes are to be extracted.

### **Data Outputs**

* **OUT_00** (`BYTE`): The first extracted byte (byte 00).

* **OUT_01** (`BYTE`): The second extracted byte (byte 01).

* **OUT_02** (`BYTE`): The third extracted byte (byte 02).

* **OUT_03** (`BYTE`): The fourth extracted byte (byte 03).

* **OUT_04** (`BYTE`): The fifth extracted byte (Byte 04).

* **OUT_05** (`BYTE`): The sixth extracted byte (Byte 05).

* **OUT_06** (`BYTE`): The seventh extracted byte (Byte 06).

* **OUT_07** (`BYTE`): The eighth extracted byte (Byte 07).

### **Adapter**
This function block has no adapter interfaces.

## Operation
As soon as a `REQ` event is received, the function block reads the input structure `IN`. It extracts each individual byte of the structure (`IN.B_00` to `IN.B_07`) and assigns it to the corresponding output parameter (`OUT_00` to `OUT_07`). Upon completion of these assignments, the `CNF` event is triggered to signal the successful operation. The internal logic is direct and transparent:


```iecst
OUT_00 := IN.B_00;
OUT_01 := IN.B_01;
OUT_02 := IN.B_02;
OUT_03 := IN.B_03;
OUT_04 := IN.B_04;
OUT_05 := IN.B_05;
OUT_06 := IN.B_06;
OUT_07 := IN.B_07;
```
## Technical Features

This function block specializes in decomposing the user-defined structure `ST08B`. Type assignment is performed directly without additional conversion logic, as both the source and target types (members of the structure and outputs) are of type `BYTE`. This ensures efficient and lossless data splitting. The block is deterministic and stateless, as it does not store any internal states that could influence the outcome of future executions.

## State Overview
The function block `ST08B_TO_BYTES` is a pure converter without internal state. Each execution is independent of previous executions and always delivers the same result for identical input data.

## Application Scenarios

* **Data Logging and Analysis**: When an 8-byte structure is received, the individual bytes can be extracted for separate logging, monitoring, or use in specific analyses.

* **Interface Adaptation**: Adapting data formats when an external interface provides an 8-byte structure, but subsequent components expect individual bytes.

* **Bit-Level Manipulation**: Preparing data for bit-level operations where each byte must be addressed individually.

* **Debugging**: Simplifies debugging data in 8-byte structures by making the contents of individual bytes visible.

## ⚖️ Comparison with Similar Components
Similar functionality could be achieved in other systems through explicit type conversions or pointer operations. In the 4diac context, this component represents an event-driven, clearly defined, and reusable solution for this specific structure-to-byte partitioning. The advantage lies in the direct connection to the 4diac event model and the explicit declaration of the interface, which improves readability and maintainability. Alternatively, the assignments would have to be made directly in the `ST` code of a Composite Function Block, which would limit reusability.

## Conclusion
The `ST08B_TO_BYTES` function block is a useful tool for decomposing a specific 8-byte structure into its individual byte components. Its simplicity, clear interface, and deterministic functionality make it a reliable building block for applications that require precise control and analysis of 8-byte data. It promotes modularity and reusability in 4diac applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```