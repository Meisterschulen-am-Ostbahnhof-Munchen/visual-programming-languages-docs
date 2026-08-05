# AD_SHL
![AD_SHL](./AD_SHL.svg)

* * * * * * * * * *
## Introduction
The function block **AD_SHL** performs a bitwise left shift of an input value. It is designed as a generic function block that communicates via adapter interfaces and supports any integer data type (ANY_INT). The actual shift operation is implemented internally by a predefined function block `F_SHL`.
## Interface Structure
### **Event Inputs**

| Event | Description | With Parameters |
|----------|----------------|---------------|
| `UPDATE` | Updates the shift count and starts the calculation. | `N` |

### **Event Outputs**
No direct event outputs are available. The event for passing the result is handled via the adapter `OUT` (event `OUT.E1`).

### **Data Inputs**

| Name | Type | Description |
|------|-----|--------------|
| `N` | `ANY_INT` | Number of bit positions to shift. |

### **Data Outputs**
No direct data outputs. The result of the shift is provided via the adapter `OUT` (data `OUT.D1`).

### **Adapter**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
| Socket | `IN` | `adapter::types::unidirectional::AD` | Receives the value to be shifted via the adapter channel. |
| Plug | `OUT` | `adapter::types::unidirectional::AD` | Provides the result of the left shift. |

## Functionality
The FB operates as a composite function block that delegates the actual operation to the block `F_SHL`. Internally, the following logic is implemented:

1. **Event Triggering**

- An incoming event from `UPDATE` or from the adapter `IN.E1` triggers the input `REQ` of the internal block `F_SHL`.
- The value of `N` is directly passed to the input `F_SHL.N`.

`` - The data value provided via the adapter `IN` (`IN.D1`) is forwarded to the `F_SHL.IN` input.

2. **Calculation**

The internal function block `F_SHL` (type `iec61131::bitwiseOperators::F_SHL`) performs a bitwise left shift of the input value by the number of times specified in `N`.

3. **Output**

The result of the calculation (`F_SHL.OUT`) is transferred to the data output of the plug adapter `OUT.D1`. Simultaneously, the event `F_SHL.CNF` signals the availability of the new result to the plug adapter (`OUT.E1`).

The function block is event-driven: Each arrival of a valid event (either externally via `UPDATE` or from the socket adapter `IN`) triggers a complete calculation.

## Technical Features
- **Adapter Interface**

Instead of fixed inputs and outputs, the function block uses adapters (`IN` as a socket, `OUT` as a plug), which enables flexible integration in various architectural contexts.

- **Generic Data Type**

The parameter `N` is declared as `ANY_INT`, allowing the function block to work with different integer types (e.g., `INT`, `DINT`, `LINT`), as long as the internal `F_SHL` supports them.

- **Combined Event Control**

Both the external event `UPDATE` and the event received from the socket adapter, `IN.E1`, can trigger the calculation. This enables both cyclic and data-driven updates.

- **Licensing**

This function block is licensed under the Eclipse Public License 2.0 and designed as a generic function block.

## State Overview

This function block is implemented as a **composite network** and does not have its own internal state machine (ECC). The sequence control is entirely determined by the event connections within the network and the `F_SHL` function block used. An explicit state machine is not required.

## Application Scenarios
- **Bit Manipulation in Control Engineering**

Shifting bit patterns for masking, scaling, or encoding signals.

- **Data Preparation in Communication Protocols**

Adapting data words by left shifting, e.g., for serial interfaces or bus systems.

- **Arithmetic Calculations**

Multiplication by powers of two by left shifting, especially in computationally critical environments.

## Comparison with Similar Blocks
- **Direct `F_SHL` Block**

The internal `F_SHL` offers the same functionality, but without an adapter interface. `AD_SHL` encapsulates this block and extends it with an adapter-based connection, which facilitates reuse in modular systems.

- **Adapter-Based Arithmetic Blocks**

Similar concepts exist for other bitwise operations (e.g., `AD_SHR`, `AD_AND`). `AD_SHL` specifies the left shift and can be used in a library of adapter-coupled logic blocks.

## Conclusion

The function block `AD_SHL` implements a bitwise left shift using an encapsulated `F_SHL` block and provides all functionality via a standardized adapter interface. Its generic design and flexible event control make it suitable for a wide range of applications in IEC 61499-based automation technology. Its composite structure makes it maintainable and easily extensible.
