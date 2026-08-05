# F_DIV
![F_DIV](https://user-images.githubusercontent.com/116869307/214143200-dff8deec-3ba6-4ac9-aad3-6418b42506c1.png)

* * * * * * * * * *
## Introduction
The **F_DIV** is a standards-compliant function block for dividing numeric values, developed under the EPL-2.0 license. Version 1.0 enables type-safe division of various numeric data types according to the IEC 61131-3 standard.
![F_DIV](F_DIV.svg)

## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with dividend and divisor)

### **Event Outputs**
- `CNF`: Calculation confirmation (with division result)

### **Data Inputs**
- `IN1` (ANY_NUM): Dividend (numerator)
- `IN2` (ANY_NUM): Divisor (denominator)

### **Data Outputs**
- `OUT` (ANY_NUM): Result of division (IN1 / IN2)

## Functional Principle

1. **Calculation Trigger**:

- `REQ` event with values for IN1 and IN2
- Both inputs must be of type ANY_NUM

2. **Division**:

- Type-preserving calculation (IN1 / IN2)
- Supported types:
- Integers (INT, DINT)
- Floating-point numbers (REAL, LREAL)
- Mixed types (automatic conversion)

3. **Result Output**:

- `CNF` event with calculated OUT value
- Floating-point result for integer division

## Technical Features

✔ **Type-safe division** (ANY_NUM support)
✔ **Automatic type conversion**

✔ **IEC 61131-3 compliant**
✔ **Deterministic execution**

## Error Handling
- **Division by zero**:
- OUT = 0 (for Integers)
- OUT = INF/NAN (for floating-point numbers)
- No execution abort
- **Type incompatibility**:
- OUT = 0
- No exception generation

## Application Scenarios
- **Process control**: Control deviation calculation
- **Data analysis**: Normalization of measured values
- **Machine control**: Speed calculations
- **Energy management**: Efficiency calculations

## ⚖️ Comparison with similar function blocks

| Feature | F_DIV | F_MUL | F_ADD |
|---------------|--------|--------|--------|
| Operation | Division | Multiplication | Addition |
| Inputs | 2 | 2 | 2 |
| Type support | ANY_NUM | ANY_NUM | ANY_NUM |

## Supported Data Types

| Category | Examples |
|----------------|-------------------------|
| Integers | INT, DINT, UDINT |
| Floating Point | REAL, LREAL |
| Type Combinations | INT/REAL, DINT/LREAL |

## 🛠️ Related Exercises
* [Exercise_111](../../../../Uebungen/test_B/Uebungen_doc/Uebung_111.md)

## Conclusion

The F_DIV function block offers a robust solution for division operations:

- Type-safe calculation
- Flexible input combinations
- Standards-compliant implementation

Particularly valuable for applications requiring precise calculations with variable inputs. Automatic type conversion and error handling make it a reliable function block in industrial control systems.
