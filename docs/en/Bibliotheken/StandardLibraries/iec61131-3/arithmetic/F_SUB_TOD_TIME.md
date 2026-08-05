# F_SUB_TOD_TIME

![F_SUB_TOD_TIME](https://github.com/user-attachments/assets/6e8ab24c-c318-4a9f-916c-777af4e7be34)

* * * * * * * * * *

![F_SUB_TOD_TIME](F_SUB_TOD_TIME.svg)

## Introduction
The **F_SUB_TOD_TIME** function block is a standards-compliant function block for subtracting time intervals from times of day (TIME_OF_DAY), developed under the EPL 2.0 license. Version 1.0 enables time-of-day-related calculations according to the IEC 61131-3 standard.


## Interface Structure

### **Event Inputs**
- `REQ`: Calculation request (with time of day and time interval)

### **Event Outputs**
- `CNF`: Calculation confirmation (with corrected time of day)

### **Data Inputs**
- `IN1` (TIME_OF_DAY): Base time of day (TOD#hh:mm:ss)
- `IN2` (TIME): Time interval to be subtracted

### **Data Outputs**
- `OUT` (TIME_OF_DAY): Calculated time of day (IN1 - IN2)

## Operating Principle

1. **Calculation Trigger**:

- `REQ` event with TIME_OF_DAY and TIME value

- Valid range: TOD#00:00:00 to TOD#23:59:59.999999

2. **Time Calculation**:

- Conversion to seconds since midnight

- Subtraction of the time interval

- Time-of-day calculation with overflow handling

3. **Result Output**:

- `CNF` event with new time of day

- Automatic 24-hour overflow (circular calculation)

## Technical Features

✔ **Microsecond Accuracy**
✔ **24-hour Overflow Handling** (circular time of day)
✔ **Negative Intervals** (time addition)
✔ **Real-time Calculation**

## Application Scenarios

- **Shift Planning**: Calculating the start of work
- **Lighting Control**: Correct sunrise times
- **Production Planning**: Calculate machine run times
- **Traffic Control Systems**: Schedule adjustments

## Error Handling

- **Overflow Handling**:

- In case of overrun: circular calculation (modulo 24h)

- Example: TOD#01:00:00 - T#2h = TOD#23:00:00

- **Special Cases**:

- IN2 = T#0s → OUT = IN1

- IN2 negative → Add the time (TOD#10:00 + T#-2h = TOD#12:00)

## ⚖️ Comparison with similar function blocks

| Feature | F_SUB_TOD_TIME | F_ADD_TOD_TIME | F_SUB_DT_TIME |

|---------------|----------------|----------------|---------------|

| Operation | Time of Day - Interval | Time of Day + Interval | Timestamp - Interval |

| Result | TIME_OF_DAY | TIME_OF_DAY | DATE_AND_TIME |

| Overflow | 24-hour Circular | 24-hour Circular | Calendar-based |

## Conclusion

The F_SUB_TOD_TIME block offers an optimized solution for time-of-day calculations:

- Precise circular time calculation
- Easy handling of shift and operating hours

- Intuitive handling of day transitions

Ideal choice for all applications with time-of-day-dependent controls.