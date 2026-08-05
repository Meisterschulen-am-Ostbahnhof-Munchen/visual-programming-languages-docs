# F_MOD
![F_MOD](https://user-images.githubusercontent.com/116869307/214143235-f81abc8c-2970-409c-8626-aeb9ec537286.png)

* * * * * * * * * *
![F_MOD](F_MOD.svg)
## Introduction
The **F_MOD** is an arithmetic function block for calculating the remainder of a division, developed under the EPL-2.0 license. Version 1.0 enables the modulo operation for integer data types according to the IEC 61131-3 standard.

## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with dividend and divisor)

### **Event Outputs**
- `CNF`: Calculation confirmation (with remainder)

### **Data Inputs**
- `IN1` (ANY_INT): Dividend (integer)
- `IN2` (ANY_INT): Divisor (integer)

### **Data Outputs**
- `OUT` (ANY_NUM): Remainder of division (IN1 mod IN2)

## Functionality

1. **Activation**:

- Triggered by the `REQ` event
- Processes two integer values

2. **Modulo Operation**:

- Calculates IN1 modulo IN2
- Formula: OUT = IN1 - (IN1 / IN2) * IN2
- Supported types: INT, DINT, UINT, UDINT

3. **Result Output**:

- `CNF` event with residual value
- Sign corresponds to dividend (IN1)

## Technical Specifications

✔ **Integer Modulo Operation**
✔ **Support for Signed and Unsigned Types**

✔ **IEC 61131-3 Compliant**
✔ **Deterministic Execution**

## Application Examples
- **Cyclic Counting**: Ring Buffer Indices
- **Time Calculations**: Weekday Determination
- **Message Processing**: Checksum Calculation
- **Positioning**: Stepper Motor Control

## Error Handling
- **Division by Zero**:
- OUT = IN1 (Original value is retained)
- No execution interruption
- **Type incompatibility**:
- Automatic type matching
- No exception generation

## Special Notes
- **Sign handling**:
- Result has the sign of the dividend
- Example: (-7 mod 3) = -1
- **Performance**:
- Optimized calculation for all integer types
- One cycle latency

## ⚖️ Comparison with similar function blocks

| Feature | F_MOD | F_DIV | F_REM |

|----------------|--------|---------|---------|

| Operation | Modulo | Division | Remainder |

| Input types | ANY_INT| ANY_NUM | ANY_NUM |

| Output type | ANY_NUM| ANY_NUM | ANY_NUM |

## Conclusion

The F_MOD function block offers essential functions for cyclic calculations:

- Efficient residual value calculation
- Flexible type support
- Reliable error handling

Indispensable for control applications with periodic patterns or index calculations. Its standards-compliant implementation enables its use in real-time systems with deterministic requirements.
