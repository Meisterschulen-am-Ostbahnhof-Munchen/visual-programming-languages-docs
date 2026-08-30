# AX_TO_AR

![AX_TO_AR](./AX_TO_AR.svg)

* * * * * * * * * *

## Introduction

The **AX_TO_AR** function block is a composite function block that converts a Boolean signal from an AX adapter (type `adapter::types::unidirectional::AX`) into a REAL value (0.0 or 1.0) and outputs it via an AR adapter (type `adapter::types::unidirectional::AR`). The conversion is performed using the IEC 61131 function block **F_SEL**.

## Interface Structure

### **Event Inputs**

The function block does not have its own event inputs at the FB level. The internal process is controlled exclusively via the event of the AX_IN adapter, which is connected to the REQ input of the F_SEL.

### **Event Outputs**

There are no event outputs at the FB level. The output event of F_SEL (CNF) is directly forwarded to the event input of the AR_OUT adapter.

### **Data Inputs**

There are no direct data inputs at the FB level. The only data input is provided via the AX_IN adapter:

- **D1** (BOOL) – the Boolean signal to be converted.

### **Data Outputs**

There are no direct data outputs at the FB level. The converted value is output via the AR_OUT adapter:

- **D1** (REAL) – the resulting REAL value (0.0 or 1.0).

### **Adapters**

- **AX_IN** (Socket):
- Type: `adapter::types::unidirectional::AX`
- Provides a Boolean signal and an event pulse.
- **AR_OUT** (Plug):
- Type: `adapter::types::unidirectional::AR`
- Outputs the converted REAL value.

## Functionality

The function block operates in an event-driven manner:

1. An incoming event at the AX_IN adapter (E1) triggers the internal F_SEL function block via its REQ input.
2. Simultaneously, the Boolean signal (AX_IN.D1) is applied to the G input of F_SEL.
3. F_SEL selects the following depending on G:

- For `G = FALSE` => Output of **IN0** (value `REAL#0.0`).
- For `G = TRUE` => Output of **IN1** (value `REAL#1.0`).
1. The result is passed via output OUT to data input D1 of the AR_OUT adapter.
2. The CNF event of F_SEL triggers output event E1 of the AR_OUT adapter, allowing the connected logic to accept the new data.

## Technical Features

- **Reusability**: The function block is implemented as a composite function block and uses the standardized IEC 61131 function block `F_SEL` from the library `iec61131::selection`.
- **Adapter Coupling**: All communication takes place via unidirectional adapters (`adapter::types::unidirectional::AX` and `adapter::types::unidirectional::AR`), enabling loose coupling and easy reuse in different contexts.
- **Configuration**: The limit values (IN0=0.0, IN1=1.0) are fixed and can be changed as needed by adjusting the parameters of the internal F_SEL.

## State Overview

The function block does not have an internal state machine. It reacts **event-driven** and performs a one-time selection for each event at the AX_IN adapter. There are no stored states – the behavior is purely combinatorial.

## Application Scenarios

- Conversion of a binary sensor signal (e.g., switch, limit switch) into a numerical value for further processing in REAL-based control loops or visualizations.
- Integration of Boolean adapter signals into systems that operate entirely with REAL values.
- Simple mapping of digital inputs/outputs to analog values (0/1) in adapter-based automation solutions.

## Comparison with Similar Function Blocks

- **Standard conversion function blocks** such as `BOOL_TO_REAL` from IEC libraries offer direct data-level conversion, but without adapter interfaces.
- **`SELECT`** (IEC 61131) can also use a Boolean signal to select between two REAL values, but requires manual wiring.
- **AX_TO_AR** encapsulates the complete adapter conversion in a reusable composite function block, thus significantly reducing the wiring effort in adapter network-based 4diac applications.

## Conclusion

The **AX_TO_AR** function block provides a compact and robust solution for converting Boolean adapter signals into real values. By utilizing `F_SEL` and encapsulating it as a composite function block, it is easy to integrate, extensible, and ideally suited for adapter-oriented automation architectures.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
