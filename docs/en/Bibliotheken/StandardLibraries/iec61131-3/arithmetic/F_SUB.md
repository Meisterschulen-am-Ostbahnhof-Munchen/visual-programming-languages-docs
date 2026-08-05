# F_SUB
![F_SUB](https://user-images.githubusercontent.com/116869307/214143366-6c54d805-8807-48bd-b8fb-2ad08dd2f1b8.png)

* * * * * * * * * *
![F_SUB](F_SUB.svg)
## Introduction
The **F_SUB** is a standards-compliant function block for subtracting numeric values, developed under the EPL-2.0 license. Version 1.0 enables type-safe subtraction of various numeric data types according to the IEC 61131-3 standard.

## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with minuend and subtrahend)

### **Event Outputs**
- `CNF`: Calculation confirmation (with result)

### **Data Inputs**
- `IN1` (ANY_MAGNITUDE): Minuend (value from which to subtract)
- `IN2` (ANY_MAGNITUDE): Subtrahend (value to be subtracted)

### **Data Outputs**
- `OUT` (ANY_MAGNITUDE): Difference of the subtraction (IN1 - IN2)

## Operating Principle

1. **Calculation Trigger**:

- `REQ` event with values for IN1 and IN2
- Both inputs must be of type ANY_MAGNITUDE

2. **Subtraction**:

- Type-preserving calculation (IN1 - IN2)
- Supported types:
- Integers (INT, DINT)
- Floating-point numbers (REAL, LREAL)
- Time values (TIME, DATE)
- Mixed types (automatic conversion)

3. **Result output**:

- `CNF` event with calculated difference
- Result in the "largest" input type

## Technical Features

✔ **Type-safe subtraction** (ANY_MAGNITUDE support)
✔ **Automatic type conversion**

✔ **Underrun protection**
✔ **Deterministic execution**

## Application Scenarios
- **Process control**: Deviation Calculation
- **Data Analysis**: Difference Calculation of Measured Values
- **Machine Control**: Position Differences
- **Time Control**: Time Interval Calculations

## Error Handling
- **Underflow Handling**:
- Wrap-around for integers
- -INF for floating-point underflow
- **Type Incompatibility**:
- OUT = 0
- No Exception Generation

## ⚖️ Comparison with Similar Function Blocks

| Feature | F_SUB | F_ADD | F_MUL |
|---------------|--------|--------|--------|
| Operation | Subtraction | Addition | Multiplication |
| Inputs | 2 | 2 | 2 |
| Type Support | ANY_MAGNITUDE | ANY_NUM | ANY_NUM |

## 🛠️ Related Exercises
* [Exercise_040](../../../../Uebungen/test_B/Uebungen_doc/Uebung_040.md)]
* [Exercise_040_2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_040_2.md)]
* [Exercise_040_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_040_AX.md)]
* [Exercise_041](../../../../Uebungen/test_B/Uebungen_doc/Uebung_041.md)]
* [Exercise_072c](../../../../Uebungen/test_B/Uebungen_doc/Uebung_072c.md)]

## Conclusion

The F_SUB function block offers a robust solution for subtraction operations:

- Precise type-preserving calculations
- Flexible input combinations
- Standards-compliant implementation

Particularly valuable for applications that need to implement difference calculations or relative changes. Automatic type conversion makes it an indispensable tool in industrial control systems.
