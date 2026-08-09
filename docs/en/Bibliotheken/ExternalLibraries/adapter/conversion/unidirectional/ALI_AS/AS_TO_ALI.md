# AS_TO_ALI

![AS_TO_ALI](./AS_TO_ALI.svg)

* * * * * * * * * *
## Introduction

The **AS_TO_ALI** function block is a composite block for converting a SINT adapter input (AS) into a LINT adapter output (ALI). It serves as a bridge between components that use different integer data types and enables the easy integration of SINT-based signals into LINT-based systems.
## Interface Structure

### **Event Inputs**

The function block has no directly visible event inputs. Event control is handled via the socket adapter **AS_IN**, which provides an event **E1**.

### **Event Outputs**

The function block has no directly visible event outputs. Event output is handled via the plug adapter **ALI_OUT**, which forwards an event **E1**.

### **Data Inputs**

No direct data inputs. The data value **D1** is read via the socket adapter **AS_IN** (data type SINT).

### **Data Outputs**

No direct data outputs. The converted data value **D1** is output via the plug adapter **ALI_OUT** (data type LINT).

### **Adapters**

- **AS_IN** (Socket, type: `adapter::types::unidirectional::AS`) – SINT adapter input with event E1 and data D1 (SINT).
- **ALI_OUT** (Plug, type: `adapter::types::unidirectional::ALI`) – LINT adapter output with event E1 and data D1 (LINT).

## Functionality

The AS_TO_ALI function block is implemented as a composite block. When an event arrives at **AS_IN.E1**, it is forwarded directly to **ALI_OUT.E1**. Simultaneously, the incoming SINT data value **AS_IN.D1** is converted to a LINT value and passed to **ALI_OUT.D1**. The conversion is lossless, as the value range of LINT completely covers that of SINT.

## Technical Features

- **Composite Structure** – no independent state logic, only forwarding and conversion.
- **Synchronized Event and Data Paths** – data is only passed after an event.
- **Implicit Type Conversion** – the conversion from SINT to LINT occurs automatically within the composite block's network.

## State Overview

The function block (FB) has no states of its own. Its functionality is limited to event-driven data passing with type conversion.

## Application Scenarios

- Connecting a SINT-based sensor to a LINT-based control system.
- Migrating existing SINT components to a LINT infrastructure.
- Heterogeneous systems where different integer data types need to be converted.

## Comparison with Similar Function Blocks

Similar converters exist for other data types (e.g., BOOL_TO_BYTE, INT_TO_DINT). The AS_TO_ALI function block is specifically designed for converting SINT to LINT and is conceived as an adapter function block, allowing it to be directly integrated into adapter-based communication structures.

## Conclusion

The AS_TO_ALI function block offers a simple, reliable, and efficient solution for converting SINT to LINT data. Its composite structure allows it to be integrated into existing 4diac projects without additional programming and facilitates the use of different data types in automation systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
