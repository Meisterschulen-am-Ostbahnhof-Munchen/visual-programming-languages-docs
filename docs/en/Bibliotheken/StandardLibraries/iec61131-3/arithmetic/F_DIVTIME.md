# F_DIVTIME

![F_DIVTIME](https://github.com/user-attachments/assets/c442ada4-119c-4919-be55-9c5e0d7acb7c)

* * * * * * * * * *
![F_DIVTIME](F_DIVTIME.svg)
## Introduction

The **F_DIVTIME** function block is a specialized function module for dividing time values by numerical factors, developed under the EPL 2.0 license. Version 1.0 enables precise time calculations using TIME and ANY_NUM data types.

## Interface Structure

### **Event Inputs**

- `REQ`: Calculation request (with input values)

### **Event Outputs**

- `CNF`: Calculation confirmation (with result)

### **Data Inputs**

- `IN1` (TIME): Time duration to be divided
- `IN2` (ANY_NUM): Divisor (numeric value)

### **Data Outputs**

- `OUT` (TIME): Result of the division (IN1 / IN2)

## Functionality

1. **Activation**:
- Triggered by the `REQ` event
- Processes TIME values and numeric divisors
2. **Calculation**:
- Divides time value (IN1) by numeric value (IN2)
- Performs automatic type conversion
- Calculation accurate to milliseconds
3. **Result Output**:
- `CNF` event with new TIME value
- Format: T#1d5h30m15s250ms

## Technical Specifications

✔ **Precise Time Division**
✔ **Support for ANY_NUM divisors**
✔ **Calculation accurate to milliseconds**
✔ **Automatic Type Conversion**

## Application Examples

- **Process Optimization**: Average Cycle Time Calculation
- **Production Planning**: Time Allocation to Stations
- **Robot Control**: Speed Adjustment
- **Energy Management**: Consumption Time Calculations

## Error Handling

- **Division by Zero**:
- OUT = T#0s
- No Aborting Execution
- **Type Incompatibility**:
- OUT = IN1 (original value is retained)
- No exception generation

## Special Notes

- **Calculation Accuracy**:
- Minimum 1 millisecond
- Rounding to the nearest millisecond
- **Validity Range**:
- Positive time values (T#0s to T#106751d23h47m16s854ms)
- Divisor must be positive

## ⚖️ Comparison with Standard F_DIV

| Feature | F_DIVTIME | F_DIV |
|----------------|-----------|-------------|
| Input Type 1 | TIME | ANY_NUM |
| Input Type 2 | ANY_NUM | ANY_NUM |
| Output Type | TIME | ANY_NUM |

## Conclusion

The F_DIVTIME function block offers essential functions for time-based calculations:

- Precise division of time values
- Flexible input parameters
- Reliable error handling

Especially valuable for applications requiring the division of time intervals. The specialized implementation guarantees correct results for all valid input combinations.
