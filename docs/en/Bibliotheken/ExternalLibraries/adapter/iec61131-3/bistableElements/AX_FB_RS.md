# AX_FB_RS
![AX_FB_RS_ecc](./AX_FB_RS_ecc.svg)
* * * * * * * * * *
## Introduction
The function block **AX_FB_RS** implements a bistable flip-flop with reset dominance, based on the IEC 61131-3 standard. Unlike the standard `RS` block, this function block uses adapter interfaces (`AX`) to transmit events and data in a bundled manner. This allows for a more compact representation in control diagrams, as data and event connections are combined in a single line.
## Interface Structure

Since this block is based exclusively on adapters, the classic event and data inputs/outputs are empty. Communication takes place entirely via the defined plugs and sockets.

### **Event Inputs**
*No direct event inputs available.*

### **Event Outputs**
*No direct event outputs available.*

### **Data Inputs**
*No direct data inputs available.*

### **Data Outputs**
*No direct data outputs available.*

### **Adapters**

This component uses the adapter type `adapter::types::unidirectional::AX`. This adapter type typically bundles a Boolean signal (`D1`) and an associated event (`E1`).

| Name | Type | Direction | Description |

| :--- | :--- | :--- | :--- |

| **Q1** | AX | Plug (Output) | The output of the flip-flop (status). |

| **SET** | AX | Socket (Input) | The set input. When active, the output `Q1` is set to TRUE (unless `RESET1` is active). |

**RESET1** | AX | Socket (Input) | The reset input. When active, the output `Q1` is set to FALSE. This input has priority over `SET`. |

## Functionality

The **AX_FB_RS** implements the logic of an RS flip-flop with reset dominance. The internal state and the output `Q1` are calculated based on the input values of the adapters `SET` and `RESET1`.

The logical function is:

Q1 := (NOT RESET1) AND (SET OR Q1)`

The behavior can be summarized as follows:

1. **Reset:** If `RESET1.D1` is TRUE, `Q1.D1` immediately becomes FALSE, regardless of the state of `SET.D1`.

2. **Set:** If `SET.D1` is TRUE and `RESET1.D1` is FALSE, `Q1.D1` becomes TRUE.

3. **Save:** If both `SET.D1` and `RESET1.D1` are FALSE, `Q1.D1` retains its previous state.

As soon as an event (`E1`) is received at one of the input adapters (`SET` or `RESET1`), the module executes the algorithm and then fires an event at the output adapter `Q1.E1`.

## Technical Features
* **Adapter Technology:** By using `AX` adapters, the module reduces visual complexity in 4diac applications, as only one connecting line needs to be drawn for the event-boolean value pair.
* **Event-Driven:** The algorithm is triggered when an event arrives via the `SET` or `RESET1` adapter.
* **Reset Dominance:** This is a safety-relevant feature. In case of a conflict (both inputs TRUE), the output safely shuts down (FALSE).

## State Overview

The function block is based on a simple ECC (Execution Control Chart) with a single main state.

* **State Name:** `REQ`
* **Action:** Executes the algorithm `REQ` and sends an event via `Q1.E1`.
* **Transitions:**
* The state `REQ` has self-transitions (self-loops) that are triggered by the arrival of events at the adapters `SET.E1` or `RESET1.E1`.

This means that the function block is always ready to process input signals and respond to them immediately.

## Application Scenarios
* **Motor Controls (Start/Stop):** Typical application for start (Set) and stop (Reset) buttons, where the stop button takes precedence for safety reasons (emergency stop logic).
* **Alarm Memory:** An alarm is set and remains active until it is explicitly reset (acknowledged).
* **State Markers:** Storing binary states within an adapter-based control logic.
* **Modular Systems:** Used in systems that consistently rely on adapter interfaces to avoid "spaghetti code" in the graphical representation.

## ⚖️ Comparison with Similar Function Blocks

| Feature | AX_FB_RS | AX_FB_SR | RS (Standard) |

| :--- | :--- | :--- | :--- |

| **Dominance** | **Reset Dominant** (Output FALSE at S=1, R=1) | Set Dominant (Output TRUE at S=1, R=1) | Reset Dominant |

| **Interface** | Adapter (`AX`) | Adapter (`AX`) | Boolean Event/Data Ports |

| **Wiring** | Minimalist (bundled) | Minimalist (bundled) | Classic (separate lines) |

## Conclusion

The **AX_FB_RS** is a modern, adapter-based implementation of the classic RS flip-flop. It is ideally suited for complex control applications in 4diac where clarity and signal encapsulation are paramount. Thanks to its integrated reset dominance, it is particularly well-suited for applications where safe shutdown takes precedence over shutdown.

**Wiring** | Minimalist (bundled) | Classic (separate lines) |

## Conclusion

The **AX_FB_RS** is a modern, adapter-based implementation of the classic RS flip-flop. It is ideally suited for complex control applications in 4diac where clarity and signal encapsulation are essential. Its integrated reset dominance makes it especially suitable for applications where safe shutdown must take precedence over shutdown.

** ---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
