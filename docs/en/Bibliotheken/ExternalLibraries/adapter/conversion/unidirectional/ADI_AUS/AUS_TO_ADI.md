# AUS_TO_ADI

![AUS_TO_ADI](./AUS_TO_ADI.svg)

* * * * * * * * * *
## Introduction

The function block AUS_TO_ADI is a composite function block that performs a unidirectional adapter conversion from `AUS` (data of type `USINT`) to `ADI` (data of type `DINT`). It encapsulates an IEC 61131 conversion block, thus enabling a clean separation of adapter types in the 4diac IDE.
## Interface Structure

### **Event Inputs**

No separate event inputs are available. Event control is handled via the socket adapter `AUS_IN` (see section **Adapters**).

### **Event Outputs**

No separate event outputs are available. Event forwarding is handled via the plug adapter `ADI_OUT` (see section **Adapters**).

### **Data Inputs**

No separate data inputs are available. Data is provided via the socket adapter `AUS_IN`.

### **Data Outputs**

No separate data outputs are available. The converted data is output via the plug adapter `ADI_OUT`.

### **Adapters**

| Name | Direction | Type | Description |
|------|----------|-----|--------------|
| `AUS_IN` | Socket (Input) | `adapter::types::unidirectional::AUS` | Unidirectional adapter input that provides a `USINT` value (and an associated event). |
| `ADI_OUT` | Plug (Output) | `adapter::types::unidirectional::ADI` | Unidirectional adapter output that outputs the converted `DINT` value (and an associated event). |

## Functionality

The module operates in an event-driven manner:

1. An incoming event at socket `AUS_IN.E1` triggers the internal conversion module `Convert` (type `F_USINT_TO_DINT`).
2. The conversion module reads the data value `AUS_IN.D1` (`USINT`) and converts it into a `DINT` value.
3. After the conversion is complete, an event is generated at output `Convert.CNF`.
4. This event is forwarded to the plug adapter `ADI_OUT.E1`, and the converted value is output via `ADI_OUT.D1`.

All logic is represented as data flow within the internal function block network – no state machine logic is used within the composite block.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- The block uses the IEC 61131 block `F_USINT_TO_DINT` (type conversion of unsigned 8-bit to signed 32-bit integer).
- It is a pure **composite block** – its behavior is entirely defined by the internal function block network.
- The adapters are designed to be **unidirectional**: data flows only from the socket to the plug.
- By encapsulating the conversion in a separate block, different adapter types can be interconnected without requiring the surrounding application to convert the types.

## State Overview

The block does not have its own state machine. Its behavior is controlled directly by the internal conversion block and the event connections. Error handling (e.g., range exceeding during conversion) is not explicitly implemented and would need to be added either in the calling context or by extending the function block.

## Application Scenarios

- **Adapter Bridge**: Exchange of data between components that use different adapter types (e.g., sensors with `USINT` values and controllers that expect `DINT` values).
- **Data Integration**: Integration of function blocks from IEC 61131 libraries into a 4diac application based on adapters.
- **Type Conversion**: Fast conversion of data types at the adapter level without having to change the logic of the connected function blocks.

## Comparison with Similar Modules

- Unlike directly using the conversion module `F_USINT_TO_DINT`, `AUS_TO_ADI` offers an adapter-oriented interface. This makes the conversion completely transparent for the user, who only works with the adapters.
- Similar adapter conversions may exist for other data types (e.g., `BOOL_TO_ADI`, `INT_TO_ADI`). This module is specifically designed for converting `USINT` to `DINT`.

## Conclusion

The `AUS_TO_ADI` composite block offers a simple and clean way to convert a `AUS` adapter (USINT-based) into a `ADI` adapter (DINT-based). Thanks to the internal use of the IEC 61131 conversion block, the conversion is standards-compliant and reusable. The block is particularly suitable for modular applications where different adapter types need to be harmonized.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
