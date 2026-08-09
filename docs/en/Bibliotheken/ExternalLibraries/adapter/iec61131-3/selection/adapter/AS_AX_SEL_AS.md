# AS_AX_SEL_AS

![AS_AX_SEL_AS](./AS_AX_SEL_AS.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AS_AX_SEL_AS` is used for binary selection between two input signals provided via adapters. Based on the state of a selection adapter (`G`), either the value of input `IN0` or input `IN1` is passed to output `OUT`.

 This function block encapsulates the classic multiplexer function (according to `SEL` from IEC 61131-3) in an event-driven IEC 61499 architecture using unidirectional adapters. This significantly simplifies signal wiring in complex control applications.

## Interface Structure

The function block does not have any classic event- or data-based inputs and outputs at the main level. All communication is handled via adapter interfaces.

### **Event Inputs**

*No direct event inputs are available. Event processing is encapsulated via the adapter sockets.*

### **Event Outputs**

*No direct event outputs are available. Event forwarding is encapsulated via the output adapter's plug.*

### **Data Inputs**

*No direct data inputs available.*

### **Data Outputs**

*No direct data outputs available.*

### **Adapters**

#### **Sockets (Input Interfaces)**

* **G** (Type: `adapter::types::unidirectional::AX`):
* **Description:** Selector interface. Determines which input is routed to the output.
* **Event:** `E1` (Trigger for updating the selection signal).
* **Data:** `D1` (Boolean value; determines the active path).
* **IN0** (Type: `adapter::types::unidirectional::AS`):

**Description:** First selectable data channel (selected when `G` has the value `FALSE`).

**Event:** `E1` (signals new data to `IN0`).

**Data:** `D1` (data value of the first channel).

**IN1** (Type: `adapter::types::unidirectional::AS`):

**Description:** Second selectable data channel (selected when `G` has the value `TRUE`).

**Event:** `E1` (signals new data to `D1`). * **Event:** `E1` (Signals new data to `IN1`).

* **Data:** `D1` (Data value of the second channel).

#### **Plugs (Output Interfaces)**

* **OUT** (Type: `adapter::types::unidirectional::AS`):
* **Description:** The selected output channel that mirrors the data of the active input.
* **Event:** `E1` (Triggered when a new selected value is output).
* **Data:** `D1` (The forwarded data value from `IN0` or `IN1`).

## Functionality

Inside the function block is a network of standard function blocks that processes the adapter signals:

1. **Signal Storage (Latch):** The data received via the adapters (`G.D1`, `IN0.D1`, `IN1.D1`) is temporarily stored in event-triggered D flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively) upon the occurrence of the respective event (`E1`).
2. **Data Conversion & Forwarding:** The cached data of types `IN0` and `IN1` are transferred to the central selection block via `F_MOVE` blocks. Internally, these operations are configured for the data type `SINT` (Short Integer).
3. **Selection Logic (`F_SEL`):** The block `F_SEL` (IEC 61131-3 Selection) performs the actual selection:
* If the state of selector `G` is equal to `FALSE`, the value of `IN0` is passed through.
* If the state of selector `G` is equal to `TRUE`, the value of `IN1` is passed through.
4. **Output Triggering:** After successful selection, the result is passed via another `F_MOVE` block to the output flip-flop `E_D_FF_ANY_OUT`. This flip-flop generates the output event `OUT.E1` and places the selected value on `OUT.D1`.

```
       +-------+
IN0 -->|       |
       | F_SEL |--> OUT (wenn G = FALSE, dann IN0; wenn G = TRUE, dann IN1)
IN1 -->|       |
       +-------+
           ^
           |
G ---------+
```

## Technical Features

* **Data Type Specificity:** Although the adapters can be flexibly configured, the internal conversion elements (`F_MOVE`) are fixed to the data type **`SINT`**. The module is therefore specifically designed for selecting signed 8-bit integers (short integers).
* **Event-Driven:** Any change or event at the inputs `IN0`, `IN1`, or `G` triggers the chain and updates the output `OUT`.

## State Overview

The following table shows the logical behavior of the function block based on the selection signal `G.D1`:

| State G.D1 | Selected Path | Output Value (OUT.D1) | Output Event (OUT.E1) |
| :--- | :--- | :--- | :--- |
| `FALSE` | Channel 0 (`IN0`) | Value of `IN0.D1` | Triggered on value change/event |
| `TRUE` | Channel 1 (`IN1`) | Value of `IN1.D1` | Triggered on value change/event |

## Application Scenarios

* **Operating Mode Switching:** Routing of setpoints (e.g., switching between a manually specified SINT value and an automatic setpoint).
* **Signal Source Selection:** Dynamic selection between two sensor values or parameter configurations distributed throughout the system via standardized unidirectional adapter structures.
* **Channel Bonding:** Reducing wiring effort in 4diac applications by encapsulating data and events in adapters.

## Comparison with Similar Function Blocks

* **`F_SEL` (Standard Selection Function Block):** Works directly with standard data types and requires explicit event connections at the application level. `AS_AX_SEL_AS`, on the other hand, fully encapsulates this logic and uses adapters, resulting in a clearer application diagram.
* **Other adapter-based selectors:** These differ primarily in the data types supported by the adapters (e.g., `INT`, `REAL` instead of `SINT`).

## Conclusion

The `AS_AX_SEL_AS` block provides an elegant, clean, and reusable solution for implementing binary signal switching based on unidirectional adapters in the 4diac IDE. The internal use of standardized components ensures deterministic behavior in the event-driven system.