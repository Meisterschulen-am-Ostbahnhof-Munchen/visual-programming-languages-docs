# F_MUX_32
![F_MUX_32](./F_MUX_32.svg)

* * * * * * * * * *
## Introduction
The function block **F_MUX_32** is a generic multiplexer (selection function) according to IEC 61131-3. It allows the selection of one of 32 input values (IN1 … IN32) and outputs it at output OUT. The selection is made using the integer selector K. The block is event-driven: When an event occurs at the REQ input, the current value of K is evaluated and the corresponding input value is applied.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-------|------------------------------------------------------------|
| REQ | Event | Service Request – triggers the selection |

### **Event Outputs**

| Name | Type | Comment |
|------|-------|-----------------------------------------------------------|
| CNF | Event | Confirmation – confirms the selection has been made |

### **Data Inputs**

| Name | Type | Comment |
|------|------------|------------------------------------------------------|
| K | ANY_INT | Selection value (0 … 31), selects one of the 32 inputs |
| IN1 | ANY | Input value 1 |
| IN2 | ANY | Input value 2 |
| … | … | … |
| IN32 | ANY | Input value 32 |

### **Data Outputs**

| Name | Type | Comment |
|------|-----|----------------------------------------------------------|
| OUT | ANY | Output value: IN1 if K=0; IN2 if K=1; …; IN32 if K=31 |

### **Adapter**

No adapters available.

## Functionality

The FB `F_MUX_32` operates in an event-driven manner:

1. An event at the **REQ** input triggers processing.

2. The selector **K** (integer value) is evaluated.

3. Depending on the value of K, the corresponding data input is selected:

- K = 0 → **IN1**
- K = 1 → **IN2**
- …
- K = 31 → **IN32**
4. The selected value is passed to the **OUT** output.

5. An event at the **CNF** output signals the completion of the operation.

Values outside the valid range (0 … 31) result in undefined behavior; the function block does not offer range checking.

## Technical Features
- **Generic Data Type (ANY):** All data inputs and the output are declared with `ANY`. The function block can therefore be used with various data types (BOOL, INT, REAL, etc.). However, all inputs and the output must have the same specific type.
- **Event Association:** The **REQ** event is associated with all data inputs (IN1 … IN32 and K). When a REQ event occurs, all these inputs are read simultaneously.
- **Lack of Range Check:** The function block does not check whether K is in the range 0 … 31. An invalid value can lead to unexpected results (e.g., selecting a non-existent channel). This must be addressed in the application.
- **Standard Compliance:** The function block implements the `SELECT` functionality from IEC 61131-3 and is classified as a "standard selection function".

## State Overview

The function block does not have an explicit state machine in its XML definition. It behaves like an event-driven function: After the **REQ** event, the output is immediately updated and **CNF** is triggered. There are no internal states.

## Application Scenarios
- **Switching between multiple sensor values** in a controller (e.g., temperature, pressure, or level sensors).
- **Configurable Configuration:** Selection of different operating modes or setpoints via an index.
- **Test and diagnostic functions** where different signal sources are connected to an analysis point.
- **Extension of existing multiplexer solutions** with fewer channels to 32 inputs.

## Comparison with Similar Function Blocks
- **F_MUX_2, F_MUX_3, … F_MUX_n:** These function blocks have a smaller number of inputs (2, 3, …). `F_MUX_32` covers the maximum requirement of 32 channels. If only a smaller number is needed, smaller variants are more space-saving and easier to understand.
- **CASE Statement (ST):** A `CASE` structure in Structured Text can represent the same behavior but is not encapsulated as a reusable function block. The function block offers event-driven encapsulation for graphical and textual programming.
- **MUX Function in IEC 61131-3:** The integrated `MUX` function is typically limited to smaller numbers (e.g., 8). The function block extends this to 32 channels.

## Conclusion

The **F_MUX_32** is a powerful and flexible multiplexer IC for use in automation technology. Its generic type and large number of 32 inputs make it suitable for a wide variety of selection tasks. The simple event control and the clean separation of event and data paths make it easily integrated into IEC 61131-3 environments. However, users should ensure the valid selection range is used to avoid errors.
