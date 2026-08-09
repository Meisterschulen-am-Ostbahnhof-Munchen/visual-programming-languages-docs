# AR_D_FF

![AR_D_FF](./AR_D_FF.svg)

* * * * * * * * * *
## Introduction

The function block **AR_D_FF** implements a data-controlled flip-flop (D-latch) according to the IEC 61499-1 Annex A specification. It serves as an encapsulation for the standard function block `iec61499::events::E_D_FF_ANY` and provides its functionality via two unidirectional adapters. The block accepts a data value on a rising edge of the clock signal and holds it until the next rising edge.
## Interface Structure

The AR_D_FF has no direct event or data inputs/outputs; all communication takes place via its two adapters.

## **Event Inputs**

- **No direct inputs.**

The clock event is provided via the input adapter **I** (see Adapter section).

### **Event Outputs**

- **No direct outputs.**

The acknowledgment event is provided via the output adapter **Q** (see Adapters section).

### **Data Inputs**

- **No direct outputs.**

The data value to be latched is provided via the input adapter **I** (see Adapters section).

### **Data Outputs**

- **No direct outputs.**

The latched data value is provided via the output adapter **Q** (see Adapters section).

### **Adapters**

| Adapter | Direction / Type | Description | Included Elements |
|---------|----------------|--------------|---------------------|
| **I** | Socket (`adapter::types::unidirectional::AR`) | Value to be latched. | **E1** (Event Input) – Clock Signal (CLK) <br>**D1** (Data Input) – Data Value |
| **Q** | Plug (`adapter::types::unidirectional::AR`) | Latched Value. | **E1** (Event Output) – Acknowledgement after Successful Latch <br>**D1** (Data Output) – Latched Data Value |

## Functionality

The component operates on the principle of an edge-triggered D flip-flop:

1. An event at the clock input **I.E1** activates the latch.
2. At the time of the rising edge, the current data value **I.D1** is stored internally.
3. The stored value is immediately output to **Q.D1**.
4. Simultaneously, an event is triggered on **Q.E1** to acknowledge the processing.

The internal state remains unchanged between two clock edges (memory behavior).

## Technical Features

- **Adapter-based encapsulation:** The AR_D_FF uses only unidirectional adapters (type `AR`) for input and output. This enables modular, standardized integration into larger adapter networks.
- **Use of the standard component `E_D_FF_ANY`:** The actual flip-flop logic is implemented using the IEC 61499 standard component. Changes to the internal implementation do not affect the externally visible interface.
- **No reset input:** Unlike other flip-flop variants, this component has no reset function. The state can only be changed by a new data value and a clock pulse.

## State overview

The component has a single internal memory (the latched data value). State transitions occur exclusively on a rising edge at the clock input **I.E1**:

| Old State | Input D1 (current) | New State | Output D1 | Event Q.E1 |
|---------------|---------------|--------------|-------------|
*any* | *any* | Value of D1 | Value of D1 | is triggered |

There are no other internal states or branches.

## Application Scenarios

- **Data Synchronization:** Transfer of a data word at a defined time, e.g., in a cyclic control system.
- **Buffering:** Intermediate storage of a value between two calculation steps.
- **Event-driven signal propagation:** Applications where a value may only be updated when a specific event occurs.

## Comparison with similar components

| Component | Property | Difference to AR_D_FF |
|----------|--------------|-------------------------|
| **AR_SR_FF** | Set-Reset Flip-Flop | Does not latch a data value, but is set/reset via Set/Reset. Has two event inputs. |
| **E_D_FF_ANY** | Standard D Flip-Flop without adapter | Same core logic, but direct event/data connections; no adapter encapsulation. |
| **AR_T_FF** | Toggle Flip-Flop | Toggles the output on each clock pulse; no data input. |

## Conclusion

The **AR_D_FF** is a simple, reliable D flip-flop that, thanks to its adapter interface, is particularly suitable for modular and reusable IEC 61499 applications. The encapsulation of this standard component increases its robustness and facilitates integration into larger systems. Specialized flip-flop variants are available for applications requiring a reset or other logic functions.
