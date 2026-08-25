# F_SUB_TOD_TOD

![F_SUB_TOD_TOD](https://github.com/user-attachments/assets/24f90fce-ebfe-4c5f-9449-ddf8e41a6821)

* * * * * * * * * *
![F_SUB_TOD_TOD](F_SUB_TOD_TOD.svg)
## Introduction

The **F_SUB_TOD_TOD** function block is a standards-compliant function block for calculating time differences between two times of day (TIME_OF_DAY), developed under the EPL-2.0 license. Version 1.0 enables precise time-of-day calculations according to the IEC 61131-3 standard.

## Interface Structure

### **Event Inputs**

- `REQ`: Calculation request (with start and end time of day)

### **Event Outputs**

- `CNF`: Calculation confirmation (with time difference)

### **Data Inputs**

- `IN1` (TIME_OF_DAY): Start time of day (TOD#hh:mm:ss)
- `IN2` (TIME_OF_DAY): End time of day

### **Data Outputs**

- `OUT` (TIME): Calculated time interval (IN1 - IN2)

## Operating Principle

1. **Calculation Trigger**:
- `REQ` event with two TIME_OF_DAY values
- Valid range: TOD#00:00:00 to TOD#23:59:59.999999
2. **Difference Calculation**:
- Conversion of both values to seconds since midnight
- Difference calculation with 24-hour overflow consideration
- Result as TIME data type
3. **Result Output**:
- `CNF` event with calculated interval
- Positive values for IN1 > IN2 (within the same day)
- Negative values at the end of the day

## Technical Features

✔ **Microsecond Accuracy**
✔ **Automatic 24-hour Overflow Handling**

✔ **Bidirectional Difference Calculation**

✔ **Real-Time Capable Execution**

## Application Scenarios

- **Time and Attendance Recording**: Shift Duration Calculation
- **Energy Management**: Peak Load Analysis
- **Production Logistics**: Throughput Time Measurement
- **Building Automation**: Daylight Utilization Times

## Error Handling

- **Special Cases**:
- IN1 = IN2 → OUT = T#0s
- Across midnight: OUT = -(24h - Difference)
- Example: TOD#01:00:00 - TOD#23:00:00 = T#-22h
- **Limit Values**:
- Maximum Difference: ±T#23:59:59.999999
- No Overflow Exception

## ⚖️ Comparison with Similar Function Blocks

| Feature | F_SUB_TOD_TOD | F_SUB_DT_DT | F_SUB_TIME |
|---------------|---------------|---------------|--------------|
| Input Types | TOD - TOD | DT - DT | TIME - TIME |
| Output Type | TIME | TIME | TIME |
| Special Features | 24-hour circular | Calendar-based | Simple difference |

## Conclusion

The F_SUB_TOD_TOD function block offers the optimal solution for calculating time-of-day differences:

- Precise handling of day transitions
- Simple measurement of operating time intervals
- Standards-compliant implementation

Especially valuable for all applications with time-of-day-dependent process analyses.
