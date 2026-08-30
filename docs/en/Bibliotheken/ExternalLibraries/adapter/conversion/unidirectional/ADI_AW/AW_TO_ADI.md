# AW_TO_ADI

![AW_TO_ADI](./AW_TO_ADI.svg)

* * * * * * * * * *

## Introduction

The **AW_TO_ADI** function block is a composite block that converts a unidirectional WORD adapter (AW) into a unidirectional DINT adapter (ADI). It enables the seamless integration of components that work with WORD data into systems that expect DINT values. Internally, the block uses the standard conversion block `F_WORD_TO_DINT` from the IEC 61131 library.

## Interface Structure

### **Event Inputs**

- **No Direct Event Inputs**

The block does not have any standalone event inputs. The triggering event is provided via the socket adapter `AW_IN`.

### **Event Outputs**

- **No Direct Event Outputs**

This function block has no independent event outputs. The result event is passed on via the plug adapter `ADI_OUT`.

### **Data Inputs**

- **No Direct Data Inputs**

The WORD value to be converted is received via the socket adapter `AW_IN`.

### **Data Outputs**

- **No Direct Data Outputs**

The converted DINT value is output via the plug adapter `ADI_OUT`.

### **Adapters**

| Name | Type | Direction | Description |
| --------- | ----------------------------- | ---------- | -------------- |
| `AW_IN` | `adapter::types::unidirectional::AW` | Socket (Input) | WORD adapter as input. Returns the trigger event (E1) and the WORD data value (D1). |
| `ADI_OUT` | `adapter::types::unidirectional::ADI` | Plug (Output) | DINT adapter as output. Returns the acknowledgment event (E1) and the converted DINT value (D1). |

## Functionality

1. An incoming event at socket `AW_IN.E1` triggers the internal function block `F_WORD_TO_DINT` via its event input `REQ`.
2. Simultaneously, the WORD data value from `AW_IN.D1` is transferred to the data input `IN` of `F_WORD_TO_DINT`.
3. After the conversion is complete, `F_WORD_TO_DINT` generates an acknowledgment event at `CNF`.
4. This event is forwarded to plug `ADI_OUT.E1`, while the converted DINT value is transferred from `F_WORD_TO_DINT.OUT` to `ADI_OUT.D1`.

The entire process is thus synchronous: A pulse at the WORD adapter results in a pulse at the DINT adapter with the converted value.

## Technical Features

- **Pure Coupling:** The block contains no logic of its own, but simply connects the adapter interfaces to an existing conversion block.
- **Use of IEC 61131 Standard Blocks:** The actual conversion is performed by `F_WORD_TO_DINT`, which provides a defined and standardized conversion.
- **Unidirectional Adapters:** Both `AW_IN` and `ADI_OUT` are designed as unidirectional adapters, meaning they only transport events and data in one direction.
- **No Internal States:** As a composite device, `AW_TO_ADI` has no internal states of its own – its behavior is entirely determined by the interconnection of its constituent elements.

## State Overview

Since this is a composite device without its own state machine, there is no separate state overview. The runtime behavior is determined by the embedded `F_WORD_TO_DINT`, which performs a processing step after an input event and outputs the result.

## Application Scenarios

- **Agricultural Technology:** Connecting sensors or actuators that deliver WORD data (e.g., via fieldbuses with 16-bit values) to controllers that require DINT.
- **Migration of Legacy Systems:** Replacing WORD-based interfaces with modern DINT components without redesigning the entire architecture.
- **Adapter Encapsulation:** Integrating libraries or modules designed for different data types using a single adapter converter.

## Comparison with Similar Components

- **Direct Conversion:** Unlike a simple `F_WORD_TO_DINT`, `AW_TO_ADI` offers an adapter-based interface that enables loose coupling between components.
- **Bidirectional Converters:** There are modules that combine both forward and reverse conversion (e.g., WORD ↔ DINT) in a single module. This module is intentionally designed to be unidirectional.
- **Type Conversion via Flexible Adapters:** Other adapter converters use generic or polymorphic interfaces; this module is specifically designed for WORD-to-DINT conversion.

## Conclusion

The `AW_TO_ADI` is a simple yet effective composite module for converting a WORD adapter to a DINT adapter. By using a standardized conversion module and clear adapter interfaces, it is particularly well-suited for use in modular automation solutions where data type conversions between components are required. Its structure is transparent, easy to understand, and allows for rapid integration into existing projects.
