# BOOLS_TO_ARR08X

<img width="1090" height="362" alt="image" src="https://github.com/user-attachments/assets/61dbe877-33a2-4798-8137-868082aad02a" />
![BOOLS_TO_ARR08X](./BOOLS_TO_ARR08X.svg)

* * * * * * * * * *
## Introduction

The function block `BOOLS_TO_ARR08X` converts eight individual Boolean (`BOOL`) input signals into a Boolean array (`ARRAY[0..7] OF BOOL`). It is a fundamental building block for signal aggregation and data structuring in control applications, especially when discrete digital signals need to be bundled for compact processing or transmission.
## Interface Structure

### **Event Inputs**

* `REQ` (Request): Triggers the conversion operation. Upon this event, the current values at the eight `IN_xx` inputs are read and written to the output array `OUT`.

### **Event Outputs**

* `CNF` (Confirm): Triggered as soon as the conversion is complete and the output array `OUT` is ready with the new values.

### **Data Inputs**

Eight individual Boolean inputs (`BOOL`), each corresponding to a bit in the resulting array:

* `IN_00`: Value for bit 00 / Array index 0.
* `IN_01`: Value for bit 01 / Array index 1.
* `IN_02`: Value for bit 02 / Array index 2.
* `IN_03`: Value for bit 03 / Array index 3.
* `IN_04`: Value for bit 04 / Array index 4.
* `IN_05`: Value for bit 05 / Array index 5.
* `IN_06`: Value for bit 6 / array index 6.
* `IN_07`: Value for bit 7 / array index 7.

### **Data Outputs**

* `OUT`: The output signal of type `ARRAY[0..7] OF BOOL`. After the `REQ` event is triggered, it contains the values present at the inputs at that time, where `IN_00` is mapped to `OUT[0]` and `IN_07` to `OUT[7]`.

### **Adapters**

This function block has no adapter interfaces.

## Functionality

The functionality is deterministic and simple. Whenever an event arrives at the `REQ` input, the contained ST code is executed. This code directly assigns the value of the corresponding individual `IN_xx` input to each element of the output array `OUT`. The mapping is hardwired:

OUT[0] := IN_00;`
OUT[1] := IN_01;`
...
OUT[7] := IN_07;`
Immediately after this assignment, the `CNF` event is generated to signal the successful completion of the operation. There is no buffering, delay, or logical combination of the input values.

## Technical Features

* **Real-time Behavior:** The operation is atomic and very fast, as it consists only of direct assignments. It introduces no significant latency into the control cycle.
* **Size Definition:** The output array is defined with the fixed size `[0..7]`, which corresponds to exactly eight elements.
* **Synchronous Processing:** All input values are acquired synchronously at the time of the `REQ` event. Changes to the inputs during processing have no effect on the current cycle.

## State Overview

The function block is stateless. It has no internal memory. Its output at any given time is solely a function of the current input values at the time of the last `REQ` event.

## Application Scenarios

* **Bundling of Switching States:** Combining the states of multiple limit switches, pushbuttons, or valves into a single array for transmission over a network or to a higher-level control module.
* **Preprocessing for Array-Based Blocks:** Providing input data for function blocks that perform their operations on entire arrays (e.g., logic operations, shift operations).
* **Structuring of I/O Data:** Organizing distributed digital input signals from a PLC into a defined data structure for improved program readability and maintainability.
* **Interface to Visualization Systems:** Easier mapping of many individual signals to a composite symbol or status display in an HMI.

## ⚖️ Comparison with Similar Blocks

* **`BOOL_TO_xxx` Blocks:** Blocks like `BOOL_TO_INT` or `BOOL_TO_BYTE` also convert multiple Boolean values into a more compact data set. `BOOLS_TO_ARR08X`, on the other hand, explicitly creates an array, which preserves indexed access to each individual bit and maintains the semantic meaning of its position.
* **Manual Wiring:** The alternative would be to directly wire each individual bit to the indices of an array variable block. `BOOLS_TO_ARR08X` encapsulates this operation, improving clarity in the FBD/LD editor and reducing wiring effort.
* **`MERGE`/`CONCAT` blocks:** General-purpose merge blocks can combine various data types. `BOOLS_TO_ARR08X` is specialized and type-safe for exactly eight BOOL inputs and a BOOL array as an output.

## 🛠️ Related Exercises

* [Exercise_054](../../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_054.md)

## Conclusion

The `BOOLS_TO_ARR08X` is a specialized, robust, and efficient function block for a common task in industrial automation: bundling discrete signals. Its strength lies in its simplicity, deterministic execution time, and clear interface definition. It is the first choice when eight Boolean signals need to be provided in an ordered array structure for further processing.
