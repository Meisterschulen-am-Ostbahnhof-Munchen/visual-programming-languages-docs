# F_SUB_DATE_DATE
![F_SUB_DATE_DATE](https://github.com/user-attachments/assets/07c56b47-428f-4e2c-b365-402ef41717ba)

* * * * * * * * * *
![F_SUB_DATE_DATE](F_SUB_DATE_DATE.svg)
## Introduction
The **F_SUB_DATE_DATE** function block is a standards-compliant function block for calculating time differences between two date values, developed under the EPL-2.0 license. Version 1.0 enables the precise calculation of time intervals according to the IEC 61131-3 standard.

## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with start and end date)

### **Event Outputs**
- `CNF`: Calculation confirmation (with time difference)

### **Data Inputs**
- `IN1` (DATE): Start date (minuend)
- `IN2` (DATE): End date (subtrahend)

### **Data Outputs**
- `OUT` (TIME): Calculated time interval (IN1 - IN2)

## Operating Principle

1. **Calculation Trigger**:

- `REQ` event with two DATE values
- Both inputs must be of type DATE

2. **Difference Calculation**:

- Conversion of both date values to seconds since January 1, 1970
- Subtraction of the timestamps (IN1 - IN2)
- Conversion to the TIME data type

3. **Result Output**:

- `CNF` event with calculated time interval
- Positive values if IN1 > IN2, negative values if IN1 < IN2

## Technical Features

✔ **Precise Time Difference** (Accurate to the Day)
✔ **Leap Year Consideration**

✔ **Negative Time Intervals** for Retrospective Calculations
✔ **Platform-Independent Time Calculation**

## Application Scenarios
- **Process Duration Calculation**: Production time between two dates
- **Maintenance Intervals**: Remaining time until next maintenance
- **Project Planning**: Time remaining until deadline
- **Inventory Management**: Shelf Life Calculation

## Error Handling
- **Date Limits**:
- Supports the range 1970-01-01 to 2106-02-07
- On exceedance: OUT = T#0s
- **Type Incompatibility**:
- OUT = T#0s
- No exception generation

## ⚖️ Comparison with Similar Function Blocks

| Feature | F_SUB_DATE_DATE | F_SUB_TIME | F_SUB_DT_DT |
|---------------|-----------------|------------|-------------|
| Input Types | DATE - DATE | TIME - TIME | DT - DT |
| Output Type | TIME | TIME | TIME |
| Accuracy | Day-accurate | Nanosecond | Microsecond |

## Conclusion

The F_SUB_DATE_DATE function block offers an optimized solution for date differences:

- Calendar-accurate calculations
- Easy handling of time intervals
- Standards-compliant implementation

Particularly valuable for applications with deadline-related calculations and long-term scheduling.
