# AS_TO_AI
![AS_TO_AI](./AS_TO_AI.svg)
* * * * * * * * * *
## Introduction
The function block `AS_TO_AI` is a composite function block that converts an AS adapter (data type SINT) to an AI adapter (data type INT). It serves as a simple converter for connecting components with different adapter types within the 4diac IDE.
## Interface Structure
### **Event Inputs**
- None

### **Event Outputs**
- None

### **Data Inputs**
- None

### **Data Outputs**
- None

### **Adapter**
- **AS_IN** (Socket, Type: `adapter::types::unidirectional::AS`)

Expects a SINT value and a corresponding event E1.

- **AI_OUT** (Plug, Type: `adapter::types::unidirectional::AI`)

Provides an INT value and an event E1.

## Functionality
The function block forwards the event E1 from the AS_IN socket directly to the AI_OUT plug. Simultaneously, the data value D1 is transferred from the AS_IN socket to the AI_OUT plug. This involves an implicit type conversion from SINT (8-bit signed) to INT (16-bit signed). No further processing or state logic takes place.

## Technical Features
- The type conversion from SINT to INT is performed automatically by the 4diac runtime environment without requiring any additional code blocks.
- The function block is implemented as a **Composite FB** and does not contain its own ECC (Execution Control Chart).
- It is located in the package `adapter::conversion::unidirectional`, which indicates unidirectional adapter conversion.

## State Overview
Since it is a composite function block, `AS_TO_AI` does not have its own states. Its behavior is determined solely by the wiring of its internal connections.

## Application Scenarios
- A sensor provides data via an AS adapter (SINT), but the connected processing component expects an AI adapter (INT).
- Migration from 8-bit to 16-bit data paths without changing the source or target component.
- Prototyping and system integration when different adapter versions interact.

## Comparison with Similar Components
- **AI_TO_AS**: Performs the reverse conversion (INT → SINT).
- **AI_TO_AD** or similar: Converts between other integer data types (e.g., INT to DINT).
- Unlike these function blocks, `AS_TO_AI` operates losslessly, as the target type (INT) can fully map to the source type (SINT).

## Conclusion
The `AS_TO_AI` function block is a simple yet effective tool for ensuring adapter compatibility in 4diac applications. It handles the automatic type conversion from SINT to INT, thus simplifying the integration of heterogeneous components without requiring manual adjustment of the data path.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
