# AUDI_TO_AUI

![AUDI_TO_AUI](./AUDI_TO_AUI.svg)
*No image available.*

* * * * * * * * * *
## Introduction

The function block `AUDI_TO_AUI` is a composite block that converts an AUDI adapter (data type UDINT) into an AUI adapter (data type UINT). It serves as a simple interface adapter between components that use different integer data types for their unidirectional adapters. The block encapsulates the conversion and enables seamless integration into IEC 61499 networks.
## Interface Structure

### **Event Inputs**

The function block does not have a direct event input at the top level. Events are received via socket `AUDI_IN`:

- **E1** – Trigger for the conversion of a new data value.

### **Event Outputs**

The FB does not have a direct event output at the top level. Events are sent via the plug `AUI_OUT`:

- **E1** – Confirmation that the converted value is present at the output.

### **Data Inputs**

The FB does not have a direct data input at the top level. Data is received via the socket `AUDI_IN`:

- **D1** (`UDINT`) – The input value to be converted.

### **Data Outputs**

The FB does not have a direct data output at the top level. Data is output via the plug `AUI_OUT`:

- **D1** (`UINT`) – The converted output value.

### **Adapters**

- **Socket `AUDI_IN`** – Unidirectional input adapter of type `adapter::types::unidirectional::AUDI`. It returns an event `E1` and a data value `D1` (type `UDINT`).
- **Plug `AUI_OUT`** – Unidirectional output adapter of type `adapter::types::unidirectional::AUI`. It expects an event `E1` and outputs a data value `D1` (type `UINT`).

## Functionality

The module is implemented as a composite and internally contains the function block `iec61131::conversion::F_UDINT_TO_UINT`. The sequence is event-driven:

1. An event at socket `AUDI_IN.E1` triggers the input `REQ` of the internal conversion module.
2. Simultaneously, the data value `AUDI_IN.D1` is transferred to the input `IN` of the converter.
3. The converter performs the conversion from `UDINT` to `UINT`.
4. Upon completion, the converter sends an event at its output `CNF`, which is forwarded to plug `AUI_OUT.E1`.
5. The converted value at the converter's output `OUT` is placed on the data output `AUI_OUT.D1`.

The entire conversion takes place within a single event pass (synchronously).

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- **Composite Architecture:** The function block is designed as a composite, meaning its functionality is entirely determined by the internal network. This facilitates reuse and adaptation.
- **Standard Conversion Block:** The actual type conversion uses the IEC 61131 block `F_UDINT_TO_UINT`, which provides a platform-independent and tested implementation.
- **License:** The block is licensed under the Eclipse Public License 2.0 (EPL-2.0).
- **Version:** 1.0, released on February 17, 2026.

## State Overview

The FB (Function Block) has no states of its own. Since the composite network consists of only a single functional block, which itself operates without state, `AUDI_TO_AUI` also behaves without state. Each event pulse immediately triggers a one-time conversion.

## Application Scenarios

- **Connecting Sensors/Actuators:** A sensor delivers values as `UDINT` via an AUDI adapter, while the subsequent processing chain expects `UINT` via AUI.
- **System Integration:** Different data types often occur in heterogeneous automation systems. The block serves as an adapter to connect components from different manufacturers or libraries.
- **Prototype Development:** Simple and quick adaptation of interfaces without manual conversion logic.

## Comparison with Similar Function Blocks

- **`AUDI_TO_XXX` Function Blocks:** Analogous function blocks exist for other target types (e.g., `AUDI_TO_DINT`, `AUDI_TO_SINT`). `AUDI_TO_AUI` is specific for conversion to `UINT`.
- **Direct Adapter Coupling:** Without a conversion block, type conversion would have to be performed in the application itself or via a generic function block. `AUDI_TO_AUI` offers an encapsulated, reusable solution.

## Conclusion

The `AUDI_TO_AUI` function block provides a compact and reliable way to mediate between two unidirectional adapters with different data types. Thanks to its composite structure and the use of a standardized conversion module, it requires little maintenance and can be easily integrated into existing IEC 61499 projects.
