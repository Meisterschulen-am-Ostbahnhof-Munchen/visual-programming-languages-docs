# UDINT_AUDI_AX_SEL

![UDINT_AUDI_AX_SEL](./UDINT_AUDI_AX_SEL.svg)

* * * * * * * * * *
## Introduction

The function block **UDINT_AUDI_AX_SEL** implements a binary selection between two input values. The selection is performed via an adapter (type `AX`), which provides an external control signal. Depending on the adapter's state, either the value at input `IN0` or `IN1` is passed to output `OUT`.
## Interface Structure

### **Event Inputs**

| Event | Comment | With Data |
|------------- |---------------------------|--------------------|
| `EI0` | Set IN0 | `IN0` |
| `EI1` | Set IN1 | `IN1` |

### **Event Outputs**

| Event | Comment |
|------------- |-------------------------------------------|
| `CNF` | Confirmation of requested operation |

### **Data Inputs**

| Variable | Type | Comment |
|----------|------------------|-------------------------------|
| `IN0` | `ANY_ELEMENTARY` | First Selectable Input |
| `IN1` | `UDINT` | Second Selectable Input |

### **Data Outputs**

| Variable | Type | Comment |
|----------|---------|---------------------------|
| `OUT` | `UDINT` | Selected Input Value |

### **Adapters**

| Adapter | Type | Comment |
|---------|------------------------------------------|--------------------|
| `G` | `adapter::types::unidirectional::AX` | Selection Control |

The adapter `G` provides the event `E1` and the data value `D1`, which serves as a selection signal.

- If the selection signal is **0**, `IN0` is used.
- If the selection signal is **1** (or other than 0), `IN1` is used.

## Functionality

The function block has two input events, `EI0` and `EI1`, which set the data `IN0` and `IN1`, respectively – but do not directly trigger the selection. The actual selection is triggered by an external event, which is passed via the adapter `G` to the internal function block `F_SEL` (type `iec61131::selection::F_SEL`).

When the adapter sends its event `E1`, the `F_SEL` block is controlled. The selection is based on the data value `D1` transmitted by the adapter:

- **D1 = 0** → Output `OUT` receives the value of `IN0`.

- **D1 ≠ 0** → Output `OUT` receives the value of `IN1`.

The event `CNF` is then output to confirm successful processing.

## Technical Features

- The input `IN0` is declared as `ANY_ELEMENTARY`, meaning it can accept values of different elementary types. However, the output `OUT` is fixed as `UDINT` – an implicit type conversion (e.g., from INT, DINT, REAL) occurs when passing the output to `F_SEL`.

- The function block internally uses a predefined `F_SEL` function block (from the IEC 61131 library) that performs the actual binary selection.

- The events `EI0` and `EI1` serve only to update the corresponding data values; the selection is only triggered by the adapter event.

## State Overview

The function block does not have an explicit state machine. Processing is event-driven:

1. **Receive of `EI0` or `EI1`** → Set the respective data value (no output event).
2. **Receive of the adapter event `G.E1`** → Perform the selection and send `CNF`.

The internal logic is purely combinatorial, triggered by the adapter event.

## Application Scenarios

- Switching between two sensor readings (e.g., different measuring ranges) depending on an operating mode.
- Selection of a parameter set (IN0 = default value, IN1 = substitute value) controlled by an external condition.
- Flexible routing of signals in an automation application with minimal configuration.

## Comparison with Similar Function Blocks

| Function Block | Property |
|---------------------|-----------------------------------------------------------------------------|
| `UDINT_AUDI_AX_SEL` | Binary selection, external selection signal via adapter, two inputs + conversion from ANY_ELEMENTARY to UDINT. |
| `F_SEL` | Pure IEC 61131 binary selection without an adapter (control signal as the third input). |
| `MUX` | Selection from more than two channels, typically with an index input. |

This function block extends `F_SEL` with adapter-based control and more flexible typing of the first input.

## Conclusion

The **UDINT_AUDI_AX_SEL** is a specialized selection function block for applications where the selection signal must be provided externally via an adapter. The combination of a universal `ANY_ELEMENTARY` input and a fixed `UDINT` output makes it versatile, but requires correct type compatibility. By reusing the proven `F_SEL` block, the functional logic remains robust and predictable.
