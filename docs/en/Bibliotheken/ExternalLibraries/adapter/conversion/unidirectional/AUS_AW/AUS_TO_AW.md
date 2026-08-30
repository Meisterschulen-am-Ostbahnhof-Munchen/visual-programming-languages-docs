# AUS_TO_AW

![AUS_TO_AW](./AUS_TO_AW.svg)

* * * * * * * * * *

## Introduction

The **AUS_TO_AW** function block is a composite function block that enables the simple and standardized conversion of a **USINT** value (0–255) to a **WORD** value (16 bits) via adapter interfaces. It acts as an intermediary between systems that provide or expect different data types via unidirectional adapters.

## Interface Structure

The function block itself has no direct inputs or outputs. All communication takes place via the two integrated adapters.

## **Event Inputs**

No direct event inputs are available. Event control is implemented via the **AUS_IN** adapter. This provides an event input **E1**, the activation of which starts the conversion process.

## **Event Outputs**

No direct event outputs are available. An event is output via the **AW_OUT** adapter after successful conversion (event output **E1**).

### **Data Inputs**

No direct data inputs are available. The USINT value to be converted is read via the **D1** data input of the **AUS_IN** adapter (type: USINT).

### **Data Outputs**

No direct data outputs are available. The converted WORD value is output via the **D1** data output of the **AW_OUT** adapter (type: WORD).

### **Adapters**

- **AUS_IN** (Socket): Unidirectional adapter of type `adapter::types::unidirectional::AUS`. Expects a USINT value and an event to trigger the conversion.
- **AW_OUT** (Plug): Unidirectional adapter of type `adapter::types::unidirectional::AW`. Provides the WORD value and a confirmation event after successful conversion.

## Functionality

1. An external event at the **E1** input of the **AUS_IN** adapter triggers execution.
2. The internal function block **F_USINT_TO_WORD** (from the IEC 61131 library) takes the USINT value present at **AUS_IN.D1** and converts it to a WORD value.
3. After the conversion is complete, the WORD value at the **OUT** output of **F_USINT_TO_WORD** is forwarded to **AW_OUT.D1**.
4. Simultaneously, an event is generated at the **CNF** output of **F_USINT_TO_WORD**, which signals externally via **AW_OUT.E1** that the converted value is available.

## Technical Features

- **Composite Block**: The conversion logic is encapsulated in its own network, promoting reuse and clarity.
- **Unidirectional Adapters**: The **OFF** and **AW** adapters are designed as pure data and event pipelines – reverse communication is not supported.
- **Standard Conversion**: The actual type conversion is based on the tested block `F_USINT_TO_WORD` from the IEC 61131 library.
- **No Internal State Logic**: The block delegates all control to the internal converter and the adapter interfaces.

## State Overview

The block does not have its own state machine. The process is event-driven and strictly sequential:

- **Idle**: Waiting for an event at the OFF_IN adapter.
- **Conversion active**: Internal **F_USINT_TO_WORD** is executed. Upon completion, the function block automatically returns to the idle state.
- **Output**: The confirmation event is sent via the AW_OUT adapter.

## Application Scenarios

- **System Integration**: A sensor delivers measured values as USINT via a unidirectional AUS adapter, but the controller expects WORD values via an AW adapter.
- **Data Preparation**: Simple type conversion without additional logic is required in an adapter-based communication chain.
- **Prototype Development**: Rapid coupling of two components using different data types without modifying the existing adapter structure.

## Comparison with Similar Function Blocks

- **F_USINT_TO_WORD** (direct): Provides pure conversion without adapter integration – suitable for internal flows within a device.
- **AUS_TO_AW**: Extends the conversion process with unidirectional adapters, enabling loose coupling between independent systems.
- **Other adapter converters (e.g., INT_TO_DWORD)**: Follow the same pattern but with different target types. **AUS_TO_AW** is specifically optimized for the USINT → WORD pairing.

## Conclusion

**AUS_TO_AW** is a compact, reliable composite component that standardizes the conversion of USINT to WORD data via unidirectional adapters and can be seamlessly integrated into existing 4diac projects. It reduces development effort and increases reusability in modular automation systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
