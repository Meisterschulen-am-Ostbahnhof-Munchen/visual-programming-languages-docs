# AUDI_UDINT_AX_SEL
![AUDI_UDINT_AX_SEL](./AUDI_UDINT_AX_SEL.svg)

* * * * * * * * * *
## Introduction
The function block `AUDI_UDINT_AX_SEL` implements a binary selection between two input values. It selects either the value of `IN0` or `IN1` to output `OUT`, controlled by a connected adapter of type `AX`. The selection is triggered once by an event from the adapter. Additional events allow the inputs to be updated.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |

|------|-----|---------------|

| `EI0` | Event | Sets input `IN0` (value is linked to data input `IN0`) |

| `EI1` | Event | Sets input `IN1` (value is linked to data input `IN1`) |

### **Event Outputs**

| Name | Type | Description |

|------|-----|---------------|

| `CNF` | Event | Confirmation of selection (sent after successful selection) |

### **Data Inputs**

| Name | Type | Description |

| Name | Type | Description |

| |------|-----|--------------|

| `IN0` | UDINT | First selectable input value (unsigned 32-bit integer) |

| `IN1` | ANY_ELEMENTARY | Second selectable input value (any elementary data type) |

### **Data Outputs**

| Name | Type | Description |

|------|-----|--------------|

| `OUT` | UDINT | Result of binary selection (the selected value, as a UDINT) |

### **Adapters**

| Name | Type | Description |

|------|-----|---------------|

| `G` | adapter::types::unidirectional::AX | Control adapter: provides the selection criterion (data `G.D1`) and the trigger signal (`G.E1`) for the selection |

## Functionality
The function block operates in two steps:

1. **Input Update:** The values of `IN0` and `IN1`, respectively, can be stored in the internal context via the events `EI0` and `EI1`. These events are not directly related to the actual selection but serve to separate data acquisition and selection in time.

## Functionality 2. **Selection:** An event on `G.E1` (from adapter `G`) triggers the internal function block `F_SEL` (type `iec61131::selection::F_SEL`). The adapter data value `G.D1` (type `AX`) determines which input is assigned to the output:
- If `G.D1 = FALSE` (0), `IN0` is assigned to `OUT`.
- At `G.D1 = TRUE` (1), `IN1` is replaced by `OUT`.

After successful selection, the event `CNF` is sent.

The data output `OUT` is always of type `UDINT`. The input `IN1` allows any elementary data types, which are implicitly converted to `UDINT` during selection. If this conversion is not possible, the function block may generate an error (depending on the runtime environment).

The data output `OUT` is always of type `UDINT`.
## Technical Features

- **ANY_ELEMENTARY Support:** The second input, `IN1`, can accept values of different elementary types (e.g., SINT, INT, REAL, BOOL). Conversion to UDINT is automatic.
- **Adapter-Based Control:** Selection is not implemented via a discrete data input, but rather via an adapter – this allows for clean encapsulation of the selector signal (e.g., from a sensor or control logic).
- **Event-Driven Update:** The inputs `IN0` and `IN1` are updated only when needed via the events `EI0`/`EI1`, which can optimize communication over fieldbuses.

## State Overview

The function block does not contain an explicit state machine. Its functionality is purely event-driven:

- After setting `IN0` or `IN1` (via `EI0`/`EI1`), the function block waits for the trigger signal from the adapter `G.E1`.
- Upon receiving `G.E1`, `F_SEL` is executed immediately, and `CNF` is output.
- Between these steps, the function block is in a passive idle state.

...
## Application Scenarios

- **Selection between two measured values:** A sensor provides the selection criterion (e.g., threshold exceedance) via the adapter `G`. `IN0` could represent a minimum value, and `IN1` a maximum value.
- **Switching parameter sets:** Two different configuration values are loaded via `EI0` and `EI1`. An external controller activates the appropriate configuration via `G`.
- **Redundant signals:** Two redundant sources (e.g., speed sensors) provide the values, and a signal determines which source is used.

## Comparison with similar components

| Component | Properties |

|----------|---------------|

| `MUX` (IEC 61131) | Multiple inputs, index selection; requires one index input as a scalar value. |

| `SEL` (IEC 61131) | Binary selection with one BOOL input. |

| `AUDI_UDINT_AX_SEL` | Adapter-controlled binary selection with separate input updates, specifically for UDINT output and support for ANY_ELEMENTARY. |

Compared to standard IEC function blocks, this function block offers decoupled communication via adapters and extracted events for data acquisition – advantageous in modular, event-driven systems.

```
## Conclusion

The function block `AUDI_UDINT_AX_SEL` represents a flexible, adapter-controlled binary selection. It is particularly suitable for applications where the selector signal originates from an external device (e.g., a PROFINET adapter) and the input values need to be updated asynchronously. Support for `ANY_ELEMENTARY` at the second input increases reusability, while the unified `UDINT` output simplifies further processing.
