# AI_TO_ALR

![AI_TO_ALR](./AI_TO_ALR.svg)

* * * * * * * * * *

## Introduction

The function block **AI_TO_ALR** is a composite function block that converts an **AI (INT adapter)** to an **ALR (LREAL adapter)**. It serves as a pure conversion interface by directly routing the event and data channels of the input adapter to the output adapter. The actual type conversion from Integer (INT) to Long Real (LREAL) is handled by the underlying adapter definitions.

## Interface Structure

### **Event Inputs**

The function block does not have direct event inputs. The event is received via the socket adapter `AI_IN`:

- **AI_IN.E1** – Event of the INT adapter (input).

### **Event Outputs**

There are no direct event outputs here either. The event is sent via the plug adapter `ALR_OUT`:

- **ALR_OUT.E1** – Event of the LREAL adapter (output).

### **Data Inputs**

- **AI_IN.D1** – Data value of type INT (via the adapter).

### **Data Outputs**

- **ALR_OUT.D1** – Data value of type LREAL (via the adapter).

### **Adapters**

- **AI_IN** (Socket) – Adapter of type `AI` (INT adapter), input interface.
- **ALR_OUT** (Plug) – Adapter of type `ALR` (LREAL adapter), output interface.

## Functionality

This component connects the signals of the socket adapter `AI_IN` directly to the plug adapter `ALR_OUT`:

- **Event Path:** The event received by `AI_IN.E1` is forwarded unchanged to `ALR_OUT.E1`.
- **Data Path:** The INT value received by `AI_IN.D1` is passed to `ALR_OUT.D1`. The adapters themselves implement the necessary type conversion from INT to LREAL.

Since this is a composite component without its own algorithm or state machine, no further processing takes place. The component functions purely as a routing and adaptation layer between different adapter types.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- **Pure Passthrough Structure:** No internal logic, no latency, and no buffering.
- **Adapter Definition Dependency:** Correct operation requires that the adapters `AI` and `ALR` are defined according to the 4diac standard and include the INT>LREAL conversion.
- **Composite Component:** Easily extensible, e.g., through additional filters or network scaling.
- **Package Structure:** The component is located in the package `adapter::conversion::unidirectional`.

## State Overview

The component does not have its own state diagram (ECC). Signal processing is purely event-driven via the passed-through adapter events. Therefore, a state is not defined.

## Application Scenarios

- **System Integration:** Connecting an INT-based sensor (e.g., digital value from a counter) to a component that expects LREAL values (e.g., a control algorithm).
- **Adapter Bridge:** Use in modular automation systems where different adapter types interact.
- **Prototype Development:** Rapid coupling of test modules with different data formats.

## Comparison with Similar Modules

While 4diac libraries often contain separate converter modules for basic data types (e.g., `INT_TO_REAL`), `AI_TO_ALR` encapsulates the conversion at the adapter level. The advantage lies in the reusability of adapter interfaces and the easy exchange of the conversion logic with other adapters. The disadvantage is the dependence on the specific adapter definitions.

## Conclusion

The **AI_TO_ALR** function block is a minimalist yet effective composite function block for type conversion between INT and LREAL adapters. It reduces wiring effort in complex control networks and enables a clean separation of interfaces and conversion logic. It is an ideal solution for applications requiring simple pass-through without additional processing.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
