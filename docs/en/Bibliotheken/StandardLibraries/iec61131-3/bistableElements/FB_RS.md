# FB_RS

<img width="1308" height="242" alt="FB_RS" src="https://github.com/user-attachments/assets/ff0ca1ab-bc02-459b-bbda-2ef4f8aa880b" />
* * * * * * * * * *
## Introduction

The FB_RS function block is a bistable element that functions as a set-reset flip-flop (RS flip-flop). It stores a state and changes it based on the input signals S (Set) and R1 (Reset). The block is implemented according to the IEC 61499-1 standard and is suitable for control applications that require state storage.
![FB_RS](FB_RS.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Normal Execution Request. Triggers the execution of the function block. Linked to the data inputs S and R1.

### **Event Outputs**

- **CNF**: Execution Confirmation. Outputs after the inputs have been processed. Linked to the data output Q1.

### **Data Inputs**

- **S (BOOL)**: Set input. Sets output Q1 to TRUE if S is TRUE and R1 is FALSE.
- **R1 (BOOL)**: Reset input. Sets output Q1 to FALSE if R1 is TRUE.

### **Data Outputs**

- **Q1 (BOOL)**: Output. Represents the stored state of the RS flip-flop.

#### **Adapters**

No adapters available.

## Functionality

The FB_RS processes inputs S and R1 on every REQ event. Output Q1 is updated according to the following logic:

- If R1 is TRUE, Q1 is set to FALSE (Reset takes priority).
- If S is TRUE and R1 is FALSE, Q1 is set to TRUE.
- If both inputs are FALSE, Q1 retains its previous state.

The logic is implemented using the following algorithm:

ALGORITHM REQ
Q1 := (NOT R1) AND (S OR Q1);
END_ALGORITHM
## Technical Features

- **IEC 61131-3 Compliance**: This component precisely replicates the behavior of the classic `RS` flip-flop. Since the inputs `S` and `R1` are data inputs that are sampled simultaneously during the `REQ` event, logical prioritization is necessary.
- **Reset Dominance (Priority)**: The reset input (`R1`) takes precedence. If `S` and `R1` are simultaneously `TRUE`, the output `Q1` is set to `FALSE`.
- **Storage Behavior**: The block retains its state as long as there is no change to `S` or `R1` (or no `REQ` event occurs).

**Storage Behavior**: The block retains its state as long as there is no change to `S` or `R1` (or no `REQ` event occurs).
## State Overview

The `FB_RS` evaluates the inputs at `REQ`:

1. **Q1 = FALSE**: If `R1` is TRUE (regardless of `S`). -> **Reset Dominance**
2. **Q1 = TRUE**: If `S` is TRUE AND `R1` is FALSE.
3. **Q1 Unchanged**: If both are FALSE.

## Application Scenarios

- Storage of switching states in control applications according to IEC 61131-3 logic.
- Implementation of interlock logic (e.g., emergency stop circuits) where switching off (reset) must always take precedence.

## ⚖️ Comparison with similar building blocks

- **[E_RS](../../events/E_RS.md)**: The `E_RS` is purely event-driven ("Last Event Wins"). The `FB_RS`, on the other hand, evaluates static signals at time `REQ` and enforces reset dominance.
- **[FB_SR](FB_SR.md)**: The counterpart with **set dominance**.

## 🛠️ Related Exercises

* [Exercise_006e2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_006e2.md)
* [Exercise_006e2_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006e2_AX.md)
* [Exercise_160b2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_160b2.md)
* [Exercise_160b2_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b2_AX.md)

## Conclusion

The FB_RS is a fundamental and robust function block for state storage in IEC 61499-based control systems. Its simple and clear logic makes it particularly suitable for applications requiring reliable set-reset behavior. Prioritizing the reset input ensures that safety functions can be executed reliably.
