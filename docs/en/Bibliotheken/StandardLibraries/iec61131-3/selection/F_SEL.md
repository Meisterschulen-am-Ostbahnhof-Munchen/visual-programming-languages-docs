# F_SEL

![image](https://user-images.githubusercontent.com/69573151/210802734-9caf89bd-f437-43d3-8ed5-294c89df8c3d.png)
<https://content.helpme-codesys.com/en/CODESYS%20Development%20System/_cds_operator_sel.html>
* * * * * * * * * *
## Introduction

The F_SEL function block is a binary selector according to the IEC 61131-3 standard. It enables selection between two input values based on a control signal. The block is used for conditional data selection in control applications.

![F_SEL](F_SEL.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service Request - triggers the selection operation

### **Event Outputs**

- **CNF**: Confirmation of the requested service operation

### **Data Inputs**

- **G**: Selector (BOOL) - Control signal for selection
- **IN0**: Selectable Input Variable (ANY) - First Input
- **IN1**: Selectable Input Variable (ANY) - Second Input

### **Data Outputs**

- **OUT**: Selected Input (ANY) - Result of the selection

### **Adapters**

No adapter interfaces available.

## Functionality

When a REQ event arrives, the F_SEL block evaluates the selector input G:

- If G = FALSE (0): OUT is set to the value of IN0
- If G = TRUE (1): OUT is set to the value of IN1

After the selection operation is complete, the CNF event is output with the calculated output value.

## Technical Features

- Uses generic data types (ANY) for the inputs and outputs IN0, IN1, and OUT
- Enables the processing of various data types
- Real-time execution upon event triggering
- Simple and deterministic operation

## State Transitions

1. **Wait State**: Block waits for REQ event
2. **Execute State**: Upon REQ event, G is evaluated and data is selected
3. **Output State**: CNF event with result is output, return to wait state

## Application Scenarios

- Switching between two sensors or measured values
- Selection between different operating modes
- Conditional data forwarding in process chains
- Implementation of multiplexer functionality

## ⚖️ Comparison with Similar Function Blocks

Compared to other selection blocks, F_SEL offers:

- Simple binary selection (only two inputs)
- Flexible type support through ANY data type
- Standardized Event Control according to IEC 61131-3

## 🛠️ Related Exercises

- [Exercise_015](../../../../Uebungen/test_B/Uebungen_doc/Uebung_015.md)
- [Exercise_016](../../../../Uebungen/test_B/Uebungen_doc/Uebung_016.md)
- [Exercise_060](../../../../Uebungen/test_B/Uebungen_doc/Uebung_060.md)

## Conclusion

The F_SEL block provides a fundamental and versatile selection function for control applications. Its simple structure and flexible type support make it a valuable component for various selection and switching tasks in industrial automation systems.
