# ADD_2
![ADD_2](https://user-images.githubusercontent.com/116869307/214142966-3facb074-7909-40e0-a9c9-4588e1bfc938.png)
* * * * * * * * * *
## Introduction
The **ADD_2** is a generic function block for adding two values, developed under the EPL-2.0 license. Version 1.0 supports various numeric data types according to the IEC 61131-3 standard.
![ADD_2](ADD_2.svg)

## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with input values)

### **Event Outputs**
- `CNF`: Calculation confirmation (with result)

### **Data Inputs**
- `IN1` (ANY_MAGNITUDE): First summand
- `IN2` (ANY_MAGNITUDE): Second summand

### **Data Outputs**
- `OUT` (ANY_MAGNITUDE): Sum result

## Functionality

1. **Calculation Request**:

- `REQ` event with Values for IN1 and IN2

2. **Addition**:

- Type-preserving calculation (IN1 + IN2)
- Supported types: INT, DINT, REAL, LREAL, etc.

3. **Result Output**:

- `CNF` event with calculated OUT value
- Automatic type adjustment

## Technical Features

✔ **Generic Implementation** (GEN_ADD)
✔ **Type-Flexible** Inputs/Outputs
✔ **IEC 61131-3 compliant**
✔ **Deterministic** calculation

## Supported Data Types

| Type | Example |

|----------|--------------------|

| INT | 123 + 456 = 579 |

| REAL | 1.23 + 4.56 = 5.79 |

| TIME | T#1s + T#2s = T#3s |

LREAL | 1.23e10 + 4.56e10 |

## Application Scenarios
- **Process Control**: Signal Processing
- **Data Analysis**: Measurement Aggregation
- **Machine Control**: Position Calculation
- **Energy Management**: Consumption Summing

## ⚖️ Comparison with Similar Function Blocks

| Feature | ADD_2 | ADD_4 | MUL_2 |

|---------------|--------|--------|--------|

| Operation | Addition | Addition | Multiplication |

| Inputs | 2 | 4 | 2 |

| Type Support | ANY_MAG | ANY_MAG | ANY_MAG |

## Error Handling
- Type incompatibility results in:
- OUT = 0 (for numeric types)
- Empty value (for other types)
- No exception generation

## 🛠️ Related Exercises
* [Exercise_000](../../../../Uebungen/test_B/Uebungen_doc/Uebung_000.md)
* [Exercise_000_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_000_AX.md)
* [Exercise_110](../../../../Uebungen/test_B/Uebungen_doc/Uebung_110.md)
* [Exercise_111](../../../../Uebungen/test_B/Uebungen_doc/Uebung_111.md)

## Conclusion

The ADD_2 block offers a flexible solution for arithmetic operations:

- Simple yet powerful addition
- Broad type support
- Standards-compliant implementation

Especially valuable for applications requiring type-safe calculations with variable inputs. The generic implementation allows for reuse in a wide variety of control contexts.