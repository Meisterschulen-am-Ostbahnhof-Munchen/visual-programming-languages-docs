# ADD_3

![ADD_3](https://user-images.githubusercontent.com/116869307/214143012-431cb6ed-2e5c-4316-a5b8-ab7a341eeb37.png)

* * * * * * * * * *
## Introduction

The **ADD_3** is an enhanced version of the adder for calculating the sum of three values, developed under the EPL-2.0 license. Version 1.0 offers type-safe addition for various numeric data types according to the IEC 61131-3 standard.
![ADD_3](ADD_3.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Calculation request (with three input values)

### **Event Outputs**

- `CNF`: Calculation confirmation (with sum result)

### **Data Inputs**

- `IN1` (ANY_MAGNITUDE): First addend
- `IN2` (ANY_MAGNITUDE): Second addend
- `IN3` (ANY_MAGNITUDE): Third addend

### **Data Outputs**

- `OUT` (ANY_MAGNITUDE): Result of addition (IN1 + IN2) + IN3)

## Operating Principle

1. **Requirement**:
- The `REQ` event triggers the calculation
- All three input values are evaluated simultaneously
2. **Calculation**:
- Type-preserving summation
- Supports all ANY_MAGNITUDE types:
- Integers (INT, DINT)
- Floating-point numbers (REAL, LREAL)
- Time values (TIME, LTIME)
3. **Result Output**:
- The `CNF` event with the calculated OUT value
- Automatic type conversion for mixed inputs

## Technical Features

✔ **Three-input addition** in a single operation
✔ **Generic implementation** (GEN_ADD class)

✔ **Broad type support** (ANY_MAGNITUDE)
✔ **Deterministic execution**

## Typical Use Cases

- **Measurement Aggregation**: Summing data from multiple sensors
- **Energy Balancing**: Calculating total energy consumption
- **Positioning Technology**: Multidimensional coordinates
- **Production Statistics**: Quantity measurement

## ⚖️ Comparison with ADD_2

| Feature | ADD_3 | ADD_2 |
|---------------|--------|--------|
| Inputs | 3 | 2 |
| Calculation | IN1+IN2+IN3 | IN1+IN2 |
| Performance | Higher efficiency with 3 inputs | Lightweight |

## Error Handling

- In case of type incompatibility:
- OUT = 0 (numeric types)
- Empty value (non-numeric types)
- Execution is not aborted

## 🛠️ Related Exercises

* [Exercise_087](../../../../Uebungen/test_B/Uebungen_doc/Uebung_087.md)
* [Exercise_087a1](../../../../Uebungen/test_B/Uebungen_doc/Uebung_087a1.md)

## Conclusion

The ADD_3 block expands the possibilities of type-safe addition:

- Efficient triple summation
- Consistent type handling
- Optimized performance compared to serial ADD_2 usage

Particularly advantageous for applications with multiple values to be aggregated. The generic implementation allows for maximum flexibility in heterogeneous control environments.
