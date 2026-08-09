# F_SEL_E_2

![F_SEL_E_2](https://github.com/user-attachments/assets/01359d6b-dfd8-4397-ab2d-a78e7f4e6168)

* * * * * * * * * *
## Introduction

The function block `F_SEL_E_2` is an event-based selector that selects between two input variables. It belongs to the category of standard selection functions according to IEC 61131-3 and is typically used in control applications where conditional selection between two input signals is required.
![F_SEL_E_2](F_SEL_E_2.svg)
## Interface Structure

### **Event Inputs**

- `REQ0`: Event input that triggers the selection of the first input variable (`IN0`).
- `REQ1`: Event input that triggers the selection of the second input variable (`IN1`).

### **Event Outputs**

- `CNF`: Confirmation event that is output after an input variable is selected. This event is linked to the output variable `OUT`.

### **Data Inputs**

- `IN0`: First selectable input variable (Type: `ANY`).
- `IN1`: Second selectable input variable (Type: `ANY`).

### **Data Outputs**

- `OUT`: Selected input variable (type: `ANY`). The value corresponds to either `IN0` or `IN1`, depending on the triggering event (`REQ0` or `REQ1`).

### **Adapters**

- This function block has no adapters.

## Functionality

The function block `F_SEL_E_2` selects between two input variables based on the incoming events:

- If the event `REQ0` is triggered, the value of `IN0` is passed to `OUT`.
- When the event `REQ1` is triggered, the value of `IN1` is passed to `OUT`.
- After selection, the confirmation event `CNF` is issued to signal successful selection.

## Technical Features

- The function block supports the data type `ANY`, meaning it is compatible with various data types.
- Selection is exclusively event-driven; that is, the logical condition for selection is controlled by external events.

## State Overview

1. **Initial State**: The function block waits for an event (`REQ0` or `REQ1`).
2. **Selection State**:
- `REQ0` selects `IN0`.
- `REQ1` selects `IN1`.
3. **Confirmation State**: After selection, `CNF` is output, and the block returns to its initial state.

## Application Scenarios

- Selection between two sensor data points based on external conditions.
- Switching between two operating modes in a controller.
- Dynamic selection of input signals depending on process events.

## ⚖️ Comparison with Similar Components

- Compared to other selection blocks (e.g., `SEL` in IEC 61131-3), `F_SEL_E_2` is purely event-driven and does not require any additional logical condition for selection.
- Similar blocks, such as `MUX` (multiplexer), allow selection from multiple inputs but are often data-flow driven and not event-based.

## 🛠️ Related Exercises

* [Exercise_019](../../../../Uebungen/test_B/Uebungen_doc/Uebung_019.md)]
* [Exercise_074](../../../../Uebungen/test_B/Uebungen_doc/Uebung_074.md)]

## Conclusion

The `F_SEL_E_2` is a flexible and easy-to-use function block for applications requiring event-based selection between two input variables. Its compatibility with the `ANY` data type makes it particularly versatile.
