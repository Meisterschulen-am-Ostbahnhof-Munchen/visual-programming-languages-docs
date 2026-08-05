# ADI_TO_ALI

![ADI_TO_ALI](./ADI_TO_ALI.svg)

* * * * * * * * * *
## Introduction
The **ADI_TO_ALI** function block is a composite block that converts a unidirectional ADI adapter (DINT data type) into a unidirectional ALI adapter (LINT data type). It adapts the data width from 32 bits to 64 bits, thus enabling the seamless integration of components of different integer types in automation systems according to IEC 61499-2. The block is available under the Eclipse Public License 2.0.



``` ## Interface Structure
### **Event Inputs**
None

### **Event Outputs**
None

### **Data Inputs**
None

### **Data Outputs**
None

### **Adapters**
- **ADI_IN** (Socket) – Type: `adapter::types::unidirectional::ADI`

Accepts a DINT value (32-bit) and its associated event.

- **ALI_OUT** (Plug) – Type: `adapter::types::unidirectional::ALI`

Outputs the converted LINT value (64-bit) and the forwarded event.

## Functionality
This function block implements direct passthrough:

- The event `E1` from the ADI_IN socket is passed to the ALI_OUT plug without delay.

- Simultaneously, the data value `D1` (DINT) is transmitted; this involves an implicit type conversion from 32-bit integer (DINT) to 64-bit integer (LINT).

- No intermediate storage or processing logic takes place – every incoming event-data combination is immediately forwarded to the output side.

## Technical Features

- **No internal state** – The function block is entirely combinatorial and has no memory.

- **Automatic type conversion** via the data connection; the value range of DINT is fully covered by LINT, so no information loss occurs.

- **Adapter-based communication** according to IEC 61499-2 enables loose coupling and reusability.

- The function block is implemented as a composite, meaning its behavior is defined solely by the internal function block network (one event and one data connection).

## State Overview
This function block does not have a state machine. Its functionality is limited to the direct forwarding of adapter signals.

## Application Scenarios

- **System migration** from 32-bit to 64-bit data processing, e.g., during the modernization of controllers.

- **Integration of older components** that provide DINT values into new modules that require LINT interfaces.

- **Adapter bridge** in heterogeneous networks to adapt different integer types between function blocks.

## Comparison with Similar Function Blocks
Simple type converters (e.g., `DINT_TO_LINT`) usually operate at the data level without event forwarding. The `ADI_TO_ALI` block, on the other hand, encapsulates events and data in an adapter interface and is therefore particularly suitable for modular, event-driven architectures. Compared to manual conversion over the network, it reduces complexity and increases system readability.

## Conclusion
`ADI_TO_ALI` is a minimal yet effective block for adapting the data width between DINT and LINT adapters. Its simple pass-through logic and automatic type conversion make it a useful tool for bridging integer types in IEC 61499 systems. Compliance with the standard and licensing under EPL 2.0 ensure open usability and interoperability.