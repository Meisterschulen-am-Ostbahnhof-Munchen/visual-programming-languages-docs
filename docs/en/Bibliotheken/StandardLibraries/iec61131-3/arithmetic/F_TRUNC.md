# F_TRUNC
![F_TRUNC](https://github.com/user-attachments/assets/b944edcb-c90b-41d8-98e6-3c3b81e50e9f)

* * * * * * * * * *
![F_TRUNC](F_TRUNC.svg)
## Introduction
The **F_TRUNC** function block is a standards-compliant function block for rounding floating-point numbers toward zero, developed under the EPL-2.0 license. Version 1.0 enables type-safe conversion according to the IEC 61131-3 standard.

*
## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with input value)

### **Event Outputs**
- `CNF`: Calculation confirmation (with rounded value)

### **Data Inputs**
- `IN` (ANY_REAL): Input value (floating-point number)

### **Data Outputs**
- `OUT` (ANY_INT): Rounded integer value

## Functional Principle

1. **Calculation Trigger**:

- `REQ` event with an ANY_REAL value
- Supported types: REAL, LREAL

2. **Truncation Operation**:

- Removes decimal places without Rounding
- Example: 3.9 → 3, -2.7 → -2
- No mathematical rounding (≠ F_ROUND)

3. **Result Output**:

- `CNF` event with integer result
- Automatic type conversion (INT, DINT, etc.)

## Technical Features

✔ **Lossless Type Conversion**

✔ **Consistent Truncation Toward Zero**

✔ **Deterministic Execution**

✔ **No Overflow Exceptions**

## Application Scenarios
- **Data Preprocessing**: Index Calculations
- **Measurement Processing**: Discretization
- **Control Logic**: Integer Position Calculations
- **Financial Calculations**: Currency Conversions

## Error Handling
- **Value Range Exceedance**:
- For values that are too large: Limit to the target type maximum
- No exception generation
- **Special Cases**:
- NaN → 0

±INF → Maximum value of the target type

## ⚖️ Comparison with similar function blocks

| Feature | F_TRUNC | F_ROUND | F_FLOOR |

|---------------|----------|----------|----------|

| Operation | Direction Zero | Mathematical | Round Down |

| Example | 3.9 → 3 | 3.9 → 4 | 3.9 → 3 |

| Example | -2.7 → -2 | -2.7 → -3 | -2.7 → -3 |

## Conclusion

The F_TRUNC function block offers a precise solution for integer conversion:

- Predictable behavior (truncation toward zero)
- Type-safe floating-point-to-integer conversion
- Robust handling of extreme values

Essential for all applications with precise range boundaries and index calculations.
