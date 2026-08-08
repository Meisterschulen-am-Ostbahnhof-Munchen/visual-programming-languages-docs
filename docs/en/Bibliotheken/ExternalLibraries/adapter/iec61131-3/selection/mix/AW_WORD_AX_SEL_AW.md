# AW_WORD_AX_SEL_AW

![AW_WORD_AX_SEL_AW](./AW_WORD_AX_SEL_AW.svg)

*(No image available)*

* * * * * * * * * *
## Introduction
The function block `AW_WORD_AX_SEL_AW` is a composite function block for IEC 61499 that implements a binary selection between two data sources of type `WORD`. The selection is event-driven via a selector. The block uses a combination of classic interfaces (event/data inputs) and modern, unidirectional adapters for flexible and modular signal processing.

## Interface Structure

### **Event Inputs**

* **EI1**: Triggers the acquisition and processing of the directly applied data value `IN1`.


### **Event Outputs**
* *No direct event outputs.* Event output is encapsulated via the output adapter `OUT`.

### **Data Inputs**
* **IN1** (WORD): Selectable input variable directly connected to the function block.

### **Data Outputs**
* *No direct data outputs.* Data is transmitted encapsulated via the output adapter `OUT`.

### **Adapters**
* **OUT** (Plug, Type: `adapter::types::unidirectional::AW`): The output adapter that outputs the selected `WORD` signal and the associated update event.

### **Adapters**
* **OUT** (Plug, Type: `adapter::types::unidirectional::AW`): The output adapter that outputs the selected `WORD` signal and the associated update event.

### * **IN0** (Socket, Type: `adapter::types::unidirectional::AW`): The first selectable input, which is coupled as an adapter.

* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector input (adapter) that controls which of the two inputs (`IN0` or `IN1`) is routed to the output.


## Functionality
Internally, the function block is based on a network of standardized auxiliary components (such as flip-flops and selectors):

1. **Event and Data Storage**:

* When an event occurs at the adapter `G` (selector) or `IN0` (input 0), or at the direct event input `EI1`, the internal D flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively) buffer the current state of the respective data channel.


 2. **Value Transfer**:

* The buffered values of `IN0` and `IN1` are transferred to the actual selection kernel (`F_SEL`) via conversion modules (`F_MOVE`).

3. **Selection Logic (F_SEL)**:

* The module `F_SEL` evaluates the state of the selector `G`:

* If `G` is **FALSE** (0), the value of `IN0` is selected.


* * If `G` is **TRUE** (1), the value of `IN1` is selected.

4. **Output**:

* The result of the selection is passed via another flip-flop (`E_D_FF_ANY_OUT`) to the output adapter `OUT`, simultaneously updating the data value (`D1`) and triggering the output event (`E1`).



 ## Technical Features
* **Hybrid Architecture**: The combination of a classic data/event interface (`IN1`/`EI1`) and adapter interfaces (`IN0`, `G`, `OUT`) enables high flexibility for integration into existing systems.

* **Asynchronous Protection**: The use of internal D flip-flops ensures that data changes are only applied when actual events occur. This prevents data inconsistencies (race conditions).

* **Encapsulation**: The use of unidirectional adapters drastically reduces the number of visible connection lines in the higher-level system or application diagram.

## State Overview

| State Selector (`G.D1`) | Selected Input | Signal at Output (`OUT.D1`) |

:--- | :--- | :--- |

**FALSE** | `IN0` (via adapter) | Value of `IN0.D1` |

**TRUE** | `IN1` (direct input) | Value of `IN1` |

## Application Scenarios

* **Switching between automatic and manual operation**: `IN0` provides the automatic setpoint via a bus system (adapter), while `IN1` represents a manual setpoint from a local visualization. The selector `G` switches between the operating modes. * **Signal Routing**: Dynamic forwarding of sensor data (in `WORD` format) in modular process engineering plants.

* **Redundant Measured Value Selection**: Fast switching to a substitute value (`IN1`) if the main sensor (`IN0`) reports a fault.

## Comparison with Similar Function Blocks
Compared to the standard function block `F_SEL` from the IEC 61131-3 library, `AW_WORD_AX_SEL_AW` offers direct integration into the event-driven world of IEC 61499. While the classic `F_SEL` must be called cyclically and has no dedicated event handling, this block operates purely on an event-driven basis, thus minimizing processor load. Furthermore, the adapter structure significantly reduces wiring effort compared to conventional 4diac selectors.

## Conclusion
The `AW_WORD_AX_SEL_AW` is a specialized and optimized component for modern, event-driven control software. Thanks to its clever combination of adapters and standard selection logic, it is ideally suited for clean, modular, and efficient application designs in the 4diac IDE.