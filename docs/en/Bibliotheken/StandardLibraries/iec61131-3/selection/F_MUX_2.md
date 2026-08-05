# F_MUX_2

![F_MUX_2](https://user-images.githubusercontent.com/116869307/214145411-87b2a7e5-fd56-4491-aaca-385941a399ab.png)

* * * * * * * * * *

## Introduction
The F_MUX_2 is a multiplexer function block according to IEC 61131-3, classified as a standard selection function. This block allows selection between two input signals based on a control signal.


![F_MUX_2](F_MUX_2.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Service Request - triggers multiplexer processing

### **Event Outputs**
- **CNF**: Confirmation of requested service - signals completion of processing

### **Data Inputs**

- **K**: Control input for selecting one of n inputs (ANY_INT type)

- **IN1**: Input value 1 (ANY type)

- **IN2**: Input value 2 (ANY type)

### **Data Outputs**

- **OUT**: Output value - returns IN1 for K = 0, IN2 for K = 1 (ANY type)

### **Adapters**
No adapter interfaces are available.

## Functionality
The F_MUX_2 operates as a 2:1 multiplexer. Upon receiving a REQ event, the function block evaluates the control input K:

- If K = 0, the value of IN1 is passed to OUT.

- If K = 1, the value of IN2 is passed to OUT.

After successful processing, the CNF event is triggered to signal the completion of the operation.
... ## Technical Features
- Use of generic data types (ANY and ANY_INT) for maximum flexibility
- Support for various data types for input values
- Simple and deterministic processing
- EPL 2.0 license

## State Transitions
1. **Wait Time**: No active processing
2. **Processing**: Upon REQ event - evaluation of K and selection of the corresponding input
3. **Completion**: Triggering of CNF after successful data transmission

## Application Scenarios
- Signal diverter in control applications
- Selection between different operating modes
- Switching between redundant signal sources
- Processing path selection in complex control systems

## ⚖️ Comparison with Similar Components
Compared to other multiplexers, F_MUX_2 offers:

- Specifically optimized for 2 inputs
- Simpler design than multiplexers with more inputs
- Direct and clear control logic
- Lower resource consumption with 2-way selection

## 🛠️ Related Exercises

* [Exercise_090a1](../../../../Uebungen/test_B/Uebungen_doc/Uebung_090a1.md)

## Conclusion
The F_MUX_2 is an efficient and reliable multiplexer for applications requiring selection between two input signals. Its simple structure and use of generic data types make it a versatile solution for various control tasks.