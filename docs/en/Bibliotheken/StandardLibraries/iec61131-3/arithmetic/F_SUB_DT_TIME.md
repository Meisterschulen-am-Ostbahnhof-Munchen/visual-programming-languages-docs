# F_SUB_DT_TIME
![F_SUB_DT_TIME](https://github.com/user-attachments/assets/7408a361-8399-43ee-b55a-0e223571633e)

* * * * * * * * * *
![F_SUB_DT_TIME](F_SUB_DT_TIME.svg)
## Introduction
The **F_SUB_DT_TIME** function block is a standards-compliant function block for subtracting time intervals from timestamps, developed under the EPL-2.0 license. Version 1.0 enables precise time calculations according to the IEC 61131-3 standard.

## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with timestamp and time interval)

### **Event Outputs**
- `CNF`: Calculation confirmation (with corrected timestamp)

### **Data Inputs**
- `IN1` (DATE_AND_TIME): Base time
- `IN2` (TIME): Time interval to be subtracted

### **Data Outputs**
- `OUT` (DATE_AND_TIME): Calculated time (IN1 - IN2)

## Functional Principle

1. **Calculation Trigger**:

- `REQ` event with DATE_AND_TIME and TIME value
- Time range: DT#1970-01-01-00:00:00 to DT#2106-02-07-06:28:15

2. **Time Calculation**:

- Conversion to epoch microseconds
- Subtraction of the time interval
- Calendar-accurate back-calculation

3. **Result Output**:

- `CNF` event with new timestamp
- Automatic calendar correction (leap years, month ends)

## Technical Features

✔ **Microsecond accuracy**
✔ **Complete calendar arithmetic**
✔ **Negative time intervals** (time shift into the future)
✔ **Cross-platform consistency**

## Application Scenarios
- **Scheduling**: Deadline calculation
- **Process control**: Predetermining start times
- **Maintenance systems**: Planning preventive maintenance Maintenance
- **Data Analysis**: Historical Time Correction

## Error Handling
- **Time Range Exceedance**:
- In case of underflow: OUT = DT#1970-01-01-00:00:00
- In case of overflow: OUT = DT#2106-02-07-06:28:15
- **Special Cases**:
- IN2 = T#0s → OUT = IN1
- IN2 negative → Addition at time

## ⚖️ Comparison with similar function blocks

| Feature | F_SUB_DT_TIME | F_ADD_DT_TIME | F_SUB_DT_DT |
|----------------|----------------|---------------|--------------|
| Operation | Time - Interval | Time + Interval | Time - Time |
Result | DATE_AND_TIME | DATE_AND_TIME | TIME |
Accuracy | Microseconds | Microseconds | Microseconds |

## Conclusion

The F_SUB_DT_TIME function block offers a reliable solution for time calculations:

- Industrial-grade precision
- Full calendar support
- Intuitive handling of time intervals

Essential for all applications involving date-related calculations and historical time analysis.
