# AUDI_AX_SEL

![AUDI_AX_SEL](./AUDI_AX_SEL.svg)

* * * * * * * * * *

## Introduction

The function block **AUDI_AX_SEL** implements a binary selection between two data values. It accepts two input values, each set via separate events, and outputs the corresponding value upon a selection event controlled by an adapter. The block integrates a standardized IEC 61131-3 selector (F_SEL) and extends it with event-driven interfaces.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| `EI0` | Event | Sets the value for `IN0` |

| `EI1` | Event | Sets the value for `IN1` |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| `CNF` | Event | Confirmation of the requested selection (issued after successful processing) |

### **Data Inputs**

| Name | Data Type | Comment |

|------|----------|-----------|

| `IN0` | UDINT | First selectable value |

| `IN1` | UDINT | Second selectable value |


### **Data Outputs**

| Name | Data Type | Comment |

|------|----------|-----------|

| `OUT` | UDINT | Selected value (corresponds to `IN0` or `IN1`) |

### **Adapters**

| Name | Type | Comment |

|------|-----|-----------|

| `G` | `AX` (unidirectional) | Controls selection via an event (`E1`) and a date (`D1`) |

## Functionality

The function block is internally constructed from the standard function block `F_SEL` (IEC 61131-3).

1. **Value Transfer**: Upon the occurrence of the events `EI0` or `EI1`, the corresponding data values are forwarded to the internal selector. `EI0` sets the value for `IN0`, and `EI1` sets the value for `IN1`.


2. **Selection**: The adapter `G` represents a control interface. When the event `G.E1` is received, the internal `F_SEL` block is triggered via its `REQ` input. The date `G.D1` (type Bool – implicitly defined by the adapter) determines which input is selected:

- `G.D1 = FALSE` → `OUT = IN0`

- `G.D1 = TRUE` → `OUT = IN1`

3. **Output**: After selection, the result is output on `OUT` and the confirmation event `CNF` is sent.

The adapter allows loose coupling of the control logic; the actual selection decision can be provided by another function block or a higher-level component.


## Technical Features

- **Integration of an IEC 61131-3 Standard Function Block**: Internally, `F_SEL` is used, ensuring that the selection process conforms to the industry standard in terms of semantics and timing.

- **Adapter-Based Control**: The selection decision is not made via a direct Boolean input, but rather via a unidirectional adapter, `AX`. This improves modularity and allows for the replacement of the control logic without modifying the function block.

- **Event-Driven Value Setting**: Each input value is set via its own event – this allows for asynchronous updates before the final selection is triggered.

## State Overview

The function block has implicit state logic based on the behavior of the internal `F_SEL`:

1. **Idle**: No event has occurred. Output `OUT` remains at its last value.

2. **Setting IN0 / IN1**: Upon arrival of `EI0` or `EI1`, the corresponding internal copies are updated.

3. **Waiting for Selection**: After the values are set, the function block waits for the event `G.E1`.

4. **Executing the Selection**: Upon arrival of `G.E1`, `F_SEL` is activated. Based on the Boolean value of `G.D1`, `OUT` is set to the appropriate value.

5. **Confirmation**: After the selection is complete, `CNF` is generated. The function block returns to the "Idle" state.

## Application Scenarios

- **Agricultural Technology**: Selection between two sensor values (e.g., speed, pressure, or level measurements) depending on a control decision (e.g., load condition).

- **Signal Routing**: Switching between redundant signal sources in safety-critical systems.

- **Configurable Through-Connection**: In modular automation systems, the `G` adapter can be connected to a higher-level configuration block that dynamically defines the selection.


## Comparison with Similar Function Blocks

- **Standard `SEL` (IEC 61131-3)**: The basic `SEL` function block only has Boolean and value inputs without event-driven control. `AUDI_AX_SEL` adds event-driven value takeover and adapter-based selection, which facilitates integration into event-driven controllers.

- **"Bistable Switch" (Flip-Flop-Based Selection)**: Unlike a flip-flop, `AUDI_AX_SEL` operates purely combinatorially for selection and does not store input values across execution boundaries. The selection is always made fresh upon arrival of `G.E1`.

- **Other Adapter-Based Selectors**: Similar function blocks exist in libraries for distributed automation (e.g., 4diac LIB). `AUDI_AX_SEL` is characterized by the explicit use of the standardized `F_SEL` and the clear separation of data provision and selection.

## Conclusion

The `AUDI_AX_SEL` function block is a modular, event-driven binary selector specifically designed for use in IEC 61499-based automation solutions. By combining event interfaces and a standardized IEC 61131-3 selector, it offers a flexible, robust, and standards-compliant solution for switching tasks in industrial and agricultural environments.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
