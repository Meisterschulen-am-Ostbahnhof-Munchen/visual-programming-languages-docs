# UDINT_AUI_AX_SEL
![UDINT_AUI_AX_SEL](./UDINT_AUI_AX_SEL.svg)

* * * * * * * * * *
## Introduction
The function block **UDINT_AUI_AX_SEL** implements a binary selection between two input values. The selection is controlled via an adapter of type `AX`, which typically provides an axis position or a digital state. This block is used for flexible switching of signal sources in automation solutions.
## Interface Structure

### **Event Inputs**

| Event | Comment |

|----------|-----------|

| `EI0` | Sets the value of `IN0` |

| `EI1` | Sets the value of `IN1` |

### **Event Outputs**

| Event | Comment |

|----------|-----------|

| `CNF` | Confirmation of completed selection |

### **Data Inputs**

| Variable | Type | Comment |

|----------|-----|-----------|

| `IN0` | ANY_ELEMENTARY | First selectable input value |

| `IN1` | UINT | Second selectable input value (fixed type) |

### **Data Outputs**

| Variable | Type | Comment |

|----------|-----|-----------|

| `OUT` | UINT | Selected value (corresponds to `IN0` or `IN1`) |

### **Adapter**

| Adapter | Type | Comment |

|---------|-----|-----------|

| `G` | `adapter::types::unidirectional::AX` | Returns the binary selection signal (0/1) |

## Functionality

The function block (FB) operates in an event-driven manner:

1. Upon an event at `EI0`, the current value of `IN0` is internally adopted.

2. Upon an event at `EI1`, the current value of `IN1` is internally adopted.

3. The selection signal `G.D1` is continuously obtained via the adapter `G`. When `G.D1 = FALSE` is present, the value of `IN0` is forwarded to the output `OUT`; when `G.D1 = TRUE` is present, the value of `IN1` is output. 4. After successful internal processing, an event is sent at output `CNF` to confirm the selection.

The actual selection logic is implemented by an internal `F_SEL` function block (IEC 61131), which controls the two buffered values based on the selection signal `G.D1`.

## Technical Features
- **Flexible Input `IN0`**: The first input is declared as `ANY_ELEMENTARY`, allowing it to accept various elementary data types. The second input and the output are fixed to `UINT` – type conversion must be done externally.
- **Adapter-based control**: Selection is not made via a direct Boolean input, but via the adapter `AX`. This allows for loose coupling to physical or logical axis signals.
- **Event-driven update**: The values of `IN0` and `IN1` are only updated by explicit events, not cyclically. This ensures deterministic selection control.
- **Internal use of `F_SEL`**: The function block uses the proven IEC 61131 function block `selection::F_SEL` for its core logic.

## State overview

The function block does not have an explicit state machine. The sequence control is purely event-driven via the event inputs and the internal `F_SEL`. The input values are latched at the corresponding events and then continuously switched according to the selection signal.

## Application Scenarios
- **Axis-Dependent Signal Selection**: In a machine tool, switching between two measurement signal sources is possible via the axis position (provided by the `AX` adapter).
- **Redundant Sensor Selection**: With two sensors that deliver different values (e.g., one analog and one digital), the function block selects the active value based on an operating mode signal.
- **Configurable Operating Modes**: An adapter provides a switching command (0/1), thus enabling selection between two predefined setpoints.

## Comparison with Similar Function Blocks

Unlike a simple IEC 61131 `SEL` function block, which directly has a Boolean input `G`, `UDINT_AUI_AX_SEL` encapsulates the selection behind an adapter. This decouples the logic from the signal source and increases reusability. The function block also offers explicit event control for input value acquisition, whereas a standard `SEL` typically samples values cyclically.

## Conclusion

The **UDINT_AUI_AX_SEL** function block is a flexible binary selector characterized by its adapter-based control and event-driven updates. It is particularly suitable for applications where the selection of signal sources depends on external axis or state information and deterministic, non-cyclic processing is required.
