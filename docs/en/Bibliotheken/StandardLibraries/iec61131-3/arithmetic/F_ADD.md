# F_ADD

![Additionsbaustein](https://github.com/user-attachments/assets/3173760a-3b67-48dc-b078-43bcfc56423a)

* * * * * * * * * *

![F_ADD](F_ADD.svg)

## Introduction
The **F_ADD** is a standards-compliant arithmetic function block according to IEC 61131-3, developed by TU Wien ACIN under the EPL-2.0 license. Version 1.0 enables type-safe addition of values (ANY_MAGNITUDE) for industrial control applications.


## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with input values)

### **Event Outputs**
- `CNF`: Calculation confirmation (with result)

### **Data Inputs**
- `IN1` (ANY_MAGNITUDE): First operand
- `IN2` (ANY_MAGNITUDE): Second operand

### **Data Outputs**
- `OUT` (ANY_MAGNITUDE): Sum of IN1 and IN2

## Functionality

1. **Activation**:

- Triggered by the `REQ` event

- Processes both input values simultaneously

2. **Type Handling**:

- Supports all ANY_MAGNITUDE types:

- Numeric types (INT, DINT, REAL, LREAL)

- Time types (TIME, LTIME)

- Automatic type conversion

3. **Computation**:

- Executes IN1 + IN2

- Maintains the highest input accuracy

4. **Result Output**:

- `CNF` event with computation result

- Latency: One execution cycle

## Technical Specifications

✔ **Generic Type Support** (ANY_MAGNITUDE)
✔ **Deterministic Execution**
✔ **Overflow Protection**
✔ **IEC 61131-3 Compliant**

## Supported Data Types

| Category | Examples |

-----------------|--------------------------|

| Integers | INT, DINT, UINT, UDINT |
| Floating Point | REAL, LREAL |

| Time | TIME, LTIME |

| Mixed | INT + REAL → REAL |

## Application Examples

- **Process Control**: Signal Conditioning
- **Measurement Systems**: Sensor Value Aggregation
- **Motion Control**: Position Calculations
- **Energy Management**: Consumption Summing

## ⚖️ Comparison with Similar Function Blocks

| Feature | F_ADD | F_SUB | F_MUL |

|--------------|---------|---------|---------|

| Operation | Addition | Subtraction | Multiplication |

| Input Types | ANY_MAGNITUDE | ANY_MAGNITUDE | ANY_NUM |

| Output Type | Equals Input Type | Equals | Equals |


## Error Handling

- **Overflow**: Wrap-around for integers, ±INF for floating-point numbers
- **Type Mismatch**: Automatic type matching
- **Invalid Input**: Returns 0/default value

## Special Notes

- For time calculations: TIME + TIME → TIME

- Mixed operations use the "higher" type

- No implicit scaling (e.g., 100ms + 1s = 1100ms)

## Conclusion

The F_ADD block offers essential arithmetic functions:

- Robust, type-safe addition
- Consistent behavior across all data types
- Seamless integration into control algorithms

Its standardized implementation makes it a reliable component for industrial automation systems that require precise arithmetic operations with various data types.