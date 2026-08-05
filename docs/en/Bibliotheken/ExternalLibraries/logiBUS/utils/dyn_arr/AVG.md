# AVG
![AVG](./AVG.svg)

* * * * * * * * * *
## Introduction
The **AVG** (Array Average) function block calculates the arithmetic mean (average) of all elements in an integer array. It is designed for use in control engineering and enables rapid statistical analysis of measured values or process data.
## Interface Structure
### **Event Inputs**

| Event | With Data |
|---|---|
| `REQ` | `A` |

### **Event Outputs**

| Event | With Data |
|---|---|
| `CNF` | *(Result Output)*, `A` |

### **Data Inputs**

| Name | Type | Initial Value | Comment |
|---|---|---|---|
| `A` | `ARRAY[*] OF INT` | – | Array of integers whose average is calculated (InOut variable) |

### **Data Outputs**

| Name | Type | Initial Value | Comment |
|---|---|---|---|
*(no name)* | `REAL` | – | Result of the average value |

### **Adapters**
None.

## Functionality

1. The function block is activated by the event `REQ`. The data array `A` is then used.

2. Internally, a loop is executed from `LOWER_BOUND(A,1)` to `UPPER_BOUND(A,1)` to sum all elements.

3. The number of elements is determined from `UPPER_BOUND(A,1) - LOWER_BOUND(A,1) + 1`.

4. The sum is accumulated as `DINT` and then divided by the number of elements. The result is converted into a value `REAL` and made available at the output.

5. After the calculation is complete, the event `CNF` is triggered. The output value is then available.

## Technical Features
- **Dynamic Array Size**: The function block accepts arrays of arbitrary length (indicated by `ARRAY[*]`), allowing for flexible adaptation to different data volumes.
- **Type Conversions**: The sum is represented as `DINT` (double word) to prevent overflows with large arrays. Division is performed after conversion to `REAL`, resulting in a floating-point value.
- **No State Machine**: The function block is purely functional – `REQ` is immediately followed by `CNF`. There are no internal states or delays.

## State Overview
Since this is a **combinatorial function block**, there are no explicit states. The process is as follows:

- Initial: Wait for `REQ`
- After `REQ`: Calculation and immediate output of `CNF`

## Application Scenarios
- **Averaging of Sensor Data**: Smoothing of measured values (e.g., temperature, pressure) over a defined measurement cycle.
- **Average Calculation in Batch Processes**: Determination of the average fill level, weight, or other process parameters.
- **Statistical Evaluation in Quality Control**: For example, calculating the diameter of multiple test specimens as a floating-point value for accuracy analysis.

## Comparison with Similar Function Blocks

| Feature | **AVG** | Typical IEC 61131-3 AVG Function Block |
|---|---|---|
| **Parameterization** | Dynamic via array (no limit) | Often static array size or lists |
**Event-driven** | Yes (REQ/CNF) | No (pure function) |
**Output type** | `REAL` | Usually `REAL` or `LREAL` |
**Overflow protection** | Sum as `DINT` | Dependent on implementation |

This function block combines IEC 61499 event control with the compact logic of an IEC 61131-3 average function block, making it particularly suitable for distributed automation systems.

## Conclusion
The **AVG** function block offers a simple and efficient way to calculate the average of an integer array in real time. Its dynamic array support and clear event interface make it a universal tool for averaging in industrial control applications. The seamless integration into the 4diac IDE and the transparent calculation logic ensure high reusability and ease of understanding.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
