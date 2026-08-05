# F_SEL_E_4
![F_SEL_E_4](https://github.com/user-attachments/assets/2deb1c98-9daf-4a3c-b155-a719bb97771b)

* * * * * * * * * *
## Introduction
The F_SEL_E_4 function block is an event-based selector that selects one input from up to four inputs and forwards it to the output. It is classified according to the IEC 61131-3 standard and serves as a standard selection function in automation systems.
![F_SEL_E_4](F_SEL_E_4.svg)
## Interface Structure

### **Event Inputs**
- **REQ0**: Event that selects the value of IN0.
- **REQ1**: Event that selects the value of IN1.
- **REQ2**: Event that selects the value of IN2.
- **REQ3**: Event that selects the value of IN3.

### **Event Outputs**
- **CNF**: Confirmation event triggered as soon as an input is selected and the value is passed to OUT.

### **Data Inputs**
- **IN0**: First selectable input (Type: ANY).
- **IN1**: Second selectable input (Type: ANY).
- **IN2**: Third selectable input (Type: ANY).
- **IN3**: Fourth selectable input (Type: ANY).

### **Data Outputs**
- **OUT**: Selected input (Type: ANY).

### **Adapters**
No adapters available.

## Functionality
Based on the triggering event (REQ0 to REQ3), F_SEL_E_4 selects the corresponding input (IN0 to IN3) and passes the value to OUT. The CNF event confirms the successful selection and transmission.

#
## Technical Features
- Supports the ANY data type, enabling flexible use with various data types.
- Event-based selection, allowing for precise control.

## State Overview
The function block has no internal states. Selection and transmission occur immediately upon the arrival of the corresponding REQ event.

## Application Scenarios
- Selection between different sensor data in a controller.
- Multiplexing of control signals in automation systems.
- Flexible data transmission depending on external events.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other selectors, F_SEL_E_4 offers event-based control, enabling more precise selection than time- or state-based alternatives.
- Support for the ANY data type makes it more flexible than type-specific selectors.

## 🛠️ Related Exercises
* [Exercise_019a](../../../../Uebungen/test_B/Uebungen_doc/Uebung_019a.md)]
* [Exercise_019b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_019b.md)]
* [Exercise_019c](../../../../Uebungen/test_B/Uebungen_doc/Uebung_019c.md)]

## Conclusion
The F_SEL_E_4 is a versatile and flexible function block for event-based data selection in automation systems. Its simple interface and support for various data types make it a practical solution for many use cases.
