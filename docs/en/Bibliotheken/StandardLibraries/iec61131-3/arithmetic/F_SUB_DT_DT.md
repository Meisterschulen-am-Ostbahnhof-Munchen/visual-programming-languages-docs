# F_SUB_DT_DT
![F_SUB_DT_DT](https://github.com/user-attachments/assets/45767e49-775c-4efc-8b6e-28967afab782)

* * * * * * * * * *
![F_SUB_DT_DT](F_SUB_DT_DT.svg)
## Introduction
The **F_SUB_DT_DT** is a standards-compliant function block for the precise calculation of time differences between two timestamps (DATE_AND_TIME), developed under the EPL-2.0 license. Version 1.0 enables microsecond-accurate time interval calculations according to the IEC 61131-3 standard.

## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with start and end timestamps)

### **Event Outputs**
- `CNF`: Calculation confirmation (with time difference)

### **Data Inputs**
- `IN1` (DATE_AND_TIME): Start time (minuend)
- `IN2` (DATE_AND_TIME): End time (subtrahend)

### **Data Outputs**
- `OUT` (TIME): Calculated time interval (IN1 - IN2)

## Functional Principle

1. **Calculation Trigger**:

- `REQ` event with two DATE_AND_TIME values
- Format: DT#1970-01-01-00:00:00 to DT#2106-02-07-06:28:15

2. **Difference Calculation**:

- Conversion to epoch microseconds
- Subtraction of timestamps (IN1 - IN2)
- Conversion to TIME data type

3. **Result Output**:

- `CNF` event with calculated interval
- Positive values for IN1 > IN2, negative values for IN1 < IN2

## Technical Features

✔ **Microsecond Accuracy**

✔ **Time Zone-Independent Calculation** (UTC Base)

✔ **Full Calendar Arithmetic** (Leap Seconds, Month Lengths)
✔ **Cross-Platform Consistency**

## Application Scenarios
- **Process Analysis**: Precise Machine Runtime Measurement
- **Laboratory Automation**: Precise Response Time Calculation
- **Energy Monitoring**: Consumption Period Differences
- **PLC Diagnostics**: Event Timestamp Evaluation

## Error Handling
- **Time Range Exceedance**:
- Supports DT#1970-01-01-00:00:00 to DT#2106-02-07-06:28:15
- On Overflow: OUT = T#0s
- **Invalid Inputs**:
- OUT = T#0s for invalid timestamps
- No Exception Generation

## ⚖️ Comparison with Similar Function Blocks

| Feature | F_SUB_DT_DT | F_SUB_DATE_DATE | F_SUB_TIME |
|---------------|----------------|-----------------|------------|
| Accuracy | Microseconds | Days | Nanoseconds |
| Input Type | DATE_AND_TIME | DATE | TIME |
| Typical Application | Process Diagnostics | Scheduling | Cycle Time |

## Conclusion

The F_SUB_DT_DT block offers the most precise solution for timestamp discrepancies:

- Industrial-grade microsecond accuracy
- Calendar-accurate UTC calculations
- Robust handling of large time intervals

Essential for high-precision process analysis and technical diagnostic systems.
