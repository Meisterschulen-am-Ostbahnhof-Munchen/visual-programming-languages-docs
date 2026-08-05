# F_UDINT_TO_REAL

<img width="1450" height="216" alt="F_UDINT_TO_REAL" src="https://github.com/user-attachments/assets/8be282c0-424f-4a10-8a26-e020cf9c2cc9" />

* * * * * * * * * *
## Introduction
The function block `F_UDINT_TO_REAL` converts an unsigned 32-bit integer value (`UDINT`) into a 32-bit floating-point value (`REAL`). This block is particularly useful in scenarios where numeric values of different data types need to be processed.

![F_UDINT_TO_REAL](F_UDINT_TO_REAL.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is processed.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The converted value is available at the data output `OUT`.

### **Data Inputs**

- **IN**: Expects an input value of type `UDINT` (unsigned 32-bit integer).

### **Data Outputs**

- **OUT**: Outputs the converted value as `REAL` (32-bit floating-point number).

### **Adapters**

- No adapters available.


### ## Functionality
When the event input `REQ` is triggered, the algorithm is started. This algorithm converts the `UDINT` value at input `IN` into a `REAL` value and provides the result at output `OUT`. The event `CNF` is then triggered to signal the successful completion of the conversion.

## Technical Features

- The conversion is performed directly using the built-in function `UDINT_TO_REAL`.

- The function block is simple and efficient because it does not require complex state machines or additional processing steps.

## State Overview
The function block has no internal states. Processing occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Conversion of raw data (e.g., from sensors or communication protocols) into floating-point values for further calculations.

- Integration into control systems where different data types need to be processed.

## ⚖️ Comparison with Similar Function Blocks

- Compared to generic conversion function blocks, `F_UDINT_TO_REAL` is specialized and optimized for the specific conversion of `UDINT` to `REAL`.

- Similar function blocks might offer additional features such as range checks or scaling, which is not the case here.


## 🛠️ Related Exercises

* [Exercise_151](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_151.md)]
* [Exercise_151_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_151_AX.md)]
* [Exercise_152](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_152.md)]
* [Exercise_153](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_153.md)]

## Conclusion
The `F_UDINT_TO_REAL` function block is a simple and efficient building block for converting unsigned 32-bit integers to floating-point numbers. Its simplicity makes it particularly suitable for applications where fast and direct conversion is required.