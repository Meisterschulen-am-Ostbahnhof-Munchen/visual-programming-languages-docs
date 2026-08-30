# ALI_TO_ADI

![ALI_TO_ADI](./ALI_TO_ADI.svg)

* * * * * * * * * *

## Introduction

This composite function block converts an **ALI** adapter type (LINT, 64-bit integer) to an **ADI** adapter type (DINT, 32-bit integer). It enables seamless integration of components using different adapter formats by encapsulating data conversion and synchronizing it via event control.

## Interface Structure

### **Event Inputs**

No direct event inputs are available. Control is handled via the incoming adapter **ALI_IN**.

### **Event Outputs**

No direct event outputs are available. Output is clocked via the outgoing adapter **ADI_OUT**.

### **Data Inputs**

No direct data inputs are available. The input data is provided via the **ALI_IN** adapter (of type ALI).

### **Data Outputs**

No direct data outputs are available. The converted data is output via the **ADI_OUT** adapter (of type ADI).

### **Adapters**

| Name | Type | Direction | Description |
| ------ | ----- | ---------- | -------------- |
| **ALI_IN** | `adapter::types::unidirectional::ALI` | Socket (Input) | Returns the LINT value and an associated event (E1). |
| **ADI_OUT** | `adapter::types::unidirectional::ADI` | Plug (Output) | Outputs the converted DINT value and an acknowledgment event (E1). |

## Functionality

The component contains the instance `Convert` of type `iec61131::conversion::F_LINT_TO_DINT`.

The event and data connections are configured as follows:

- The event `ALI_IN.E1` triggers the conversion via `Convert.REQ`.
- The data value `ALI_IN.D1` is passed to `Convert.IN`.
- After successful conversion, `Convert.CNF` signals the event `ADI_OUT.E1`.
- The result value `Convert.OUT` is forwarded to `ADI_OUT.D1`.

Thus, with each event at the input adapter, the LINT value is converted to a DINT value and synchronously provided via the output adapter.

## Technical Features

- **Numeric conversion**: value-preserving cast (narrowing may truncate, widening/sign-extension is safe).

- **Composite Block**: The function block encapsulates the conversion in a reusable adapter-to-adapter converter.
- **Data Type Conversion**: A 64-bit to 32-bit integer conversion takes place. Values outside the DINT range (−2³¹ … 2³¹−1) result in an overflow or a limit (depending on the implementation).
- **Event Synchronization**: The conversion is strictly timed through the event chain; a new value is only processed after a previous event.

## State Overview

The block does not have its own state machine (ECC). Its entire logic is implemented by the internal function block `F_LINT_TO_DINT`, which operates as a simple conversion block without state behavior.

## Application Scenarios

- Connecting a component that provides a 64-bit counter or timestamp (LINT) to a system that only supports 32-bit DINT adapters.
- Migrating legacy systems with 32-bit arithmetic to newer 64-bit sensors without changing the entire adapter landscape.
- Intermediate layer in a hierarchy where different integer widths meet.

## Comparison with Similar Blocks

Separate conversion blocks such as `F_LINT_TO_DINT` exist for direct data conversions. The `ALI_TO_ADI` function block stands out because it fully integrates the conversion into the adapter interface. Instead of multiple discrete function blocks and manual adapter wiring, all the logic is combined in a reusable composite block that automatically handles the event and data streams.

## Conclusion

The `ALI_TO_ADI` function block offers a clean, encapsulated solution for converting LINT to DINT adapters. By using a composite block, it reduces application complexity and ensures standardized, event-driven conversion between different integer widths in the IEC 61499 environment.
