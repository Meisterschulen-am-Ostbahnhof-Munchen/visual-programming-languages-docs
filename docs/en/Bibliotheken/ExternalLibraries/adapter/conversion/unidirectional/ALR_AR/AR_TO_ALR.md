# AR_TO_ALR

![AR_TO_ALR](./AR_TO_ALR.svg)

* * * * * * * * * *
## Introduction

Composite function block for converting an AR adapter (REAL) to an ALR adapter (LREAL). It is used to adapt data formats in IEC 61499-2 environments and is licensed under the Eclipse Public License 2.0.
## Interface Structure

### **Event Inputs**

| Name | Description |
|------|--------------|
| **E1** (from AR_IN) | Event to trigger data transfer |

### **Event Outputs**

| Name | Description |
|------|--------------|
**E1** (from ALR_OUT) | Event output after successful conversion |

### **Data Inputs**

| Name | Data Type | Description |
|------|----------|--------------|
**D1** (from AR_IN) | REAL | 32-bit floating-point number |

### **Data Outputs**

| Name | Data Type | Description |
|------|----------|--------------|
**D1** (from ALR_OUT) | LREAL | 64-bit floating-point number |

### **Adapters**

- **ALR_OUT** (Plug): Type `adapter::types::unidirectional::ALR` – LREAL output adapter
- **AR_IN** (Socket): Type `adapter::types::unidirectional::AR` – REAL input adapter

## Functionality

This function block connects the adapter interfaces directly. An incoming event at `AR_IN.E1` is immediately forwarded to `ALR_OUT.E1`. Simultaneously, the data value `AR_IN.D1` (REAL) is copied to `ALR_OUT.D1` (LREAL), with the runtime environment performing an implicit type conversion. There is no state machine; the function is purely combinatorial.

## Technical Features

- Composite function block without its own logic (no ECC)
- Use of unidirectional adapters according to IEC 61499-2
- Automatic type conversion via the 4diac runtime (e.g., 4diac-ide)
- Package: `adapter::conversion::unidirectional`

## State Overview

No states present – the function block does not have an execution state machine.

## Application Scenarios

- Connecting a REAL-providing sensor to a component that expects LREAL
- Migrating existing REAL adapters to LREAL with higher accuracy
- Interface adaptation in heterogeneous automation systems

## Comparison with Similar Function Blocks

Similar function blocks exist for other type conversions (e.g., `LREAL_TO_REAL`, `INT_TO_REAL`). This block is specifically designed for the unidirectional adapters `AR` and `ALR` and requires no custom implementation logic.

## Conclusion

The `AR_TO_ALR` block enables simple and efficient conversion of REAL to LREAL adapter data. Implemented as a composite function block, it utilizes the direct connection of the adapter interfaces, thus offering high performance with minimal latency.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
