# F_MUX_3

<img width="1366" height="254" alt="F_MUX_3" src="https://github.com/user-attachments/assets/2dbe8298-6066-469e-96d6-1a6850de8bd8" />
* * * * * * * * * *
## Introduction

The function block `F_MUX_3` is a multiplexer that selects three input signals based on a control signal and forwards them to the output. It is part of the IEC 61131-3 standard library and is used for signal selection in automation applications.
![F_MUX_3](F_MUX_3.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Service Request – triggers the selection and forwarding of the corresponding input signal. Linked to the data inputs `IN1`, `IN2`, `IN3`, and `K`.

### **Event Outputs**

- **CNF**: Confirmation of Requested Service – confirms the successful selection and forwarding of the signal. Linked to the data output `OUT`.

### **Data Inputs**

- **K** (ANY_INT): Control signal indicating which input is selected (0 for `IN1`, 1 for `IN2`, 2 for `IN3`).
- **IN1** (ANY): Input value 1.
- **IN2** (ANY): Input value 2.
- **IN3** (ANY): Input value 3.

### **Data Outputs**

- **OUT** (ANY): Output value corresponding to the selected input (`IN1` for `K = 0`, `IN2` for `K = 1`, `IN3` for `K = 2`).

### **Adapters**

No adapters included.

## Functionality

Upon a `REQ` event, the function block evaluates the value of `K` and forwards the corresponding input (`IN1`, `IN2`, or `IN3`) to the output `OUT`. The `CNF` event is then triggered to confirm the successful operation.

## Technical Specifications

- Supports any data type (`ANY`) for the inputs and output.
- The control input `K` must be an integer type (`ANY_INT`).
- Initial values for the inputs are not predefined.

## State Overview

The function block has no internal states. Selection and routing occur immediately upon a `REQ` event.

## Application Scenarios

- Signal routing in control applications.
- Selection between different sensor data.
- Dynamic configuration of signal paths.

## ⚖️ Comparison with Similar Function Blocks

- `F_MUX_2`: A simpler multiplexer with only two inputs.
- `F_SEL`: A more general selector that may support more complex selection criteria.

## 🛠️ Related Exercises

- [Exercise_090a2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_090a2.md)

## Conclusion

The `F_MUX_3` is a simple and efficient multiplexer for applications where selection between three signals is required. Its flexibility regarding data types makes it versatile.
