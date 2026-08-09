# AX_TO_AD

![AX_TO_AD](./AX_TO_AD.svg)

* * * * * * * * * *
## Introduction

The composite function block `AX_TO_AD` converts a Boolean adapter (AX) to a DWORD adapter (AD). It forwards event and data signals from the input adapter directly to the output adapter and implicitly converts the data type from Boolean to DWORD.
## Interface Structure

### **Event Inputs**

The function block has no direct event inputs. Event control is handled via the socket `AX_IN`.

### **Event Outputs**

There are no direct event outputs. Events are passed via the plug `AD_OUT`.

### **Data Inputs**

There are no direct data inputs. Data is acquired via socket `AX_IN`.

### **Data Outputs**

There are no direct data outputs. Data output is handled via plug `AD_OUT`.

### **Adapters**

- **AX_IN** (Socket): Adapter of type `adapter::types::unidirectional::AX`. Provides a BOOL signal (D1) and a trigger event (E1).
- **AD_OUT** (Plug): Adapter of type `adapter::types::unidirectional::AD`. Expects a DWORD signal (D1) and a trigger event (E1).

## Functionality

The function block (FB) links the input adapter `AX_IN` directly to the output adapter `AD_OUT`:

- **Event Path**: The event from `AX_IN.E1` is forwarded unchanged to `AD_OUT.E1`.
- **Data Path**: The Boolean value from `AX_IN.D1` is transferred to `AD_OUT.D1`. An implicit type conversion occurs: `TRUE` becomes `1` (DWORD), and `FALSE` becomes `0` (DWORD).

The function block itself contains no internal logic or state machines – it functions purely as a pass-through converter between the two adapter types.

## Technical Features

- **Composite FB**: The implementation consists solely of wiring within the FB network, without any additional algorithms.
- **Implicit Data Type Conversion**: The BOOL value is automatically converted to a DWORD value (bits 0-31: 0 or 1).
- **Unidirectional Adapters**: Both the input and output use unidirectional adapters that support only one data and one event connection.

## State Overview

The `AX_TO_AD` function block does not have its own internal state. Its behavior is purely reactive: An incoming event at the input is immediately passed on to the output, optionally accompanied by the updated data signature.

- **Implicit Data Type Conversion**: The BOOL value is automatically converted to a DWORD value (bits 0-31: 0 or 1).
- **Unidirectional Adapters**:** Both the input and output use unidirectional adapters that support only one data and one event connection.


- **Composite FB**:**
## Application Scenarios

- Integration of a digital sensor (e.g., switch, light barrier) into a system that expects a DWORD adapter for data acquisition.
- Gradual migration of an application from BOOL-based to DWORD-based adapter interfaces.
- Prototypical connection between different libraries or components with incompatible adapter types.

## Comparison with Similar Function Blocks

- **BOOL_TO_DWORD** (function block): Performs pure data type conversion, but without adapter encapsulation.
- **AX_TO_AD** specializes in adapter interfaces and is therefore particularly suitable for exchanging data between different communication patterns in 4diac.
- Similar function blocks exist for other type combinations, e.g., `INT_TO_REAL_AD` or `WORD_TO_BOOL_AD`.

## Conclusion

The `AX_TO_AD` function block offers a simple and clean way to convert a BOOL adapter to a DWORD adapter without requiring the user to write any conversion logic. It is ideally suited for linking different adapter worlds in 4diac projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
