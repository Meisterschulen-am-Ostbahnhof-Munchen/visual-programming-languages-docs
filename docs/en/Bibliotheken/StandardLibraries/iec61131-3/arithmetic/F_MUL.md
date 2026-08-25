# F_MUL

![F_MUL](https://user-images.githubusercontent.com/116869307/214143289-3262368c-fae6-4fc7-bd1d-b2b445c245c9.png)

* * * * * * * * * *
![F_MUL](F_MUL.svg)
## Introduction

The **F_MUL** is a standards-compliant function block for multiplying numeric values, developed under the EPL-2.0 license. Version 1.0 enables type-safe multiplication of various numeric data types according to the IEC 61131-3 standard.

## Interface Structure

### **Event Inputs**

- `REQ`: Calculation request (with two factors)

### **Event Outputs**

- `CNF`: Calculation confirmation (with result)

### **Data Inputs**

- `IN1` (ANY_NUM): First factor
- `IN2` (ANY_NUM): Second factor

### **Data Outputs**

- `OUT` (ANY_NUM): Product of the multiplication (IN1 × IN2)

## Operating Principle

1. **Calculation Trigger**:
- `REQ` event with values for IN1 and IN2
- Both inputs must be of type ANY_NUM be
2. **Multiplication**:
- Type-preserving calculation (IN1 × IN2)
- Supported types:
- Integers (INT, DINT)
- Floating-point numbers (REAL, LREAL)
- Mixed types (automatic conversion)
3. **Result output**:
- `CNF` event with calculated product
- Result in the "largest" input type

## Technical Features

✔ **Type-safe multiplication** (ANY_NUM support)
✔ **Automatic type conversion**

✔ **Overflow protection**
✔ **Deterministic execution**

## Application Scenarios

- **Process control**: Scaling calculations
- **Data analysis**: Measured value processing
- **Machine control**: Position calculations
- **Energy management**: Power calculations

## Error handling

- **Overflow handling**:
- Wrap-around in case of Integers
- ±INF (± infinity) on floating-point overflow
- **Type incompatibility**:
- OUT = 0
- No exception generation

## ⚖️ Comparison with similar function blocks

| Feature | F_MUL | F_ADD | F_DIV |
|---------------|--------|--------|--------|
| Operation | Multiplication | Addition | Division |
| Inputs | 2 | 2 | 2 |
| Type support | ANY_NUM | ANY_NUM | ANY_NUM |

## 🛠️ Related Exercises

* [Exercise_034b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_034b.md)

## Conclusion

The F_MUL function block offers a robust solution for multiplication operations:

- Precise type-preserving calculations
- Flexible input combinations
- Standards-compliant implementation

Particularly valuable for applications that need to implement scaled calculations or physical formulas. Automatic type conversion makes it a versatile tool in industrial control systems.
