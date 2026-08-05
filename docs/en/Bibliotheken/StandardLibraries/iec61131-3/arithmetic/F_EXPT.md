# F_EXPT
![F_EXPT](https://github.com/user-attachments/assets/0446a2d1-6283-400f-976d-18ac9c482b25)

* * * * * * * * * *
![F_EXPT](F_EXPT.svg)
## Introduction
The **F_EXPT** function block is a mathematical function module for calculating power values, developed under the EPL-2.0 license. Version 1.0 enables the calculation of base-exponent combinations with ANY_REAL data types.

## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with base and exponent)

### **Event Outputs**
- `CNF`: Calculation confirmation (with result)

### **Data Inputs**
- `IN1` (ANY_REAL): Base value
- `IN2` (ANY_REAL): Exponent

### **Data Outputs**
- `OUT` (ANY_REAL): Result of exponentiation (IN1^IN2)

## Functionality

1. **Activation**:

- Triggered by the `REQ` event
- Processes two ANY_REAL values

2. **Calculation**:

- Calculates IN1 raised to the power of IN2
- Supports all REAL and LREAL combinations
- Automatic type conversion (higher accuracy)

3. **Result Output**:

- `CNF` event with calculated power value
- Result in the more accurate input type

## Technical Specifications

✔ **Precise power calculation**

✔ **Support for REAL and LREAL**

✔ **Automatic type conversion**

✔ **IEC 61131-3 compliant**

## Application Examples
- **Physical calculations**: Acceleration formulas
- **Financial mathematics**: Compound interest calculation
- **Control engineering**: Nonlinear characteristics
- **Signal processing**: Exponential filters

## Error Handling
- **Invalid inputs**:
- Negative base with non-integer exponent: OUT = 0
- Zero to a negative exponent: OUT = +INF
- Infinity calculations according to IEEE 754

## Special Notes
- **Accuracy**:
- LREAL inputs produce LREAL results
- REAL inputs produce REAL results
- Mixed inputs: LREAL result
- **Performance**:
- LREAL calculations require more cycles
- For real-time applications, prefer REAL

## ⚖️ Comparison with similar building blocks

| Feature | F_EXPT | F_LN | F_POWER |

|----------------|---------|---------|---------|

| Function | a^b | ln(a) | a^b |

| Input types | ANY_REAL| ANY_REAL| ANY_NUM |

| Accuracy | High | High | Medium |

## Conclusion

The F_EXPT function block offers powerful mathematical functions:

- Precise exponential calculations
- Flexible input combinations
- Reliable error handling

Indispensable for advanced control algorithms requiring nonlinear calculations. Its standards-compliant implementation enables its use in demanding industrial applications.
