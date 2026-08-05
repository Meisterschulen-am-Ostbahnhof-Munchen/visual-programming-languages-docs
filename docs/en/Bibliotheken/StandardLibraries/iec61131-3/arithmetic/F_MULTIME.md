# F_MULTIME

![F_MULTIME](https://github.com/user-attachments/assets/89982d6d-aa50-4897-b32c-6d280da63b1a)

* * * * * * * * * *

![F_MULTIME](F_MULTIME.svg)

## Introduction
The **F_MULTIME** function block is a standards-compliant function block for multiplying time values by numerical factors, developed under the EPL-2.0 license. Version 1.0 enables type-safe scaling of time intervals according to the IEC 61131-3 standard.


## Interface Structure

### **Event Inputs**

- `REQ`: Calculation request (with time value and multiplier)

### **Event Outputs**

- `CNF`: Calculation confirmation (with scaled time value)

### **Data Inputs**

- `IN1` (TIME): Time value (base value)

- `IN2` (ANY_NUM): Scaling factor

### **Data Outputs**

- `OUT` (TIME): Scaled time value (IN1 × IN2)

## Functional Principle

1. **Calculation Trigger**:

- `REQ` event with time value (IN1) and factor (IN2)

- IN1 must be of type TIME, IN2 must be of type ANY_NUM

2. **Multiplication**:

- Time value is converted to nanoseconds

- Multiplication by a numeric factor

- Conversion back to TIME data type

3. **Result Output**:

- `CNF` event with scaled time value

- Result always of type TIME

## Technical Features

✔ **Type-safe time value processing**

✔ **Precise nanosecond calculation**

✔ **Automatic type conversion** (ANY_NUM → REAL)

✔ **Overflow protection** (limit to maximum TIME value)

## Application Scenarios

- **Cycle time adjustment**: Scaling of time intervals

- **Process control**: Lengthening/shortening of timeouts

- **Motion control**: Speed adjustments

- **Scheduling**: Dynamic Schedule Scaling

## Error Handling

- **Overflow Handling**:

- Limit to T#24d20h31m23s647ms (Maximum)

- No wrap-around for time values

- **Type Incompatibility**:

- OUT = T#0s

- No exception generation

## ⚖️ Comparison with Similar Function Blocks

| Feature | F_MULTIME | F_MUL | F_DIVTIME |

|----------------|-----------|---------|----------|

| Operation | Time Multiplication | Numeric Multiplication | Time Division |

| Inputs | TIME × ANY_NUM | ANY_NUM × ANY_NUM | TIME ÷ ANY_NUM |

| Output Type | TIME | ANY_NUM | TIME |

## 🛠️ Related Exercises

* [Exercise_020c2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_020c2.md)]

## Conclusion

The F_MULTIME function block offers a specialized solution for scaling time values:

- Industrial-grade precision (nanosecond basis)
- Safe type conversion
- Robust overflow handling

Essential for applications with dynamically adjustable time parameters and cyclical control processes.