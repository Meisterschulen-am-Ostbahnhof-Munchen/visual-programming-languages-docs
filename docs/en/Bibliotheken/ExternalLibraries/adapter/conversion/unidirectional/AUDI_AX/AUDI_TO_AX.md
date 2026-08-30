# AUDI_TO_AX

![AUDI_TO_AX](./AUDI_TO_AX.svg)

* * * * * * * * * *
The function block `AUDI_TO_AX` is a composite function block that converts an **AUDI** adapter (UDINT data) into an **AX** adapter (BOOL data). It serves as a unidirectional converter for applications where an integer value (e.g., from a counter) needs to be mapped to a binary signal – specifically, it checks whether the input value is non-zero. The function block is implemented as a pure network connection using IEC 61131-compliant components.
The function block does not have its own event inputs. The event to start processing is provided via the socket adapter `AUDI_IN` (see section Adapters).

The FB has no built-in event outputs. The result event is output via the plug adapter `AX_OUT` (see section Adapters).

The FB has no built-in data inputs. The UDINT value to be processed is provided via the socket adapter `AUDI_IN` (see section Adapters).

The FB has no built-in data outputs. The result (BOOL) is output via the plug adapter `AX_OUT` (see section Adapters).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Name | Type | Adapter Type | Direction | Comment |
| ------ | ----- | ------------------ | ---------- | ----------- |
| `AUDI_IN` | `adapter::types::unidirectional::AUDI` | Socket | Input | Provides the UDINT value (D1) and the associated event (E1) |
| `AX_OUT` | `adapter::types::unidirectional::AX` | Plug | Output | Provides the BOOL value (D1) and the acknowledgment event (E1) |

## Functionality

The internal process is divided into three steps:

1. **Event Reception:** The event `E1` of the socket adapter `AUDI_IN` triggers the processing.
2. **Comparison:** The received UDINT value (`AUDI_IN.D1`) is compared in the function block `F_NE` (IEC 61131-3: *not equal*) with the constant value `UDINT#0`.
3. **Result Output:** The result of the comparison (`F_NE.OUT`) – a BOOL – is placed on the output data port `AX_OUT.D1`. Simultaneously, the event `F_NE.CNF` is forwarded to the event input `AX_OUT.E1`, so that the output adapter signals the result.
4. **Result Output:** The result of the comparison (`F_NE.OUT`) – a BOOL – is placed on the output data port `AX_OUT.D1`. **Context:**

- If the input value is not equal to 0 → Output `TRUE`
- If the input value is equal to 0 → Output `FALSE`
- **Library Used:** The core consists of the IEC 61131 function block `F_NE` (non-equal comparison). This is imported from the library `iec61131::comparison::F_NE`.
- **No Dedicated ECC:** As a composite function block, `AUDI_TO_AX` does not have its own execution state – the entire logic is purely data flow-driven.
- **Unidirectional Adapters:** Both the input and output adapters are designed as *unidirectional*, meaning they only support a defined data and event flow from the source to the sink.
- - **Parameterization:** The comparison value is fixed at `UDINT#0` and cannot be externally parameterized.

The function block (FB) does not have its own state machine. Its behavior is entirely determined by incoming events: Every event at socket `AUDI_IN.E1` triggers an execution of the internal logic and an output at plug `AX_OUT`.

- **Binary Threshold Output:** A counter value (e.g., number of parts detected) should be passed on to a downstream controller as a switching signal (`TRUE` if present, `FALSE` if zero).
- **Network Simplification:** The function block encapsulates the non-zero logic, thereby reducing the complexity of higher-level function plans.
- **`AUDI_TO_BOOL` (hypothetical):** Would offer the same functionality, but without the adapter concept – possibly with direct data inputs/outputs.
- **Direct Comparison `F_NE`:** A single function block that performs the comparison, but without adapter adaptation.

The advantage of `AUDI_TO_AX` lies in its seamless integration into an adapter-based architecture, as is common in the 4diac IDE. It avoids additional conversion steps between different interface types.

The `AUDI_TO_AX` function block is a specialized yet highly useful converter for the unidirectional transfer of a UDINT value to a BOOL signal. By clearly encapsulating the comparison logic and using standard adapters, it simplifies the signal chain in IEC 61499-based automation systems. It is robust, easy to understand, and requires no complex configuration – ideal for common tasks such as binary meter reading.

---

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de
