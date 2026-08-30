# ALR_TO_AS

![ALR_TO_AS](./ALR_TO_AS.svg)

* * * * * * * * * *

## Introduction

The **ALR_TO_AS** function block is a composite function block that converts an **LREAL adapter** (ALR) into a **SINT adapter** (AS). It encapsulates the conversion of a floating-point value (LREAL) into a signed 8-bit integer value (SINT) and provides the result data via the SINT adapter. This function block is typically used in automation technology when data needs to be transferred between different adapter interfaces.

## Interface Structure

### **Event Inputs**

The function block does not have separate event inputs. The conversion is controlled by the event of the connected **ALR Adapter Socket** (`ALR_IN.E1`).

### **Event Outputs**

The function block does not have separate event outputs. The completion of the conversion is signaled by the event of the **AS Adapter Plug** (`AS_OUT.E1`).

### **Data Inputs**

The function block does not have separate data inputs. The input data (LREAL value) is provided via the **ALR Adapter** (`ALR_IN.D1`).

### **Data Outputs**

The function block does not have separate data outputs. The output data (SINT value) is provided via the **AS adapter** (`AS_OUT.D1`).

### **Adapter**

| Adapter | Direction | Type | Description |
| --------- | ---------- | ----- | -------------- |
| `ALR_IN` | Socket | `adapter::types::unidirectional::ALR` | LREAL adapter input: provides the LREAL value to be converted and a trigger event (`E1`). |
| `AS_OUT` | Plug | `adapter::types::unidirectional::AS` | SINT adapter output: provides the converted SINT value and an acknowledgment event (`E1`). |

## Functionality

The function block is implemented as a composite FB. Internally, it contains a function block `F_LREAL_TO_SINT` from the IEC 61131 library. The connections within the network cause:

1. **Event-driven activation**: An incoming event at the adapter `ALR_IN` (`E1`) triggers the conversion FB (`Convert.REQ`).
2. **Data conversion**: The LREAL value of `ALR_IN.D1` is forwarded to the input `Convert.IN`. The function block (FB) converts this value into a SINT value (rounding according to IEC 61131 rules).
3. **Result Output**: After successful conversion, `Convert.CNF` signals an event to the output adapter `AS_OUT` (`E1`), and the converted SINT value is passed to `AS_OUT.D1`.

This enables synchronous, event-driven conversion of an LREAL value to a SINT value via adapter interfaces.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- **Composite Structure**: The function block completely encapsulates the conversion logic in a network, making the implementation transparent and easily extensible.
- **Adapter-based**: Instead of individual event and data ports, standardized unidirectional adapters (`ALR` and `AS`) are used. This simplifies integration into existing adapter-based architectures.
- **Reuse**: The internal function block `F_LREAL_TO_SINT` is a proven IEC function block and ensures correct conversion to the standard.
- **No dedicated state machine**: Since this is a composite function block, there is no independent state machine; control is achieved solely through the connected adapter events.

## State Overview

The function block does not have an explicit state machine. Its behavior is determined by the internal function block `F_LREAL_TO_SINT` and the event connections. This internal function block (FB) executes a simple **IDLE → CONVERTING → DONE** cycle, controlled by the events `REQ` and `CNF`. For the user, the block is therefore transparent and usable as an **event-driven converter**.

## Application Scenarios

- **Data Bridge Between Systems**: When a control module provides LREAL values via a `ALR` adapter, but a downstream module expects SINT values via a `AS` adapter.
- **Uniform Adapter Interfaces**: Simplifying system design by outsourcing conversions to standalone function blocks.
- **PLC Connection**: Connecting sensors or actuators that operate with LREAL accuracy to a SINT-based bus communication.

## Comparison with Similar Components

Compared to directly wiring a `F_LREAL_TO_SINT` component with individual event/data ports, the `ALR_TO_AS` component offers **a higher level of abstraction through adapters**. This facilitates the exchange of data between components that are already designed for adapter interfaces. Similar components could be `ALR_TO_ADI` (conversion to INT) or `ALR_TO_UDI` (conversion to UDINT), which are structured analogously but use different target data types.

## Conclusion

The `ALR_TO_AS` function block is a clean, adapter-based solution for converting LREAL to SINT values in the 4diac IDE. Its composite structure and use of standardized IEC conversion blocks ensure reliable, event-driven data conversion and facilitate integration into modular automation systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
