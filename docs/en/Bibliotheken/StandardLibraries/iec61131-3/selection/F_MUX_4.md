# F_MUX_4

<img width="1298" height="244" alt="image" src="https://github.com/user-attachments/assets/ca36e916-c580-4eb8-bf05-67d67557302f" />
* * * * * * * * * *
The function block `F_MUX_4` is a four-input multiplexer that selects one of four input values based on a control signal and outputs it. It is part of the IEC 61131-3 standard library and is used for selection operations in control applications.
![F_MUX_4](F_MUX_4.svg)

- `REQ`: Service request. Triggers the selection and output of the corresponding input value. Linked to the data inputs `IN1`, `IN2`, `IN3`, `IN4`, and `K`.
- `CNF`: Confirmation of the requested service. Triggered after the output value is set. Linked to the data output `OUT`.
- `K` (`ANY_INT`): Control signal that determines the input to be selected.
- `CNF`: Confirmation of the requested service. Triggered after the output value is set.
- `K` (`ANY_INT`): Control signal that determines the input to be selected ...### **Event Outputs**
- `K = 1`: Selects `IN2`
- `K = 2`: Selects `IN3`
- `K = 3`: Selects `IN4`
- `IN1` (`ANY`): Input value 1
- `IN2` (`ANY`): Input value 2
- `IN3` (`ANY`): Input value 3.
- `IN4` (`ANY`): Input value 4.
- `OUT` (`ANY`): Output value corresponding to the input selected by `K`.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

No adapters available.

## Functionality

Upon receiving the event `REQ`, the function block evaluates the value of `K` and outputs the corresponding input value (`IN1` to `IN4`) at output `OUT`. The event `CNF` is then triggered to confirm successful selection and output.

- Supports any data type (`ANY`) for the inputs and output.
- The control input `K` must be an integer value (`ANY_INT`).
- The initial values of the inputs are empty; no default values are provided.

1. **Idle State**: Waits for the event `REQ`.
2. **Selection State**: Evaluates `K` and selects the corresponding input.
3. **Output State**: Sets `OUT` to the selected value and triggers `CNF`.

- Selection between different sensor data based on control logic.
- Switching between different operating modes in a controller.
- Dynamic selection of data sources depending on external conditions.
- `F_MUX_2`: Simple multiplexer with only two inputs.
- `F_MUX_3`: Three-input multiplexer.
- `F_MUX_4` offers an extension to four inputs, providing greater flexibility in selection.

The `F_MUX_4` is a versatile and easy-to-use multiplexer, ideally suited for applications requiring selection between four different input values. Its support for arbitrary data types and clear event-driven control make it a valuable component in the IEC 61131-3 standard library.

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion
