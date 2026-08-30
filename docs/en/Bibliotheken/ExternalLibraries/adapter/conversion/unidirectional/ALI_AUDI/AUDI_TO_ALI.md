# AUDI_TO_ALI

![AUDI_TO_ALI](./AUDI_TO_ALI.svg)

* * * * * * * * * *

## Introduction

The **AUDI_TO_ALI** function block is a composite module that bridges an **AUDI** adapter (of type *UDINT*) and an **ALI** adapter (of type *LINT*). It converts incoming UDINT values to LINT values using a standardized conversion function and forwards them to the output adapter. This module is typically used in applications that need to connect different address or integer types within a 4diac adapter concept.

## Interface Structure

### **Event Inputs**

| Name | Description |
|------|--------------|
| *No dedicated event inputs* | Event control is handled via the internal socket AUDI_IN.E1. |

### **Event Outputs**

| Name | Description |
|------|--------------|
| *No custom event outputs* | Event forwarding is handled via the internal plug ALI_OUT.E1. |

### **Data Inputs**

| Name | Data Type | Description |
|------|----------|--------------|
| *No custom data inputs* | – | The data value is supplied by socket AUDI_IN.D1. |

### **Data Outputs**

| Name | Data Type | Description |
|------|----------|--------------|
| *No custom data outputs* | – | The converted value is provided via the ALI_OUT.D1 plug. |

### **Adapter**

| Type | Name | Direction | Description |
| ----- | ------ | ---------- | -------------- |
| **AUDI** (unidirectional) | `AUDI_IN` | Socket (Input) | UDINT data adapter that provides a value based on event E1 and date D1. |
| **ALI** (unidirectional) | `ALI_OUT` | Plug (Output) | LINT data adapter that outputs the converted value based on event E1 and date D1. |

## Functionality

The module functions as a pure **type conversion bridge** for adapters:

1. **Event Receipt**: An event on socket `AUDI_IN.E1` activates the internal conversion module `F_UDINT_TO_LINT` via its event input `REQ`.
2. **Data Conversion**: The current UDINT value of `AUDI_IN.D1` is placed on the data input `IN` of the converter. `F_UDINT_TO_LINT` performs the IEC 61131-compliant conversion from an unsigned 32-bit integer (UDINT) to a signed 64-bit integer (LINT).
3. **Output**: After successful conversion, the converter signals with `CNF` that the output value is valid. This event is directly passed to the plug `ALI_OUT.E1`, and the converted LINT value from `Convert.OUT` is placed on `ALI_OUT.D1`.

The entire processing is **event-driven** and takes place within a single execution step (without any additional delay).

## Technical Features

- **Composite Block** – it contains no logic of its own but delegates the conversion entirely to the IEC 61131 block `F_UDINT_TO_LINT`.
- **Adapter-oriented interface** – All inputs and outputs are handled via standardized unidirectional adapters (`AUDI` and `ALI`), enabling easy integration into existing adapter networks.
- **License & Copyright** – This block is licensed under the **Eclipse Public License 2.0** and was developed by **HR Agrartechnik GmbH** (as of 2026).
- **Type safety** – Conversion from UDINT (unsigned 32-bit) to LINT (signed 64-bit) is lossless, as the value is simply sign-extended.
- **Package name** – In the CompilerInfo, the block is listed as `adapter::conversion::unidirectional`.

## State overview

As a composite block, `AUDI_TO_ALI` does not have its own states. The state logic is contained within the integrated `F_UDINT_TO_LINT` block, which transitions to a processing state after each `REQ` event and acknowledges this with `CNF`.

## Application Scenarios

- **Transition between different automation protocols** – when a system delivers UDINT values via an AUDI adapter, but the target system expects LINT values via an ALI adapter.
- **Data adaptation in adapter hierarchies** – redirection of 32-bit counter values (e.g., speed, pulse counter) to a 64-bit bus.
- **Migration** – legacy systems with UDINT sections can be connected to new 64-bit interfaces without changing the adapter structure.
- **Test Environments** – Simple loop-through of type conversion between two adapters, without separate conversion modules in the network.

## Comparison with similar modules

| Module | Type | Special Feature |
| ---------- | ----- | -------------- |
| `F_UDINT_TO_LINT` | Pure converter | No adapters, direct data I/O; no event handling via adapters, requires its own control. |
| `AUDI_TO_ALI` (this one) | Adapter converter | Encapsulates the conversion in an adapter-based interface; events and data are automatically routed via the adapters. |
| `ALI_TO_AUDI` (hypothetical) | Adapter converter | Would convert LINT backwards to UDINT (potentially lossy). |

The **main difference** compared to directly using `F_UDINT_TO_LINT` is the seamless integration into adapter networks and the avoidance of additional lines for event and data connections.

## Conclusion

The **AUDI_TO_ALI** function block is a practical adapter converter that bridges the gap between a UDINT-based AUDI adapter and a LINT-based ALI adapter. By internally using the standardized IEC 61131 converter `F_UDINT_TO_LINT`, the conversion is efficient and type-safe. The block is particularly suitable for modular architectures where different address widths are encountered and simplifies the reuse of adapter interfaces in heterogeneous automation environments.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
