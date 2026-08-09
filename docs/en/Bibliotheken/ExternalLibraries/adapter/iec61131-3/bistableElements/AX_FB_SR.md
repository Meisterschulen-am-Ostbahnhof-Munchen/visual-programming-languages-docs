# AX_FB_SR

[Image of the AX_FB_SR function block, if available]
![AX_FB_SR_ecc](./AX_FB_SR_ecc.svg)

* * * * * * * * * *
## Introduction

The **AX_FB_SR** function block implements a bistable latch with **set dominance** (SR flip-flop). Unlike conventional IEC 61131-3 function blocks, this block does not use discrete event and data connections, but rather **adapters** for signal transmission. This allows for a more compact representation and simplified wiring in complex control applications based on the adapter concept.

The block stores a binary state. If both the set (SET) and reset (RESET) signals are active simultaneously, the set signal takes precedence (set dominance).

## Interface Structure

The block communicates exclusively via adapter interfaces. Traditional discrete inputs and outputs are not present, as these are encapsulated within the adapters.

### **Event Inputs**

*No direct event inputs available (these are contained in sockets `SET1` and `RESET`).*

### **Event Outputs**

*No direct event outputs available (these are contained in plug `Q1`).*

### **Data Inputs**

*No direct data inputs available (these are contained in sockets `SET1` and `RESET`).*

### **Data Outputs**

*No direct data outputs available (these are contained in plug `Q1`).*

### **Adapter**

| Name | Type | Direction | Description |
| :--- | :--- | :--- | :--- |
| **Q1** | `adapter::types::unidirectional::AX` | Plug (Output) | The output adapter that provides the current state (Q) and the associated event. |
| **SET1** | `adapter::types::unidirectional::AX` | Socket (Input) | The set input adapter. A `TRUE` signal here sets the output to `TRUE`. |
| **RESET** | `adapter::types::unidirectional::AX` | Socket (Input) | The reset input adapter. A `TRUE` signal here sets the output to `FALSE` (if SET1 is not active). |

*Note: The adapter type `AX` typically implies a combination of a Boolean data point (`D1`) and an event (`E1`).*

## Functionality

The internal algorithm implements the logic of an SR flip-flop with set precedence. The logic is executed as soon as an event is received at one of the adapter inputs (`SET1.E1` or `RESET.E1`).

The logical equation is (in ST syntax):

```st
Q1.D1 := SET1.D1 OR ((NOT RESET.D1) AND Q1.D1);
```
## Technical Features

* **Adapter-based:** The main advantage of this function block is the reduction of connection lines in the function plan, as data and events are bundled via a single adapter connection.
* **Event-driven:** The function block reacts immediately to incoming events at the `SET1` or `RESET` adapters and forwards the result immediately.
* **State machine (ECC):** The Execution Control Chart (ECC) is minimal. It consists of a single state, `REQ`, which waits for input events and executes the algorithm `REQ`.

## State Overview

The following truth table describes the behavior of the function block (where `Q_n` is the old state and `Q_n+1` is the new state):

| SET1.D1 | RESET.D1 | Q_n (Old State) | Q_n+1 (New State) | Description |
| :---: | :---: | :---: | :---: | :--- |
| 0 | 0 | 0 | 0 | Hold State |
| 0 | 0 | 1 | 1 | Hold State |
| 0 | 1 | X | 0 | Reset |
| 1 | 0 | X | 1 | Set |
| 1 | 1 | X | 1 | **Set (Dominant)** |

## Application Scenarios

* **Adapter-Based Control Systems:** Ideal for projects that consistently utilize 4diac's adapter technology to avoid the "spaghetti code" of parallel event and data lines.
* **Start/Stop Logic:** Implementing machine controls where the "on" signal (set) has priority or where continuous activation must be ensured as long as the button is pressed.
* **Alarm Handling:** Storing alarm states that must be manually acknowledged (reset).

## ⚖️ Comparison with similar components

* **SR (Standard):** The `AX_FB_SR` is logically equivalent to the standard `SR` component of IEC 61131-3, but differs in that it uses `AX` adapters instead of discrete `BOOL` and `EVENT` pins.
* **AX_FB_RS:** This is the counterpart with **reset dominance**. With the `AX_FB_RS`, if SET and RESET are applied simultaneously, the output would go to `FALSE`.
* **E_SR:** An event-driven standard SR flip-flop without adapters.

## Conclusion

The **AX_FB_SR** is a specialized component for structured, adapter-based programming in 4diac. It offers the classic functionality of a set-dominant memory element, but optimizes the graphical representation and handling by encapsulating signals in adapters. It is indispensable in applications based on modular and clearly structured interface definitions.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
