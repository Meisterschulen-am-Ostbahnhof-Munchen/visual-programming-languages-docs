# AUDI_AX_SEL_REQ
![AUDI_AX_SEL_REQ](./AUDI_AX_SEL_REQ.svg)

* * * * * * * * * *
## Introduction
The function block **AUDI_AX_SEL_REQ** implements a binary selection between two input values. It is triggered by an event input or an adapter and outputs the selected value along with an acknowledgment. This function block is specifically designed for use with a unidirectional adapter of type `AX` and is suitable for applications where the selection is controlled by an external component.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| `REQ` | Event | Service Request; triggers the selection |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| `CNF` | Event | Confirmation; output after selection |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| `IN0` | UDINT | First selectable value |

| `IN1` | UDINT | Second selectable value |

### **Data Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| `OUT` | UDINT | Selected Value (corresponds to either IN0 or IN1) |

### **Adapter**

| Name | Type | Comment |

|------|-----|------------|

| `G` | Socket: `adapter::types::unidirectional::AX` | Selector; provides the selection signal (via data output `D1`) and an event `E1` |

## Functionality
The function block internally contains a block of type `iec61131::selection::F_SEL`. This performs the actual selection:

- The adapter's data output `G.D1` is connected to the selector input of `F_SEL`.
- The value of `F_SEL.OUT` is equal to `IN0` if `G.D1 = FALSE` is present, and equal to `IN1` otherwise.

The event `REQ` and the adapter event `G.E1` are routed to the `REQ` input of `F_SEL`. Since the event linking is implemented as an OR gate, the selection is triggered as soon as either event occurs. After processing, `F_SEL` outputs the confirmation event `CNF` and the selected value `OUT`.

The event `F_SEL` is also routed to the `REQ` input of `F_SEL`. The internal connection ensures that `OUT` always represents the currently valid value (IN0 or IN1) at the time of the triggering event.

## Technical Features
- **Adapter-Based Selection**: The selection value is not provided directly as a BOOL, but via an adapter. This enables loose coupling and reuse of the adapter type `AX`.
- **Dual Triggering**: The selection can be triggered either by an external `REQ` event or by an event from the adapter (`G.E1`) – or by both simultaneously.
- **Integrity**: Because the internal `F_SEL` is based on IEC 61131, deterministic selection and transmission times are guaranteed.
- **Type Stability**: All data ports are defined as `UDINT` (unsigned 32-bit integer), allowing even large values to be processed without overflow.

## State Overview
The function block (FB) does not have its own state machine. Its behavior is entirely determined by the internal `F_SEL` block:

- **Wait**: No pending event – no output.
- **Selection**: Upon arrival of `REQ` or `G.E1`, `OUT` is set and `CNF` is output.

## Application Scenarios
- **Switching Operating Modes**: Selection between two setpoints (e.g., speed, pressure) depending on an external selector.
- **Source Switching**: Selection between two signal sources (e.g., measurement data from different sensors) and output of the currently valid value.
- **Safety Logic**: Separation of normal operation and emergency operation through binary selection of critical parameters.

## Comparison with Similar Function Blocks
- **Standard MUX (IEC 61131 MUX)**: A MUX selects from more than two inputs and requires an index. The `AUDI_AX_SEL_REQ` is limited to two inputs and uses an adapter instead of a direct BOOL input.
- **BOOL SEL Function Blocks**: Simple selectors with BOOL input often only have one event input. This function block additionally allows triggering via the adapter, enabling flexible control.
- **Adapter-Based Solutions**: Compared to hard-wired selectors, the adapter offers greater modularity – the triggering adapter can be exchanged depending on the context.

**Adapter-Based Solutions**:
## Conclusion

The `AUDI_AX_SEL_REQ` is a compact yet flexible binary selector that distinguishes itself from simple selectors through its combination of adapter connectivity and dual triggering. It is particularly well-suited for modular automation solutions where the selection signal is provided by an external component and reliable, immediate forwarding of the result is required. The use of standardized IEC types and clear interfaces facilitates integration into existing control architectures.
