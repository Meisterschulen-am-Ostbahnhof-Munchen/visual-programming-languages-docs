# ALR_TO_AX
![ALR_TO_AX](./ALR_TO_AX.svg)
* * * * * * * * * *
## Introduction
The **ALR_TO_AX** function block is a composite function block for converting an LREAL value (via the unidirectional ALR adapter) into a BOOL value (via the unidirectional AX adapter). It is typically used to convert an analog input signal into a digital output signal – for example, to detect a threshold being exceeded. The function block is based on a simple zero comparison and triggers the output event as soon as a valid value is present at the input.
## Interface Structure
### **Event Inputs**
- **ALR_IN.E1** – Event from the ALR adapter; indicates that a new LREAL value is available.

### **Event Outputs**
- **AX_OUT.E1** – Event to the AX adapter; Indicates that the converted BOOL value is valid.

### **Data Inputs**
- **ALR_IN.D1** – LREAL input value (via the ALR adapter).

### **Data Outputs**
- **AX_OUT.D1** – BOOL output value (via the AX adapter); derived by comparing the input value to 0.0.

### **Adapters**
- **ALR_IN** – Socket (Type: *adapter::types::unidirectional::ALR*): unidirectional LREAL input adapter.
- **AX_OUT** – Plug (Type: *adapter::types::unidirectional::AX*): unidirectional BOOL output adapter.

## Functionality
When an event arrives via **ALR_IN.E1**, the data value **ALR_IN.D1** (LREAL) is passed to the internal IEC 61131 block **F_NE**. This compares the value with the constant `LREAL#0.0` and returns **TRUE** if the input is not zero, otherwise **FALSE**. The result is then passed directly to **AX_OUT.D1**, and an acknowledgment event is triggered via **AX_OUT.E1**.

The entire process takes place within a single cycle, as this is a composite block without its own state machine.

## Technical Details
- **License & Origin**: The block is licensed under the Eclipse Public License 2.0 and was provided with version information 1.0.

`` - **Libraries Used**: The comparison block *F_NE* is from the IEC 61131 library (*iec61131::comparison*).

- **Package Name**: The function block belongs to the package *adapter::conversion::unidirectional*.
- **Compatibility**: It requires the adapter specification of the 4diac framework and is designed for unidirectional adapter types.

## State Overview
The function block does not have an explicit state machine. Its logic is purely combinational and event-driven:

1. Wait for an event at **ALR_IN.E1**.

2. Data processing (comparison with 0.0).

3. Output the BOOL result to **AX_OUT.D1** and send the acknowledgment event to **AX_OUT.E1**.

## Application Scenarios
- **Analog-to-Digital Conversion**: Detects whether an analog measurement value (e.g., pressure sensor, temperature) is non-zero.
- **Threshold Detection**: Any threshold logic can be implemented through simple modification (replacing *F_NE* with *F_GT* or *F_LT*).
- **Adapter Coupling**: Integrates ALR-based sensors into AX-based control logic without requiring complex type conversions at a higher level.

## Comparison with Similar Function Blocks
- **LREAL_TO_BOOL**: While a dedicated LREAL-to-BOOL function block often supports a threshold and hysteresis, *ALR_TO_AX* implements the simplest form – null ≠ null → TRUE.
- **Comparison blocks (F_NE, F_EQ, etc.)**: These operate directly on data, while *ALR_TO_AX* handles complete adapter integration and event control.
- **Adapter-Converter blocks**: The same package contains additional unidirectional/bidirectional converters that perform similar tasks for other types (e.g., BOOL_TO_ALR).

## Conclusion
The **ALR_TO_AX** function block offers a streamlined and reliable way to convert an LREAL adapter output to a BOOL adapter input. Thanks to its simple structure, it is ideally suited for basic digitization tasks in IEC 61499-based control systems. It is easy to understand, readily extensible, and follows common design patterns for unidirectional adapter conversion.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
