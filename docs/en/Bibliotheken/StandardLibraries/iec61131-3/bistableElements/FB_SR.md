# FB_SR

<img width="1312" height="242" alt="FB_SR" src="https://github.com/user-attachments/assets/97406c32-e30d-47c7-958c-cb76b2fcd83c" />
* * * * * * * * * *
## Introduction

The function block `FB_SR` is a bistable element that functions as a set-reset flip-flop (SR flip-flop). It stores a state based on the input signals and retains this state until it is changed by new input signals.
![FB_SR](FB_SR.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal Execution Request (trigger for executing the function block)

### **Event Outputs**

- **CNF**: Execution Acknowledgement (triggered after processing the inputs)

### **Data Inputs**

- **S1** (BOOL): Set Input (sets output `Q1` to `TRUE` if `TRUE`)
- **R** (BOOL): Reset Input (sets output `Q1` to `FALSE` if `TRUE`)

### **Data Outputs**

- **Q1** (BOOL): Output (stored state of the flip-flop)

### **Adapter**

No adapters available.

## Functionality

The function block `FB_SR` processes the inputs `S1` (Set) and `R` (Reset) according to the following logic:

- If `S1` is `TRUE`, `Q1` is set to `TRUE`.
- If `R` is `TRUE`, `Q1` is set to `FALSE`.
- If both inputs are `FALSE`, `Q1` retains its previous state.

The logic is implemented using the following algorithm:

ALGORITHM REQ
Q1 := S1 OR ((NOT R) AND Q1);
END_ALGORITHM
## Technical Features

- **IEC 61131-3 Compliance**: This function block precisely replicates the behavior of the classic `SR` flip-flop. Since the inputs `S1` and `R` are data inputs that are sampled simultaneously during the `REQ` event, logical prioritization is necessary.
- **Set Dominance**: The function block implements **set priority**. If `S1` and `R` are simultaneously `TRUE`, the output `Q1` is set to `TRUE`.
- **Trigger**: Execution (logic calculation) occurs only on the event `REQ`.

## State Overview

The state of the flip-flop (`Q1`) depends on the current values of `S1` and `R` (at the time of `REQ`):

- `S1 = TRUE`: `Q1` is set to `TRUE` (independently of `R`). -> **Set Dominance**
- `R = TRUE` AND `S1 = FALSE`: `Q1` is set to `FALSE`.
- `S1 = FALSE` and `R = FALSE`: `Q1` remains unchanged.

## Application Scenarios

- Storage of binary states in control applications where IEC 61131-3 behavior is required.
- Use in switching networks where the dominance of the set signal is necessary for safety or process reasons.

## ⚖️ Comparison with similar building blocks

- **[E_SR](../../events/E_SR.md)**: The `E_SR` is purely event-driven. There are no simultaneous signals and therefore no dominance in this sense (the last event wins). The `FB_SR`, on the other hand, evaluates static signals at time `REQ` and enforces set dominance.
- **[FB_RS](FB_RS.md)**: The counterpart with **reset dominance** (reset priority).

## 🛠️ Related Exercises

* [Exercise_006e1](../../../../Uebungen/test_B/Uebungen_doc/Uebung_006e1.md)]
* [Exercise_006e1_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006e1_AX.md)]

## Conclusion

The `FB_SR` is a basic and efficient function block for storing binary states in control applications. Its simple logic and clear interface make it ideal for use in various industrial automation solutions.
