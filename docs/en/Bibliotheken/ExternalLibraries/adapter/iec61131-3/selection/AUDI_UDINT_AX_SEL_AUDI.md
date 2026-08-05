# AUDI_UDINT_AX_SEL_AUDI

![AUDI_UDINT_AX_SEL_AUDI](./AUDI_UDINT_AX_SEL_AUDI.svg)

* * * * * * * * * *
## Introduction

The function block **AUDI_UDINT_AX_SEL_AUDI** implements a binary selection between two data sources. An internal IEC 61131 selection block (F_SEL) selects either the value from an adapter input or a direct data input based on a Boolean selector signal and outputs the result via an adapter output. The function block is modeled as a composite function block and uses adapters for flexible and type-safe coupling.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| EI1 | Event | Sets the value of IN1 (not directly evaluated, used for data provision synchronization) |

### **Event Outputs**

This function block has **no dedicated event outputs**. Event control is handled via the adapter output **OUT** (see Adapter).

### **Data Inputs**

| Name | Type | Comment |

|------|-------|-----------|

| IN1 | UDINT | Second selectable input variable (direct) |

### **Data Outputs**

This function block has **no dedicated data outputs**. Output data is provided via the adapter **OUT**.

### **Adapter**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| Socket | IN0 | adapter::types::unidirectional::AUDI | First selectable input variable |

| Socket | G | adapter::types::unidirectional::AX | Selector (contains the Boolean selection signal and an event) |

| Plug | OUT | adapter::types::unidirectional::AUDI | Selected output (driven with event and data) |

**Adapter details (according to their type definition):**

- **AUDI**: Contains a data point (D1) and an event (E1).

- **AX**: Contains a data point (D1) and an event (E1).

## Functionality

The function block is implemented as a composite and internally uses the function block **F_SEL** (type `iec61131::selection::F_SEL`).

1. The socket **G** provides the trigger for the selection via its event **E1**.

2. As soon as this event arrives, the internal **F_SEL** is activated via its REQ input.

3. **F_SEL** evaluates the Boolean selector signal **G.D1**:

- If **G.D1 = FALSE**, the value of **IN0** (via adapter data **IN0.D1**) is passed to the output **OUT**.

- If **G.D1 = TRUE**, the value of the direct data input **IN1** is passed to the output **OUT**.

4. After a selection is made, **F_SEL.CNF** sends an event to the output adapter **OUT.E1**, and the selected data value is placed on **OUT.D1**.

The event input **EI1** is used solely for providing data from **IN1** (according to the WITH statement). The actual processing is performed exclusively by the selector event **G.E1**.

## Technical Features

- **Adapter-based interfaces**: Instead of individual parameters, complex, typed adapters (AUDI, AX) are used. This enables modular and reusable coupling in hierarchies.

- **Composite Block**: The internal logic is encapsulated in another function block (F_SEL). The overall function results from the interconnection of the sub-blocks and event/data connections.

- **No Internal State Machine**: The block does not have an ECC; sequence control is handled solely via the event network of the composite.

## State Overview

The block does not have an internal state machine. Its behavior is derived entirely from the internal F_SEL (IEC 61131 selection), which calculates a new output value after each event at the selector input.

## Application Scenarios

- **Selection between two sensor values** in agricultural control systems (e.g., two different measurement sources for one parameter).

- **Switching between a primary and a backup signal**, controlled by an error or switchover command.

- **Parameterizable configuration** of setpoints or actuator outputs via a Boolean selector.

## Comparison with similar function blocks

- **Simple SELECT function block (IEC 61131-3)**: Implements the same logic without an adapter, requires separate inputs for the selector, IN0, and IN1.

This function block encapsulates this functionality in an adapter-oriented interface.

- **MUX function blocks (e.g., 4-channel multiplexers)**: Offer multiple inputs, limited here to two sources.

- **Event-driven selection**: Unlike purely data-driven selectors, selection is only performed when an event occurs on the selector channel.

## Conclusion

**AUDI_UDINT_AX_SEL_AUDI** is a compact, adapter-oriented binary selector. It is particularly suitable for systems based on type-safe adapter connections and enables a clear separation of event and data flows. By using an established IEC 61131 selection kernel, the function remains reliable and compliant with standards.