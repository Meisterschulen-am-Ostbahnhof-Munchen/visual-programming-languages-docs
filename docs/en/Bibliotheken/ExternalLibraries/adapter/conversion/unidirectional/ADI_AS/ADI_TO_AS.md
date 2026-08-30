# ADI_TO_AS

![ADI_TO_AS](./ADI_TO_AS.svg)

* * * * * * * * * *

## Introduction

The composite function block **ADI_TO_AS** is used to convert a **DINT adapter signal** (type `ADI`) into a **SINT adapter signal** (type `AS`). It is used when data and event exchange is required via unidirectional adapters and a data type conversion from DINT (32-bit signed integer) to SINT (8-bit signed integer) is necessary.

## Interface Structure

### **Event Inputs**

No separate event inputs – event control is handled via the integrated **ADI-IN adapter** (socket).

### **Event Outputs**

No separate event outputs – event forwarding is handled via the integrated **AS-OUT adapter** (plug).

### **Data Inputs**

No separate data inputs – the data value is provided via the **ADI-IN adapter**.

### **Data Outputs**

No separate data outputs – the converted value is output via the **AS-OUT adapter**.

### **Adapters**

| Adapter | Direction | Type | Comment |
| --------- | ---------- | ----- | ----------- |
| **ADI_IN** | Socket (Input) | `adapter::types::unidirectional::ADI` | DINT Adapter Input |
| **AS_OUT** | Plug (Output) | `adapter::types::unidirectional::AS` | SINT Adapter Output |

The **ADI-IN Adapter** provides an event interface `E1` and a data interface `D1` (type DINT). The **AS-OUT Adapter** provides `E1` and `D1` (type SINT).

## Functionality

Inside the composite module, a single function block `Convert` of type `iec61131::conversion::F_DINT_TO_SINT` is used. The signal connections are as follows:

1. An incoming event at the **ADI-IN adapter** (`E1`) triggers the **Convert FB** via its event input `REQ`.
2. Simultaneously, the DINT value is transferred from the adapter's data port `ADI_IN.D1` to the **Convert input** `IN`.
3. After the conversion is complete, **Convert** generates an event at its output `CNF`.
4. This event is forwarded directly to the **AS-OUT adapter** (`E1`).
5. The converted SINT value is available at the **Convert output** `OUT` and is transferred to the adapter data port `AS_OUT.D1`.

This enables complete, event-driven conversion from DINT to SINT via the adapter interfaces.

## Technical Details

- **License and Origin:** This module is subject to the **Eclipse Public License 2.0** and is from **HR Agrartechnik GmbH** (Version 1.0, Author: Franz Höpfinger, Date: 2026-02-17).
- **Dependency:** It uses the library module `iec61131::conversion::F_DINT_TO_SINT` from the IEC 61131 conversion package.
- **Composite Structure:** No separate states or algorithms are defined – all logic is executed by the internal network.
- **Packet Assignment:** The function block is organized in the package `adapter::conversion::unidirectional`.

## State Overview

As a composite function block, **ADI_TO_AS** does not have its own state machine. Its behavior results solely from the execution of the embedded function block `F_DINT_TO_SINT` and the hard-wired connections.

## Application Scenarios

- **Adapter Type Conversion:** When a component (e.g., a sensor or actuator) communicates via a unidirectional DINT adapter, but the target system expects a SINT adapter.
- **Data Range Reduction:** Applications where a 32-bit value needs to be converted to an 8-bit value, e.g.,... B. for controlling simple peripherals with limited resolution.
- **Interface adaptation:** Integration into a toolchain based on 4diac's unidirectional adapter concept, requiring a clean separation of event and data flows.

## Comparison with similar modules

Other adapter conversion modules exist, such as `ADI_TO_AI` (DINT → INT) or `ADI_TO_ADI` (identical passthrough). The **ADI_TO_AS** module differs in its specific target type conversion to SINT. All share a uniform adapter interface and event-driven processing via an integrated conversion module.

## Conclusion

The **ADI_TO_AS** is a compact, pre-built composite module that reliably and easily converts a DINT adapter signal to a SINT adapter signal. It is ideal for all applications requiring clean type conversion within the 4diac adapter concept, without the need to manually implement separate conversion logic. Thanks to its EPL 2.0 license, it can be freely used and adapted in your own projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
